#pragma once
#include "VideoFrame.g.h"

namespace winrt::AgoraWinRT::implementation
{
    struct VideoFrame : VideoFrameT<VideoFrame>
    {
        VideoFrame() = default;
        ~VideoFrame();

        bool BeModified();
        void BeModified(bool value);
        AgoraWinRT::VIDEO_FRAME_TYPE type();
        void type(AgoraWinRT::VIDEO_FRAME_TYPE const& value);
        uint32_t width();
        void width(uint32_t value);
        uint32_t height();
        void height(uint32_t value);
        uint32_t yStride();
        void yStride(uint32_t value);
        uint32_t uStride();
        void uStride(uint32_t value);
        uint32_t vStride();
        void vStride(uint32_t value);
        com_array<uint8_t> yBuffer();
        void yBuffer(array_view<uint8_t const> value);
        com_array<uint8_t> uBuffer();
        void uBuffer(array_view<uint8_t const> value);
        com_array<uint8_t> vBuffer();
        void vBuffer(array_view<uint8_t const> value);
        uint16_t rotation();
        void rotation(uint16_t value);
        int64_t renderTimeMs();
        void renderTimeMs(int64_t value);
        int64_t avsync_type();
        void avsync_type(int64_t value);
        void Close();
    private:
        bool m_beModified = false;
        AgoraWinRT::VIDEO_FRAME_TYPE m_type;
        uint32_t m_width;
        uint32_t m_height;
        uint32_t m_yStride;
        uint32_t m_uStride;
        uint32_t m_vStride;
        com_array<uint8_t> m_yBuffer = com_array<uint8_t>();
        com_array<uint8_t> m_uBuffer = com_array<uint8_t>();
        com_array<uint8_t> m_vBuffer = com_array<uint8_t>();
        uint16_t m_rotation;
        int64_t m_renderTimeMs;
        int64_t m_avsync_type;
    };
}
