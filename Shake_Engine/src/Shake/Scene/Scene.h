#pragma once

#include "entt.hpp"
#include "box2d/b2_world.h"

namespace Shake
{
    class Timestep;
    class Entity;
    
    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity();
        
        void OnBeginPlay();
        void OnUpdate(Timestep ts);
        void OnViewportResize(uint32_t width, uint32_t height);
        
        // container that contains our entities
        entt::registry m_registry;
        
        std::unique_ptr<b2World> m_physicsWorld;
    private:
        b2Vec2 gravity{0.0f, -9.81};
        int32_t m_velocityIterations = 6;
        int32_t m_positionIteartions = 2;
        

        uint32_t m_viewportWidth = 0;
        uint32_t m_viewportHeight = 0;
    };
}
