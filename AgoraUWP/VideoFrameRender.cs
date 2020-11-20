using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Windows.Graphics.Imaging;
using Windows.Media.Capture.Frames;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;

namespace AgoraUWP
{
    [ComImport]
    [Guid("5B0D3235-4DBA-4D44-865E-8F1D0E4FD04D")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    unsafe interface IMemoryBufferByteAccess
    {
        void GetBuffer(out byte* buffer, out uint capacity);
    }

    public interface IVideoFrameRender
    {
        bool Rendering { get; set; }
        VideoCanvas Canvas { get; set; }

        void RenderFrame(MediaFrameReference frame);
    }

    public class ImageVideoFrameRender : IVideoFrameRender<Image>
    {
        private SoftwareBitmap backBuffer;
        private bool running = false;
        private bool rendering = false;
        private VideoCanvas<Image> canvas = null;
        private SoftwareBitmapSource target = null;

        public bool Rendering { get => rendering; set => rendering = value; }
        public VideoCanvas<Image> Canvas
        {
            get => canvas;
            set
            {
                canvas = value;
                target = (SoftwareBitmapSource)canvas?.Target.Source;
            }

        }

        public void RenderFrame(MediaFrameReference frame)
        {
            if (!Rendering || Canvas == null || Canvas.Target == null) return;
            var bitmap = ConvertToImage(frame?.VideoMediaFrame);
            RenderBitmap(bitmap);
        }

        private void RenderBitmap(SoftwareBitmap bitmap)
        {
            if (bitmap == null) return;
            bitmap = Interlocked.Exchange(ref this.backBuffer, bitmap);
            bitmap?.Dispose();

            _ = Canvas.Target.Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal,
                async () =>
                {
                    if (this.running) return;
                    this.running = true;

                    SoftwareBitmap tempBitmap;
                    while ((tempBitmap = Interlocked.Exchange(ref this.backBuffer, null)) != null)
                    {
                        await target?.SetBitmapAsync(tempBitmap);
                        tempBitmap.Dispose();
                    }

                    this.running = false;
                });
        }

        private unsafe SoftwareBitmap ConvertToImage(VideoMediaFrame input)
        {
            using (var inputBitmap = input?.SoftwareBitmap)
            {
                if (inputBitmap == null) return null;
                return SoftwareBitmap.Convert(inputBitmap, BitmapPixelFormat.Bgra8, BitmapAlphaMode.Ignore);
            }
        }
    }
}
