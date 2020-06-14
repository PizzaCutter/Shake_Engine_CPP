#include <iostream>
#include "Shake.h"

class Sable : public Shake::Application
{
public:
	Sable(const std::string& applicationName) : Application(applicationName)
	{
		
	}

	~Sable()
	{
		
	}
};

Shake::Application* Shake::CreateApplication()
{
	return new Sable("Sable");
}
