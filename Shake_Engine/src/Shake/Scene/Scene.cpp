#include "sepch.h"
#include "Scene.h"

#include "Shake/Scene/Entities/Entity.h"

#include "Shake/Scene/Components/Components.h"
#include "Components/TransformComponent.h"
#include "Components/CollisionComponent.h"
#include "Shake/Events/Event.h"

#include "Shake/Renderer/Renderer2D.h"


namespace Shake
{
    Scene::Scene()
    {
        m_physicsWorld = std::make_unique<b2World>(gravity);
    }

    Scene::~Scene()
    {
    }

    Entity Scene::CreateEntity()
    {
        Entity entity = Entity(m_registry.create(), this);
        entity.AddComponent<TransformComponent>();
        return entity;
    }

    void Scene::OnBeginPlay()
    {
        auto view = m_registry.view<CollisionComponent>();
        for (auto entity : view)
        { 
            auto& collisionComponent = m_registry.get<CollisionComponent>(entity);
            collisionComponent.OnCreate(Entity{entity, this});
        }
    }

    void Scene::OnUpdate(Timestep ts)
    {
        // PHYSICS UPDATE
        {
            m_physicsWorld->Step(ts.GetSeconds(), m_velocityIterations, m_positionIteartions);

            auto view = m_registry.view<CollisionComponent>();
            for (auto entity : view)
            {
                auto& transformComponent = m_registry.get<TransformComponent>(entity);
                auto& collisionComponent = m_registry.get<CollisionComponent>(entity);
                const auto position = collisionComponent.m_physicsBody->GetPosition();
                const auto rotation = collisionComponent.m_physicsBody->GetAngle();
                transformComponent.SetPositionAndRotation(SVector3(position.x, position.y, 0.0f), rotation);
            }
        }

        // // UPDATE SCRIPTS
        m_registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
        {
            // TODO: move to Scene::OnScenePlay
            if (nsc.Instance == false)
            {
                nsc.Instance = nsc.InstantiateScript();
                nsc.Instance->m_entity = Entity{entity, this};
                nsc.Instance->OnCreate();
            }

            nsc.Instance->OnUpdate(ts);
        });
        
        // FIND MAIN CAMERA 
        // TODO[rsmekens]: make this 'independent' from entt use a thin wrapper layer instead so we can layer implement our own system
        SceneCamera* mainCamera = nullptr;
        {
            auto group = m_registry.group<CameraComponent>(entt::get<TransformComponent>);
            for (auto entity : group)
            {
                auto [camera, transform] = group.get<CameraComponent, TransformComponent>(entity);
                if (camera.Primary)
                {
                    mainCamera = &camera.Camera;
                    mainCamera->UpdateViewProjection(transform);
                    break;
                }
            }
        }

        if (mainCamera == nullptr)
        {
            // TODO[rsmekens]: add asssert 
            return;
        }

        // RENDER SPRITES
        Renderer2D::BeginScene(*mainCamera);

        auto group = m_registry.group<TransformComponent>(entt::get<SpriteComponent>);
        for (auto entity : group)
        {
            auto [transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

            Renderer2D::DrawQuad(transform, sprite.Color);
        }


        Renderer2D::EndScene();
    }

    void Scene::OnViewportResize(uint32_t width, uint32_t height)
    {
        m_viewportWidth = width;
        m_viewportHeight = height;

        auto group = m_registry.view<CameraComponent>();
        for (auto entity : group)
        {
            auto& camera = group.get<CameraComponent>(entity);
            if (camera.FixedAspectRatio == false)
            {
                camera.Camera.SetViewportSize(width, height);
            }
        }
    }
}
