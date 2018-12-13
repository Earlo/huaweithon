//
// Created by j00428315 on 2018/4/01.
//

#include "hello_ar_application.h"
#include <android/asset_manager.h>
#include <array>
#include "plane_renderer.h"
#include "util.h"
#include <jni.h>

namespace hello_ar {
    namespace {

        constexpr size_t kMaxNumberOfAndroidsToRender = 20;
        constexpr int32_t kPlaneColorRgbaSize = 16;

        const glm::vec3 kWhite = {255, 255, 255};

        constexpr std::array<uint32_t, kPlaneColorRgbaSize> kPlaneColorRgba = {
                0xFFFFFFFF, 0xF44336FF, 0xE91E63FF, 0x9C27B0FF, 0x673AB7FF, 0x3F51B5FF,
                0x2196F3FF, 0x03A9F4FF, 0x00BCD4FF, 0x009688FF, 0x4CAF50FF, 0x8BC34AFF,
                0xCDDC39FF, 0xFFEB3BFF, 0xFFC107FF, 0xFF9800FF};

        inline glm::vec3 GetRandomPlaneColor() {
            const int32_t colorRgba = kPlaneColorRgba[std::rand() % kPlaneColorRgbaSize];
            return glm::vec3(((colorRgba >> 24) & 0xff) / 255.0f,
                             ((colorRgba >> 16) & 0xff) / 255.0f,
                             ((colorRgba >> 8) & 0xff) / 255.0f);
        }
    }  // namespace

    HelloArApplication::HelloArApplication(AAssetManager *asset_manager)
            : asset_manager_(asset_manager) {
        LOGI("HelloArApplication-----OnCreate()");
    }

    HelloArApplication::~HelloArApplication() {
        if (ar_session_ != nullptr) {
            HwArSession_destroy(ar_session_);
            HwArFrame_destroy(ar_frame_);
        }
    }

    void HelloArApplication::OnPause() {
        LOGI("HelloArApplication-----OnPause()");
        if (ar_session_ != nullptr) {
            HwArSession_pause(ar_session_);
        }
    }

    void HelloArApplication::OnResume(void *env, void *context, void *activity) {
        LOGI("HelloArApplication-----OnResume()");

        HwArEnginesAvaliblity engines = HwArEnginesSelector_checkAllAvailableEngines(env, activity);
        LOGI("HelloArApplication-----jds added ---1--- OnResume():Check_EnginesAvailability,engines=%d",
             engines);

        HwArEnginesSelector_setAREngine(HWAR_ENGINE);
        //HwArApk_getCreatedEngine(&objectIndex);
        //LOGI("HelloArApplication-----OnResume(),objectIndex=%d",objectIndex);
        if (ar_session_ == nullptr) {
            HwArInstallStatus install_status;
            // If install was not yet requested, that means that we are resuming the
            // activity first time because of explicit user interaction (such as
            // launching the application)
            bool user_requested_install = !install_requested_;


            CHECK(HwArEnginesApk_requestInstall(env, activity, user_requested_install,
                                                &install_status) == HWAR_SUCCESS);
            switch (install_status) {
                case HWAR_INSTALL_STATUS_INSTALLED:
                    break;
                case HWAR_INSTALL_STATUS_INSTALL_REQUESTED:
                    install_requested_ = true;
                    return;
            }

            CHECK(HwArSession_create(env, context, &ar_session_) == HWAR_SUCCESS);
            CHECK(ar_session_);

            HwArConfig *ar_config = nullptr;
            HwArConfig_create(ar_session_, &ar_config);

            CHECK(ar_config);

            const HwArStatus status = HwArSession_checkSupported(ar_session_, ar_config);
            CHECK(status == HWAR_SUCCESS);

            CHECK(HwArSession_configure(ar_session_, ar_config) == HWAR_SUCCESS);

            HwArConfig_destroy(ar_config);

            HwArFrame_create(ar_session_, &ar_frame_);
            CHECK(ar_frame_);

            HwArSession_setDisplayGeometry(ar_session_, display_rotation_, width_,
                                           height_);
        }

        const HwArStatus status = HwArSession_resume(ar_session_);
        CHECK(status == HWAR_SUCCESS);
    }

    void HelloArApplication::OnSurfaceCreated() {
        LOGI("HelloArApplication-----OnSurfaceCreated()");
        created_engine = HwArEnginesSelector_getCreatedEngine();
        //LOGI("HelloArApplication-----OnSurfaceCreated(),objectIndex=%d",objectIndex);
        background_renderer_.InitializeGlContent();
        point_cloud_renderer_.InitializeGlContent();
        if (created_engine == HWAR_ENGINE) {
            andy_renderer_.InitializeGlContent(asset_manager_, "AR_logo.obj", "AR_logo.png");
        } else if (created_engine == GOOGLE_ARCORE) {
            andy_renderer_.InitializeGlContent(asset_manager_, "andy.obj", "andy.png");
        } else {
            LOGE("HelloArApplication: get object index error!!!");
        }
        //andy_renderer_.InitializeGlContent(asset_manager_, "AR_logo.obj", "AR_logo.png");
        plane_renderer_.InitializeGlContent(asset_manager_);
    }

    void HelloArApplication::OnDisplayGeometryChanged(int display_rotation,
                                                      int width, int height) {
        LOGI("HelloArApplication-----OnSurfaceChanged(%d, %d)", width, height);
        glViewport(0, 0, width, height);
        display_rotation_ = display_rotation;
        width_ = width;
        height_ = height;
        if (ar_session_ != nullptr) {
            HwArSession_setDisplayGeometry(ar_session_, display_rotation, width, height);
        }
    }

    void HelloArApplication::OnDrawFrame() {
        LOGI("HelloArApplication-----OnDrawFrame()");
        // Render the scene.
        glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (ar_session_ == nullptr) return;

        HwArSession_setCameraTextureName(ar_session_,
                                         background_renderer_.GetTextureId());

        // Update session to get current frame and render camera background.
        if (HwArSession_update(ar_session_, ar_frame_) != HWAR_SUCCESS) {
            LOGE("HelloArApplication::OnDrawFrame ArSession_update error");
        }

        HwArCamera *ar_camera;
        HwArFrame_acquireCamera(ar_session_, ar_frame_, &ar_camera);

        glm::mat4 view_mat;
        glm::mat4 projection_mat;
        HwArCamera_getViewMatrix(ar_session_, ar_camera, glm::value_ptr(view_mat));
        //LOGI("HelloArApplication-----OnDrawFrame() HwArCamera_getViewMatrix=%f,%f",glm::value_ptr(view_mat)[0],glm::value_ptr(view_mat)[1]);
        HwArCamera_getProjectionMatrix(ar_session_, ar_camera, 0.1f, /*far=*/100.f, glm::value_ptr(projection_mat));
        //LOGI("HelloArApplication-----OnDrawFrame() HwArCamera_getProjectionMatrix=%f,%f",glm::value_ptr(projection_mat)[0],glm::value_ptr(projection_mat)[1]);
        HwArTrackingState camera_tracking_state;
        HwArCamera_getTrackingState(ar_session_, ar_camera, &camera_tracking_state);
        HwArCamera_release(ar_camera);

        background_renderer_.Draw(ar_session_, ar_frame_);

        // If the camera isn't tracking don't bother rendering other objects.
        if (camera_tracking_state != HWAR_TRACKING_STATE_TRACKING) {
            return;
        }

        // Get light estimation value.
        HwArLightEstimate *ar_light_estimate;
        HwArLightEstimateState ar_light_estimate_state;
        HwArLightEstimate_create(ar_session_, &ar_light_estimate);

        HwArFrame_getLightEstimate(ar_session_, ar_frame_, ar_light_estimate);
        HwArLightEstimate_getState(ar_session_, ar_light_estimate,
                                   &ar_light_estimate_state);

        // Set light intensity to default. Intensity value ranges from 0.0f to 1.0f.
        float light_intensity = 0.8f;
        if (ar_light_estimate_state == HWAR_LIGHT_ESTIMATE_STATE_VALID) {
            HwArLightEstimate_getPixelIntensity(ar_session_, ar_light_estimate,
                                                &light_intensity);
        }

        HwArLightEstimate_destroy(ar_light_estimate);
        ar_light_estimate = nullptr;

        // Render Andy objects.
        glm::mat4 model_mat(1.0f);
        for (const auto &colored_anchor : colored_anchors_) {
            HwArTrackingState tracking_state = HWAR_TRACKING_STATE_STOPPED;
            HwArAnchor_getTrackingState(ar_session_, colored_anchor.anchor, &tracking_state);
            if (tracking_state == HWAR_TRACKING_STATE_TRACKING) {
                // Render object only if the tracking state is AR_TRACKING_STATE_TRACKING.
                util::GetTransformMatrixFromAnchor(ar_session_, colored_anchor.anchor, &model_mat);
                //if user AR_logo.obj, we need to downscale the model
                if (created_engine == 1) {
                    model_mat = glm::scale(model_mat, glm::vec3(0.2f, 0.2f, 0.2f));
                }
                andy_renderer_.Draw(projection_mat, view_mat, model_mat, light_intensity,
                                    colored_anchor.color);
            }
        }

        // Update and render planes.
        HwArTrackableList *plane_list = nullptr;
        HwArTrackableList_create(ar_session_, &plane_list);
        CHECK(plane_list != nullptr);

        HwArTrackableType plane_tracked_type = HWAR_TRACKABLE_PLANE;
        HwArSession_getAllTrackables(ar_session_, plane_tracked_type, plane_list);

        int32_t plane_list_size = 0;
        HwArTrackableList_getSize(ar_session_, plane_list, &plane_list_size);
        plane_count_ = plane_list_size;

        for (int i = 0; i < plane_list_size; ++i) {
            HwArTrackable *ar_trackable = nullptr;
            HwArTrackableList_acquireItem(ar_session_, plane_list, i, &ar_trackable);
            HwArPlane *ar_plane = HwArAsPlane(ar_trackable);
            HwArTrackingState out_tracking_state;
            HwArTrackable_getTrackingState(ar_session_, ar_trackable,
                                           &out_tracking_state);

            HwArPlane *subsume_plane;
            HwArPlane_acquireSubsumedBy(ar_session_, ar_plane, &subsume_plane);
            if (subsume_plane != nullptr) {
                HwArTrackable_release(HwArAsTrackable(subsume_plane));
                continue;
            }

            if (HwArTrackingState::HWAR_TRACKING_STATE_TRACKING != out_tracking_state) {
                continue;
            }

            HwArTrackingState plane_tracking_state;
            HwArTrackable_getTrackingState(ar_session_, HwArAsTrackable(ar_plane),
                                           &plane_tracking_state);
            if (plane_tracking_state == HWAR_TRACKING_STATE_TRACKING) {
                const auto iter = plane_color_map_.find(ar_plane);
                glm::vec3 color;
                if (iter != plane_color_map_.end()) {
                    color = iter->second;

                    // If this is an already observed trackable release it so it doesn't
                    // leave an additional reference dangling.
                    HwArTrackable_release(ar_trackable);
                } else {
                    // The first plane is always white.
                    if (!first_plane_has_been_found_) {
                        first_plane_has_been_found_ = true;
                        color = kWhite;
                    } else {
                        color = GetRandomPlaneColor();
                    }
                    plane_color_map_.insert({ar_plane, color});
                }

                plane_renderer_.Draw(projection_mat, view_mat, ar_session_, ar_plane,
                                     color);
            }
        }

        HwArTrackableList_destroy(plane_list);
        plane_list = nullptr;

        // Update and render point cloud.
        HwArPointCloud *ar_point_cloud = nullptr;
        LOGI("HelloArApplication-----point_cloud_status == HWAR_SUCCESS-----");
        HwArStatus point_cloud_status =
                HwArFrame_acquirePointCloud(ar_session_, ar_frame_, &ar_point_cloud);
        if (point_cloud_status == HWAR_SUCCESS) {
            LOGI("HelloArApplication-----point_cloud_status == HWAR_SUCCESS");
            point_cloud_renderer_.Draw(projection_mat * view_mat, ar_session_,
                                       ar_point_cloud);
            LOGI("HelloArApplication-----point_cloud_status == HWAR_SUCCESS******");
            HwArPointCloud_release(ar_point_cloud);
        }
    }

    void HelloArApplication::OnTouched(float x, float y) {
        LOGI("HelloArApplication-----OnTouched()");
        if (ar_frame_ != nullptr && ar_session_ != nullptr) {
            HwArHitResultList *hit_result_list = nullptr;
            HwArHitResultList_create(ar_session_, &hit_result_list);
            CHECK(hit_result_list);
            HwArFrame_hitTest(ar_session_, ar_frame_, x, y, hit_result_list);

            int32_t hit_result_list_size = 0;
            HwArHitResultList_getSize(ar_session_, hit_result_list,
                                      &hit_result_list_size);

            // The hitTest method sorts the resulting list by distance from the camera,
            // increasing.  The first hit result will usually be the most relevant when
            // responding to user input.

            HwArHitResult *ar_hit_result = nullptr;
            HwArTrackableType trackable_type = HWAR_TRACKABLE_NOT_VALID;
            for (int32_t i = 0; i < hit_result_list_size; ++i) {
                HwArHitResult *ar_hit = nullptr;
                HwArHitResult_create(ar_session_, &ar_hit);
                HwArHitResultList_getItem(ar_session_, hit_result_list, i, ar_hit);

                if (ar_hit == nullptr) {
                    LOGE("HelloArApplication::OnTouched ArHitResultList_getItem error");
                    return;
                }

                HwArTrackable *ar_trackable = nullptr;
                HwArHitResult_acquireTrackable(ar_session_, ar_hit, &ar_trackable);
                HwArTrackableType ar_trackable_type = HWAR_TRACKABLE_NOT_VALID;
                HwArTrackable_getType(ar_session_, ar_trackable, &ar_trackable_type);
                // Creates an anchor if a plane or an oriented point was hit.
                if (HWAR_TRACKABLE_PLANE == ar_trackable_type) {
                    HwArPose *ar_pose = nullptr;
                    HwArPose_create(ar_session_, nullptr, &ar_pose);
                    HwArHitResult_getHitPose(ar_session_, ar_hit, ar_pose);
                    int32_t in_polygon = 0;
                    HwArPlane *ar_plane = HwArAsPlane(ar_trackable);
                    HwArPlane_isPoseInPolygon(ar_session_, ar_plane, ar_pose, &in_polygon);

                    // Use hit pose and camera pose to check if hittest is from the
                    // back of the plane, if it is, no need to create the anchor.
                    HwArPose *camera_pose = nullptr;
                    HwArPose_create(ar_session_, nullptr, &camera_pose);
                    HwArCamera *ar_camera;
                    HwArFrame_acquireCamera(ar_session_, ar_frame_, &ar_camera);
                    HwArCamera_getPose(ar_session_, ar_camera, camera_pose);
                    HwArCamera_release(ar_camera);
                    float normal_distance_to_plane = util::CalculateDistanceToPlane(
                            *ar_session_, *ar_pose, *camera_pose);

                    HwArPose_destroy(ar_pose);
                    HwArPose_destroy(camera_pose);
                    if (!in_polygon || normal_distance_to_plane < 0) {
                        continue;
                    }

                    ar_hit_result = ar_hit;
                    trackable_type = ar_trackable_type;
                    break;
                } else if (HWAR_TRACKABLE_POINT == ar_trackable_type) {
                    HwArPoint *ar_point = HwArAsPoint(ar_trackable);
                    HwArPointOrientationMode mode;
                    HwArPoint_getOrientationMode(ar_session_, ar_point, &mode);
                    if (HWAR_POINT_ORIENTATION_ESTIMATED_SURFACE_NORMAL == mode) {
                        ar_hit_result = ar_hit;
                        trackable_type = ar_trackable_type;
                        break;
                    }
                }
            }

            if (ar_hit_result) {
                // Note that the application is responsible for releasing the anchor
                // pointer after using it. Call ArAnchor_release(anchor) to release.
                HwArAnchor *anchor = nullptr;
                if (HwArHitResult_acquireNewAnchor(ar_session_, ar_hit_result, &anchor) !=
                    HWAR_SUCCESS) {
                    LOGE(
                            "HelloArApplication::OnTouched ArHitResult_acquireNewAnchor error");
                    return;
                }

                HwArTrackingState tracking_state = HWAR_TRACKING_STATE_STOPPED;
                HwArAnchor_getTrackingState(ar_session_, anchor, &tracking_state);
                if (tracking_state != HWAR_TRACKING_STATE_TRACKING) {
                    HwArAnchor_release(anchor);
                    return;
                }

                if (colored_anchors_.size() >= kMaxNumberOfAndroidsToRender) {
                    HwArAnchor_detach(ar_session_, colored_anchors_[0].anchor);
                    HwArAnchor_release(colored_anchors_[0].anchor);
                    colored_anchors_.erase(colored_anchors_.begin());
                }

                ColoredAnchor colored_anchor;
                colored_anchor.anchor = anchor;
                switch (trackable_type) {
                    case HWAR_TRACKABLE_POINT:
                        SetColor(66.0f, 133.0f, 244.0f, 255.0f, colored_anchor.color);
                        break;
                    case HWAR_TRACKABLE_PLANE:
                        SetColor(139.0f, 195.0f, 74.0f, 255.0f, colored_anchor.color);
                        break;
                    default:
                        SetColor(0.0f, 0.0f, 0.0f, 0.0f, colored_anchor.color);
                        break;
                }

                colored_anchors_.push_back(colored_anchor);
                HwArHitResult_destroy(ar_hit_result);
                ar_hit_result = nullptr;

                HwArHitResultList_destroy(hit_result_list);
                hit_result_list = nullptr;
            }
        }
    }

    void HelloArApplication::SetColor(float r, float g, float b, float a,
                                      float *color4f) {
        *(color4f) = r;
        *(color4f + 1) = g;
        *(color4f + 2) = b;
        *(color4f + 3) = a;
    }
}  // namespace hello_ar
