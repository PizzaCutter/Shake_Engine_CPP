#include "sepch.h"
#include "Scene.h"

//#include "entityx/quick.h"
#include "Shake/Serialization/metastuff/example/nlohmann_json/json.hpp"
#include "Shake/Serialization/metastuff/example/JsonCast.h"

#include "Shake/Serialization/metastuff/example/Person.h"
#include "Shake/Serialization/metastuff/include/Meta.h"

class Unregistered
{
};

void printSeparator()
{
    std::cout << "========================\n";
}


namespace ns
{
    struct BaseComponent
    {
        std::string ComponentName = "BaseComponent";
        int testNumber = 2;
        float otherTestNumber = 3.0f;
    };

    struct TestComponent : BaseComponent
    {
        TestComponent()
        {
            ComponentName = "TestComponent";
        }

        int32 integerNumber = 1;
    };

    struct OtherComponent : BaseComponent
    {
        OtherComponent()
        {
            ComponentName = "OtherComponent";
        }

        float floatNumber = 2.0f;
    };

    struct TestEntity
    {
        TestEntity(const std::string& name)
            : Name(name)
        {
        }

        std::string Name = "";
        std::vector<BaseComponent*> Components;
    };


    void from_json(const json& j, TestEntity& p)
    {
    }

    void to_json(json& j, const OtherComponent& p)
    {
        j = json{{"floatNumber", p.floatNumber}};
    }

    void to_json(json& j, const TestComponent& p)
    {
        j = json{{"integerNumber", p.integerNumber}};
    }

    void to_json(json& j, const BaseComponent& p)
    {
        j = json{{"ComponentName", p.ComponentName}, {"IntNumber", p.testNumber}, {"OtherNumber", p.otherTestNumber}};
    }

    // void to_json(json& j, const TagComponent& p)
    // {
    //     j = json{{"ComponentName", "TagComponent"}, {"ObjectName", p.ObjectName}, {"ComponentId", p.ComponentId}};       
    // }


    void from_json(const json& j, BaseComponent& p)
    {
        j.at("ComponentName").get_to(p.ComponentName);
        j.at("IntNumber").get_to(p.testNumber);
        j.at("OtherNumber").get_to(p.otherTestNumber);
    }

    void to_json(json& j, const BaseComponent* p)
    {
        j = json{
            {"ComponentName", p->ComponentName}, {"IntNumber", p->testNumber}, {"OtherNumber", p->otherTestNumber}
        };
    }

    void to_json(json& j, const TestEntity& p)
    {
        for (auto component : p.Components)
        {
            j.push_back(component);
        }
        //j = json{{"components",  p.Components}};
        //j.push_back(p.Components[0]);
    }
}

namespace Shake
{
    void SceneX::Update(entityx::TimeDelta ts)
    {
        if (m_updateSystems == false)
        {
            auto renderSystem = systems.system<RenderSystem>();
            renderSystem->update(entities, events, ts);
            return;
        }

        m_physicsWorld->Step(ts, m_velocityIterations, m_positionIteartions);
        systems.update_all(ts);

        SELOG(LogVerbosity::Info, "{0}", entities.size());
    }

    void SceneX::SaveScene()
    {
        std::string sceneData = "";
        json jsonEntities;
        entities.each<TagComponent>(
            [this, &sceneData, &jsonEntities](entityx::Entity entity, TagComponent& tagComponent)
            {
                json jsonEntity;
                jsonEntity.push_back(tagComponent);

                if (entity.has_component<TransformComponent>())
                {
                    jsonEntity.push_back(*entity.component<TransformComponent>().get());
                }
                if (entity.has_component<SpriteComponent>())
                {
                    jsonEntity.push_back(*entity.component<SpriteComponent>().get());
                }
                if (entity.has_component<CollisionComponent>())
                {
                    jsonEntity.push_back(*entity.component<CollisionComponent>().get());
                }
                if (entity.has_component<PlayerMovementComponent>())
                {
                    jsonEntity.push_back(*entity.component<PlayerMovementComponent>().get());
                }

                jsonEntities.push_back(jsonEntity);
            });

        sceneData = jsonEntities.dump();

        SE_ENGINE_LOG(LogVerbosity::Verbose, "\n{0}", sceneData);

        std::ofstream sceneFile;
        // TODO[rsmekens]: pull this from a file
        sceneFile.open("scene.shake");
        sceneFile << sceneData;
        sceneFile.close();
    }

    inline bool IsSpace(unsigned char c)
    {
        return (c == ' ' || c == '\n' || c == '\r' ||
            c == '\t' || c == '\v' || c == '\f');
    }

    // Might be interesting to read this article https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring 
    void SceneX::LoadScene()
    {
        // LOADING SCENE DATA
        std::string serializedSceneData;
        std::ifstream sceneFile("scene.shake");
        json jf = json::parse(sceneFile);
        sceneFile.close();

        entities.each<TagComponent>([this](entityx::Entity entity, TagComponent& tagComponent)
        {
            entities.destroy(entity.id());
        });

        // RESETTING PHYSICS
        m_physicsWorld.reset();
        m_physicsWorld = std::make_unique<b2World>(gravity);
        std::shared_ptr<SpawnSystem> spawnSystem = systems.system<SpawnSystem>();
        spawnSystem->m_physicsWorld = m_physicsWorld.get();
        spawnSystem->Reset();

        for (auto element : jf.items())
        {
            entityx::Entity newEntity = entities.create();
            for (json::iterator it = element.value().begin(); it != element.value().end(); ++it)
            {
                nlohmann::basic_json<> temp = it.value();
                nlohmann::basic_json<>::iterator otherTemp = temp.find("name");

                if (otherTemp.value() == TagComponent::GetComponentName())
                {
                    TagComponent newTagComp;
                    from_json(temp, newTagComp);
                    newEntity.assign<TagComponent>(newTagComp);
                }
                if (otherTemp.value() == TransformComponent::GetComponentName())
                {
                    TransformComponent newTransformComponent;
                    from_json(temp, newTransformComponent);
                    newEntity.assign<TransformComponent>(newTransformComponent);
                }
                if (otherTemp.value() == SpriteComponent::GetComponentName())
                {
                    SpriteComponent newSpriteComponent;
                    from_json(temp, newSpriteComponent);
                    newEntity.assign<SpriteComponent>(newSpriteComponent);
                }
                if (otherTemp.value() == CollisionComponent::GetComponentName())
                {
                    CollisionComponent newCollisionComponent;
                    from_json(temp, newCollisionComponent);
                    newEntity.assign<CollisionComponent>(newCollisionComponent);
                }
                if(otherTemp.value() == PlayerMovementComponent::GetComponentName()) 
                {
                    PlayerMovementComponent newPlayerMovementComponent;
                    from_json(temp, newPlayerMovementComponent);
                    newEntity.assign<PlayerMovementComponent>(newPlayerMovementComponent);
                }
            }
        }
    }
}
