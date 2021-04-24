#include "pch.h"
#include "Utils.h"

namespace Utils {

	std::string To(winrt::hstring const& value) {
		std::wstring wvalue(value.c_str());
		return std::string(wvalue.begin(), wvalue.end());
	}

	char* Copy(winrt::hstring const& value) {
		std::string source = Utils::To(value);
		int length = source.length() + 1;
		char* result = new char[length];
		strcpy_s(result, length, source.c_str());
		return result;
	}

	winrt::hstring To(const char* value) {
		if (value == NULL) return winrt::hstring();
		std::string string = std::string(value);
		int size = MultiByteToWideChar(CP_UTF8, 0, &string[0], (int)string.size(), NULL, 0);
		std::wstring wstring(size, 0);
		MultiByteToWideChar(CP_UTF8, 0, &string[0], (int)string.size(), &wstring[0], size);
		return winrt::hstring(wstring);
	}

	winrt::hstring To(const char* value, size_t length) {
		if (value == NULL || length == 0) return winrt::hstring();
		std::string string = std::string(value, length);
		int size = MultiByteToWideChar(CP_UTF8, 0, &string[0], (int)string.size(), NULL, 0);
		std::wstring wstring(size, 0);
		MultiByteToWideChar(CP_UTF8, 0, &string[0], (int)string.size(), &wstring[0], size);
		return winrt::hstring(wstring);
	}

	winrt::AgoraWinRT::RtcStats To(agora::rtc::RtcStats const& raw) {
		winrt::AgoraWinRT::RtcStats stats;
		stats.duration = raw.duration;
		stats.txBytes = raw.txBytes;
		stats.rxBytes = raw.rxBytes;
		stats.txAudioBytes = raw.txAudioBytes;
		stats.txVideoBytes = raw.txVideoBytes;
		stats.rxAudioBytes = raw.rxAudioBytes;
		stats.rxVideoBytes = raw.rxVideoBytes;
		stats.txKBitRate = raw.txKBitRate;
		stats.rxKBitRate = raw.rxKBitRate;
		stats.rxAudioKBitRate = raw.rxAudioKBitRate;
		stats.txAudioKBitRate = raw.txAudioKBitRate;
		stats.rxVideoKBitRate = raw.rxVideoKBitRate;
		stats.txVideoKBitRate = raw.txVideoKBitRate;
		stats.lastmileDelay = raw.lastmileDelay;
		stats.txPacketLossRate = raw.txPacketLossRate;
		stats.rxPacketLossRate = raw.rxPacketLossRate;
		stats.userCount = raw.userCount;
		stats.cpuAppUsage = raw.cpuAppUsage;
		stats.cpuTotalUsage = raw.cpuTotalUsage;
		stats.gatewayRtt = raw.gatewayRtt;
		stats.memoryAppUsageRatio = raw.memoryAppUsageRatio;
		stats.memoryTotalUsageRatio = raw.memoryTotalUsageRatio;
		stats.memoryAppUsageInKbytes = raw.memoryAppUsageInKbytes;
		return stats;
	}

	winrt::AgoraWinRT::LocalAudioStats To(agora::rtc::LocalAudioStats const& raw) {
		winrt::AgoraWinRT::LocalAudioStats stats;
		stats.numChannels = raw.numChannels;
		stats.sentSampleRate = raw.sentSampleRate;
		stats.sentBitrate = raw.sentBitrate;
		stats.txPacketLossRate = raw.txPacketLossRate;
		return stats;
	}

	winrt::AgoraWinRT::LocalVideoStats To(agora::rtc::LocalVideoStats const& raw) {
		winrt::AgoraWinRT::LocalVideoStats stats;
		stats.sentBitrate = raw.sentBitrate;
		stats.sentFrameRate = raw.sentFrameRate;
		stats.encoderOutputFrameRate = raw.encoderOutputFrameRate;
		stats.rendererOutputFrameRate = raw.rendererOutputFrameRate;
		stats.targetBitrate = raw.targetBitrate;
		stats.targetFrameRate = raw.targetFrameRate;
		stats.qualityAdaptIndication = (winrt::AgoraWinRT::QUALITY_ADAPT_INDICATION)raw.qualityAdaptIndication;
		stats.encodedBitrate = raw.encodedBitrate;
		stats.encodedFrameWidth = raw.encodedFrameWidth;
		stats.encodedFrameHeight = raw.encodedFrameHeight;
		stats.encodedFrameCount = raw.encodedFrameCount;
		stats.codecType = (winrt::AgoraWinRT::VIDEO_CODEC_TYPE)raw.codecType;
		stats.txPacketLossRate = raw.txPacketLossRate;
		stats.captureFrameRate = raw.captureFrameRate;
		stats.captureBrightnessLevel = (winrt::AgoraWinRT::CAPTURE_BRIGHTNESS_LEVEL_TYPE)raw.captureBrightnessLevel;
		return stats;
	}

	winrt::AgoraWinRT::RemoteAudioStats To(agora::rtc::RemoteAudioStats const& raw) {
		winrt::AgoraWinRT::RemoteAudioStats stats;
		stats.uid = raw.uid;
		stats.quality = raw.quality;
		stats.networkTransportDelay = raw.networkTransportDelay;
		stats.jitterBufferDelay = raw.jitterBufferDelay;
		stats.audioLossRate = raw.audioLossRate;
		stats.numChannels = raw.numChannels;
		stats.receivedSampleRate = raw.receivedSampleRate;
		stats.receivedBitrate = raw.receivedBitrate;
		stats.totalFrozenTime = raw.totalFrozenTime;
		stats.frozenRate = raw.frozenRate;
		stats.totalActiveTime = raw.totalActiveTime;
		stats.publishDuration = raw.publishDuration;
		stats.qoeQuality = raw.qoeQuality;
		stats.qualityChangedReason = raw.qualityChangedReason;
		stats.mosValue = raw.mosValue;
		return stats;
	}

	winrt::AgoraWinRT::RemoteVideoStats To(agora::rtc::RemoteVideoStats const& raw) {
		winrt::AgoraWinRT::RemoteVideoStats stats;
		stats.uid = raw.uid;
		stats.delay = raw.delay;
		stats.width = raw.width;
		stats.height = raw.height;
		stats.receivedBitrate = raw.receivedBitrate;
		stats.decoderOutputFrameRate = raw.decoderOutputFrameRate;
		stats.rendererOutputFrameRate = raw.rendererOutputFrameRate;
		stats.packetLossRate = raw.packetLossRate;
		stats.rxStreamType = (winrt::AgoraWinRT::REMOTE_VIDEO_STREAM_TYPE)raw.rxStreamType;
		stats.totalFrozenTime = raw.totalFrozenTime;
		stats.frozenRate = raw.frozenRate;
		stats.totalActiveTime = raw.totalActiveTime;
		stats.publishDuration = raw.publishDuration;
		return stats;
	}

	winrt::com_array<winrt::AgoraWinRT::AudioVolumeInfo> To(const agora::rtc::AudioVolumeInfo* raw, int count) {
		auto infos = winrt::com_array<winrt::AgoraWinRT::AudioVolumeInfo>(count);
		for (int i = 0; i < count; i++) {
			auto &info = infos[i];
			info.channelId = Utils::To(raw[i].channelId);
			info.uid = raw[i].uid;
			info.vad = raw[i].vad;
			info.volume = raw[i].volume;
		}
		return infos;
	}

	winrt::AgoraWinRT::LastmileProbeOneWayResult To(const agora::rtc::LastmileProbeOneWayResult& raw) {
		winrt::AgoraWinRT::LastmileProbeOneWayResult result;
		result.packetLossRate = raw.packetLossRate;
		result.jitter = raw.jitter;
		result.availableBandwidth = raw.availableBandwidth;
		return result;
	}

	winrt::AgoraWinRT::LastmileProbeResult To(const agora::rtc::LastmileProbeResult& raw) {
		winrt::AgoraWinRT::LastmileProbeResult result;
		result.state = (winrt::AgoraWinRT::LASTMILE_PROBE_RESULT_STATE)raw.state;
		result.uplinkReport = Utils::To(raw.uplinkReport);
		result.downlinkReport = Utils::To(raw.downlinkReport);
		result.rtt = raw.rtt;
		return result;
	}

	winrt::com_array<uint8_t> To(void* raw, int count) {
		uint8_t* buffer = reinterpret_cast<uint8_t*>(raw);
		return winrt::com_array(buffer, buffer + count);
	}

	winrt::com_ptr<winrt::AgoraWinRT::implementation::Metadata> To(const agora::rtc::IMetadataObserver::Metadata& raw) {
		auto result = winrt::make_self<winrt::AgoraWinRT::implementation::Metadata>();
		result->uid(raw.uid);
		result->timestamp(raw.timeStampMs);
		result->buffer(Utils::To(raw.buffer, raw.size));
		return result;
	}

	winrt::com_ptr<winrt::AgoraWinRT::implementation::Packet> To(const agora::rtc::IPacketObserver::Packet& raw) {
		auto result = winrt::make_self<winrt::AgoraWinRT::implementation::Packet>();
		result->buffer(Utils::To(const_cast<unsigned char*>(raw.buffer), raw.size));
		return result;
	}

	winrt::com_ptr<winrt::AgoraWinRT::implementation::AudioFrame> To(const agora::media::IAudioFrameObserver::AudioFrame& raw) {
		auto result = winrt::make_self<winrt::AgoraWinRT::implementation::AudioFrame>();
		result->type((winrt::AgoraWinRT::AUDIO_FRAME_TYPE)raw.type);
		result->samples(raw.samples);
		result->bytesPerSample(raw.bytesPerSample);
		result->channels(raw.channels);
		result->samplesPerSec(raw.samplesPerSec);
		result->buffer(Utils::To(raw.buffer, raw.samples * raw.channels * raw.bytesPerSample));
		result->renderTimeMs(raw.renderTimeMs);
		result->avsync_type(raw.avsync_type);
		return result;
	}

	winrt::com_ptr<winrt::AgoraWinRT::implementation::VideoFrame> To(const agora::media::IVideoFrameObserver::VideoFrame& raw) {
		auto result = winrt::make_self<winrt::AgoraWinRT::implementation::VideoFrame>();
		result->type((winrt::AgoraWinRT::VIDEO_FRAME_TYPE)raw.type);
		result->width(raw.width);
		result->height(raw.height);
		result->yStride(raw.yStride);
		result->uStride(raw.uStride);
		result->vStride(raw.vStride);
		result->yBuffer(Utils::To(raw.yBuffer, raw.height * raw.width));
		result->uBuffer(Utils::To(raw.uBuffer, raw.height * raw.width / 4));
		result->vBuffer(Utils::To(raw.vBuffer, raw.height * raw.width / 4));
		result->rotation(raw.rotation);
		result->renderTimeMs(raw.renderTimeMs);
		result->avsync_type(raw.avsync_type);
		return result;
	}

	void* To(winrt::com_array<uint8_t> const& value) {
		auto raw = new byte[value.size()];
		memcpy_s(raw, value.size(), value.data(), value.size());
		return raw;
	}

	void To(winrt::com_ptr<winrt::AgoraWinRT::implementation::VideoFrame> const& value, agora::media::IVideoFrameObserver::VideoFrame& raw) {
		raw.type = (agora::media::IVideoFrameObserver::VIDEO_FRAME_TYPE)(value->type());
		raw.width = value->width();
		raw.height = value->height();
		raw.yStride = value->yStride();
		raw.uStride = value->uStride();
		raw.vStride = value->vStride();
		delete[] raw.yBuffer;
		raw.yBuffer = Utils::To(value->yBuffer());
		delete[] raw.uBuffer;
		raw.uBuffer = Utils::To(value->uBuffer());
		delete[] raw.vBuffer;
		raw.vBuffer = Utils::To(value->vBuffer());
		raw.rotation = value->rotation();
		raw.renderTimeMs = value->renderTimeMs();
		raw.avsync_type = value->avsync_type();
	}

	agora::rtc::BeautyOptions To(winrt::AgoraWinRT::BeautyOptions const& value) {
		agora::rtc::BeautyOptions raw;
		raw.lighteningContrastLevel = (agora::rtc::BeautyOptions::LIGHTENING_CONTRAST_LEVEL)value.lighteningContrastLevel;
		raw.lighteningLevel = value.lighteningLevel;
		raw.smoothnessLevel = value.smoothnessLevel;
		raw.rednessLevel = value.rednessLevel;
		return raw;
	}

	agora::rtc::VideoEncoderConfiguration To(winrt::AgoraWinRT::VideoEncoderConfiguration const& value) {
		agora::rtc::VideoEncoderConfiguration raw;
		raw.dimensions.width = value.dimensions.width;
		raw.dimensions.height = value.dimensions.height;
		raw.frameRate = (agora::rtc::FRAME_RATE)value.frameRate;
		raw.minFrameRate = value.minFrameRate;
		raw.bitrate = value.bitrate;
		raw.minBitrate = value.minBitrate;
		raw.orientationMode = (agora::rtc::ORIENTATION_MODE)value.orientationMode;
		raw.degradationPreference = (agora::rtc::DEGRADATION_PREFERENCE)value.degradationPreference;
		raw.mirrorMode = (agora::rtc::VIDEO_MIRROR_MODE_TYPE)value.mirrorMode;
		return raw;
	}

	agora::rtc::TranscodingUser* To(winrt::com_array<winrt::AgoraWinRT::TranscodingUser> const& value) {
		auto raw = new agora::rtc::TranscodingUser[value.size()];
		int index = 0;
		std::for_each(value.begin(), value.end(),
			[raw, &index](winrt::AgoraWinRT::TranscodingUser const& elem) {
				auto user = &raw[index++];
				user->uid = elem.uid;
				user->x = elem.x;
				user->y = elem.y;
				user->width = elem.width;
				user->height = elem.height;
				user->zOrder = elem.zOrder;
				user->alpha = elem.alpha;
				user->audioChannel = elem.audioChannel;
			});

		return raw;
	}

	agora::rtc::RtcImage* To(winrt::AgoraWinRT::RtcImage const& value) {
		auto raw = new agora::rtc::RtcImage();
		raw->url = Utils::Copy(value.url);
		raw->x = value.x;
		raw->y = value.y;
		raw->width = value.width;
		raw->height = value.height;
		return raw;
	}

	agora::rtc::LiveStreamAdvancedFeature* To(winrt::com_array<winrt::AgoraWinRT::LiveStreamAdvancedFeature> const& value) {
		auto raw = new agora::rtc::LiveStreamAdvancedFeature[value.size()];
		int index = 0;
		std::for_each(value.begin(), value.end(),
			[raw, &index](winrt::AgoraWinRT::LiveStreamAdvancedFeature const& elem) {
				auto feature = &raw[index++];
				feature->LBHQ = Utils::Copy(elem.LBHQ);
				feature->VEO = Utils::Copy(elem.VEO);
				feature->featureName = Utils::Copy(elem.featureName);
				feature->opened = elem.opened;
			});
		return raw;
	}

	agora::rtc::LiveTranscoding To(winrt::AgoraWinRT::LiveTranscoding const& value) {
		agora::rtc::LiveTranscoding raw;
		raw.width = value.width();
		raw.height = value.height();
		raw.videoBitrate = value.videoBitrate();
		raw.videoFramerate = value.videoFramerate();
		raw.lowLatency = value.lowLatency();
		raw.videoGop = value.videoGop();
		raw.videoCodecProfile = (agora::rtc::VIDEO_CODEC_PROFILE_TYPE)value.videoCodecProfile();
		raw.backgroundColor = value.backgroundColor();
		auto users = value.transcodingUsers();
		raw.userCount = users.size();
		raw.transcodingUsers = Utils::To(users);
		raw.transcodingExtraInfo = Utils::Copy(value.transcodingExtraInfo());
		raw.metadata = Utils::Copy(value.metadata());
		raw.watermark = Utils::To(value.watermark());
		raw.backgroundImage = Utils::To(value.backgroundImage());
		raw.audioSampleRate = (agora::rtc::AUDIO_SAMPLE_RATE_TYPE)value.audioSampleRate();
		raw.audioBitrate = value.audioBitrate();
		raw.audioChannels = value.audioChannels();
		raw.audioCodecProfile = (agora::rtc::AUDIO_CODEC_PROFILE_TYPE)value.audioCodecProfile();
		auto features = value.advancedFeatures();
		raw.advancedFeatureCount = features.size();
		raw.advancedFeatures = Utils::To(features);
		return raw;
	}

	agora::rtc::ChannelMediaInfo* To(winrt::AgoraWinRT::ChannelMediaInfo const& value) {
		auto raw = new agora::rtc::ChannelMediaInfo();
		raw->channelName = Utils::Copy(value.name);
		raw->token = Utils::Copy(value.token);
		raw->uid = value.uid;
		return raw;
	}

	agora::rtc::ChannelMediaInfo* To(winrt::com_array<winrt::AgoraWinRT::ChannelMediaInfo> const& value) {
		auto raw = new agora::rtc::ChannelMediaInfo[value.size()];
		int index = 0;
		std::for_each(value.begin(), value.end(),
			[raw, &index](winrt::AgoraWinRT::ChannelMediaInfo const& elem) {
				auto info = &raw[index++];
				info->channelName = Utils::Copy(elem.name);
				info->token = Utils::Copy(elem.token);
				info->uid = elem.uid;
			});
		return raw;
	}

	agora::rtc::ChannelMediaRelayConfiguration To(winrt::AgoraWinRT::ChannelMediaRelayConfiguration const& value) {
		agora::rtc::ChannelMediaRelayConfiguration raw;
		raw.srcInfo = Utils::To(value.src());
		auto dest = value.dest();
		raw.destCount = dest.size();
		raw.destInfos = Utils::To(dest);
		return raw;
	}

	agora::rtc::LastmileProbeConfig To(winrt::AgoraWinRT::LastmileProbeConfig const& value) {
		agora::rtc::LastmileProbeConfig raw;
		raw.probeUplink = value.probeUplink;
		raw.probeDownlink = value.probeDownlink;
		raw.expectedUplinkBitrate = value.expectedUplinkBitrate;
		raw.expectedDownlinkBitrate = value.expectedDownlinkBitrate;
		return raw;
	}


	agora::media::ExternalVideoFrame* To(winrt::AgoraWinRT::ExternalVideoFrame const& value) {
		auto raw = new agora::media::ExternalVideoFrame();
		raw->type = (agora::media::ExternalVideoFrame::VIDEO_BUFFER_TYPE)value.type();
		raw->format = (agora::media::ExternalVideoFrame::VIDEO_PIXEL_FORMAT)value.format();
		raw->stride = value.stride();
		raw->buffer = Utils::To(value.buffer());
		raw->height = value.height();
		raw->cropLeft = value.cropLeft();
		raw->cropTop = value.cropTop();
		raw->cropRight = value.cropRight();
		raw->cropBottom = value.cropBottom();
		raw->rotation = value.rotation();
		raw->timestamp = value.timestamp();
		return raw;
	}

	void Free(agora::media::ExternalVideoFrame* value) {
		delete[] value->buffer;
		delete value;
	}

	agora::media::IAudioFrameObserver::AudioFrame* To(winrt::AgoraWinRT::AudioFrame const& value) {
		auto raw = new agora::media::IAudioFrameObserver::AudioFrame();
		raw->type = (agora::media::IAudioFrameObserver::AUDIO_FRAME_TYPE)value.type();
		raw->samples = value.samples();
		raw->bytesPerSample = value.bytesPerSample();
		raw->channels = value.channels();
		raw->samplesPerSec = value.samplesPerSec();
		raw->buffer = Utils::To(value.buffer());
		raw->renderTimeMs = value.renderTimeMs();
		raw->avsync_type = value.avsync_type();
		return raw;
	}

	void Free(agora::media::IAudioFrameObserver::AudioFrame* value) {
		delete[] value->buffer;
		delete value;
	}

	agora::rtc::Rectangle To(winrt::AgoraWinRT::Rectangle const& value) {
		agora::rtc::Rectangle raw;
		raw.x = value.x;
		raw.y = value.y;
		raw.width = value.width;
		raw.height = value.height;
		return raw;
	}

	agora::rtc::WatermarkOptions To(winrt::AgoraWinRT::WatermarkOptions const& value) {
		agora::rtc::WatermarkOptions raw;
		raw.visibleInPreview = value.visibleInPreview;
		raw.positionInLandscapeMode = Utils::To(value.positionInLandscapeMode);
		raw.positionInPortraitMode = Utils::To(value.positionInProtraitMode);
		return raw;
	}

	agora::rtc::EncryptionConfig To(winrt::AgoraWinRT::EncryptionConfig const& value) {
		agora::rtc::EncryptionConfig raw;
		raw.encryptionMode = (agora::rtc::ENCRYPTION_MODE)value.mode;
		raw.encryptionKey = Utils::Copy(value.key);
		return raw;
	}

	agora::rtc::InjectStreamConfig To(winrt::AgoraWinRT::InjectStreamConfig const& value) {
		agora::rtc::InjectStreamConfig raw;
		raw.width = value.width;
		raw.height = value.height;
		raw.videoGop = value.videoGop;
		raw.videoFramerate = value.videoFramerate;
		raw.videoBitrate = value.videoBitrate;
		raw.audioSampleRate = (agora::rtc::AUDIO_SAMPLE_RATE_TYPE)value.audioSampleRate;
		raw.audioBitrate = value.audioBitrate;
		raw.audioChannels = value.audioChannels;
		return raw;
	}

	agora::rtc::CameraCapturerConfiguration To(winrt::AgoraWinRT::CameraCapturerConfiguration const& value)
	{
		agora::rtc::CameraCapturerConfiguration raw;
		raw.preference = (agora::rtc::CAPTURER_OUTPUT_PREFERENCE)value.prefernce;
		raw.captureHeight = value.captureHeight;
		raw.captureWidth = value.captureWidth;
		return raw;
	}

	agora::rtc::ChannelMediaOptions To(winrt::AgoraWinRT::ChannelMediaOptions const& value) {
		agora::rtc::ChannelMediaOptions raw;
		raw.autoSubscribeAudio = value.autoSubscribeAudio;
		raw.autoSubscribeVideo = value.autoSubscribeVideo;
		return raw;
	}

	void* To(winrt::array_view<const uint8_t> const& value)
	{
		auto result = new byte[value.size()];
		memcpy_s(result, value.size(), value.data(), value.size());
		return result;
	}

	agora::rtc::ClientRoleOptions To(winrt::AgoraWinRT::ClientRoleOptions const& value)
	{
		agora::rtc::ClientRoleOptions raw;
		raw.audienceLatencyLevel = (agora::rtc::AUDIENCE_LATENCY_LEVEL_TYPE)value.audienceLatencyLevel();
		return raw;
	}

	agora::rtc::DataStreamConfig To(winrt::AgoraWinRT::DataStreamConfig const& value)
	{
		agora::rtc::DataStreamConfig raw;
		raw.ordered = value.ordered;
		raw.syncWithAudio = value.syncWithAudio;
		return raw;
	}
	agora::rtc::LogConfig To(winrt::AgoraWinRT::LogConfig const& value)
	{
		agora::rtc::LogConfig raw;
		raw.filePath = value.filePath.empty() ? nullptr : Utils::To(value.filePath).c_str();
		raw.fileSize = value.fileSize;
		raw.level = (agora::LOG_LEVEL)value.level;
		return raw;
	}
}