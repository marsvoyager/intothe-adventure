#pragma once
#include <locale> 
//merged on xson_parse.cpp
/*
 atoi in c++style, might skip empty spaces
*/
int strtoi(std::string sstr);

/*
 use this to force or not to read an empty buffer from the console,
 depending on flag, accept newline finish filling input
*/
std::string peek_read(std::istream &cin, bool empty=false);


std::string toUpper (std::string str, bool skipws=false);