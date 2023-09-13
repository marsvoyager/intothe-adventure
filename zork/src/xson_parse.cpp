#include "stdafx.h"
#include <locale>
using namespace std;

std::string toUpper (std::string str, bool skipws){
	std::locale loc; 
	std::string n; 
	for (std::string::size_type i=0; i<str.length(); ++i)
	{
		if(skipws && (str[i]==' '))
			continue;	
		n += toupper(str[i], loc);
	}
		
    return n;
}
int strtoi(std::string sstr)
{
	std::stringstream str;
	str.unsetf(std::ios::skipws);
	str<<sstr;
	int res;
	str >> res;
	return res;
}

string peek_read(std::istream &_cin, bool empty){
	string res;
	stringstream sssupper;
	char c(_cin.peek());
	int done=1;
	while(done)
	{		
		if(c=='\n'){
			if(empty)
			{
				_cin.get();
				//res = cin.get();
				return res;
			}
			else
			{
				_cin.unget();
				_cin >> res;
				c = res[0];
			}
		}
		//else if((c!=NULL) && (c != -1)){			
		else if(c!=NULL)
		{
			std::getline(_cin, res);
			/*locale loc; 
			string n;
			for (string::size_type i=0; i<res.length(); ++i)
				n += toupper(res[i], loc);*/			
			done=!done;
			return res;
		}
		//else{
		//	cin.unget();
		//	cin.unget();
		//	std::getline(_cin, res);
		//	//if(_cin.eof())
		//	return res;
		//}
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