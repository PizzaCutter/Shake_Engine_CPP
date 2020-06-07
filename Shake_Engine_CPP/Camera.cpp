#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(int screenWidth, int screenHeight)
{
    lastXPosition = screenWidth / 2.0f;
    lastYPosition = screenHeight / 2.0f;
}

void Camera::ProcessInput(EMovementInput input, float deltaTime)
{
    float deltaSpeed = cameraSpeed * deltaTime;
    if(input == EMovementInput::Forward)
    {
        position += deltaSpeed * frontVector;
    }
    if(input == EMovementInput::Backwards)
    {
        position -= deltaSpeed * frontVector;
    }
    if(input == EMovementInput::Right)
    {
        position += deltaSpeed * glm::normalize(glm::cross(frontVector, upVector));
    }
    if(input == EMovementInput::Left)
    {
        position -= deltaSpeed * glm::normalize(glm::cross(frontVector, upVector));
    }
}

void Camera::ProcessMouseInput(double newXPos, double newYPos)
{
    float xOffset = newXPos - lastXPosition;
    float yOffset = lastYPosition - newYPos;
    lastXPosition = newXPos;
    lastYPosition = newYPos;

    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if(pitch > 89.0f)
    {
        pitch = 89.0f;
    }
    if(pitch < -89.0f)
    {
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    frontVector = glm::normalize(front);
}

void Camera::ProcessScrollInput(double xOffset, double yOffset)
{
    if(yOffset > 0.01f)
    {
        cameraSpeed += cameraSpeedIncrement;
    }
    if(yOffset < 0.01f)
    {
        cameraSpeed -= cameraSpeedIncrement;
    }

    if(cameraSpeed <= 0.0f)
    {
        cameraSpeed = cameraSpeedIncrement;
    }
}

glm::mat4 Camera::GetViewMatrix()
{
   return glm::lookAt(position, position + frontVector, upVector); 
}

