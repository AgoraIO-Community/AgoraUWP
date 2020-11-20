#include "pch.h"
#include "Metadata.h"
#include "Metadata.g.cpp"

namespace winrt::AgoraWinRT::implementation
{
    Metadata::Metadata() :
        m_buffer(com_array<uint8_t>()),
        m_uid(0),
        m_timestamp(0)
    {
    }
    Metadata::~Metadata()
    {
        Close();
    }
    void Metadata::Close()
    {
        m_buffer.clear();
    }
    uint64_t Metadata::uid()
    {
        return m_uid;
    }
    void Metadata::uid(uint64_t value)
    {
        m_uid = value;
    }
    com_array<uint8_t> Metadata::buffer()
    {
        return com_array(m_buffer.begin(), m_buffer.end());
    }
    void Metadata::buffer(array_view<uint8_t const> value)
    {
        m_buffer.clear();
        m_buffer = com_array(value.begin(), value.end());
    }
    int64_t Metadata::timestamp()
    {
        return m_timestamp;
    }
    void Metadata::timestamp(int64_t value)
    {
        m_timestamp = value;
    }
}
