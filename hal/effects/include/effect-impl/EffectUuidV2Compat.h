/*
 * Copyright (c) 2026 Klee Project
 * SPDX-License-Identifier: BSD-3-Clause-Clear
 */

#pragma once

#include <cstdint>
#include <cstdio>

#include <aidl/android/hardware/audio/effect/Descriptor.h>
#include <aidl/android/media/audio/common/AudioUuid.h>

namespace aidl::qti::effects::v2 {

using ::aidl::android::hardware::audio::effect::Descriptor;
using ::aidl::android::media::audio::common::AudioUuid;

inline AudioUuid parseUuid(const char* str) {
    AudioUuid uuid{};
    uint32_t fields[10]{};
    if (str == nullptr ||
        std::sscanf(str, "%08x-%04x-%04x-%04x-%02x%02x%02x%02x%02x%02x", fields,
                    fields + 1, fields + 2, fields + 3, fields + 4, fields + 5,
                    fields + 6, fields + 7, fields + 8, fields + 9) != 10) {
        return uuid;
    }

    uuid.timeLow = static_cast<int32_t>(fields[0]);
    uuid.timeMid = static_cast<int32_t>(fields[1]);
    uuid.timeHiAndVersion = static_cast<int32_t>(fields[2]);
    uuid.clockSeq = static_cast<int32_t>(fields[3]);
    uuid.node.insert(uuid.node.end(),
                     {static_cast<uint8_t>(fields[4]), static_cast<uint8_t>(fields[5]),
                      static_cast<uint8_t>(fields[6]), static_cast<uint8_t>(fields[7]),
                      static_cast<uint8_t>(fields[8]), static_cast<uint8_t>(fields[9])});
    return uuid;
}

#define KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(symbol, descriptorSymbol)       \
    inline const AudioUuid& getEffectTypeUuid##symbol() {                  \
        static const AudioUuid uuid = parseUuid(Descriptor::descriptorSymbol); \
        return uuid;                                                       \
    }

KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(AcousticEchoCanceler, EFFECT_TYPE_UUID_AEC)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(AutomaticGainControlV1, EFFECT_TYPE_UUID_AGC1)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(AutomaticGainControlV2, EFFECT_TYPE_UUID_AGC2)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(BassBoost, EFFECT_TYPE_UUID_BASS_BOOST)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(Downmix, EFFECT_TYPE_UUID_DOWNMIX)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(DynamicsProcessing, EFFECT_TYPE_UUID_DYNAMICS_PROCESSING)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(Equalizer, EFFECT_TYPE_UUID_EQUALIZER)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(HapticGenerator, EFFECT_TYPE_UUID_HAPTIC_GENERATOR)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(LoudnessEnhancer, EFFECT_TYPE_UUID_LOUDNESS_ENHANCER)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(EnvReverb, EFFECT_TYPE_UUID_ENV_REVERB)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(PresetReverb, EFFECT_TYPE_UUID_PRESET_REVERB)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(NoiseSuppression, EFFECT_TYPE_UUID_NS)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(Spatializer, EFFECT_TYPE_UUID_SPATIALIZER)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(Virtualizer, EFFECT_TYPE_UUID_VIRTUALIZER)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(Visualizer, EFFECT_TYPE_UUID_VISUALIZER)
KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER(Volume, EFFECT_TYPE_UUID_VOLUME)

inline const AudioUuid& zeroUuid() {
    static const AudioUuid uuid{};
    return uuid;
}

#undef KLEE_DEFINE_EFFECT_TYPE_UUID_GETTER

} // namespace aidl::qti::effects::v2
