#pragma once

#include "Shake/Core/Core.h"
#include "Shake/Scene/Scene.h"

namespace Shake
{
class BasePanel
{
public:
    BasePanel() {};
    BasePanel(SharedPtr<Scene> scene)
    {
        BasePanel::SetContext(scene);
    };
    virtual ~BasePanel() {};

    virtual void SetContext(const SharedPtr<Scene>& scene)
    {
        m_currentScene = scene;    
    }

    virtual void OnImGuiRender() = 0;
protected:
    SharedPtr<Scene> m_currentScene;
};
}
