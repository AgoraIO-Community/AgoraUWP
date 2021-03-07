#include "pch.h"
#include "AgoraRtc.h"
#include "AgoraRtc.g.cpp"
#include "Utils.h"
#include "Channel.h"
#include "AudioDeviceManager.h"

namespace winrt::AgoraWinRT::implementation
{
	AgoraRtc::AgoraRtc(AgoraWinRT::EngineContext const& context)
	{		
		if (context.appId.empty())
			throw hresult_invalid_argument(L"vendorKey is empty");

		m_rtcEngine = createAgoraRtcEngine();
		if (m_rtcEngine == nullptr)
			throw L"createAgoraRtcEngine failed";

		agora::rtc::RtcEngineContext rtcContext;
		rtcContext.appId = Utils::Copy(context.appId);
		rtcContext.eventHandler = this;
		//rtcContext.areaCode = (unsigned int)context.areaCode;
		//rtcContext.logConfig = Utils::To(context.logConfig);

		if (m_rtcEngine->initialize(rtcContext) == 0)
		{
			//ÉèÖÃIMediaEngine½Ó¿Ú
			agora::media::IMediaEngine* media = nullptr;
			if (!m_rtcEngine->queryInterface(agora::AGORA_IID_MEDIA_ENGINE, reinterpret_cast<void**>(&media))) {
				m_mediaEngine = media;
				m_rawAudioFrameObserver = new AgoraWinRT::implementation::RawAudioFrameObserver();
				m_mediaEngine->registerAudioFrameObserver(m_rawAudioFrameObserver);
				m_rawVideoFrameObserver = new AgoraWinRT::implementation::RawVideoFrameObserver();
				m_mediaEngine->registerVideoFrameObserver(m_rawVideoFrameObserver);
			}
			else
				throw L"media engine initialize failed";

			m_rtcEngine->registerMediaMetadataObserver(this, agora::rtc::IMetadataObserver::METADATA_TYPE::VIDEO_METADATA);
		}
		else
			throw L"rtcEngine initialize failed";
	}
	void AgoraRtc::RegisterRtcEngineEventHandler(AgoraWinRT::AgoraRtcEventHandler handler)
	{
		m_handler = handler;
	}
	void AgoraRtc::RegisterMediaMetadataObserver(AgoraWinRT::MetadataObserver observer)
	{
		m_metadataObserver = observer;
	}
	int16_t AgoraRtc::SetChannelProfile(AgoraWinRT::CHANNEL_PROFILE_TYPE const& type)
	{
		return m_rtcEngine->setChannelProfile((agora::rtc::CHANNEL_PROFILE_TYPE)type);
	}
	int16_t AgoraRtc::SetClientRole(AgoraWinRT::CLIENT_ROLE_TYPE const& type)
	{
		return m_rtcEngine->setClientRole((agora::rtc::CLIENT_ROLE_TYPE)type);
	}
	int16_t AgoraRtc::SetClientRole(AgoraWinRT::CLIENT_ROLE_TYPE const& type, AgoraWinRT::ClientRoleOptions const& options)
	{
		return m_rtcEngine->setClientRole((agora::rtc::CLIENT_ROLE_TYPE)type, Utils::To(options));
	}
	int16_t AgoraRtc::JoinChannel(hstring const& token, hstring const& channel, hstring const& info, uint64_t uid)
	{
		return m_rtcEngine->joinChannel(Utils::To(token).c_str(), Utils::To(channel).c_str(), Utils::To(info).c_str(), uid);
	}
	int16_t AgoraRtc::JoinChannel(hstring const& token, hstring const& channel, hstring const& info, uint64_t uid, AgoraWinRT::ChannelMediaOptions const& options)
	{
		return m_rtcEngine->joinChannel(Utils::To(token).c_str(), Utils::To(channel).c_str(), Utils::To(info).c_str(), uid, Utils::To(options));
	}
	int16_t AgoraRtc::SwitchChannel(hstring const& token, hstring const& channel)
	{
		return m_rtcEngine->switchChannel(Utils::To(token).c_str(), Utils::To(channel).c_str());
	}
	int16_t AgoraRtc::SwitchChannel(hstring const& token, hstring const& channel, AgoraWinRT::ChannelMediaOptions const& options)
	{
		return m_rtcEngine->switchChannel(Utils::To(token).c_str(), Utils::To(channel).c_str(), Utils::To(options));
	}
	int16_t AgoraRtc::LeaveChannel()
	{
		return m_rtcEngine->leaveChannel();
	}
	int16_t AgoraRtc::RenewToken(hstring const& token)
	{
		return m_rtcEngine->renewToken(Utils::To(token).c_str());
	}
	AgoraWinRT::CONNECTION_STATE_TYPE AgoraRtc::GetConnectionState()
	{
		return (AgoraWinRT::CONNECTION_STATE_TYPE)m_rtcEngine->getConnectionState();
	}
	void AgoraRtc::Close()
	{
		m_rtcEngine->release(true);
		delete m_rawAudioFrameObserver;
		delete m_rawVideoFrameObserver;
		delete m_videoSource;
	}
	int16_t AgoraRtc::EnableAudio()
	{
		return m_rtcEngine->enableAudio();
	}
	int16_t AgoraRtc::DisableAudio()
	{
		return m_rtcEngine->disableAudio();
	}
	int16_t AgoraRtc::SetAudioProfile(AgoraWinRT::AUDIO_PROFILE_TYPE const& profile, AgoraWinRT::AUDIO_SCENARIO_TYPE const& scenario)
	{
		return m_rtcEngine->setAudioProfile((agora::rtc::AUDIO_PROFILE_TYPE)profile, (agora::rtc::AUDIO_SCENARIO_TYPE)scenario);
	}
	int16_t AgoraRtc::AdjustRecordingSignalVolume(int16_t volume)
	{
		return m_rtcEngine->adjustRecordingSignalVolume(volume);
	}
	int16_t AgoraRtc::AdjustUserPlaybackSignalVolume(uint64_t uid, int16_t volume)
	{
		return m_rtcEngine->adjustUserPlaybackSignalVolume(uid, volume);
	}
	int16_t AgoraRtc::AdjustPlaybackSignalVolume(int16_t volume)
	{
		return m_rtcEngine->adjustPlaybackSignalVolume(volume);
	}
	int16_t AgoraRtc::EnableLocalAudio(bool enabled)
	{
		return m_rtcEngine->enableLocalAudio(enabled);
	}
	int16_t AgoraRtc::MuteLocalAudioStream(bool muted)
	{
		return m_rtcEngine->muteLocalAudioStream(muted);
	}
	int16_t AgoraRtc::MuteRemoteAudioStream(uint64_t uid, bool muted)
	{
		return m_rtcEngine->muteRemoteAudioStream(uid, muted);
	}
	int16_t AgoraRtc::MuteAllRemoteAudioStreams(bool muted)
	{
		return m_rtcEngine->muteAllRemoteAudioStreams(muted);
	}
	int16_t AgoraRtc::SetDefaultMuteAllRemoteAudioStreams(bool muted)
	{
		return m_rtcEngine->setDefaultMuteAllRemoteAudioStreams(muted);
	}
	int16_t AgoraRtc::EnableVideo()
	{
		return m_rtcEngine->enableVideo();
	}
	int16_t AgoraRtc::DisableVideo()
	{
		return m_rtcEngine->disableVideo();
	}
	int16_t AgoraRtc::SetVideoEncoderConfiguration(AgoraWinRT::VideoEncoderConfiguration const& config)
	{
		return m_rtcEngine->setVideoEncoderConfiguration(Utils::To(config));
	}
	int16_t AgoraRtc::MuteLocalVideoStream(bool muted)
	{
		return m_rtcEngine->muteLocalVideoStream(muted);
	}
	int16_t AgoraRtc::MuteRemoteVideoStream(uint64_t uid, bool muted)
	{
		return m_rtcEngine->muteRemoteVideoStream(uid, muted);
	}
	int16_t AgoraRtc::MuteAllRemoteVideoStream(bool muted)
	{
		return m_rtcEngine->muteAllRemoteVideoStreams(muted);
	}
	int16_t AgoraRtc::SetDefaultMuteAllRemoteVideoStreams(bool muted)
	{
		return m_rtcEngine->setDefaultMuteAllRemoteVideoStreams(muted);
	}
	int16_t AgoraRtc::SetBeautyEffectOptions(bool enabled, AgoraWinRT::BeautyOptions const& options)
	{
		return m_rtcEngine->setBeautyEffectOptions(enabled, Utils::To(options));
	}
	int16_t AgoraRtc::StartAudioMixing(hstring const& file, bool loopback, bool replace, int32_t cycle)
	{
		return m_rtcEngine->startAudioMixing(Utils::To(file).c_str(), loopback, replace, cycle);
	}
	int16_t AgoraRtc::StopAudioMixing()
	{
		return m_rtcEngine->stopAudioMixing();
	}
	int16_t AgoraRtc::PauseAudioMixing()
	{
		return m_rtcEngine->pauseAudioMixing();
	}
	int16_t AgoraRtc::ResumeAudioMixing()
	{
		return m_rtcEngine->resumeAudioMixing();
	}
	int16_t AgoraRtc::AdjustAudioMixingVolume(uint16_t volume)
	{
		return m_rtcEngine->adjustAudioMixingVolume(volume);
	}
	int16_t AgoraRtc::AdjustAudioMixingPlayoutVolume(uint16_t volume)
	{
		return m_rtcEngine->adjustAudioMixingPlayoutVolume(volume);
	}
	int16_t AgoraRtc::AdjustAudioMixingPublishVolume(uint16_t volume)
	{
		return m_rtcEngine->adjustAudioMixingPublishVolume(volume);
	}
	int16_t AgoraRtc::GetAudioMixingPublishVolume()
	{
		return m_rtcEngine->getAudioMixingPublishVolume();
	}
	int16_t AgoraRtc::GetAudioMixingDuration()
	{
		return m_rtcEngine->getAudioMixingDuration();
	}
	int16_t AgoraRtc::GetAudioMixingCurrentPosition()
	{
		return m_rtcEngine->getAudioMixingCurrentPosition();
	}
	int16_t AgoraRtc::SetAudioMixingPosition(uint64_t pos)
	{
		return m_rtcEngine->setAudioMixingPosition(pos);
	}
	int16_t AgoraRtc::SetAudioMixingPitch(int16_t pitch)
	{
		return m_rtcEngine->setAudioMixingPitch(pitch);
	}
	int16_t AgoraRtc::GetEffectsVolume()
	{
		return m_rtcEngine->getEffectsVolume();
	}
	int16_t AgoraRtc::SetEffectsVolume(uint16_t volume)
	{
		return m_rtcEngine->setEffectsVolume(volume);
	}
	int16_t AgoraRtc::SetVolumeOfEffect(uint64_t soundId, uint16_t volume)
	{
		return m_rtcEngine->setVolumeOfEffect(soundId, volume);
	}
	int16_t AgoraRtc::PlayEffect(uint64_t soundId, hstring const& file, int16_t loopCount, float pitch, float pan, float gain, bool publish)
	{
		return m_rtcEngine->playEffect(soundId, Utils::To(file).c_str(), loopCount, pitch, pan, gain, publish);
	}
	int16_t AgoraRtc::StopEffect(uint64_t soundId)
	{
		return m_rtcEngine->stopEffect(soundId);
	}
	int16_t AgoraRtc::StopAllEffect()
	{
		return m_rtcEngine->stopAllEffects();
	}
	int16_t AgoraRtc::PreloadEffect(uint64_t soundId, hstring const& file)
	{
		return m_rtcEngine->preloadEffect(soundId, Utils::To(file).c_str());
	}
	int16_t AgoraRtc::UnloadEffect(uint64_t soundId)
	{
		return m_rtcEngine->unloadEffect(soundId);
	}
	int16_t AgoraRtc::PauseEffect(uint64_t soundId)
	{
		return m_rtcEngine->pauseEffect(soundId);
	}
	int16_t AgoraRtc::PauseAllEffect()
	{
		return m_rtcEngine->pauseAllEffects();
	}
	int16_t AgoraRtc::ResumeEffect(uint64_t soundId)
	{
		return m_rtcEngine->resumeEffect(soundId);
	}
	int16_t AgoraRtc::ResumeAllEffect()
	{
		return m_rtcEngine->resumeAllEffects();
	}
	int16_t AgoraRtc::SetLocalVoiceChanger(AgoraWinRT::VOICE_CHANGER_PRESET const& changer)
	{
		return m_rtcEngine->setLocalVoiceChanger((agora::rtc::VOICE_CHANGER_PRESET)changer);
	}
	int16_t AgoraRtc::SetLocalVoiceReverbPreset(AgoraWinRT::AUDIO_REVERB_PRESET const& preset)
	{
		return m_rtcEngine->setLocalVoiceReverbPreset((agora::rtc::AUDIO_REVERB_PRESET)preset);
	}
	int16_t AgoraRtc::SetLocalVoicePitch(float pitch)
	{
		return m_rtcEngine->setLocalVoicePitch(pitch);
	}
	int16_t AgoraRtc::SetLocalVoiceEqualization(AgoraWinRT::AUDIO_EQUALIZATION_BAND_FREQUENCY const& freq, int16_t gain)
	{
		return m_rtcEngine->setLocalVoiceEqualization((agora::rtc::AUDIO_EQUALIZATION_BAND_FREQUENCY)freq, gain);
	}
	int16_t AgoraRtc::SetLocalVoiceReverb(AgoraWinRT::AUDIO_REVERB_TYPE const& type, uint64_t value)
	{
		return m_rtcEngine->setLocalVoiceReverb((agora::rtc::AUDIO_REVERB_TYPE)type, value);
	}
	int16_t AgoraRtc::SetVoiceBeautifierPreset(AgoraWinRT::VOICE_BEAUTIFIER_PRESET const& preset)
	{
		return m_rtcEngine->setVoiceBeautifierPreset((agora::rtc::VOICE_BEAUTIFIER_PRESET)preset);
	}
	int16_t AgoraRtc::SetVoiceBeautifierParameters(AgoraWinRT::VOICE_BEAUTIFIER_PRESET const& preset, int16_t param1, int16_t param2)
	{
		return m_rtcEngine->setVoiceBeautifierParameters((agora::rtc::VOICE_BEAUTIFIER_PRESET)preset, param1, param2);
	}
	int16_t AgoraRtc::SetAudioEffectPreset(AgoraWinRT::AUDIO_EFFECT_PRESET const& preset)
	{
		return m_rtcEngine->setAudioEffectPreset((agora::rtc::AUDIO_EFFECT_PRESET)preset);
	}
	int16_t AgoraRtc::SetAudioEffectParameters(AgoraWinRT::AUDIO_EFFECT_PRESET const& preset, uint8_t param1, uint8_t param2)
	{
		return m_rtcEngine->setAudioEffectParameters((agora::rtc::AUDIO_EFFECT_PRESET)preset, param1, param2);
	}
	int16_t AgoraRtc::SetVoiceConversionPreset(AgoraWinRT::VOICE_CONVERSION_PRESET const& preset)
	{
		return m_rtcEngine->setVoiceConversionPreset((agora::rtc::VOICE_CONVERSION_PRESET)preset);
	}
	int16_t AgoraRtc::EnableSoundPositionIndication(bool enabled)
	{
		return m_rtcEngine->enableSoundPositionIndication(enabled);
	}
	int16_t AgoraRtc::SetRemoteVoicePosition(uint64_t uid, float pan, float gain)
	{
		return m_rtcEngine->setRemoteVoicePosition(uid, pan, gain);
	}
	int16_t AgoraRtc::SetLiveTranscoding(AgoraWinRT::LiveTranscoding const& transcoding)
	{
		return m_rtcEngine->setLiveTranscoding(Utils::To(transcoding));
	}
	int16_t AgoraRtc::AddPublishStreamUrl(hstring const& url, bool enabled)
	{
		return m_rtcEngine->addPublishStreamUrl(Utils::To(url).c_str(), enabled);
	}
	int16_t AgoraRtc::RemovePublishStreamUrl(hstring const& url)
	{
		return m_rtcEngine->removePublishStreamUrl(Utils::To(url).c_str());
	}
	int16_t AgoraRtc::StartChannelMediaRelay(AgoraWinRT::ChannelMediaRelayConfiguration const& config)
	{
		return m_rtcEngine->startChannelMediaRelay(Utils::To(config));
	}
	int16_t AgoraRtc::UpdateChannelMediaRelay(AgoraWinRT::ChannelMediaRelayConfiguration const& config)
	{
		return m_rtcEngine->updateChannelMediaRelay(Utils::To(config));
	}
	int16_t AgoraRtc::StopChannelMediaRelay()
	{
		return m_rtcEngine->stopChannelMediaRelay();
	}
	int16_t AgoraRtc::EnableAudioVolumeIndication(int32_t interval, uint8_t smooth, bool report)
	{
		return m_rtcEngine->enableAudioVolumeIndication(interval, smooth, report);
	}
	int16_t AgoraRtc::EnableDualStreamMode(bool enabled)
	{
		return m_rtcEngine->enableDualStreamMode(enabled);
	}
	int16_t AgoraRtc::SetRemoteVideoStreamType(uint64_t uid, AgoraWinRT::REMOTE_VIDEO_STREAM_TYPE const& type)
	{
		return m_rtcEngine->setRemoteVideoStreamType(uid, (agora::rtc::REMOTE_VIDEO_STREAM_TYPE)type);
	}
	int16_t AgoraRtc::SetRemoteDefaultVideoStreamType(AgoraWinRT::REMOTE_VIDEO_STREAM_TYPE const& type)
	{
		return m_rtcEngine->setRemoteDefaultVideoStreamType((agora::rtc::REMOTE_VIDEO_STREAM_TYPE)type);
	}
	int16_t AgoraRtc::SetLocalPublishFallbackOption(AgoraWinRT::STREAM_FALLBACK_OPTIONS const& option)
	{
		return m_rtcEngine->setLocalPublishFallbackOption((agora::rtc::STREAM_FALLBACK_OPTIONS)option);
	}
	int16_t AgoraRtc::SetRemoteSubscribeFallbackOption(AgoraWinRT::STREAM_FALLBACK_OPTIONS const& option)
	{
		return m_rtcEngine->setRemoteSubscribeFallbackOption((agora::rtc::STREAM_FALLBACK_OPTIONS)option);
	}
	int16_t AgoraRtc::SetRemoteUserPriority(uint64_t uid, AgoraWinRT::PRIORITY_TYPE const& type)
	{
		return m_rtcEngine->setRemoteUserPriority(uid, (agora::rtc::PRIORITY_TYPE)type);
	}
	int16_t AgoraRtc::StartEchoTest(uint8_t interval)
	{
		return m_rtcEngine->startEchoTest(interval);
	}
	int16_t AgoraRtc::StopEchoTest()
	{
		return m_rtcEngine->stopEchoTest();
	}
	int16_t AgoraRtc::EnableLastmileTest()
	{
		return m_rtcEngine->enableLastmileTest();
	}
	int16_t AgoraRtc::DisableLastmileTest()
	{
		return m_rtcEngine->disableLastmileTest();
	}
	int16_t AgoraRtc::StartLastmileProbeTest(AgoraWinRT::LastmileProbeConfig const& config)
	{
		return m_rtcEngine->startLastmileProbeTest(Utils::To(config));
	}
	int16_t AgoraRtc::StopLastmileProbeTest()
	{
		return m_rtcEngine->stopLastmileProbeTest();
	}
	bool AgoraRtc::SetVideoSource(AgoraWinRT::VideoSource const& source)
	{
		if (m_videoSource != nullptr) delete m_videoSource;
		m_videoSource = new AgoraWinRT::implementation::RawVideoSource(source);
		return m_rtcEngine->setVideoSource(m_videoSource);
	}

	int16_t AgoraRtc::SetExternalVideoSource(bool enable, bool useTexture)
	{
		return m_mediaEngine->setExternalVideoSource(enable, useTexture);
	}
	int16_t AgoraRtc::PushVideoFrame(AgoraWinRT::ExternalVideoFrame const& frame)
	{
		LARGE_INTEGER freq, curCount;
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&curCount);
		curCount.QuadPart = curCount.QuadPart * 1000 / freq.QuadPart;
		frame.timestamp(curCount.QuadPart);
		auto raw = Utils::To(frame);
		auto result = m_mediaEngine->pushVideoFrame(raw);
		Utils::Free(raw);
		return result;
	}
	int16_t AgoraRtc::SetExternalAudioSource(bool enable, uint32_t sampleRate, uint8_t channels)
	{
		return m_rtcEngine->setExternalAudioSource(enable, sampleRate, channels);
	}
	int16_t AgoraRtc::PushAudioFrame(AgoraWinRT::AudioFrame const& frame)
	{
		frame.renderTimeMs(GetTickCount64());
		auto raw = Utils::To(frame);
		auto result = m_mediaEngine->pushAudioFrame(raw);
		Utils::Free(raw);
		return result;
	}
	int16_t AgoraRtc::SetExternalAudioSink(bool enable, uint32_t sampleRate, uint8_t channels)
	{
		return m_rtcEngine->setExternalAudioSink(enable, sampleRate, channels);
	}
	int16_t AgoraRtc::PullAudioFrame(AgoraWinRT::AudioFrame const& frame)
	{
		auto raw = Utils::To(frame);
		auto length = raw->samples * raw->channels * raw->bytesPerSample;
		delete[] raw->buffer;
		raw->buffer = new byte[length]();
		int result = m_mediaEngine->pullAudioFrame(raw);		
		if (result == 0) frame.buffer(Utils::To(raw->buffer, length));
		Utils::Free(raw);
		return result;
	}
	int16_t AgoraRtc::AddVideoWatermark(hstring const& file, AgoraWinRT::WatermarkOptions const& option)
	{
		return m_rtcEngine->addVideoWatermark(Utils::To(file).c_str(), Utils::To(option));
	}
	int16_t AgoraRtc::ClearVideoWatermark()
	{
		return m_rtcEngine->clearVideoWatermarks();
	}
	int16_t AgoraRtc::EnableEncryption(bool enable, AgoraWinRT::EncryptionConfig const& config)
	{
		if (enable) m_rtcEngine->registerPacketObserver(this);
		return m_rtcEngine->enableEncryption(enable, Utils::To(config));
	}
	void AgoraRtc::RegisterPacketObserver(AgoraWinRT::PacketObserver const& observer)
	{
		m_packetObserver = observer;
	}
	int16_t AgoraRtc::StartAudioRecording(hstring const& file, uint32_t sampleRate, AgoraWinRT::AUDIO_RECORDING_QUALITY_TYPE const& type)
	{
		return m_rtcEngine->startAudioRecording(Utils::To(file).c_str(), (agora::rtc::AUDIO_RECORDING_QUALITY_TYPE)type);
	}
	int16_t AgoraRtc::StopAudioRecording()
	{
		return m_rtcEngine->stopAudioRecording();
	}
	int16_t AgoraRtc::AddInjectStreamUrl(hstring const& url, AgoraWinRT::InjectStreamConfig const& config)
	{
		return m_rtcEngine->addInjectStreamUrl(Utils::To(url).c_str(), Utils::To(config));
	}
	int16_t AgoraRtc::RemoveInjectStreamUrl(hstring const& url)
	{
		return m_rtcEngine->removeInjectStreamUrl(Utils::To(url).c_str());
	}
	int64_t AgoraRtc::CreateDataStream(bool reliable, bool ordered)
	{
		int streamId;
		auto result = m_rtcEngine->createDataStream(&streamId, reliable, ordered);
		return result == 0 ? streamId : result;
	}
	int64_t AgoraRtc::CreateDataStream(int64_t& streamId, AgoraWinRT::DataStreamConfig const& config)
	{
		int id;
		auto result = m_rtcEngine->createDataStream(&id, Utils::To(config));
		streamId = id;
		return result;
	}
	int16_t AgoraRtc::SendStreamMessage(int64_t streamId, hstring const& data)
	{
		auto msg = Utils::To(data);
		return m_rtcEngine->sendStreamMessage(streamId, msg.c_str(), msg.size());
	}
	int16_t AgoraRtc::EnableLoopbackRecording(bool enabled, hstring const& deviceName)
	{
		return m_rtcEngine->enableLoopbackRecording(enabled, Utils::To(deviceName).c_str());
	}
	int16_t AgoraRtc::SetCameraCapturerConfiguration(AgoraWinRT::CameraCapturerConfiguration const& config)
	{
		return m_rtcEngine->setCameraCapturerConfiguration(Utils::To(config));
	}
	int16_t AgoraRtc::SetCloudProxy(AgoraWinRT::CLOUD_PROXY_TYPE const& type)
	{
		return m_rtcEngine->setCloudProxy((agora::rtc::CLOUD_PROXY_TYPE)type);
	}
	int16_t AgoraRtc::EnableDeepLearningDenoise(bool enabled)
	{
		return m_rtcEngine->enableDeepLearningDenoise(enabled);
	}
	int16_t AgoraRtc::SendCustomReportMessage(hstring const& id, hstring const& category, hstring const& eventName, hstring const& label, int64_t value)
	{
		return m_rtcEngine->sendCustomReportMessage(
			Utils::To(id).c_str(),
			Utils::To(category).c_str(),
			Utils::To(eventName).c_str(),
			Utils::To(label).c_str(),
			value);
	}
	int16_t AgoraRtc::GetCallId(hstring& id)
	{
		agora::util::AString callId;
		auto result = m_rtcEngine->getCallId(callId);
		if (result == 0) id = Utils::To(callId.get()->c_str());
		else id = hstring{};
		return result;
	}
	int16_t AgoraRtc::Rate(hstring const& callId, uint8_t rating, hstring const& desc)
	{
		return m_rtcEngine->rate(
			Utils::To(callId).c_str(),
			rating,
			Utils::To(desc).c_str()
		);
	}
	int16_t AgoraRtc::Complain(hstring const& callId, hstring const& desc)
	{
		return m_rtcEngine->complain(Utils::To(callId).c_str(), Utils::To(desc).c_str());
	}
	hstring AgoraRtc::GetVersion(int64_t& build)
	{
		int version;
		auto result = m_rtcEngine->getVersion(&version);
		build = version;
		return Utils::To(result);
	}
	int16_t AgoraRtc::SetLogFile(hstring const& file)
	{
		return m_rtcEngine->setLogFile(Utils::To(file).c_str());
	}
	int16_t AgoraRtc::SetLogFilter(uint16_t filter)
	{
		return m_rtcEngine->setLogFilter(filter);
	}
	int16_t AgoraRtc::SetLogFileSize(uint64_t size)
	{
		return m_rtcEngine->setLogFileSize(size);
	}
	hstring AgoraRtc::GetErrorDesc(int64_t code)
	{
		return Utils::To(m_rtcEngine->getErrorDescription(code));
	}
	void AgoraRtc::RegisterAudioFrameObserver(AgoraWinRT::AudioFrameObserver const& observer)
	{
		m_rawAudioFrameObserver->RegisterObserver(observer);
	}
	int16_t AgoraRtc::SetRecordingAudioFrameParameters(uint32_t sampleRate, uint8_t channels, AgoraWinRT::RAW_AUDIO_FRAME_OP_MODE_TYPE const& mode, uint32_t samplesPerCall)
	{
		return m_rtcEngine->setRecordingAudioFrameParameters(sampleRate, channels, (agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);
	}
	int16_t AgoraRtc::SetPlaybackAudioFrameParameters(uint32_t sampleRate, uint8_t channels, AgoraWinRT::RAW_AUDIO_FRAME_OP_MODE_TYPE const& mode, uint32_t samplesPerCall)
	{
		return m_rtcEngine->setPlaybackAudioFrameParameters(sampleRate, channels, (agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE)mode, samplesPerCall);
	}
	int16_t AgoraRtc::SetMixedAudioFrameParameters(uint32_t sampleRate, uint32_t samplesPerCall)
	{
		return m_rtcEngine->setMixedAudioFrameParameters(sampleRate, samplesPerCall);
	}
	void AgoraRtc::RegisterVideoFrameObserver(AgoraWinRT::VideoFrameObserver const& observer)
	{
		m_rawVideoFrameObserver->RegisterObserver(observer);
	}
	AgoraWinRT::Channel AgoraRtc::CreateChannel(hstring const& channel)
	{
		auto engine2 = dynamic_cast<agora::rtc::IRtcEngine2*>(m_rtcEngine);
		auto innerChannel = engine2->createChannel(Utils::To(channel).c_str());
		return winrt::make<AgoraWinRT::implementation::Channel>(innerChannel);
	}
	AgoraWinRT::AudioDeviceManager AgoraRtc::GetAudioDeviceManager()
	{
		return winrt::make<AgoraWinRT::implementation::AudioDeviceManager>(m_rtcEngine);
	}
	void AgoraRtc::onConnectionStateChanged(agora::rtc::CONNECTION_STATE_TYPE type, agora::rtc::CONNECTION_CHANGED_REASON_TYPE reason)
	{
		if (m_handler) m_handler.OnConnectionStateChanged((CONNECTION_STATE_TYPE)type, (CONNECTION_CHANGED_REASON_TYPE)reason);
	}
	void AgoraRtc::onJoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
	{
		if (m_handler) m_handler.OnJoinChannelSuccess(Utils::To(channel), uid, elapsed);
	}
	void AgoraRtc::onRejoinChannelSuccess(const char* channel, agora::rtc::uid_t uid, int elapsed)
	{
		if (m_handler) m_handler.OnRejoinChannelSuccess(Utils::To(channel), uid, elapsed);
	}
	void AgoraRtc::onLeaveChannel(const agora::rtc::RtcStats& value)
	{
		if (m_handler) {
			m_handler.OnLeaveChannel(Utils::To(value));
		}
	}
	void AgoraRtc::onClientRoleChanged(agora::rtc::CLIENT_ROLE_TYPE oldRole, agora::rtc::CLIENT_ROLE_TYPE newRole)
	{
		if (m_handler) m_handler.OnClientRoleChanged((CLIENT_ROLE_TYPE)oldRole, (CLIENT_ROLE_TYPE)newRole);
	}
	void AgoraRtc::onUserJoined(agora::rtc::uid_t uid, int elapsed)
	{
		if (m_handler) m_handler.OnUserJoined(uid, elapsed);
	}
	void AgoraRtc::onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason)
	{
		if (m_handler) m_handler.OnUserOffline(uid, (USER_OFFLINE_REASON_TYPE)reason);
	}
	void AgoraRtc::onNetworkTypeChanged(agora::rtc::NETWORK_TYPE type)
	{
		if (m_handler) m_handler.OnNetworkTypeChanged((NETWORK_TYPE)type);
	}
	void AgoraRtc::onConnectionLost()
	{
		if (m_handler) m_handler.OnConnectionLost();
	}
	void AgoraRtc::onTokenPrivilegeWillExpire(const char* token)
	{
		if (m_handler) m_handler.OnTokenPrivilegeWillExpire(Utils::To(token));
	}
	void AgoraRtc::onRequestToken()
	{
		if (m_handler) m_handler.OnRequestToken();
	}
	void AgoraRtc::onLocalAudioStateChanged(agora::rtc::LOCAL_AUDIO_STREAM_STATE state, agora::rtc::LOCAL_AUDIO_STREAM_ERROR error)
	{
		if (m_handler) m_handler.OnLocalAudioStateChanged((AgoraWinRT::LOCAL_AUDIO_STREAM_STATE)state, (AgoraWinRT::LOCAL_AUDIO_STREAM_ERROR)error);
	}
	void AgoraRtc::onLocalVideoStateChanged(agora::rtc::LOCAL_VIDEO_STREAM_STATE state, agora::rtc::LOCAL_VIDEO_STREAM_ERROR error)
	{
		if (m_handler) m_handler.OnLocalVideoStateChanged((AgoraWinRT::LOCAL_VIDEO_STREAM_STATE)state, (AgoraWinRT::LOCAL_VIDEO_STREAM_ERROR)error);
	}
	void AgoraRtc::onFirstLocalAudioFramePublished(int elapsed)
	{
		if (m_handler) m_handler.OnFirstLocalAudioFramePublished(elapsed);
	}
	void AgoraRtc::onFirstLocalVideoFramePublished(int elapsed)
	{
		if (m_handler) m_handler.OnFirstLocalVideoFramePublished(elapsed);
	}
	void AgoraRtc::onFirstLocalVideoFrame(int width, int height, int elapsed)
	{
		if (m_handler) m_handler.OnFirstLocalVideoFrame(width, height, elapsed);
	}
	void AgoraRtc::onAudioPublishStateChanged(const char* channel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapsed)
	{
		if (m_handler) m_handler.OnAudioPublishStateChanged(Utils::To(channel), (AgoraWinRT::STREAM_PUBLISH_STATE)oldState, (AgoraWinRT::STREAM_PUBLISH_STATE)newState, elapsed);
	}
	void AgoraRtc::onVideoPublishStateChanged(const char* channel, agora::rtc::STREAM_PUBLISH_STATE oldState, agora::rtc::STREAM_PUBLISH_STATE newState, int elapsed)
	{
		if (m_handler) m_handler.OnVideoPublishStateChanged(Utils::To(channel), (AgoraWinRT::STREAM_PUBLISH_STATE)oldState, (AgoraWinRT::STREAM_PUBLISH_STATE)newState, elapsed);
	}
	void AgoraRtc::onRemoteAudioStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_AUDIO_STATE state, agora::rtc::REMOTE_AUDIO_STATE_REASON reason, int elapsed)
	{
		if (m_handler) m_handler.OnRemoteAudioStateChanged(uid, (AgoraWinRT::REMOTE_AUDIO_STATE)state, (AgoraWinRT::REMOTE_AUDIO_STATE_REASON)reason, elapsed);
	}
	void AgoraRtc::onRemoteVideoStateChanged(agora::rtc::uid_t uid, agora::rtc::REMOTE_VIDEO_STATE state, agora::rtc::REMOTE_VIDEO_STATE_REASON reason, int elapsed)
	{
		if (m_handler) m_handler.OnRemoteVideoStateChanged(uid, (AgoraWinRT::REMOTE_VIDEO_STATE)state, (AgoraWinRT::REMOTE_VIDEO_STATE_REASON)reason, elapsed);
	}
	void AgoraRtc::onFirstRemoteVideoFrame(agora::rtc::uid_t uid, int width, int height, int elapsed)
	{
		if (m_handler) m_handler.OnFirstRemoteVideoFrame(uid, width, height, elapsed);
	}
	void AgoraRtc::onAudioSubscribeStateChanged(const char* channel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapsed)
	{
		if (m_handler) m_handler.OnAudioSubscribeStateChanged(Utils::To(channel), uid, (AgoraWinRT::STREAM_SUBSCRIBE_STATE)oldState, (AgoraWinRT::STREAM_SUBSCRIBE_STATE)newState, elapsed);
	}
	void AgoraRtc::onVideoSubscribeStateChanged(const char* channel, agora::rtc::uid_t uid, agora::rtc::STREAM_SUBSCRIBE_STATE oldState, agora::rtc::STREAM_SUBSCRIBE_STATE newState, int elapsed)
	{
		if (m_handler) m_handler.OnVideoSubscribeStateChanged(Utils::To(channel), uid, (AgoraWinRT::STREAM_SUBSCRIBE_STATE)oldState, (AgoraWinRT::STREAM_SUBSCRIBE_STATE)newState, elapsed);
	}
	void AgoraRtc::onRtcStats(const agora::rtc::RtcStats& stats)
	{
		if (m_handler) m_handler.OnRtcStats(Utils::To(stats));
	}
	void AgoraRtc::onNetworkQuality(agora::rtc::uid_t uid, int txQuality, int rxQuality)
	{
		if (m_handler) m_handler.OnNetworkQuality(uid, (AgoraWinRT::QUALITY_TYPE)txQuality, (AgoraWinRT::QUALITY_TYPE)rxQuality);
	}
	void AgoraRtc::onLocalAudioStats(const agora::rtc::LocalAudioStats& stats)
	{
		if (m_handler) m_handler.OnLocalAudioStats(Utils::To(stats));
	}
	void AgoraRtc::onLocalVideoStats(const agora::rtc::LocalVideoStats& stats)
	{
		if (m_handler) m_handler.OnLocalVideoStats(Utils::To(stats));
	}
	void AgoraRtc::onRemoteAudioStats(const agora::rtc::RemoteAudioStats& stats)
	{
		if (m_handler) m_handler.OnRemoteAudioStats(Utils::To(stats));
	}
	void AgoraRtc::onRemoteVideoStats(const agora::rtc::RemoteVideoStats& stats)
	{
		if (m_handler) m_handler.OnRemoteVideoStats(Utils::To(stats));
	}
	void AgoraRtc::onAudioMixingStateChanged(agora::rtc::AUDIO_MIXING_STATE_TYPE state, agora::rtc::AUDIO_MIXING_ERROR_TYPE error)
	{
		if (m_handler) m_handler.OnAudioMixingStateChanged((AgoraWinRT::AUDIO_MIXING_STATE_TYPE)state, (AgoraWinRT::AUDIO_MIXING_ERROR_TYPE)error);
	}
	void AgoraRtc::onRemoteAudioMixingBegin()
	{
		if (m_handler) m_handler.OnRemoteAudioMixingBegin();
	}
	void AgoraRtc::onRemoteAudioMixingEnd()
	{
		if (m_handler) m_handler.OnRemoteAudioMixingEnd();
	}
	void AgoraRtc::onAudioEffectFinished(int soundId)
	{
		if (m_handler) m_handler.OnAudioEffectFinished(soundId);
	}
	void AgoraRtc::onRtmpStreamingStateChanged(const char* url, agora::rtc::RTMP_STREAM_PUBLISH_STATE state, agora::rtc::RTMP_STREAM_PUBLISH_ERROR error)
	{
		if (m_handler) m_handler.OnRtmpStreamingStateChanged(Utils::To(url), (AgoraWinRT::RTMP_STREAM_PUBLISH_STATE)state, (AgoraWinRT::RTMP_STREAM_PUBLISH_ERROR)error);
	}
	void AgoraRtc::onRtmpStreamingEvent(const char* url, agora::rtc::RTMP_STREAMING_EVENT code)
	{
		if (m_handler) m_handler.OnRtmpStreamingEvent(Utils::To(url), (AgoraWinRT::RTMP_STREAMING_EVENT)code);
	}
	void AgoraRtc::onTranscodingUpdated()
	{
		if (m_handler) m_handler.OnTranscodingUpdated();
	}
	void AgoraRtc::onChannelMediaRelayStateChanged(agora::rtc::CHANNEL_MEDIA_RELAY_STATE state, agora::rtc::CHANNEL_MEDIA_RELAY_ERROR error)
	{
		if (m_handler)
			m_handler.OnChannelMediaRelayStateChanged(
				(AgoraWinRT::CHANNEL_MEDIA_RELAY_STATE)state,
				(AgoraWinRT::CHANNEL_MEDIA_RELAY_ERROR)error);
	}
	void AgoraRtc::onChannelMediaRelayEvent(agora::rtc::CHANNEL_MEDIA_RELAY_EVENT code)
	{
		if (m_handler) m_handler.OnChannelMediaRelayEvent((AgoraWinRT::CHANNEL_MEDIA_RELAY_EVENT)code);
	}
	void AgoraRtc::onAudioVolumeIndication(const agora::rtc::AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
	{
		if (m_handler) {
			auto speakerArray = Utils::To(speakers, speakerNumber);
			m_handler.OnAudioVolumeIndication(speakerArray, totalVolume);
			//speakerArray.clear();
		}
	}
	void AgoraRtc::onActiveSpeaker(agora::rtc::uid_t uid)
	{
		if (m_handler) m_handler.OnActiveSpeaker(uid);
	}
	void AgoraRtc::onLocalPublishFallbackToAudioOnly(bool isFallbackOrRecover)
	{
		if (m_handler) m_handler.OnLocalPublishFallbackToAudioOnly(isFallbackOrRecover);
	}
	void AgoraRtc::onRemoteSubscribeFallbackToAudioOnly(agora::rtc::uid_t uid, bool isFallbackOrRecover)
	{
		if (m_handler) m_handler.OnRemoteSubscribeFallbackToAudioOnly(uid, isFallbackOrRecover);
	}
	void AgoraRtc::onLastmileQuality(int quality)
	{
		if (m_handler) m_handler.OnLastmileQuality((winrt::AgoraWinRT::QUALITY_TYPE)quality);
	}
	void AgoraRtc::onLastmileProbeResult(const agora::rtc::LastmileProbeResult& result)
	{
		if (m_handler)
			m_handler.OnLastmileProbeResult(Utils::To(result));
	}
	void AgoraRtc::onStreamInjectedStatus(const char* url, agora::rtc::uid_t uid, int status)
	{
		if (m_handler) m_handler.OnStreamInjectedStatus(Utils::To(url), uid, (AgoraWinRT::INJECT_STREAM_STATUS)status);
	}
	void AgoraRtc::onStreamMessage(agora::rtc::uid_t uid, int streamId, const char* data, size_t length)
	{
		if (m_handler) m_handler.OnStreamMessage(uid, streamId, Utils::To(data));
	}
	void AgoraRtc::onStreamMessageError(agora::rtc::uid_t uid, int streamId, int code, int missed, int cached)
	{
		if (m_handler) m_handler.OnStreamMessageError(uid, streamId, code, missed, cached);
	}
	void AgoraRtc::onWarning(int warn, const char* msg)
	{
		if (m_handler) m_handler.OnWarning(warn, Utils::To(msg));
	}
	void AgoraRtc::onError(int err, const char* msg)
	{
		if (m_handler) m_handler.OnError(err, Utils::To(msg));
	}
	void AgoraRtc::onApiCallExecuted(int err, const char* api, const char* result)
	{
		if (m_handler) m_handler.OnApiCallExecuted(err, Utils::To(api), Utils::To(result));
	}
	void AgoraRtc::onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
	{
		if (m_handler) m_handler.OnAudioDeviceStateChanged(Utils::To(deviceId), AgoraWinRT::MEDIA_DEVICE_TYPE(deviceType), AgoraWinRT::MEDIA_DEVICE_STATE_TYPE(deviceState));
	}
	void AgoraRtc::onAudioDeviceVolumeChanged(agora::rtc::MEDIA_DEVICE_TYPE type, int volume, bool muted)
	{
		if (m_handler) m_handler.OnAudioDeviceVolumeChanged(AgoraWinRT::MEDIA_DEVICE_TYPE(type), volume, muted);
	}
	int AgoraRtc::getMaxMetadataSize()
	{
		if (m_metadataObserver) return m_metadataObserver.GetMaxMetadataSize();
		else return 1024;
	}
	bool AgoraRtc::onReadyToSendMetadata(agora::rtc::IMetadataObserver::Metadata& metadata)
	{
		auto data = Utils::To(metadata);
		if (m_metadataObserver) return m_metadataObserver.OnReadyToSendMetadata(*data);
		else return true;
	}
	void AgoraRtc::onMetadataReceived(const agora::rtc::IMetadataObserver::Metadata& metadata)
	{
		auto data = Utils::To(metadata);
		if (m_metadataObserver) m_metadataObserver.OnMetadataReceived(*data);
	}
	bool AgoraRtc::onSendAudioPacket(Packet& packet)
	{
		if (m_packetObserver) {
			auto data = Utils::To(packet);
			return m_packetObserver.OnSendAudioPacket(*data);
		}
		else return true;
	}
	bool AgoraRtc::onSendVideoPacket(Packet& packet)
	{
		if (m_packetObserver) {
			auto data = Utils::To(packet);
			return m_packetObserver.OnSendVideoPacket(*data);
		}
		else return true;
	}
	bool AgoraRtc::onReceiveAudioPacket(Packet& packet)
	{
		if (m_packetObserver) {
			auto data = Utils::To(packet);
			return m_packetObserver.OnReceiveAudioPacket(*data);
		}
		else return true;
	}
	bool AgoraRtc::onReceiveVideoPacket(Packet& packet)
	{
		if (m_packetObserver) {
			auto data = Utils::To(packet);
			return m_packetObserver.OnReceiveVideoPacket(*data);
		}
		else return true;
	}
}
