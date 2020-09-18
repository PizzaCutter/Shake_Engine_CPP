#pragma once
#include "Shake/Math/SMath.h"

namespace Shake
{
    struct SpriteComponent
    {
        SpriteComponent(const SVector4& color)
            : Color(color)
        {
            
        }
        
        SVector4 Color{1.0f, 1.0f, 1.0f, 1.0f};
    };
}