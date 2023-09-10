// main.cpp: define el punto de entrada de la aplicación de consola.
#include "stdafx.h"

#include <algorithm>
using namespace std;
using namespace efm;

void Entity::query(Player &p){
	getDesc().print();
	(*m_Desc.getBehaviour())(p);
}
int Entity::EndGameBehaviour::operator()(Entity::Player &player)
{
	return 0;
}
int PlayerStatusBehaviour::operator()(Entity::Player &player)
{
	print();
	m_playindex = (*((BehaviouralPlayerImplHandler*)player.getImpl()))(this);
	return m_playindex;
}

int Entity::BranchBehaviour::operator()(Entity::Player &player){
	if(connection.size() == 0){
		return -1;
	}
	(*((BehaviouralPlayerImplHandler*)player.getImpl()))(this);

	return 0;
}

void BehaviouralPlayerImplHandler::init()
{
	m_Adventureidx = 0;	

	m_ability = 10+(rand()%10);
	m_strength= 10+(rand()%10);
	m_mney = 200+(rand()%100);
	m_szAction="";
}

int BehaviouralPlayerImplHandler::operator()(Entity::StatusBehaviour*s)
{
	if(m_szAction.empty()){
		cout << "Your ability " << m_ability << std::endl;
		cout << "Your strength " << m_strength << std::endl;
		cout << "You have " << m_mney << (char)234 << std::endl;
	}
	m_szAction.clear();

	return m_Adventureidx;
}
int Entity::BranchBehaviour::getConnection(std::string index)
{
	//std::pair<std::string,int> item(index,);
	//pbranch = std::find(connection.begin(), connection.end()
	std::vector<std::pair<std::string,int>>::const_iterator pbranch;
	pbranch = connection.begin();
	while(pbranch !=  connection.end()){
		if(pbranch->first.compare(index)==0){
			return pbranch->second;
		}
		pbranch++;
	}

	return -1;
}
int BehaviouralPlayerImplHandler::operator()(Entity::BranchBehaviour*s)
{
	int nextindex=-1;
	if(!m_szAction.empty())
	{
		nextindex = s->getConnection(m_szAction);
		if(nextindex!=-1){
			m_szAction.clear();
			m_Adventureidx = nextindex;
		}
	}
	else
		m_szAction=peek_read(std::cin,true);

	return m_Adventureidx;

}