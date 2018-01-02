LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := screencap
LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS += -pie -fPIC
LOCAL_LDFLAGS += -pie  -fPIC 
LOCAL_ARM_MODE := arm
LOCAL_MULTILIB := 32

LOCAL_LDLIBS += -llog -lstdc++ -landroid -l
LOCAL_LDLIBS+=$(LOCAL_PATH)/../jni/libs/armeabi/libffplayer.so

LOCAL_SRC_FILES := test.c

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/../jni/include \
	
LOCAL_PRELINK_MODULE := false
include $(BUILD_EXECUTABLE)
