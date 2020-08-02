#pragma once
#include "Shake/Core/Core.h"

namespace Shake
{
    class Texture
    {
    public:
        ~Texture() = default;
        
        virtual int32_t GetWidth() const = 0;
        virtual int32_t GetHeight() const = 0;

        virtual void Bind(int32_t slot = 0) = 0;
    };

    class Texture2D : public Texture
    {
    public:
        ~Texture2D() = default; 
    
        static Ref<Texture2D> Create(const std::string& path);
    };
}
