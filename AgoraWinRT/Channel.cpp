#include "pch.h"
#include "Channel.h"
#include "Channel.g.cpp"
#include "Utils.h"

namespace winrt::AgoraWinRT::implementation
{
    Channel::Channel(agora::rtc::IChannel* channel) :
        m_channel(channel)
    {
        m_channel->registerMediaMetadataObserver(this, agora::rtc::IMetadataObserver::VIDEO_METADATA);
        m_channel->registerPacketObserver(this);
        m_channel->setChannelEventHandler(this);
    }
    Channel::~Channel()
    {
        Close();
    }
    void Channel::RegisterChannelEventHandler(AgoraWinRT::ChannelEventHandler const& handler)
    {
        m_eventHandler = handler;
    }
    int16_t Channel::JoinChannel(hstring const& token, hstring const& info, uint64_t uid, AgoraWinRT::ChannelMediaOptions const& options)
    {
        return m_channel->joinChannel(Utils::To(token).c_str(), Utils::To(info).c_str(), uid, Utils::To(options));
    }
    int16_t Channel::JoinChannelWithUserAccount(hstring const& token, hstring const& account, AgoraWinRT::ChannelMediaOptions const& options)
    {
        return m_channel->joinChannelWithUserAccount(Utils::To(token).c_str(), Utils::To(account).c_str(), Utils::To(options));
    }
    int16_t Channel::LeaveChannel()
    {
        return m_channel->leaveChannel();
    }
    int16_t Channel::Publish()
    {
        return m_channel->publish();
    }
    int16_t Channel::Unpublish()
    {
        return m_channel->unpublish();
    }
    hstring Channel::ChannelId()
    {
        return Utils::To(m_channel->channelId());
    }
    int16_t Channel::GetCallId(hstring& callId)
    {
        agora::util::AString id;
        auto result = m_channel->getCallId(id);
        callId = Utils::To(id->c_str());
        return result;
    }
    int16_t Channel::renewToken(hstring const& token)
    {
        return m_channel->renewToken(Utils::To(token).c_str());
    }
    int16_t Channel::SetEncryptionSecret(hstring const& secret)
    {
        return m_channel->setEncryptionSecret(Utils::To(secret).c_str());
    }
    int16_t Channel::SetEncryptionMode(hstring const& mode)
    {
        return m_channel->setEncryptionMode(Utils::To(mode).c_str());
    }
    int16_t Channel::EnableEncryption(bool enabled, AgoraWinRT::EncryptionConfig const& config)
    {
        return m_channel->enableEncryption(enabled, Utils::To(config));
    }
    void Channel::RegisterPacketObserver(AgoraWinRT::PacketObserver const& observer)
    {
        m_packetObserver = observer;
    }
    void Channel::RegisterMediaMetadataObserver(AgoraWinRT::MetadataObserver const& observer)
    {
        m_metadataObserver = observer;
    }
    int16_t Channel::SetClientRole(AgoraWinRT::CLIENT_ROLE_TYPE const& type)
    {
        return m_channel->setClientRole((agora::rtc::CLIENT_ROLE_TYPE)type);
    }
    int16_t Channel::SetRemoteUserPriority(uint64_t uid, AgoraWinRT::PRIORITY_TYPE const& priority)
    {
        return m_channel->setRemoteUserPriority(uid, (agora::rtc::PRIORITY_TYPE)priority);
    }
    int16_t Channel::SetRemoteVoicePosition(uint64_t uid, float pan, float gain)
    {
        return m_channel->setRemoteVoicePosition(uid, pan, gain);
    }
    int16_t Channel::SetRemoteRenderMode(uint64_t uid, AgoraWinRT::RENDER_MODE_TYPE const& renderMode, AgoraWinRT::VIDEO_MIRROR_MODE_TYPE const& mirrorMode)
    {
        return m_channel->setRemoteRenderMode(uid, (agora::rtc::RENDER_MODE_TYPE)renderMode, (agora::rtc::VIDEO_MIRROR_MODE_TYPE)mirrorMode);
    }
    int16_t Channel::SetDefaultMuteAllRemoteAudioStreams(bool mute)
    {
        return m_channel->setDefaultMuteAllRemoteAudioStreams(mute);
    }
    int16_t Channel::SetDefaultMuteAllRemoteVideoStreams(bool mute)
    {
        return m_channel->setDefaultMuteAllRemoteVideoStreams(mute);
    }
    int16_t Channel::MuteAllRemoteAudioStreams(bool mute)
    {
        return m_channel->muteAllRemoteAudioStreams(mute);
    }
    int16_t Channel::AdjustUserPlaybackSignalVolume(uint64_t uid, int16_t volume)
    {
        return m_channel->adjustUserPlaybackSignalVolume(uid, volume);
    }
    int16_t Channel::MuteRemoteAudioStream(uint64_t uid, bool mute)
    {
        return m_channel->muteRemoteAudioStream(uid, mute);
    }
    int16_t Channel::MuteAllRemoteVideoStreams(bool mute)
    {
        return m_channel->muteAllRemoteVideoStreams(mute);
    }
    int16_t Channel::MuteRemoteVideoStream(uint64_t uid, bool mute)
    {
        return m_channel->muteRemoteVideoStream(uid, mute);
    }
    int16_t Channel::SetRemoteVideoStreamType(uint64_t uid, AgoraWinRT::REMOTE_VIDEO_STREAM_TYPE const& type)
    {
        return m_channel->setRemoteVideoStreamType(uid, (agora::rtc::REMOTE_VIDEO_STREAM_TYPE)type);
    }
    int16_t Channel::SetRemoteDefaultVideoStreamType(AgoraWinRT::REMOTE_VIDEO_STREAM_TYPE const& type)
    {
        return m_channel->setRemoteDefaultVideoStreamType((agora::rtc::REMOTE_VIDEO_STREAM_TYPE)type);
    }
    int16_t Channel::CreateDataStream(bool reliable, bool ordered)
    {
        int streamId;
        auto result = m_channel->createDataStream(&streamId, reliable, ordered);
        return result == 0 ? streamId : result;
    }
    int16_t Channel::SendStreamMessage(int64_t streamId, hstring const& data)
    {
        auto msg = Utils::To(data);
        return m_channel->sendStreamMessage(streamId, msg.c_str(), msg.size());
    }
    int16_t Channel::AddPublishStreamUrl(hstring const& url, bool transcodingEnabled)
    {
        return m_channel->addPublishStreamUrl(Utils::To(url).c_str(), transcodingEnabled);
    }
    int16_t Channel::RemovePublishStreamUrl(hstring const& url)
    {
        return m_channel->removePublishStreamUrl(Utils::To(url).c_str());
    }
    int16_t Channel::SetLiveTranscoding(AgoraWinRT::LiveTranscoding const& transcoding)
    {
        return m_channel->setLiveTranscoding(Utils::To(transcoding));
    }
    int16_t Channel::AddInjectStreamUrl(hstring const& url, AgoraWinRT::InjectStreamConfig const& config)
    {
        return m_channel->addInjectStreamUrl(Utils::To(url).c_str(), Utils::To(config));
    }
    int16_t Channel::RemoveInjectStreamUrl(hstring const& url)
    {
        return m_channel->removeInjectStreamUrl(Utils::To(url).c_str());
    }
    int16_t Channel::StartChannelMediaRelay(AgoraWinRT::ChannelMediaRelayConfiguration const& config)
    {
        return m_channel->startChannelMediaRelay(Utils::To(config));
    }
    int16_t Channel::UpdateChannelMediaRelay(AgoraWinRT::ChannelMediaRelayConfiguration const& config)
    {
        return m_channel->updateChannelMediaRelay(Utils::To(config));
    }
    int16_t Channel::StopChannelMediaRelay()
    {
        return m_channel->stopChannelMediaRelay();
    }
    AgoraWinRT::CONNECTION_STATE_TYPE Channel::GetConnectionState()
    {
        return (AgoraWinRT::CONNECTION_STATE_TYPE)(m_channel->getConnectionState());
    }
    void Channel::Close()
    {
        if (m_channel) m_channel->release();
    }
    bool Channel::onSendAudioPacket(Packet& packet)
    {
        if (m_packetObserver) {
            auto data = Utils::To(packet);
            return m_packetObserver.OnSendAudioPacket(*data);
        }
        else return true;
    }
    bool Channel::onSendVideoPacket(Packet& packet)
    {
        if (m_packetObserver) {
            auto data = Utils::To(packet);
            return m_packetObserver.OnSendVideoPacket(*data);
        }
        else return true;
    }
    bool Channel::onReceiveAudioPacket(Packet& packet)
    {
        if (m_packetObserver) {
            auto data = Utils::To(packet);
            return m_packetObserver.OnReceiveAudioPacket(*data);
        }
        else return true;
    }
    bool Channel::onReceiveVideoPacket(Packet& packet)
    {
        if (m_packetObserver) {
            auto data = Utils::To(packet);
            return m_packetObserver.OnReceiveVideoPacket(*data);
        }
        else return true;
    }
    int Channel::getMaxMetadataSize()
    {
        if (m_metadataObserver) return m_metadataObserver.GetMaxMetadataSize();
        else return 1024;
    }
    bool Channel::onReadyToSendMetadata(Metadata& metadata)
    {
        auto data = Utils::To(metadata);
        if (m_metadataObserver) return m_metadataObserver.OnReadyToSendMetadata(*data);
        else return true;
    }
    void Channel::onMetadataReceived(const Metadata& metadata)
    {
        auto data = Utils::To(metadata);
        if (m_metadataObserver) m_metadataObserver.OnMetadataReceived(*data);
    }
    void Channel::onChannelWarning(agora::rtc::IChannel* rtcChannel, int warn, const char* msg)
    {
        if (m_eventHandler) m_eventHandler.OnChannelWarning(*this, warn, Utils::To(msg));
    }
    void Channel::onChannelError(agora::rtc::IChannel* rtcChannel, int err, const char* msg)
    {
        if (m_eventHandler) m_eventHandler.OnChannelError(*this, err, Utils::To(msg));
    }
    void Channel::onJoinChannelSuccess(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, int elapsed)
    {
        if (m_eventHandler) m_eventHandler.OnJoinChannelSuccess(*this, uid, elapsed);
    }
    void Channel::onRejoinChannelSuccess(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, int elapsed)
    {
        if (m_eventHandler) m_eventHandler.OnRejoinChannelSuccess(*this, uid, elapsed);
    }
    void Channel::onLeaveChannel(agora::rtc::IChannel* rtcChannel, const agora::rtc::RtcStats& stats)
    {
        if (m_eventHandler) m_eventHandler.OnLeaveChannel(*this, Utils::To(stats));
    }
    void Channel::onClientRoleChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::CLIENT_ROLE_TYPE oldRole, agora::rtc::CLIENT_ROLE_TYPE newRole)
    {
        if (m_eventHandler) m_eventHandler.OnClientRoleChanged(*this, (AgoraWinRT::CLIENT_ROLE_TYPE)oldRole, (AgoraWinRT::CLIENT_ROLE_TYPE)newRole);
    }
    void Channel::onUserJoined(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, int elapsed)
    {
        if (m_eventHandler) m_eventHandler.OnUserJoined(*this, uid, elapsed);
    }
    void Channel::onUserOffline(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
    {
        if (m_eventHandler) m_eventHandler.OnUserOffline(*this, uid, (AgoraWinRT::USER_OFFLINE_REASON_TYPE)reason);
    }
    void Channel::onConnectionLost(agora::rtc::IChannel* rtcChannel)
    {
        if (m_eventHandler) m_eventHandler.OnConnectionLost(*this);
    }
    void Channel::onRequestToken(agora::rtc::IChannel* rtcChannel)
    {
        if (m_eventHandler) m_eventHandler.OnRequestToken(*this);
    }
    void Channel::onTokenPrivilegeWillExpire(agora::rtc::IChannel* rtcChannel, const char* token)
    {
        if (m_eventHandler) m_eventHandler.OnTokenPrivilegeWillExpire(*this, Utils::To(token));
    }
    void Channel::onRtcStats(agora::rtc::IChannel* rtcChannel, const agora::rtc::RtcStats& stats)
    {
        if (m_eventHandler) m_eventHandler.OnRtcStats(*this, Utils::To(stats));
    }
    void Channel::onNetworkQuality(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, int txQuality, int rxQuality)
    {
        if (m_eventHandler) m_eventHandler.OnNetworkQuality(*this, uid, (AgoraWinRT::QUALITY_TYPE)txQuality, (AgoraWinRT::QUALITY_TYPE)rxQuality);
    }
    void Channel::onRemoteVideoStats(agora::rtc::IChannel* rtcChannel, const agora::rtc::RemoteVideoStats& stats)
    {
        if (m_eventHandler) m_eventHandler.OnRemoteVideoStats(*this, Utils::To(stats));
    }
    void Channel::onRemoteAudioStats(agora::rtc::IChannel* rtcChannel, const agora::rtc::RemoteAudioStats& stats)
    {
        if (m_eventHandler) m_eventHandler.OnRemoteAudioStats(*this, Utils::To(stats));
    }
    void Channel::onRemoteAudioStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, agora::rtc::REMOTE_AUDIO_STATE state, agora::rtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed)
    {
        if (m_eventHandler) m_eventHandler.OnRemoteAudioStateChanged(*this, uid, (AgoraWinRT::REMOTE_AUDIO_STATE)state, (AgoraWinRT::REMOTE_AUDIO_STATE_REASON)reason, elapsed);
    }
    void Channel::onAudioPublishStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapsed)
    {
        if (m_eventHandler) m_eventHandler.OnAudioPublishStateChanged(*this, (AgoraWinRT::STREAM_PUBLISH_STATE)oldState, (AgoraWinRT::STREAM_PUBLISH_STATE)newState, elapsed);
    }
    void Channel::onVideoPublishStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapsed)
    {
        if (m_eventHandler) m_eventHandler.OnVideoPublishStateChanged(*this, (AgoraWinRT::STREAM_PUBLISH_STATE)oldState, (AgoraWinRT::STREAM_PUBLISH_STATE)newState, elapsed);
    }
    void Channel::onAudioSubscribeStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapsed)
    {
        if (m_eventHandler) m_eventHandler.OnAudioSubscribeStateChanged(*this, uid, (AgoraWinRT::STREAM_SUBSCRIBE_STATE)oldState, (AgoraWinRT::STREAM_SUBSCRIBE_STATE)newState, elapsed);
    }
    void Channel::onVideoSubscribeStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapsed)
    {
        if (m_eventHandler) m_eventHandler.OnVideoSubscribeStateChanged(*this, uid, (AgoraWinRT::STREAM_SUBSCRIBE_STATE)oldState, (AgoraWinRT::STREAM_SUBSCRIBE_STATE)newState, elapsed);
    }
    void Channel::onActiveSpeaker(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid)
    {
        if (m_eventHandler) m_eventHandler.OnActiveSpeake(*this, uid);
    }
    void Channel::onVideoSizeChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, int width, int height, int rotation)
    {
        if (m_eventHandler) m_eventHandler.OnVideoSizeChanged(*this, uid, width, height, rotation);
    }
    void Channel::onRemoteVideoStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, agora::rtc::REMOTE_VIDEO_STATE state, agora::rtc::REMOTE_VIDEO_STATE_REASON reason, int elapsed)
    {
        if (m_eventHandler) m_eventHandler.OnRemoteVideoStateChanged(*this, uid, (AgoraWinRT::REMOTE_VIDEO_STATE)state, (AgoraWinRT::REMOTE_VIDEO_STATE_REASON)reason, elapsed);
    }
    void Channel::onStreamMessage(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, int streamId, const char* data, size_t length)
    {
        if (m_eventHandler) m_eventHandler.OnStreamMessage(*this, uid, streamId, Utils::To(data, length));
    }
    void Channel::onStreamMessageError(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, int streamId, int code, int missed, int cached)
    {
        if (m_eventHandler) m_eventHandler.OnStreamMessageError(*this, uid, streamId, code, missed, cached);
    }
    void Channel::onChannelMediaRelayStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::CHANNEL_MEDIA_RELAY_STATE state, agora::rtc::CHANNEL_MEDIA_RELAY_ERROR code)
    {
        if (m_eventHandler) m_eventHandler.OnChannelMediaRelayStateChanged(*this, (AgoraWinRT::CHANNEL_MEDIA_RELAY_STATE)state, (AgoraWinRT::CHANNEL_MEDIA_RELAY_ERROR)code);
    }
    void Channel::onChannelMediaRelayEvent(agora::rtc::IChannel* rtcChannel, agora::rtc::CHANNEL_MEDIA_RELAY_EVENT code)
    {
        if (m_eventHandler) m_eventHandler.OnChannelMediaRelayEvent(*this, (AgoraWinRT::CHANNEL_MEDIA_RELAY_EVENT)code);
    }
    void Channel::onRtmpStreamingStateChanged(agora::rtc::IChannel* rtcChannel, const char* url, agora::rtc::RTMP_STREAM_PUBLISH_STATE state, agora::rtc::RTMP_STREAM_PUBLISH_ERROR errCode)
    {
        if (m_eventHandler) m_eventHandler.OnRtmpStreamingStateChanged(*this, Utils::To(url), (AgoraWinRT::RTMP_STREAM_PUBLISH_STATE)state, (AgoraWinRT::RTMP_STREAM_PUBLISH_ERROR)errCode);
    }
    void Channel::onRtmpStreamingEvent(agora::rtc::IChannel* rtcChannel, const char* url, agora::rtc::RTMP_STREAMING_EVENT eventCode)
    {
        if (m_eventHandler) m_eventHandler.OnRtmpStreamingEvent(*this, Utils::To(url), (AgoraWinRT::RTMP_STREAMING_EVENT)eventCode);
    }
    void Channel::onTranscodingUpdated(agora::rtc::IChannel* rtcChannel)
    {
        if (m_eventHandler) m_eventHandler.OnTranscodingUpdated(*this);
    }
    void Channel::onStreamInjectedStatus(agora::rtc::IChannel* rtcChannel, const char* url, agora::rtc::uid_t uid, int status)
    {
        if (m_eventHandler) m_eventHandler.OnStreamInjectedStatus(*this, Utils::To(url), uid, (AgoraWinRT::INJECT_STREAM_STATUS)status);
    }
    void Channel::onLocalPublishFallbackToAudioOnly(agora::rtc::IChannel* rtcChannel, bool isFallbackOrRecover)
    {
        if (m_eventHandler) m_eventHandler.OnLocalPublishFallbackToAudioOnly(*this, isFallbackOrRecover);
    }
    void Channel::onRemoteSubscribeFallbackToAudioOnly(agora::rtc::IChannel* rtcChannel, agora::rtc::uid_t uid, bool isFallbackOrRecover)
    {
        if (m_eventHandler) m_eventHandler.OnRemoteSubscribeFallbackToAudioOnly(*this, uid, isFallbackOrRecover);
    }
    void Channel::onConnectionStateChanged(agora::rtc::IChannel* rtcChannel, agora::rtc::CONNECTION_STATE_TYPE state, agora::rtc::CONNECTION_CHANGED_REASON_TYPE reason)
    {
        if (m_eventHandler) m_eventHandler.OnConnectionStateChanged(*this, (AgoraWinRT::CONNECTION_STATE_TYPE)state, (AgoraWinRT::CONNECTION_CHANGED_REASON_TYPE)reason);
    }
}
