#include "Application.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(int, char**)
{
	int width = 1280;
	int height = 720;
	std::string name = "Physics Sim";
	bool demo = false;

	std::unique_ptr<App::Application> app = std::make_unique<App::Application>();
	if(app->Init(name, width, height)) app->Run(demo);

	return 0;
}