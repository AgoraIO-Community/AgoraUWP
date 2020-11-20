#pragma once
#include "pch.h"
#include "VideoSourceConsumer.g.h"

namespace winrt::AgoraWinRT::implementation
{
    struct VideoSourceConsumer : VideoSourceConsumerT<VideoSourceConsumer>
    {
        VideoSourceConsumer() = default;
        VideoSourceConsumer(agora::rtc::IVideoFrameConsumer* consumer);

        ~VideoSourceConsumer();

        void ConsumeRawVideoFrame(array_view<uint8_t const> buffer, AgoraWinRT::VIDEO_PIXEL_FORMAT const& type, uint32_t width, uint32_t height, uint16_t rotation, uint64_t timestamp);
    private:
        agora::rtc::IVideoFrameConsumer* m_consumer{ nullptr };
        void* preData{ nullptr };
    };
}
