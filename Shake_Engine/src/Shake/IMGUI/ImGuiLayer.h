#pragma once

#include "Shake/Core/Layer.h"

namespace Shake
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;

        void OnEvent(Event& event) override; 
        
        void Begin();
        void End();
        
        void OnImGuiRender() override;

        void BlockEvents(bool newState)
        {
           m_blockEvents = newState; 
        }
    private:
        bool m_blockEvents = false;
        float m_Time = 0.0f;
    };
}
