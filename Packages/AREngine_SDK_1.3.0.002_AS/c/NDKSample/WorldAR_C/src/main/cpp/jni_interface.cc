//
// Created by j00428315 on 2018/4/01.
//

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <jni.h>

#include "hello_ar_application.h"
#include "surfacetest.h"

#define JNI_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_com_huawei_arengine_examples_c_helloar_JniInterface_##method_name

#define SURFACE_METHOD(return_type, method_name) \
  JNIEXPORT return_type JNICALL              \
      Java_com_huawei_arengine_examples_c_helloar_SurfaceTest_##method_name

extern "C" {

namespace {
    //maintain a reference to the JVM so we can use it later.
    static JavaVM *g_vm = nullptr;

    inline jlong jptr(hello_ar::HelloArApplication *native_hello_ar_application) {
        return reinterpret_cast<intptr_t>(native_hello_ar_application);
    }

    inline hello_ar::HelloArApplication *native(jlong ptr) {
        return reinterpret_cast<hello_ar::HelloArApplication *>(ptr);
    }

}  // namespace

jint JNI_OnLoad(JavaVM *vm, void *) {
    g_vm = vm;
    return JNI_VERSION_1_6;
}

///////////////////////////////////////////////

SURFACE_METHOD(jlong, getSurface)
(JNIEnv *env, jlong) {
    return 11;
}

#if __ANDROID_API__ >= 26

SURFACE_METHOD(jobject, createPreviewSurface)
(JNIEnv *env, jlong val) {
    return SurfaceTest_createPreviewSurface(env, val);
}

SURFACE_METHOD(jobject, createPreviewSurfaces)
(JNIEnv *env, jlong val) {
    return SurfaceTest_createPreviewSurfaces(env, val);
}

#endif

//////////////////////////////////////////////

JNI_METHOD(jlong, createNativeApplication)
(JNIEnv *env, jclass, jobject j_asset_manager) {
    AAssetManager *asset_manager = AAssetManager_fromJava(env, j_asset_manager);
    return jptr(new hello_ar::HelloArApplication(asset_manager));
}

JNI_METHOD(void, destroyNativeApplication)
(JNIEnv *, jclass, jlong native_application) {
    delete native(native_application);
}

JNI_METHOD(void, onPause)
(JNIEnv *, jclass, jlong native_application) {
    native(native_application)->OnPause();
}

JNI_METHOD(void, onResume)
(JNIEnv *env, jclass, jlong native_application, jobject context,
 jobject activity) {
    native(native_application)->OnResume(env, context, activity);
}

JNI_METHOD(void, onGlSurfaceCreated)
(JNIEnv *, jclass, jlong native_application) {
    native(native_application)->OnSurfaceCreated();
}

JNI_METHOD(void, onDisplayGeometryChanged)
(JNIEnv *, jobject, jlong native_application, int display_rotation, int width,
 int height) {
    native(native_application)->OnDisplayGeometryChanged(display_rotation, width, height);
}

JNI_METHOD(void, onGlSurfaceDrawFrame)
(JNIEnv *, jclass, jlong native_application) {
    native(native_application)->OnDrawFrame();
}

JNI_METHOD(void, onTouched)
(JNIEnv *, jclass, jlong native_application, jfloat x, jfloat y) {
    native(native_application)->OnTouched(x, y);
}

JNI_METHOD(jboolean, hasDetectedPlanes)
(JNIEnv *, jclass, jlong native_application) {
    return static_cast<jboolean>(native(native_application)->HasDetectedPlanes() ? JNI_TRUE : JNI_FALSE);
}

JNIEnv *GetJniEnv() {
    JNIEnv *env;
    jint result = g_vm->AttachCurrentThread(&env, nullptr);
    return result == JNI_OK ? env : nullptr;
}

jclass FindClass(const char *classname) {
    JNIEnv *env = GetJniEnv();
    return env->FindClass(classname);
}

}  // extern "C"
