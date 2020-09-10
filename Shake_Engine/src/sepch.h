#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Shake/Core/Utils/Pointer.h"

// ------------- STRINGS ------------
#include "Shake/Strings/SString.h"

#include "Shake/Core/Utils/Timestep.h"

// ------------- DEBUG ----------------
#include "Shake/Debug/Log.h"
#include "Shake/Debug/Asserts.h"

// ------------- PROFILING ------------
#include "Shake/Debug/Instrumentor.h"

#ifdef SE_PLATFORM_WINDOWS
    #include <Windows.h>
#endif


