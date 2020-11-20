#include "pch.h"
#include "VideoFrame.h"
#include "VideoFrame.g.cpp"

namespace winrt::AgoraWinRT::implementation
{

    VideoFrame::~VideoFrame()
    {
        Close();
    }
    bool VideoFrame::BeModified()
    {
        return m_beModified;
    }
    void VideoFrame::BeModified(bool value)
    {
        m_beModified = value;
    }
    AgoraWinRT::VIDEO_FRAME_TYPE VideoFrame::type()
    {
        return m_type;
    }
    void VideoFrame::type(AgoraWinRT::VIDEO_FRAME_TYPE const& value)
    {
        m_type = value;
    }
    uint32_t VideoFrame::width()
    {
        return m_width;
    }
    void VideoFrame::width(uint32_t value)
    {
        m_width = value;
    }
    uint32_t VideoFrame::height()
    {
        return m_height;
    }
    void VideoFrame::height(uint32_t value)
    {
        m_height = value;
    }
    uint32_t VideoFrame::yStride()
    {
        return m_yStride;
    }
    void VideoFrame::yStride(uint32_t value)
    {
        m_yStride = value;
    }
    uint32_t VideoFrame::uStride()
    {
        return m_uStride;
    }
    void VideoFrame::uStride(uint32_t value)
    {
        m_uStride = value;
    }
    uint32_t VideoFrame::vStride()
    {
        return m_vStride;
    }
    void VideoFrame::vStride(uint32_t value)
    {
        m_vStride = value;
    }
    com_array<uint8_t> VideoFrame::yBuffer()
    {
        return com_array(m_yBuffer.begin(), m_yBuffer.end());
    }
    void VideoFrame::yBuffer(array_view<uint8_t const> value)
    {
        m_yBuffer.clear();
        m_yBuffer = com_array(value.begin(), value.end());
    }
    com_array<uint8_t> VideoFrame::uBuffer()
    {
        return com_array(m_uBuffer.begin(), m_uBuffer.end());
    }
    void VideoFrame::uBuffer(array_view<uint8_t const> value)
    {
        m_uBuffer.clear();
        m_uBuffer = com_array(value.begin(), value.end());
    }
    com_array<uint8_t> VideoFrame::vBuffer()
    {
        return com_array(m_vBuffer.begin(), m_vBuffer.end());
    }
    void VideoFrame::vBuffer(array_view<uint8_t const> value)
    {
        m_vBuffer.clear();
        m_vBuffer = com_array(value.begin(), value.end());
    }
    uint16_t VideoFrame::rotation()
    {
        return m_rotation;
    }
    void VideoFrame::rotation(uint16_t value)
    {
        m_rotation = value;
    }
    int64_t VideoFrame::renderTimeMs()
    {
        return m_renderTimeMs;
    }
    void VideoFrame::renderTimeMs(int64_t value)
    {
        m_renderTimeMs = value;
    }
    int64_t VideoFrame::avsync_type()
    {
        return m_avsync_type;
    }
    void VideoFrame::avsync_type(int64_t value)
    {
        m_avsync_type = value;
    }
    void VideoFrame::Close()
    {
        m_yBuffer.clear();
        m_uBuffer.clear();
        m_vBuffer.clear();
    }
}
