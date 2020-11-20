#include "pch.h"
#include "RawAudioFrameObsever.h"
#include "Utils.h"

namespace winrt::AgoraWinRT::implementation
{
	void winrt::AgoraWinRT::implementation::RawAudioFrameObserver::RegisterObserver(AgoraWinRT::AudioFrameObserver observer)
	{
		m_observer = observer;
	}

	bool winrt::AgoraWinRT::implementation::RawAudioFrameObserver::onRecordAudioFrame(AudioFrame& audioFrame)
	{
		if (m_observer) {
			auto data = Utils::To(audioFrame);
			return m_observer.OnRecordAudioFrame(*data);
		}
		else return true;
	}

	bool winrt::AgoraWinRT::implementation::RawAudioFrameObserver::onPlaybackAudioFrame(AudioFrame& audioFrame)
	{
		if (m_observer) {
			auto data = Utils::To(audioFrame);
			return m_observer.OnPlaybackAudioFrame(*data);
		}
		else return true;
	}

	bool winrt::AgoraWinRT::implementation::RawAudioFrameObserver::onMixedAudioFrame(AudioFrame& audioFrame)
	{
		if (m_observer) {
			auto data = Utils::To(audioFrame);
			return m_observer.OnMixedAudioFrame(*data);
		}
		else return true;
	}

	bool winrt::AgoraWinRT::implementation::RawAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame& audioFrame)
	{
		if (m_observer) {
			auto data = Utils::To(audioFrame);
			return m_observer.OnPlaybackAudioFrameBeforeMixing(uid, *data);
		}
		else return true;
	}

	bool winrt::AgoraWinRT::implementation::RawAudioFrameObserver::isMultipleChannelFrameWanted()
	{
		if (m_observer) return m_observer.IsMultipleChannelAudioFrameWanted();
		else return false;
	}

	bool winrt::AgoraWinRT::implementation::RawAudioFrameObserver::onPlaybackAudioFrameBeforeMixingEx(const char* channelId, unsigned int uid, AudioFrame& audioFrame)
	{
		if (m_observer) {
			auto data = Utils::To(audioFrame);
			return m_observer.OnPlaybackAudioFrameBeforeMixingEx(Utils::To(channelId), uid, *data);
		}
		else return true;
	}
}