#pragma once

#pragma warning(disable:4996)

#include <unknwn.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include "../agorasdk/include/AgoraBase.h"
#include "../agorasdk/include/IAgoraMediaEngine.h"
#include "../agorasdk/include/IAgoraRtcEngine.h"
#include "../agorasdk/include/IAgoraService.h"
#include "../agorasdk/include/IAgoraRtcChannel.h"

#pragma comment(lib, "../agorasdk/x86/agora_rtc_sdk.lib")

#define MAX_ID_STRING 512