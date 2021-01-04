#include "pch.h"
#include "ClientRoleOptions.h"
#include "ClientRoleOptions.g.cpp"

namespace winrt::AgoraWinRT::implementation
{
    AgoraWinRT::AUDIENCE_LATENCY_LEVEL_TYPE ClientRoleOptions::audienceLatencyLevel()
    {
        return m_audienceLatencyLevel;
    }
    void ClientRoleOptions::audienceLatencyLevel(AgoraWinRT::AUDIENCE_LATENCY_LEVEL_TYPE const& value)
    {
        m_audienceLatencyLevel = value;
    }
}
