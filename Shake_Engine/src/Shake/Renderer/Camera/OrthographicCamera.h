#pragma once
#include "glm/glm.hpp"
#include "Shake/Math/SMath.h"

namespace Shake
{
    class OrthographicCamera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        virtual ~OrthographicCamera() = default;
        
        void SetProjection(float left, float right, float bottom, float top);
        
        const SVector3 GetPosition() const { return m_position; }
        void SetPosition(const SVector3& position)
        {
            m_position = position;
            RecalculateViewMatrix();
        }
        
        const float GetRotation() const { return m_rotation; }
        void SetRotation(float rotation)
        {
            m_rotation = rotation;
            RecalculateViewMatrix();
        }

        const SMat4 GetProjectionMatrix() const { return m_projectionMatrix; }
        const SMat4 GetViewMatrix() const { return m_viewMatrix; }
        const SMat4 GetViewProjectionMatrix() const { return m_viewProjectionMatrix; }
    private:
        void RecalculateViewMatrix();
        
    private:
        SMat4 m_projectionMatrix;
        SMat4 m_viewMatrix;
        SMat4 m_viewProjectionMatrix;

        SVector3 m_position = SVector3(0.0f, 0.0f, 0.0f);
        // TODO[rsmekens]: use quaternion for rotation 
        float m_rotation = 0.0f;
    };
}
