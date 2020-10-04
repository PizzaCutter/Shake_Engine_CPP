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
    void to_json(json& j, const OtherComponent& p){
        j = json{{"floatNumber", p.floatNumber}};
    }
    void to_json(json& j, const TestComponent& p){
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
        j = json{{"ComponentName", p->ComponentName}, {"IntNumber", p->testNumber}, {"OtherNumber", p->otherTestNumber}};
        
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
        ///std::cout << std::setw(4) << root << std::endl;

        //Unregistered y;
        //json root2 = y; // this will fail at compile time

        printSeparator();

        std::cout << "Serializing Person 2 from JSON:\n";

        auto person2 = root.get<Person>();
        std::cout << "Person 2 name is " << person2.getName() << " too!" << '\n';
    }

    void SceneX::TestOwnMetaStuff()
    {
        TransformComponent transformComponent{SVector3(0.0f)};

        // printing members of different classes
        std::cout << "Members of class Person:\n";
        meta::doForAllMembers<TransformComponent>(
            [](const auto& member)
        {
            std::cout << "* " << member.getName() << '\n';
        }
        );

        printSeparator();

        // checking if classes are registered
        if (meta::isRegistered<TransformComponent>()) {
            std::cout << "TransformComponent class is registered\n";
            std::cout << "It has " << meta::getMemberCount<TransformComponent>() << " members registered.\n";
        }

        // checking if class has a member
        if (meta::hasMember<TransformComponent>("rotation")) {
            std::cout << "TransformComponent has member named 'rotation'\n";
        }

        // getting members
        auto rotation = meta::getMemberValue<float>(transformComponent, "rotation");
        std::cout << "Got transform rotation: " << rotation << '\n';

        // setting members
        meta::setMemberValue<float>(transformComponent, "rotation", 1.0f);
        rotation = meta::getMemberValue<float>(transformComponent, "rotation");
        std::cout << "Changed rotation to" << rotation << '\n';

        printSeparator();

        // And here's how you can serialize/deserialize
        // (if you write a function for your type)
        std::cout << "Serializing transformComponent:" << '\n';
        json root = transformComponent;
        //std::cout << std::setw(4) << root << std::endl;


        auto testTransformComponent = root.get<TransformComponent>();
        rotation = meta::getMemberValue<float>(testTransformComponent, "rotation");
        std::cout << "Changed rotation to" << rotation << '\n'; 
        
        // MetaTestComponent component;
        // component.test = 5.0f;
        // json root(component);
        // std::cout << std::setw(4) << root << std::endl;
    }



    void SceneX::SaveScene()
    {
        // std::vector<ns::TestEntity> entityList;
        //
        // ns::TestEntity entity_01("entity_01");
        // ns::TestComponent* testComponent_01 = new ns::TestComponent();
        // testComponent_01->integerNumber = 100;
        // testComponent_01->testNumber = 200;
        // entity_01.Components.push_back(testComponent_01);
        //
        // entity_01.Components.push_back(new ns::OtherComponent());
        // entityList.push_back(entity_01);
        //
        // ns::TestEntity entity_02("entity_02");
        // entity_02.Components.push_back(new ns::TestComponent());
        // entity_02.Components.push_back(new ns::OtherComponent());
        // entityList.push_back(entity_02);
        //
        // json tagRoot(entityList);
        // //tagRoot.push_back(entity_01);
        // //tagRoot.push_back(entity_02);
        // //std::string sceneData = tagRoot.dump();
        // std::string sceneData = tagRoot.dump();
        //
        // std::cout << sceneData << std::endl;
            
        //TestMetaStuff();
        //TestOwnMetaStuff();
        
        std::string sceneData = "";
        // sceneData += '"';
        // sceneData += "entities";
        // sceneData += '"';
        // sceneData += ": \n[";
        //
        json jsonEntities;
        entities.each<TagComponent>(
            [this, &sceneData, &jsonEntities](entityx::Entity entity, TagComponent& tagComponent)
            {
                json jsonEntity;
                jsonEntity.push_back(tagComponent);

                if(entity.has_component<TransformComponent>())
                {
                   jsonEntity.push_back(*entity.component<TransformComponent>().get()); 
                }
                if(entity.has_component<CollisionComponent>())
                {
                   //jsonEntity.push_back(*entity.component<CollisionComponent>().get()); 
                   //jsonEntity.push_back(entity.component<CollisionComponent>()); 
                }
                if(entity.has_component<SpriteComponent>())
                {
                   //jsonEntity.push_back(*entity.component<TransformComponent>().get()); 
                   //jsonEntity.push_back(entity.component<SpriteComponent>());
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
        
        for (auto element : jf.items())
        {
            entityx::Entity newEntity = entities.create();
            for(json::iterator it = element.value().begin(); it != element.value().end(); ++it)
            {
                nlohmann::basic_json<> temp = it.value();
                nlohmann::basic_json<>::iterator otherTemp = temp.find("name");

                if(otherTemp.value() == "TagComponent")
                {
                    TagComponent newTagComp;
                    from_json(temp, newTagComp);
                    newEntity.assign<TagComponent>(newTagComp);
                }
                if(otherTemp.value() == "TransformComponent")
                {
                     TransformComponent newTransformComponent;
                     from_json(temp, newTransformComponent);
                     newEntity.assign<TransformComponent>(newTransformComponent);
                }
            }

            newEntity.assign<SpriteComponent>(SVector4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }
}
