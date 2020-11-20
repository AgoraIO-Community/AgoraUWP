#include "pch.h"
#include "Packet.h"
#include "Packet.g.cpp"

namespace winrt::AgoraWinRT::implementation
{
    Packet::Packet() :
        m_buffer(com_array<uint8_t>())
    {
    }
    Packet::~Packet()
    {
        Close();
    }
    com_array<uint8_t> Packet::buffer()
    {
        return com_array(m_buffer.begin(), m_buffer.end());
    }
    void Packet::buffer(array_view<uint8_t const> value)
    {
        m_buffer.clear();
        m_buffer = com_array(value.begin(), value.end());
    }
    void Packet::Close()
    {
        m_buffer.clear();
    }
}
