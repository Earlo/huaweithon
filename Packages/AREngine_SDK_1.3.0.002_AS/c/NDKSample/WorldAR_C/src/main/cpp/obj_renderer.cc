//
// Created by j00428315 on 2018/4/01.
//

#include "obj_renderer.h"
#include "util.h"

namespace hello_ar {
    namespace {

        const glm::vec4 kLightDirection(0.0f, 1.0f, 0.0f, 0.0f);

        constexpr char kVertexShader[] = R"(
        uniform mat4 u_ModelView;
        uniform mat4 u_ModelViewProjection;

        attribute vec4 a_Position;
        attribute vec3 a_Normal;
        attribute vec2 a_TexCoord;

        varying vec3 v_ViewPosition;
        varying vec3 v_ViewNormal;
        varying vec2 v_TexCoord;

        void main() {
            v_ViewPosition = (u_ModelView * a_Position).xyz;
            v_ViewNormal = normalize((u_ModelView * vec4(a_Normal, 0.0)).xyz);
            v_TexCoord = a_TexCoord;
            gl_Position = u_ModelViewProjection * a_Position;
        })";

        constexpr char kFragmentShader[] = R"(
        precision mediump float;

        uniform sampler2D u_Texture;

        uniform vec4 u_LightingParameters;
        uniform vec4 u_MaterialParameters;

        varying vec3 v_ViewPosition;
        varying vec3 v_ViewNormal;
        varying vec2 v_TexCoord;
        uniform vec4 u_ObjColor;

        void main() {
            // We support approximate sRGB gamma.
            const float kGamma = 0.4545454;
            const float kInverseGamma = 2.2;

            // Unpack lighting and material parameters for better naming.
            vec3 viewLightDirection = u_LightingParameters.xyz;
            float lightIntensity = u_LightingParameters.w;

            float materialAmbient = u_MaterialParameters.x;
            float materialDiffuse = u_MaterialParameters.y;
            float materialSpecular = u_MaterialParameters.z;
            float materialSpecularPower = u_MaterialParameters.w;

            // Normalize varying parameters, because they are linearly interpolated in
            // the vertex shader.
            vec3 viewFragmentDirection = normalize(v_ViewPosition);
            vec3 viewNormal = normalize(v_ViewNormal);

            // Apply inverse SRGB gamma to the texture before making lighting
            // calculations.
            // Flip the y-texture coordinate to address the texture from top-left.
            vec4 objectColor = texture2D(u_Texture,
                    vec2(v_TexCoord.x, 1.0 - v_TexCoord.y));
            if (u_ObjColor.a >= 255.0) {
                float intensity = objectColor.r;
                objectColor.rgb = u_ObjColor.rgb * intensity / 255.0;
            }
            objectColor.rgb = pow(objectColor.rgb, vec3(kInverseGamma));

            // Ambient light is unaffected by the light intensity.
            float ambient = materialAmbient;

            // Approximate a hemisphere light (not a harsh directional light).
            float diffuse = lightIntensity * materialDiffuse *
                    0.5 * (dot(viewNormal, viewLightDirection) + 1.0);

            // Compute specular light.
            vec3 reflectedLightDirection = reflect(viewLightDirection, viewNormal);
            float specularStrength = max(0.0, dot(viewFragmentDirection,
                    reflectedLightDirection));
            float specular = lightIntensity * materialSpecular *
                    pow(specularStrength, materialSpecularPower);

            // Apply SRGB gamma before writing the fragment color.
            gl_FragColor.a = objectColor.a;
            gl_FragColor.rgb = pow(objectColor.rgb * (ambient + diffuse) + specular,
                vec3(kGamma));
        })";
    }  // namespace

    void ObjRenderer::InitializeGlContent(AAssetManager *asset_manager,
                                          const std::string &obj_file_name,
                                          const std::string &png_file_name) {
        shader_program_ = util::CreateProgram(kVertexShader, kFragmentShader);

        if (!shader_program_) {
            LOGE("Could not create program.");
        }

        uniform_mvp_mat_ = glGetUniformLocation(shader_program_, "u_ModelViewProjection");
        uniform_mv_mat_ = glGetUniformLocation(shader_program_, "u_ModelView");
        uniform_texture_ = glGetUniformLocation(shader_program_, "u_Texture");

        uniform_lighting_param_ =
                glGetUniformLocation(shader_program_, "u_LightingParameters");
        uniform_material_param_ =
                glGetUniformLocation(shader_program_, "u_MaterialParameters");
        uniform_color_ = glGetUniformLocation(shader_program_, "u_ObjColor");

        attri_vertices_ = glGetAttribLocation(shader_program_, "a_Position");
        attri_uvs_ = glGetAttribLocation(shader_program_, "a_TexCoord");
        attri_normals_ = glGetAttribLocation(shader_program_, "a_Normal");

        glGenTextures(1, &texture_id_);
        glBindTexture(GL_TEXTURE_2D, texture_id_);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (!util::LoadPngFromAssetManager(GL_TEXTURE_2D, png_file_name)) {
            LOGE("Could not load png texture for planes.");
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        LOGE("util::LoadObjFile start!");
        util::LoadObjFile(asset_manager, obj_file_name, &vertices_, &normals_, &uvs_,
                          &indices_);
        LOGE("util::LoadObjFile end!");

        util::CheckGlError("obj_renderer::InitializeGlContent()");
    }

    void ObjRenderer::SetMaterialProperty(float ambient, float diffuse,
                                          float specular, float specular_power) {
        ambient_ = ambient;
        diffuse_ = diffuse;
        specular_ = specular;
        specular_power_ = specular_power;
    }

    void ObjRenderer::Draw(const glm::mat4 &projection_mat,
                           const glm::mat4 &view_mat, const glm::mat4 &model_mat,
                           float light_intensity,
                           const float *object_color4) const {
        if (!shader_program_) {
            LOGE("shader_program is null.");
            return;
        }

        glUseProgram(shader_program_);

        glActiveTexture(GL_TEXTURE0);
        glUniform1i(uniform_texture_, 0);
        glBindTexture(GL_TEXTURE_2D, texture_id_);

        glm::mat4 mvp_mat = projection_mat * view_mat * model_mat;
        glm::mat4 mv_mat = view_mat * model_mat;
        glm::vec4 view_light_direction = glm::normalize(mv_mat * kLightDirection);

        glUniform4f(uniform_lighting_param_, view_light_direction[0],
                    view_light_direction[1], view_light_direction[2],
                    light_intensity);
        glUniform4f(uniform_material_param_, ambient_, diffuse_, specular_,
                    specular_power_);
        glUniform4fv(uniform_color_, 1, object_color4);

        glUniformMatrix4fv(uniform_mvp_mat_, 1, GL_FALSE, glm::value_ptr(mvp_mat));
        glUniformMatrix4fv(uniform_mv_mat_, 1, GL_FALSE, glm::value_ptr(mv_mat));

        // Note: for simplicity, we are uploading the model each time we draw it.  A
        // real application should use vertex buffers to upload the geometry once.

        glEnableVertexAttribArray(attri_vertices_);
        glVertexAttribPointer(attri_vertices_, 3, GL_FLOAT, GL_FALSE, 0,
                              vertices_.data());

        glEnableVertexAttribArray(attri_normals_);
        glVertexAttribPointer(attri_normals_, 3, GL_FLOAT, GL_FALSE, 0,
                              normals_.data());

        glEnableVertexAttribArray(attri_uvs_);
        glVertexAttribPointer(attri_uvs_, 2, GL_FLOAT, GL_FALSE, 0, uvs_.data());

        glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_SHORT,
                       indices_.data());

        glDisableVertexAttribArray(attri_vertices_);
        glDisableVertexAttribArray(attri_uvs_);
        glDisableVertexAttribArray(attri_normals_);

        glUseProgram(0);
        util::CheckGlError("obj_renderer::Draw()");
    }

}  // namespace hello_ar
