#pragma once
#include "Shake/Math/SMath.h"


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
        TransformComponent(const std::string& inData)
        {
            // PARSE X LOCATION 
            const uint32_t positionXStartIndex = 1;
            const uint32_t positionXEndIndex = inData.find_first_of(",");

            // PARSE Y LOCATION
            uint32_t temp = positionXEndIndex;
            const uint32_t positionYStartIndex = inData.substr(temp).find_first_of(",") + temp + 1;
            temp = positionYStartIndex;
            const uint32_t positionYEndIndex = inData.substr(temp).find_first_of(",") + temp;

            // PARSE Z LOCATION
            temp = positionYEndIndex;
            const uint32_t positionZStartIndex = inData.substr(temp).find_first_of(",") + temp + 1;
            temp = positionZStartIndex;
            const uint32_t positionZEndIndex = inData.substr(temp).find_first_of("}") + temp;

            const std::string positionXAsString = inData.substr(positionXStartIndex, positionXEndIndex - positionXStartIndex);
            const std::string positionYAsString = inData.substr(positionYStartIndex, positionYEndIndex - positionYStartIndex);
            const std::string positionZAsString = inData.substr(positionZStartIndex, positionZEndIndex - positionZStartIndex);

            std::string::size_type sz;
            Position = SVector3(
                std::stof(positionXAsString, &sz), std::stof(positionYAsString, &sz), std::stof(positionZAsString, &sz)
            );

            // PARSING ROTATION
            temp = positionZEndIndex;
            const uint32_t rotationStartIndex = inData.substr(temp).find_first_of("{") + temp + 1;
            temp = rotationStartIndex;
            const uint32_t rotationEndIndex = inData.substr(rotationStartIndex + 1).find_first_of("}") + temp + 1;

            const std::string rotationAsString = inData.substr(rotationStartIndex, rotationEndIndex - rotationStartIndex);
            Rotation = std::stof(rotationAsString);


             // PARSE X SCALE 
            temp = rotationEndIndex;
            const uint32_t scaleXStartIndex = inData.substr(temp).find_first_of("{") + temp + 1;
            temp = scaleXStartIndex;
            const uint32_t scaleXEndIndex = inData.substr(temp).find_first_of(",") + temp;

            // PARSE Y LOCATION
            temp = scaleXEndIndex;
            const uint32_t scaleYStartIndex = inData.substr(temp).find_first_of(",") + temp + 1;
            temp = scaleYStartIndex;
            const uint32_t scaleYEndIndex= inData.substr(temp).find_first_of("}") + temp;

            const std::string scaleXAsString = inData.substr(scaleXStartIndex, scaleXEndIndex - scaleXStartIndex);
            const std::string scaleYAsString = inData.substr(scaleYStartIndex, scaleYEndIndex - scaleYStartIndex); 

            Scale = SVector2( std::stof(scaleXAsString), std::stof(scaleYAsString));
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
            serializedData += "{" + std::to_string(Position.x) + "," + std::to_string(Position.y) + "," + std::to_string(Position.z) + "}";
            serializedData += "{" + std::to_string(Rotation) + "}";
            serializedData += "{" + std::to_string(Scale.x) + "," + std::to_string(Scale.y) + "}}";
            return serializedData;
        }

    };
}
