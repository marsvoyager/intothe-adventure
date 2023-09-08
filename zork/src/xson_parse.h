#pragma once

/*
 Use to detect JSON-style begin/end token of classes, arrays, etc.
*/
int xson_token(std::fstream &f_in, const char token='{');
int xson_data(std::fstream &f_in, int &data);

/*
 Parse strings data according to "token"Whatever string format"token" 
*/
int xson_data(std::fstream &f_in, std::string &data, const char token='\"');