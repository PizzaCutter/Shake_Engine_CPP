#pragma once
#include "Shake.h"
#include "Shake/Renderer/Camera/OrthographicCameraController.h"

namespace Shake {
    class VertexArray;
    class Texture2D;
}

class BaseLayer : public Shake::Layer
{
public:
    BaseLayer();
    ~BaseLayer() override;
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(Shake::Timestep timeStep) override;
    void OnImGuiRender() override;
    void OnEvent(Shake::Event& event) override;

private:
    Shake::OrthographicCameraController m_orthoCameraController;

    float m_playerMovementSpeed = 5.0f;
    SVector3 m_playerPosition;
    SVector3 m_editableColor;

    Shake::ShaderLibrary m_shaderLibrary;
    Shake::Ref<Shake::Texture2D> m_Texture;
    Shake::Ref<Shake::Texture2D> m_TransparentTexture;
    Shake::Ref<Shake::VertexArray> m_vertexArray;
 
};
