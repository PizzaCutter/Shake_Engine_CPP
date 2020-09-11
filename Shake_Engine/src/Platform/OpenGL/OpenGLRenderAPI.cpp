#include "sepch.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>


#include "Shake/Renderer/Renderer2D.h"
#include "Shake/Renderer/Shader.h"
#include "Shake/Renderer/VertexArray.h"
#include "Shake/Renderer/Buffers/FrameBuffer.h"

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

    void OpenGLRenderAPI::DrawIndexed(const SharedPtr<VertexArray>& vertexArray, uint32_t indexCount)
    {
        const uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGLRenderAPI::RenderFrameBuffer(const SharedPtr<FrameBuffer>& frameBuffer)
    {
        // //second pass
        // glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
        // glClearColor(0.0f, 1.0f, 1.0f, 1.0f); 
        // glClear(GL_COLOR_BUFFER_BIT);
        //
        // float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        //     // positions   // texCoords
        //     -1.0f,  1.0f,  0.0f, 1.0f,
        //     -1.0f, -1.0f,  0.0f, 0.0f,
        //      1.0f, -1.0f,  1.0f, 0.0f,
        //
        //     -1.0f,  1.0f,  0.0f, 1.0f,
        //      1.0f, -1.0f,  1.0f, 0.0f,
        //      1.0f,  1.0f,  1.0f, 1.0f
        // };
        //
        // unsigned int quadVAO, quadVBO;
        // glGenVertexArrays(1, &quadVAO);
        // glGenBuffers(1, &quadVBO);
        // glBindVertexArray(quadVAO);
        // glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        // glEnableVertexAttribArray(0);
        // glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        // glEnableVertexAttribArray(1);
        // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        // //
        // // Renderer2D::m_rendererStorage.m_textureShader->Bind();
        // // //Renderer2D::m_rendererStorage.m_textureShader->Bind();
        // // //screenShader.use();  
        // glBindVertexArray(quadVAO);
        // glDisable(GL_DEPTH_TEST);
        // glBindTexture(GL_TEXTURE_2D, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 6);

    }
}
