#include "sepch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include "Shake/Math/SMath.h"

namespace Shake
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
    {
        m_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        m_viewMatrix = glm::identity<glm::mat4>();
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;

        RecalculateViewMatrix();
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        SMat4 transform = SMath::Translate(SMat4(1.0f), m_position) * SMath::Rotate(SMat4(1.0f), glm::radians(m_rotation), SVector3(0,0,1));
        
        m_viewMatrix = glm::inverse(transform);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
}

