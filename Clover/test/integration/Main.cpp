#include "..\..\src\core\Engine.h"

int WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR cmdLine, int cmdShow)
{
	Engine* e = new Engine();
	e->Start();
	return 0;
}