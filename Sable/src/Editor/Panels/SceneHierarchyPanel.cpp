#include "SceneHierarchyPanel.h"

#include "Shake/Strings/SString.h"
#include "imgui/imgui.h"

namespace Shake
{
    SceneHierarchyPanel::SceneHierarchyPanel(SharedPtr<SceneX> scene)
        : BasePanel(scene)
    {
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");

        m_currentScene->entities.each<TagComponent>(
            [this](entityx::Entity entity, TagComponent& tagComponent)
            {
                DrawEntityNode(entity);
            });

        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode(entityx::Entity entity)
    {
        
        ImGuiTreeNodeFlags flags = ((SelectedEntity == entity) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;// | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        entityx::ComponentHandle<TagComponent> tagComponent = entity.component<TagComponent>();
        bool opened = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)tagComponent.get()->ComponentId, flags, tagComponent.get()->ObjectName.c_str());
        if(ImGui::IsItemClicked())
        {
            SelectedEntity = entity;
        }
        if(opened)
        {
            ImGui::TreePop();
        }
    }
}
