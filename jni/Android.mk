LOCAL_PATH :=$(call my-dir)

# godot-cpp lib
# include $(CLEAR_VARS)
# LOCAL_MODULE := godot-cpp
# LOCAL_SRC_FILES := libgodot-cpp.android.debug.arm64v8.a
# include $(PREBUILT_STATIC_LIBRARY)

FILE_LIST := \
  $(wildcard $(LOCAL_PATH)/*.cpp) \
  $(wildcard $(LOCAL_PATH)/*.c) \
  $(wildcard $(LOCAL_PATH)/play_integrity_native/*.cpp) \
  $(wildcard $(LOCAL_PATH)/gni_runtime/cpp/src/gni/*.cpp) \
  $(wildcard $(LOCAL_PATH)/gni_runtime/cpp/src/gni/common/*.cpp) \
  $(wildcard $(LOCAL_PATH)/gni_runtime\c\src\gni/*.cc)

include $(CLEAR_VARS)
LOCAL_MODULE := "simple"
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
TARGET_ARCH := arm64
TARGET_PLATFORM := android-31
LOCAL_LDLIBS := -llog
LOCAL_CFLAGS := -D__ANDROID__
# LOCAL_STATIC_LIBRARIES := godot-cpp

LOCAL_C_INCLUDES := \
  $(LOCAL_PATH)/../godot-headers \
  $(LOCAL_PATH)/gni_runtime/c/include \
  $(LOCAL_PATH)/gni_runtime/c/src \
  $(LOCAL_PATH)/gni_runtime/cpp/include \
  $(LOCAL_PATH)/gni_runtime/cpp/src \
  $(LOCAL_PATH)/play_integrity_native

include $(BUILD_SHARED_LIBRARY)
