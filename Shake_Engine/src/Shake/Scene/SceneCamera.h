#pragma once
#include "Camera.h"

namespace Shake
{
    class SceneCamera : public Camera
    {
    public:
        SceneCamera();
        virtual ~SceneCamera() = default;

        void SetOrthographic(float size, float nearClip, float farClip);
        void SetViewportSize(uint32_t width, uint32_t height);
    private:
        void RecaluclateProjection();
        
        float m_orthographicSize = 10.0f;
        float m_orthographicNear = -1.0f;
        float m_orthographicFar = 1.0f;

        float m_aspectRatio = 0.0f;
    };
}
