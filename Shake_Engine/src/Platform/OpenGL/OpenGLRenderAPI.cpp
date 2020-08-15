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

        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderAPI::WindowResize(int32_t width, int32_t height)
    {
        glViewport(0, 0, width, height);
    }

    void OpenGLRenderAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
    {
        const uint32_t count = indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
