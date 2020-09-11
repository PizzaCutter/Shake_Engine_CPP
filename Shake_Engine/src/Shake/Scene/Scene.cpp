#include "sepch.h"
#include "Scene.h"

#include "Shake/Scene/Components/Components.h"
#include "Shake/Renderer/Renderer2D.h"

#include "Shake/Scene/Entities/Entity.h"

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
        // UPDATE SCRIPTS
        m_registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
        {
            // TODO: move to Scene::OnScenePlay
            if (nsc.Instance == false)
            {
                nsc.Instance = nsc.InstantiateScript();
                nsc.Instance->m_entity = Entity{ entity, this} ;
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
                if(camera.Primary)
                {
                    mainCamera = &camera.Camera;
                    mainCamera->UpdateViewProjection(transform);
                    break;
                }
            }
        }

        SE_ENGINE_LOG(LogVerbosity::Info, "AspectRatio {0}", mainCamera->GetAspectRatio());

        if(mainCamera == nullptr)
        {
            // TODO[rsmekens]: add asssert 
            return;
        }

        // RENDER SPRITES
        Renderer2D::BeginScene(*mainCamera);
        
        auto group = m_registry.group<TransformComponent>(entt::get<SpriteComponent>);
        for(auto entity : group)
        {
            auto[transform, sprite] = group.get<TransformComponent, SpriteComponent>(entity);

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
            if(camera.FixedAspectRatio == false)
            {
                camera.Camera.SetViewportSize(width, height);
            }
        }
    }
}
