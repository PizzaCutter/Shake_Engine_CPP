#include "SceneHierarchyPanel.h"

#include "Shake/Strings/SString.h"
#include "imgui/imgui.h"

namespace Shake
{
    SceneHierarchyPanel::SceneHierarchyPanel(SharedPtr<Scene> scene)
        : BasePanel(scene)
    {
        
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");
        
        m_currentScene->m_registry.each([&](auto entityID)
        {
            Entity entity {entityID, m_currentScene.get()};
            DrawEntityNode(entity);
        });
        
        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {
        SString s = std::to_string(entity.GetEntityId());
        ImGuiTreeNodeFlags flags = ((m_selectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;// | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)entity.GetEntityId(), flags , s.c_str());
        
        if(ImGui::IsItemClicked())
        {
            m_selectionContext = entity;
        }
        
        if(opened)
        {            
            ImGui::TreePop();
        }
    }
}
