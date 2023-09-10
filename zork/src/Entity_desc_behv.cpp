// main.cpp: define el punto de entrada de la aplicación de consola.
#include "stdafx.h"



using namespace std;
using namespace MRK_UTIL;
using namespace efm;

void Entity::ShopBehaviour::serialize(std::ostream &_cout){
	_cout << "{maxitems:" << maxItems << ",[";
	for(std::vector<std::pair<std::string,int>>::iterator it = items.begin(); it != items.end(); it++)
	{
		_cout << "(\"" << (*it).first <<"\"," << (*it).second << ")";					
	}
	_cout << "],{nextsite:" << nextSite << "},";
	_cout << "},";
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
									connection.push_back(std::pair<std::string,int>(branchdesc,branchdest));
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
