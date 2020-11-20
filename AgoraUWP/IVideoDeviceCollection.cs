using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;
using Windows.Devices.Enumeration;

namespace AgoraUWP
{
    public interface IVideoDeviceCollection : IDisposable
    {
        int GetCount();
        void GetDevice(int index, out string name, out string id);
        void SetDevice(string id);
    }
    
}
