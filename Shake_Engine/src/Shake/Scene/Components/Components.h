#pragma once
#include "Shake/Scene/Cameras/SceneCamera.h"
#include "Shake/Scene/Entities/ScriptableEntity.h"
#include "Shake/Math/SMath.h"

namespace Shake
{
    struct TransformComponent 
    {
    public:
        SMat4 Transform {SMat4(1.0f)};

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const SMat4& transform) : Transform(transform) {};

        operator SMat4&() { return Transform; }
        operator const SMat4&() const { return Transform; }
    };

    struct SpriteComponent
    {
    public:
        SVector4 Color{1.0f, 1.0f, 1.0f, 1.0f};

        SpriteComponent() = default;
        SpriteComponent(const SpriteComponent&) = default;
        SpriteComponent(const SVector4& color) : Color(color) {}
    };

    struct CameraComponent
    {
        SceneCamera Camera;
        bool Primary = false;
        bool FixedAspectRatio = false;

        CameraComponent() = default;
        CameraComponent(const CameraComponent&) = default;
    };

    struct NativeScriptComponent
    {
        ScriptableEntity* Instance = nullptr;


        void InstantiateFunction();

        // FUNCTION POINTERS
        ScriptableEntity*(*InstantiateScript)();
        void (*DestroyScript)(NativeScriptComponent*);
        
        template <typename T>
        void Bind()
        {
            InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
            DestroyScript = [](NativeScriptComponent* nsc)
            {
                delete nsc->Instance;
                nsc->Instance = nullptr;
            };
       }
    };
}
