# Copyright (C) 2008 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := libicuuc
LOCAL_MODULE := libicuuc_shim
LOCAL_PROPRIETARY_MODULE := true
LOCAL_SRC_FILES := icuuc.c
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SHARED_LIBRARIES := liblog
LOCAL_MODULE := liblog_shim
LOCAL_PROPRIETARY_MODULE := true
LOCAL_CFLAGS := -Wno-unused-parameter
LOCAL_SRC_FILES := log.c
include $(BUILD_SHARED_LIBRARY)

# camera
include $(CLEAR_VARS)
LOCAL_SRC_FILES := gui.c
LOCAL_SHARED_LIBRARIES := libgui libutils liblog
LOCAL_MODULE := libgui_shim
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := binder.c
LOCAL_SHARED_LIBRARIES := libbinder
LOCAL_MODULE := libbinder_shim
LOCAL_PROPRIETARY_MODULE := true
include $(BUILD_SHARED_LIBRARY)
