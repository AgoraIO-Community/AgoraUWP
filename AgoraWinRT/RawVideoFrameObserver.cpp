#include "pch.h"
#include "RawVideoFrameObserver.h"
#include "Utils.h"

namespace winrt::AgoraWinRT::implementation
{
	void winrt::AgoraWinRT::implementation::RawVideoFrameObserver::RegisterObserver(AgoraWinRT::VideoFrameObserver observer)
	{
		m_observer = observer;
	}

	bool winrt::AgoraWinRT::implementation::RawVideoFrameObserver::onCaptureVideoFrame(VideoFrame& videoFrame)
	{
		if (m_observer) {
			auto data = Utils::To(videoFrame);
			auto result = m_observer.OnCaptureVideoFrame(*data);
			if (result && data->BeModified()) Utils::To(data, videoFrame);
			return result;
		}
		else return true;
	}

	bool winrt::AgoraWinRT::implementation::RawVideoFrameObserver::onPreEncodeVideoFrame(VideoFrame& videoFrame)
	{
		if (m_observer) {
			auto data = Utils::To(videoFrame);
			auto result = m_observer.OnPreEncodeVideFrame(*data);
			if (result && data->BeModified()) Utils::To(data, videoFrame);
			return result;
		}
		else return true;
	}

	bool winrt::AgoraWinRT::implementation::RawVideoFrameObserver::onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame)
	{
		if (m_observer) {
			auto data = Utils::To(videoFrame);
			auto result = m_observer.OnRenderVideoFrame(uid, *data);
			if (result && data->BeModified()) Utils::To(data, videoFrame);
			return result;
		}
		else return true;
	}

	agora::media::IVideoFrameObserver::VIDEO_FRAME_TYPE winrt::AgoraWinRT::implementation::RawVideoFrameObserver::getVideoFormatPreference()
	{
		if (m_observer) return (agora::media::IVideoFrameObserver::VIDEO_FRAME_TYPE)m_observer.GetVideoFramePreference();
		else return agora::media::IVideoFrameObserver::FRAME_TYPE_YUV420;
	}

	bool winrt::AgoraWinRT::implementation::RawVideoFrameObserver::getRotationApplied()
	{
		if (m_observer) return m_observer.GetRotationApplied();
		else return false;
	}

	bool winrt::AgoraWinRT::implementation::RawVideoFrameObserver::getMirrorApplied()
	{
		if (m_observer) return m_observer.GetMirrorApplied();
		else return false;
	}

	bool winrt::AgoraWinRT::implementation::RawVideoFrameObserver::getSmoothRenderingEnabled()
	{
		if (m_observer) return m_observer.GetSmoothRenderingEnabled();
		else return false;
	}

	uint32_t winrt::AgoraWinRT::implementation::RawVideoFrameObserver::getObservedFramePosition()
	{
		if (m_observer) return m_observer.GetObservedFramePosition();
		else return agora::media::IVideoFrameObserver::POSITION_POST_CAPTURER | agora::media::IVideoFrameObserver::POSITION_PRE_RENDERER;
	}

	bool winrt::AgoraWinRT::implementation::RawVideoFrameObserver::isMultipleChannelFrameWanted()
	{
		if (m_observer) return m_observer.IsMultipleChannelVideoFrameWanted();
		else return false;
	}

	bool winrt::AgoraWinRT::implementation::RawVideoFrameObserver::onRenderVideoFrameEx(const char* channelId, unsigned int uid, VideoFrame& videoFrame)
	{
		if (m_observer) {
			auto data = Utils::To(videoFrame);
			auto result = m_observer.OnRenderVideoFrameEx(Utils::To(channelId), uid, *data);
			if (result && data->BeModified()) Utils::To(data, videoFrame);
			return result;
		}
		else return true;
	}
}