#pragma once
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

enum EMovementInput
{
    Forward,
    Backwards,
    Left,
    Right
};

class Camera
{
public:
    Camera(int screenWidth, int screenHeight);
    
    void ProcessInput(EMovementInput input, float deltaTime);
    void ProcessMouseInput(double newXPos, double newYPos);
    void ProcessScrollInput(double xOffset, double yOffset);

    glm::mat4 GetViewMatrix();
    float GetFOV() const { return fov; }
private:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 frontVector = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

    bool firstMouse = true;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float fov = 45.0f;

    // SHOULD USE SCREEN WIDTH AND HEIGHT INSTEAD OF HARDCODED
    float lastXPosition = 800.0f / 2.0f;
    float lastYPosition = 600.0f / 2.0f;

    float cameraSpeed = 2.5f;
    float cameraSpeedIncrement = 0.1f;

    
    float mouseSensitivity = 0.1f;
    
};
