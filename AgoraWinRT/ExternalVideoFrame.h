#pragma once
#include "ExternalVideoFrame.g.h"

namespace winrt::AgoraWinRT::implementation
{
    struct ExternalVideoFrame : ExternalVideoFrameT<ExternalVideoFrame>
    {
        ExternalVideoFrame() = default;

        ~ExternalVideoFrame();

        AgoraWinRT::VIDEO_BUFFER_TYPE type();
        void type(AgoraWinRT::VIDEO_BUFFER_TYPE const& value);
        AgoraWinRT::VIDEO_PIXEL_FORMAT format();
        void format(AgoraWinRT::VIDEO_PIXEL_FORMAT const& value);
        com_array<uint8_t> buffer();
        void buffer(array_view<uint8_t const> value);
        uint32_t stride();
        void stride(uint32_t value);
        uint32_t height();
        void height(uint32_t value);
        uint32_t cropLeft();
        void cropLeft(uint32_t value);
        uint32_t cropTop();
        void cropTop(uint32_t value);
        uint32_t cropRight();
        void cropRight(uint32_t value);
        uint32_t cropBottom();
        void cropBottom(uint32_t value);
        uint16_t rotation();
        void rotation(uint16_t value);
        int64_t timestamp();
        void timestamp(int64_t value);
        void Close();

    private:
        AgoraWinRT::VIDEO_BUFFER_TYPE m_type;
        AgoraWinRT::VIDEO_PIXEL_FORMAT m_format;
        com_array<uint8_t> m_buffer = com_array<uint8_t>();
        uint32_t m_stride;
        uint32_t m_height;
        uint32_t m_cropLeft;
        uint32_t m_cropTop;
        uint32_t m_cropRight;
        uint32_t m_cropBottom;
        uint16_t m_rotation;
        int64_t m_timestamp;
    };
}
namespace winrt::AgoraWinRT::factory_implementation
{
    struct ExternalVideoFrame : ExternalVideoFrameT<ExternalVideoFrame, implementation::ExternalVideoFrame>
    {

    };
}
