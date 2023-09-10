// main.cpp: define el punto de entrada de la aplicación de consola.
#include "stdafx.h"

using namespace std;
using namespace efm;

class Engine{
	public:
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

		virtual ~Engine(){}
		Engine()
			:m_Quit(false)
		{}
		void load(string szfilename){

			class EntitySerialize:public Entity, public Serializer{
				public:
					virtual ~EntitySerialize(){
					}
					EntitySerialize(){				
					}
					EntitySerialize(const Entity &other)
						:Entity(other){				
					}

					EntitySerialize(std::fstream &f_in){
						deserialize(f_in);
					}
					
					EntitySerialize(std::istream &cin){
						deserialize_cin(cin);
					}
					virtual void serialize(std::ostream &advfile){
											
						advfile << "{";
						Desc_serialize((*this), advfile);
						advfile << "}," << std::endl;
					}
					virtual void deserialize(std::fstream &f_in){
						if( xson_token(f_in, '{'))
						{
							Desc_deserialize((*this), f_in);

							if( !xson_token(f_in, '}') || !xson_token(f_in, ','))
							{
								//reset!
								
								m_Desc.reset();
								return;				
							}
						}				
					}
					
					virtual void deserialize_cin(std::istream &cin){
						
						m_Desc.deserialize_cin(cin);

						int type = m_Desc.getType();
						
						Behaviour *pbv = m_Desc.getBehaviour();
						if(type == -1 || !pbv)
						{
							return;				
						}
						pbv->deserialize_cin(cin);

						Player test;
						if((*pbv)(test) == -1){
							cout << "Inconsistent Player state\n";
							m_Desc.~DescSerialize();
							return;
						}
					}
				};
			//class end EntitySerialize
			///////////////////////////////////////////////////////////
			
			bool endDefinition = false;
			string path("test\\");
			path += szfilename;

			fstream advfile;
			advfile.open(path.c_str(), ios::in);
			if(advfile.is_open()){
				entities.clear();
				endDefinition=false;
				while(!endDefinition){
					entities.push_back(EntitySerialize (advfile));
					
					if(entities.back().getDesc().getType()==-1)
					{
						entities.pop_back();
						endDefinition=!endDefinition;
						if(!advfile.eof())
						{
							printf("Mismatch EOF, error in definition file!");
							m_Quit = !m_Quit;
						}
						else{
							printf("Level loaded!\n");
						
						}
					}
				}		
			
			//for(std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); it++)
			//{
			//	entities.push_back(EntitySerialize(advfile));

			////	//EntitySerialize entout(*it);
			////	//entout.deserialize(advfile);		
			//}
		
			advfile.close();		
			}

		
		}
		void deserialize_adventure()
		{
			//EntitySerialize newEnt(cin);
			//e.addEntity(newEnt);
			load("zork.jzo");
		}
		virtual void init(){
			printf("Zork Adventure Engine Player by Mars 'Martínez' Voyager");
			printf("loading default adventure, use 'load' to change");

			deserialize_adventure();
		}
		
		virtual void start(){
			while(!m_Quit)
			{
				update();
				draw();
			}			
		}
		virtual void handleInput()
		{
			string szinput;
			szinput = peek_read(cin,true);
			if(szinput.compare("quit") == 0){
				m_Quit=!m_Quit;
			}
		}
		virtual void update()
		{
			handleInput();

		}
		virtual void draw(){}

		virtual void addEntity(Entity &entity){}
		virtual void removeEntity(){}
		virtual void addSystem(){}
		virtual void removeSystem(){}
private:
	bool m_Quit;
	std::vector<Entity> entities;
	};

int _tmain(int argc, _TCHAR* argv[])
{
	Engine engine;
	engine.init();

	

	engine.start();
	return 0;
}