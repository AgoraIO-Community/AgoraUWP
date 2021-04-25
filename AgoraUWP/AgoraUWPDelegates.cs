using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AgoraWinRT;

namespace AgoraUWP
{
    #region AgoraRtcEventHandler
    public delegate void OnConnectionStateChangedDelegate(CONNECTION_STATE_TYPE type, CONNECTION_CHANGED_REASON_TYPE reason);
    public delegate void OnJoinChannelSuccessDelegate(string channel, ulong uid, uint elapsed);
    public delegate void OnRejoinChannelSuccessDelegate(string channel, ulong uid, uint elapsed);
    public delegate void OnLeaveChannelDelegate(RtcStats stats);
    public delegate void OnClientRoleChangedDelegate(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole);
    public delegate void OnUserJoinedDelegate(ulong uid, uint elapsed);
    public delegate void OnUserOfflineDelegate(ulong uid, USER_OFFLINE_REASON_TYPE reason);
    public delegate void OnNetworkTypeChangedDelegate(NETWORK_TYPE type);
    public delegate void OnConnectionLostDelegate();
    public delegate void OnTokenPrivilegeWillExpireDelegate(string token);
    public delegate void OnRequestTokenDelegate();
    public delegate void OnLocalAudioStateChangedDelegate(LOCAL_AUDIO_STREAM_STATE state, LOCAL_AUDIO_STREAM_ERROR error);
    public delegate void OnLocalVideoStateChangedDelegate(LOCAL_VIDEO_STREAM_STATE state, LOCAL_VIDEO_STREAM_ERROR error);
    public delegate void OnFirstLocalAudioFramePublishedDelegate(uint elapsed);
    public delegate void OnFirstLocalVideoFramePublishedDelegate(uint elapsed);
    public delegate void OnFirstLocalVideoFrameDelegate(uint width, uint height, uint elapsed);
    public delegate void OnAudioPublishStateChangedDelegate(string channel, STREAM_PUBLISH_STATE oldState, STREAM_PUBLISH_STATE newState, uint elapsed);
    public delegate void OnVideoPublishStateChangedDelegate(string channel, STREAM_PUBLISH_STATE oldState, STREAM_PUBLISH_STATE newState, uint elapsed);
    public delegate void OnRemoteAudioStateChangedDelegate(ulong uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, uint elapsed);
    public delegate void OnRemoteVideoStateChangedDelegate(ulong uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, uint elapsed);
    public delegate void OnFirstRemoteVideoFrameDelegate(ulong uid, uint width, uint height, uint elapsed);
    public delegate void OnAudioSubscribeStateChangedDelegate(string channel, ulong uid, STREAM_SUBSCRIBE_STATE oldState, STREAM_SUBSCRIBE_STATE newState, uint elapsed);
    public delegate void OnVideoSubscribeStateChangedDelegate(string channel, ulong uid, STREAM_SUBSCRIBE_STATE oldState, STREAM_SUBSCRIBE_STATE newState, uint elapsed);
    public delegate void OnRtcStatsDelegate(RtcStats stats);
    public delegate void OnNetworkQualityDelegate(ulong uid, QUALITY_TYPE txQuality, QUALITY_TYPE rxQuality);
    public delegate void OnLocalAudioStatsDelegate(LocalAudioStats stats);
    public delegate void OnLocalVideoStatsDelegate(LocalVideoStats stats);
    public delegate void OnRemoteAudioStatsDelegate(RemoteAudioStats stats);
    public delegate void OnRemoteVideoStatsDelegate(RemoteVideoStats stats);
    public delegate void OnAudioMixingStateChangedDelegate(AUDIO_MIXING_STATE_TYPE state, AUDIO_MIXING_REASON_TYPE error);
    public delegate void OnRemoteAudioMixingBeginDelegate();
    public delegate void OnRemoteAudioMixingEndDelegate();
    public delegate void OnAudioEffectFinishedDelegate(ulong soundId);
    public delegate void OnRtmpStreamingStateChangedDelegate(string url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR error);
    public delegate void OnRtmpStreamingEventDelegate(string url, RTMP_STREAMING_EVENT code);
    public delegate void OnTranscodingUpdatedDelegate();
    public delegate void OnChannelMediaRelayStateChangedDelegate(CHANNEL_MEDIA_RELAY_STATE state, CHANNEL_MEDIA_RELAY_ERROR error);
    public delegate void OnChannelMediaRelayEventDelegate(CHANNEL_MEDIA_RELAY_EVENT code);
    public delegate void OnAudioVolumeIndicationDelegate(AudioVolumeInfo[] speakers, byte totalVolume);
    public delegate void OnActiveSpeakerDelegate(ulong uid);
    public delegate void OnLocalPublishFallbackToAudioOnlyDelegate(bool isFallbackOrRecover);
    public delegate void OnRemoteSubscribeFallbackToAudioOnlyDelegate(ulong uid, bool isFallbackOrRecover);
    public delegate void OnLastmileQualityDelegate(QUALITY_TYPE quality);
    public delegate void OnLastmileProbeResultDelegate(LastmileProbeResult result);
    public delegate void OnStreamInjectedStatusDelegate(string url, ulong uid, INJECT_STREAM_STATUS status);
    public delegate void OnStreamMessageDelegate(ulong uid, long streamId, string data);
    public delegate void OnStreamMessageErrorDelegate(ulong uid, long streamId, uint error, ushort missed, ushort cached);
    public delegate void OnWarningDelegate(long code, string msg);
    public delegate void OnErrorDelegate(long code, string msg);
    public delegate void OnApiCallExecutedDelegate(long code, string api, string result);
    public delegate void OnAudioDeviceStateChangedDelegate(string id, MEDIA_DEVICE_TYPE type, MEDIA_DEVICE_STATE_TYPE state);
    public delegate void OnAudioDeviceVolumeChangedDelegate(MEDIA_DEVICE_TYPE type, byte volume, bool muted);
    public delegate void OnVideoDeviceStateChangedDelegate(string id, MEDIA_DEVICE_TYPE type, MEDIA_DEVICE_STATE_TYPE state);
    #endregion AgoraRtcEventHandler

    #region VideoFrameObserver
    public delegate bool OnCaptureVideoFrameDelegate(VideoFrame frame);
    public delegate bool OnPreEncodeVideFrameDelegate(VideoFrame frame);
    public delegate bool OnRenderVideoFrameDelegate(ulong uid, VideoFrame frame);
    public delegate VIDEO_FRAME_TYPE GetVideoFramePreferenceDelegate();
    public delegate bool GetRotationAppliedDelegate();
    public delegate bool GetMirrorAppliedDelegate();
    public delegate bool GetSmoothRenderingEnabledDelegate();
    public delegate uint GetObservedFramePositionDelegate();
    public delegate bool IsMultipleChannelVideoFrameWantedDelegate();
    public delegate bool OnRenderVideoFrameExDelegate(string channel, ulong uid, VideoFrame frame);
    #endregion VideoFrameObserver

    #region AudioFrameObserver
    public delegate bool OnRecordAudioFrameDelegate(AudioFrame frame);
    public delegate bool OnPlaybackAudioFrameDelegate(AudioFrame frame);
    public delegate bool OnMixedAudioFrameDelegate(AudioFrame frame);
    public delegate bool OnPlaybackAudioFrameBeforeMixingDelegate(ulong uid, AudioFrame frame);
    public delegate bool IsMultipleChannelAudioFrameWantedDelegate();
    public delegate bool OnPlaybackAudioFrameBeforeMixingExDelegate(string channel, ulong uid, AudioFrame frame);
    #endregion AudioFrameObserver



}
