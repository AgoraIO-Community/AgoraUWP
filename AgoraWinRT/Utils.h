#pragma once
#include <string>
#include "pch.h"
#include "Metadata.h"
#include "Packet.h"
#include "AudioFrame.h"
#include "VideoFrame.h"

namespace Utils {

	std::string To(winrt::hstring const& value);

	char* Copy(winrt::hstring const& value);

	winrt::hstring To(const char* value);

	winrt::hstring To(const char* value, size_t length);

	winrt::AgoraWinRT::RtcStats To(agora::rtc::RtcStats const& raw);

	winrt::AgoraWinRT::LocalAudioStats To(agora::rtc::LocalAudioStats const& raw);

	winrt::AgoraWinRT::LocalVideoStats To(agora::rtc::LocalVideoStats const& raw);

	winrt::AgoraWinRT::RemoteAudioStats To(agora::rtc::RemoteAudioStats const& raw);

	winrt::AgoraWinRT::RemoteVideoStats To(agora::rtc::RemoteVideoStats const& raw);

	winrt::com_array<winrt::AgoraWinRT::AudioVolumeInfo> To(const agora::rtc::AudioVolumeInfo* raw, int count);

	winrt::AgoraWinRT::LastmileProbeOneWayResult To(const agora::rtc::LastmileProbeOneWayResult& raw);

	winrt::AgoraWinRT::LastmileProbeResult To(const agora::rtc::LastmileProbeResult& raw);

	winrt::com_array<uint8_t> To(void* raw, int count);

	winrt::com_ptr<winrt::AgoraWinRT::implementation::Metadata> To(const agora::rtc::IMetadataObserver::Metadata& raw);

	winrt::com_ptr<winrt::AgoraWinRT::implementation::Packet> To(const agora::rtc::IPacketObserver::Packet& raw);

	winrt::com_ptr<winrt::AgoraWinRT::implementation::AudioFrame> To(const agora::media::IAudioFrameObserver::AudioFrame& raw);

	winrt::com_ptr<winrt::AgoraWinRT::implementation::VideoFrame> To(const agora::media::IVideoFrameObserver::VideoFrame& raw);

	void* To(winrt::com_array<uint8_t> const& value);

	void To(winrt::com_ptr<winrt::AgoraWinRT::implementation::VideoFrame> const& value, agora::media::IVideoFrameObserver::VideoFrame& raw);

	agora::rtc::BeautyOptions To(winrt::AgoraWinRT::BeautyOptions const& value);

	agora::rtc::VideoEncoderConfiguration To(winrt::AgoraWinRT::VideoEncoderConfiguration const& value);

	agora::rtc::TranscodingUser* To(winrt::com_array<winrt::AgoraWinRT::TranscodingUser> const& value);

	agora::rtc::RtcImage* To(winrt::AgoraWinRT::RtcImage const& value);

	agora::rtc::LiveStreamAdvancedFeature* To(winrt::com_array<winrt::AgoraWinRT::LiveStreamAdvancedFeature> const& value);

	agora::rtc::LiveTranscoding To(winrt::AgoraWinRT::LiveTranscoding const& value);

	agora::rtc::ChannelMediaInfo* To(winrt::AgoraWinRT::ChannelMediaInfo const& value);

	agora::rtc::ChannelMediaInfo* To(winrt::com_array<winrt::AgoraWinRT::ChannelMediaInfo> const& value);

	agora::rtc::ChannelMediaRelayConfiguration To(winrt::AgoraWinRT::ChannelMediaRelayConfiguration const& value);

	agora::rtc::LastmileProbeConfig To(winrt::AgoraWinRT::LastmileProbeConfig const& value);


	agora::media::ExternalVideoFrame* To(winrt::AgoraWinRT::ExternalVideoFrame const& value);

	void Free(agora::media::ExternalVideoFrame* value);

	agora::media::IAudioFrameObserver::AudioFrame* To(winrt::AgoraWinRT::AudioFrame const& value);

	void Free(agora::media::IAudioFrameObserver::AudioFrame* value);

	agora::rtc::Rectangle To(winrt::AgoraWinRT::Rectangle const& value);

	agora::rtc::WatermarkOptions To(winrt::AgoraWinRT::WatermarkOptions const& value);

	agora::rtc::EncryptionConfig To(winrt::AgoraWinRT::EncryptionConfig const& value);

	agora::rtc::InjectStreamConfig To(winrt::AgoraWinRT::InjectStreamConfig const& value);

	agora::rtc::CameraCapturerConfiguration To(winrt::AgoraWinRT::CameraCapturerConfiguration const& value);

	agora::rtc::ChannelMediaOptions To(winrt::AgoraWinRT::ChannelMediaOptions const& value);

	void* To(winrt::array_view<const uint8_t> const& value);

	agora::rtc::ClientRoleOptions To(winrt::AgoraWinRT::ClientRoleOptions const& value);

	agora::rtc::DataStreamConfig To(winrt::AgoraWinRT::DataStreamConfig const& value);

	agora::rtc::LogConfig To(winrt::AgoraWinRT::LogConfig const& value);
}