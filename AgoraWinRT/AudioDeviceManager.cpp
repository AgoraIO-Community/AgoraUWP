#include "pch.h"
#include "AudioDeviceManager.h"
#include "AudioDeviceManager.g.cpp"
#include "Utils.h"
#include "AudioDeviceCollection.h"

namespace winrt::AgoraWinRT::implementation
{
    AudioDeviceManager::AudioDeviceManager(agora::rtc::IRtcEngine* engine) :
        m_engine(engine)
    {
        m_manager = new agora::rtc::AAudioDeviceManager(m_engine);
    }
    AgoraWinRT::AudioDeviceCollection AudioDeviceManager::enumeratePlaybackDevices()
    {
        auto raw = m_manager->get()->enumeratePlaybackDevices();
        return winrt::make<AgoraWinRT::implementation::AudioDeviceCollection>(raw);
    }
    AgoraWinRT::AudioDeviceCollection AudioDeviceManager::enumerateRecordingDevices()
    {
        auto raw = m_manager->get()->enumerateRecordingDevices();
        return winrt::make<AgoraWinRT::implementation::AudioDeviceCollection>(raw);
    }
    int16_t AudioDeviceManager::SetPlaybackDevice(hstring const& id)
    {
        return m_manager->get()->setPlaybackDevice(Utils::To(id).c_str());
    }
    int16_t AudioDeviceManager::GetPlaybackDevice(hstring& id)
    {
        char deviceId[MAX_ID_STRING];
        auto result = m_manager->get()->getPlaybackDevice(deviceId);
        id = Utils::To(deviceId);
        return result;
    }
    int16_t AudioDeviceManager::GetPlaybackDeviceInfo(hstring& id, hstring& name)
    {
        char deviceId[MAX_ID_STRING];
        char deviceName[MAX_ID_STRING];
        auto result = m_manager->get()->getPlaybackDeviceInfo(deviceId, deviceName);
        id = Utils::To(deviceId);
        name = Utils::To(deviceName);
        return result;
    }
    int16_t AudioDeviceManager::SetRecordingDevice(hstring const& id)
    {
        return m_manager->get()->setRecordingDevice(Utils::To(id).c_str());
    }
    int16_t AudioDeviceManager::GetRecordingDevice(hstring& id)
    {
        char deviceId[MAX_ID_STRING];
        auto result = m_manager->get()->getRecordingDevice(deviceId);
        id = Utils::To(deviceId);
        return result;
    }
    int16_t AudioDeviceManager::GetRecordingDeviceInfo(hstring& id, hstring& name)
    {
        char deviceId[MAX_ID_STRING];
        char deviceName[MAX_ID_STRING];
        auto result = m_manager->get()->getRecordingDeviceInfo(deviceId, deviceName);
        id = Utils::To(deviceId), name = Utils::To(deviceName);
        return result;
    }
    int16_t AudioDeviceManager::StartPlaybackDeviceTest(hstring const& path)
    {
        return m_manager->get()->startPlaybackDeviceTest(Utils::To(path).c_str());
    }
    int16_t AudioDeviceManager::StopPlaybackDeviceTest()
    {
        return m_manager->get()->stopPlaybackDeviceTest();
    }
    int16_t AudioDeviceManager::SetPlaybackDevieVolume(uint8_t volume)
    {
        return m_manager->get()->setPlaybackDeviceVolume(volume);
    }
    int16_t AudioDeviceManager::GetPlaybackDeviceVolume(uint8_t& volume)
    {
        int vol;
        auto result = m_manager->get()->getPlaybackDeviceVolume(&vol);
        volume = vol;
        return result;
    }
    int16_t AudioDeviceManager::SetRecordingDeviceVolume(uint8_t volume)
    {
        return m_manager->get()->setRecordingDeviceVolume(volume);
    }
    int16_t AudioDeviceManager::GetRecordingDeviceVolume(uint8_t& volume)
    {
        int vol;
        auto result = m_manager->get()->getRecordingDeviceVolume(&vol);
        volume = vol;
        return result;
    }
    int16_t AudioDeviceManager::SetPlaybackDeviceMute(bool muted)
    {
        return m_manager->get()->setPlaybackDeviceMute(muted);
    }
    int16_t AudioDeviceManager::GetPlaybackDeviceMute(bool& muted)
    {
        bool m;
        auto result = m_manager->get()->getPlaybackDeviceMute(&m);
        muted = m;
        return result;
    }
    int16_t AudioDeviceManager::SetRecordingDeviceMute(bool muted)
    {
        return m_manager->get()->setRecordingDeviceMute(muted);
    }
    int16_t AudioDeviceManager::GetRecordingDeviceMute(bool& muted)
    {
        bool m;
        auto result = m_manager->get()->getRecordingDeviceMute(&m);
        muted = m;
        return result;
    }
    int16_t AudioDeviceManager::StartRecordingDeviceTest(int64_t interval)
    {
        return m_manager->get()->startRecordingDeviceTest(interval);
    }
    int16_t AudioDeviceManager::StopRecordingDeviceTest()
    {
        return m_manager->get()->stopRecordingDeviceTest();
    }
    int16_t AudioDeviceManager::StartAudioDeviceLoopbackTest(int64_t interval)
    {
        return m_manager->get()->startAudioDeviceLoopbackTest(interval);
    }
    int16_t AudioDeviceManager::StopAudioDeviceLoopbackTest()
    {
        return m_manager->get()->stopAudioDeviceLoopbackTest();
    }
    void AudioDeviceManager::Close()
    {
        m_manager->release();
    }
}
