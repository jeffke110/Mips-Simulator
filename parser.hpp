#ifndef PARSER_HPP
#define PARSER_HPP

// define the parser module here

#include "lexer.hpp"
#include "token.hpp"
#include "dataGrammar.hpp"
#include "textGrammar.hpp"
#include <string>
#include <vector>
#include <unordered_map>


struct labelType {
	bool isTextLabel;
	size_t instructionIndex;
	size_t lineNumber;
};

class Parser
{
private:
	//vector string of registers
	std::vector <std::string> registerList = {
		"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2","$a3",
		"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
		"$s0","$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
		"$t8", "$t9", "$k0","$k1", "$gp", "$sp", "$fp", "$ra",
		"$0", "$1", "$2","$3", "$4", "$5", "$6", "$7", "$8", "$9",
		"$10", "$11", "$12","$13", "$14", "$15", "$16", "$17", "$18", "$19",
		"$20", "$21", "$22","$23", "$24", "$25", "$26", "$27", "$28", "$29", "$30", "$31",

	};
	//vector string of RsSsL registers
	std::vector <std::string> RsSsLlist = {
		"beq", "bne", "blt", "ble", "bgt", "bge",
	};
	//vector string of RsM registers 
	std::vector <std::string> RsMlist = {
		"lw", "lh", "lb", "la", "sw", "sh", "sb",
	};
	size_t lastAddressIndex = 0x00000000;

	bool checkTextLabel(std::list<Token> List);


	//store constant into constant map
	bool storeConstant(std::list<Token> List);
	//store data label into label map
	bool storeDataLabel(std::list<Token> List);
	//store layout in the data section
	bool storeLayout(std::list<Token> List);
	//store .word layout
	bool storeWord(std::list<Token> List);
	//store .half layout
	bool storeHalf(std::list<Token> List);
	//store .byte layout
	bool storeByte(std::list<Token> List);
	//store .space layout
	bool storeSpace(std::list<Token> List);
	//store ascii layout
	bool storeAscii(std::list<Token> List);
	//store asciiz layout
	bool storeAsciiz(std::list<Token> List);

	//allocate space for .word layout in the memory map
	void wordAllocation(size_t start, std::string inputString);
	//allocate space for .half layout in the memory map
	void halfAllocation(size_t start, std::string inputString);
	//allocate space for .byte layout in the memory map
	void byteAllocation(size_t start, std::string inputString);
	//allocate space for .space layout in the memory map
	void spaceAllocation(std::string inputString);
	//allocate space for .ascii or asciiz layout in the memory map
	void asciiAllocation(std::string inputString);

	//store text label into label map
	bool storeTextLabel(std::list<Token> List);
	//store <isntruction> <register> SEP <register> SEP <source> instruction
	bool storeRsRsSInstruction(std::list<Token> List);
	//store <isntruction> <register> SEP <source> SEP <label> instruction
	bool storeRsSsLInstruction(std::list<Token> List);
	//store <isntruction> <register> SEP <register>
	bool storeRsRInstruction(std::list<Token> List);
	//store <isntruction> <register> SEP <source> instruction
	bool storeRsSInstruction(std::list<Token> List);
	//store <instruction> <register> SEP <immediate> instruction
	bool storeRsIInstruction(std::list<Token> List);
	//store <instruction> <register> instruction
	bool storeRInstruction(std::list<Token> List);
	//store <instruction> <memref> instruction
	bool storeRsMInstruction(std::list<Token> List);
	//store <instruction> <label> instruction
	bool storeJumpInstruction(std::list<Token> List);

	//check <isntruction> <register> SEP <source> SEP <label> instruction
	bool checkRsSsLInstruction(std::list<Token> List);
	//check <instruction> <memref> instruction
	bool checkRsMInstructiton(std::list<Token> List);
	//check <instruction> <label> instruction
	bool checkJumpInstruction(std::list<Token> List);

	//find constant in constant map
	bool findConstant(std::string input);
	//find text label in label map
	bool findTextLabel(std::string input);
	//check the hex value of the inputted integer
	std::string checkHexVal(size_t integer);
	//check if the inputted string is a immediate type argument
	std::string checkImmediate(std::string inputString);
	//check if the inputted string is a source type argument
	std::string checkSource(std::string inputString);
	//get list element 
	Token getListElement(std::list<Token> List, int position);
	//check if the inputted string is an integer for immediate type
	bool checkIntegerImmediate(std::string inputString);
	//check the bits of the input string and layout type
	bool checkBits(std::string layoutType, std::string inputInteger);
	//converts register to one variable ($t0 -> 
	std::string convertRegister(std::string inputString);

public:
	std::string errorMessage;

	//overall parse instruction to parse tokens
	bool parse(std::istream& input);
	//used for testing parse data grammar
	bool parseDataTest(std::istream& input);
	//used for testing parse text grammar
	bool parseTextTest(std::istream& input);
	//parse data section
	bool parseData(std::list<Token> tokenList);
	//parse text section
	bool parseText(std::list<Token> tokenList);
	//prints constants map, label map, list of instructions
	void printParseDetails(void);
	std::unordered_map<std::string, labelType> labelsMap;;
	std::unordered_map<std::string, std::string> constantsMap;
	std::vector<std::string> memoryLayout;
	std::vector<instruction> instructionList;
};




#endif
