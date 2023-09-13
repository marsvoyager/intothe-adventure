#include "stdafx.h"
using namespace std;
using namespace efm;
using namespace engine;
Engine::Player Engine::Player::factory(efm::PlayerStatusBehaviour *pstatus)
{
	if(!pstatus)
		exit(0);

	return Engine::Player(pstatus);
}

//:m_pImpl((Entity::Player::Implementation*)&m_pbpimpl)
Engine::Player::Player(Entity::StatusBehaviour *pstatusbehavinventory)
:m_pbpimpl(pstatusbehavinventory)
{
	m_pImpl=&m_pbpimpl;
	m_pbpimpl.init();	
}
Engine::Engine()
:m_Quit(false), _player(Engine::Player::factory())
{
	pplayerhandler = 
		((BehaviouralPlayerImplHandler*)_player.getImpl());	

}

void Engine::init(){
	printf("Zork Adventure Engine Player by Mars 'Martínez' Voyager");
	printf("Preview build. Use with caution"); 
	printf("loading default adventure, use 'load' to change");

	deserialize_adventure();

	if(m_Quit){
		return;
	}
	pplayerhandler->init();	
	cout << "ready?" << std::endl;
	string a("\0");
	do{
		a= peek_read(cin,true);
	}while(a[0]!='Y');
	cout << "sure?" << std::endl;
	do{
		a= peek_read(cin,true);
	}while(a[0]!='Y');
	status(_player);	
	
}
void Engine::load(string szfilename)
{

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
					cin.get();
				}
				else if(entities.size()<2){
					printf("The impossible adventure (<2 nodes)");
					m_Quit = !m_Quit;
					cin.get();
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
void Engine::handleInput()
{
	string szinput;
	//pplayerhandler = ((BehaviouralPlayerImplHandler*)_player.getImpl());

	szinput = pplayerhandler->lastAction();
	
	entities[status.getPlayindex()].query(_player);			
	
	status(_player);
	
	//TODO: maybe move to status...
	if(szinput.compare("load") == 0){
		cout << "Not implemented yet!" << std::endl;
		status(_player);
	}
	else if(szinput.compare("quit") == 0){
		m_Quit=!m_Quit;
	}
	else if(szinput.compare("status") == 0){
		status(_player);
	}
}
void Engine::update()
{	
	handleInput();
	if(entities[status.getPlayindex()].getDesc().getType() == 5){
		m_Quit=true;		
	}
}
void Engine::draw()
{
	entities[status.getPlayindex()].query(_player);
}