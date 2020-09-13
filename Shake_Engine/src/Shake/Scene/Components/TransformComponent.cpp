#include "sepch.h"
#include "TransformComponent.h"

namespace Shake
{
    void TransformComponent::SetPosition(glm::vec3 newPosition)
    {
        Position = newPosition;
        UpdateMatrix();
    }

    void TransformComponent::SetRotation(float newRotation)
    {
        Rotation = newRotation;
        UpdateMatrix();
    }

    void TransformComponent::SetScale(glm::vec2 newScale)
    {
        Scale = newScale;
        UpdateMatrix();
    }

    glm::vec3 TransformComponent::GetPosition() const
    {
        return Position;
    }

    float TransformComponent::GetRotation() const
    {
        return Rotation;
    }

    glm::vec2 TransformComponent::GetScale() const
    {
        return Scale;
    }

    void TransformComponent::AddPosition(glm::vec3 addedPosition)
    {
        SetPosition(Position + addedPosition);
    }

    void TransformComponent::AddRotation(float addedRotation)
    {
        SetRotation(Rotation + addedRotation);
    }

    void TransformComponent::UpdateMatrix()
    {
        Transform = SMath::Translate(SMat4(1.0f), Position)
            * SMath::Rotate(SMat4(1.0f), Rotation, SVector3(0.0f, 0.0f, 1.0f))
            * SMath::Scale(SMat4(1.0f), {Scale.x, Scale.y, 1.0f});
    }
}
