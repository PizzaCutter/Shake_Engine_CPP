#include "sepch.h"
#include "Renderer.h"


#include "OrthographicCamera.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "VertexArray.h"

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

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
    {
        shader->Bind();
        shader->UploadUniformMat4("u_viewProjection", m_sceneData.m_viewProjectionMatrix);
        
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}
