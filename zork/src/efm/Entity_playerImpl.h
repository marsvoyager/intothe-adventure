#pragma once


#define MAX_ENTITES 500

namespace efm{

class BehaviouralPlayerImplHandler
	:public Entity::Player::Implementation
{
public:
	virtual ~BehaviouralPlayerImplHandler(){
		if(m_pstatusbehavinventory){
			delete m_pstatusbehavinventory;
			m_pstatusbehavinventory = NULL;
		}
	}
	BehaviouralPlayerImplHandler(Entity::StatusBehaviour *pstatusbehavinventory)
		:m_pstatusbehavinventory(pstatusbehavinventory)
	{		
	}
	void init();
	int operator()(Entity::EndGameBehaviour*s)
	{
		std::cout << "Thanks for playing" << std::endl;
		std::cin.get();
		return MAX_ENTITES;
		//m_Adventureidx = MAX_ENTITES;
		//return m_Adventureidx;
	}
	int operator()(Entity::StatusBehaviour*s);
	int operator()(Entity::BranchBehaviour*s);
	int operator()(Entity::ShopBehaviour*s);
	int getIndex(){return m_Adventureidx;}
	std::string lastAction(){return m_szAction;}

	/*static Entity::Player &factory(){
		Entity::Player player;
	}*/

private:
	int m_Adventureidx;
	int m_ability, m_strength, m_mney;
	std::string m_szAction;
	//Player Inventory
	Entity::StatusBehaviour *m_pstatusbehavinventory;
};
/////////////
class PlayerStatusBehaviour: public Entity::StatusBehaviour{
public:
	virtual ~PlayerStatusBehaviour(){
		m_playerImpl = NULL;
	}

	virtual int operator()(Entity::Player &player);
	virtual void print();
	int getPlayindex(){return m_playindex;}
			//in-game item management for derived classes

	//static PlayerStatusBehaviour factory();
	//static Player &factory();
private:
	BehaviouralPlayerImplHandler *m_playerImpl;
	int m_playindex;
};
}