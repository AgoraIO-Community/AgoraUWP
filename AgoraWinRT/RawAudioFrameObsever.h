#pragma once
#include "pch.h"
#include "winrt/AgoraWinRT.h"

namespace winrt::AgoraWinRT::implementation
{
    class RawAudioFrameObserver : public agora::media::IAudioFrameObserver
    {
    public:
        void RegisterObserver(AgoraWinRT::AudioFrameObserver observer);

        // Í¨¹ý IAudioFrameObserver ¼Ì³Ð
        virtual bool onRecordAudioFrame(AudioFrame& audioFrame) override;
        virtual bool onPlaybackAudioFrame(AudioFrame& audioFrame) override;
        virtual bool onMixedAudioFrame(AudioFrame& audioFrame) override;
        virtual bool onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame& audioFrame) override;
        virtual bool isMultipleChannelFrameWanted() override;
        virtual bool onPlaybackAudioFrameBeforeMixingEx(const char* channelId, unsigned int uid, AudioFrame& audioFrame) override;
    private:
        AgoraWinRT::AudioFrameObserver m_observer{ nullptr };
    };

}
