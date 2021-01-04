#pragma once
#include "ClientRoleOptions.g.h"

namespace winrt::AgoraWinRT::implementation
{
    struct ClientRoleOptions : ClientRoleOptionsT<ClientRoleOptions>
    {
        ClientRoleOptions() = default;

        AgoraWinRT::AUDIENCE_LATENCY_LEVEL_TYPE audienceLatencyLevel();
        void audienceLatencyLevel(AgoraWinRT::AUDIENCE_LATENCY_LEVEL_TYPE const& value);

    private:
        AgoraWinRT::AUDIENCE_LATENCY_LEVEL_TYPE m_audienceLatencyLevel = AgoraWinRT::AUDIENCE_LATENCY_LEVEL_TYPE::AUDIENCE_LATENCY_LEVEL_LOW_LATENCY;

    };
}
