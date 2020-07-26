#include "sepch.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "VertexArray.h"

namespace Shake
{
    void Renderer::BeginScene()
    {
        
    }

    void Renderer::EndScene()
    {
        
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}
