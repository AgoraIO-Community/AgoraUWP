#include "pch.h"
#include "ExternalVideoFrame.h"
#include "ExternalVideoFrame.g.cpp"

namespace winrt::AgoraWinRT::implementation
{
	ExternalVideoFrame::~ExternalVideoFrame()
	{
		Close();
	}
	AgoraWinRT::VIDEO_BUFFER_TYPE ExternalVideoFrame::type()
	{
		return m_type;
	}
	void ExternalVideoFrame::type(AgoraWinRT::VIDEO_BUFFER_TYPE const& value)
	{
		m_type = value;
	}
	AgoraWinRT::VIDEO_PIXEL_FORMAT ExternalVideoFrame::format()
	{
		return m_format;
	}
	void ExternalVideoFrame::format(AgoraWinRT::VIDEO_PIXEL_FORMAT const& value)
	{
		m_format = value;
	}
	com_array<uint8_t> ExternalVideoFrame::buffer()
	{
		return com_array(m_buffer.begin(), m_buffer.end());
	}
	void ExternalVideoFrame::buffer(array_view<uint8_t const> value)
	{
		m_buffer.clear();
		m_buffer = com_array(value.begin(), value.end());
	}
	uint32_t ExternalVideoFrame::stride()
	{
		return m_stride;
	}
	void ExternalVideoFrame::stride(uint32_t value)
	{
		m_stride = value;
	}
	uint32_t ExternalVideoFrame::height()
	{
		return m_height;
	}
	void ExternalVideoFrame::height(uint32_t value)
	{
		m_height = value;
	}
	uint32_t ExternalVideoFrame::cropLeft()
	{
		return m_cropLeft;
	}
	void ExternalVideoFrame::cropLeft(uint32_t value)
	{
		m_cropLeft = value;
	}
	uint32_t ExternalVideoFrame::cropTop()
	{
		return m_cropTop;
	}
	void ExternalVideoFrame::cropTop(uint32_t value)
	{
		m_cropTop = value;
	}
	uint32_t ExternalVideoFrame::cropRight()
	{
		return m_cropRight;
	}
	void ExternalVideoFrame::cropRight(uint32_t value)
	{
		m_cropRight = value;
	}
	uint32_t ExternalVideoFrame::cropBottom()
	{
		return m_cropBottom;
	}
	void ExternalVideoFrame::cropBottom(uint32_t value)
	{
		m_cropBottom = value;
	}
	uint16_t ExternalVideoFrame::rotation()
	{
		return m_rotation;
	}
	void ExternalVideoFrame::rotation(uint16_t value)
	{
		m_rotation = value;
	}
	int64_t ExternalVideoFrame::timestamp()
	{
		return m_timestamp;
	}
	void ExternalVideoFrame::timestamp(int64_t value)
	{
		m_timestamp = value;
	}
	void ExternalVideoFrame::Close()
	{
		m_buffer.clear();
	}
}
