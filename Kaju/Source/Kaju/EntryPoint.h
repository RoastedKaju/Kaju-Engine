#pragma once

#ifdef KJ_PLATFORM_WINDOWS

extern KJ::Application* KJ::CreateApplication();

int main(int argc, char** argv)
{
	KJ::Log::Init();
	KJ_CORE_WARN("Engine is Running.");

	auto application = KJ::CreateApplication();
	application->Run();
	delete application;
}

#endif // KJ_PLATFORM_WINDOWS