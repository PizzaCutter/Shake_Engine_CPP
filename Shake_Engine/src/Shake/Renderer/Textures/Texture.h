#pragma once
#include "Shake/Core/Core.h"

namespace Shake
{
    class Texture
    {
    public:
        virtual ~Texture() = default;
        
        virtual int32_t GetWidth() const = 0;
        virtual int32_t GetHeight() const = 0;

        virtual void SetData(void* data, int32_t size) = 0;
        virtual void Bind(int32_t slot = 0) = 0;

        virtual bool operator==(const Texture& other) = 0;
    };

    class Texture2D : public Texture
    {
    public:
        virtual ~Texture2D() = default;

        virtual uint32_t GetRendererID() const = 0;

        static SharedPtr<Texture2D> Create(uint32_t width, uint32_t height);
        static SharedPtr<Texture2D> Create(const SString& path);
    };
}
