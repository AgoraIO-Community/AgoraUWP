using AgoraWinRT;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading.Tasks;
using Windows.Media.Capture;
using Windows.Media.Capture.Frames;
using Windows.Media.MediaProperties;

namespace AgoraUWP
{
    class MediaCaptureVideoSource : AgoraWinRT.VideoSource
    {
        private VideoSourceConsumer m_consumer;
        private GeneralMediaCapturer m_capturer;

        public bool OnInitialize(VideoSourceConsumer consumer)
        {
            m_consumer = consumer;
            return this.InitCaptureAsync();
        }

        public void OnDispose()
        {
            m_capturer?.Dispose();
        }

        public bool OnStart()
        {
            m_capturer?.EnableVideo(true);
            return true;
        }

        public void OnStop()
        {
            m_capturer?.EnableVideo(false);
        }

        public VIDEO_PIXEL_FORMAT GetBufferType()
        {
            return VIDEO_PIXEL_FORMAT.VIDEO_PIXEL_NV12;
        }

        public VIDEO_CAPTURE_TYPE GetVideoCaptureType()
        {
            return VIDEO_CAPTURE_TYPE.VIDEO_CAPTURE_CAMERA;
        }

        public VIDEO_CONTENT_HINT GetVideoContentHint()
        {
            return VIDEO_CONTENT_HINT.CONTENT_HINT_NONE;
        }

        private bool InitCaptureAsync()
        {
            var mediaCapture = new MediaCapture();
            var sourceGroup = MediaFrameSourceGroup.FindAllAsync().AsTask().GetAwaiter().GetResult();
            if (sourceGroup.Count == 0) return false;
            m_capturer = new GeneralMediaCapturer(sourceGroup[0], StreamingCaptureMode.Video);
            m_capturer.OnVideoFrameArrived += VideoFrameArrivedEvent;
            return true;
        }

        private void VideoFrameArrivedEvent(MediaFrameReference frame)
        {
            var buffer = frame.BufferMediaFrame;
            if (buffer == null) return;
            var format = frame.VideoMediaFrame?.VideoFormat;
            if (format == null) return;
            m_consumer.ConsumeRawVideoFrame(
                buffer.Buffer.ToArray(),
                VIDEO_PIXEL_FORMAT.VIDEO_PIXEL_NV12,
                format.Width, format.Height,
                0,
                (ulong)new DateTimeOffset().ToUnixTimeMilliseconds());
        }
    }
}
