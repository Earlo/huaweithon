

cmake_minimum_required(VERSION 3.4.1)
add_library(huawei_arengine_ndk SHARED IMPORTED)
set_target_properties(huawei_arengine_ndk PROPERTIES IMPORTED_LOCATION
                     "${ARENGINE_LIBPATH}/${ANDROID_ABI}/libhuawei_arengine_ndk.so")

# This is the main app library.
add_library(hello_ar_native SHARED
           src/main/cpp/background_renderer.cc
           src/main/cpp/hello_ar_application.cc
           src/main/cpp/jni_interface.cc
           src/main/cpp/obj_renderer.cc
           src/main/cpp/plane_renderer.cc
           src/main/cpp/point_cloud_renderer.cc
           src/main/cpp/util.cc
           src/main/cpp/surfacetest.cc)

target_include_directories(hello_ar_native PRIVATE
           src/main/cpp
           ${ARENGINE_INCLUDE}
            ${ANDROID_NDK}/sources/third_party/vulkan/src/libs/glm)

target_link_libraries(hello_ar_native
                      android
                      log
                      GLESv2
                      huawei_arengine_ndk
                      mediandk
                      )

