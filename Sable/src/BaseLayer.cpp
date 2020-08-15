#include "sepch.h"
#include "BaseLayer.h"

#include "Shake/Core/Timestep.h"

#include "glm/gtc/type_ptr.hpp"
#include "imgui/imgui.h"
#include "Shake/Helpers/Timer.h"
#include "Shake/Renderer/Renderer2D.h"

#define PROFILE_SCOPE(name) Shake::Timer timer##__LINE__(name, [&](ProfileResult result) { m_profileResults.push_back(result); })

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
    PROFILE_SCOPE("BaseLayer::OnUpdate");
    
    m_orthoCameraController.OnUpdate(timeStep); 

    Shake::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Shake::RenderCommand::Clear();

    Shake::Renderer2D::BeginScene(m_orthoCameraController.GetCamera());

    {
        PROFILE_SCOPE("BaseLayer::Rendering");
        Shake::Renderer2D::DrawQuad({0.5f,0.0f,0.0f}, {0.5f, 0.5f}, {1.0f, 0.2f, 0.2f, 1.0f});
        Shake::Renderer2D::DrawQuadTextured({-0.5f, 0.0f, 0.0f}, {0.5f, 0.5f}, m_TestTexture);
        Shake::Renderer2D::DrawQuadTextured({0.0f, 0.5f, 0.0f}, {0.5f, 0.5f}, m_TestTexture, {1.0f, 1.0f, 1.0f, 1.0f},
                                            {10.0f, 10.0f});
    }

    Shake::Renderer2D::EndScene();
}

void BaseLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_editableColor));

    for(auto& result : m_profileResults)
    {
        char label[50];
        strcpy_s(label, result.m_name);
        strcat_s(label, "  %.3fms");
        ImGui::Text(label, result.m_duration);        
    }
    m_profileResults.clear();

    ImGui::End();
}

void BaseLayer::OnEvent(Shake::Event& event)
{
    m_orthoCameraController.OnEvent(event);
}
