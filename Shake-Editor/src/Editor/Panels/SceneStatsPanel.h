#pragma once

#include "BasePanel.h"
#include "Shake/Core/Core.h"
#include "Shake/Scene/Scene.h"

namespace Shake
{
    class SceneStatsPanel : public BasePanel
    {
    public:
        SceneStatsPanel(SharedPtr<Scene> scene);
        virtual ~SceneStatsPanel() {};

        void OnImGuiRender() override;
        
    private:
        SharedPtr<Scene> m_context;
    };
}