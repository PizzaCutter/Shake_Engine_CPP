#pragma once

#include "entt.hpp"

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
        void OnUpdate(Timestep ts);
        void OnViewportResize(uint32_t width, uint32_t height);
        
        entt::registry& GetRegistry() { return m_registry; }
        
    private:
        // container that contains our entities
        entt::registry m_registry;

        uint32_t m_viewportWidth = 0;
        uint32_t m_viewportHeight = 0;
    };
}
