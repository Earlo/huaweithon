#include "surfacetest.h"

#include <unistd.h>
#include <sstream>
#include <string>

extern "C" {

#if __ANDROID_API__ >= 26

jobject SurfaceTest_createPreviewSurface(JNIEnv *env, jlong val) {
    LOGI("SurfaceTest_createPreviewSurface enter.");

    AImageReader *pImageReader = nullptr;
    ssize_t status = AImageReader_new(
            1920,
            1080,
            AIMAGE_FORMAT_YUV_420_888,
            8,
            &pImageReader
    );

    if ((status != AMEDIA_OK) || (pImageReader == nullptr)) {
        LOGE("AImageReader_new fail.");
        return nullptr;
    }

    ANativeWindow *pWindow = nullptr;
    status = AImageReader_getWindow(pImageReader, &pWindow);
    if ((status != AMEDIA_OK) || (pWindow == nullptr)) {
        LOGE("AImageReader_getWindow fail.");
        return nullptr;
    }

    LOGI("SurfaceTest_createPreviewSurface exit.");
    return ANativeWindow_toSurface(env, pWindow); // API level > 26
}

jobject SurfaceTest_createPreviewSurfaces(JNIEnv *env, jlong val) {
    LOGI("SurfaceTest_createPreviewSurfacess enter.");

    jsize n = 2;
    jclass clazz = env->FindClass("android/view/Surface");
    jobjectArray surfaces = env->NewObjectArray(n, clazz, nullptr);

    for (jsize i = 0; i < n; i++) {
        jobject surf = SurfaceTest_createPreviewSurface(env, val);
        env->SetObjectArrayElement(surfaces, i, surf);
    }
    LOGI("SurfaceTest_createPreviewSurfacess exit.");
    return surfaces;
}

#endif

}