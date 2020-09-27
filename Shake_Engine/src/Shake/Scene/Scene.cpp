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

    void SceneX::TestMetaStuff()
    {
        Person person;
        person.age = 25;
        person.salary = 3.50f;
        person.name = "Alex"; // I'm a person!

        person.favouriteMovies["Nostalgia Critic"] = {MovieInfo{"The Room", 8.5f}};
        person.favouriteMovies["John Tron"] = {
            MovieInfo{"Goosebumps", 10.0f},
            MovieInfo{"Talking Cat", 9.0f}
        };

        // printing members of different classes
        std::cout << "Members of class Person:\n";
        meta::doForAllMembers<Person>(
            [](const auto& member)
            {
                std::cout << "* " << member.getName() << '\n';
            }
        );

        std::cout << "Members of class MovieInfo:\n";
        meta::doForAllMembers<MovieInfo>(
            [](const auto& member)
            {
                std::cout << "* " << member.getName() << '\n';
            }
        );

        printSeparator();

        // checking if classes are registered
        if (meta::isRegistered<Person>())
        {
            std::cout << "Person class is registered\n";
            std::cout << "It has " << meta::getMemberCount<Person>() << " members registered.\n";
        }

        // meta::isRegistered is constexpr, so can be used in enable_if and static_assert!
        static_assert(meta::isRegistered<Person>(), "Person class is not registered!");
        static_assert(meta::getMemberCount<Person>() == 4, "Person does not have 4 members registered?");

        if (!meta::isRegistered<Unregistered>())
        {
            std::cout << "Unregistered class is unregistered\n";
            std::cout << "It has " << meta::getMemberCount<Unregistered>() << " members registered.\n";
        }

        // checking if class has a member
        if (meta::hasMember<Person>("age"))
        {
            std::cout << "Person has member named 'age'\n";
        }

        // getting members
        auto age = meta::getMemberValue<int>(person, "age");
        std::cout << "Got person's age: " << age << '\n';

        auto name = meta::getMemberValue<std::string>(person, "name");
        std::cout << "Got person's name: " << name << '\n';

        // setting members
        meta::setMemberValue<std::string>(person, "name", "Ron Burgundy");
        name = meta::getMemberValue<std::string>(person, "name");
        std::cout << "Changed person's name to " << name << '\n';

        printSeparator();

        // And here's how you can serialize/deserialize
        // (if you write a function for your type)
        std::cout << "Serializing person:" << '\n';
        json root = person;
        std::cout << std::setw(4) << root << std::endl;

        //Unregistered y;
        //json root2 = y; // this will fail at compile time

        printSeparator();

        std::cout << "Serializing Person 2 from JSON:\n";

        auto person2 = root.get<Person>();
        std::cout << "Person 2 name is " << person2.getName() << " too!" << '\n';
    }

    void SceneX::SaveScene()
    {
        //TestMetaStuff();
        
        std::string sceneData = "";
        entities.each<TagComponent, TransformComponent, CollisionComponent>(
            [this, &sceneData](entityx::Entity entity, TagComponent& tagComponent,
                               TransformComponent& transformComponent, CollisionComponent& collisionComponent)
            {
                sceneData += tagComponent.serialize() + ";\n\t" + transformComponent.serialize() + ";\n\t" +
                    collisionComponent.serialize() + ";%" + "\n";
            });
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
        std::string lineData;
        while (getline(sceneFile, lineData))
        {
            serializedSceneData += lineData + "\n";
        }
        sceneFile.close();

        serializedSceneData.erase(std::remove_if(serializedSceneData.begin(), serializedSceneData.end(), IsSpace),
                                  serializedSceneData.end());

        std::string sceneDataCopy = serializedSceneData;
        std::vector<std::string> entitiesData;
        // CONVERTING SCENE DATA INTO ACTUAL ENTITIES
        while (sceneDataCopy.length() > 0)
        {
            uint32 entityEndIndex = sceneDataCopy.find_first_of("%");
            std::string entityString = sceneDataCopy.substr(0, entityEndIndex + 1);
            entitiesData.push_back(entityString);
            sceneDataCopy = sceneDataCopy.substr(entityEndIndex + 1);
            SE_ENGINE_LOG(LogVerbosity::Info, "{0}", sceneDataCopy);
        }

        // CONVERT THIS STRING DATA TO COMPONENT NAME AND COMPONENT DATA
        struct DataLayout
        {
            std::vector<std::string> Data;
        };
        struct EntityData
        {
            std::vector<std::pair<std::string, DataLayout>> Components;
        };

        std::vector<EntityData> en;
        for (int i = 0; i < entitiesData.size(); ++i)
        {
            std::string& inData = entitiesData[i];
            EntityData entityData;

            while (inData.length() > 1)
            {
                size_t componentNameStartIndex = inData.find_first_of("[");
                size_t componentNameEndIndex = inData.find_first_of("]");
                size_t componentDataStartIndex = inData.find_first_of("{");
                size_t componentDataEndIndex = inData.find_first_of(";");

                std::string componentName = inData.substr(componentNameStartIndex + 1,
                                                          componentNameEndIndex - componentNameStartIndex - 1);
                std::string componentData = inData.substr(componentDataStartIndex + 1,
                                                          componentDataEndIndex - componentDataStartIndex - 2);

                DataLayout data;
                while (componentData.length() > 0)
                {
                    size_t dataSetStart = componentData.find_first_of("{");
                    size_t dataSetEnd = componentData.find_first_of("}") + 1;

                    const std::string something = componentData.substr(dataSetStart + 1, dataSetEnd - dataSetStart - 2);
                    data.Data.push_back(something);
                    componentData = componentData.substr(dataSetEnd);
                }

                entityData.Components.push_back(std::make_pair(componentName, data));
                inData = inData.substr(componentDataEndIndex + 1);
            }

            en.push_back(entityData);
        }

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

        for (int i = 0; i < en.size(); ++i)
        {
            const EntityData& e = en[i];
            entityx::Entity newEntity = entities.create();

            for (int j = 0; j < e.Components.size(); ++j)
            {
                const auto& component = e.Components[j];

                if (component.first == TagComponent::GetComponentName())
                {
                    newEntity.assign<TagComponent>(component.second.Data);
                }
                if (component.first == TransformComponent::GetComponentName())
                {
                    newEntity.assign<TransformComponent>(component.second.Data);
                }
                if (component.first == CollisionComponent::GetComponentName())
                {
                    newEntity.assign<CollisionComponent>(component.second.Data);
                }
            }

            newEntity.assign<SpriteComponent>(SVector4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }
}
