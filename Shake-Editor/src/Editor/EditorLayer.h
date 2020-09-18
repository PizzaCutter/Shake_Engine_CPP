#pragma once
#include "Shake.h"
#include "box2d/b2_world.h"
#include "imgui/imgui.h"
#include "Shake/Renderer/Textures/SubTexture2D.h"
#include "Shake/Renderer/Camera/OrthographicCameraController.h"
#include "Shake/Scene/Entities/Entity.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/SceneStatsPanel.h"
#include "Shake/Events/KeyEvent.h"

#include "entityx/quick.h"
#include "entityx/System.h"

namespace ex = entityx;

namespace Shake {
    class BasePanel;
    class Scene;
    class FrameBuffer;
    class VertexArray;
    class Texture2D;

    struct Transform
    {
        Transform(const SVector3& position)
            : Position(position), Scale(1.0f), Rotation(0.0f)
        {
             
        }

        Transform(const SVector3& position, const SVector2& scale)
            : Position(position), Scale(scale)
        {
            
        }
        
        Transform(const SVector3& position, const SVector2& scale, float rotation)
            : Position(position), Scale(scale), Rotation(rotation)
        {
            
        }
        
        SVector3 Position{0.0f, 0.0f, 0.0f};
        SVector2 Scale{1.0f, 1.0f};
        float Rotation{0.0f};
    };

    struct Sprite
    {
        Sprite(const SVector4& color)
            : Color(color)
        {
            
        }
        
        SVector4 Color{1.0f, 1.0f, 1.0f, 1.0f};
    };

    class SpawnSystem : public ex::System<SpawnSystem>
    {
    public:
        explicit SpawnSystem()
        {
        }

        void configure(entityx::EventManager& events) override
        {
           
        }

        void update(entityx::EntityManager& em, entityx::EventManager& events, entityx::TimeDelta dt) override
        {
        }
    };

    class RenderSystem : public ex::System<RenderSystem>
    {
    public:
        explicit RenderSystem(SharedPtr<OrthographicCamera> camera)
            : Camera(camera)
        {
        }

        void configure(entityx::EventManager& events) override
        {
        }

        void update(ex::EntityManager& es, ex::EventManager& events, ex::TimeDelta dt) override
        {
            Renderer2D::BeginScene(Camera->GetViewProjectionMatrix());
            
            es.each<Transform, Sprite>([this](ex::Entity entity, Transform &transform, Sprite &sprite)
            {
                Renderer2D::DrawRotatedQuad(transform.Position, transform.Scale, transform.Rotation, sprite.Color);                
            });
            
            Renderer2D::EndScene();
        }
    private:
        SharedPtr<OrthographicCamera> Camera;
    };

    class SceneX : public ex::EntityX
    {
    public:
        explicit SceneX(SharedPtr<OrthographicCamera> camera)
        {
            systems.add<SpawnSystem>();
            systems.add<RenderSystem>(camera);
            systems.configure();
        }
        virtual ~SceneX() = default;

        void Update(entityx::TimeDelta dt)
        {
            systems.update_all(dt);
        }
    };

class EditorLayer : public Layer
{
public:
    EditorLayer();
    ~EditorLayer() override;
    void OnAttach() override;
    b2Body* CreatePhysicsBody(Entity entity);
    void OnDetach() override;
    void OnUpdate(Timestep timeStep) override;

    void OnImGuiRender() override;

    void OnEvent(Event& event) override;
    bool OnWindowResizeCallback(const WindowResizeEvent& eventData);
    bool OnMouseButtonPressedCallback(const MouseButtonPressedEvent& eventData);
    bool OnKeyPressedCallback(const KeyPressedEvent& eventData);
    void OnResizeViewport(uint32_t width, uint32_t height);

private:
    void ImGuiSetupDockspace();
    void ImGuiCloseDockSpace();
    void ViewportPanel();
    
    void AddObject();
    void SaveScene();

    SharedPtr<SceneX> m_testScene;
    
    SharedPtr<Texture2D> m_SpriteSheet;
    SharedPtr<SubTexture2D> m_SubTextureTest;

    SharedPtr<FrameBuffer> m_frameBuffer;
    SharedPtr<OrthographicCamera> m_orthoCameraController;

    SVector2 m_viewportSize = SVector2(0.0f, 0.0f);
    bool m_viewportFocused = false;
    bool m_viewportHovered = false;

    SVector4 m_editableColor;

    float m_rotation = 0.0f;

    std::vector<SharedPtr<BasePanel>> m_editorPanels;

    bool m_simulatePhysics = false;
    
    bool m_isEditorHidden = true;
    bool m_recalculateViewportSize = true;

    // TRYING TO CREATE AN ACTION PANEL
    ImVec2 m_actionPanelLocation;
    bool m_actionPanelEnabled = false;
    bool m_triggeredSave = false;

    //SharedPtr<OrthographicCameraController> m_orthoCameraController;
};
    
}
