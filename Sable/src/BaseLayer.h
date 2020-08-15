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

    Shake::ShaderLibrary m_shaderLibrary;
    Shake::Ref<Shake::Texture2D> m_TestTexture;

    SVector4 m_editableColor;
};
