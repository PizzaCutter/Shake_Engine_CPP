#pragma once
#include "Shake.h"
#include "imgui/imgui.h"
#include "Shake/Renderer/Textures/SubTexture2D.h"
#include "Shake/Renderer/Camera/OrthographicCameraController.h"
#include "Shake/Scene/Entities/Entity.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/SceneStatsPanel.h"
#include "Shake/Events/KeyEvent.h"

#include "entityx/quick.h"
#include "entityx/System.h"

namespace ex = entityx;

namespace Shake
{
    class BasePanel;
    class Scene;
    class FrameBuffer;
    class VertexArray;
    class Texture2D;

    class SableLayer : public Layer
    {
    public:
        SableLayer();
        ~SableLayer() override;

        void OnAttach() override;
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

        SharedPtr<SceneX> m_testScene;

        SharedPtr<Texture2D> m_SpriteSheet;
        SharedPtr<SubTexture2D> m_SubTextureTest;

        SharedPtr<FrameBuffer> m_frameBuffer;
        SharedPtr<OrthographicCameraController> m_controller;
        SharedPtr<OrthographicCamera> m_orthoCameraController;

        SVector2 m_viewportSize = SVector2(0.0f, 0.0f);
        bool m_viewportFocused = false;
        bool m_viewportHovered = false;

        std::vector<SharedPtr<BasePanel>> m_editorPanels;

        bool m_isEditorHidden = true;
        bool m_recalculateViewportSize = true;

        // TRYING TO CREATE AN ACTION PANEL
        ImVec2 m_actionPanelLocation;
        bool m_actionPanelEnabled = false;
    };
}
