#include "sdpch.h"
#include "Engine/Engine.h"

int main(int argc, char** argv)
{
	Shadow::Engine::Instance()->InitEngine();

	Shadow::Engine::Instance()->Run();
	
	Shadow::Engine::Instance()->DestroyEngine();

	return 0;
}