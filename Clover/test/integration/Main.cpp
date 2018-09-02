#include "..\..\src\core\Engine.h"

int WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR cmdLine, int cmdShow)
{
	Engine::GetInstance()->Start();
	return 0;
}