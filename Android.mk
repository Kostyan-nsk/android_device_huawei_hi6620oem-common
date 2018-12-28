LOCAL_PATH := $(call my-dir)

ifneq ($(filter p6s_u06 p7_l10 p7_l00,$(TARGET_DEVICE)),)

    include $(call all-makefiles-under,$(LOCAL_PATH))

endif
