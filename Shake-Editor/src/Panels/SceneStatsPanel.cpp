#include "SceneStatsPanel.h"

#include "imgui/imgui.h"
#include "Shake/Renderer/Renderer2D.h"

namespace Shake
{
    SceneStatsPanel::SceneStatsPanel(SharedPtr<Scene> scene)
        : BasePanel(scene)
    {
        
    }

    void SceneStatsPanel::OnImGuiRender()
    {
        ImGui::Begin("RENDER STATS");
        const RenderStatistics& renderStats = Renderer2D::GetRenderStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", renderStats.BatchCount);
        ImGui::Text("Quad Count: %d", renderStats.QuadCount);
        ImGui::Text("Index Count: %d", renderStats.IndexCount);
        ImGui::Text("Texture Count: %d", renderStats.TextureCount);
        ImGui::End(); 
    }
}
