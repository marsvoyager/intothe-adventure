// main.cpp: define el punto de entrada de la aplicación de consola.
#include "stdafx.h"

using namespace std;
using namespace efm;
using namespace engine;

int _tmain(int argc, _TCHAR* argv[])
{
	Engine engine;
	engine.init();

		////
		//class Entity{
		//public:
		//	class InheritedComponent{
		//	public:
		//		virtual ~InheritedComponent(){}
		//	};
		//	virtual ~Entity(){} 

		//	template<typename T>
		//	Entity *addComponent(InheritedComponent *){return this;}

		//	template<typename T>
		//	Entity *removeComponent(InheritedComponent *){return this;}
		//	
		//};
		//class System{
		//public:
		//	class InheritedProps{
		//	public:
		//		virtual ~InheritedProps(){}
		//	};
		//	virtual ~System(){}
		//	virtual void onEntityAdded(Entity &){}
		//	virtual void onEntityRemoved(Entity &){}
		//	virtual void onSystemAdded(Engine *){}
		//	virtual void onSystemRemoved(Engine *){}
		//};
		////


	engine.start();
	return 0;
}