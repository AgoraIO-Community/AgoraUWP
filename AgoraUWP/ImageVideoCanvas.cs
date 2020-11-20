using AgoraWinRT;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Windows.Foundation;
using Windows.Graphics.Imaging;
using Windows.Media.Capture.Frames;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;

namespace AgoraUWP
{


    public class ImageVideoCanvas : VideoCanvas
    {
        private Image target;
        private SoftwareBitmap backBuffer;
        private bool running;
        private SoftwareBitmapSource source;
        private ushort oldRotation = 0;
        private ScaleTransform mirrorTransform;
        private RotateTransform rotateTransform;
        private ScaleTransform adapterTransform;
        private TransformGroup tranforms;

        public ImageVideoCanvas()
        {
            this.mirrorTransform = new ScaleTransform();
            this.mirrorTransform.ScaleX = 1;

            this.rotateTransform = new RotateTransform();
            this.rotateTransform.Angle = 0;

            this.adapterTransform = new ScaleTransform();

            this.tranforms = new TransformGroup();
            this.tranforms.Children.Add(this.rotateTransform);
            this.tranforms.Children.Add(this.adapterTransform);
            this.tranforms.Children.Add(this.mirrorTransform);

        }

        public override RENDER_MODE_TYPE RenderMode
        {
            get => base.RenderMode;
            set
            {
                base.RenderMode = value;
                AdjustAdapterTransform();
            }
        }

        private void AdjustAdapterTransform()
        {

        }

        public override VIDEO_MIRROR_MODE_TYPE MirrorMode
        {
            get => base.MirrorMode;
            set
            {
                base.MirrorMode = value;
                if (value == VIDEO_MIRROR_MODE_TYPE.VIDEO_MIRROR_MODE_ENABLED) this.mirrorTransform.ScaleX = -1;
                else this.mirrorTransform.ScaleX = 1;
            }
        }

        public override object Target
        {
            get => target;
            set
            {
                target = value as Image;
                if (target != null)
                {
                    target.Source = new SoftwareBitmapSource();
                    source = (SoftwareBitmapSource)target.Source;
                    target.RenderTransformOrigin = new Point(0.5, 0.5);
                    target.RenderTransform = tranforms;
                }
            }
        }

        public override void Render(MediaFrameReference frame)
        {
            if (source == null) return;
            RenderBitmap(Utils.ConvertToImageAsync(frame?.VideoMediaFrame));
        }

        private void RenderBitmap(SoftwareBitmap bitmap)
        {
            if (bitmap == null) return;
            bitmap = Interlocked.Exchange(ref this.backBuffer, bitmap);
            bitmap?.Dispose();

            _ = target.Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal,
                async () =>
                {
                    if (this.running) return;
                    this.running = true;

                    SoftwareBitmap tempBitmap;
                    while ((tempBitmap = Interlocked.Exchange(ref this.backBuffer, null)) != null)
                    {

                        await source?.SetBitmapAsync(tempBitmap);
                        tempBitmap.Dispose();
                    }

                    this.running = false;
                });
        }


        public override void Render(VideoFrame frame)
        {
            if (source == null) return;
            if (this.oldRotation != frame.rotation)
            {
                this.oldRotation = frame.rotation;
                _ = target.Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal, () => { this.rotateTransform.Angle = this.oldRotation; });
            }
            var nvBuffer = Utils.ConvertToNv12(frame);
            var image = Utils.ConvertToImage(nvBuffer, (int)frame.width, (int)frame.height);
            RenderBitmap(image);
        }

    }
}
