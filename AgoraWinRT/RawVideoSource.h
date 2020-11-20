#pragma once
#include "pch.h"
#include "winrt/AgoraWinRT.h"

namespace winrt::AgoraWinRT::implementation {
	class RawVideoSource : public agora::rtc::IVideoSource
	{
	public:
		RawVideoSource(AgoraWinRT::VideoSource source);

		// Í¨¹ý IVideoSource ¼Ì³Ð
		virtual bool onInitialize(agora::rtc::IVideoFrameConsumer* consumer) override;
		virtual void onDispose() override;
		virtual bool onStart() override;
		virtual void onStop() override;
		virtual agora::media::ExternalVideoFrame::VIDEO_PIXEL_FORMAT getBufferType() override;
		virtual agora::rtc::VIDEO_CAPTURE_TYPE getVideoCaptureType() override;
		virtual agora::rtc::VideoContentHint getVideoContentHint() override;

	private:
		AgoraWinRT::VideoSource m_source{ nullptr };
		AgoraWinRT::VideoSourceConsumer m_consumer{ nullptr };
	};

}

