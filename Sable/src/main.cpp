#include <iostream>
#include "Shake.h"
#include "Shake/Core/EntryPoint.h"

#include "EditorLayer.h"


class Sable : public Shake::Application
{
public:
    Sable(const SString& applicationName) : Application(applicationName)
    {
        PushLayer(new EditorLayer());
    }

    ~Sable()
    {
    }
};

Shake::Application* Shake::CreateApplication()
{
    return new Sable("Sable");
}
