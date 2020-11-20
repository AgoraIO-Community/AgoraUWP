using AgoraWinRT;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.Devices.Sensors;
using Windows.Media.Capture;
using Windows.Media.Capture.Frames;
using Windows.Media.MediaProperties;

namespace AgoraUWP
{
    public class GeneralMediaCapturer: IMediaCapturer
    {
        private MediaFrameReader videoFrameReader;
        private MediaFrameReader audioFrameReader;
        private MediaCapture mediaCapture;

        public event VideoFrameArrivedDelegate OnVideoFrameArrived;
        public event AudioFrameArrivedDelegate OnAudioFrameArrived;

        public GeneralMediaCapturer(MediaFrameSourceGroup sourceGroup, StreamingCaptureMode mode)
        {
            var settings = CreateSettings(mode);
            settings.SourceGroup = sourceGroup;
            mediaCapture = new MediaCapture();
            mediaCapture.InitializeAsync(settings).AsTask().Wait();
            InitReader();
        }
        public GeneralMediaCapturer(DeviceInformation device, StreamingCaptureMode mode)
        {
            var settings = CreateSettings(mode);

            if (mode == StreamingCaptureMode.Video) settings.VideoDeviceId = device.Id;
            else settings.AudioDeviceId = device.Id;

            mediaCapture = new MediaCapture();
            mediaCapture.InitializeAsync(settings).AsTask().Wait();
            InitReader();
        }
        private MediaCaptureInitializationSettings CreateSettings(StreamingCaptureMode mode)
        {
            return new MediaCaptureInitializationSettings
            {
                SharingMode = MediaCaptureSharingMode.SharedReadOnly,
                StreamingCaptureMode = mode,
                MemoryPreference = MediaCaptureMemoryPreference.Auto,
            };
        }
        private void InitReader()
        {
            foreach (MediaFrameSource source in mediaCapture.FrameSources.Values)
            {
                if (source.Info.SourceKind == MediaFrameSourceKind.Color)
                {
                    VideoDevice = source.Info.DeviceInformation;
                    videoFrameReader = mediaCapture.CreateFrameReaderAsync(source, MediaEncodingSubtypes.Nv12).AsTask().GetAwaiter().GetResult();
                    videoFrameReader.FrameArrived += VideoFrameArrivedEvent;
                }
                else if (source.Info.SourceKind == MediaFrameSourceKind.Audio)
                {
                    AudioDevice = source.Info.DeviceInformation;
                    AudioFormat = source.CurrentFormat;
                    audioFrameReader = mediaCapture.CreateFrameReaderAsync(source).AsTask().GetAwaiter().GetResult();
                    audioFrameReader.FrameArrived += AudioFrameArrivedEvent;
                }
            }

        }
        public MediaFrameFormat AudioFormat { get; private set; }
        public VIDEO_PIXEL_FORMAT VideoFormat { get=>VIDEO_PIXEL_FORMAT.VIDEO_PIXEL_NV12; }
        public VIDEO_BUFFER_TYPE VideoBufferType { get => VIDEO_BUFFER_TYPE.VIDEO_BUFFER_RAW_DATA; }

        public DeviceInformation VideoDevice { get; private set; }

        public DeviceInformation AudioDevice { get; private set; }

        public void EnableVideo(bool enabled)
        {
            if (enabled) videoFrameReader?.StartAsync().AsTask().Wait();
            else videoFrameReader?.StopAsync().AsTask().Wait();
        }
        public void EnableAudio(bool enabled)
        {
            if (enabled) audioFrameReader?.StartAsync().AsTask().Wait();
            else audioFrameReader?.StopAsync().AsTask().Wait();
        }
        private void AudioFrameArrivedEvent(MediaFrameReader sender, MediaFrameArrivedEventArgs args)
        {
            if (OnAudioFrameArrived == null) return;
            using(var frame = sender.TryAcquireLatestFrame())
            {
                if (frame != null) OnAudioFrameArrived?.Invoke(frame.AudioMediaFrame);
            }
        }
        private void VideoFrameArrivedEvent(MediaFrameReader sender, MediaFrameArrivedEventArgs args)
        {
            if (OnVideoFrameArrived == null) return;
            using(var frame = sender.TryAcquireLatestFrame())
            {
                if (frame != null) OnVideoFrameArrived?.Invoke(frame);
            }
        }

        public void Dispose()
        {
            videoFrameReader?.StopAsync().AsTask().Wait();
            videoFrameReader?.Dispose();
            audioFrameReader?.StopAsync().AsTask().Wait();
            audioFrameReader?.Dispose();
            mediaCapture?.Dispose();
        }

    }
}
