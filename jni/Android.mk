LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_CFLAGS += -fPIC -std=c99
LOCAL_LDFLAGS += -fPIC
LOCAL_LDLIBS := -llog

LOCAL_MODULE    := offline_audience_switcher
LOCAL_SRC_FILES := offline_audience_switcher.c

include $(BUILD_EXECUTABLE)
