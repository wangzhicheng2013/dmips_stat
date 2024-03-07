LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := dmips_stat_android
LOCAL_C_INCLUDES := $(LOCAL_PATH)/inc
LOCAL_C_INCLUDES += $(LOCAL_PATH)/src
LOCAL_SRC_FILES = $(LOCAL_PATH)/src/main.cpp
LOCAL_LDLIBS = -L$(LOCAL_PATH)/lib -pthread 

include $(BUILD_EXECUTABLE)
