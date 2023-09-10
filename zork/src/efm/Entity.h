#pragma once


#define MAX_ENTITES 500

namespace efm{
class Entity{
public:
	/////////////
	class Player{
	public:
		//
		class Implementation{
		public:
			virtual ~Implementation(){}		
		};
		//
		virtual ~Player()
		{	m_pImpl = NULL;}

		Implementation *getImpl(){return m_pImpl;}

	protected:
		Implementation *m_pImpl;
	};
	/////////////
	class Behaviour : public MRK_UTIL::Serializer{
	public:
		virtual  ~Behaviour(){}
		virtual int operator()(Player &)=0;
		
		virtual void print()=0;
	};
	/////////////
	class BehaviouralPlayerImplementationHandler : public Player::Implementation{
	public:
		virtual ~BehaviouralPlayerImplementationHandler(){}
		virtual int operator()(Behaviour *)=0;
	};
	/////////////
	class StatusBehaviour: public Behaviour{
	public:
		virtual ~StatusBehaviour(){}		
	};
	/////////////
	class ShopBehaviour: public Behaviour{
	public:
		virtual ~ShopBehaviour(){}				
		virtual int operator()(Player &player){return 0;}
		virtual void print(){std::cout << "Tienda\n";}
		virtual void deserialize_cin(std::istream &cin);
		void serialize(std::ostream &_cout);
	private:
		int maxItems;
		std::vector<std::pair<std::string,int>> items;
		int nextSite;
	};

	class FightBehaviour: public Behaviour{
	public:
		virtual ~FightBehaviour(){}				
		virtual int operator()(Player &player){					
			return 0;
		}
	virtual void deserialize_cin(std::istream &cin);
		virtual void print(){}
		virtual void serialize(std::ostream &_cout);
	private:
		int enemyAbility, enemyStrenght;
		int winNextSite, loseNextSite, fleeNextSite; 
	};

	class EndGameBehaviour: public Behaviour{
	public:
		virtual ~EndGameBehaviour(){}				
		virtual int operator()(Player &player);
		virtual void print(){}
		virtual void deserialize_cin(std::istream &cin){
		}
		virtual void deserialize(std::fstream &advf){
		}
		virtual void serialize(std::ostream &_cout){
		}
	};

	class ItemCheckBehaviour: public Behaviour{
	public:
		virtual ~ItemCheckBehaviour(){}				
		virtual int operator()(Player &player){				
			return 0;
		}
		virtual void print(){}
		virtual void deserialize_cin(std::istream &cin);

		virtual void serialize(std::ostream &_cout);
	private:
		std::string szRequestItem;
		int winNextSite, loseNextSite;
	};

	class BranchBehaviour: public Behaviour{
	public:
		virtual ~BranchBehaviour(){}				
		virtual int operator()(Player &player);
		/*virtual int operator()(Player &player){
			if(connection.size() == 0){
				return -1;
			}
			return 0;
		}*/

		//void setConnections(int max, std::vector<std::pair<std::string,int>> connection){};
		int getConnection(std::string index);//{return 0;}//;strtoi(connection.at(strtoi(index)));};
		int getmaxConnections(){return maxConnections;};
		virtual void serialize(std::ostream &_cout);
		virtual void deserialize_cin(std::istream &cin);
		virtual void deserialize(std::fstream &advf);

		virtual void print(){
			std::cout << "Doors: " << maxConnections << "\n";

			//TODO: std::find check repeating conditions before insert
				for(std::vector<std::pair<std::string,int>>::iterator it = connection.begin(); it != connection.end(); it++)
				{
					std::cout << (*it).first << " : " << (*it).second << "\n";
				}
		}
		
	private:
		int maxConnections;
		std::vector<std::pair<std::string,int>> connection;
	};
	/////
	class Desc{
	public:
		void reset(){
			m_type=-1;
			if(m_pbehave != NULL){
				delete m_pbehave;
				m_pbehave=NULL;
			}
		}
		virtual ~Desc(){
			m_type=-1;
			if(m_pbehave != NULL){
				delete m_pbehave;
				m_pbehave=NULL;
			}
		};
		//void Release()
		//{
		//	m_type = -1;
		//	m_pbehave=NULL; //should be assigned or LEAK!
		//}
		Desc(std::string bstr=std::string())
			:m_type(-1),m_bstr(bstr), m_pbehave(NULL){
		}
		Desc(const Desc &other)
			:m_type(other.m_type),m_bstr(other.m_bstr), m_pbehave(other.m_pbehave)
		{
			printf("HEYHEY");
		}
		
	
		virtual void print(bool extra=false){ 
			if(!extra)
				std::cout << m_bstr << std::endl;
			else
				std::cout << "t:" << m_type << ": " << m_bstr << std::endl;
		}
		
		Behaviour *getBehaviour(){return m_pbehave;}
		
		//void setType(int t){m_type=t;}
		int getType(){return m_type;}				

	protected:
		//const char*m_str;
		std::string m_bstr;
		Behaviour *m_pbehave;
		int m_type;
	};
	class DescSerialize: public Desc, public MRK_UTIL::Serializer
	{
	public: 
		virtual ~DescSerialize(){
			m_pbehave=NULL; //the weak_ptr should be already be copied on const "other" parent class!!
		}
		virtual void serialize(std::ostream &_cout);
		/*virtual void serialize(std::ostream &std::cout){
			std::cout << "{{t:" << m_type << "},{d:\"" << m_bstr << "\"},";
			m_pbehave->serialize(std::cout);

			std::cout << "},\n";
		}*/
		virtual void deserialize(std::fstream &advf);
		virtual void deserialize_cin(std::istream &cin);
	

	};
	/////////////

	virtual ~Entity(){};

	Desc &getDesc(){
		return m_Desc;
	}

	void Desc_serialize(const Entity &other, std::ostream &advfile)
	{
		m_Desc.serialize(advfile);
	}
	void Desc_deserialize(const Entity &other, std::fstream &advfile)
	{
		m_Desc.deserialize(advfile);
	}
	
	virtual void query(Player &p);
	/*virtual void query(Player &p){
		(*m_Desc.getBehaviour())(p);
	}*/

protected:
	DescSerialize m_Desc;
	//Behaviour *m_Behave;

	/*
	static Entity &factory(const char *pWhat){
	 return Entity();
	}*/
};

}