#ifndef C_AREngine_HELLOE_AR_SURFACE_TEST_H_
#define C_AREngine_HELLOE_AR_SURFACE_TEST_H_

#include <assert.h>
#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

#include <android/hardware_buffer.h>
#include <android/native_activity.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/rect.h>
#include <android/window.h>

#include <media/NdkImage.h>
#include <media/NdkImageReader.h>
#include <media/NdkMediaCodec.h>
#include <media/NdkMediaCrypto.h>
#include <media/NdkMediaDrm.h>
#include <media/NdkMediaError.h>
#include <media/NdkMediaExtractor.h>
#include <media/NdkMediaFormat.h>
#include <media/NdkMediaMuxer.h>

#include "util.h"

extern "C" {

#if __ANDROID_API__ >= 26

jobject SurfaceTest_createPreviewSurface(JNIEnv *env, jlong val);
jobject SurfaceTest_createPreviewSurfaces(JNIEnv *env, jlong val);
#endif

}
#endif  // C_AREngine_HELLOE_AR_SURFACE_TEST_H_
