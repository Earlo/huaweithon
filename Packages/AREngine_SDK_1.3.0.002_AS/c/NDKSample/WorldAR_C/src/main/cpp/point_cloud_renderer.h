//
// Created by j00428315 on 2018/4/01.
//

#ifndef C_AREngine_HELLOE_AR_POINT_CLOUD_RENDERER_H_
#define C_AREngine_HELLOE_AR_POINT_CLOUD_RENDERER_H_

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <cstdlib>
#include <vector>

#include "huawei_arengine_interface.h"
#include "glm.h"

namespace hello_ar {

    class PointCloudRenderer {
    public:
        // Default constructor of PointCloudRenderer.
        PointCloudRenderer() = default;

        // Default deconstructor of PointCloudRenderer.
        ~PointCloudRenderer() = default;

        // Initialize the GL content, needs to be called on GL thread.
        void InitializeGlContent();

        // Render the AR point cloud.
        //
        // @param mvp_matrix, the model view projection matrix of point cloud.
        // @param ar_session, the session that is used to query point cloud points
        //     from ar_point_cloud.
        // @param ar_point_cloud, point cloud data to for rendering.
        void Draw(glm::mat4 mvp_matrix, HwArSession *ar_session,
                  HwArPointCloud *ar_point_cloud) const;

    private:
        GLuint shader_program_;
        GLuint attribute_vertices_;
        GLuint uniform_mvp_mat_;
    };
}  // namespace hello_ar

#endif  // C_AREngine_HELLOE_AR_POINT_CLOUD_RENDERER_H_
