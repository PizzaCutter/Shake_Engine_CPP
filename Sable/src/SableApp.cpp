#include <iostream>
#include "Shake.h"
#include "Shake/Core/EntryPoint.h"

#include "Editor/SableLayer.h"


class SableApp : public Shake::Application
{
public:
    SableApp(const SString& applicationName) : Application(applicationName)
    {
        PushLayer(new Shake::SableLayer());
    }

    ~SableApp()
    {
    }
};

Shake::Application* Shake::CreateApplication()
{
    return new SableApp("Sable");
}
