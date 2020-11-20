using AgoraWinRT;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.Media.Capture.Frames;

namespace AgoraUWP
{
    public delegate void VideoFrameArrivedDelegate(MediaFrameReference frame);
    public delegate void AudioFrameArrivedDelegate(AudioMediaFrame frame);

    public interface IMediaCapturer: IDisposable
    {
        event VideoFrameArrivedDelegate OnVideoFrameArrived;
        event AudioFrameArrivedDelegate OnAudioFrameArrived;
        DeviceInformation VideoDevice { get; }
        DeviceInformation AudioDevice { get; }
        MediaFrameFormat AudioFormat { get; }
        VIDEO_PIXEL_FORMAT VideoFormat { get; }
        VIDEO_BUFFER_TYPE VideoBufferType { get; }
        void EnableVideo(bool enabled);
        void EnableAudio(bool enabled);
    }

}
