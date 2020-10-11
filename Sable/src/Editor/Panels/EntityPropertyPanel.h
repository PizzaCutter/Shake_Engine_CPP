#pragma once

#include "BasePanel.h"
#include "SceneHierarchyPanel.h"
#include "Shake/Core/Core.h"
#include "Shake/Scene/Scene.h"
#include "Shake/Scene/Entities/Entity.h"

namespace Shake
{
    class EntityPropertyPanel : public BasePanel
    {
    public:
        EntityPropertyPanel(SharedPtr<SceneX> scene, SharedPtr<SceneHierarchyPanel> sceneHierarchyPanel);
        bool RenderEntityProperties();
        void RenderTagComponent(TagComponent* inTagComponent);
        void RenderTransformComponent(TransformComponent* inTransformComponent);
        void RenderCollisionComponent(CollisionComponent* inCollisionComponent);
        void RenderPlayerMovementComponent(PlayerMovementComponent* inPlayerMovementComponent); 
        virtual ~EntityPropertyPanel() {};

        void OnImGuiRender() override;
    private:
       SharedPtr<SceneHierarchyPanel> CachedSceneHierarchyPanel;
    };
}
