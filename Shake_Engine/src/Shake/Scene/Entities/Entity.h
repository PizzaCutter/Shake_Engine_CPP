#pragma once

#include "Shake/Scene/Scene.h"
#include "entt.hpp"

using EntityHandle = entt::entity;
#define EmptyEntityHandle entt::null

namespace Shake
{

    class Entity
    {
    public:
        Entity() = default;
        Entity(EntityHandle handle, Scene* scene)
        {
            m_entityId = handle;
            m_scene = scene;
        }
        Entity(const Entity& other) = default;

        template<typename T>
        bool HasComponent()
        {
           return m_scene->GetRegistry().has<T>(m_entityId); 
        }

        template<typename T>
        T& GetComponent()
        {
            //SE_CORE_ASSERT(HasComponent<T>, "Entity does not have component!");
            return m_scene->GetRegistry().get<T>(m_entityId);
        }

        template<typename T, typename... Args>
        T& AddComponent(Args &&... args)
        {
            SE_CORE_ASSERT(HasComponent<T>, "Entity does not have component!");
            return m_scene->GetRegistry().emplace<T>(m_entityId, std::forward<Args>(args)...);
        }

        template<typename T>
        T& RemoveComponent()
        {
            SE_CORE_ASSERT(HasComponent<T>, "Entity does not have component!");
            return m_scene->GetRegistry().remove<T>(m_entityId);
        }

        operator bool() const { return m_entityId == EmptyEntityHandle; }
        operator uint32_t() const { return static_cast<uint32_t>(m_entityId); }
        bool operator==(const Entity& other) const { return (m_entityId == other.m_entityId && m_scene == other.m_scene); }
        bool operator!=(const Entity& other) const { return !(*this == other); }

        const uint32_t GetEntityId() const { return static_cast<uint32_t>(m_entityId); }
    private:
        EntityHandle m_entityId { EmptyEntityHandle };
        Scene* m_scene = nullptr;
    };

}
