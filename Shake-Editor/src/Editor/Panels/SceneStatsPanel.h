#pragma once

#include "BasePanel.h"
#include "Shake/Core/Core.h"
#include "Shake/Scene/Scene.h"

namespace Shake
{
    class SceneStatsPanel : public BasePanel
    {
    public:
        SceneStatsPanel(SharedPtr<SceneX> scene);
        virtual ~SceneStatsPanel() {};

        void OnImGuiRender() override;
        
    private:
        SharedPtr<SceneX> m_context;
    };
}