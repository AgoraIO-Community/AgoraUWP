#pragma once
#include "EncryptionConfig.g.h"

namespace winrt::AgoraWinRT::implementation
{
    struct EncryptionConfig : EncryptionConfigT<EncryptionConfig>
    {
        EncryptionConfig();
        ~EncryptionConfig();

        AgoraWinRT::ENCRYPTION_MODE mode();
        void mode(AgoraWinRT::ENCRYPTION_MODE const& value);
        hstring key();
        void key(hstring const& value);
        com_array<uint8_t> salt();
        void salt(array_view<uint8_t const> value);
        void Close();
    private:
        AgoraWinRT::ENCRYPTION_MODE m_mode;
        hstring m_key;
        com_array<uint8_t> m_salt;
    };
}
