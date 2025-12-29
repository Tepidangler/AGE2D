#pragma once

#include <iostream>
#include <functional>
#include <memory>
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <variant>
#include <optional>
#include <set>
#include <any>
#include <atomic>
#include <execution>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <tuple>
#include <stdlib.h>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#ifdef AG_PLATFORM_WINDOWS
#include <ppltasks.h>
#endif


#include "Log.h"
#include "Core.h"
#include "Debug/Public/Instrumentor.h"

//#include <src/tmx.h>


#ifdef AG_PLATFORM_WINDOWS
	#include <Windows.h>
	#include <commdlg.h>
	#include <x3daudio.h>
	#include <Xinput.h>
	#include <wrl/client.h>


#endif


#ifdef AK_WIN
	#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
	#define _WIN32_WINNT 0x0A00	// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
	#endif

	// Windows Header Files:
//	#include <windows.h>
#endif

