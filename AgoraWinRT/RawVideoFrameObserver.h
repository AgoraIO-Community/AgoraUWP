#pragma once
#include "pch.h"
#include "winrt/AgoraWinRT.h"

namespace winrt::AgoraWinRT::implementation
{

    class RawVideoFrameObserver : public agora::media::IVideoFrameObserver
    {
    public:
        void RegisterObserver(AgoraWinRT::VideoFrameObserver observer);

        // Í¨¹ý IVideoFrameObserver ¼Ì³Ð
        virtual bool onCaptureVideoFrame(VideoFrame& videoFrame) override;
        virtual bool onPreEncodeVideoFrame(VideoFrame& videoFrame) override;
        virtual bool onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame) override;
        virtual VIDEO_FRAME_TYPE getVideoFormatPreference() override;
        virtual bool getRotationApplied();
        virtual bool getMirrorApplied();
        virtual bool getSmoothRenderingEnabled();
        virtual uint32_t getObservedFramePosition();
        virtual bool isMultipleChannelFrameWanted();
        virtual bool onRenderVideoFrameEx(const char* channelId, unsigned int uid, VideoFrame& videoFrame) override;

    private:
        AgoraWinRT::VideoFrameObserver m_observer{ nullptr };
    };
}
