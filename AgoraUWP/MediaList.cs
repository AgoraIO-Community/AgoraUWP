using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.Media.Capture.Frames;

namespace AgoraUWP
{
    public class MediaList
    {
        public static async Task<MediaList> GetInstance()
        {
            var list = new MediaList();
            list.VideoDevices = await DeviceInformation.FindAllAsync(DeviceClass.VideoCapture);
            list.AudioDevices = await DeviceInformation.FindAllAsync(DeviceClass.AudioCapture);
            list.SpeakerDevices = await DeviceInformation.FindAllAsync(DeviceClass.AudioRender);
            return list;
        }

        private MediaList() { }
        public IReadOnlyCollection<DeviceInformation> VideoDevices { get; private set; }
        public IReadOnlyCollection<DeviceInformation> AudioDevices { get; private set; }
        public IReadOnlyCollection<DeviceInformation> SpeakerDevices { get; private set; }
    }
}
