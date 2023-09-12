#pragma once


namespace engine{
class Engine{
	public:
		//////////
		class Player:public efm::Entity::Player{
		public:
			virtual ~Player(){}
		protected:
			Player(efm::Entity::StatusBehaviour *pstatusbehavinventory);
		
		public:
			static Player factory(efm::PlayerStatusBehaviour *pstatus=new efm::PlayerStatusBehaviour());

		private:
			efm::BehaviouralPlayerImplHandler m_pbpimpl;
		};
		//////////

		virtual ~Engine(){}
		Engine();
		void load(std::string szfilename);
		void deserialize_adventure()
		{
			//EntitySerialize newEnt(cin);
			//e.addEntity(newEnt);
			load("zork.jzo");
		}
		virtual void init();
		
		virtual void start(){
			while(!m_Quit)
			{
				update();
				draw();
			}			
		}
		virtual void handleInput();
		virtual void update();
		virtual void draw();

		/*virtual void addEntity(Entity &entity){}
		virtual void removeEntity(){}
		virtual void addSystem(){}
		virtual void removeSystem(){}*/
private:
	bool m_Quit;
	std::vector<efm::Entity> entities;
	efm::PlayerStatusBehaviour status;
	Player _player;
	efm::BehaviouralPlayerImplHandler *pplayerhandler;
};

}