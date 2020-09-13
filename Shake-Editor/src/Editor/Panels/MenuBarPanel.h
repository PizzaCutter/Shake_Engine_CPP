#pragma once

#include "BasePanel.h"
#include "Shake/Core/Core.h"
#include "Shake/Scene/Scene.h"

namespace Shake
{
    class MenuBarPanel : public BasePanel
    {
    public:
        MenuBarPanel(SharedPtr<Scene> scene);
        virtual ~MenuBarPanel() {}

        void OnImGuiRender() override;
    };
}