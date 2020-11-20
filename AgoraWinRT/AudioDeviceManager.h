#pragma once
#include "pch.h"
#include "AudioDeviceManager.g.h"

namespace winrt::AgoraWinRT::implementation
{
    struct AudioDeviceManager : AudioDeviceManagerT<AudioDeviceManager>
    {
        AudioDeviceManager(agora::rtc::IRtcEngine* engine);

        AgoraWinRT::AudioDeviceCollection enumeratePlaybackDevices();
        AgoraWinRT::AudioDeviceCollection enumerateRecordingDevices();
        int16_t SetPlaybackDevice(hstring const& id);
        int16_t GetPlaybackDevice(hstring& id);
        int16_t GetPlaybackDeviceInfo(hstring& id, hstring& name);
        int16_t SetRecordingDevice(hstring const& id);
        int16_t GetRecordingDevice(hstring& id);
        int16_t GetRecordingDeviceInfo(hstring& id, hstring& name);
        int16_t StartPlaybackDeviceTest(hstring const& path);
        int16_t StopPlaybackDeviceTest();
        int16_t SetPlaybackDevieVolume(uint8_t volume);
        int16_t GetPlaybackDeviceVolume(uint8_t& volume);
        int16_t SetRecordingDeviceVolume(uint8_t volume);
        int16_t GetRecordingDeviceVolume(uint8_t& volume);
        int16_t SetPlaybackDeviceMute(bool muted);
        int16_t GetPlaybackDeviceMute(bool& muted);
        int16_t SetRecordingDeviceMute(bool muted);
        int16_t GetRecordingDeviceMute(bool& muted);
        int16_t StartRecordingDeviceTest(int64_t interval);
        int16_t StopRecordingDeviceTest();
        int16_t StartAudioDeviceLoopbackTest(int64_t interval);
        int16_t StopAudioDeviceLoopbackTest();
        void Close();
    private:
        agora::rtc::IRtcEngine* m_engine;
        agora::rtc::AAudioDeviceManager* m_manager;
    };
}
