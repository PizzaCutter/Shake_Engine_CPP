#pragma once
#include "Shake/Core/Utils/Timestep.h"
#include "Shake/Events/Event.h"

namespace Shake
{
    class Layer
    {
    public:
        Layer(const SString& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep timeStep) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        const SString& GetName() const { return m_DebugName; }
    protected:
        SString m_DebugName = "";
    };
}
