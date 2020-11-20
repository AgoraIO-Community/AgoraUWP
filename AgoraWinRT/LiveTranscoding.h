#pragma once
#include "LiveTranscoding.g.h"

namespace winrt::AgoraWinRT::implementation
{
	struct LiveTranscoding : LiveTranscodingT<LiveTranscoding>
	{
		LiveTranscoding();

		~LiveTranscoding();

		void Close();

		int32_t width();
		void width(int32_t value);
		int32_t height();
		void height(int32_t value);
		int32_t videoBitrate();
		void videoBitrate(int32_t value);
		int32_t videoFramerate();
		void videoFramerate(int32_t value);
		bool lowLatency();
		void lowLatency(bool value);
		int32_t videoGop();
		void videoGop(int32_t value);
		AgoraWinRT::VIDEO_CODEC_PROFILE_TYPE videoCodecProfile();
		void videoCodecProfile(AgoraWinRT::VIDEO_CODEC_PROFILE_TYPE const& value);
		uint64_t backgroundColor();
		void backgroundColor(uint64_t value);
		com_array<AgoraWinRT::TranscodingUser> transcodingUsers();
		void transcodingUsers(array_view<AgoraWinRT::TranscodingUser const> value);
		hstring transcodingExtraInfo();
		void transcodingExtraInfo(hstring const& value);
		hstring metadata();
		void metadata(hstring const& value);
		AgoraWinRT::RtcImage watermark();
		void watermark(AgoraWinRT::RtcImage const& value);
		AgoraWinRT::RtcImage backgroundImage();
		void backgroundImage(AgoraWinRT::RtcImage const& value);
		AgoraWinRT::AUDIO_SAMPLE_RATE_TYPE audioSampleRate();
		void audioSampleRate(AgoraWinRT::AUDIO_SAMPLE_RATE_TYPE const& value);
		int32_t audioBitrate();
		void audioBitrate(int32_t value);
		int32_t audioChannels();
		void audioChannels(int32_t value);
		AgoraWinRT::AUDIO_CODEC_PROFILE_TYPE audioCodecProfile();
		void audioCodecProfile(AgoraWinRT::AUDIO_CODEC_PROFILE_TYPE const& value);
		com_array<AgoraWinRT::LiveStreamAdvancedFeature> advancedFeatures();
		void advancedFeatures(array_view<AgoraWinRT::LiveStreamAdvancedFeature const> value);
	private:
		int32_t m_width;
		int32_t m_height;
		int32_t m_videoBitrate;
		int32_t m_videoFramerate;
		bool m_lowLatency;
		int32_t m_videoGop;
		AgoraWinRT::VIDEO_CODEC_PROFILE_TYPE m_videoCodecProfile;
		uint64_t m_backgroundColor;
		com_array<AgoraWinRT::TranscodingUser> m_transcodingUsers;
		hstring m_transcodingExtraInfo;
		hstring m_metadata;
		AgoraWinRT::RtcImage m_watermark;
		AgoraWinRT::RtcImage m_backgroundImage;
		AgoraWinRT::AUDIO_SAMPLE_RATE_TYPE m_audioSampleRate;
		int32_t m_audioBitrate;
		int32_t m_audioChannels;
		AgoraWinRT::AUDIO_CODEC_PROFILE_TYPE m_audioCodecProfile;
		com_array<AgoraWinRT::LiveStreamAdvancedFeature> m_advancedFeatures;
	};
}
