#pragma once
#include "entityx/System.h"
#include "Shake/Renderer/Renderer2D.h"
#include "Shake/Renderer/Camera/OrthographicCamera.h"
#include "Shake/Scene/Components/SpriteComponent.h"
#include "Shake/Scene/Components/TransformComponent.h"

namespace Shake
{
    class RenderSystem : public entityx::System<RenderSystem>
    {
    public:
        explicit RenderSystem(OrthographicCamera& camera)
            : Camera(camera)
        {
        }

        void configure(entityx::EventManager& events) override
        {
        }

        void update(entityx::EntityManager& es, entityx::EventManager& events, entityx::TimeDelta dt) override
        {
            Renderer2D::BeginScene(Camera.GetViewProjectionMatrix());
            
            es.each<TransformComponent, SpriteComponent>([this](entityx::Entity entity, TransformComponent &transform, SpriteComponent &sprite)
            {
                Renderer2D::DrawRotatedQuad(transform.Position, transform.Scale, transform.Rotation, sprite.Color);                
            });
            
            Renderer2D::EndScene();
        }
    private:
        OrthographicCamera& Camera;
    };
}
