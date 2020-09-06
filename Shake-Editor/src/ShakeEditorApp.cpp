#include <iostream>
#include "Shake.h"
#include "Shake/Core/EntryPoint.h"

#include "EditorLayer.h"


class ShakeEditor : public Shake::Application
{
public:
    ShakeEditor(const SString& applicationName) : Application(applicationName)
    {
        PushLayer(new Shake::EditorLayer());
    }

    ~ShakeEditor()
    {
    }
};

Shake::Application* Shake::CreateApplication()
{
    return new ShakeEditor("Sable");
}
