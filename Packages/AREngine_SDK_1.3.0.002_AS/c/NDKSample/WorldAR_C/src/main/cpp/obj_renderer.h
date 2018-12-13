//
// Created by j00428315 on 2018/4/01.
//

#ifndef C_AREngine_HELLOE_AR_OBJ_RENDERER_
#define C_AREngine_HELLOE_AR_OBJ_RENDERER_

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/asset_manager.h>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "huawei_arengine_interface.h"
#include "glm.h"

namespace hello_ar {

    // PlaneRenderer renders ARCore plane type.
    class ObjRenderer {
    public:
        ObjRenderer() = default;

        ~ObjRenderer() = default;

        // Loads the OBJ file and texture and sets up OpenGL resources used to draw
        // the model.  Must be called on the OpenGL thread prior to any other calls.
        void InitializeGlContent(AAssetManager *asset_manager,
                                 const std::string &obj_file_name,
                                 const std::string &png_file_name);

        // Sets the surface's lighting reflectace properties.  Diffuse is modulated by
        // the texture's color.
        void SetMaterialProperty(float ambient, float diffuse, float specular,
                                 float specular_power);

        // Draws the model.
        void Draw(const glm::mat4 &projection_mat, const glm::mat4 &view_mat,
                  const glm::mat4 &model_mat, float light_intensity,
                  const float *object_color4) const;

    private:
        // Shader material lighting pateremrs
        float ambient_ = 0.0f;
        float diffuse_ = 3.5f;
        float specular_ = 1.0f;
        float specular_power_ = 6.0f;

        // Model attribute arrays
        std::vector<GLfloat> vertices_;
        std::vector<GLfloat> uvs_;
        std::vector<GLfloat> normals_;

        // Model triangle indices
        std::vector<GLushort> indices_;

        // Loaded TEXTURE_2D object name
        GLuint texture_id_;

        // Shader program details
        GLuint shader_program_;
        GLuint attri_vertices_;
        GLuint attri_uvs_;
        GLuint attri_normals_;
        GLuint uniform_mvp_mat_;
        GLuint uniform_mv_mat_;
        GLuint uniform_texture_;
        GLuint uniform_lighting_param_;
        GLuint uniform_material_param_;
        GLint uniform_color_;
    };
}  // namespace hello_ar

#endif  // C_AREngine_HELLOE_AR_OBJ_RENDERER_
