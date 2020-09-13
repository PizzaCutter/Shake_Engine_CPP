#pragma once

#include "BasePanel.h"
#include "Shake/Core/Core.h"
#include "Shake/Scene/Scene.h"
#include "Shake/Scene/Entities/Entity.h"

namespace Shake
{
    class SceneHierarchyPanel : public BasePanel
    {
    public:
        SceneHierarchyPanel(SharedPtr<Scene> scene);
        virtual ~SceneHierarchyPanel() {};

        void OnImGuiRender() override;
        
    private:
        void DrawEntityNode(Entity entity);
        Entity m_selectionContext;
    };
}
