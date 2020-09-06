#pragma once
#include "RenderAPI.h"

namespace Shake
{
    class Shader;
    class OrthographicCamera;

    class Renderer
    {
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit(const SharedPtr<VertexArray>& vertexArray, const SharedPtr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
        
        inline static RenderAPI::API GetRenderAPI() { return RenderAPI::GetAPI(); };

    private:
        struct SceneData
        {
             glm::mat4 m_viewProjectionMatrix;
        };
        
        static SceneData m_sceneData;
    };
}
