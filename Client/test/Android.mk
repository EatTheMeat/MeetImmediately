LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := screencap
LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS += -fPIC
LOCAL_LDFLAGS += -fPIC 
LOCAL_ARM_MODE := arm
LOCAL_MULTILIB := 32

LOCAL_LDLIBS += -llog -lstdc++ -landroid


LOCAL_SRC_FILES := test.cpp

LOCAL_PRELINK_MODULE := false
include $(BUILD_EXECUTABLE)
