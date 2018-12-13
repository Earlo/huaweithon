//
// Created by j00428315 on 2018/4/01.
//

// This modules handles drawing the passthrough camera image into the OpenGL
// scene.

#include <type_traits>

#include "background_renderer.h"

namespace hello_ar {
    namespace {
        // Positions of the quad vertices in clip space (X, Y, Z).
        const GLfloat kVertices[] = {
                -1.0f, -1.0f, 0.0f, +1.0f, -1.0f, 0.0f,
                -1.0f, +1.0f, 0.0f, +1.0f, +1.0f, 0.0f,
        };

        // UVs of the quad vertices (S, T)
        const GLfloat kUvs[] = {
                0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        };

        constexpr char kVertexShader[] = R"(
        attribute vec4 vertex;
        attribute vec2 textureCoords;
        varying vec2 v_textureCoords;
        void main() {
            v_textureCoords = textureCoords;
            gl_Position = vertex;
        })";

        constexpr char kFragmentShader[] = R"(
        #extension GL_OES_EGL_image_external : require
        precision mediump float;
        uniform samplerExternalOES texture;
        varying vec2 v_textureCoords;
        void main() {
            gl_FragColor = texture2D(texture, v_textureCoords);
        })";

    }  // namespace

    void BackgroundRenderer::InitializeGlContent() {
        shader_program_ = util::CreateProgram(kVertexShader, kFragmentShader);

        if (!shader_program_) {
            LOGE("Could not create program.");
        }

        glGenTextures(1, &texture_id_);
        glBindTexture(GL_TEXTURE_EXTERNAL_OES, texture_id_);
        glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_EXTERNAL_OES, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        uniform_texture_ = glGetUniformLocation(shader_program_, "texture");
        attribute_vertices_ = glGetAttribLocation(shader_program_, "vertex");
        attribute_uvs_ = glGetAttribLocation(shader_program_, "textureCoords");
    }

    void BackgroundRenderer::Draw(const HwArSession *session, const HwArFrame *frame) {
        static_assert(std::extent<decltype(kUvs)>::value == kNumVertices * 2,
                      "Incorrect kUvs length");
        static_assert(std::extent<decltype(kVertices)>::value == kNumVertices * 3,
                      "Incorrect kVertices length");

        // If display rotation changed (also includes view size change), we need to
        // re-query the uv coordinates for the on-screen portion of the camera image.
        int32_t geometry_changed = 0;
        HwArFrame_getDisplayGeometryChanged(session, frame, &geometry_changed);
        if (geometry_changed != 0 || !uvs_initialized_) {
            HwArFrame_transformDisplayUvCoords(session, frame, kNumVertices * 2, kUvs,
                                               transformed_uvs_);
            LOGI("BackgroundRenderer::Draw(),transformed_uvs_=%f,%f,%f,%f,%f,%f,%f,%f",
                 transformed_uvs_[0], transformed_uvs_[1], transformed_uvs_[2], transformed_uvs_[3],
                 transformed_uvs_[4], transformed_uvs_[5], transformed_uvs_[6],
                 transformed_uvs_[7]);

            uvs_initialized_ = true;
        }

        glUseProgram(shader_program_);
        glDepthMask(GL_FALSE);

        glUniform1i(uniform_texture_, 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_EXTERNAL_OES, texture_id_);

        glEnableVertexAttribArray(attribute_vertices_);
        glVertexAttribPointer(attribute_vertices_, 3, GL_FLOAT, GL_FALSE, 0,
                              kVertices);

        glEnableVertexAttribArray(attribute_uvs_);
        glVertexAttribPointer(attribute_uvs_, 2, GL_FLOAT, GL_FALSE, 0,
                              transformed_uvs_);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glUseProgram(0);
        glDepthMask(GL_TRUE);
        util::CheckGlError("BackgroundRenderer::Draw() error");
    }

    GLuint BackgroundRenderer::GetTextureId() const { return texture_id_; }

}  // namespace hello_ar
