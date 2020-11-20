#pragma once
#include "pch.h"
#include "AudioDeviceCollection.g.h"

namespace winrt::AgoraWinRT::implementation
{
    struct AudioDeviceCollection : AudioDeviceCollectionT<AudioDeviceCollection>
    {
        AudioDeviceCollection(agora::rtc::IAudioDeviceCollection* collection);

        int32_t GetCount();
        int16_t GetDevice(int32_t index, hstring& name, hstring& id);
        int16_t SetDevice(hstring const& id);
        int16_t SetApplicationVolume(uint8_t volume);
        int16_t GetApplicationVolume(uint8_t& volume);
        int16_t SetApplicationMute(bool muted);
        int16_t IsApplicationMute(bool& muted);
        void Close();
    private:
        agora::rtc::IAudioDeviceCollection* m_raw;
    };
}
