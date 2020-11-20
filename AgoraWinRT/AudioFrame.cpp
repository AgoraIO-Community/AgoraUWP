#include "pch.h"
#include "AudioFrame.h"
#include "AudioFrame.g.cpp"

namespace winrt::AgoraWinRT::implementation
{
    AudioFrame::AudioFrame() :
        m_buffer(com_array<uint8_t>())
    {
    }
    AudioFrame::~AudioFrame()
    {
        Close();
    }
    AgoraWinRT::AUDIO_FRAME_TYPE AudioFrame::type()
    {
        return m_type;
    }
    void AudioFrame::type(AgoraWinRT::AUDIO_FRAME_TYPE const& value)
    {
        m_type = value;
    }
    uint32_t AudioFrame::samples()
    {
        return m_samples;
    }
    void AudioFrame::samples(uint32_t value)
    {
        m_samples = value;
    }
    uint8_t AudioFrame::bytesPerSample()
    {
        return m_bytesPerSample;
    }
    void AudioFrame::bytesPerSample(uint8_t value)
    {
        m_bytesPerSample = value;
    }
    uint8_t AudioFrame::channels()
    {
        return m_channels;
    }
    void AudioFrame::channels(uint8_t value)
    {
        m_channels = value;
    }
    uint32_t AudioFrame::samplesPerSec()
    {
        return m_samplePerSec;
    }
    void AudioFrame::samplesPerSec(uint32_t value)
    {
        m_samplePerSec = value;
    }
    com_array<uint8_t> AudioFrame::buffer()
    {
        return com_array(m_buffer.begin(), m_buffer.end());
    }
    void AudioFrame::buffer(array_view<uint8_t const> value)
    {
        m_buffer.clear();
        m_buffer = com_array(value.begin(), value.end());
    }
    uint64_t AudioFrame::renderTimeMs()
    {
        return m_renderTimeMs;
    }
    void AudioFrame::renderTimeMs(uint64_t value)
    {
        m_renderTimeMs = value;
    }
    int64_t AudioFrame::avsync_type()
    {
        return m_avsync_type;
    }
    void AudioFrame::avsync_type(int64_t value)
    {
        m_avsync_type = value;
    }
    void AudioFrame::Close()
    {
        m_buffer.clear();
    }
}
