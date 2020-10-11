#include "EntityPropertyPanel.h"

#include "imgui/imgui.h"

#include "Shake/Strings/SString.h"
#include "Shake/Debug/Log.h"

namespace Shake
{
    EntityPropertyPanel::EntityPropertyPanel(SharedPtr<SceneX> scene,
                                             SharedPtr<SceneHierarchyPanel> sceneHierarchyPanel)
        : BasePanel(scene), CachedSceneHierarchyPanel(sceneHierarchyPanel)
    {
    }

    void EntityPropertyPanel::OnImGuiRender()
    {
        ImGui::Begin("Entity Properties");

        RenderEntityProperties();

        ImGui::End();
    }

    bool EntityPropertyPanel::RenderEntityProperties()
    {
        if (CachedSceneHierarchyPanel.get() == nullptr)
        {
            return false;
        }

        entityx::Entity currentSelectedEntity = CachedSceneHierarchyPanel->SelectedEntity;
        if (currentSelectedEntity.valid() == false)
        {
            return false;
        }

        if (currentSelectedEntity.has_component<TagComponent>())
        {
            TagComponent* tagComponent = currentSelectedEntity.component<TagComponent>().get();
            RenderTagComponent(currentSelectedEntity.component<TagComponent>().get());
        }
        if (currentSelectedEntity.has_component<TransformComponent>())
        {
            TransformComponent* transformComponent = currentSelectedEntity.component<TransformComponent>().get();
            RenderTransformComponent(transformComponent);
        }
        if (currentSelectedEntity.has_component<CollisionComponent>())
        {
            CollisionComponent* collisionComponent = currentSelectedEntity.component<CollisionComponent>().get();
            RenderCollisionComponent(collisionComponent);
        }
        if (currentSelectedEntity.has_component<PlayerMovementComponent>())
        {
            PlayerMovementComponent* playerMovementComponent = currentSelectedEntity.component<PlayerMovementComponent>().get();
            RenderPlayerMovementComponent(playerMovementComponent);
        }
        return true;
    }

    void EntityPropertyPanel::RenderTagComponent(TagComponent* inTagComponent)
    {
        if (inTagComponent == nullptr)
        {
            return;
        }

        if (ImGui::TreeNode(TagComponent::GetComponentName().c_str()))
        {
            std::string& objectName = inTagComponent->ObjectName;
            std::vector<char> char_data(objectName.begin(), objectName.end());

            const int stringCharCount = 256;
            char str1[stringCharCount] = "";
            for (int i = 0; i < objectName.size(); ++i)
            {
                str1[i] = objectName.at(i);
            }

            if (ImGui::InputText("Object Name", str1, IM_ARRAYSIZE(str1)))
            {
                objectName.resize(stringCharCount);
                int32_t newStringSize = -1;
                for (int i = 0; i < 256; ++i)
                {
                    objectName[i] = str1[i];
                    if (str1[i] == '\0')
                    {
                        newStringSize = i;
                        break;
                    }
                }
                objectName.resize(newStringSize);
            }

            ImGui::TreePop();
        }
    }

    void EntityPropertyPanel::RenderTransformComponent(TransformComponent* inTransformComponent)
    {
        if (inTransformComponent == nullptr)
        {
            return;
        }

        if (ImGui::TreeNode(TransformComponent::GetComponentName().c_str()))
        {
            // RENDER POSITION PROPERTY
            float position[3] = {
                inTransformComponent->Position.x, inTransformComponent->Position.y, inTransformComponent->Position.z
            };
            if (ImGui::DragFloat3("position", position, 0.01f, -1000000.0f, 1000000.0f))
            {
                inTransformComponent->Position.x = position[0];
                inTransformComponent->Position.y = position[1];
                inTransformComponent->Position.z = position[2];
            }

            // RENDER POSITION PROPERTY
            float rotation = {
                inTransformComponent->Rotation
            };
            if (ImGui::DragFloat("rotation", &rotation, 0.01f, -1000000.0f, 1000000.0f))
            {
                inTransformComponent->Rotation = rotation;
            }

            // RENDER SCALE PROPERTY
            float scale[2] = {
                inTransformComponent->Scale.x, inTransformComponent->Scale.y
            };
            if (ImGui::DragFloat2("scale", scale, 0.01f, -1000000.0f, 1000000.0f))
            {
                inTransformComponent->Scale.x = scale[0];
                inTransformComponent->Scale.y = scale[1];
            }

            ImGui::TreePop();
        }
    }

    void EntityPropertyPanel::RenderCollisionComponent(CollisionComponent* inCollisionComponent)
    {
        if (inCollisionComponent == nullptr)
        {
            return;
        }

        // RENDER PHYSICS TYPE
        if (ImGui::TreeNode(CollisionComponent::GetComponentName().c_str()))
        {
            // Expose flags as checkbox for the demo
            static ImGuiComboFlags flags = 0;
            const char* items[] = {"STATIC", "DYNAMIC", "KINEMATIC"};
            static int item_current_idx = static_cast<int>(inCollisionComponent->CollisionData.PhysicsType);
            // Here our selection data is an index.
            const char* combo_label = items[item_current_idx];
            // Label to preview before opening the combo (technically could be anything)(
            if (ImGui::BeginCombo("physics type", combo_label, flags))
            {
                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {
                    const bool is_selected = (item_current_idx == n);
                    if (ImGui::Selectable(items[n], is_selected))
                    {
                        item_current_idx = n;
                        inCollisionComponent->CollisionData.PhysicsType = item_current_idx;
                    }

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            // RENDER DENSITY PROPERTY
            float density = {
                inCollisionComponent->CollisionData.Density
            };
            if (ImGui::DragFloat("density", &density, 0.01f, -1000000.0f, 1000000.0f))
            {
                inCollisionComponent->CollisionData.Density = density;
            }

            // RENDER FRICTION PROPERTY
            float friction = {
                inCollisionComponent->CollisionData.Friction
            };
            if (ImGui::DragFloat("friction", &friction, 0.01f, -1000000.0f, 1000000.0f))
            {
                inCollisionComponent->CollisionData.Friction = friction;
            }

            // RENDER FIXED ROTATION PROPERTY
            bool fixedRotation = inCollisionComponent->CollisionData.FixedRotation;
            ImGui::Checkbox("fixed rotation", &fixedRotation);

            // RENDER ALLOW SLEEP PROPERTY
            bool allowSleep = inCollisionComponent->CollisionData.AllowSleep;
            ImGui::Checkbox("allow sleep", &allowSleep);

            // RENDER AWAKE PROPERTY
            bool awake = inCollisionComponent->CollisionData.Awake;
            ImGui::Checkbox("awake", &awake);

            ImGui::TreePop();
        }
    }

    //void EntityPropertyPanel::RenderCollisionComponent(CollisionComponent* inCollisionComponent)
    void EntityPropertyPanel::RenderPlayerMovementComponent(PlayerMovementComponent* inPlayerMovementComponent)
    {
        if (inPlayerMovementComponent == nullptr)
        {
            return;
        }

        // RENDER PHYSICS TYPE
        if (ImGui::TreeNode(PlayerMovementComponent::GetComponentName().c_str()))
        {
            // RENDER MOVEMENT SPEED INCREASE PROPERTY
            float movementSpeedIncrease = {
                inPlayerMovementComponent->MovementSpeedIncrease
            };
            if (ImGui::DragFloat("movement speed increase", &movementSpeedIncrease, 0.01f, -1000000.0f, 1000000.0f))
            {
                inPlayerMovementComponent->MovementSpeedIncrease = movementSpeedIncrease;
            }

            // RENDER MAX MOVEMENT SPEED PROPERTY
            float maxMovementSpeed = {
                inPlayerMovementComponent->MaxMovementSpeed
            };
            if (ImGui::DragFloat("max movement speed", &maxMovementSpeed, 0.01f, -1000000.0f, 1000000.0f))
            {
                inPlayerMovementComponent->MaxMovementSpeed = maxMovementSpeed;
            }

            // RENDER MAX MOVEMENT SPEED PROPERTY
            float velocityMultiplier = {
                inPlayerMovementComponent->VelocityMultiplier
            };
            if (ImGui::DragFloat("velocity multiplier", &velocityMultiplier, 0.01f, -1000000.0f, 1000000.0f))
            {
                inPlayerMovementComponent->VelocityMultiplier = velocityMultiplier;
            }

            // RENDER JUMP VELOCITY PROPERTY
            float jumpVelocity = {
                inPlayerMovementComponent->JumpVelocity
            };
            if (ImGui::DragFloat("jump velocity", &jumpVelocity, 0.01f, -1000000.0f, 1000000.0f))
            {
                inPlayerMovementComponent->JumpVelocity = jumpVelocity;
            }

            ImGui::TreePop();
        }
    }
}
