#pragma once

#include "Shake/Core/Layer.h"

namespace Shake
{
    class SHAKE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;

        void Begin();
        void End();
        
        void OnImGuiRender() override;
    private:
        float m_Time = 0.0f;
    };
}
