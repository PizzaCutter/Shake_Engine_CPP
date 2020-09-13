#pragma once
#include "Shake.h"
#include "box2d/b2_world.h"
#include "imgui/imgui.h"
#include "Shake/Renderer/Textures/SubTexture2D.h"
#include "Shake/Renderer/Camera/OrthographicCameraController.h"
#include "Shake/Scene/Entities/Entity.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/SceneStatsPanel.h"
#include "Shake/Events/KeyEvent.h"

namespace Shake {
    class BasePanel;
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
    b2Body* CreatePhysicsBody(Entity entity);
    void OnDetach() override;
    void OnUpdate(Timestep timeStep) override;

    void OnImGuiRender() override;

    void OnEvent(Event& event) override;
    bool OnWindowResizeCallback(const WindowResizeEvent& eventData);
    bool OnMouseButtonPressedCallback(const MouseButtonPressedEvent& eventData);
    bool OnKeyPressedCallback(const KeyPressedEvent& eventData);
    void OnResizeViewport(uint32_t width, uint32_t height);

private:
    void ImGuiSetupDockspace();
    void ImGuiCloseDockSpace();
    void ViewportPanel();
    
    void AddObject();
    void SaveScene();

    //OrthographicCameraController m_orthoCameraController;

    SharedPtr<Texture2D> m_TestTexture;
    SharedPtr<Texture2D> m_SpriteSheet;
    SharedPtr<SubTexture2D> m_SubTextureTest;
    
    SharedPtr<FrameBuffer> m_frameBuffer;

    SharedPtr<Scene> m_scene;
    Entity m_cameraEntity;
    Entity m_playerEntity;
    std::vector<Entity> m_testEntities;
    std::vector<b2Body*> m_testPhysicEntities;

    SVector2 m_viewportSize = SVector2(0.0f, 0.0f);
    bool m_viewportFocused = false;
    bool m_viewportHovered = false;

    SVector4 m_editableColor;

    float m_rotation = 0.0f;

    std::vector<SharedPtr<BasePanel>> m_editorPanels;

    bool m_simulatePhysics = false;
    
    bool m_isEditorHidden = true;
    bool m_recalculateViewportSize = true;

    // TRYING TO CREATE AN ACTION PANEL
    ImVec2 m_actionPanelLocation;
    bool m_actionPanelEnabled = false;
    bool m_triggeredSave = false;

    std::unique_ptr<b2World> m_world;
    b2Body* dynamicBodyTest = nullptr;
};
    
}
