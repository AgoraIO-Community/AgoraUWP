#pragma once
#include "Metadata.g.h"

namespace winrt::AgoraWinRT::implementation
{
    struct Metadata : MetadataT<Metadata>
    {
        Metadata();
        ~Metadata();
        void Close();

        uint64_t uid();
        void uid(uint64_t value);
        com_array<uint8_t> buffer();
        void buffer(array_view<uint8_t const> value);
        int64_t timestamp();
        void timestamp(int64_t value);
    private:
        uint64_t m_uid;
        com_array<uint8_t> m_buffer;
        int64_t m_timestamp;
    };
}
