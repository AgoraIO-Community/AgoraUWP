using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;
using Windows.UI.Text;
using Windows.UI.Xaml.Media.Animation;

namespace AgoraUWP
{
    public interface IVideoDeviceManager : IDisposable
    {
        Task<IVideoDeviceCollection> EnumerateVideoDevices();
        void StartDeviceTest(VideoCanvas videoCanvas);
        void StopDeviceTest();
        void SetDevice(string id);
        string GetDevice();
    }

    internal class VideoDeviceCollection : IVideoDeviceCollection
    {
        private IVideoDeviceManager m_manager;
        private List<DeviceInformation> m_infos;

        public VideoDeviceCollection(IVideoDeviceManager manager, DeviceInformationCollection devices)
        {
            m_manager = manager;
            m_infos = new List<DeviceInformation>();
            for (var i = 0; i < devices.Count; i++) m_infos.Add(devices[i]);
        }
        public void Dispose()
        {
            m_infos.Clear();
        }

        public int GetCount()
        {
            return m_infos.Count;
        }

        public void GetDevice(int index, out string name, out string id)
        {
            if (index < m_infos.Count && index >= 0)
            {
                var info = m_infos[index];
                name = info.Name;
                id = info.Id;
            }
            else throw new IndexOutOfRangeException();
        }

        public void SetDevice(string id)
        {
            m_manager.SetDevice(id);

        }
    }
    internal class VideoDeviceManager : IVideoDeviceManager
    {
        private AgoraRtc m_engine;

        public VideoDeviceManager(AgoraRtc engine)
        {
            m_engine = engine;
        }
        public void Dispose()
        {
            
        }

        public async Task<IVideoDeviceCollection> EnumerateVideoDevices()
        {
            var devices = await DeviceInformation.FindAllAsync(DeviceClass.VideoCapture);
            return new VideoDeviceCollection(this, devices);
        }

        public string GetDevice()
        {
            return m_engine.CurrentVideoDevice?.Id;
        }

        public async void SetDevice(string id)
        {
            var device = await DeviceInformation.CreateFromIdAsync(id);
            if (device == null) throw new ArgumentOutOfRangeException();
            else m_engine.CurrentVideoDevice = device;
        }

        public void StartDeviceTest(VideoCanvas videoCanvas)
        {
            m_engine.StartVideoTest(videoCanvas);
        }

        public void StopDeviceTest()
        {
            m_engine.StopVideoTest();
        }
    }
}
