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
        SceneHierarchyPanel(SharedPtr<SceneX> scene);
        virtual ~SceneHierarchyPanel() {};

        void OnImGuiRender() override;
        
    private:
        entityx::Entity SelectedEntity;
        void DrawEntityNode(entityx::Entity entity);
    };
}
