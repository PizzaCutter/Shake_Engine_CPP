#pragma once
#include "Shake/Math/SMath.h"

namespace Shake
{
    struct TransformComponent 
    {
    public:
        SMat4 Transform {SMat4(1.0f)};
        SVector3 Position {SVector3()};
        float Rotation {0.0f};
        SVector2 Scale {SVector2(1.0f)};

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const SMat4& transform) : Transform(transform) {};

        void SetPosition(SVector3 newPosition);
        void SetRotation(float newRotation);
        void SetScale(SVector2 newScale);

        SVector3 GetPosition() const;
        float GetRotation() const;
        SVector2 GetScale() const;

        void AddPosition(SVector3 addedPosition);
        void AddRotation(float addedRotation);

        void UpdateMatrix();

        operator SMat4&() { return Transform; }
        operator const SMat4&() const { return Transform; }
    };
}
