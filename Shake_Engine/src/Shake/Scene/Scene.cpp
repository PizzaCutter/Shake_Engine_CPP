#include "sepch.h"
#include "Scene.h"

#include "Components.h"
#include "Shake/Renderer/Renderer2D.h"

#include "Shake/Scene/Entity.h"

namespace Shake
{
    Scene::Scene()
    {
        
    }

    Scene::~Scene()
    {
        
    }

    Entity Scene::CreateEntity()
    {
        Entity entity = Entity(m_registry.create(), this);
        return entity;
    }

    void Scene::OnUpdate(Timestep ts)
    {
       auto group = m_registry.group<TransformComponent>(entt::get<SpriteComponent>);
        for(auto entity : group)
        {
            auto&[transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

            Renderer2D::DrawQuad(transform, sprite.Color);
        }
    }
}
