#ifndef TEXTGRAMMAR_HPP
#define TEXTGRAMMAR_HPP

#include "token.hpp"
#include <string>
#include <vector>
#include <ostream>
#include <list>
enum instructionType {RsRsS, RsR, RsS, RsSsL, RsI, RsM, R, Jump, nop};
enum argumentType {Register, integerImmediate, Label, Offset, Constant };



class argument {
    private:
        std::string value;
        argumentType type;

    public:
        argument(std::string Value, argumentType Type)
        {
            value = Value;
            type = Type;
        }
        void setValue(std::string Value) { value = Value; }
        std::string getValue() { return value; }
        void setType(argumentType Type) { type = Type; }
        argumentType getType() { return type; }
};
struct instruction {
    int lineNumber;
	instructionType type;
	std::string opcode;
    std::string name;
	std::vector<argument> instructionArguments;
};

//check for label for text grammar section
//bool checkTextLabel(std::list<Token> List);
//check for <isntruction> <register> SEP <register> SEP <source> instruction
bool checkRsRsSInstruction(std::list<Token> List);
//check for <isntruction> <register> SEP <register>
bool checkRsRInstruction(std::list<Token> List);
//check for <instruction> <register> SEP <source>
bool checkRsSInstruction(std::list<Token> List);
//check for <instruction> <register>
bool checkRInstruction(std::list<Token> List);
//check for <register> SEP <immediate>
bool checkRsIInstruction(std::list<Token> List);


//search through the inputted vector list and match the input string
bool searchInputList(std::vector <std::string> list, std::string input);



#endif
