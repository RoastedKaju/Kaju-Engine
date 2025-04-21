#include <Kaju.h>

class Sandbox : public KJ::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}


};

KJ::Application* KJ::CreateApplication()
{
	return new Sandbox();
}