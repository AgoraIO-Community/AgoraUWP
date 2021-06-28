#include "pch.h"
#include "EncryptionConfig.h"
#include "EncryptionConfig.g.cpp"

namespace winrt::AgoraWinRT::implementation
{
    EncryptionConfig::EncryptionConfig() :
        m_mode(AgoraWinRT::ENCRYPTION_MODE::AES_128_GCM2),
        m_salt(winrt::com_array<uint8_t>())
    {}

    EncryptionConfig::~EncryptionConfig()
    {
        Close();
    }

    AgoraWinRT::ENCRYPTION_MODE EncryptionConfig::mode()
    {
        return m_mode;
    }
    void EncryptionConfig::mode(AgoraWinRT::ENCRYPTION_MODE const& value)
    {
        m_mode = value;
    }
    hstring EncryptionConfig::key()
    {
        return m_key;
    }
    void EncryptionConfig::key(hstring const& value)
    {
        m_key = value;
    }
    com_array<uint8_t> EncryptionConfig::salt()
    {
        return com_array(m_salt.begin(), m_salt.end());
    }
    void EncryptionConfig::salt(array_view<uint8_t const> value)
    {
        m_salt.clear();
        m_salt = com_array(value.begin(), value.end());
    }
    void EncryptionConfig::Close()
    {
        m_salt.clear();
    }
}
