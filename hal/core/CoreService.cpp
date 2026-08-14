/*
 * Copyright (c) 2023-2024 Qualcomm Innovation Center, Inc. All rights reserved.
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#define LOG_TAG "AHAL_CoreService_QTI"

#include <android-base/logging.h>
#include <android-base/properties.h>
#include <android/binder_ibinder_platform.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

#include <qti-audio-core/Module.h>
#include <qti-audio-core/ModulePrimary.h>
#include <qti-audio-core/Platform.h>
#include <cstdlib>
#include <ctime>

static std::shared_ptr<aidl::android::hardware::audio::core::IModule> gModuleDefaultQti;

auto registerBinderAsService = [](auto &&binder, const std::string &serviceName) {
    AIBinder_setMinSchedulerPolicy(binder.get(), SCHED_NORMAL, ANDROID_PRIORITY_AUDIO);
    binder_exception_t status = AServiceManager_addService(binder.get(), serviceName.c_str());
    if (status != EX_NONE) {
        LOG(ERROR) << __func__ << " failed to register " << serviceName << " ret:" << status;
    } else {
        LOG(INFO) << __func__ << " successfully registered " << serviceName << " ret:" << status;
    }
    return status;
};

bool makeIModuleDefaultQti() {
    if (gModuleDefaultQti == nullptr) {
        auto& platform = ::qti::audio::core::Platform::getInstance();
        if (!platform.isPalReady()) {
            LOG(ERROR) << __func__
                       << " PAL is unavailable; leaving IModule/default to the AOSP fallback";
            return false;
        }
        gModuleDefaultQti = ndk::SharedRefBase::make<::qti::audio::core::ModulePrimary>();
    }
    return true;
}

int32_t registerIModuleDefaultQti() {
    if (!makeIModuleDefaultQti()) {
        return STATUS_NO_INIT;
    }
    const std::string kServiceName =
            std::string(gModuleDefaultQti->descriptor).append("/").append("default");
    return registerBinderAsService(gModuleDefaultQti->asBinder(), kServiceName);
}

extern "C" __attribute__((visibility("default"))) int32_t registerServices() {
    return registerIModuleDefaultQti();
}

extern "C" __attribute__((visibility("default"))) void* getIModuleDefaultQti() {
    if (!makeIModuleDefaultQti()) {
        return nullptr;
    }
    return gModuleDefaultQti.get();
}
