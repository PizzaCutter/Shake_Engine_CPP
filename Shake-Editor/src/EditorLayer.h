#pragma once
#include "Shake.h"
#include "Shake/Renderer/Textures/SubTexture2D.h"
#include "Shake/Renderer/Camera/OrthographicCameraController.h"
#include "Shake/Scene/Entities/Entity.h"
#include "Panels/SceneHierarchyPanel.h"

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

    SharedPtr<Texture2D> m_TestTexture;
    SharedPtr<Texture2D> m_SpriteSheet;
    SharedPtr<SubTexture2D> m_SubTextureTest;
    SharedPtr<FrameBuffer> m_frameBuffer;

    SharedPtr<Scene> m_scene;
    Entity m_cameraEntity;

    SVector2 m_viewportSize = SVector2(0.0f, 0.0f);
    bool m_viewportFocused = false;
    bool m_viewportHovered = false;

    SVector4 m_editableColor;

    float m_rotation = 0.0f;

    SceneHierarchyPanel m_sceneHierarchyPanel;
};
}
