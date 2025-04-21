#pragma once

#ifdef KJ_PLATFORM_WINDOWS

extern KJ::Application* KJ::CreateApplication();

int main(int argc, char** argv)
{
	KJ::Log::Init();
	KJ_CORE_WARN("Engine is Running.");
	int value{ 5 };
	KJ_INFO("The value is {0}", value);

	auto application = KJ::CreateApplication();
	application->Run();
	delete application;
}

#endif // KJ_PLATFORM_WINDOWS