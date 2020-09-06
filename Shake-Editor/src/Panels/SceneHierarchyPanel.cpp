#include "SceneHierarchyPanel.h"

#include <string>

#include "imgui/imgui.h"

namespace Shake
{
    SceneHierarchyPanel::SceneHierarchyPanel(const SharedPtr<Scene>& scene)
    {
        SetContext(scene);
    }

    void SceneHierarchyPanel::SetContext(const SharedPtr<Scene>& scene)
    {
        m_context = scene;    
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");

        m_context->GetRegistry().each([&](auto entityID)
        {
            Entity entity {entityID, m_context.get()};
            DrawEntityNode(entity);
        });

        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {
        std::string s = std::to_string(entity.GetEntityId());
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
