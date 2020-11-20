#include "pch.h"
#include "RawVideoSource.h"
#include "VideoSourceConsumer.h"

namespace winrt::AgoraWinRT::implementation {
	RawVideoSource::RawVideoSource(AgoraWinRT::VideoSource source) : m_source(source)
	{

	}

	bool RawVideoSource::onInitialize(agora::rtc::IVideoFrameConsumer* consumer)
	{
		m_consumer = winrt::make<winrt::AgoraWinRT::implementation::VideoSourceConsumer>(consumer);

		return m_source.OnInitialize(m_consumer);
	}

	void RawVideoSource::onDispose()
	{
		m_source.OnDispose();
	}

	bool RawVideoSource::onStart()
	{
		return m_source.OnStart();
	}

	void RawVideoSource::onStop()
	{
		m_source.OnStop();
	}

	agora::media::ExternalVideoFrame::VIDEO_PIXEL_FORMAT RawVideoSource::getBufferType()
	{
		return agora::media::ExternalVideoFrame::VIDEO_PIXEL_FORMAT();
	}

	agora::rtc::VIDEO_CAPTURE_TYPE RawVideoSource::getVideoCaptureType()
	{
		return agora::rtc::VIDEO_CAPTURE_TYPE(m_source.GetVideoCaptureType());
	}

	agora::rtc::VideoContentHint RawVideoSource::getVideoContentHint()
	{
		return agora::rtc::VideoContentHint(m_source.GetVideoContentHint());
	}

}