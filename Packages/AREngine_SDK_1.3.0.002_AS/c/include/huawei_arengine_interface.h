//
// Created by j00428315 on 2018/3/27.
//

#ifndef ARNDK_HWAR_INTERFACE_H
#define ARNDK_HWAR_INTERFACE_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <vector>
#include <string>

typedef struct HwArConfig_ HwArConfig;
typedef struct HwArSession_ HwArSession;
typedef struct HwArPose_ HwArPose;
typedef struct HwArCamera_ HwArCamera;
typedef struct HwArFrame_ HwArFrame;
typedef struct HwArLightEstimate_ HwArLightEstimate;
typedef struct HwArPointCloud_ HwArPointCloud;
typedef struct HwArImageMetadata_ HwArImageMetadata;
typedef struct HwArTrackable_ HwArTrackable;
typedef struct HwArTrackableList_ HwArTrackableList;
typedef struct HwArPlane_ HwArPlane;
typedef struct HwArPoint_ HwArPoint;
typedef struct HwArAnchor_ HwArAnchor;
typedef struct HwArAnchorList_ HwArAnchorList;
typedef struct HwArHitResult_ HwArHitResult;
typedef struct HwArHitResultList_ HwArHitResultList;
typedef struct ACameraMetadata ACameraMetadata;

typedef struct HwArHand_ HwArHand;
typedef struct HwArBody_ HwArBody;

typedef struct HwArFace_ HwArFace;
typedef struct HwArPose_ HwArFacePose;
typedef struct HwArFaceGeometry_ HwArFaceGeometry;
typedef struct HwArFaceBlendShapes_ HwArFaceBlendShapes;
typedef struct HwArCameraInfo_ HwArCameraInfo;

typedef struct HwArAugmentedImage_ HwArAugmentedImage;
typedef struct HWArAugmentedImageDatabase_ HwArAugmentedImageDatabase;
#ifdef __cplusplus

/// Upcasts to ArTrackable
inline HwArTrackable *HwArAsTrackable(HwArPlane *plane) {
    return reinterpret_cast<HwArTrackable *>(plane);
}

inline HwArTrackable *HwArAsTrackable(HwArPoint *point) {
    return reinterpret_cast<HwArTrackable *>(point);
}

inline HwArTrackable *ArAsTrackable(HwArAugmentedImage *augmented_image) {
    return reinterpret_cast<HwArTrackable *>(augmented_image);
}

/// downcasts to ArXXX
inline HwArPlane *HwArAsPlane(HwArTrackable *trackable) {
    return reinterpret_cast<HwArPlane *>(trackable);
}

inline HwArPoint *HwArAsPoint(HwArTrackable *trackable) {
    return reinterpret_cast<HwArPoint *>(trackable);
}

inline HwArAugmentedImage *ArAsAugmentedImage(HwArTrackable *trackable) {
    return reinterpret_cast<HwArAugmentedImage *>(trackable);
}
#endif

#if __cplusplus >= 201100
#define HWAR_DEFINE_ENUM(_type) enum _type : int32_t
#else
#define HWAR_DEFINE_ENUM(_type) \
  typedef int32_t _type;      \
  enum
#endif

HWAR_DEFINE_ENUM(HwArEnginesType) {
    HWAR_NONE = 0,
    HWAR_ENGINE = 1,
    GOOGLE_ARCORE = 2
};
HWAR_DEFINE_ENUM(HwArEnginesAvaliblity) {
    HWAR_NONE_ENGINES_SUPPORTED = 0,
    HWAR_ENGINE_SUPPORTED = 1,
    GOOGLE_ARCORE_SUPPORTED = 2,
    HWAR_BOTH_ENGINES_SUPPORTED = 3
};


HWAR_DEFINE_ENUM(HwArTrackableType) {
    HWAR_TRACKABLE_BASE_TRACKABLE = 0x41520100,
    HWAR_TRACKABLE_PLANE = 0x41520101,
    HWAR_TRACKABLE_POINT = 0x41520102,
    HWAR_TRACKABLE_AUGMENTED_IMAGE = 0x41520104,
    HWAR_TRACKABLE_HAND = 0x50000000,
    HWAR_TRACKABLE_BODY = 0x50000001,
    HWAR_TRACKABLE_FACE = 0x50000002,
    HWAR_TRACKABLE_TARGET_DETECTION = 0x50000003,
    HWAR_TRACKABLE_NOT_VALID = 0
};
HWAR_DEFINE_ENUM(HwArStatus) {
    HWAR_SUCCESS = 0,
    HWAR_ERROR_INVALID_ARGUMENT = -1,
    HWAR_ERROR_FATAL = -2,
    HWAR_ERROR_SESSION_PAUSED = -3,
    HWAR_ERROR_SESSION_NOT_PAUSED = -4,
    HWAR_ERROR_NOT_TRACKING = -5,
    HWAR_ERROR_TEXTURE_NOT_SET = -6,
    HWAR_ERROR_MISSING_GL_CONTEXT = -7,
    HWAR_ERROR_UNSUPPORTED_CONFIGURATION = -8,
    HWAR_ERROR_CAMERA_PERMISSION_NOT_GRANTED = -9,
    HWAR_ERROR_DEADLINE_EXCEEDED = -10,
    HWAR_ERROR_RESOURCE_EXHAUSTED = -11,
    HWAR_ERROR_NOT_YET_AVAILABLE = -12,
    HWAR_ERROR_CAMERA_NOT_AVAILABLE = -13,
    HWAR_UNAVAILABLE_ARSERVICE_NOT_INSTALLED = -100,
    HWAR_UNAVAILABLE_DEVICE_NOT_COMPATIBLE = -101,
    HWAR_UNAVAILABLE_APK_TOO_OLD = -103,
    HWAR_UNAVAILABLE_SDK_TOO_OLD = -104,
    HWAR_UNAVAILABLE_USER_DECLINED_INSTALLATION = -105,
    HWAR_UNAVAILABLE_EMUI_NOT_COMPATIBLE = -1000,
    HWAR_UNAVAILABLE_CONNECT_SERVER_TIME_OUT = -1001
};
HWAR_DEFINE_ENUM(HwArTrackingState) {
    HWAR_TRACKING_STATE_TRACKING = 0,
    HWAR_TRACKING_STATE_PAUSED = 1,
    HWAR_TRACKING_STATE_STOPPED = 2
};
HWAR_DEFINE_ENUM(HwArAvailability) {
    HWAR_AVAILABILITY_UNKNOWN_ERROR = 0,
    HWAR_AVAILABILITY_UNKNOWN_CHECKING = 1,
    HWAR_AVAILABILITY_UNKNOWN_TIMED_OUT = 2,
    HWAR_AVAILABILITY_UNSUPPORTED_DEVICE_NOT_CAPABLE = 100,
    HWAR_AVAILABILITY_SUPPORTED_NOT_INSTALLED = 201,
    HWAR_AVAILABILITY_SUPPORTED_APK_TOO_OLD = 202,
    HWAR_AVAILABILITY_SUPPORTED_INSTALLED = 203,
    HWAR_AVAILABILITY_UNSUPPORTED_EMUI_NOT_CAPABLE = 5000
};
HWAR_DEFINE_ENUM(HwArInstallStatus) {
    HWAR_INSTALL_STATUS_INSTALLED = 0,
    HWAR_INSTALL_STATUS_INSTALL_REQUESTED = 1
};
HWAR_DEFINE_ENUM(HwArInstallBehavior) {
    HWAR_INSTALL_BEHAVIOR_REQUIRED = 0,
    HWAR_INSTALL_BEHAVIOR_OPTIONAL = 1
};
HWAR_DEFINE_ENUM(HwArInstallUserMessageType) {
    HWAR_INSTALL_USER_MESSAGE_TYPE_APPLICATION = 0,
    HWAR_INSTALL_USER_MESSAGE_TYPE_FEATURE = 1,
    HWAR_INSTALL_USER_MESSAGE_TYPE_USER_ALREADY_INFORMED = 2
};
HWAR_DEFINE_ENUM(HwArLightEstimationMode) {
    HWAR_LIGHT_ESTIMATION_MODE_DISABLED = 0,
    HWAR_LIGHT_ESTIMATION_MODE_AMBIENT_INTENSITY = 1
};
HWAR_DEFINE_ENUM(HwArPlaneFindingMode) {
    HWAR_PLANE_FINDING_MODE_DISABLED = 0,
    HWAR_PLANE_FINDING_MODE_HORIZONTAL = 1,
    HWAR_PLANE_FINDING_MODE_VERTICAL = 2,
    HWAR_PLANE_FINDING_MODE_HORIZONTAL_AND_VERTICAL = 3
};
HWAR_DEFINE_ENUM(HwArUpdateMode) {
    HWAR_UPDATE_MODE_BLOCKING = 0,
    HWAR_UPDATE_MODE_LATEST_CAMERA_IMAGE = 1
};
HWAR_DEFINE_ENUM(HwArPowerMode) {
    HWAR_POWER_MODE_NORMAL = 0,
    HWAR_POWER_MODE_POWER_SAVING = 1,
    HWAR_POWER_MODE_ULTRA_POWER_SAVING = 2,
};

HWAR_DEFINE_ENUM(HwArEnableItem) {
    HWAR_ENABLE_NULL = 0,
    HWAR_ENABLE_DEPTH = 1<<0,
    HWAR_ENABLE_MASK = 1<<1,
};

HWAR_DEFINE_ENUM(HwArPlaneType) {
    HWAR_PLANE_HORIZONTAL_UPWARD_FACING = 0,
    HWAR_PLANE_HORIZONTAL_DOWNWARD_FACING = 1,
    HWAR_PLANE_VERTICAL_FACING = 2,
    HWAR_PLANE_UNKNOWN_FACING = 3
};
HWAR_DEFINE_ENUM(HwArLightEstimateState) {
    HWAR_LIGHT_ESTIMATE_STATE_NOT_VALID = 0,
    HWAR_LIGHT_ESTIMATE_STATE_VALID = 1
};
HWAR_DEFINE_ENUM(HwArType) {
    HWAR_TYPE_WORLD = 0x1,
    HWAR_TYPE_BODY = 0x2,
    HWAR_TYPE_HAND = 0x4,
    HWAR_TYPE_FACE = 0x10,
    HWAR_TYPE_IMAGE = 0x80
};
HWAR_DEFINE_ENUM(HwArCameraLensFacing) {
    HWAR_CAMERA_FACING_REAR = 0,
    HWAR_CAMERA_FACING_FRONT = 1
};
HWAR_DEFINE_ENUM(HwArHandFindingMode) {
    HwAr_HAND_FINDING_MODE_DISABLED = 0x0,
    HwAr_HAND_FINDING_MODE_2D_ENABLED = 0x1,
    HwAr_HAND_FINDING_MODE_3D_ENABLED = 0x2
};
HWAR_DEFINE_ENUM(HwArPointOrientationMode) {
    HWAR_POINT_ORIENTATION_INITIALIZED_TO_IDENTITY = 0,
    HWAR_POINT_ORIENTATION_ESTIMATED_SURFACE_NORMAL = 1
};
HWAR_DEFINE_ENUM(HwAr_Pose_Type) {
    HWAR_POSE_TYPE_IDENTITY = 0,
    HWAR_POSE_TYPE_ROTATE_Z_90,
    HWAR_POSE_TYPE_ROTATE_Z_180,
    HWAR_POSE_TYPE_ROTATE_Z_270,
    HWAR_POSE_TYPE_TYPE_MAX
};
HWAR_DEFINE_ENUM(HwArNativeWindowType) {
    HWAR_PREVIEW = 0,
    HWAR_VGA = 1,
    HWAR_METADATA = 2,
    HWAR_DEPTH = 4
};
HWAR_DEFINE_ENUM(HwArImageInputMode) {
    NON_INPUT = 0,
    EXTERNAL_INPUT_ALL = -1
};
HWAR_DEFINE_ENUM(HwArWorldMappingState) {
        HWAR_WORLD_MAPPING_NOT_AVAILABLE = -1,
        HWAR_WORLD_MAPPING_LIMITED = 0,
        HWAR_WORLD_MAPPING_EXTENDING,
        HWAR_WORLD_MAPPING_MAPPED
};

HWAR_DEFINE_ENUM(HwArAlignState) {
        HWAR_ALIGN_NONE = 0,
        HWAR_ALIGN_FAILED,
        HWAR_ALIGN_PROCESSING,
        HWAR_ALIGN_SUCCESS
};


HWAR_DEFINE_ENUM(HwArAnimojiBlendShape) {
    HwAr_Animoji_Eye_Blink_Left = 0,
    HwAr_Animoji_Eye_Look_Down_Left = 1,
    HwAr_Animoji_Eye_Look_In_Left = 2,
    HwAr_Animoji_Eye_Look_Out_Left = 3,
    HwAr_Animoji_Eye_Look_Up_Left = 4,
    HwAr_Animoji_Eye_Squint_Left = 5,
    HwAr_Animoji_Eye_Wide_Left = 6,
    HwAr_Animoji_Eye_Blink_Right = 7,
    HwAr_Animoji_Eye_Look_Down_Right = 8,
    HwAr_Animoji_Eye_Look_In_Right = 9,
    HwAr_Animoji_Eye_Look_Out_Right = 10,
    HwAr_Animoji_Eye_Look_Up_Right = 11,
    HwAr_Animoji_Eye_Squint_Right = 12,
    HwAr_Animoji_Eye_Wide_Right = 13,
    HwAr_Animoji_Jaw_Forward = 14,
    HwAr_Animoji_Jaw_Left = 15,
    HwAr_Animoji_Jaw_Right = 16,
    HwAr_Animoji_Jaw_Open = 17,
    HwAr_Animoji_Mouth_Funnel = 18,
    HwAr_Animoji_Mouth_Pucker = 19,
    HwAr_Animoji_Mouth_Left = 20,
    HwAr_Animoji_Mouth_Right = 21,
    HwAr_Animoji_Mouth_Smile_Left = 22,
    HwAr_Animoji_Mouth_Smile_Right = 23,
    HwAr_Animoji_Mouth_Frown_Left = 24,
    HwAr_Animoji_Mouth_Frown_Right = 25,
    HwAr_Animoji_Mouth_Dimple_Left = 26,
    HwAr_Animoji_Mouth_Dimple_Right = 27,
    HwAr_Animoji_Mouth_Stretch_Left = 28,
    HwAr_Animoji_Mouth_Stretch_Right = 29,
    HwAr_Animoji_Mouth_Roll_Lower = 30,
    HwAr_Animoji_Mouth_Roll_Upper = 31,
    HwAr_Animoji_Mouth_Shrug_Lower = 32,
    HwAr_Animoji_Mouth_Shrug_Upper = 33,
    HwAr_Animoji_Mouth_Upper_Up = 34,
    HwAr_Animoji_Mouth_Lower_Down = 35,
    HwAr_Animoji_Mouth_Lower_Out = 36,
    HwAr_Animoji_Brow_Down_Left = 37,
    HwAr_Animoji_Brow_Down_Right = 38,
    HwAr_Animoji_Brow_Inner_Up = 39,
    HwAr_Animoji_Brow_Outer_Up_Left = 40,
    HwAr_Animoji_Brow_Outer_Up_Right = 41,
    HwAr_Animoji_Cheek_Puff = 42,
    HwAr_Animoji_Cheek_Squint_Left = 43,
    HwAr_Animoji_Cheek_Squint_Right = 44,
    HwAr_Animoji_Frown_Nose_Mouth_Up = 45,
    HwAr_Animoji_Tongue_In = 46,
    HwAr_Animoji_Tongue_Out_Slight = 47,
    HwAr_Animoji_Tongue_Left = 48,
    HwAr_Animoji_Tongue_Right = 49,
    HwAr_Animoji_Tongue_Up = 50,
    HwAr_Animoji_Tongue_Down = 51,
    HwAr_Animoji_Tongue_Left_Up = 52,
    HwAr_Animoji_Tongue_Left_Down = 53,
    HwAr_Animoji_Tongue_Right_Up = 54,
    HwAr_Animoji_Tongue_Right_Down = 55,
    HwAr_Animoji_Left_Eyeball_Left = 56,
    HwAr_Animoji_Left_Eyeball_Right = 57,
    HwAr_Animoji_Left_Eyeball_Up = 58,
    HwAr_Animoji_Left_Eyeball_Down = 59,
    HwAr_Animoji_Right_Eyeball_Left = 60,
    HwAr_Animoji_Right_Eyeball_Right = 61,
    HwAr_Animoji_Right_Eyeball_Up = 62,
    HwAr_Animoji_Right_Eyeball_Down = 63,
    HwAr_ANIMOJI_BLENDSHAPE_LENGTH = 64
};

HWAR_DEFINE_ENUM(HwArAnimojiTriangleLabel) {
    // label: -1=non_face, 0=face_other, 1=lower_lip, 2=upper_lip, 3=left_eye, 4=right_eye,
    // 5=left_brow, 6=right_brow,7=brow_center, 8=nose
    HwAr_Animoji_Label_non_face = -1,
    HwAr_Animoji_Label_face_other = 0,
    HwAr_Animoji_Label_lower_lip = 1,
    HwAr_Animoji_Label_upper_lip = 2,
    HwAr_Animoji_Label_left_eye = 3,
    HwAr_Animoji_Label_right_eye = 4,
    HwAr_Animoji_Label_left_brow = 5,
    HwAr_Animoji_Label_right_brow = 6,
    HwAr_Animoji_Label_brow_center = 7,
    HwAr_Animoji_Label_nose = 8,
    HwAr_ANIMOJI_TRIANGLE_LABELS_LENGTH
};

HWAR_DEFINE_ENUM(HwArCoordinateSystemType) {
    HwAr_Coordinate_System_Type_Unknown = -1,
    HwAr_Coordinate_System_Type_3D_World,        // world coordinate system
    HwAr_Coordinate_System_Type_3D_Body,         // 3d image coordinate system for bodypose
    HwAr_Coordinate_System_Type_2D_Image,         // 2D image coordinate system for gesture (openGL)
    HwAr_Coordinate_System_Type_3D_Camera
};
HWAR_DEFINE_ENUM(HwArBodySkeletonType) {
    HwAr_BodySkeleton_Head = 0,
    HwAr_BodySkeleton_Neck = 1,
    HwAr_BodySkeleton_r_Sho = 2,
    HwAr_BodySkeleton_r_Elbow = 3,
    HwAr_BodySkeleton_r_Wrist = 4,
    HwAr_BodySkeleton_l_Sho = 5,
    HwAr_BodySkeleton_l_Elbow = 6,
    HwAr_BodySkeleton_l_Wrist = 7,
    HwAr_BodySkeleton_r_Hip = 8,
    HwAr_BodySkeleton_r_Knee = 9,
    HwAr_BodySkeleton_r_Ankle = 10,
    HwAr_BodySkeleton_l_Hip = 11,
    HwAr_BodySkeleton_l_Knee = 12,
    HwAr_BodySkeleton_l_Ankle = 13,
    HwAr_BodySkeleton_Hip_mid = 14,
    HwAr_BodySkeleton_Length
};
HWAR_DEFINE_ENUM(HwArBodyAction) {
    HwAr_Body_Action_None = 0,
    HwAr_Body_Action_1,
    HwAr_Body_Action_2,
    HwAr_Body_Action_3,
    HwAr_Body_Action_4,
    HwAr_Body_Action_5,
    HwAr_Body_Action_6
};

HWAR_DEFINE_ENUM(HwArHandType) {
    HwAr_Hand_Unknown = -1,
    HwAr_Hand_Right,
    HwAr_Hand_Left
};
HWAR_DEFINE_ENUM(HwArHandGesutreType) {
    HwAr_GESTURE_HAND_UNKNOWN = -1,
    HwAr_GESTURE_HAND_0 = 0, //in use
    HwAr_GESTURE_HAND_1, //in use
    HwAr_GESTURE_HAND_2,
    HwAr_GESTURE_HAND_3,
    HwAr_GESTURE_HAND_4,
    HwAr_GESTURE_HAND_5, //in use
    HwAr_GESTURE_HAND_6, //in use
    HwAr_GESTURE_HAND_7, //in use
    HwAr_GESTURE_HAND_8,
    HwAr_GESTURE_HAND_9,
    HwAr_GESTURE_HAND_10,// in use
    HwAr_GESTURE_HAND_11,
    HwAr_GESTURE_HAND_Length = 13
};

HWAR_DEFINE_ENUM(HwArHandSkeletonType) {
    HwAr_HandSkeleton_Root = 0,
    HwAr_HandSkeleton_Pinky_1,
    HwAr_HandSkeleton_Pinky_2,
    HwAr_HandSkeleton_Pinky_3,
    HwAr_HandSkeleton_Pinky_4,
    HwAr_HandSkeleton_Ring_1,
    HwAr_HandSkeleton_Ring_2,
    HwAr_HandSkeleton_Ring_3,
    HwAr_HandSkeleton_Ring_4,
    HwAr_HandSkeleton_Middle_1,
    HwAr_HandSkeleton_Middle_2,
    HwAr_HandSkeleton_Middle_3,
    HwAr_HandSkeleton_Middle_4,
    HwAr_HandSkeleton_Index_1,
    HwAr_HandSkeleton_Index_2,
    HwAr_HandSkeleton_Index_3,
    HwAr_HandSkeleton_Index_4,
    HwAr_HandSkeleton_Thumb_1,
    HwAr_HandSkeleton_Thumb_2,
    HwAr_HandSkeleton_Thumb_3,
    HwAr_HandSkeleton_Thumb_4,
    HwAr_HandSkeleton_Length = 21
};

#undef HWAR_DEFINE_ENUM

#ifndef MAX_WINDOWS_COUNT
#define MAX_WINDOWS_COUNT 64
#endif


#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------------------
 detailed functions added for AR Engine
 ----------------------------------------------------------------------------------------*/
HwArEnginesAvaliblity
HwArEnginesSelector_checkAllAvailableEngines(void *env, void *application_context);
HwArEnginesType HwArEnginesSelector_setAREngine(HwArEnginesType ar_options);

HwArEnginesType HwArEnginesSelector_getCreatedEngine();

void HwArEnginesApk_checkAvailability(void *env,
                                      void *application_context,
                                      HwArAvailability *out_availability);

HwArStatus HwArEnginesApk_requestInstall(void *env,
                                         void *application_activity,
                                         bool user_requested_install,
                                         HwArInstallStatus *out_install_status);

void HwArConfig_getArType(const HwArSession *session,
                          const HwArConfig *config,
                          HwArType *type);
void HwArConfig_setArType(const HwArSession *session,
                          HwArConfig *config,
                          HwArType type);
void HwArConfig_getCameraLensFacing(const HwArSession *session,
                                    const HwArConfig *config,
                                    HwArCameraLensFacing *facing);
void HwArConfig_setCameraLensFacing(const HwArSession *session,
                                    HwArConfig *config,
                                    HwArCameraLensFacing facing);

void HwArSession_stop(HwArSession *session);
HwArStatus HwArSession_save(HwArSession *session,
                      char *buffer, int64_t buf_len, int64_t *const ret);
HwArStatus HwArSession_load(HwArSession *session,
                      char *buffer, int64_t buf_len);
HwArStatus HwArSession_getSaveLimit(HwArSession* session, int64_t* const out_size);

HwArStatus HwArSession_serializeAnchors(HwArSession *session,HwArAnchorList* anchor_list, bool is_need_align,
                                        char *buffer, int64_t buf_len, int64_t* out_size);
HwArStatus HwArSession_deserializeAnchors(HwArSession *session, char* buffer, int64_t buf_len,
                                          HwArAnchorList* out_anchor_list);
HwArStatus HwArSession_getSerializeAnchorsLimit(HwArSession *session, int64_t* const out_size);

///*
// AugmentedImage config----------------------------------------------------------------
void HwArConfig_setAugmentedImageDatabase(const HwArSession *session,
                                          HwArConfig *config,
                                          const HwArAugmentedImageDatabase *augmented_image_database);
void HwArConfig_getAugmentedImageDatabase(const HwArSession *session,
                                          const HwArConfig *config,
                                          HwArAugmentedImageDatabase *out_augmented_image_database);

//HwArAugmentedImage--------------------------------------------------------------------
void HwArAugmentedImage_getCenterPose(const HwArSession *session,
                                      const HwArAugmentedImage *augmented_image,
                                      HwArPose *out_pose);

void HwArAugmentedImage_getExtentX(const HwArSession *session,
                                   const HwArAugmentedImage *augmented_image,
                                   float *out_extent_x);

void HwArAugmentedImage_getExtentZ(const HwArSession *session,
                                   const HwArAugmentedImage *augmented_image,
                                   float *out_extent_z);

void HwArAugmentedImage_getIndex(const HwArSession *session,
                                 const HwArAugmentedImage *augmented_image,
                                 int32_t *out_index);

void HwArAugmentedImage_acquireName(const HwArSession *session,
                                    const HwArAugmentedImage *augmented_image,
                                    char **out_augmented_image_name);

//HwArAugmentedImageDatabase--------------------------------------------------------------------
void HwArAugmentedImageDatabase_create(const HwArSession *session,
                                        HwArAugmentedImageDatabase **out_augmented_image_database);

HwArStatus HwArAugmentedImageDatabase_deserialize(const HwArSession *session,
                                                  const uint8_t *database_raw_bytes,
                                                  int64_t database_raw_bytes_size,
                                                  HwArAugmentedImageDatabase **out_augmented_image_database);

void HwArAugmentedImageDatabase_serialize(const HwArSession *session,
                                          const HwArAugmentedImageDatabase *augmented_image_database,
                                          uint8_t **out_image_database_raw_bytes,
                                          int64_t *out_image_database_raw_bytes_size);

HwArStatus HwArAugmentedImageDatabase_addImage(const HwArSession *session,
                                               HwArAugmentedImageDatabase *augmented_image_database,
                                               const char *image_name,
                                               const uint8_t *image_grayscale_pixels,
                                               int32_t image_width_in_pixels,
                                               int32_t image_height_in_pixels,
                                               int32_t image_stride_in_pixels,
                                               int32_t *out_index);

HwArStatus HwArAugmentedImageDatabase_addImageWithPhysicalSize(const HwArSession *session,
                                                               HwArAugmentedImageDatabase *augmented_image_database,
                                                               const char *image_name,
                                                               const uint8_t *image_grayscale_pixels,
                                                               int32_t image_width_in_pixels,
                                                               int32_t image_height_in_pixels,
                                                               int32_t image_stride_in_pixels,
                                                               float image_width_in_meters,
                                                               int32_t *out_index);

void HwArAugmentedImageDatabase_getNumImages(const HwArSession *session,
                                             const HwArAugmentedImageDatabase *augmented_image_database,
                                             int32_t *out_num_images);
void HwArAugmentedImageDatabase_destroy(HwArAugmentedImageDatabase *augmented_image_database);
//*/

// HwArHand --------------------------------------------------------------------
void HwArHand_getGestureCoordinateSystem(const HwArSession *session,
                                         const HwArHand *hand,
                                         HwArCoordinateSystemType *out_gestureCoordinateSyste);
void HwArHand_getHandId(const HwArSession *session,
                        const HwArHand *hand, int32_t *out_handId);
void HwArHand_getGestureType(const HwArSession *session,
                             const HwArHand *hand, HwArHandGesutreType *out_gestureType);
void HwArHand_getHandType(const HwArSession *session,
                          const HwArHand *hand, HwArHandType *out_handType);
void HwArHand_getGestureHandBox(const HwArSession *session,
                                const HwArHand *hand, const float **out_handBox);
void HwArHand_getGestureCenter(const HwArSession *session,
                               const HwArHand *hand, const float **out_center);
void HwArHand_getGestureActionSize(const HwArSession *session,
                                   const HwArHand *hand, int32_t *out_count);
void HwArHand_getGestureAction(const HwArSession *session,
                               const HwArHand *hand, const int32_t **out_action);
void HwArHand_getGestureOrientation(const HwArSession *session,
                                    const HwArHand *hand, const float **out_orientation);

// Hand Skeleton--------------------------------------------------------
void HwArHand_getSkeletonCoordinateSystem(const HwArSession *session,
                                          const HwArHand *hand,
                                          HwArCoordinateSystemType *out_skeletonCoordinateSystem);
void HwArHand_getHandSkeletonType(const HwArSession *session,
                                  const HwArHand *hand,
                                  const HwArHandSkeletonType **out_handSkeletonType);
void HwArHand_getHandSkeletonCount(const HwArSession *session,
                                   const HwArHand *hand, int32_t *out_skeletonCount);
void HwArHand_getHandSkeletonArray(const HwArSession *session,
                                   const HwArHand *hand, const float **out_skeletonArray);
void HwArHand_getHandSkeletonConnectionSize(const HwArSession *session,
                                             const HwArHand *hand, int32_t *out_connectionSize);
void HwArHand_getHandSkeletonConnection(const HwArSession *session,
                                        const HwArHand *hand, const int32_t **out_connection);

// HwArBody --------------------------------------------------------------------
void HwArBody_getCoordinateSystemType(const HwArSession *session,
                                      const HwArBody *body,
                                      HwArCoordinateSystemType *out_coordinateSystemType);
void HwArBody_getBodyId(const HwArSession *session,
                        const HwArBody *body, int32_t *out_personId);
void HwArBody_getSkeletonPointCount(const HwArSession *session,
                                    const HwArBody *body, int32_t *out_pointCount);
void HwArBody_getSkeletonTypes(const HwArSession *session,
                               const HwArBody *body,
                               const HwArBodySkeletonType **out_skeleton_types);
void HwArBody_getSkeletonPointIsExist2D(const HwArSession *session,
                                        const HwArBody *body,
                                        const int32_t **out_skeletonPintIsExist_2D);
void HwArBody_getSkeletonPointIsExist3D(const HwArSession *session,
                                        const HwArBody *body,
                                        const int32_t **out_skeletonPintIsExist_3D);
void HwArBody_getSkeletonPoint2D(const HwArSession *session,
                                 const HwArBody *body, const float **out_point2D);
void HwArBody_getSkeletonPoint3D(const HwArSession *session,
                                 const HwArBody *body, const float **out_point3D);
void HwArBody_getSkeletonConfidence(const HwArSession *session,
                                        const HwArBody *body, const float **out_confidence);
void HwArBody_getSkeletonConnectionSize(const HwArSession *session,
                                         const HwArBody *body, int32_t *out_connetionCountSize);
void HwArBody_getSkeletonConnection(const HwArSession *session,
                                    const HwArBody *body, const int32_t **out_skeletonConnection);
void HwArBody_getBodyAction(const HwArSession *session,
                            const HwArBody *body, HwArBodyAction *out_bodyAction);


// HwArFace --------------------------------------------------------------------
void HwArFace_getPose(const HwArSession *session,
                      const HwArFace *face, HwArPose *pose);
void HwArFace_acquireGeometry(const HwArSession *session,
                              const HwArFace *face, HwArFaceGeometry **geometry);
void HwArFace_acquireBlendShapes(const HwArSession *session,
                                 const HwArFace *face, HwArFaceBlendShapes **blendshapes);

// HwArFaceGeometry ---------------------------------------------------------------------------
void HwArFaceGeometry_release(HwArFaceGeometry *geometry);

void HwArFaceGeometry_getTriangleCount(const HwArSession *session,
                                       const HwArFaceGeometry *geometry, int32_t *count);
void HwArFaceGeometry_getVerticesSize(const HwArSession *session,
                                      const HwArFaceGeometry *geometry, int32_t *count);
void HwArFaceGeometry_acquireVertices(const HwArSession *session,
                                      const HwArFaceGeometry *geometry, const float **data);
void HwArFaceGeometry_getTexCoordSize(const HwArSession *session,
                                      const HwArFaceGeometry *geometry, int32_t *count);
void HwArFaceGeometry_acquireTexCoord(const HwArSession *session,
                                      const HwArFaceGeometry *geometry, const float **data);
void HwArFaceGeometry_getTriangleIndicesSize(const HwArSession *session,
                                             const HwArFaceGeometry *geometry, int32_t *count);
void HwArFaceGeometry_acquireTriangleIndices(const HwArSession *session,
                                             const HwArFaceGeometry *geometry,
                                             const int32_t **data);
void HwArFaceGeometry_getTriangleLabelsSize(const HwArSession *session,
                                            const HwArFaceGeometry *geometry, int32_t *count);
void HwArFaceGeometry_acquireTriangleLabels(const HwArSession *session,
                                            const HwArFaceGeometry *geometry,
                                            const HwArAnimojiTriangleLabel **data);

// HwArFaceBlendShapes ---------------------------------------------------------------------------
void HwArFaceBlendShapes_release(HwArFaceBlendShapes *blendshapes);
void HwArFaceBlendShapes_acquireData(const HwArSession *session,
                                     const HwArFaceBlendShapes *blendshapes, const float **data);
void HwArFaceBlendShapes_getCount(const HwArSession *session,
                                  const HwArFaceBlendShapes *blendshapes, int32_t *count);
void HwArFaceBlendShapes_acquireTypes(const HwArSession *session,
                                      const HwArFaceBlendShapes *blendshapes,
                                      const HwArAnimojiBlendShape **types);

/*------------------------------------------------------------------------------
 detailed functions consistent with ARCore
 ------------------------------------------------------------------------------*/

void HwArApk_checkAvailability(void *env,
                               void *application_context,
                               HwArAvailability *out_availability);

HwArStatus HwArApk_requestInstall(void *env,
                                  void *application_activity,
                                  bool user_requested_install,
                                  HwArInstallStatus *out_install_status);

HwArStatus HwArApk_requestInstallCustom(void *env,
                                        void *application_activity,
                                        int32_t user_requested_install,
                                        HwArInstallBehavior install_behavior,
                                        HwArInstallUserMessageType message_type,
                                        HwArInstallStatus *out_install_status);

HwArStatus HwArSession_create(void *env,
                              void *application_context,
                              HwArSession **out_session_pointer);

void HwArConfig_create(const HwArSession *session, HwArConfig **out_config);

void HwArConfig_destroy(HwArConfig *config);
void HwArConfig_getLightEstimationMode(const HwArSession *session,
                                       const HwArConfig *config,
                                       HwArLightEstimationMode *light_estimation_mode);
void HwArConfig_setLightEstimationMode(const HwArSession *session,
                                       HwArConfig *config,
                                       HwArLightEstimationMode light_estimation_mode);
void HwArConfig_getPlaneFindingMode(const HwArSession *session,
                                    const HwArConfig *config,
                                    HwArPlaneFindingMode *plane_finding_mode);
void HwArConfig_setPlaneFindingMode(const HwArSession *session,
                                    HwArConfig *config,
                                    HwArPlaneFindingMode plane_finding_mode);
void HwArConfig_getUpdateMode(const HwArSession *session,
                              const HwArConfig *config,
                              HwArUpdateMode *update_mode);
void HwArConfig_setUpdateMode(const HwArSession *session,
                              HwArConfig *config,
                              HwArUpdateMode update_mode);
void HwArConfig_getPowerMode(const HwArSession *session,
                              const HwArConfig *config,
                              HwArPowerMode *power_mode);
void HwArConfig_setPowerMode(const HwArSession *session,
                              HwArConfig *config,
                              HwArPowerMode power_mode);
void HwArConfig_getEnableItem(const HwArSession* session,
                               const HwArConfig* config,
                               uint64_t * item);
void HwArConfig_setEnableItem(const HwArSession* session,
                                HwArConfig* config,
                                uint64_t item);
void HwArConfig_getImageInputMode(const HwArSession *session,
                                  const HwArConfig *config,
                                  HwArImageInputMode *mode);
void HwArConfig_setImageInputMode(const HwArSession *session,
                                  HwArConfig *config,
                                  HwArImageInputMode mode);
int32_t HwArConfig_getInputNativeWindows(const HwArSession *session,
                                         const HwArConfig *config,
                                         int32_t count,
                                         int64_t **windows);
int32_t HwArConfig_getInputNativeWindowTypes(const HwArSession *session,
                                             const HwArConfig *config,
                                             int32_t count,
                                             HwArNativeWindowType **types);
void HwArConfig_getHandFindingMode(const HwArSession *session,
                                   HwArConfig *config,
                                   HwArHandFindingMode *mode);
void HwArConfig_setHandFindingMode(const HwArSession *session,
                                   HwArConfig *config,
                                   HwArHandFindingMode mode);
void HwArSession_destroy(HwArSession *session);
HwArStatus HwArSession_checkSupported(const HwArSession *session,
                                      const HwArConfig *config);
HwArStatus HwArSession_configure(HwArSession *session, const HwArConfig *config);
HwArStatus HwArSession_resume(HwArSession *session);
HwArStatus HwArSession_pause(HwArSession *session);
void HwArSession_setCameraTextureName(HwArSession *session, uint32_t texture_id);
void HwArSession_setDisplayGeometry(HwArSession *session,
                                    int32_t rotation,
                                    int32_t width,
                                    int32_t height);
HwArStatus HwArSession_update(HwArSession *session, HwArFrame *out_frame);
HwArStatus HwArSession_acquireNewAnchor(HwArSession *session,
                                        const HwArPose *pose,
                                        HwArAnchor **out_anchor);
void HwArSession_getAllAnchors(const HwArSession *session,
                               HwArAnchorList *out_anchor_list);
void HwArSession_getAllTrackables(const HwArSession *session,
                                  HwArTrackableType filter_type,
                                  HwArTrackableList *out_trackable_list);
void HwArPose_create(const HwArSession *session,
                     const float *pose_raw,
                     HwArPose **out_pose);
void HwArPose_destroy(HwArPose *pose);
void HwArPose_getPoseRaw(const HwArSession *session,
                         const HwArPose *pose,
                         float *out_pose_raw);
void HwArPose_getMatrix(const HwArSession *session,
                        const HwArPose *pose,
                        float *out_matrix_col_major_4x4);
void HwArCamera_getPose(const HwArSession *session,
                        const HwArCamera *camera,
                        HwArPose *out_pose);
void HwArCamera_getDisplayOrientedPose(const HwArSession *session,
                                       const HwArCamera *camera,
                                       HwArPose *out_pose);
void HwArCamera_getViewMatrix(const HwArSession *session,
                              const HwArCamera *camera,
                              float *out_col_major_4x4);
void HwArCamera_getTrackingState(const HwArSession *session,
                                 const HwArCamera *camera,
                                 HwArTrackingState *out_tracking_state);
void HwArCamera_getProjectionMatrix(const HwArSession *session,
                                    const HwArCamera *camera,
                                    float near,
                                    float far,
                                    float *dest_col_major_4x4);
void HwArCamera_release(HwArCamera *camera);
void HwArFrame_create(const HwArSession *session, HwArFrame **out_frame);
void HwArFrame_destroy(HwArFrame *frame);
void HwArFrame_getDisplayGeometryChanged(const HwArSession *session,
                                         const HwArFrame *frame,
                                         int32_t *out_geometry_changed);
void HwArFrame_getTimestamp(const HwArSession *session,
                            const HwArFrame *frame,
                            int64_t *out_timestamp_ns);
void HwArFrame_getMappingState(const HwArSession *session,
                               const HwArFrame *frame,
                               HwArWorldMappingState *out_mapping_state);
void HwArFrame_getAlignState(
        const HwArSession *session,
        const HwArFrame *frame,
        HwArAlignState *out_align_state);
void HwArFrame_transformDisplayUvCoords(const HwArSession *session,
                                        const HwArFrame *frame,
                                        int32_t num_elements,
                                        const float *uvs_in,
                                        float *uvs_out);
void HwArFrame_hitTest(const HwArSession *session,
                       const HwArFrame *frame,
                       float pixel_x,
                       float pixel_y,
                       HwArHitResultList *hit_result_list);
void HwArFrame_getLightEstimate(const HwArSession *session,
                                const HwArFrame *frame,
                                HwArLightEstimate *out_light_estimate);
HwArStatus HwArFrame_acquirePointCloud(const HwArSession *session,
                                       const HwArFrame *frame,
                                       HwArPointCloud **out_point_cloud);
void HwArFrame_acquireCamera(const HwArSession *session,
                             const HwArFrame *frame,
                             HwArCamera **out_camera);
HwArStatus HwArFrame_acquireImageMetadata(const HwArSession *session,
                                          const HwArFrame *frame,
                                          HwArImageMetadata **out_metadata);
void HwArFrame_getUpdatedAnchors(const HwArSession *session,
                                 const HwArFrame *frame,
                                 HwArAnchorList *out_anchor_list);
void HwArFrame_getUpdatedTrackables(const HwArSession *session,
                                    const HwArFrame *frame,
                                    HwArTrackableType filter_type,
                                    HwArTrackableList *out_trackable_list);
void HwArPointCloud_getNumberOfPoints(const HwArSession *session,
                                      const HwArPointCloud *point_cloud,
                                      int32_t *out_number_of_points);
void HwArPointCloud_getData(const HwArSession *session,
                            const HwArPointCloud *point_cloud,
                            const float **out_point_cloud_data);
void HwArPointCloud_getTimestamp(const HwArSession *session,
                                 const HwArPointCloud *point_cloud,
                                 int64_t *out_timestamp_ns);
void HwArPointCloud_release(HwArPointCloud *point_cloud);
void HwArImageMetadata_getNdkCameraMetadata(
        const HwArSession *session,
        const HwArImageMetadata *image_metadata,
        const ACameraMetadata **out_ndk_metadata);
void HwArImageMetadata_release(HwArImageMetadata *metadata);
void HwArLightEstimate_create(const HwArSession *session,
                              HwArLightEstimate **out_light_estimate);
void HwArLightEstimate_destroy(HwArLightEstimate *light_estimate);
void HwArLightEstimate_getState(const HwArSession *session,
                                const HwArLightEstimate *light_estimate,
                                HwArLightEstimateState *out_light_estimate_state);
void HwArLightEstimate_getPixelIntensity(const HwArSession *session,
                                         const HwArLightEstimate *light_estimate,
                                         float *out_pixel_intensity);
void HwArAnchorList_create(const HwArSession *session,
                           HwArAnchorList **out_anchor_list);
void HwArAnchorList_destroy(HwArAnchorList *anchor_list);
void HwArAnchorList_getSize(const HwArSession *session,
                            const HwArAnchorList *anchor_list,
                            int32_t *out_size);
void HwArAnchorList_acquireItem(const HwArSession *session,
                                const HwArAnchorList *anchor_list,
                                int32_t index,
                                HwArAnchor **out_anchor);
void HwArAnchorList_addItem(const HwArSession *session,
                            HwArAnchorList *anchor_list,
                            HwArAnchor *anchor);
void HwArAnchor_getPose(const HwArSession *session,
                        const HwArAnchor *anchor,
                        HwArPose *out_pose);
void HwArAnchor_getTrackingState(const HwArSession *session,
                                 const HwArAnchor *anchor,
                                 HwArTrackingState *out_tracking_state);
void HwArAnchor_detach(HwArSession *session, HwArAnchor *anchor);
void HwArAnchor_release(HwArAnchor *anchor);
void HwArTrackableList_create(const HwArSession *session,
                              HwArTrackableList **out_trackable_list);
void HwArTrackableList_destroy(HwArTrackableList *trackable_list);
void HwArTrackableList_getSize(const HwArSession *session,
                               const HwArTrackableList *trackable_list,
                               int32_t *out_size);
void HwArTrackableList_acquireItem(const HwArSession *session,
                                   const HwArTrackableList *trackable_list,
                                   int32_t index,
                                   HwArTrackable **out_trackable);
void HwArTrackable_release(HwArTrackable *trackable);
void HwArTrackable_getType(const HwArSession *session,
                           const HwArTrackable *trackable,
                           HwArTrackableType *out_trackable_type);
void HwArTrackable_getTrackingState(const HwArSession *session,
                                    const HwArTrackable *trackable,
                                    HwArTrackingState *out_tracking_state);
HwArStatus HwArTrackable_acquireNewAnchor(HwArSession *session,
                                          HwArTrackable *trackable,
                                          HwArPose *pose,
                                          HwArAnchor **out_anchor);
void HwArTrackable_getAnchors(const HwArSession *session,
                              const HwArTrackable *trackable,
                              HwArAnchorList *out_anchor_list);
void HwArPlane_acquireSubsumedBy(const HwArSession *session,
                                 const HwArPlane *plane,
                                 HwArPlane **out_subsumed_by);
void HwArPlane_getType(const HwArSession *session,
                       const HwArPlane *plane,
                       HwArPlaneType *out_plane_type);
void HwArPlane_getCenterPose(const HwArSession *session,
                             const HwArPlane *plane,
                             HwArPose *out_pose);
void HwArPlane_getExtentX(const HwArSession *session,
                          const HwArPlane *plane,
                          float *out_extent_x);
void HwArPlane_getExtentZ(const HwArSession *session,
                          const HwArPlane *plane,
                          float *out_extent_z);
void HwArPlane_getPolygonSize(const HwArSession *session,
                              const HwArPlane *plane,
                              int32_t *out_polygon_size);
void HwArPlane_getPolygon(const HwArSession *session,
                          const HwArPlane *plane,
                          float *out_polygon_xz);
void HwArPlane_isPoseInExtents(const HwArSession *session,
                               const HwArPlane *plane,
                               const HwArPose *pose,
                               int32_t *out_pose_in_extents);
void HwArPlane_isPoseInPolygon(const HwArSession *session,
                               const HwArPlane *plane,
                               const HwArPose *pose,
                               int32_t *out_pose_in_polygon);
void HwArPoint_getPose(const HwArSession *session,
                       const HwArPoint *point,
                       HwArPose *out_pose);
void HwArPoint_getOrientationMode(const HwArSession *session,
                                  const HwArPoint *point,
                                  HwArPointOrientationMode *out_orientation_mode);
void HwArHitResultList_create(const HwArSession *session,
                              HwArHitResultList **out_hit_result_list);
void HwArHitResultList_destroy(HwArHitResultList *hit_result_list);
void HwArHitResultList_getSize(const HwArSession *session,
                               const HwArHitResultList *hit_result_list,
                               int32_t *out_size);
void HwArHitResultList_getItem(const HwArSession *session,
                               const HwArHitResultList *hit_result_list,
                               int32_t index,
                               HwArHitResult *out_hit_result);
void HwArHitResult_create(const HwArSession *session, HwArHitResult **out_hit_result);
void HwArHitResult_destroy(HwArHitResult *hit_result);
void HwArHitResult_getDistance(const HwArSession *session,
                               const HwArHitResult *hit_result,
                               float *out_distance);
void HwArHitResult_getHitPose(const HwArSession *session,
                              const HwArHitResult *hit_result,
                              HwArPose *out_pose);
void HwArHitResult_acquireTrackable(const HwArSession *session,
                                    const HwArHitResult *hit_result,
                                    HwArTrackable **out_trackable);
HwArStatus HwArHitResult_acquireNewAnchor(HwArSession *session,
                                          HwArHitResult *hit_result,
                                          HwArAnchor **out_anchor);


#ifdef __cplusplus
}
#endif
#endif //ARNDK_HWAR_INTERFACE_H
