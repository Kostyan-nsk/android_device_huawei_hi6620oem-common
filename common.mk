#
# Copyright (C) 2015 The CyanogenMod Project
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
#

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

# Product common configurations
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# The gps config appropriate for this device
$(call inherit-product, device/common/gps/gps_eu_supl.mk)

# Wifi configuration
$(call inherit-product, hardware/broadcom/wlan/bcmdhd/config/config-bcm.mk)

# Inherit vendor tree common for hi6620oem platform
$(call inherit-product, vendor/huawei/hi6620oem-common/hi6620oem-vendor.mk)

# Overlays
DEVICE_PACKAGE_OVERLAYS += $(LOCAL_PATH)/overlay

# we have enough storage space to hold precise GC data
PRODUCT_TAGS += dalvik.gc.type-precise

# Ramdisk
PRODUCT_COPY_FILES += \
  $(call find-copy-subdir-files,*,$(LOCAL_PATH)/rootdir,root)

# Audio
PRODUCT_PACKAGES += \
    audio.a2dp.default \
    audio.usb.default \
    audio.r_submix.default \
    libaudioutils \
    libaudioroute \
    libaudio-resampler

# HW Codecs
PRODUCT_PACKAGES += \
    libstagefrighthw \
    libhantro_omx_core \
    libhantrovideodec \
    libhantrovideoenc

# HW specific
PRODUCT_PACKAGES += \
    gralloc.hi6620oem \
    hwcomposer.hi6620oem \
    lights.hi6620oem \
    memtrack.hi6620oem \
    power.hi6620oem \
    sensors.hi6620oem \
    liblivedisplay_jni \
    mac_addr \
    gpsdaemon \
    libfbcnf

# Shim libs
PRODUCT_PACKAGES += \
    libicuuc_shim \
    liblog_shim \
    libgui_shim \
    libbinder_shim

# Wifi
PRODUCT_PACKAGES += \
    hostapd \
    wpa_supplicant \
    wpa_supplicant.conf

# Packages
PRODUCT_PACKAGES += \
    HwCamera \
    YahooWeatherProvider \
    Lawnchair \
    Jelly

# Capabilities
PRODUCT_PACKAGES += \
    fs_config_files

# Recovery
PRODUCT_PACKAGES += \
    boot_reason \
    leds
PRODUCT_COPY_FILES += \
    bionic/libc/zoneinfo/tzdata:recovery/root/system/usr/share/zoneinfo/tzdata
#    $(LOCAL_PATH)/recovery/sbin/oeminfo_nvm_server:recovery/root/sbin/oeminfo_nvm_server \

# Properties
ADDITIONAL_DEFAULT_PROPERTIES += \
    ro.secure=0 \
    ro.adb.secure=0 \
    sys.usb.config=mpt,adb \
    dalvik.vm.image-dex2oat-threads=4 \
    dalvik.vm.boot-dex2oat-threads=3 \
    dalvik.vm.dex2oat-threads=3

PRODUCT_PROPERTY_OVERRIDES += \
    ro.opengles.version=131072 \
    ro.telephony.ril_class=HwHisiRIL \
    camera2.portability.force_api=1 \
    debug.hwui.render_dirty_regions=false \
    ro.hwui.texture_cache_size=48 \
    ro.hwui.texture_cache_flushrate=0.4

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.camera.autofocus.xml:system/etc/permissions/android.hardware.camera.autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.flash-autofocus.xml:system/etc/permissions/android.hardware.camera.flash-autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.front.xml:system/etc/permissions/android.hardware.camera.front.xml \
    frameworks/native/data/etc/android.hardware.bluetooth_le.xml:system/etc/permissions/android.hardware.bluetooth_le.xml \
    frameworks/native/data/etc/android.hardware.location.gps.xml:system/etc/permissions/android.hardware.location.gps.xml \
    frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:system/etc/permissions/android.hardware.sensor.gyroscope.xml \
    frameworks/native/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/native/data/etc/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
    frameworks/native/data/etc/android.hardware.telephony.gsm.xml:system/etc/permissions/android.hardware.telephony.gsm.xml \
    frameworks/native/data/etc/android.hardware.touchscreen.multitouch.jazzhand.xml:system/etc/permissions/android.hardware.touchscreen.multitouch.jazzhand.xml \
    frameworks/native/data/etc/android.hardware.usb.accessory.xml:system/etc/permissions/android.hardware.usb.accessory.xml \
    frameworks/native/data/etc/android.hardware.usb.host.xml:system/etc/permissions/android.hardware.usb.host.xml \
    frameworks/native/data/etc/android.hardware.wifi.direct.xml:system/etc/permissions/android.hardware.wifi.direct.xml \
    frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
    frameworks/native/data/etc/handheld_core_hardware.xml:system/etc/permissions/handheld_core_hardware.xml

# Media codecs
PRODUCT_COPY_FILES += \
    frameworks/av/media/libstagefright/data/media_codecs_google_video_le.xml:system/etc/media_codecs_google_video_le.xml \
    frameworks/av/media/libstagefright/data/media_codecs_google_audio.xml:system/etc/media_codecs_google_audio.xml

# Open GApps
GAPPS_VARIANT := nano
GAPPS_FORCE_MATCHING_DPI := true
GAPPS_EXCLUDED_PACKAGES := FaceLock
$(call inherit-product-if-exists, vendor/opengapps/build/opengapps-packages.mk)

PRODUCT_GMS_CLIENTID_BASE := android-huawei