#ifndef DATAGRAMMAR_HPP
#define DATAGRAMMAR_HPP


#include "token.hpp"
#include <string>
#include <vector>
#include <ostream>
#include <list>
#include <sstream>
#include <iterator>
#include <iostream>

//helper functions that check the data grammar
//checking if input token has an appropriate constant name
bool checkVariableName(Token input);
//check if the input token has an appropriate label name
bool checkLabelName(Token input);
//check if the input token has an appropriate label name
bool checkLabelStringName(Token input);
//checking if the input list has the appropriate tokens for a label
bool checkLabel(std::list<Token> List);
//checking if the input list has the appropriate tokens for a Constant
bool checkConstant(std::list<Token> List);
//checking if the input token is an appropriate integer
bool checkInteger(Token input);
//checking if the in the input string is an appropriate integer
bool checkIntegerString(std::string inputString);
//checks the list of tokens if it is a layout parameter
bool checkGeneralLayout(std::list<Token> List);

//checks the list of tokens if it a string layout 
bool checkStringLayout(std::list<Token> List);
//checks the list of tokens if it a string layout
bool checkIntLayout(std::list<Token> List);
//checks the list of tokens if it is a list of integers
bool checkListOfIntegers(std::list<Token> List);

//returns element in list
Token getListElement(std::list<Token> List, int position);
// prints a 2d array
//void print2dArray(std::list<std::list<Token>> List);
// creates a 2d array list of tokens
std::list<std::list<Token>> create2dDataArray(TokenList tokens);


#endif