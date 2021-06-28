#pragma once

#pragma warning(disable:4996)

#include <unknwn.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include "../agorasdk/include/AgoraBase.h"
#include "../agorasdk/include/AgoraRtcCryptoCppLoader.h"
#include "../agorasdk/include/IAgoraLog.h"
#include "../agorasdk/include/IAgoraMediaEngine.h"
#include "../agorasdk/include/IAgoraRtcEngine.h"
#include "../agorasdk/include/IAgoraService.h"
#include "../agorasdk/include/IAgoraRtcChannel.h"

#pragma comment(lib, "../agorasdk/x86_64/agora_rtc_sdk.lib")
#pragma comment(lib, "../agorasdk/x86_64/libagora_segmentation_extension.lib")

#define MAX_ID_STRING 512