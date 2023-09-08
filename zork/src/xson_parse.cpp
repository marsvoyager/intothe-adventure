#include "stdafx.h"

using namespace std;

int strtoi(std::string sstr)
{
	std::stringstream str;
	str.unsetf(std::ios::skipws);
	str<<sstr;
	int res;
	str >> res;
	return res;
}

string peek_read(std::istream &cin, bool empty){
	string res;
	char c(cin.peek());
	int done=1;
	while(done)
	{		
		if(c=='\n'){
			if(empty)
			{
				cin.get();
				//res = cin.get();
				return res;
			}
			else
			{
				cin.unget();
				cin >> res;
				c = res[0];
			}
		}
		else if(c!=NULL){
			cin >> res;
			cin.get();
			done=!done;
			return res;		
		}
	}
	return res;

/*
/*if(cin.peek() == '\n')
					{						
						cin.get();
					}
					else{
						cin.unget();
						cin >> std::ws  >> m_bstr;
					}*/

}

/*
 Use to detect JSON-style begin/end token of classes, arrays, etc.
*/
int xson_token(std::fstream &f_in, const char token)
{
	char delim;
	//f_in >> delim;
	delim=f_in.get();
	return (delim == token) && f_in.good(); 
}
/*
	parse type data
*/
int xson_data(std::fstream &f_in, int &data)
{
	f_in >> data;
	return f_in.good();
}
/*
 Parse strings data according to "token"Whatever string format"token" 
*/
int xson_data(std::fstream &f_in, std::string &data, const char token)
{
	char delim;
	data.empty();
	f_in >> delim;
	if(delim != token)
		return data.length();
	//reads until string end token
	std::getline(f_in, data, delim);
	
	return (!data.empty()) && f_in.good();
}