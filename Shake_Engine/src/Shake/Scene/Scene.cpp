#include "sepch.h"
#include "Scene.h"

#include <entt.hpp>

namespace Shake
{
    void SceneX::SaveScene()
    {
        std::string sceneData = ""; 
        entities.each<TagComponent, TransformComponent>([this, &sceneData](entityx::Entity entity, TagComponent& tagComponent, TransformComponent& transformComponent)
        {
            sceneData += tagComponent.serialize() + ";\n\t" + transformComponent.serialize() + ";%" + "\n";
        });
        SE_ENGINE_LOG(LogVerbosity::Verbose, "\n{0}", sceneData);

        std::ofstream sceneFile;
        // TODO[rsmekens]: pull this from a file
        sceneFile.open ("scene.shake");
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
        while (getline (sceneFile, lineData))
        {
            serializedSceneData += lineData + "\n"; 
        }
        sceneFile.close();
        
        serializedSceneData.erase(std::remove_if(serializedSceneData.begin(), serializedSceneData.end(), IsSpace), serializedSceneData.end());

        std::string sceneDataCopy = serializedSceneData;
        std::vector<std::string> entitiesData;
        // CONVERTING SCENE DATA INTO ACTUAL ENTITIES
        while(sceneDataCopy.length() > 0)
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
            
            while(inData.length() > 1)
            {
                size_t componentNameStartIndex = inData.find_first_of("[");
                size_t componentNameEndIndex = inData.find_first_of("]");
                size_t componentDataStartIndex = inData.find_first_of("{");
                size_t componentDataEndIndex = inData.find_first_of(";");
                // if(componentDataEndIndex == std::string::npos)
                // {
                //    componentDataEndIndex = inData.find_first_of("%");
                // }

                std::string componentName = inData.substr(componentNameStartIndex + 1, componentNameEndIndex - componentNameStartIndex - 1);
                std::string componentData = inData.substr(componentDataStartIndex + 1, componentDataEndIndex - componentDataStartIndex - 2);

                DataLayout data;
                while(componentData.length() > 0)
                {
                    size_t dataSetStart = componentData.find_first_of("{");
                    size_t dataSetEnd = componentData.find_first_of("}") + 1;

                    const std::string something = componentData.substr(dataSetStart + 1, dataSetEnd - dataSetStart - 2);
                    data.Data.push_back(something);
                    componentData = componentData.substr(dataSetEnd); 
                }

                entityData.Components.push_back(std::make_pair(componentName, data));
                
                //size_t index = std::clamp(static_cast<int>(componentDataEndIndex + 1), 0, static_cast<int>(inData.size())); 
                inData = inData.substr(componentDataEndIndex + 1);
            }
            
            en.push_back(entityData);
            
            SELOG(LogVerbosity::Verbose, "{0}", entitiesData[i]); 
        }

        for (int i = 0; i < en.size(); ++i)
        {
            const EntityData& e  = en[i];
            entityx::Entity newEntity = entities.create();

            for (int j = 0; j < e.Components.size(); ++j)
            {
                const auto& component = e.Components[j];

                // TODO[rsmekens]: remove magic number
                // if(component.first == TagComponent::GetComponentName())
                // {
                //     newEntity.assign<TagComponent>(component.second); 
                // }
                if(component.first == TransformComponent::GetComponentName())
                {
                    newEntity.assign<TransformComponent>(component.second.Data); 
                }
            }
            
            newEntity.assign<SpriteComponent>(SVector4(1.0f, 1.0f, 1.0f, 1.0f));
        }
    }
}
