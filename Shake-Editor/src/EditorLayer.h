#pragma once
#include "Shake.h"
#include "Shake/Renderer/SubTexture2D.h"
#include "Shake/Renderer/Camera/OrthographicCameraController.h"

namespace Shake {
    class Scene;
    class FrameBuffer;
    class VertexArray;
    class Texture2D;

class EditorLayer : public Layer
{
public:
    EditorLayer();
    ~EditorLayer() override;
    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate(Timestep timeStep) override;
    void OnImGuiRender() override;
    void OnEvent(Event& event) override;

private:
    OrthographicCameraController m_orthoCameraController;

    Ref<Texture2D> m_TestTexture;
    Ref<Texture2D> m_SpriteSheet;
    Ref<SubTexture2D> m_SubTextureTest;
    Ref<FrameBuffer> m_frameBuffer;

    Ref<Scene> m_scene;

    SVector2 m_viewportSize = SVector2(0.0f, 0.0f);
    bool m_viewportFocused = false;
    bool m_viewportHovered = false;

    SVector4 m_editableColor;

    float m_rotation = 0.0f;
};
}
