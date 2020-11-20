#include "pch.h"
#include "AudioDeviceCollection.h"
#include "AudioDeviceCollection.g.cpp"
#include <Utils.h>

namespace winrt::AgoraWinRT::implementation
{
    AudioDeviceCollection::AudioDeviceCollection(agora::rtc::IAudioDeviceCollection* collection):
        m_raw(collection)
    {
       
    }
    int32_t AudioDeviceCollection::GetCount()
    {
        return m_raw->getCount();
    }
    int16_t AudioDeviceCollection::GetDevice(int32_t index, hstring& name, hstring& id)
    {
        char deviceName[MAX_ID_STRING] = {};
        char deviceId[MAX_ID_STRING] = {};
        auto result = m_raw->getDevice(index, deviceName, deviceId);
        if (result == 0) {
            name = Utils::To(deviceName);
            id = Utils::To(deviceId);
        }
        return result;
    }
    int16_t AudioDeviceCollection::SetDevice(hstring const& id)
    {
        return m_raw->setDevice(Utils::To(id).c_str());
    }
    int16_t AudioDeviceCollection::SetApplicationVolume(uint8_t volume)
    {
        return m_raw->setApplicationVolume(volume);
    }
    int16_t AudioDeviceCollection::GetApplicationVolume(uint8_t& volume)
    {
        int vol;
        auto result = m_raw->getApplicationVolume(vol);
        volume = vol;
        return result;
    }
    int16_t AudioDeviceCollection::SetApplicationMute(bool muted)
    {
        return m_raw->setApplicationMute(muted);
    }
    int16_t AudioDeviceCollection::IsApplicationMute(bool& muted)
    {
        bool m;
        auto result = m_raw->isApplicationMute(m);
        muted = m;
        return result;
    }
    void AudioDeviceCollection::Close()
    {
        m_raw->release();
    }
}
