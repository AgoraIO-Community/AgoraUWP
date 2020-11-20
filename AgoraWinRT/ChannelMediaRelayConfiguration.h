#pragma once
#include "ChannelMediaRelayConfiguration.g.h"

namespace winrt::AgoraWinRT::implementation
{
    struct ChannelMediaRelayConfiguration : ChannelMediaRelayConfigurationT<ChannelMediaRelayConfiguration>
    {
        ChannelMediaRelayConfiguration();

        ~ChannelMediaRelayConfiguration();

        AgoraWinRT::ChannelMediaInfo src();
        void src(AgoraWinRT::ChannelMediaInfo const& value);
        com_array<AgoraWinRT::ChannelMediaInfo> dest();
        void dest(array_view<AgoraWinRT::ChannelMediaInfo const> value);
        void Close();
    private:
        AgoraWinRT::ChannelMediaInfo m_src;
        com_array<AgoraWinRT::ChannelMediaInfo> m_dest;
    };
}
