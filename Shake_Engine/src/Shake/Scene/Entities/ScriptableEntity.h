#pragma once
#include "Entity.h"

namespace Shake
{
    struct ScriptableEntity 
    {
        ScriptableEntity() = default;
        virtual ~ScriptableEntity() {}
        
        template<typename T>
        T& GetComponent()
        {
            return m_entity.GetComponent<T>();
        }
        
        virtual void OnCreate() {}
        virtual void OnDestroy() {}
        virtual void OnUpdate(Timestep ts) {}
    
        Entity m_entity;
        friend class Scene;
    
    };
}
