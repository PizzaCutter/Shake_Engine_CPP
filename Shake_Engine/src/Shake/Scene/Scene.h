#pragma once

#include "entt.hpp"
#include "Shake/Core/Timestep.h"

namespace Shake
{
    class Entity;
    
    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity();
        void OnUpdate(Timestep ts);
        
        entt::registry& GetRegistry() { return m_registry; }
        
    private:
        // container that contains our entities
        entt::registry m_registry;
    };
}
