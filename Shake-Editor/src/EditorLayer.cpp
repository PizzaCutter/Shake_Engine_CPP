#include "sepch.h"
#include "EditorLayer.h"

#include "Shake/Core/Timestep.h"

#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"
#include "Shake/Renderer/FrameBuffer.h"
#include "Shake/Renderer/Renderer2D.h"

EditorLayer::EditorLayer() : Layer("EditorLayer"),
                         m_orthoCameraController(1280.0f / 720.0f),
                         m_editableColor(SVector4(1.0f))
{
    m_TestTexture = Shake::Texture2D::Create("Content/Textures/Test.png");
    m_SpriteSheet = Shake::Texture2D::Create("Content/Game/Textures/industrial.v2.png");
    m_SubTextureTest = Shake::SubTexture2D::CreateSubTexture(m_SpriteSheet, Shake::SubTextureData(2, 14, 16, 16));
}

EditorLayer::~EditorLayer()
{
}

void EditorLayer::OnAttach()
{
   Shake::FramebufferSpecifications spec;
    spec.width = 1280;
    spec.height = 720;
    m_frameBuffer = Shake::FrameBuffer::Create(spec);
}

void EditorLayer::OnDetach()
{
}

auto EditorLayer::OnUpdate(Shake::Timestep timeStep) -> void
{
    SE_PROFILE_FUNCTION()

    {
        SE_PROFILE_SCOPE("Gameplay update");
        m_orthoCameraController.OnUpdate(timeStep);
        m_rotation += 10.0f * timeStep.GetSeconds();
    }

    {
        SE_PROFILE_SCOPE("Rendering - Prep");
        m_frameBuffer->Bind();
        Shake::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Shake::RenderCommand::Clear();

        Shake::Renderer2D::BeginScene(m_orthoCameraController.GetCamera());
    }

    {
        SE_PROFILE_SCOPE("Rendering - Draw");
        Shake::Renderer2D::DrawQuad({0.5f, 0.0f, 0.0f}, {0.2f, 0.2f}, {1.0f, 0.2f, 0.2f, 1.0f});

        //Shake::Renderer2D::DrawQuadTextured({-0.9f, 0.0f, 0.0f}, {0.5f, 0.5f}, m_TestTexture, {1.0f, 0.2f, 0.2f, 1.0f});

        Shake::Renderer2D::DrawRotatedQuad({1.0f, 0.0f, 0.0f}, {0.2f, 0.2f}, SMath::Radians(m_rotation),
                                           {0.2f, 0.2f, 1.0f, 1.0f});
        Shake::Renderer2D::DrawRotatedQuadTextured({0.5f, 0.7f, 0.0f}, {0.5f, 0.5f}, SMath::Radians(m_rotation),
                                                   m_TestTexture, {10.f, 10.0f});

        Shake::Renderer2D::DrawQuad({-0.9f, 0.0f, -0.1f}, {0.5f, 0.5f}, {0.2f, 1.0f, 0.2f, 1.0f});
        Shake::Renderer2D::DrawQuadSubTexture({-0.9f, 0.0f, 0.0f}, {0.5f, 0.5f}, m_SubTextureTest,
                                              {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f});

        // for(float y = -5.0f; y < 5.0f; y += 0.5f)
        // {
        //    for(float x = -5.0f; x < 5.0f; x += 0.5f)
        //    {
        //        glm::vec4 color = {(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 1.0f};
        //        Shake::Renderer2D::DrawQuad({x,y, -0.5f}, {0.45f, 0.45f}, color);
        //    }
        // }

        //Shake::Renderer2D::DrawQuadTextured({0.9f, 0.0f, 0.0f}, {0.5f, 0.5f}, m_SpriteSheet, {1.0f, 1.0f, 1.0f, 1.0f});
    }

    {
        SE_PROFILE_SCOPE("Rendering - Shutdown");
        Shake::Renderer2D::EndScene();

        m_frameBuffer->Unbind();
    }
}

void EditorLayer::OnImGuiRender()
{
     bool p_open = true;
     static bool opt_fullscreen_persistant = true;
     bool opt_fullscreen = opt_fullscreen_persistant;
     static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    
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
     if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
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
         ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
     }
     else
     {
         //ShowDockingDisabledMessage();
     }
    
     if (ImGui::BeginMenuBar())
     {
         if (ImGui::BeginMenu("Docking"))
         {
             // Disabling fullscreen would allow the window to be moved to the front of other windows,
             // which we can't undo at the moment without finer window depth/z control.
             //ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);
    
             if (ImGui::MenuItem("Exit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))
             {
                 Shake::Application::Get().Close();
             }
             
             ImGui::EndMenu();
         }
         ImGui::EndMenuBar();
     }

     {
         ImGui::Begin("Settings");
         ImGui::ColorEdit4("Square Color", glm::value_ptr(m_editableColor));
         const Shake::RenderStatistics& renderStats = Shake::Renderer2D::GetRenderStats();
         ImGui::Text("Renderer2D Stats:");
         ImGui::Text("Draw Calls: %d", renderStats.BatchCount);
         ImGui::Text("Quad Count: %d", renderStats.QuadCount);
         ImGui::Text("Index Count: %d", renderStats.IndexCount);
         ImGui::Text("Texture Count: %d", renderStats.TextureCount);
         ImGui::End();

         ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0)); // Removes padding around the window
         ImGui::Begin("Viewport");
         
         ImVec2 viewportSize = ImGui::GetContentRegionAvail();
         
         if(viewportSize.x != m_viewportSize.x || viewportSize.y != m_viewportSize.y)
         {
             m_viewportSize.x = viewportSize.x;
             m_viewportSize.y = viewportSize.y;
             m_frameBuffer->Resize(static_cast<uint32_t>(m_viewportSize.x), static_cast<uint32_t>(m_viewportSize.y));

             m_orthoCameraController.OnResize(m_viewportSize.x, m_viewportSize.y);
         }

         uint32_t rendererID = m_frameBuffer->GetColorAttachmentRendererID();
         ImGui::Image((void*)rendererID, ImVec2(viewportSize.x, viewportSize.y), ImVec2(0,1), ImVec2(1, 0));
      
         ImGui::End();
         ImGui::PopStyleVar();
     }

    ImGui::End();
}

void EditorLayer::OnEvent(Shake::Event& event)
{
    m_orthoCameraController.OnEvent(event);
}
