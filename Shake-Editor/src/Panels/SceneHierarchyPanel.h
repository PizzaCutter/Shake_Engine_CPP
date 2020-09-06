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
        SceneHierarchyPanel(const Ref<Scene>& scene);

        void SetContext(const Ref<Scene>& scene);

        void OnImGuiRender();
    private:
        void DrawEntityNode(Entity entity);
        
        Ref<Scene> m_context;
        Entity m_selectionContext;
    };
}
