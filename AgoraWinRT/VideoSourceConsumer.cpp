#include "pch.h"
#include "VideoSourceConsumer.h"
#include "VideoSourceConsumer.g.cpp"
#include "Utils.h"

namespace winrt::AgoraWinRT::implementation
{
    VideoSourceConsumer::VideoSourceConsumer(agora::rtc::IVideoFrameConsumer* consumer): m_consumer(consumer)
    {
    }
    VideoSourceConsumer::~VideoSourceConsumer()
    {
        if (preData != nullptr) delete[] preData;
    }
    void VideoSourceConsumer::ConsumeRawVideoFrame(array_view<uint8_t const> buffer, AgoraWinRT::VIDEO_PIXEL_FORMAT const& type, uint32_t width, uint32_t height, uint16_t rotation, uint64_t timestamp)
    {
        if (preData != nullptr) delete[] preData;
        void* data = Utils::To(buffer);
        m_consumer->consumeRawVideoFrame(reinterpret_cast<unsigned char*>(data), agora::media::ExternalVideoFrame::VIDEO_PIXEL_FORMAT(type), width, height, rotation, timestamp);    
        preData = data;
    }
}
