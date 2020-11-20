#include "pch.h"
#include "ChannelMediaRelayConfiguration.h"
#include "ChannelMediaRelayConfiguration.g.cpp"

namespace winrt::AgoraWinRT::implementation
{
    ChannelMediaRelayConfiguration::ChannelMediaRelayConfiguration() :
        m_dest(winrt::com_array<AgoraWinRT::ChannelMediaInfo>())
    {}

    ChannelMediaRelayConfiguration::~ChannelMediaRelayConfiguration()
    {
        Close();
    }

    AgoraWinRT::ChannelMediaInfo ChannelMediaRelayConfiguration::src()
    {
        return m_src;
    }
    void ChannelMediaRelayConfiguration::src(AgoraWinRT::ChannelMediaInfo const& value)
    {
        m_src = value;
    }
    com_array<AgoraWinRT::ChannelMediaInfo> ChannelMediaRelayConfiguration::dest()
    {
        return com_array(m_dest.begin(), m_dest.end());
    }
    void ChannelMediaRelayConfiguration::dest(array_view<AgoraWinRT::ChannelMediaInfo const> value)
    {
        m_dest.clear();
        m_dest = com_array(value.begin(), value.end());
    }
    void ChannelMediaRelayConfiguration::Close()
    {
        m_dest.clear();
    }
}
