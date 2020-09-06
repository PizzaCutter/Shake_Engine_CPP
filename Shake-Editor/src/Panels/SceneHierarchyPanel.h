#pragma once

#include "Shake/Scene/Scene.h"
#include "Shake/Core/Core.h"
#include "Shake/Scene/Entities/Entity.h"

namespace Shake
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() {}
        SceneHierarchyPanel(const SharedPtr<Scene>& scene);

        void SetContext(const SharedPtr<Scene>& scene);

        void OnImGuiRender();
    private:
        void DrawEntityNode(Entity entity);
        
        SharedPtr<Scene> m_context;
        Entity m_selectionContext;
    };
}
