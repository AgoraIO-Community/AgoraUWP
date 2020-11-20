#include "pch.h"
#include "LiveTranscoding.h"
#include "LiveTranscoding.g.cpp"

namespace winrt::AgoraWinRT::implementation
{
    LiveTranscoding::LiveTranscoding() :
        m_transcodingUsers(winrt::com_array<AgoraWinRT::TranscodingUser>()),
        m_advancedFeatures(winrt::com_array<AgoraWinRT::LiveStreamAdvancedFeature>())
    {}

    LiveTranscoding::~LiveTranscoding()
    {
        Close();
    }
    void LiveTranscoding::Close()
    {
        m_transcodingUsers.clear();
        m_advancedFeatures.clear();
    }
    int32_t LiveTranscoding::width()
    {
        return m_width;
    }
    void LiveTranscoding::width(int32_t value)
    {
        m_width = value;
    }
    int32_t LiveTranscoding::height()
    {
        return m_height;
    }
    void LiveTranscoding::height(int32_t value)
    {
        m_height = value;
    }
    int32_t LiveTranscoding::videoBitrate()
    {
        return m_videoBitrate;
    }
    void LiveTranscoding::videoBitrate(int32_t value)
    {
        m_videoBitrate = value;
    }
    int32_t LiveTranscoding::videoFramerate()
    {
        return m_videoFramerate;
    }
    void LiveTranscoding::videoFramerate(int32_t value)
    {
        m_videoFramerate = value;
    }
    bool LiveTranscoding::lowLatency()
    {
        return m_lowLatency;
    }
    void LiveTranscoding::lowLatency(bool value)
    {
        m_lowLatency = value;
    }
    int32_t LiveTranscoding::videoGop()
    {
        return m_videoGop;
    }
    void LiveTranscoding::videoGop(int32_t value)
    {
        m_videoGop = value;
    }
    AgoraWinRT::VIDEO_CODEC_PROFILE_TYPE LiveTranscoding::videoCodecProfile()
    {
        return m_videoCodecProfile;
    }
    void LiveTranscoding::videoCodecProfile(AgoraWinRT::VIDEO_CODEC_PROFILE_TYPE const& value)
    {
        m_videoCodecProfile = value;
    }
    uint64_t LiveTranscoding::backgroundColor()
    {
        return m_backgroundColor;
    }
    void LiveTranscoding::backgroundColor(uint64_t value)
    {
        m_backgroundColor = value;
    }
    com_array<AgoraWinRT::TranscodingUser> LiveTranscoding::transcodingUsers()
    {
        return com_array(m_transcodingUsers.begin(), m_transcodingUsers.end());
    }
    void LiveTranscoding::transcodingUsers(array_view<AgoraWinRT::TranscodingUser const> value)
    {
        m_transcodingUsers.clear();
        m_transcodingUsers = com_array(value.begin(), value.end());
    }
    hstring LiveTranscoding::transcodingExtraInfo()
    {
        return m_transcodingExtraInfo;
    }
    void LiveTranscoding::transcodingExtraInfo(hstring const& value)
    {
        m_transcodingExtraInfo = value;
    }
    hstring LiveTranscoding::metadata()
    {
        return m_metadata;
    }
    void LiveTranscoding::metadata(hstring const& value)
    {
        m_metadata = value;
    }
    AgoraWinRT::RtcImage LiveTranscoding::watermark()
    {
        return m_watermark;
    }
    void LiveTranscoding::watermark(AgoraWinRT::RtcImage const& value)
    {
        m_watermark = value;
    }
    AgoraWinRT::RtcImage LiveTranscoding::backgroundImage()
    {
        return m_backgroundImage;
    }
    void LiveTranscoding::backgroundImage(AgoraWinRT::RtcImage const& value)
    {
        m_backgroundImage = value;
    }
    AgoraWinRT::AUDIO_SAMPLE_RATE_TYPE LiveTranscoding::audioSampleRate()
    {
        return m_audioSampleRate;
    }
    void LiveTranscoding::audioSampleRate(AgoraWinRT::AUDIO_SAMPLE_RATE_TYPE const& value)
    {
        m_audioSampleRate = value;
    }
    int32_t LiveTranscoding::audioBitrate()
    {
        return m_audioBitrate;
    }
    void LiveTranscoding::audioBitrate(int32_t value)
    {
        m_audioBitrate = value;
    }
    int32_t LiveTranscoding::audioChannels()
    {
        return m_audioChannels;
    }
    void LiveTranscoding::audioChannels(int32_t value)
    {
        m_audioChannels = value;
    }
    AgoraWinRT::AUDIO_CODEC_PROFILE_TYPE LiveTranscoding::audioCodecProfile()
    {
        return m_audioCodecProfile;
    }
    void LiveTranscoding::audioCodecProfile(AgoraWinRT::AUDIO_CODEC_PROFILE_TYPE const& value)
    {
        m_audioCodecProfile = value;
    }
    com_array<AgoraWinRT::LiveStreamAdvancedFeature> LiveTranscoding::advancedFeatures()
    {
        return com_array(m_advancedFeatures.begin(), m_advancedFeatures.end());
    }
    void LiveTranscoding::advancedFeatures(array_view<AgoraWinRT::LiveStreamAdvancedFeature const> value)
    {
        m_advancedFeatures.clear();
        m_advancedFeatures = com_array(value.begin(), value.end());
    }
}
