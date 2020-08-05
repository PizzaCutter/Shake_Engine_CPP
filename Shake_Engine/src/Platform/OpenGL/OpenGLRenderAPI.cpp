#include "sepch.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

#include "Shake/Renderer/VertexArray.h"

namespace Shake
{
    void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
    {
       glClearColor(color.r, color.g, color.b, color.a); 
    }

    void OpenGLRenderAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    
    }

    void OpenGLRenderAPI::Initialize()
    {
       glEnable(GL_BLEND);
       glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
    }

    void OpenGLRenderAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr); 
    }
}
