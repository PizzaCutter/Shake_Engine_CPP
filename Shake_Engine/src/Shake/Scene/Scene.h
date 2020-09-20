#pragma once

#include "entt.hpp"
#include "box2d/b2_world.h"
#include "Components/TagComponent.h"
#include "entityx/quick.h"
#include "Shake/Renderer/Camera/OrthographicCamera.h"
#include "Systems/CollisionSystem.h"
#include "Systems/PlayerMovementSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/SpawnSystem.h"

namespace Shake
{
    class SceneX : public entityx::EntityX
    {
    public:
        explicit SceneX(OrthographicCamera& camera)
        {
            m_physicsWorld = std::make_unique<b2World>(gravity);
            systems.add<SpawnSystem>(m_physicsWorld.get());
            systems.add<CollisionSystem>();
            systems.add<RenderSystem>(camera);
            systems.add<PlayerMovementSystem>();
            systems.configure();
        }
        
        void Update(entityx::TimeDelta ts)
        {
            m_physicsWorld->Step(ts, m_velocityIterations, m_positionIteartions);
            systems.update_all(ts); 
        }

        void SaveScene();
        void LoadScene();

        entityx::Entity CreateEntity(const std::string& objectName, uint32_t id)
        {
            entityx::Entity newEntity = entities.create();
            newEntity.assign<TagComponent>(objectName, id);
            newEntity.assign<TransformComponent>(SVector3(0.0f));
            return newEntity;
        }
        
        std::unique_ptr<b2World> m_physicsWorld;
        
        // MOVE THIS TO A CONFIG FILE
        b2Vec2 gravity{0.0f, -9.81};
        int32_t m_velocityIterations = 6;
        int32_t m_positionIteartions = 2;
    };
}
