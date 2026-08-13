LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE            := libaudiocorehal.default
LOCAL_MULTILIB          := 64
LOCAL_VENDOR_MODULE     := true
LOCAL_MODULE_RELATIVE_PATH := hw

LOCAL_CFLAGS := \
    -DBACKEND_NDK \
    -Wall \
    -Wextra \
    -Werror \
    -Wthread-safety

LOCAL_VINTF_FRAGMENTS += manifest_audiocorehal_default.xml

LOCAL_SRC_FILES := \
    DefaultServices.cpp

LOCAL_HEADER_LIBRARIES :=  \
    libxsdc-utils \
    liberror_headers

LOCAL_SHARED_LIBRARIES := \
    libaudioaidlcommon \
    libaudioserviceexampleimpl \
    android.hardware.audio.core-V4-ndk \
    android.hardware.audio.core.sounddose-V4-ndk \
    libbase \
    libbinder_ndk \
    libcutils \
    liblog \
    libdl \
    libxml2 \
    libaudioutils \
    libutils \
    android.hardware.common-V2-ndk \
    android.media.audio.common.types-V5-ndk \
    libmedia_helper \
    libstagefright_foundation \
    libhidlbase \
    libhardware \
    libfmq

include $(BUILD_SHARED_LIBRARY)
