LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libffplayer
LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS += -fPIC
LOCAL_LDFLAGS += -fPIC 
LOCAL_ARM_MODE := arm
LOCAL_MULTILIB := 32
LOCAL_LDLIBS:=$(LOCAL_PATH)/prebuild/libavcodec.so
LOCAL_LDLIBS+=$(LOCAL_PATH)/prebuild/libavformat.so
LOCAL_LDLIBS+=$(LOCAL_PATH)/prebuild/libavutil.so

LOCAL_LDLIBS += -lmediandk -llog -lstdc++ -landroid

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/include \
	$(LOCAL_PATH)/src/encoder/include \

LOCAL_SRC_FILES := $(wildcard *.cpp $(LOCAL_PATH)/src/*.cpp)
LOCAL_SRC_FILES := $(wildcard *.c $(LOCAL_PATH)/src/*.c)
LOCAL_SRC_FILES += $(wildcard *.c $(LOCAL_PATH)/src/utils/*.c)
LOCAL_SRC_FILES += $(wildcard *.c $(LOCAL_PATH)/src/encoder/*.c)

LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)
