#include "sepch.h"
#include "BaseLayer.h"

#include "Shake/Core/Timestep.h"

#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"
#include "Shake/Renderer/Renderer2D.h"

BaseLayer::BaseLayer() : Layer("Base"),
                         m_orthoCameraController(1280.0f / 720.0f),
                         m_editableColor(SVector4(1.0f))
{
    m_TestTexture = Shake::Texture2D::Create("Content/Textures/Test.png");
}

BaseLayer::~BaseLayer()
{
}

void BaseLayer::OnAttach()
{
}

void BaseLayer::OnDetach()
{
}

auto BaseLayer::OnUpdate(Shake::Timestep timeStep) -> void
{
    SE_PROFILE_FUNCTION()

    {
        SE_PROFILE_SCOPE("Gameplay update");
        m_orthoCameraController.OnUpdate(timeStep);
        m_rotation += 10.0f * timeStep.GetSeconds();
    }

    {
        SE_PROFILE_SCOPE("Rendering - Prep");
        Shake::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Shake::RenderCommand::Clear();

        Shake::Renderer2D::BeginScene(m_orthoCameraController.GetCamera());
    }

    {
        SE_PROFILE_SCOPE("Rendering - Draw");
        Shake::Renderer2D::DrawQuad({0.5f,0.0f,0.0f}, {0.2f, 0.2f}, {1.0f, 0.2f, 0.2f, 1.0f});

        Shake::Renderer2D::DrawQuad({-0.6f, 0.0f, -0.1f}, {0.6f, 0.6f}, {0.2f, 1.0f, 0.2f, 1.0f});
        Shake::Renderer2D::DrawQuadTextured({-0.9f, 0.0f, 0.0f}, {0.5f, 0.5f}, m_TestTexture, {1.0f, 0.2f, 0.2f, 1.0f});
        
        Shake::Renderer2D::DrawRotatedQuad({1.0f, 0.0f, 0.0f}, {0.2f, 0.2f}, SMath::Radians(m_rotation), {0.2f, 0.2f, 1.0f, 1.0f});
        Shake::Renderer2D::DrawRotatedQuadTextured({-0.5f, 0.7f, 0.0f}, {0.5f, 0.5f}, SMath::Radians(m_rotation), m_TestTexture, {10.f, 10.0f});

        // for(float y = -5.0f; y < 5.0f; y += 0.5f)
        // {
        //    for(float x = -5.0f; x < 5.0f; x += 0.5f)
        //    {
        //        glm::vec4 color = {(x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 1.0f};
        //        Shake::Renderer2D::DrawQuad({x,y, -0.5f}, {0.45f, 0.45f}, color);
        //    }
        // }
    }

    {
        SE_PROFILE_SCOPE("Rendering - Shutdown");
        Shake::Renderer2D::EndScene();
    }
}

void BaseLayer::OnImGuiRender()
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
}

void BaseLayer::OnEvent(Shake::Event& event)
{
    m_orthoCameraController.OnEvent(event);
}
