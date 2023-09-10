// main.cpp: define el punto de entrada de la aplicación de consola.
#include "stdafx.h"



using namespace std;
using namespace MRK_UTIL;
using namespace efm;
/*
 JSON-like serialization
*/
void Entity::DescSerialize::serialize(std::ostream &_cout){
	_cout << "{{t:" << m_type << "},{d:\"" << m_bstr << "\"},";
	m_pbehave->serialize(_cout);

	_cout << "},";
}
/*

*/
void Entity::DescSerialize::deserialize(std::fstream &advf)
{
	if( xson_token(advf, '{') && xson_token(advf, '{')
		&& xson_token(advf, 't') && xson_token(advf, ':'))
	{						
		if(xson_data(advf, m_type)){
			if( xson_token(advf, '}') && xson_token(advf, ',')
				&& xson_token(advf, '{') && xson_token(advf, 'd')
				&& xson_token(advf, ':')){
					if(xson_data(advf, m_bstr))
					{
						if( xson_token(advf, '}') && xson_token(advf, ','))
						{
							if(m_type == -1)
								return;
						}
						//read ok: read behaviour										
					}
				}							
			}
		}
		//Desc_deserialize((*this), f_in);
		//read ok: deserialize behaviour
		if(m_type<1 || m_type > 5)
		{	
			m_type = -1;
			return;
		}

		switch(m_type)
		{
		case 1:
			m_pbehave = new BranchBehaviour();
			break;
		case 2:
			m_pbehave = new FightBehaviour();
			break;						
		case 3:
			m_pbehave = new ShopBehaviour();
			break;						
		case 4:
			m_pbehave = new ItemCheckBehaviour();
			break;						
		case 5:
			m_pbehave = new EndGameBehaviour();
			break;						
		default:
			m_type = -1;
			m_pbehave = NULL;					
		}					
		if(!m_pbehave)
		{
			m_type = -1;
			return;
		}
		m_pbehave->deserialize(advf);
		

		if(  xson_token(advf, '}')  && xson_token(advf, ','))
		{
			print();
		}
		else
		{
			m_type = -1;
		}
}


