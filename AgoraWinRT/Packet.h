#pragma once
#include "Packet.g.h"

namespace winrt::AgoraWinRT::implementation
{
    struct Packet : PacketT<Packet>
    {
        Packet();
        ~Packet();

        com_array<uint8_t> buffer();
        void buffer(array_view<uint8_t const> value);
        void Close();
    private:
        com_array<uint8_t> m_buffer;
    };
}
