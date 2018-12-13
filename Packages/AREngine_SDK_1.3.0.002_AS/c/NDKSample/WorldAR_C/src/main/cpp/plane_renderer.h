//
// Created by j00428315 on 2018/4/01.
//

#ifndef C_AREngine_HELLOE_AR_PLANE_RENDERER_H_
#define C_AREngine_HELLOE_AR_PLANE_RENDERER_H_

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/asset_manager.h>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "huawei_arengine_interface.h"
#include "glm.h"

namespace hello_ar {

    // PlaneRenderer renders ARCore plane type.
    class PlaneRenderer {
    public:
        PlaneRenderer() = default;

        ~PlaneRenderer() = default;

        // Sets up OpenGL state used by the plane renderer.  Must be called on the
        // OpenGL thread.
        void InitializeGlContent(AAssetManager *asset_manager);

        // Draws the provided plane.
        void Draw(const glm::mat4 &projection_mat, const glm::mat4 &view_mat,
                  const HwArSession *ar_session, const HwArPlane *ar_plane,
                  const glm::vec3 &color);

    private:

        void UpdateForPlane(const HwArSession *ar_session, const HwArPlane *ar_plane);

        std::vector<glm::vec3> vertices_;
        std::vector<GLushort> triangles_;
        glm::mat4 model_mat_ = glm::mat4(1.0f);
        glm::vec3 normal_vec_ = glm::vec3(0.0f);

        //GLuint vertex_buffers_[2];
        GLuint texture_id_;

        GLuint shader_program_;
        GLint attri_vertices_;
        GLint uniform_mvp_mat_;
        GLint uniform_texture_;
        GLint uniform_model_mat_;
        GLint uniform_normal_vec_;
        GLint uniform_color_;
    };
}  // namespace hello_ar

#endif  // C_AREngine_HELLOE_AR_PLANE_RENDERER_H_
