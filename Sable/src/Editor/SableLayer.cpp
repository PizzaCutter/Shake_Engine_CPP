#include "sepch.h"
#include "SableLayer.h"

#include <algorithm>

#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"
#include "Panels/MenuBarPanel.h"
#include "Shake/Events/KeyEvent.h"
#include "Shake/Renderer/Buffers/FrameBuffer.h"
#include "Shake/Scene/Entities/Entity.h"

namespace ex = entityx;

namespace Shake
{

    
    SableLayer::SableLayer() : Layer("EditorLayer")
    {
        m_SpriteSheet = Texture2D::Create("Content/Game/Textures/industrial.v2.png");
        m_SubTextureTest = SubTexture2D::CreateSubTexture(m_SpriteSheet, SubTextureData(2, 14, 16, 16));

        m_controller = CreateSharedPtr<OrthographicCameraController>(1920.0f / 1080.0f);
        m_orthoCameraController = CreateSharedPtr<OrthographicCamera>(-1.7f, 1.7, -1.0f, 1.0f);
    }

    SableLayer::~SableLayer()
    {
    }

    void SableLayer::OnAttach()
    {
        const uint32_t width = Application::Get().GetWindow().GetWidth();
        const uint32_t height = Application::Get().GetWindow().GetHeight();

        FramebufferSpecifications spec;
        spec.width = width;
        spec.height = height;
        m_frameBuffer = FrameBuffer::Create(spec);
        
        m_testScene = CreateSharedPtr<SceneX>(m_controller->GetCamera());
        m_testScene->LoadScene();

#if 0
        {
            entityx::Entity newEntity = m_testScene->CreateEntity("Player", 0);
            newEntity.assign<SpriteComponent>(SVector4(1.0f, 0.0f, 0.0f, 1.0f));
            CollisionData data;
            data.PhysicsType = CollisionType::Dynamic;
            data.FixedRotation = true;
            newEntity.assign<CollisionComponent>(data);
            newEntity.assign<PlayerMovementComponent>();
        }
        
        {
            entityx::Entity newEntity = m_testScene->CreateEntity("Physics Box", 1);
            entityx::ComponentHandle<TransformComponent> transform = newEntity.component<TransformComponent>();
            transform->SetPosition(SVector3(0.5f, 2.0f, 0.0f));
            transform->SetScale(SVector2(2.0f, 1.0f));
            newEntity.assign<SpriteComponent>(SVector4(0.0f, 0.0f, 1.0f, 1.0f));
            CollisionData data;
            data.PhysicsType = CollisionType::Dynamic;
            newEntity.assign<CollisionComponent>(data);
        }
        
        {
            entityx::Entity newEntity = m_testScene->CreateEntity("Ground", 2);
            entityx::ComponentHandle<TransformComponent> transform = newEntity.component<TransformComponent>();
            transform->SetPosition(SVector3(0.0f, -10.0f, 0.0f));
            transform->SetScale(SVector2(50.0f, 10.0f));
            newEntity.assign<SpriteComponent>(SVector4(0.2f, 0.2f, 0.2f, 1.0f));
            CollisionData data;
            data.PhysicsType = CollisionType::Static;
            newEntity.assign<CollisionComponent>(data);
        }
#endif

        // std::string serializeTest = "{111.111,22.222,3.3333}{3.14}{4.00, 5.00}";
        // const TransformComponent test = TransformComponent::deserialize(serializeTest);
        //
        


        // m_editorPanels.push_back(CreateSharedPtr<MenuBarPanel>(m_scene));
        // m_editorPanels.push_back(CreateSharedPtr<SceneHierarchyPanel>(m_scene));
        // m_editorPanels.push_back(CreateSharedPtr<SceneStatsPanel>(m_scene));
        //
        // m_scene->OnViewportResize(1280, 720);
        // m_scene->OnBeginPlay();
    }

    void SableLayer::OnDetach()
    {
    }

    auto SableLayer::OnUpdate(Shake::Timestep timeStep) -> void
    {
        SE_PROFILE_FUNCTION()

        {
            SE_PROFILE_SCOPE("Gameplay update");
        }

        {
            SE_PROFILE_SCOPE("Rendering - Prep");
            if (m_isEditorHidden == false)
            {
            }

            RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
            RenderCommand::Clear();
        }

        {
            SE_PROFILE_SCOPE("Rendering - Draw");

            m_testScene->Update(timeStep.GetSeconds());
        }


        {
            SE_PROFILE_SCOPE("Rendering - Shutdown");
            if (m_isEditorHidden == false)
            {
                m_frameBuffer->Unbind();
            }

            RenderCommand::RenderFrameBuffer(m_frameBuffer);
        }

        if (m_isEditorHidden && m_recalculateViewportSize)
        {
            const uint32_t width = Application::Get().GetWindow().GetWidth();
            const uint32_t height = Application::Get().GetWindow().GetHeight();
            OnResizeViewport(width, height);
        }
    }

    void SableLayer::OnImGuiRender()
    {
        if (m_isEditorHidden)
        {
            return;
        }

        ImGuiSetupDockspace();

        for (SharedPtr<BasePanel> panel : m_editorPanels)
        {
            panel->OnImGuiRender();
        }

        ViewportPanel();

        if (m_actionPanelEnabled)
        {
            ImGui::SetNextWindowPos(m_actionPanelLocation, ImGuiCond_Always, ImVec2(0.0f, 0.0f));
            ImGui::Begin("Action Panel");
            if (ImGui::Button("AddObject"))
            {
                AddObject();
                m_actionPanelEnabled = false;
            }
            ImGui::End();
        }

        ImGuiCloseDockSpace();
    }

    void SableLayer::ImGuiSetupDockspace()
    {
        bool p_open = true;
        static bool opt_fullscreen_persistant = true;
        bool opt_fullscreen = opt_fullscreen_persistant;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->GetWorkPos());
            ImGui::SetNextWindowSize(viewport->GetWorkSize());
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (ImGuiDockNodeFlags_None & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &p_open, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
        }
        else
        {
            //ShowDockingDisabledMessage();
        }
    }

    void SableLayer::ImGuiCloseDockSpace()
    {
        ImGui::End();
    }

    void SableLayer::ViewportPanel()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0)); // Removes padding around the window
        ImGui::Begin("Viewport");

        m_viewportFocused = ImGui::IsWindowFocused();
        m_viewportHovered = ImGui::IsWindowHovered();
        Application::Get().GetImGuiLayer()->BlockEvents(!m_viewportFocused || !m_viewportHovered);

        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        if ((viewportSize.x != m_viewportSize.x || viewportSize.y != m_viewportSize.y) && viewportSize.x > 0 &&
            viewportSize.y > 0)
        {
            m_viewportSize.x = viewportSize.x;
            m_viewportSize.y = viewportSize.y;
            OnResizeViewport(static_cast<uint32_t>(m_viewportSize.x), static_cast<uint32_t>(m_viewportSize.y));
        }

        if (m_recalculateViewportSize)
        {
            m_viewportSize.x = viewportSize.x;
            m_viewportSize.y = viewportSize.y;
            OnResizeViewport(static_cast<uint32_t>(m_viewportSize.x), static_cast<uint32_t>(m_viewportSize.y));
        }

        uint32_t rendererID = m_frameBuffer->GetColorAttachmentRendererID();
        ImGui::Image(INT2VOIDP(rendererID), ImVec2(viewportSize.x, viewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleVar();
    }

    void SableLayer::AddObject()
    {
        SE_ENGINE_LOG(LogVerbosity::Info, "Attempted to add object");
    }

    void SableLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT(SableLayer::OnMouseButtonPressedCallback));
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(SableLayer::OnKeyPressedCallback));

        if (m_isEditorHidden)
        {
            dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(SableLayer::OnWindowResizeCallback));
        }
    }

    bool SableLayer::OnWindowResizeCallback(const WindowResizeEvent& eventData)
    {
        OnResizeViewport(eventData.GetWidth(), eventData.GetHeight());
        return true;
    }

    bool SableLayer::OnMouseButtonPressedCallback(const MouseButtonPressedEvent& eventData)
    {
        if (eventData.GetMouseButton() == MouseCode::ButtonRight)
        {
            m_actionPanelLocation = ImGui::GetMousePos();
            m_actionPanelEnabled = !m_actionPanelEnabled;
        }
        if (eventData.GetMouseButton() == MouseCode::ButtonLeft)
        {
            m_actionPanelEnabled = false;
        }
        return true;
    }

    bool SableLayer::OnKeyPressedCallback(const KeyPressedEvent& eventData)
    {
        if (eventData.GetKeyCode() == KeyCode::F1)
        {
            m_isEditorHidden = !m_isEditorHidden;
            m_recalculateViewportSize = true;
        }
        if (eventData.GetKeyCode() == KeyCode::F2)
        {
            m_simulatePhysics = true;
        }
        if(Input::IsKeyPressed(KeyCode::LeftControl) && Input::IsKeyPressed(KeyCode::S))
        {
           m_testScene->SaveScene(); 
        }
        if(Input::IsKeyPressed(KeyCode::LeftControl) && Input::IsKeyPressed(KeyCode::O))
        {
           m_testScene->LoadScene(); 
        }
        return true;
    }

    void SableLayer::OnResizeViewport(uint32_t width, uint32_t height)
    {
        //m_scene->OnViewportResize(width, height);
        m_recalculateViewportSize = false;
    }
}
