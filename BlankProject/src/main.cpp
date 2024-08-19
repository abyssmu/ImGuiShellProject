#include "Application.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main(int, char**)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int width = 1280;
	int height = 720;
	string name = "Physics Sim";
	bool demo = true;

	unique_ptr<App::Application> app{ new App::Application(width, height, name) };
	app->Run(demo);

	return 0;
}