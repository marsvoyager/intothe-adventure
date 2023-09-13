// main.cpp: define el punto de entrada de la aplicación de consola.
#include "stdafx.h"

#include <algorithm>

using namespace std;
using namespace MRK_UTIL;
using namespace efm;


struct FindBy_ItemDesc
{
public:
//bool operator()(T  &lhs) const

//bool operator()(std::vector<Entity::ShopBehaviour::ItemPair>::iterator  &lhs)
//bool operator==(Entity::ShopBehaviour::ItemPair const &lhs) const
bool operator()(Entity::ShopBehaviour::ItemPair const  &lhs) const
{ 	
	
	string res;
	
	return toUpper(lhs.first,true).compare(rhsitem)==0; 
}
string rhsitem;
//std::stringstream szupper;
};


void Entity::ShopBehaviour::addItem(Entity::ShopBehaviour::ItemPair itemdata, Entity::ShopBehaviour &merkat)
{
	items.push_back(itemdata);
}
void Entity::ShopBehaviour::removeItem(Entity::ShopBehaviour::ItemPair itemdata, Entity::ShopBehaviour &merkat)
{
	items.erase(
		std::find(items.begin(), items.end(), itemdata));
}

Entity::ShopBehaviour::itemit Entity::ShopBehaviour::getItem(string itemdesc)
{	
	if(itemdesc.empty())
		return items.end();
	
	FindBy_ItemDesc upcasecompare;

	upcasecompare.rhsitem = toUpper(itemdesc,true);
	
	return (std::find_if(
		items.begin(), items.end(), upcasecompare));

	//return Entity::ShopBehaviour::ItemPair("",0);
}

void Entity::ShopBehaviour::serialize(std::ostream &_cout){
	_cout << "{{m:" << maxItems << "},[";
	for(std::vector<std::pair<std::string,int>>::iterator it = items.begin(); it != items.end(); it++)
	{
		_cout << "(\"" << (*it).first <<"\"," << (*it).second << ")";					
	}
	_cout << "],{n:" << nextSite << "},";
	_cout << "},";
}
void Entity::ShopBehaviour::deserialize(std::fstream &advf)
{
	int branchcnt = 0;
	std::string itemdesc;
	int itemcost;

	if( xson_token(advf, '{') && xson_token(advf, '{')
		&& xson_token(advf, 'm') && xson_token(advf, ':'))
	{
		if(xson_data(advf, maxItems)){
			if( xson_token(advf, '}') && xson_token(advf, ',')
				&& xson_token(advf, '[')){
					do{
						if( xson_token(advf, '(') && xson_data(advf, itemdesc, '\"')){
							if( xson_token(advf, ',') && xson_data(advf, itemcost)){
								/*if(branchdest>MAX_ENTITES){
									connection.clear();
									maxConnections=0;
									return;
								}*/
								if( xson_token(advf, ')')){
									items.push_back(std::pair<std::string,int>(itemdesc,itemcost));
									branchcnt++;
								}
								else{
									items.clear();
									maxItems=0;
									return;
								}
							}										
						}
					}while(branchcnt < maxItems);

					if(!( xson_token(advf, ']')  && xson_token(advf, ',')))
					{
						items.clear();
						maxItems=0;
						return;
					}
					if( xson_token(advf, '{') && xson_token(advf, 'n') && xson_token(advf, ':')
						&& xson_data(advf, nextSite))
					{
						//TODO:WARNING!
						nextSite--;
						if(nextSite>MAX_ENTITES) 
						{
							items.clear();
							maxItems=0;
							return;
						}
						if( !( xson_token(advf, '}')  && xson_token(advf, ',')
							&& xson_token(advf, '}')  && xson_token(advf, ',')))
						{
							items.clear();
							maxItems=0;
							return;
						}
					}
			}				
		}
	}	
}

/*
*/
void Entity::FightBehaviour::serialize(std::ostream &_cout){
	_cout << "{{enemyAbility:" << enemyAbility << "},";
	_cout << "{enemyStrenght:" << enemyAbility << "},";
	_cout << "{winNextSite:" << winNextSite << "},";
	_cout << "{loseNextSite:" << loseNextSite << "},";
	_cout << "{fleeNextSite:" << fleeNextSite << "},";
	_cout << "}," << std::endl;
}
void Entity::ItemCheckBehaviour::serialize(std::ostream &_cout)
{
	_cout << "{{szRequestItem:" << szRequestItem << "},";
	_cout << "{winNextSite:" << winNextSite << "},";
	_cout << "{loseNextSite:" << loseNextSite << "},";					
	_cout << "}," << std::endl;
}
void Entity::BranchBehaviour::serialize(std::ostream &_cout)
{
	_cout << "{{m:" << maxConnections << "},[";
	for(std::vector<std::pair<std::string,int>>::iterator it = connection.begin(); it != connection.end(); it++)
	{
		_cout << "(\"" << (*it).first <<"\"," << (*it).second << ")";					
	}
	//TODO
	_cout << "]}," << std::endl;
}
void Entity::EndGameBehaviour::deserialize(std::fstream &advf)
{

}
void Entity::BranchBehaviour::deserialize(std::fstream &advf)
{
	int branchcnt = 0;
	std::string branchdesc;
	int branchdest;

	if( xson_token(advf, '{') && xson_token(advf, '{')
		&& xson_token(advf, 'm') && xson_token(advf, ':'))
	{						
		if(xson_data(advf, maxConnections)){
			if( xson_token(advf, '}') && xson_token(advf, ',')
				&& xson_token(advf, '[')){
					do{
						if( xson_token(advf, '(') && xson_data(advf, branchdesc, '\"')){
							if( xson_token(advf, ',') && xson_data(advf, branchdest)){
								if(branchdest>MAX_ENTITES){
									connection.clear();
									maxConnections=0;
									return;
								}
								if( xson_token(advf, ')')){
									connection.push_back(std::pair<std::string,int>(branchdesc,branchdest-1));
									branchcnt++;
								}
								else{
									connection.clear();
									maxConnections=0;
									return;
								}
							}										
						}
					}while(branchcnt < maxConnections);

					if(!( xson_token(advf, ']') && xson_token(advf, '}') && xson_token(advf, ',')))
					{
						connection.clear();
						maxConnections=0;
						return;
					}
			}				
		}
	}
}
