using AgoraWinRT;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Graphics.Imaging;
using Windows.Media.Capture.Frames;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;

namespace AgoraUWP
{
    public abstract class VideoCanvas
    {
        public abstract object Target { get; set; }
        public virtual AgoraWinRT.RENDER_MODE_TYPE RenderMode { get; set; } = AgoraWinRT.RENDER_MODE_TYPE.RENDER_MODE_FIT;
        public virtual String Channel { get; set; } = null;
        public virtual UInt64 User { get; set; } = 0;
        public virtual AgoraWinRT.VIDEO_MIRROR_MODE_TYPE MirrorMode { get; set; } = AgoraWinRT.VIDEO_MIRROR_MODE_TYPE.VIDEO_MIRROR_MODE_DISABLED;

        public virtual void Render(MediaFrameReference frame) { }

        public virtual void Render(VideoFrame frame) { }
    }

}
