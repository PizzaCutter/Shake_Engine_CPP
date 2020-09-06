#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// ------------- DEBUG ----------------
#include "Shake/Core/Log.h"
#include "Shake/Debug/Asserts.h"

// ------------- PROFILING ------------
#include "Shake/Debug/Instrumentor.h"

#ifdef SE_PLATFORM_WINDOWS
    #include <Windows.h>
#endif


