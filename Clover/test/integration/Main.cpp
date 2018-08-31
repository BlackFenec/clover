#include "..\core\Engine.h"

int main()
{
	//Vector2D a(0, 4), b(4, 0);
	//double c = a.DotProduct(b);
	//Entity * tt = EntityManager::GetInstance()->CreateEntity({ new PositionComponent(1,1) });
	//tt->GetGuid();
	////std::pair<GUID, Entity*>(tt->GetGuid(), tt);
	//EntityManager::GetInstance()->CreateEntity({ new PositionComponent(2,4) });

	Engine* e = new Engine();
	e->Start();
	return 0;
}