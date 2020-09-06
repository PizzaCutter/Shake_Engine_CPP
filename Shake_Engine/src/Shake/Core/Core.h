#pragma once

#ifdef SE_PLATFORM_WINDOWS
#else
    #error Shake_Engine only supports windows!
#endif

#define BIT(x) (1 << x)

#include "Shake/Core/Pointer.h"

#define BIND_EVENT(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); } 