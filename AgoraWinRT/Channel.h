#pragma once
#include "pch.h"
#include "Channel.g.h"

namespace winrt::AgoraWinRT::implementation
{
	struct Channel : ChannelT<Channel>,
		public agora::rtc::IPacketObserver,
		public agora::rtc::IMetadataObserver,
		public agora::rtc::IChannelEventHandler
	{
		Channel() = default;
		Channel(agora::rtc::IChannel* channel);
		~Channel();

		void RegisterChannelEventHandler(AgoraWinRT::ChannelEventHandler const& handler);
		int16_t JoinChannel(hstring const& token, hstring const& info, uint64_t uid, AgoraWinRT::ChannelMediaOptions const& options);
		int16_t JoinChannelWithUserAccount(hstring const& token, hstring const& account, AgoraWinRT::ChannelMediaOptions const& options);
		int16_t LeaveChannel();
		int16_t Publish();
		int16_t Unpublish();
		hstring ChannelId();
		int16_t GetCallId(hstring& callId);
		int16_t renewToken(hstring const& token);
		int16_t SetEncryptionSecret(hstring const& secret);
		int16_t SetEncryptionMode(hstring const& mode);
		int16_t EnableEncryption(bool enabled, AgoraWinRT::EncryptionConfig const& config);
		void RegisterPacketObserver(AgoraWinRT::PacketObserver const& observer);
		void RegisterMediaMetadataObserver(AgoraWinRT::MetadataObserver const& observer);
		int16_t SetClientRole(AgoraWinRT::CLIENT_ROLE_TYPE const& type);
		int16_t SetRemoteUserPriority(uint64_t uid, AgoraWinRT::PRIORITY_TYPE const& priority);
		int16_t SetRemoteVoicePosition(uint64_t uid, float pan, float gain);
		int16_t SetRemoteRenderMode(uint64_t uid, AgoraWinRT::RENDER_MODE_TYPE const& renderMode, AgoraWinRT::VIDEO_MIRROR_MODE_TYPE const& mirrorMode);
		int16_t SetDefaultMuteAllRemoteAudioStreams(bool mute);
		int16_t SetDefaultMuteAllRemoteVideoStreams(bool mute);
		int16_t MuteAllRemoteAudioStreams(bool mute);
		int16_t AdjustUserPlaybackSignalVolume(uint64_t uid, int16_t volume);
		int16_t MuteRemoteAudioStream(uint64_t uid, bool mute);
		int16_t MuteAllRemoteVideoStreams(bool mute);
		int16_t MuteRemoteVideoStream(uint64_t uid, bool mute);
		int16_t SetRemoteVideoStreamType(uint64_t uid, AgoraWinRT::REMOTE_VIDEO_STREAM_TYPE const& type);
		int16_t SetRemoteDefaultVideoStreamType(AgoraWinRT::REMOTE_VIDEO_STREAM_TYPE const& type);
		int16_t CreateDataStream(bool reliable, bool ordered);
		int16_t SendStreamMessage(int64_t streamId, hstring const& data);
		int16_t AddPublishStreamUrl(hstring const& url, bool transcodingEnabled);
		int16_t RemovePublishStreamUrl(hstring const& url);
		int16_t SetLiveTranscoding(AgoraWinRT::LiveTranscoding const& transcoding);
		int16_t AddInjectStreamUrl(hstring const& url, AgoraWinRT::InjectStreamConfig const& config);
		int16_t RemoveInjectStreamUrl(hstring const& url);
		int16_t StartChannelMediaRelay(AgoraWinRT::ChannelMediaRelayConfiguration const& config);
		int16_t UpdateChannelMediaRelay(AgoraWinRT::ChannelMediaRelayConfiguration const& config);
		int16_t StopChannelMediaRelay();
		AgoraWinRT::CONNECTION_STATE_TYPE GetConnectionState();
		void Close();

		int16_t MuteLocalAudioStream(bool mute);
		int16_t MuteLocalVideoStream(bool mute);
	private:
		AgoraWinRT::ChannelEventHandler m_eventHandler{ nullptr };
		agora::rtc::IChannel* m_channel{ nullptr };
		AgoraWinRT::PacketObserver m_packetObserver{ nullptr };
		AgoraWinRT::MetadataObserver m_metadataObserver{ nullptr };

		// 通过 IPacketObserver 继承
		virtual bool onSendAudioPacket(Packet& packet) override;
		virtual bool onSendVideoPacket(Packet& packet) override;
		virtual bool onReceiveAudioPacket(Packet& packet) override;
		virtual bool onReceiveVideoPacket(Packet& packet) override;

		// 通过 IMetadataObserver 继承
		virtual int getMaxMetadataSize() override;
		virtual bool onReadyToSendMetadata(Metadata& metadata) override;
		virtual void onMetadataReceived(const Metadata& metadata) override;

		// 通过 IChannelEventHandler 继承
		virtual void onChannelWarning(agora::rtc::IChannel* rtcChannel, int warn, const char* msg) override;
		virtual void onChannelError(agora::rtc::IChannel* rtcChannel, int err, const char* msg) override;
		virtual void onJoinChannelSuccess(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, int elapsed) override;
		virtual void onRejoinChannelSuccess(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, int elapsed) override;
		virtual void onLeaveChannel(agora::rtc::IChannel* rtcChannel, const agora::rtc::RtcStats& stats) override;
		virtual void onClientRoleChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::CLIENT_ROLE_TYPE oldRole, agora::rtc::CLIENT_ROLE_TYPE newRole) override;
		virtual void onUserJoined(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, int elapsed) override;
		virtual void onUserOffline(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;
		virtual void onConnectionLost(agora::rtc::IChannel* rtcChannel) override;
		virtual void onRequestToken(agora::rtc::IChannel* rtcChannel) override;
		virtual void onTokenPrivilegeWillExpire(agora::rtc::IChannel* rtcChannel, const char* token) override;
		virtual void onRtcStats(agora::rtc::IChannel* rtcChannel, const agora::rtc::RtcStats& stats) override;
		virtual void onNetworkQuality(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, int txQuality, int rxQuality) override;
		virtual void onRemoteVideoStats(agora::rtc::IChannel* rtcChannel, const agora::rtc::RemoteVideoStats& stats) override;
		virtual void onRemoteAudioStats(agora::rtc::IChannel* rtcChannel, const agora::rtc::RemoteAudioStats& stats) override;
		virtual void onRemoteAudioStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, agora::rtc::REMOTE_AUDIO_STATE state, agora::rtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed) override;
		virtual void onAudioPublishStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapsed) override;
		virtual void onVideoPublishStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapsed) override;
		virtual void onAudioSubscribeStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapsed) override;
		virtual void onVideoSubscribeStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapsed) override;
		virtual void onActiveSpeaker(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid) override;
		virtual void onVideoSizeChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, int width, int height, int rotation) override;
		virtual void onRemoteVideoStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, agora::rtc::REMOTE_VIDEO_STATE state, agora::rtc::REMOTE_VIDEO_STATE_REASON reason, int elapsed) override;
		virtual void onStreamMessage(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, int streamId, const char* data, size_t length) override;
		virtual void onStreamMessageError(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, int streamId, int code, int missed, int cached) override;
		virtual void onChannelMediaRelayStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::CHANNEL_MEDIA_RELAY_STATE state, agora::rtc::CHANNEL_MEDIA_RELAY_ERROR code) override;
		virtual void onChannelMediaRelayEvent(agora::rtc::IChannel* rtcChannel, agora::rtc::CHANNEL_MEDIA_RELAY_EVENT code) override;
		virtual void onRtmpStreamingStateChanged(agora::rtc::IChannel* rtcChannel, const char* url, agora::rtc::RTMP_STREAM_PUBLISH_STATE state, agora::rtc::RTMP_STREAM_PUBLISH_ERROR errCode) override;
		virtual void onRtmpStreamingEvent(agora::rtc::IChannel* rtcChannel, const char* url, agora::rtc::RTMP_STREAMING_EVENT eventCode) override;
		virtual void onTranscodingUpdated(agora::rtc::IChannel* rtcChannel) override;
		virtual void onStreamInjectedStatus(agora::rtc::IChannel* rtcChannel, const char* url, agora::rtc::uid_t uid, int status) override;
		virtual void onLocalPublishFallbackToAudioOnly(agora::rtc::IChannel* rtcChannel, bool isFallbackOrRecover) override;
		virtual void onRemoteSubscribeFallbackToAudioOnly(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, bool isFallbackOrRecover) override;
		virtual void onConnectionStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::CONNECTION_STATE_TYPE state, agora::rtc::CONNECTION_CHANGED_REASON_TYPE reason) override;
	};
}
