#include "sepch.h"
#include "Renderer.h"


#include "Camera/OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Shake
{
    Renderer::SceneData Renderer::m_sceneData = Renderer::SceneData{}; 
    
    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        m_sceneData.m_viewProjectionMatrix = camera.GetViewProjectionMatrix(); 
    }

    void Renderer::EndScene()
    {
        
    }

    void Renderer::Submit(const SharedPtr<VertexArray>& vertexArray, const SharedPtr<Shader>& shader, const glm::mat4& transform)
    {
        shader->Bind();

        shader->UploadUniformMat4("u_viewProjection", m_sceneData.m_viewProjectionMatrix);
        shader->UploadUniformMat4("u_Transform", transform);
        
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}
