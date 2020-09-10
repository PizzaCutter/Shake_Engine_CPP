#include "sepch.h"
#include "EditorLayer.h"

#include "Shake/Core/Utils/Timestep.h"

#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"
#include "Shake/Renderer/Buffers/FrameBuffer.h"
#include "Shake/Renderer/Renderer2D.h"

EditorLayer::EditorLayer() : Layer("Base"),
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
    }
}

void EditorLayer::OnImGuiRender()
{

}

void EditorLayer::OnEvent(Shake::Event& event)
{
    m_orthoCameraController.OnEvent(event);
}
