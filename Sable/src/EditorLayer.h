#pragma once
#include "Shake.h"
#include "Shake/Renderer/SubTexture2D.h"
#include "Shake/Renderer/Camera/OrthographicCameraController.h"

namespace Shake {
    class FrameBuffer;
    class VertexArray;
    class Texture2D;
}

class EditorLayer : public Shake::Layer
{
public:
    EditorLayer();
    ~EditorLayer() override;
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(Shake::Timestep timeStep) override;
    void OnImGuiRender() override;
    void OnEvent(Shake::Event& event) override;

private:
    Shake::OrthographicCameraController m_orthoCameraController;

    Shake::ShaderLibrary m_shaderLibrary;
    Shake::Ref<Shake::Texture2D> m_TestTexture;
    Shake::Ref<Shake::Texture2D> m_SpriteSheet;
    Shake::Ref<Shake::SubTexture2D> m_SubTextureTest;

    SVector4 m_editableColor;

    float m_rotation = 0.0f;
};
