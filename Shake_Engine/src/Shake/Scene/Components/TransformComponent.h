#pragma once
#include "Shake/Math/SMath.h"
#include "Shake/Serialization/SSerialize.h"


namespace Shake
{
    struct TransformComponent 
    {
        SMat4 Transform {SMat4(1.0f)};
        SVector3 Position {SVector3(0.0f)};
        float Rotation {0.0f};
        SVector2 Scale {SVector2(1.0f)};
    
        //TransformComponent() = default;
        //TransformComponent(const TransformComponent&) = default;
        //TransformComponent(const SMat4& transform) : Transform(transform) {};
        TransformComponent(const SVector3& position)
          : Position(position), Scale(SVector2(1.0f)), Rotation(0.0f) { }
        TransformComponent(const SVector3& position, const SVector2& scale)
            : Position(position), Scale(scale), Rotation(0.0f) { }
        TransformComponent(const SVector3& position, const float rotation, const SVector2& scale)
            : Position(position), Rotation(rotation), Scale(scale) { }
        TransformComponent(const std::vector<std::string>& inData)
        {
            Position = SVector3::Deserialize(inData[0]);
            Rotation = SSerialize::DeserializeFloat(inData[1]);
            Scale = SVector2::Deserialize(inData[2]);
            UpdateMatrix();
        }
    
    
        void SetPosition(SVector3 newPosition)
        {
            Position = newPosition;
            UpdateMatrix();
        }
        
        void SetRotation(float newRotation)
        {
            Rotation = newRotation;
            UpdateMatrix();
        }
        void SetScale(SVector2 newScale)
        {
            Scale = newScale;
            UpdateMatrix();
        }
        void SetPositionAndRotation(SVector3 newPosition, float newRotation)
        {
            Position = newPosition;
            Rotation = newRotation;
            UpdateMatrix();
        }
        
        SMat4 GetTransform() const { return Transform; };
        SVector3 GetPosition() const { return Position; };
        float GetRotation() const { return Rotation; };
        SVector2 GetScale() const { return Scale; };
        
        void AddPosition(SVector3 addedPosition)
        {
            SetPosition(Position + addedPosition); 
        }
        void AddRotation(float addedRotation)
        {
            SetRotation(Rotation + addedRotation);  
        }
        
        void UpdateMatrix()
        {
            Transform = SMath::Translate(SMat4(1.0f), Position)
                * SMath::Rotate(SMat4(1.0f), Rotation, SVector3(0.0f, 0.0f, 1.0f))
                * SMath::Scale(SMat4(1.0f), {Scale.x, Scale.y, 1.0f});
        }
    
        operator SMat4&() { return Transform; }
        operator const SMat4&() const { return Transform; }

        static std::string GetComponentName()
        {
            return "TransformComponent";
        }
        
        std::string serialize()
        {
            std::string serializedData = "[" + GetComponentName() + "]{";
            serializedData += Position.Serialize();
            serializedData += SSerialize::SerializeFloat(Rotation);
            serializedData += Scale.Serialize();
            serializedData += "}"; 
            return serializedData;
        }

    };
}
