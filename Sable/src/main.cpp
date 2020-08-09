#include <iostream>
#include "Shake.h"
#include "Shake/Core/EntryPoint.h"

#include "BaseLayer.h"


class Sable : public Shake::Application
{
public:
    Sable(const std::string& applicationName) : Application(applicationName)
    {
        PushLayer(new BaseLayer());
    }

    ~Sable()
    {
    }
};

Shake::Application* Shake::CreateApplication()
{
    return new Sable("Sable");
}
