//
// Created by j00428315 on 2018/4/01.
//

#include "point_cloud_renderer.h"
#include "util.h"

namespace hello_ar {
    namespace {
        constexpr char kVertexShader[] = R"(
        attribute vec4 vertex;
        uniform mat4 mvp;
        void main() {
            gl_PointSize = 5.0;
            // Pointcloud vertex's w component is confidence value.
            // Not used in renderer.
            gl_Position = mvp * vec4(vertex.xyz, 1.0);
        })";

        constexpr char kFragmentShader[] = R"(
        precision lowp float;
        void main() {
            gl_FragColor = vec4(0.1215, 0.7372, 0.8235, 1.0);
        })";
    }  // namespace

    void PointCloudRenderer::InitializeGlContent() {
        shader_program_ = util::CreateProgram(kVertexShader, kFragmentShader);

        CHECK(shader_program_);

        attribute_vertices_ = glGetAttribLocation(shader_program_, "vertex");
        uniform_mvp_mat_ = glGetUniformLocation(shader_program_, "mvp");

        util::CheckGlError("point_cloud_renderer::InitializeGlContent()");
    }

    void PointCloudRenderer::Draw(glm::mat4 mvp_matrix, HwArSession *ar_session,
                                  HwArPointCloud *ar_point_cloud) const {
        CHECK(shader_program_);

        glUseProgram(shader_program_);

        int32_t number_of_points = 0;
        //LOGI("PointCloudRenderer::Draw00,number_of_points=%d",number_of_points);
        HwArPointCloud_getNumberOfPoints(ar_session, ar_point_cloud, &number_of_points);
        //LOGI("PointCloudRenderer::Draw,number_of_points=%d",number_of_points);

        if (number_of_points <= 0) {
            return;
        }

        const float *point_cloud_data;
        HwArPointCloud_getData(ar_session, ar_point_cloud, &point_cloud_data);
        glUniformMatrix4fv(uniform_mvp_mat_, 1, GL_FALSE, glm::value_ptr(mvp_matrix));
        //LOGI("PointCloudRenderer::Draw,number_of_points=%d------2",number_of_points);
        glEnableVertexAttribArray(attribute_vertices_);
        //LOGI("PointCloudRenderer::Draw,number_of_points=%d------3",number_of_points);
        glVertexAttribPointer(attribute_vertices_, 4, GL_FLOAT, GL_FALSE, 0,
                              point_cloud_data);
        //LOGI("PointCloudRenderer::Draw,number_of_points=%d------4",number_of_points);
        glDrawArrays(GL_POINTS, 0, number_of_points);
        //LOGI("PointCloudRenderer::Draw,number_of_points=%d------5",number_of_points);
        glUseProgram(0);
        util::CheckGlError("PointCloudRenderer::Draw");
        //LOGI("PointCloudRenderer::Draw,number_of_points=%d-----end",number_of_points);
    }

}  // namespace hello_ar
