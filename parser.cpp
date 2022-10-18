#include "parser.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include "dataGrammar.hpp"
#include "textGrammar.hpp"

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <iterator> 
#include <bitset>
#include <limits>

bool Parser::parse(std::istream& input) {
	TokenList tokens = tokenize(input);
	std::list<std::list<Token>>  token2dList = create2dDataArray(tokens);
	//print2dArray(token2dList);
	bool isDataSection = false;
	bool isTextSection = false;
	for (auto i1 = token2dList.begin(); i1 != token2dList.end(); i1++) {
		std::list<Token>& tokenLineList = *i1;
		//check .data/.text
		if (tokenLineList.front().type() != COMMENT) {
			if (tokenLineList.size() == 2 && getListElement(tokenLineList, 0).type() == STRING && getListElement(tokenLineList, 0).value() == ".data" && tokenLineList.back().type() == EOL) {
				isDataSection = true;
				isTextSection = false;
			}
			else if (tokenLineList.size() == 2 && getListElement(tokenLineList, 0).type() == STRING && getListElement(tokenLineList, 0).value() == ".text" && tokenLineList.back().type() == EOL) {
				isDataSection = false;
				isTextSection = true;
			}
			else if (isDataSection == false && isTextSection == true && tokenLineList.size() != 1) {
				if (parseText(tokenLineList) == false) { return false; }
			}
			else if (isDataSection == true && isTextSection == false && tokenLineList.size() != 1) {

				if (parseData(tokenLineList) == false) { return false; }

			}
		}
	}
	return true;
}
bool Parser::parseData(std::list<Token> tokenList) {
	if (tokenList.size() > 1) {
		if (checkConstant(tokenList)) {
			//Store the Constant
			if (storeConstant(tokenList) == false) { return false; }
		}
		else if (checkLabel(tokenList)) {
			//Store the Label
			if (storeDataLabel(tokenList) == false) { return false; }
		}
		else if (checkGeneralLayout(tokenList)) {
			//Store Layout
			if (storeLayout(tokenList) == false) { return false; }
		}
		else {
			std::cerr << "Error:" << tokenList.front().line() << ": line could not be parsed into Label, Const, Layout" << std::endl;
			errorMessage = "Error:" + std::to_string(tokenList.front().line()) + ": line could not be parsed into Label, Const, Layout";
			return false;
		}
	}
	return true;
}
bool Parser::parseText(std::list<Token> tokenList) {
	if (tokenList.size() > 1) {
		if (tokenList.front().value() == "nop") {
			instruction instruct;
			instruct.type = nop;
			Token instructionName = getListElement(tokenList, 0);
			instruct.lineNumber = instructionName.line();
			instruct.name = instructionName.value();
			instructionList.push_back(instruct);
		}
		else if (checkRsRsSInstruction(tokenList)) {
			if (storeRsRsSInstruction(tokenList) == false) { return false; }
		}
		else if (checkRsSsLInstruction(tokenList)) {
			if (storeRsSsLInstruction(tokenList) == false) { return false; }
			//beq $t1, source, label
		}
		else if (checkRsRInstruction(tokenList)) {
			// mult 	$t2, $t0
			if (storeRsRInstruction(tokenList) == false) { return false; }
		}
		else if (checkRsSInstruction(tokenList)) {
			// not $t2, source
			if (storeRsSInstruction(tokenList) == false) { return false; }
		}
		else if (checkRsMInstructiton(tokenList)) {
			// lw $t1, memref
			if (storeRsMInstruction(tokenList) == false) { return false; }
		}
		else if (checkRsIInstruction(tokenList)) {
			// li $t1, immediate
			if (storeRsIInstruction(tokenList) == false) { return false; }
		}
		else if (checkRInstruction(tokenList)) {
			// mfhi $t1
			if (storeRInstruction(tokenList) == false) { return false; }
		}
		else if (checkJumpInstruction(tokenList)) {
			if (storeJumpInstruction(tokenList) == false) { return false; }
		}
		else if (checkTextLabel(tokenList)) {
			if (storeTextLabel(tokenList) == false) { return false; }
		}
		else {
			std::cerr << "Error:" << tokenList.front().line() << ": line could not be parsed into an instruction" << std::endl;
			errorMessage = "Error:" + std::to_string(tokenList.front().line()) + ": line could not be parsed into an instruction";
			return false;
		}
	}
	return true;
}

bool Parser::checkTextLabel(std::list<Token> List)
{
	//check size
	std::string errorMessage;
	if (List.size() == 2) {
		if (checkLabelName(List.front()) && getListElement(List, 1).type() == EOL) {
			return true;
		}
		else {
			return false;
		}
	}
	// comment condition
	else if (List.size() == 3) {
		if (checkLabelName(List.front()) && getListElement(List, 1).type() == COMMENT && getListElement(List, 2).type() == EOL) {
			return true;
		}
		if (checkLabelName(List.front()) && getListElement(List, 1).value() == "nop" && getListElement(List, 2).type() == EOL) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (List.size() > 3) {
		if (checkLabelName(List.front())) {
			std::list<Token> subList;
			for (int i = 1; i < List.size(); i++) {
				subList.push_back(getListElement(List, i));
			}
			if (parseText(subList)) {
				return true;
			}
		}
		else {
			return false;
		}

	}


}


bool Parser::parseDataTest(std::istream& input) {
	TokenList tokens = tokenize(input);
	std::list<std::list<Token>>  token2dList = create2dDataArray(tokens);
	//DATA
	for (auto i1 = token2dList.begin(); i1 != token2dList.end(); i1++) {
		std::list<Token>& tokenLineList = *i1;
		if (tokenLineList.size() > 1) {
			if (checkConstant(tokenLineList)) {
				//Store the Constant
				if (storeConstant(tokenLineList) == false) { return false; }
			}
			else if (checkLabel(tokenLineList)) {
				//Store the Label
				if (storeDataLabel(tokenLineList) == false) { return false; }
			}
			else if (checkGeneralLayout(tokenLineList)) {
				//Store Layout
				if (storeLayout(tokenLineList) == false) { return false; }
			}
			else {
				std::cerr << "Error:" << tokenLineList.front().line() << ": line could not be parsed into Label, Const, Layout" << std::endl;
				return false;
			}
		}
	}
	return true;

};
bool Parser::parseTextTest(std::istream& input) {
	TokenList tokens = tokenize(input);
	std::list<std::list<Token>>  token2dList = create2dDataArray(tokens);
	for (auto i1 = token2dList.begin(); i1 != token2dList.end(); i1++) {
		std::list<Token>& tokenLineList = *i1;
		if (tokenLineList.size() > 1) {
			if (checkTextLabel(tokenLineList)) {
				if (storeTextLabel(tokenLineList) == false) { return false; }
			}
			else if (checkRsRsSInstruction(tokenLineList)) {
				if (storeRsRsSInstruction(tokenLineList) == false) { return false; }
			}
			else if (checkRsSsLInstruction(tokenLineList)) {
				if (storeRsSsLInstruction(tokenLineList) == false) { return false; }
			}
			else if (checkRsRInstruction(tokenLineList)) {
				if (storeRsRInstruction(tokenLineList) == false) { return false; }
			}
			else if (checkRsSInstruction(tokenLineList)) {
				if (storeRsSInstruction(tokenLineList) == false) { return false; }
			}
			else if (checkRsMInstructiton(tokenLineList)) {
				if (storeRsMInstruction(tokenLineList) == false) { return false; }
			}
			else if (checkRsIInstruction(tokenLineList)) {
				if (storeRsIInstruction(tokenLineList) == false) { return false; }
			}
			else if (checkRInstruction(tokenLineList)) {
				if (storeRInstruction(tokenLineList) == false) { return false; }
			}
			else if (checkJumpInstruction(tokenLineList)) {
				if (storeJumpInstruction(tokenLineList) == false) { return false; }
			}
			else {
				std::cerr << "Error:" << tokenLineList.front().line() << ": line could not be parsed into an instruction" << std::endl;
				return false;
			}
		}
	}
	//print2dArray(token2dList);
	return true;

};

bool Parser::storeLayout(std::list<Token> List) {
	std::string layoutType = getListElement(List, 1).value();
	if (layoutType == ".word") {
		if (storeWord(List)) { return true; }
	}
	else if (layoutType == ".half") {
		if (storeHalf(List)) { return true; }
	}
	else if (layoutType == ".byte") {
		if (storeByte(List)) { return true; }
	}
	else if (layoutType == ".space") {
		if (storeSpace(List)) { return true; }
	}
	//special case (vm/test01.asm)
	//---------------------------------------------------
	else if (getListElement(List, 0).value() == ".space") {
		if (storeSpace(List)) { return true; }
	}
	//---------------------------------------------------
	else if (layoutType == ".ascii") {
		if (storeAscii(List)) { return true; }
	}
	else if (layoutType == ".asciiz") {
		if (storeAsciiz(List)) { return true; }
	}
	else {
		std::cerr << "Error:" << List.front().line() << ": line could not be parsed into .word, .half, .space, .ascii, .asciiz" << std::endl;
		errorMessage = "Error:" + std::to_string(List.front().line()) + ": line could not be parsed into .word, .half, .space, .ascii, .asciiz";
		return false;
	}
	return false;
}
bool Parser::storeWord(std::list<Token> List) { //ERROR MESSAGE
	if (storeDataLabel(List) == false) {
		return false;
	}
	for (auto const& token : List) {
		if (token.type() == STRING && checkInteger(token)) {
			if (checkBits(".word", token.value())) {
				wordAllocation(0, token.value());
				wordAllocation(8, token.value());
				wordAllocation(16, token.value());
				wordAllocation(24, token.value());
				//return true;
			}
			else {
				std::cerr << "Error:" << token.line() << ": token does not follow bit conditions for .word" << std::endl;
				errorMessage = "Error:" + std::to_string(List.front().line()) + ": token does not follow bit conditions for .word";
				return false;
			}
		}
		else if (token.type() == STRING && findConstant(token.value()) && checkIntegerString(constantsMap.find(token.value())->second)) {
			if (checkBits(".word", constantsMap.find(token.value())->second)) {
				wordAllocation(0, constantsMap.find(token.value())->second);
				wordAllocation(8, constantsMap.find(token.value())->second);
				wordAllocation(16, constantsMap.find(token.value())->second);
				wordAllocation(24, constantsMap.find(token.value())->second);
				//return true;
			}
			else {
				std::cerr << "Error:" << token.line() << ": token does not follow bit conditions for .word" << std::endl;
				errorMessage = "Error:" + std::to_string(List.front().line()) + ": token does not follow bit conditions for .word";
				return false;
			}
		}
	}
	return true;
}
void Parser::wordAllocation(size_t start, std::string inputString) {
	std::bitset<32> bits((int32_t)stol(inputString));
	size_t leftHexidecimal = 0, rightHexidecimal = 0;
	if (bits[start])
		rightHexidecimal += 1;
	if (bits[start + 1])
		rightHexidecimal += 2;
	if (bits[start + 2])
		rightHexidecimal += 4;
	if (bits[start + 3])
		rightHexidecimal += 8;
	if (bits[start + 4])
		leftHexidecimal += 1;
	if (bits[start + 5])
		leftHexidecimal += 2;
	if (bits[start + 6])
		leftHexidecimal += 4;
	if (bits[start + 7])
		leftHexidecimal += 8;
	std::string hexidecimal = checkHexVal(leftHexidecimal).append(checkHexVal(rightHexidecimal));
	memoryLayout.push_back(hexidecimal);
	lastAddressIndex++;
}
bool Parser::storeHalf(std::list<Token> List) { //ERROR MESSAGE
	if (storeDataLabel(List) == false) {
		return false;
	}
	for (auto const& token : List) {
		if (token.type() == STRING && checkInteger(token)) {
			if (checkBits(".half", token.value())) {
				halfAllocation(0, token.value());
				halfAllocation(8, token.value());
				//return true;
			}
			else {
				std::cerr << "Error:" << token.line() << ": token does not follow bit conditions for .half" << std::endl;
				errorMessage = "Error:" + std::to_string(List.front().line()) + ": token does not follow bit conditions for .half";
				return false;
			}
		}
		else if (token.type() == STRING && findConstant(token.value()) && checkIntegerString(constantsMap.find(token.value())->second)) {
			if (checkBits(".half", constantsMap.find(token.value())->second)) {
				wordAllocation(0, constantsMap.find(token.value())->second);
				wordAllocation(8, constantsMap.find(token.value())->second);
				//return true;
			}
			else {
				std::cerr << "Error:" << token.line() << ": token does not follow bit conditions for .half" << std::endl;
				errorMessage = "Error:" + std::to_string(List.front().line()) + ": token does not follow bit conditions for .half";
				return false;
			}
		}
	}
	return true;
}
void Parser::halfAllocation(size_t start, std::string inputString) {
	std::bitset<16> bits((int16_t)stol(inputString));
	size_t leftHexidecimal = 0, rightHexidecimal = 0;
	if (bits[start])
		rightHexidecimal += 1;
	if (bits[start + 1])
		rightHexidecimal += 2;
	if (bits[start + 2])
		rightHexidecimal += 4;
	if (bits[start + 3])
		rightHexidecimal += 8;
	if (bits[start + 4])
		leftHexidecimal += 1;
	if (bits[start + 5])
		leftHexidecimal += 2;
	if (bits[start + 6])
		leftHexidecimal += 4;
	if (bits[start + 7])
		leftHexidecimal += 8;
	std::string hexidecimal = checkHexVal(leftHexidecimal).append(checkHexVal(rightHexidecimal));
	memoryLayout.push_back(hexidecimal);
	lastAddressIndex++;
}
bool Parser::storeByte(std::list<Token> List) { //ERROR MESSAGE
	if (storeDataLabel(List) == false) {
		return false;
	}
	for (auto const& token : List) {
		if (token.type() == STRING && checkInteger(token)) {
			if (checkBits(".byte", token.value())) {
				byteAllocation(0, token.value());
				//return true;
			}
			else {
				std::cerr << "Error:" << token.line() << ": token does not follow bit conditions for .byte" << std::endl;
				errorMessage = "Error:" + std::to_string(List.front().line()) + ": token does not follow bit conditions for .byte";
				return false;
			}
		}
		else if (token.type() == STRING && findConstant(token.value()) && checkIntegerString(constantsMap.find(token.value())->second)) {
			if (checkBits(".byte", constantsMap.find(token.value())->second)) {
				wordAllocation(0, constantsMap.find(token.value())->second);
				//return true;
			}
			else {
				std::cerr << "Error:" << token.line() << ": token does not follow bit conditions for .byte" << std::endl;
				errorMessage = "Error:" + std::to_string(List.front().line()) + ": token does not follow bit conditions for .byte";
				return false;
			}
		}
	}
	return true;
}
void Parser::byteAllocation(size_t start, std::string inputString) {
	std::bitset<8> bits((int8_t)stol(inputString));
	size_t leftHexidecimal = 0, rightHexidecimal = 0;
	if (bits[start])
		rightHexidecimal += 1;
	if (bits[start + 1])
		rightHexidecimal += 2;
	if (bits[start + 2])
		rightHexidecimal += 4;
	if (bits[start + 3])
		rightHexidecimal += 8;
	if (bits[start + 4])
		leftHexidecimal += 1;
	if (bits[start + 5])
		leftHexidecimal += 2;
	if (bits[start + 6])
		leftHexidecimal += 4;
	if (bits[start + 7])
		leftHexidecimal += 8;
	std::string hexidecimal = checkHexVal(leftHexidecimal).append(checkHexVal(rightHexidecimal));
	memoryLayout.push_back(hexidecimal);
	lastAddressIndex++;
}
bool Parser::storeSpace(std::list<Token> List) { 
	//special case (vm/test01.asm)
	//---------------------------------------------------
	if (List.size() == 3) {
		Token element = getListElement(List, 1);
		if (element.type() == STRING) {
			//check for consant
			if (findConstant(element.value())) {
				std::string constantValue = constantsMap.find(element.value())->second;
				if (checkBits(".space", constantValue)) {
					spaceAllocation(constantValue);
					return true;
				}
				else {
					std::cerr << "Error:" << element.line() << ": token does not follow bit conditions for .space" << std::endl;
					errorMessage = "Error:" + std::to_string(List.front().line()) + ": token does not follow bit conditions for .space";
					return false;
				}
			}
			else if (checkInteger(element)) {
				if (checkBits(".space", element.value())) {
					spaceAllocation(element.value());
					return true;
				}
				else {
					std::cerr << "Error:" << element.line() << ": token does not follow bit conditions for .space" << std::endl;
					errorMessage = "Error:" + std::to_string(List.front().line()) + ": token does not follow bit conditions for .space";
					return false;
				}
			}
		}
		else {
			std::cerr << "Error:" << element.line() << ": token does not follow bit conditions for .space" << std::endl;
			errorMessage = "Error:" + std::to_string(List.front().line()) + ": token does not follow bit conditions for .space";
			return false;

		}
	}
	//--------------------------------------------------------------------------------------------------
	else {
		if (storeDataLabel(List) == false) {
			return false;
		}
		Token element = getListElement(List, 2);
		if (element.type() == STRING) {
			//check for consant
			if (findConstant(element.value())) {
				std::string constantValue = constantsMap.find(element.value())->second;
				if (checkBits(".space", constantValue)) {
					spaceAllocation(constantValue);
					return true;
				}
				else {
					std::cerr << "Error:" << element.line() << ": token does not follow bit conditions for .space" << std::endl;
					errorMessage = "Error:" + std::to_string(List.front().line()) + ": token does not follow bit conditions for .space";
					return false;
				}
			}
			else if (checkInteger(element)) {
				if (checkBits(".space", element.value())) {
					spaceAllocation(element.value());
					return true;
				}
				else {
					std::cerr << "Error:" << element.line() << ": token does not follow bit conditions for .space" << std::endl;
					errorMessage = "Error:" + std::to_string(List.front().line()) + ": token does not follow bit conditions for .space";
					return false;
				}
			}
		}
		else {
			std::cerr << "Error:" << element.line() << ": token does not follow bit conditions for .space" << std::endl;
			errorMessage = "Error:" + std::to_string(List.front().line()) + ": token does not follow bit conditions for .space";
			return false;

		}
	}
	return false;
}
void Parser::spaceAllocation(std::string inputString) {
	int32_t allocationSize = std::stol(inputString);
	for (int32_t i = 0; i < allocationSize; i++) {
		memoryLayout.push_back("00");
		lastAddressIndex++;
	}
}
bool Parser::storeAscii(std::list<Token> List) {
	if (storeDataLabel(List) == false) {
		return false;
	}
	std::string inputString = getListElement(List, 3).value();
	asciiAllocation(inputString);
	return true;
}
void Parser::asciiAllocation(std::string inputString) {

	for (size_t i = 0; i < inputString.size(); i++) {
		std::bitset<8> bits((uint8_t)(inputString[i]));
		size_t leftHexidecimal = 0, rightHexidecimal = 0;
		if (bits[0])
			rightHexidecimal += 1;
		if (bits[1])
			rightHexidecimal += 2;
		if (bits[2])
			rightHexidecimal += 4;
		if (bits[3])
			rightHexidecimal += 8;
		if (bits[4])
			leftHexidecimal += 1;
		if (bits[5])
			leftHexidecimal += 2;
		if (bits[6])
			leftHexidecimal += 4;
		if (bits[7])
			leftHexidecimal += 8;
		std::string hexidecimal = checkHexVal(leftHexidecimal).append(checkHexVal(rightHexidecimal));
		memoryLayout.push_back(hexidecimal);
		lastAddressIndex++;
	}

}
bool Parser::storeAsciiz(std::list<Token> List) {
	if (storeDataLabel(List) == false) {
		return false;
	}
	std::string inputString = getListElement(List, 3).value();
	asciiAllocation(inputString);
	memoryLayout.push_back("00");
	lastAddressIndex++;
	return true;
}

std::string Parser::checkHexVal(size_t integer)
{
	if (integer == 0)
		return "0";
	else if (integer == 1)
		return "1";
	else if (integer == 2)
		return "2";
	else if (integer == 3)
		return "3";
	else if (integer == 4)
		return "4";
	else if (integer == 5)
		return "5";
	else if (integer == 6)
		return "6";
	else if (integer == 7)
		return "7";
	else if (integer == 8)
		return "8";
	else if (integer == 9)
		return "9";
	else if (integer == 10)
		return "a";
	else if (integer == 11)
		return "b";
	else if (integer == 12)
		return "c";
	else if (integer == 13)
		return "d";
	else if (integer == 14)
		return "e";
	else if (integer == 15)
		return "f";
	else
		std::cerr << "Error: integer could not be converted into hex" << std::endl;
	exit(EXIT_FAILURE);
}
bool Parser::checkBits(std::string layoutType, std::string inputInteger)
{
	char firstChar = inputInteger.front();
	int64_t convertedInput = std::stoll(inputInteger);

	if (layoutType == ".word" || layoutType == ".space" ) {
		if (firstChar == '+' || firstChar == '-') { 
			int32_t i32min = std::numeric_limits<int32_t>::min(); 

			if ((convertedInput >= i32min) && (convertedInput <= 2147483647))
				return true;
		}
		else { 
			if (convertedInput <= 4294967295)
				return true;
		}
	}
	else if (layoutType == ".half") {
		if (firstChar == '+' || firstChar == '-') { 
			if ((convertedInput >= -32768) && (convertedInput <= 32767))
				return true;
		}
		else { 
			if (convertedInput <= 665535)
				return true;
		}
	}
	else if (layoutType == ".byte") {
		if (firstChar == '+' || firstChar == '-') { 
			if ((convertedInput >= -128) && (convertedInput <= 127))
				return true;
		}
		else {
			if (convertedInput <= 255)
				return true;
		}
	}

	return false; 
}
bool Parser::findConstant(std::string input) {
	auto findConstant = constantsMap.find(input);
	if (findConstant != constantsMap.end()) {
		return true;
	}
	else {
		return false;
	}
}
bool Parser::storeConstant(std::list<Token> List) {
	std::string constantName = List.front().value();
	std::string integer = getListElement(List, 2).value();
	auto findConstant = constantsMap.find(constantName);
	if (findConstant != constantsMap.end()) {
		findConstant->second = integer;
	}
	else {
		constantsMap.emplace(constantName, integer);
	}
	return true;
}
bool Parser::storeDataLabel(std::list<Token> List) {
	std::string labelName = List.front().value().substr(0, List.front().value().size() - 1);
	auto findLabel = labelsMap.find(labelName);
	if (findLabel != labelsMap.end()) {
		std::cerr << "Error:" << List.front().line() << ": Label is already defined" << std::endl;
		errorMessage = "Error:" + std::to_string(List.front().line()) + ": Label is already defined";
		return false;
	}
	else {
		labelType labelObject;
		labelObject.isTextLabel = false;
		labelObject.instructionIndex = lastAddressIndex;
		labelsMap.emplace(labelName, labelObject);
	}
	return true;
}

std::string Parser::checkImmediate(std::string inputString) {

	if (checkIntegerImmediate(inputString)) {
		return "integerImmediate";
	}
	else if (findConstant(inputString)) {
		return "constant";
	}
	return "error";
}
bool Parser::checkIntegerImmediate(std::string inputString) {
	std::string errorMessage;
	char firstChar = inputString.front();
	if ((inputString.length() == 1) && !isdigit(firstChar)) {
		return false;
	}
	else {
		size_t checkCounter = 0;
		if ((firstChar == '-') || (firstChar == '+'))
			checkCounter = 1;

		while (checkCounter < inputString.length()) {
			if (!isdigit(inputString[checkCounter])) {
				return false;
			}
			checkCounter++;
		}

	}
	return true;
}
std::string Parser::checkSource(std::string inputString) {
	if (searchInputList(registerList, inputString)) {
		return "register";
	}
	else if (checkIntegerImmediate(inputString)) {
		return "integerImmediate";
	}
	else if (findConstant(inputString)) {
		return "constant";
	}
	else {
		return "error";
	}
}

bool Parser::storeTextLabel(std::list<Token> List) {
	std::string labelName = List.front().value().substr(0, List.front().value().size() - 1);
	auto findLabel = labelsMap.find(labelName);
	if (findLabel != labelsMap.end()) {
		std::cerr << "Error:" << List.front().line() << ": Label is already defined" << std::endl;
		errorMessage = "Error:" + std::to_string(List.front().line()) + ": Label is already defined";
		return false;
	}
	else {
		labelType labelObject;
		labelObject.isTextLabel = true;
		labelObject.instructionIndex = instructionList.size();
		labelObject.lineNumber = List.front().line();
		/*
		if (List.size() == 4 || List.size() == 5) {
			if (getListElement(List, 1).value() == "j") {
				labelObject.lineNumber = List.front().line() - 1;
			}
		}
		*/
		labelsMap.emplace(labelName, labelObject);
	}
	return true;
}
bool Parser::storeRsRsSInstruction(std::list<Token> List) {
    //<instruction> <register> SEP <register> SEP <source>
	instruction instruct;
	instruct.type = RsRsS;
	Token instructionName = getListElement(List, 0);
	instruct.lineNumber = instructionName.line();
	instruct.name = instructionName.value();
	std::vector<argument> arguments;

	Token registerOne = getListElement(List, 1);
	arguments.push_back(argument(convertRegister(registerOne.value()), Register));
	Token registerTwo = getListElement(List, 3);
	arguments.push_back(argument(convertRegister(registerTwo.value()), Register));
	Token source = getListElement(List, 5);

	if (checkSource(source.value()) == "integerImmediate") {
		arguments.push_back(argument(source.value(), integerImmediate));
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
	}
	else if (checkSource(source.value()) == "constant") {
		arguments.push_back(argument(source.value(), Constant));
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
	}
	else if (checkSource(source.value()) == "register"){
		arguments.push_back(argument(convertRegister(source.value()), Register));
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
	}
	else {
		std::cerr << "Error:" << List.front().line() << ": Instruction could not be stored " << std::endl;
		errorMessage = "Error:" + std::to_string(List.front().line()) + ": Instruction could not be stored";
		return false;
	}
	return true;
}
bool Parser::storeRsSsLInstruction(std::list<Token> List) {
	//<instruction> <register> SEP <register> SEP <source>
	instruction instruct;
	instruct.type = RsSsL;
	Token instructionName = getListElement(List, 0);
	instruct.lineNumber = instructionName.line();
	instruct.name = instructionName.value();
	std::vector<argument> arguments;
	Token registerOne = getListElement(List, 1);
	arguments.push_back(argument(convertRegister(registerOne.value()), Register));
	Token label = getListElement(List, 5);

	Token source = getListElement(List, 3);
	if (checkSource(source.value()) == "integerImmediate" && checkLabelStringName(label)) {
		
		arguments.push_back(argument(source.value(), integerImmediate));

		arguments.push_back(argument(label.value(), Label));
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
	}
	else if (checkSource(source.value()) == "constant" && checkLabelStringName(label)) {
		arguments.push_back(argument(source.value(), Constant));
		arguments.push_back(argument(label.value(), Label));
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
	}
	else if (checkSource(source.value()) == "register" && checkLabelStringName(label)) {
		arguments.push_back(argument(convertRegister(source.value()), Register));
		arguments.push_back(argument(label.value(), Label));
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
	}
	else {
		std::cerr << "Error:" << List.front().line() << ": Instruction could not be stored " << std::endl;
		errorMessage = "Error:" + std::to_string(List.front().line()) + ": Instruction could not be stored";
		return false;
	}
	return true;
}
bool Parser::storeRsRInstruction(std::list<Token> List) {
	//<instruction> <register> SEP <register>
	instruction instruct;
	instruct.type = RsR;
	Token instructionName = getListElement(List, 0);
	instruct.lineNumber = instructionName.line();
	instruct.name = instructionName.value();
	std::vector<argument> arguments;
	Token registerOne = getListElement(List, 1);
	arguments.push_back(argument(convertRegister(registerOne.value()), Register));
	Token registerTwo = getListElement(List, 3);
	arguments.push_back(argument(convertRegister(registerTwo.value()), Register));
	instruct.instructionArguments = arguments;
	instructionList.push_back(instruct);
	return true;
}
bool Parser::storeRsSInstruction(std::list<Token> List) {
	//<instruction> <register> SEP <source>
	instruction instruct;
	instruct.type = RsS;
	Token instructionName = getListElement(List, 0);
	instruct.lineNumber = instructionName.line();
	instruct.name = instructionName.value();
	std::vector<argument> arguments;
	Token registerOne = getListElement(List, 1);
	arguments.push_back(argument(convertRegister(registerOne.value()), Register));
	Token source = getListElement(List, 3);
	if (checkSource(source.value()) == "integerImmediate") {
		arguments.push_back(argument(source.value(), integerImmediate));
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
	}
	else if (checkSource(source.value()) == "constant") {
		arguments.push_back(argument(source.value(), Constant));
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
	}
	else if (checkSource(source.value()) == "register") {
		arguments.push_back(argument(convertRegister(source.value()), Register));
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
	}
	else {
		std::cerr << "Error:" << List.front().line() << ": Instruction could not be stored " << std::endl;
		errorMessage = "Error:" + std::to_string(List.front().line()) + ": Instruction could not be stored";
		return false;
	}
	return true;

}
bool Parser::storeRsIInstruction(std::list<Token> List) {
	// li $t1, immediate
	//<instruction> <register> SEP <immediate>
	instruction instruct;
	instruct.type = RsI;
	Token instructionName = getListElement(List, 0);
	instruct.lineNumber = instructionName.line();
	instruct.name = instructionName.value();
	std::vector<argument> arguments;
	Token registerOne = getListElement(List, 1);
	arguments.push_back(argument(convertRegister(registerOne.value()), Register));
	Token immediate = getListElement(List, 3);
	if (checkImmediate(immediate.value()) == "integerImmediate") {
		arguments.push_back(argument(immediate.value(), integerImmediate));
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
	}
	else if (checkImmediate(immediate.value()) == "constant") {
		arguments.push_back(argument(immediate.value(), Constant));
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
	}
	else {
		std::cerr << "Error:" << List.front().line() << ": Instruction could not be stored " << std::endl;
		errorMessage = "Error:" + std::to_string(List.front().line()) + ": Instruction could not be stored";
		return false;
	}
	return true;

}
bool Parser::storeRInstruction(std::list<Token> List) {
	// mfhi $t1
	instruction instruct;
	instruct.type = R;
	Token instructionName = getListElement(List, 0);
	instruct.lineNumber = instructionName.line();
	instruct.name = instructionName.value();
	std::vector<argument> arguments;
	Token registerOne = getListElement(List, 1);
	arguments.push_back(argument(convertRegister(registerOne.value()), Register));
	instruct.instructionArguments = arguments;
	instructionList.push_back(instruct);
	return true;
}
bool Parser::storeRsMInstruction(std::list<Token> List) {
	//'lw' <register> SEP <memref>
	instruction instruct;
	instruct.type = RsM;
	Token instructionName = getListElement(List, 0);
	instruct.lineNumber = instructionName.line();
	instruct.name = instructionName.value();
	std::vector<argument> arguments;
	Token registerOne = getListElement(List, 1);
	arguments.push_back(argument(convertRegister(registerOne.value()), Register));
	//----------------------------------------------------------------------------------------
	int offsetIndex = 0;//offset index
	int withinIndex = 0;//within index

	// <instruction> <register> SEP '(' <label> ')' \n
	if ((List.size() == 7 || List.size() == 8) && getListElement(List, 3).type() == OPEN_PAREN && getListElement(List, 4).type() == STRING && getListElement(List, 5).type() == CLOSE_PAREN) {
		offsetIndex = 0;// no off set
		withinIndex = 4; 
	}
	// <instruction> <register> SEP [offset] '(' <label> ')'  \n
	if ((List.size() == 8 || List.size() == 9) && getListElement(List, 3).type() == STRING && getListElement(List, 4).type() == OPEN_PAREN && getListElement(List, 5).type() == STRING && getListElement(List, 6).type() == CLOSE_PAREN) {
		offsetIndex = 3;// there is an off set
		withinIndex = 5;
	}
	//<instruction> <register> SEP <label>
	if ((List.size() == 5 || List.size() == 6) && getListElement(List, 3).type() == STRING) {
		offsetIndex = 0;
		withinIndex = 3;
	}
	Token offset = getListElement(List, offsetIndex);
	bool offsetBool = false;
	if (offsetIndex != 0) {
		if (checkInteger(offset)) {
			//arguments.push_back(argument(offset.value(), Offset));
			offsetBool = true;
		}
		else {
			std::cerr << "Error:" << List.front().line() << ": Instruction could not be stored " << std::endl;
			errorMessage = "Error:" + std::to_string(List.front().line()) + ": Instruction could not be stored";
			return false;
		}
	}
	Token memref = getListElement(List, withinIndex);
	//check register
	if (searchInputList(registerList, memref.value())) {
		arguments.push_back(argument(convertRegister(memref.value()), Register));
		if(offsetBool == true){ arguments.push_back(argument(offset.value(), Offset)); }
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
		return true;
	}
	//check immediate
	if (checkImmediate(memref.value()) == "integerImmediate") {
		arguments.push_back(argument(memref.value(), integerImmediate));
		if (offsetBool == true) { arguments.push_back(argument(offset.value(), Offset)); }
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
		return true;
	}
	//check constant
	if (checkImmediate(memref.value()) == "constant") {
		arguments.push_back(argument(memref.value(), Constant));
		if (offsetBool == true) { arguments.push_back(argument(offset.value(), Offset)); }
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
		return true;
	}
	//check label
	if (checkLabelStringName(memref)) {
		arguments.push_back(argument(memref.value(), Label));
		if (offsetBool == true) { arguments.push_back(argument(offset.value(), Offset)); }
		instruct.instructionArguments = arguments;
		instructionList.push_back(instruct);
		return true;
	}
	std::cerr << "Error:" << List.front().line() << ": Instruction could not be stored " << std::endl;
	errorMessage = "Error:" + std::to_string(List.front().line()) + ": Instruction could not be stored";
	return false;
}
bool Parser::storeJumpInstruction(std::list<Token> List) {
	instruction instruct;
	instruct.type = Jump;
	Token instructionName = getListElement(List, 0);
	instruct.lineNumber = instructionName.line();
	instruct.name = instructionName.value();
	std::vector<argument> arguments;
	Token label = getListElement(List, 1);
	arguments.push_back(argument(label.value(), Label));
	instruct.instructionArguments = arguments;
	instructionList.push_back(instruct);
	return true;
}

bool Parser::checkRsSsLInstruction(std::list<Token> List) {
	//<register> SEP <source> SEP <label>
	if (List.size() == 7) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token source = getListElement(List, 3);
		Token sepTwo = getListElement(List, 4);
		Token label = getListElement(List, 5);
		//EOL
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && source.type() == STRING && sepTwo.type() == SEP && label.type() == STRING && getListElement(List, 6).type() == EOL) {
			if (searchInputList(RsSsLlist, instruction.value()) && searchInputList(registerList, registerOne.value())) {
				//&& findTextLabel(label.value())
				return true;
			}
			return false;
		}
		return false;

	}
	//check for comment
	else if (List.size() == 8) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token source = getListElement(List, 3);
		Token sepTwo = getListElement(List, 4);
		Token label = getListElement(List, 5);
		//EOL
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && source.type() == STRING && sepTwo.type() == SEP && label.type() == STRING && getListElement(List, 6).type() == COMMENT && getListElement(List, 7).type() == EOL) {
			if (searchInputList(RsSsLlist, instruction.value()) && searchInputList(registerList, registerOne.value())) {
			//&& findTextLabel(label.value()
				return true;
			}
			return false;
		}
		return false;
	}

	return false;
}
bool Parser::checkRsMInstructiton(std::list<Token> List) {
	//<register> SEP <memref>
	//<memref> :: = <label> | <immediate> | <register> 
	if (List.size() == 5) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token check = getListElement(List, 3);
		Token eol = List.back();
		//<instruction> <register> SEP <string>
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && check.type() == STRING && eol.type() == EOL) {
			if (searchInputList(RsMlist, instruction.value()) && searchInputList(registerList, registerOne.value())) {
				return true;
			}
			return false;
		}
		return false;
	}
	//check comment
	if (List.size() == 6) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token check = getListElement(List, 3);
		Token comment = getListElement(List, 4);
		Token eol = List.back();
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && check.type() == STRING && comment.type() == COMMENT && eol.type() == EOL) {
			if (searchInputList(RsMlist, instruction.value()) && searchInputList(registerList, registerOne.value())) {
				return true;
			}
			return false;
		}
		return false;

	}
	//[offset] '(' <label> ')' | [offset] '(' <immediate> ')' | [offset] '(' <register> ')'
	// no offset
	if (List.size() == 7) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token openParen = getListElement(List, 3);
		Token registerTwo = getListElement(List, 4);
		Token closeParen = getListElement(List, 5);
		Token eol = List.back();
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && openParen.type() == OPEN_PAREN && registerTwo.type() == STRING && closeParen.type() == CLOSE_PAREN && eol.type() == EOL) {
			if (searchInputList(RsMlist, instruction.value()) && searchInputList(registerList, registerOne.value())) {
				return true;
			}
			return false;
		}
		return false;
	}
	// no offset with comment 
	if (List.size() == 8) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token openParen = getListElement(List, 3);
		Token registerTwo = getListElement(List, 4);
		Token closeParen = getListElement(List, 5);
		Token comment = getListElement(List, 6);
		Token eol = List.back();
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && openParen.type() == OPEN_PAREN && registerTwo.type() == STRING && closeParen.type() == CLOSE_PAREN && comment.type() == COMMENT && eol.type() == EOL) {
			if (searchInputList(RsMlist, instruction.value()) && searchInputList(registerList, registerOne.value())) {
				return true;
			}
			return false;
		}
		//offset case
		Token offset = getListElement(List, 3);
		openParen = getListElement(List, 4);
		registerTwo = getListElement(List, 5);
		closeParen = getListElement(List, 6);
		eol = List.back();
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && offset.type() == STRING && openParen.type() == OPEN_PAREN && registerTwo.type() == STRING && closeParen.type() == CLOSE_PAREN && eol.type() == EOL) {
			if (searchInputList(RsMlist, instruction.value()) && searchInputList(registerList, registerOne.value())) {
				return true;
			}
			return false;
		}
		return false;
	}
	//offset case with comment
	if (List.size() == 9) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token offset = getListElement(List, 3);
		Token openParen = getListElement(List, 4);
		Token registerTwo = getListElement(List, 5);
		Token closeParen = getListElement(List, 6);
		Token comment = getListElement(List, 7);
		Token eol = List.back();
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && offset.type() == STRING && openParen.type() == OPEN_PAREN && registerTwo.type() == STRING && closeParen.type() == CLOSE_PAREN && comment.type() == COMMENT && eol.type() == EOL) {
			if (searchInputList(RsMlist, instruction.value()) && searchInputList(registerList, registerOne.value())) {
				return true;
			}
			return false;
		}
		return false;
	}
	return false;
}
bool Parser::checkJumpInstruction(std::list<Token> List) {
	//<isntruction> <register>
	if (List.size() == 3) {
		Token instruction = getListElement(List, 0);
		Token label = getListElement(List, 1);

		//EOL
		if (instruction.type() == STRING && label.type() == STRING && getListElement(List, 2).type() == EOL) {
			if (instruction.value() == "j" && checkLabelStringName(label)) {
				return true;
			}
			return false;
		}
		return false;

	}
	//check for comment
	else if (List.size() == 4) {
		Token instruction = getListElement(List, 0);
		Token label = getListElement(List, 1);
		//EOL
		if (instruction.type() == STRING && label.type() == STRING && getListElement(List, 2).type() == COMMENT && getListElement(List, 3).type() == EOL) {
			if (instruction.value() == "j" && checkLabelStringName(label)) {
				return true;
			}
			return false;
		}
		return false;
	}

	return false;
}
bool Parser::findTextLabel(std::string input) {
	auto findLabel = labelsMap.find(input);
	if (findLabel != labelsMap.end()) {
		return true;
	}
	else {
		return false;
	}
}
Token Parser::getListElement(std::list<Token> List, int position) {
	std::list<Token>::iterator it = List.begin();
	for (int i = 0; i < position; i++) {
		++it;
	}
	return *it;
}
void Parser::printParseDetails(void) {

	//print instruction list
	//std::vector<instruction> instructionList;
	std::cout << "List of Instructions:" << std::endl;
	for (instruction instructionElement : instructionList) {
		// and(RsRsS) Line(3) : and(instruction) $t1(Register) $t1(Register)
		std::cout << instructionElement.name << " (" << instructionElement.type << ") Line(" << instructionElement.lineNumber << ") : ";
		std::vector<argument> arguments = instructionElement.instructionArguments;
		for (argument argumentElement : arguments) {
			std::cout << argumentElement.getValue() << "(" << argumentElement.getType() << ") ";
		}
		std::cout << std::endl;
	}

	std::cout << "List of Labels:" << std::endl;
	for (auto pair : labelsMap) {
		if (pair.second.isTextLabel) {
			std::cout << "{ " << pair.first << ": Type(TextLabel) index(" << pair.second.instructionIndex << ") }\n";
		}
		else {
			std::cout << "{ " << pair.first << ": Type(DataLabel)  index(" << pair.second.instructionIndex << ") }\n";
		}
		
	}

	//std::unordered_map<std::string, std::string> constantsMap;
	std::cout << "List of Constants:" << std::endl;
	for (auto pair : constantsMap) {
		std::cout << "{ " << pair.first << ": " << pair.second << " }\n";
	}

	std::cout << "Memory Layout:" << std::endl;
	for (std::string memorySlot : memoryLayout) {
		std::cout << memorySlot << std::endl;
	}




}

std::string Parser::convertRegister(std::string inputString)
{
	if (inputString == "$0" || inputString == "$zero")
		return "$0";
	else if (inputString == "$1" || inputString == "$at")
		return "$0";
	else if (inputString == "$2" || inputString == "$v0")
		return "$2";
	else if (inputString == "$3" || inputString == "$v1")
		return "$3";
	else if (inputString == "$4" || inputString == "$a0")
		return "$4";
	else if (inputString == "$5" || inputString == "$a1")
		return "$5";
	else if (inputString == "$6" || inputString == "$a2")
		return "$6";
	else if (inputString == "$7" || inputString == "$a3")
		return "$7";
	else if (inputString == "$8" || inputString == "$t0")
		return "$8";
	else if (inputString == "$9" || inputString == "$t1")
		return "$9";
	else if (inputString == "$10" || inputString == "$t2")
		return "$10";
	else if (inputString == "$11" || inputString == "$t3")
		return "$11";
	else if (inputString == "$12" || inputString == "$t4")
		return "$12";
	else if (inputString == "$13" || inputString == "$t5")
		return "$13";
	else if (inputString == "$14" || inputString == "$t6")
		return "$14";
	else if (inputString == "$15" || inputString == "$t7")
		return "$15";
	else if (inputString == "$16" || inputString == "$s0")
		return "$16";
	else if (inputString == "$17" || inputString == "$s1")
		return "$17";
	else if (inputString == "$18" || inputString == "$s2")
		return "$18";
	else if (inputString == "$19" || inputString == "$s3")
		return "$19";
	else if (inputString == "$20" || inputString == "$s4")
		return "$20";
	else if (inputString == "$21" || inputString == "$s5")
		return "$21";
	else if (inputString == "$22" || inputString == "$s6")
		return "$22";
	else if (inputString == "$23" || inputString == "$s7")
		return "$23";
	else if (inputString == "$24" || inputString == "$t8")
		return "$24";
	else if (inputString == "$25" || inputString == "$t9")
		return "$25";
	else if (inputString == "$26" || inputString == "$k0")
		return "$26";
	else if (inputString == "$27" || inputString == "$k1")
		return "$27";
	else if (inputString == "$28" || inputString == "$gp")
		return "$28";
	else if (inputString == "$29" || inputString == "$sp")
		return "$29";
	else if (inputString == "$30" || inputString == "$fp")
		return "$30";
	else if (inputString == "$31" || inputString == "$ra")
		return "$31";
	else if (inputString == "$pc")
		return "$pc";
	else if (inputString == "$hi")
		return "$hi";
	else if (inputString == "$lo")
		return "$lo";
	else
		return "error";
}
