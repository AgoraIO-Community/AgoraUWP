using AgoraWinRT;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Windows.Graphics.Imaging;
using Windows.Media.Capture.Frames;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;

namespace AgoraUWP
{
    public class ImageBrushVideoCanvas : VideoCanvas
    {
        private ImageBrush target;
        private SoftwareBitmapSource source;
        private ScaleTransform mirrorTransform;
        private RotateTransform rotateTransform;
        private TransformGroup tranforms;
        private SoftwareBitmap backBuffer;
        private bool running;
        private ushort oldRotation;

        public ImageBrushVideoCanvas()
        {
            mirrorTransform = new ScaleTransform();
            mirrorTransform.CenterX = 0.5;
            mirrorTransform.CenterY = 0.5;
            mirrorTransform.ScaleX = 1;

            rotateTransform = new RotateTransform();
            rotateTransform.CenterX = 0.5;
            rotateTransform.CenterY = 0.5;
            rotateTransform.Angle = 0;


            tranforms = new TransformGroup();
            tranforms.Children.Add(this.rotateTransform);
            tranforms.Children.Add(this.mirrorTransform);
        }
        public override RENDER_MODE_TYPE RenderMode
        {
            get => base.RenderMode;
            set
            {
                base.RenderMode = value;
                if (target != null) target.Stretch = GetStretch();
            }
        }
        public override VIDEO_MIRROR_MODE_TYPE MirrorMode { 
            get => base.MirrorMode;
            set
            {
                base.MirrorMode = value;
                if (value == VIDEO_MIRROR_MODE_TYPE.VIDEO_MIRROR_MODE_ENABLED)
                    mirrorTransform.ScaleX = -1;
                else
                    mirrorTransform.ScaleX = 1;
            }
        }
        public override object Target
        {
            get => target;
            set
            {
                target = value as ImageBrush;
                if (target != null)
                {
                    target.ImageSource = new SoftwareBitmapSource();
                    source = (SoftwareBitmapSource)target.ImageSource;
                    target.RelativeTransform = tranforms;
                    target.Stretch = GetStretch();
                }
            }
        }

        public override void Render(MediaFrameReference frame)
        {
            if (source == null) return;
            RenderBitmap(Utils.ConvertToImageAsync(frame?.VideoMediaFrame));
        }

        public override void Render(VideoFrame frame)
        {
            if (source == null) return;
            if (oldRotation != frame.rotation)
            {
                oldRotation = frame.rotation;
                _ = target.Dispatcher.RunAsync(
                    Windows.UI.Core.CoreDispatcherPriority.Normal,
                    () => { 
                        rotateTransform.Angle = oldRotation; 
                    });
            }
            var nvbuffer = Utils.ConvertToNv12(frame);
            var image = Utils.ConvertToImage(nvbuffer, (int)frame.width, (int)frame.height);
            RenderBitmap(image);
        }

        private void RenderBitmap(SoftwareBitmap bitmap)
        {
            if (bitmap == null) return;
            bitmap = Interlocked.Exchange(ref backBuffer, bitmap);
            bitmap?.Dispose();

            _ = target.Dispatcher.RunAsync(Windows.UI.Core.CoreDispatcherPriority.Normal,
                async () =>
                {
                    if (running) return;
                    running = true;

                    SoftwareBitmap tempBitmap;
                    while ((tempBitmap = Interlocked.Exchange(ref backBuffer, null)) != null)
                    {

                        await source?.SetBitmapAsync(tempBitmap);
                        tempBitmap.Dispose();
                    }

                    running = false;
                });
        }

        private Stretch GetStretch()
        {
            switch(RenderMode)
            {
                case RENDER_MODE_TYPE.RENDER_MODE_FIT: return Stretch.Uniform;
                case RENDER_MODE_TYPE.RENDER_MODE_HIDDEN: return Stretch.UniformToFill;
                case RENDER_MODE_TYPE.RENDER_MODE_FILL: return Stretch.Fill;
                default: return Stretch.None;
            }
        }
    }
}
