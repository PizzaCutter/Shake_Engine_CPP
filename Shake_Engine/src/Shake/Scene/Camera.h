#pragma once
#include "Shake/Math/SMath.h"

namespace Shake
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(const SMat4& projection)
            : m_projection(projection)
        {
        
        }

        void UpdateViewProjection(SMat4 transform)
        {
            m_viewProjection = m_projection * transform;
        }

        const SMat4& GetProjection() { return m_projection; }
        const SMat4& GetViewProjection() { return m_viewProjection; }
    
    protected:
        SMat4 m_projection = SMat4(1.0f);
        SMat4 m_viewProjection = SMat4(1.0f);
    };
}
