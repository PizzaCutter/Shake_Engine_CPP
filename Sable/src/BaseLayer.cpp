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
    m_orthoCameraController.OnUpdate(timeStep); 

    Shake::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
    Shake::RenderCommand::Clear();

    Shake::Renderer2D::BeginScene(m_orthoCameraController.GetCamera());

    Shake::Renderer2D::DrawQuad({0.5f,0.0f,0.0f}, {0.5f, 0.5f}, {1.0f, 0.2f, 0.2f, 1.0f});
    Shake::Renderer2D::DrawQuadTextured({-0.5f, 0.0f, 0.0f}, {0.5f, 0.5f}, m_TestTexture);

    Shake::Renderer2D::EndScene();
}

void BaseLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");

    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_editableColor));

    ImGui::End();
}

void BaseLayer::OnEvent(Shake::Event& event)
{
    m_orthoCameraController.OnEvent(event);
}
