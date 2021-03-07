using AgoraWinRT;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.Foundation;
using Windows.Media.Capture;
using Windows.Media.Capture.Frames;
using Windows.Media.MediaProperties;
using Windows.Security.Authentication.Identity.Core;
using Windows.Security.Cryptography.Core;
using Windows.UI.Notifications;
using Windows.UI.Xaml.Media;
 
namespace AgoraUWP
{
    public class AgoraRtc : AgoraWinRT.AgoraRtc,
        AgoraWinRT.AgoraRtcEventHandler,
        AgoraWinRT.VideoFrameObserver,
        AgoraWinRT.AudioFrameObserver
    {
        private VideoCanvas localVideo = null;
        private bool previewing = false;
        private DateTime? firstLocalVideoFrameElapsed = null;
        private bool joinChanneled = false;
        private Dictionary<ulong, VideoCanvas> remoteVideos = new Dictionary<ulong, VideoCanvas>();
        private DateTime? firstRemoteVideoFrameElapsed = null;
        private IMediaCapturer defaultMediaCapturer;
        private bool useExternalVideoSoruce;
        private VideoCanvas testVideoCanvas;
        private bool videoTesting = false;
        private DeviceWatcher videoDeviceWatcher;

        /// <summary>
        /// 得到Camera的使用权限
        /// </summary>
        public static async void RequestCameraAccess()
        {
            var mediaCapture = new MediaCapture();
            await mediaCapture.InitializeAsync();
        }

        public AgoraRtc(string vendorKey) : base(vendorKey)
        {
            base.RegisterRtcEngineEventHandler(this);
            base.RegisterVideoFrameObserver(this);
            base.RegisterAudioFrameObserver(this);

            InitDefaultCapture();
            InitVideoDeviceWatcher();
        }

        private void InitVideoDeviceWatcher()
        {
            videoDeviceWatcher = DeviceInformation.CreateWatcher(DeviceClass.VideoCapture);
            videoDeviceWatcher.Removed += (watcher, info) =>
            {
                OnVideoDeviceStateChanged?.Invoke(info.Id, MEDIA_DEVICE_TYPE.VIDEO_CAPTURE_DEVICE, MEDIA_DEVICE_STATE_TYPE.MEDIA_DEVICE_STATE_UNPLUGGED);
            };
            videoDeviceWatcher.Updated += (watcher, update) =>
            {
                if (update.Properties.TryGetValue("System.Devices.Connected", out object connected))
                {
                    OnVideoDeviceStateChanged?.Invoke(update.Id, MEDIA_DEVICE_TYPE.VIDEO_CAPTURE_DEVICE, (bool)connected ? MEDIA_DEVICE_STATE_TYPE.MEDIA_DEVICE_STATE_ACTIVE : MEDIA_DEVICE_STATE_TYPE.MEDIA_DEVICE_STATE_DISABLED);
                }
                if (update.Properties.TryGetValue("System.Devices.InterfaceEnabled", out object enabled))
                {
                    OnVideoDeviceStateChanged?.Invoke(update.Id, MEDIA_DEVICE_TYPE.VIDEO_CAPTURE_DEVICE, (bool)enabled ? MEDIA_DEVICE_STATE_TYPE.MEDIA_DEVICE_STATE_ACTIVE : MEDIA_DEVICE_STATE_TYPE.MEDIA_DEVICE_STATE_DISABLED);
                }
            };
            videoDeviceWatcher.Start();
        }

        private void InitDefaultCapture()
        {
            var sourceGroup = MediaFrameSourceGroup.FindAllAsync().AsTask().GetAwaiter().GetResult();
            if (sourceGroup.Count == 0) return;
            InitVideoCapture(sourceGroup[0]);
        }
        private void InitVideoCapture(MediaFrameSourceGroup group)
        {
            defaultMediaCapturer?.Dispose();
            defaultMediaCapturer = new GeneralMediaCapturer(group, StreamingCaptureMode.Video);
            defaultMediaCapturer.OnVideoFrameArrived += VideoFrameArrivedEvent;
            base.SetExternalVideoSource(true, false);
        }
        private void InitVideoCapture(DeviceInformation device)
        {
            defaultMediaCapturer?.Dispose();
            defaultMediaCapturer = new GeneralMediaCapturer(device, StreamingCaptureMode.Video);
            defaultMediaCapturer.OnVideoFrameArrived += VideoFrameArrivedEvent;
            base.SetExternalVideoSource(true, false);
        }
        internal DeviceInformation CurrentVideoDevice
        {
            get
            {
                return defaultMediaCapturer?.VideoDevice;
            }
            set
            {
                if (value == null || value.Id.Equals(CurrentVideoDevice?.Id)) return;
                InitVideoCapture(value);
            }
        }
        internal void StartVideoTest(VideoCanvas canvas)
        {
            testVideoCanvas = canvas;
            videoTesting = true;
        }
        internal void StopVideoTest()
        {
            testVideoCanvas = null;
            videoTesting = false;
        }
        private void VideoFrameArrivedEvent(MediaFrameReference frame)
        {
            if (frame == null) return;

            using (frame)
            {
                var buffer = frame.BufferMediaFrame;
                if (buffer == null) return;
                var format = frame.VideoMediaFrame?.VideoFormat;
                if (format == null) return;
                using (var externalFrame = new ExternalVideoFrame())
                {
                    externalFrame.format = defaultMediaCapturer.VideoFormat;
                    externalFrame.type = defaultMediaCapturer.VideoBufferType;
                    externalFrame.stride = format.Width;
                    externalFrame.height = format.Height;
                    externalFrame.buffer = buffer.Buffer.ToArray();
                    PushVideoFrame(externalFrame);
                }
                if (this.previewing || this.joinChanneled) this.localVideo?.Render(frame);
                if (this.videoTesting) this.testVideoCanvas?.Render(frame);
            }
        }

        public new void Dispose()
        {
            videoDeviceWatcher?.Stop();
            videoTesting = false;
            defaultMediaCapturer?.Dispose();
            base.Dispose();
        }

        public new short SetExternalVideoSource(bool enabled, bool useTexture)
        {
            useExternalVideoSoruce = enabled;
            defaultMediaCapturer.EnableVideo(!enabled);
            return 0;
        }

        public new short JoinChannel(string token, string channel, string info, ulong uid)
        {
            if (!this.firstLocalVideoFrameElapsed.HasValue) this.firstLocalVideoFrameElapsed = DateTime.Now;
            this.firstRemoteVideoFrameElapsed = DateTime.Now;

            return base.JoinChannel(token, channel, info, uid);
        }

        public new short EnableVideo()
        {
            var result = base.EnableVideo();
            EnableLocalVideo(true);
            return result;
        }

        public new short DisableVideo()
        {
            EnableLocalVideo(false);
            return base.DisableVideo();
        }

        public void EnableLocalVideo(bool enabled)
        {
            if (!useExternalVideoSoruce)
                defaultMediaCapturer.EnableVideo(enabled);
        }

        public void SetupLocalVideo(VideoCanvas videoCanvas)
        {
            this.localVideo = videoCanvas;
        }
        public void SetupRemoteVideo(VideoCanvas videoCanvas)
        {
            this.remoteVideos[videoCanvas.User] = videoCanvas;
        }
        public void SetLocalRenderMode(RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode)
        {
            localVideo.RenderMode = renderMode;
            localVideo.MirrorMode = mirrorMode;
        }
        public void SetRemoteRenderMode(ulong uid, RENDER_MODE_TYPE renderMode, VIDEO_MIRROR_MODE_TYPE mirrorMode)
        {
            if (this.remoteVideos.TryGetValue(uid, out var videoCanvas))
            {
                videoCanvas.RenderMode = renderMode;
                videoCanvas.MirrorMode = mirrorMode;
            }
        }
        public void StartPreview()
        {
            this.previewing = true;
            if (!this.firstLocalVideoFrameElapsed.HasValue) this.firstLocalVideoFrameElapsed = DateTime.Now;
        }

        public void StopPreview()
        {
            this.previewing = false;
        }

        public IVideoDeviceManager GetVideoDeviceManager()
        {
            return new VideoDeviceManager(this);
        }

        #region AgoraRtcEventHandler

        public event OnConnectionStateChangedDelegate OnConnectionStateChanged;
        public event OnJoinChannelSuccessDelegate OnJoinChannelSuccess;
        public event OnRejoinChannelSuccessDelegate OnRejoinChannelSuccess;
        public event OnLeaveChannelDelegate OnLeaveChannel;
        public event OnClientRoleChangedDelegate OnClientRoleChanged;
        public event OnUserJoinedDelegate OnUserJoined;
        public event OnUserOfflineDelegate OnUserOffline;
        public event OnNetworkTypeChangedDelegate OnNetworkTypeChanged;
        public event OnConnectionLostDelegate OnConnectionLost;
        public event OnTokenPrivilegeWillExpireDelegate OnTokenPrivilegeWillExpire;
        public event OnRequestTokenDelegate OnRequestToken;
        public event OnLocalAudioStateChangedDelegate OnLocalAudioStateChanged;
        public event OnLocalVideoStateChangedDelegate OnLocalVideoStateChanged;
        public event OnFirstLocalAudioFramePublishedDelegate OnFirstLocalAudioFramePublished;
        public event OnFirstLocalVideoFramePublishedDelegate OnFirstLocalVideoFramePublished;
        public event OnFirstLocalVideoFrameDelegate OnFirstLocalVideoFrame;
        public event OnAudioPublishStateChangedDelegate OnAudioPublishStateChanged;
        public event OnVideoPublishStateChangedDelegate OnVideoPublishStateChanged;
        public event OnRemoteAudioStateChangedDelegate OnRemoteAudioStateChanged;
        public event OnRemoteVideoStateChangedDelegate OnRemoteVideoStateChanged;
        public event OnFirstRemoteVideoFrameDelegate OnFirstRemoteVideoFrame;
        public event OnAudioSubscribeStateChangedDelegate OnAudioSubscribeStateChanged;
        public event OnVideoSubscribeStateChangedDelegate OnVideoSubscribeStateChanged;
        public event OnRtcStatsDelegate OnRtcStats;
        public event OnNetworkQualityDelegate OnNetworkQuality;
        public event OnLocalAudioStatsDelegate OnLocalAudioStats;
        public event OnLocalVideoStatsDelegate OnLocalVideoStats;
        public event OnRemoteAudioStatsDelegate OnRemoteAudioStats;
        public event OnRemoteVideoStatsDelegate OnRemoteVideoStats;
        public event OnAudioMixingStateChangedDelegate OnAudioMixingStateChanged;
        public event OnRemoteAudioMixingBeginDelegate OnRemoteAudioMixingBegin;
        public event OnRemoteAudioMixingEndDelegate OnRemoteAudioMixingEnd;
        public event OnAudioEffectFinishedDelegate OnAudioEffectFinished;
        public event OnRtmpStreamingStateChangedDelegate OnRtmpStreamingStateChanged;
        public event OnRtmpStreamingEventDelegate OnRtmpStreamingEvent;
        public event OnTranscodingUpdatedDelegate OnTranscodingUpdated;
        public event OnChannelMediaRelayStateChangedDelegate OnChannelMediaRelayStateChanged;
        public event OnChannelMediaRelayEventDelegate OnChannelMediaRelayEvent;
        public event OnAudioVolumeIndicationDelegate OnAudioVolumeIndication;
        public event OnActiveSpeakerDelegate OnActiveSpeaker;
        public event OnLocalPublishFallbackToAudioOnlyDelegate OnLocalPublishFallbackToAudioOnly;
        public event OnRemoteSubscribeFallbackToAudioOnlyDelegate OnRemoteSubscribeFallbackToAudioOnly;
        public event OnLastmileQualityDelegate OnLastmileQuality;
        public event OnLastmileProbeResultDelegate OnLastmileProbeResult;
        public event OnStreamInjectedStatusDelegate OnStreamInjectedStatus;
        public event OnStreamMessageDelegate OnStreamMessage;
        public event OnStreamMessageErrorDelegate OnStreamMessageError;
        public event OnWarningDelegate OnWarning;
        public event OnErrorDelegate OnError;
        public event OnApiCallExecutedDelegate OnApiCallExecuted;
        public event OnAudioDeviceStateChangedDelegate OnAudioDeviceStateChanged;
        public event OnAudioDeviceVolumeChangedDelegate OnAudioDeviceVolumeChanged;
        public event OnVideoDeviceStateChangedDelegate OnVideoDeviceStateChanged;

        void AgoraRtcEventHandler.OnConnectionStateChanged(CONNECTION_STATE_TYPE type, CONNECTION_CHANGED_REASON_TYPE reason)
        {
            OnConnectionStateChanged?.Invoke(type, reason);
        }

        void AgoraRtcEventHandler.OnJoinChannelSuccess(string channel, ulong uid, uint elapsed)
        {
            this.joinChanneled = true;
            OnJoinChannelSuccess?.Invoke(channel, uid, elapsed);
        }

        void AgoraRtcEventHandler.OnRejoinChannelSuccess(string channel, ulong uid, uint elapsed)
        {
            this.joinChanneled = true;
            OnRejoinChannelSuccess?.Invoke(channel, uid, elapsed);
        }

        void AgoraRtcEventHandler.OnLeaveChannel(RtcStats stats)
        {
            this.joinChanneled = false;
            OnLeaveChannel?.Invoke(stats);
        }

        void AgoraRtcEventHandler.OnClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole)
        {
            OnClientRoleChanged?.Invoke(oldRole, newRole);
        }

        void AgoraRtcEventHandler.OnUserJoined(ulong uid, uint elapsed)
        {
            OnUserJoined?.Invoke(uid, elapsed);
        }

        void AgoraRtcEventHandler.OnUserOffline(ulong uid, USER_OFFLINE_REASON_TYPE reason)
        {
            OnUserOffline?.Invoke(uid, reason);
        }

        void AgoraRtcEventHandler.OnNetworkTypeChanged(NETWORK_TYPE type)
        {
            OnNetworkTypeChanged?.Invoke(type);
        }

        void AgoraRtcEventHandler.OnConnectionLost()
        {
            OnConnectionLost?.Invoke();
        }

        void AgoraRtcEventHandler.OnTokenPrivilegeWillExpire(string token)
        {
            OnTokenPrivilegeWillExpire?.Invoke(token);
        }

        void AgoraRtcEventHandler.OnRequestToken()
        {
            OnRequestToken?.Invoke();
        }

        void AgoraRtcEventHandler.OnLocalAudioStateChanged(LOCAL_AUDIO_STREAM_STATE state, LOCAL_AUDIO_STREAM_ERROR error)
        {
            OnLocalAudioStateChanged?.Invoke(state, error);
        }

        void AgoraRtcEventHandler.OnLocalVideoStateChanged(LOCAL_VIDEO_STREAM_STATE state, LOCAL_VIDEO_STREAM_ERROR error)
        {
            OnLocalVideoStateChanged?.Invoke(state, error);
        }

        void AgoraRtcEventHandler.OnFirstLocalAudioFramePublished(uint elapsed)
        {
            OnFirstLocalAudioFramePublished?.Invoke(elapsed);
        }

        void AgoraRtcEventHandler.OnFirstLocalVideoFramePublished(uint elapsed)
        {
            OnFirstLocalVideoFramePublished?.Invoke(elapsed);
        }

        void AgoraRtcEventHandler.OnFirstLocalVideoFrame(uint width, uint height, uint elapsed)
        {
            OnFirstLocalVideoFrame?.Invoke(width, height, elapsed);
        }

        void AgoraRtcEventHandler.OnAudioPublishStateChanged(string channel, STREAM_PUBLISH_STATE oldState, STREAM_PUBLISH_STATE newState, uint elapsed)
        {
            OnAudioPublishStateChanged?.Invoke(channel, oldState, newState, elapsed);
        }

        void AgoraRtcEventHandler.OnVideoPublishStateChanged(string channel, STREAM_PUBLISH_STATE oldState, STREAM_PUBLISH_STATE newState, uint elapsed)
        {
            OnVideoPublishStateChanged?.Invoke(channel, oldState, newState, elapsed);
        }

        void AgoraRtcEventHandler.OnRemoteAudioStateChanged(ulong uid, REMOTE_AUDIO_STATE state, REMOTE_AUDIO_STATE_REASON reason, uint elapsed)
        {
            OnRemoteAudioStateChanged?.Invoke(uid, state, reason, elapsed);
        }

        void AgoraRtcEventHandler.OnRemoteVideoStateChanged(ulong uid, REMOTE_VIDEO_STATE state, REMOTE_VIDEO_STATE_REASON reason, uint elapsed)
        {
            OnRemoteVideoStateChanged?.Invoke(uid, state, reason, elapsed);
        }

        void AgoraRtcEventHandler.OnFirstRemoteVideoFrame(ulong uid, uint width, uint height, uint elapsed)
        {
            OnFirstRemoteVideoFrame?.Invoke(uid, width, height, elapsed);
        }

        void AgoraRtcEventHandler.OnAudioSubscribeStateChanged(string channel, ulong uid, STREAM_SUBSCRIBE_STATE oldState, STREAM_SUBSCRIBE_STATE newState, uint elapsed)
        {
            OnAudioSubscribeStateChanged?.Invoke(channel, uid, oldState, newState, elapsed);
        }

        void AgoraRtcEventHandler.OnVideoSubscribeStateChanged(string channel, ulong uid, STREAM_SUBSCRIBE_STATE oldState, STREAM_SUBSCRIBE_STATE newState, uint elapsed)
        {
            OnVideoSubscribeStateChanged?.Invoke(channel, uid, oldState, newState, elapsed);
        }

        void AgoraRtcEventHandler.OnRtcStats(RtcStats stats)
        {
            OnRtcStats?.Invoke(stats);
        }

        void AgoraRtcEventHandler.OnNetworkQuality(ulong uid, QUALITY_TYPE txQuality, QUALITY_TYPE rxQuality)
        {
            OnNetworkQuality?.Invoke(uid, txQuality, rxQuality);
        }

        void AgoraRtcEventHandler.OnLocalAudioStats(LocalAudioStats stats)
        {
            OnLocalAudioStats?.Invoke(stats);
        }

        void AgoraRtcEventHandler.OnLocalVideoStats(LocalVideoStats stats)
        {
            OnLocalVideoStats?.Invoke(stats);
        }

        void AgoraRtcEventHandler.OnRemoteAudioStats(RemoteAudioStats stats)
        {
            OnRemoteAudioStats?.Invoke(stats);
        }

        void AgoraRtcEventHandler.OnRemoteVideoStats(RemoteVideoStats stats)
        {
            OnRemoteVideoStats?.Invoke(stats);
        }

        void AgoraRtcEventHandler.OnAudioMixingStateChanged(AUDIO_MIXING_STATE_TYPE state, AUDIO_MIXING_ERROR_TYPE error)
        {
            OnAudioMixingStateChanged?.Invoke(state, error);
        }

        void AgoraRtcEventHandler.OnRemoteAudioMixingBegin()
        {
            OnRemoteAudioMixingBegin?.Invoke();
        }

        void AgoraRtcEventHandler.OnRemoteAudioMixingEnd()
        {
            OnRemoteAudioMixingEnd?.Invoke();
        }

        void AgoraRtcEventHandler.OnAudioEffectFinished(ulong soundId)
        {
            OnAudioEffectFinished?.Invoke(soundId);
        }

        void AgoraRtcEventHandler.OnRtmpStreamingStateChanged(string url, RTMP_STREAM_PUBLISH_STATE state, RTMP_STREAM_PUBLISH_ERROR error)
        {
            OnRtmpStreamingStateChanged?.Invoke(url, state, error);
        }

        void AgoraRtcEventHandler.OnRtmpStreamingEvent(string url, RTMP_STREAMING_EVENT code)
        {
            OnRtmpStreamingEvent?.Invoke(url, code);
        }

        void AgoraRtcEventHandler.OnTranscodingUpdated()
        {
            OnTranscodingUpdated?.Invoke();
        }

        void AgoraRtcEventHandler.OnChannelMediaRelayStateChanged(CHANNEL_MEDIA_RELAY_STATE state, CHANNEL_MEDIA_RELAY_ERROR error)
        {
            OnChannelMediaRelayStateChanged?.Invoke(state, error);
        }

        void AgoraRtcEventHandler.OnChannelMediaRelayEvent(CHANNEL_MEDIA_RELAY_EVENT code)
        {
            OnChannelMediaRelayEvent?.Invoke(code);
        }

        void AgoraRtcEventHandler.OnAudioVolumeIndication(AudioVolumeInfo[] speakers, byte totalVolume)
        {
            OnAudioVolumeIndication?.Invoke(speakers, totalVolume);
        }

        void AgoraRtcEventHandler.OnActiveSpeaker(ulong uid)
        {
            OnActiveSpeaker?.Invoke(uid);
        }

        void AgoraRtcEventHandler.OnLocalPublishFallbackToAudioOnly(bool isFallbackOrRecover)
        {
            OnLocalPublishFallbackToAudioOnly?.Invoke(isFallbackOrRecover);
        }

        void AgoraRtcEventHandler.OnRemoteSubscribeFallbackToAudioOnly(ulong uid, bool isFallbackOrRecover)
        {
            OnRemoteSubscribeFallbackToAudioOnly?.Invoke(uid, isFallbackOrRecover);
        }

        void AgoraRtcEventHandler.OnLastmileQuality(QUALITY_TYPE quality)
        {
            OnLastmileQuality?.Invoke(quality);
        }

        void AgoraRtcEventHandler.OnLastmileProbeResult(LastmileProbeResult result)
        {
            OnLastmileProbeResult?.Invoke(result);
        }

        void AgoraRtcEventHandler.OnStreamInjectedStatus(string url, ulong uid, INJECT_STREAM_STATUS status)
        {
            OnStreamInjectedStatus?.Invoke(url, uid, status);
        }

        void AgoraRtcEventHandler.OnStreamMessage(ulong uid, long streamId, string data)
        {
            OnStreamMessage?.Invoke(uid, streamId, data);
        }

        void AgoraRtcEventHandler.OnStreamMessageError(ulong uid, long streamId, uint error, ushort missed, ushort cached)
        {
            OnStreamMessageError?.Invoke(uid, streamId, error, missed, cached);
        }

        void AgoraRtcEventHandler.OnWarning(long code, string msg)
        {
            OnWarning?.Invoke(code, msg);
        }

        void AgoraRtcEventHandler.OnError(long code, string msg)
        {
            OnError?.Invoke(code, msg);
        }

        void AgoraRtcEventHandler.OnApiCallExecuted(long code, string api, string result)
        {
            OnApiCallExecuted?.Invoke(code, api, result);
        }

        void AgoraRtcEventHandler.OnAudioDeviceStateChanged(string id, MEDIA_DEVICE_TYPE type, MEDIA_DEVICE_STATE_TYPE state)
        {
            OnAudioDeviceStateChanged?.Invoke(id, type, state);
        }

        void AgoraRtcEventHandler.OnAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE type, byte volume, bool muted)
        {
            OnAudioDeviceVolumeChanged?.Invoke(type, volume, muted);
        }

        void AgoraRtcEventHandler.OnVideoDeviceStateChanged(string id, MEDIA_DEVICE_TYPE type, MEDIA_DEVICE_STATE_TYPE state)
        {
            throw new NotImplementedException();
        }
        #endregion AgoraRtcEventHandler

        #region VideoFrameObserver
        public event OnCaptureVideoFrameDelegate OnCaptureVideoFrame;
        public event OnPreEncodeVideFrameDelegate OnPreEncodeVideFrame;
        public event OnRenderVideoFrameDelegate OnRenderVideoFrame;
        public event GetVideoFramePreferenceDelegate GetVideoFramePreference;
        public event GetRotationAppliedDelegate GetRotationApplied;
        public event GetMirrorAppliedDelegate GetMirrorApplied;
        public event GetSmoothRenderingEnabledDelegate GetSmoothRenderingEnabled;
        public event GetObservedFramePositionDelegate GetObservedFramePosition;
        public event IsMultipleChannelVideoFrameWantedDelegate IsMultipleChannelVideoFrameWanted;
        public event OnRenderVideoFrameExDelegate OnRenderVideoFrameEx;

        bool VideoFrameObserver.OnCaptureVideoFrame(VideoFrame frame)
        {
            return OnCaptureVideoFrame == null ? true : OnCaptureVideoFrame(frame);
        }

        bool VideoFrameObserver.OnPreEncodeVideFrame(VideoFrame frame)
        {
            var result = OnPreEncodeVideFrame == null ? true : OnPreEncodeVideFrame(frame);
            localVideo?.Render(frame);
            if (firstLocalVideoFrameElapsed.HasValue && localVideo != null)
            {
                TimeSpan elapsed = new TimeSpan(DateTime.Now.Ticks - firstLocalVideoFrameElapsed.Value.Ticks);
                OnFirstLocalVideoFrame?.Invoke(frame.width, frame.height, (uint)elapsed.TotalMilliseconds);
                firstLocalVideoFrameElapsed = null;
            }
            return result;
        }

        bool VideoFrameObserver.OnRenderVideoFrame(ulong uid, VideoFrame frame)
        {
            var result = OnRenderVideoFrame == null ? true : OnRenderVideoFrame(uid, frame);
            if (this.remoteVideos.TryGetValue(uid, out var remoteVideo))
            {
                remoteVideo.Render(frame);
                if (firstRemoteVideoFrameElapsed.HasValue)
                {
                    TimeSpan elapsed = new TimeSpan(DateTime.Now.Ticks - firstRemoteVideoFrameElapsed.Value.Ticks);
                    OnFirstRemoteVideoFrame(uid, frame.width, frame.height, (uint)elapsed.TotalMilliseconds);
                    firstRemoteVideoFrameElapsed = null;
                }
            }
            return result;
        }

        VIDEO_FRAME_TYPE VideoFrameObserver.GetVideoFramePreference()
        {
            return GetVideoFramePreference == null ? VIDEO_FRAME_TYPE.FRAME_TYPE_YUV420 : GetVideoFramePreference();
        }

        bool VideoFrameObserver.GetRotationApplied()
        {
            return GetRotationApplied == null ? false : GetRotationApplied();
        }

        bool VideoFrameObserver.GetMirrorApplied()
        {
            return GetMirrorApplied == null ? false : GetMirrorApplied();
        }

        bool VideoFrameObserver.GetSmoothRenderingEnabled()
        {
            return GetSmoothRenderingEnabled == null ? false : GetSmoothRenderingEnabled();
        }

        uint VideoFrameObserver.GetObservedFramePosition()
        {
            return GetObservedFramePosition == null ? Convert.ToUInt16(VIDEO_OBSERVER_POSITION.POSITION_POST_CAPTURER | VIDEO_OBSERVER_POSITION.POSITION_PRE_RENDERER) : GetObservedFramePosition();
        }

        bool VideoFrameObserver.IsMultipleChannelVideoFrameWanted()
        {
            return IsMultipleChannelVideoFrameWanted == null ? false : IsMultipleChannelVideoFrameWanted();
        }

        bool VideoFrameObserver.OnRenderVideoFrameEx(string channel, ulong uid, VideoFrame frame)
        {
            return OnRenderVideoFrameEx == null ? true : OnRenderVideoFrameEx(channel, uid, frame);
        }

        #endregion VideoFrameObserver

        #region AudioFrameObserver
        public event OnRecordAudioFrameDelegate OnRecordAudioFrame;
        public event OnPlaybackAudioFrameDelegate OnPlaybackAudioFrame;
        public event OnMixedAudioFrameDelegate OnMixedAudioFrame;
        public event OnPlaybackAudioFrameBeforeMixingDelegate OnPlaybackAudioFrameBeforeMixing;
        public event IsMultipleChannelAudioFrameWantedDelegate IsMultipleChannelAudioFrameWanted;
        public event OnPlaybackAudioFrameBeforeMixingExDelegate OnPlaybackAudioFrameBeforeMixingEx;

        bool AudioFrameObserver.OnRecordAudioFrame(AudioFrame frame)
        {
            return OnRecordAudioFrame == null ? true : OnRecordAudioFrame(frame);
        }

        bool AudioFrameObserver.OnPlaybackAudioFrame(AudioFrame frame)
        {
            var result = OnPlaybackAudioFrame == null ? true : OnPlaybackAudioFrame(frame);
            return result;
        }

        bool AudioFrameObserver.OnMixedAudioFrame(AudioFrame frame)
        {
            return OnMixedAudioFrame == null ? true : OnMixedAudioFrame(frame);
        }

        bool AudioFrameObserver.OnPlaybackAudioFrameBeforeMixing(ulong uid, AudioFrame frame)
        {
            return OnPlaybackAudioFrameBeforeMixing == null ? true : OnPlaybackAudioFrameBeforeMixing(uid, frame);
        }

        bool AudioFrameObserver.IsMultipleChannelAudioFrameWanted()
        {
            return IsMultipleChannelAudioFrameWanted == null ? false : IsMultipleChannelAudioFrameWanted();
        }

        bool AudioFrameObserver.OnPlaybackAudioFrameBeforeMixingEx(string channel, ulong uid, AudioFrame frame)
        {
            return OnPlaybackAudioFrameBeforeMixingEx == null ? true : OnPlaybackAudioFrameBeforeMixingEx(channel, uid, frame);
        }

        #endregion AudioFrameObserver

    }
}
