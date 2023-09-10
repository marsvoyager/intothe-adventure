#pragma once


#define MAX_ENTITES 500

namespace efm{

class BehaviouralPlayerImplHandler:public Entity::Player::Implementation
{
public:
	virtual ~BehaviouralPlayerImplHandler(){}
	void init();
	int operator()(Entity::StatusBehaviour*s);
	int operator()(Entity::BranchBehaviour*s);
	int getIndex(){return m_Adventureidx;}
	std::string lastAction(){return m_szAction;}
private:
	int m_Adventureidx;
	int m_ability, m_strength, m_mney;
	std::string m_szAction;

};
/////////////
class PlayerStatusBehaviour: public Entity::StatusBehaviour{
public:
	virtual ~PlayerStatusBehaviour(){}
	virtual int operator()(Entity::Player &player);
	virtual void print(){std::cout << "Status:";}
	int getPlayindex(){return m_playindex;}
private:
	BehaviouralPlayerImplHandler *m_playerImpl;
	int m_playindex;
};
}