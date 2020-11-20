#pragma once
#include "AudioFrame.g.h"

namespace winrt::AgoraWinRT::implementation
{
    struct AudioFrame : AudioFrameT<AudioFrame>
    {
        AudioFrame();
        ~AudioFrame();

        AgoraWinRT::AUDIO_FRAME_TYPE type();
        void type(AgoraWinRT::AUDIO_FRAME_TYPE const& value);
        uint32_t samples();
        void samples(uint32_t value);
        uint8_t bytesPerSample();
        void bytesPerSample(uint8_t value);
        uint8_t channels();
        void channels(uint8_t value);
        uint32_t samplesPerSec();
        void samplesPerSec(uint32_t value);
        com_array<uint8_t> buffer();
        void buffer(array_view<uint8_t const> value);
        uint64_t renderTimeMs();
        void renderTimeMs(uint64_t value);
        int64_t avsync_type();
        void avsync_type(int64_t value);
        void Close();
    private:
        AgoraWinRT::AUDIO_FRAME_TYPE m_type;
        uint32_t m_samples;
        uint8_t m_bytesPerSample;
        uint8_t m_channels;
        uint32_t m_samplePerSec;
        com_array<uint8_t> m_buffer;
        uint64_t m_renderTimeMs;
        int64_t m_avsync_type;
    };
}

namespace winrt::AgoraWinRT::factory_implementation
{
    struct AudioFrame : AudioFrameT<AudioFrame, implementation::AudioFrame>
    {

    };
}

