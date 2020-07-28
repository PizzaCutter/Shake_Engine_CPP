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

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const ::std::shared_ptr<Shader>& shader);
        
        inline static RenderAPI::API GetRenderAPI() { return RenderAPI::GetAPI(); };

    private:
        struct SceneData
        {
             glm::mat4 m_viewProjectionMatrix;
        };
        
        static SceneData m_sceneData;
    };
}
