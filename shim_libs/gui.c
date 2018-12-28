/*
 * Copyright (C) 2016 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "gui_shim"

#include <pthread.h>
#include <utils/Timers.h>
#include <log/log.h>

//various funcs we'll need to call, in their mangled form

//android::String8::String8(char const*)
extern void _ZN7android7String8C1EPKc(void **str8P, const char *str);

//android::String8::~String8()
extern void _ZN7android7String8D1Ev(void **str8P);

//android::String16::String16(char const*)
extern void _ZN7android8String16C1EPKc(void **str16P, const char *str);

//android::String16::~String16()
extern void _ZN7android8String16D1Ev(void **str16P);

//android::SensorManager::~SensorManager()
extern void _ZN7android13SensorManagerD1Ev(void *sensorMgr);

//android::SensorManager::SensorManager(android::String16 const&)
extern void _ZN7android13SensorManagerC1ERKNS_8String16E(void *sensorMgr, void **str16P);

//android::SensorManager::createEventQueue(android::String8, int)
extern void _ZN7android13SensorManager16createEventQueueENS_7String8Ei(void **retVal, void *sensorMgr, void **str8P, int mode);

/*
//---------------------------------------------------------------------------------------------------------------------
//android::BufferItem::BufferItem()
extern void _ZN7android10BufferItemC1Ev(void **BufferItem);
extern void _ZN7android10BufferItemC2Ev(void **BufferItem);

//android::BufferItemConsumer::acquireBuffer(android::BufferItem*, nsecs_t presentWhen, bool waitForFence)
extern int32_t _ZN7android18BufferItemConsumer13acquireBufferEPNS_10BufferItemExb(void* BufferItemConsumer, void *BufferItem,
                                                                nsecs_t presentWhen, int waitForFence);

//android::BufferItemConsumer::releaseBuffer(const BufferItem &item, const sp<Fence>& releaseFence = Fence::NO_FENCE)
extern int32_t _ZN7android18BufferItemConsumer13releaseBufferERKNS_10BufferItemERKNS_2spINS_5FenceEEE(void *BufferItemConsumer,
                                                                const void *BufferItem, int);

//android::ConsumerBase::acquireBufferLocked(android::BufferItem*, nsecs_t presentWhen, uint64_t maxFrameNumber = 0)
extern int32_t _ZN7android12ConsumerBase19acquireBufferLockedEPNS_10BufferItemExy(void *ConsumerBase, void *item,
                                                                nsecs_t presentWhen, uint64_t maxFrameNumber);
//---------------------------------------------------------------------------------------------------------------------
*/

//data exports we must provide for camera library to be happy

/*
 * DATA:     android::Singleton<android::SensorManager>::sLock
 * USE:      INTERPOSE: a mutes that camera lib will insist on accessing
 * NOTES:    In L, the sensor manager exposed this lock that callers
 *           actually locked & unlocked when accessing it. In M this
 *           is no longer the case, but we still must provide it for
 *           the camera library to be happy. It will lock nothnhing, but
 *           as long as it is a real lock and pthread_mutex_* funcs
 *           work on it, the camera library will be happy.
 */
pthread_mutex_t _ZN7android9SingletonINS_13SensorManagerEE5sLockE = PTHREAD_MUTEX_INITIALIZER;

/*
 * DATA:     android::Singleton<android::SensorManager>::sInstance
 * USE:      INTERPOSE: a singleton instance of SensorManager
 * NOTES:    In L, the sensor manager exposed this variable, as it was
 *           a singleton and one could just access this directly to get
 *           the current already-existing instance if it happened to
 *           already exist. If not one would create one and store it
 *           there. In M this is entirely different, but the camera library
 *           does not know that. So we'll init it to NULL to signify that
 *           no current instance exists, let it create one, and store it
 *           here, and upon unloading we'll clean it up, if it is not
 *           NULL (which is what it would be if the camera library itself
 *           did the cleanup).
 */
void* _ZN7android9SingletonINS_13SensorManagerEE9sInstanceE = NULL;

/*
 * FUNCTION: android::SensorManager::SensorManager(void)
 * USE:      INTERPOSE: construct a sensor manager object
 * NOTES:    This constructor no longer exists in M, instead now one must pass
 *           in a package name as a "string16" to the consrtuctor. Since this
 *           lib only services camera library, it is easy for us to just do that
 *           and this provide the constructor that the camera library wants.
 *           The package name we use if "camera.msm8960". Why not?
 */
void _ZN7android13SensorManagerC1Ev(void *sensorMgr)
{
    void *string;

    _ZN7android8String16C1EPKc(&string, "camera.hi6620oem");
    _ZN7android13SensorManagerC1ERKNS_8String16E(sensorMgr, &string);
    _ZN7android8String16D1Ev(&string);
}

/*
 * FUNCTION: android::SensorManager::createEventQueue(void)
 * USE:      INTERPOSE: create an event queue to receive events
 * NOTES:    This function no longer exists in M, instead now one must pass
 *           in a client name as a "string8" and an integer "mode"to it. M
 *           sources list default values for these params as an empty string
 *           and 0. So we'll craft the same call here.
 */
void _ZN7android13SensorManager16createEventQueueEv(void **retVal, void *sensorMgr)
{
    void *string;

    _ZN7android7String8C1EPKc(&string, "");
    _ZN7android13SensorManager16createEventQueueENS_7String8Ei(retVal, sensorMgr, &string, 0);
    _ZN7android7String8D1Ev(&string);
}
/*
//---------------------------------------------------------------------------------------------------------------------
// android::ConsumerBase::acquireBufferLocked(android::IGraphicBufferConsumer::BufferItem*, long long)
int32_t _ZN7android12ConsumerBase19acquireBufferLockedEPNS_22IGraphicBufferConsumer10BufferItemEx(void *ConsumerBase, void *BufferItem, nsecs_t presentWhen)
{
    ALOGD("android::ConsumerBase::acquireBufferLocked(android::IGraphicBufferConsumer::BufferItem*, long long)");
    return _ZN7android12ConsumerBase19acquireBufferLockedEPNS_10BufferItemExy(ConsumerBase, BufferItem, presentWhen, 0);
}


// android::IGraphicBufferConsumer::BufferItem::BufferItem()
void _ZN7android22IGraphicBufferConsumer10BufferItemC2Ev(void **BufferItem)
{
    ALOGD("android::IGraphicBufferConsumer::BufferItem::BufferItem()");
    _ZN7android10BufferItemC2Ev(BufferItem);
}

// android::IGraphicBufferConsumer::BufferItem::BufferItem()
void _ZN7android22IGraphicBufferConsumer10BufferItemC1Ev(void **BufferItem)
{
    ALOGD("android::IGraphicBufferConsumer::BufferItem::BufferItem()");
    _ZN7android10BufferItemC2Ev(BufferItem);
}

// android::BufferItemConsumer::acquireBuffer(android::IGraphicBufferConsumer::BufferItem*, long long, bool)
int32_t _ZN7android18BufferItemConsumer13acquireBufferEPNS_22IGraphicBufferConsumer10BufferItemExb(void *BufferItemConsumer, void *BufferItem, nsecs_t presentWhen, int waitForFence)
{
    ALOGD("android::BufferItemConsumer::acquireBuffer(android::IGraphicBufferConsumer::BufferItem*, long long, bool)");
    return _ZN7android18BufferItemConsumer13acquireBufferEPNS_10BufferItemExb(BufferItemConsumer, BufferItem, presentWhen, waitForFence);
}

// android::BufferItemConsumer::releaseBuffer(android::IGraphicBufferConsumer::BufferItem const&, android::sp<android::Fence> const&)
int32_t _ZN7android18BufferItemConsumer13releaseBufferERKNS_22IGraphicBufferConsumer10BufferItemERKNS_2spINS_5FenceEEE(void *BufferItemConsumer, const void *BufferItem, __unused int Fence)
{
    ALOGD("android::BufferItemConsumer::releaseBuffer(android::IGraphicBufferConsumer::BufferItem const&, android::sp<android::Fence> const&)");
    return _ZN7android18BufferItemConsumer13releaseBufferERKNS_10BufferItemERKNS_2spINS_5FenceEEE(BufferItemConsumer, BufferItem, 0);
}

// android::BufferItemConsumer::setDefaultBufferFormat(unsigned int)
int32_t _ZN7android18BufferItemConsumer22setDefaultBufferFormatEj(__unused uint32_t defaultFormat)
{
    ALOGD("android::BufferItemConsumer::setDefaultBufferFormat(unsigned int)");
    return 0;
}

// android::BufferItemConsumer::setDefaultBufferSize(unsigned int, unsigned int)
int32_t _ZN7android18BufferItemConsumer20setDefaultBufferSizeEjj(__unused uint32_t w, __unused uint32_t h)
{
    ALOGD("android::BufferItemConsumer::setDefaultBufferSize(unsigned int, unsigned int)");
    return 0;
}

// android::ICameraRecordingProxy::getCommonBaseAddress()
uint32_t _ZN7android21ICameraRecordingProxy20getCommonBaseAddressEv(void)
{
    ALOGD("android::ICameraRecordingProxy::getCommonBaseAddress()");
    return 0;
}
//---------------------------------------------------------------------------------------------------------------------
*/