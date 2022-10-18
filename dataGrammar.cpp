#include "dataGrammar.hpp"
#include "lexer.hpp"
#include "token.hpp"

#include <string>
#include <unordered_map>
#include <sstream>
#include <iterator>
#include <cctype>
#include <iomanip>


bool checkLabel(std::list<Token> List)
{
	
	//checks conditions for label
	if (List.size() == 2) {
		if (checkLabelName(List.front())  && getListElement(List, 1).type() == EOL) {
			return true;
		}
		else {
			return false;
		}
	}
	//comment condition for checking the label
	else if (List.size() == 3) {
		if (checkLabelName(List.front()) && getListElement(List, 1).type() == COMMENT && getListElement(List, 2).type() == EOL) {
			return true;
		}
		else {
			return false;
		}
	}

	return false;

}
bool checkConstant(std::list<Token> List)
{
	//checks conditions for a constant
	if (List.size() == 4) {
		if (checkVariableName(List.front()) && getListElement(List, 1).type() == EQUAL && checkInteger(getListElement(List, 2)) && getListElement(List, 3).type() == EOL) {
			return true;
		}
		else {
			return false;
		}
	}
	//comment condition for checking constant
	else if (List.size() == 5) {
		if (checkVariableName(List.front()) && getListElement(List, 1).type() == EQUAL && checkInteger(getListElement(List, 2)) && getListElement(List, 3).type() == COMMENT && getListElement(List, 4).type() == EOL) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
	
}
bool checkLabelName(Token input) {

	//check if token is string
	if (input.type() == STRING) {
		std::string inputString = input.value();
		char firstChar = inputString.front();

		//check first character
		if (!isalpha(firstChar)) {
			return false;
		}
		else {
			//check rest of the string
			if (inputString.length() > 1) {
				for (size_t i = 1; i < inputString.length()-1; i++) {
					if (!isdigit(inputString[i]) && !isalpha(inputString[i]) && !(inputString[i] == '_')) {
						return false;
					}
				}
			}
			if (inputString.back() != ':') {
				return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}
bool checkLabelStringName(Token input) {
	//check if token is string type
	if (input.type() == STRING) {
		std::string inputString = input.value();
		char firstChar = inputString.front();

		//check first character
		if (!isalpha(firstChar)) {
			return false;
		}
		else {
			//check rest of string
			if (inputString.length() > 1) {
				for (size_t i = 1; i < inputString.length() - 1; i++) {
					if (!isdigit(inputString[i]) && !isalpha(inputString[i]) && !(inputString[i] == '_')) {
						return false;
					}
				}
			}
		}
		return true;
	}
	else {
		return false;
	}

}
bool checkVariableName(Token input) {
	//check token type is string
	if (input.type() == STRING) {
		std::string inputString = input.value();
		char firstChar = inputString.front();


		//check first character
		if (!isalpha(firstChar)) {
			return false;
		}
		else {
		//check rest of string
			if (inputString.length() > 1) {
				for (size_t i = 1; i < inputString.length(); i++) {
					if (!isdigit(inputString[i]) && !isalpha(inputString[i]) && !(inputString[i] == '_')) {
						return false;
					}
				}
			}
		}
		return true;
	}
	else {
		return false;
	}
}
bool checkInteger(Token input)
{
	//check string type
	if (input.type() == STRING) {
		std::string inputString = input.value();
		char firstChar = inputString.front();
		if ((inputString.length() == 1) && !isdigit(firstChar)) {
			return false;
		}
		else {
			//check sign
			size_t checkCounter = 0;
			if ((firstChar == '-') || (firstChar == '+'))
				checkCounter = 1;
			//check rest of string
			while (checkCounter < inputString.length()) {
				if (!isdigit(inputString[checkCounter])) {
					return false;
				}
				checkCounter++;
			}

		}
		return true;
	}
	else {
		return false;
	}
}

bool checkIntegerString(std::string inputString)
{		
		//check first character
		char firstChar = inputString.front();
		if ((inputString.length() == 1) && !isdigit(firstChar)) {
			return false;
		}
		else {
			//check sign
			size_t checkCounter = 0;
			if ((firstChar == '-') || (firstChar == '+'))
				checkCounter = 1;
			//check rest string
			while (checkCounter < inputString.length()) {
				if (!isdigit(inputString[checkCounter])) {
					return false;
				}
				checkCounter++;
			}

		}
		return true;
}
bool checkGeneralLayout(std::list<Token> List) {
	
	if(List.size() >= 3){
		if(checkStringLayout(List)){
			return true;
		}
		if(checkIntLayout(List)){
			return true;
		}
	}
	return false;
	
}
bool checkStringLayout(std::list<Token> List) {
	if (List.size() == 6) {
		//check label
		if (checkLabelName(List.front())) {
			// check ".ascii" or ".asciiz"
			Token temp = getListElement(List, 1);
			if (temp.type() == STRING && (temp.value() == ".ascii" || temp.value() == ".asciiz")) {
				// check string delim, string, string delim, EOL
				if (getListElement(List, 2).type() == STRING_DELIM && getListElement(List, 3).type() == STRING && getListElement(List, 4).type() == STRING_DELIM && getListElement(List, 5).type() == EOL) {
					return true;
				}
			}
		}
		return false;
	}
	//check comment case
	else if (List.size() == 7) {
		//check label
		if (checkLabelName(List.front())) {
			// check ".ascii" or ".asciiz"
			Token temp = getListElement(List, 1);
			if (temp.type() == STRING && (temp.value() == ".ascii" || temp.value() == ".asciiz")) {
				// check string delim, string, string delim, EOL
				if (getListElement(List, 2).type() == STRING_DELIM && getListElement(List, 3).type() == STRING && getListElement(List, 4).type() == STRING_DELIM && getListElement(List, 5).type() == COMMENT && getListElement(List, 6).type() == EOL) {
					return true;
				}
			}
		}
		return false;
	}
	return false;
}


bool checkIntLayout(std::list<Token> List) {
	//special case (vm/test01.asm)
	//---------------------------------------------------
	if (List.size() == 3) {
		//check label
			Token temp = getListElement(List, 0);
			if (temp.type() == STRING && (temp.value() == ".word" || temp.value() == ".half" || temp.value() == ".byte" || temp.value() == ".space")) {
				// check String(integer), EOL
				if (temp.value() == ".space" && getListElement(List, 1).type() == STRING && getListElement(List, 2).type() == EOL) {
					return true;
				}
				else if (getListElement(List, 1).type() == STRING && getListElement(List, 2).type() == EOL) {
					//&& checkInteger(getListElement(List, 2))
					return true;
				}
			}
		return false;
	}
	//--------------------------------------------------
	//check one int element
	else if (List.size() == 4) {
		//check label
		if (checkLabelName(List.front())) {
			Token temp = getListElement(List, 1);
			if (temp.type() == STRING && (temp.value() == ".word" || temp.value() == ".half" || temp.value() == ".byte" || temp.value() == ".space")) {
				// check String(integer), EOL
				if (temp.value() == ".space" && getListElement(List, 2).type() == STRING && getListElement(List, 3).type() == EOL) {
					return true;
				}
				else if (getListElement(List, 2).type() == STRING  &&  getListElement(List, 3).type() == EOL) {
					//&& checkInteger(getListElement(List, 2))
					return true;
				}
			}
		}
		return false;
	}
	//check one int element and comment
	else if (List.size() == 5 && getListElement(List, List.size() - 2).type() == COMMENT) {
		//check label
		if (checkLabelName(List.front())) {
			Token temp = getListElement(List, 1);
			if (temp.type() == STRING && (temp.value() == ".word" || temp.value() == ".half" || temp.value() == ".byte" || temp.value() == ".space")) {
				// check String(integer), Comment, EOL
				if (temp.value() == ".space" && getListElement(List, 2).type() == STRING && getListElement(List, 3).type() == COMMENT && getListElement(List, 4).type() == EOL) {
					return true;
				}
				else if (getListElement(List, 2).type() == STRING  && getListElement(List, 3).type() == COMMENT && getListElement(List, 4).type() == EOL) {
					//&& checkInteger(getListElement(List, 2))
					return true;
				}
			}
		}
		return false;
	}
	//check multiple ints
	else if (List.size() > 4) {
		//check label
		if (checkLabelName(List.front())) {
			Token temp = getListElement(List, 1);
			if (temp.type() == STRING && (temp.value() == ".word" || temp.value() == ".half" || temp.value() == ".byte")) {
				if (checkListOfIntegers(List)) {
					return true;
				}
			}
		}
		return false;
	}
	return false;
}
bool checkListOfIntegers(std::list<Token> List) {
	int commentElement = 1;
	//no comment
	if (getListElement(List, List.size() - 2).type() == COMMENT) {
		commentElement = 2;
	}
	bool checkComma = false;
	for (unsigned int i = 2; i < List.size() - commentElement; i++) {
		Token element = getListElement(List, i);
		if (element.type() == SEP && i == List.size() - commentElement - 1) {
			return false;
		}
		if (i == List.size() - commentElement - 1 && element.type() == STRING) {
			Token integer = getListElement(List, List.size() - commentElement - 1);
			if ((integer.type() != STRING || !checkInteger(integer))) {
				return false;
			}
			getListElement(List, i).setType(INTEGER);
		}
		if (element.type() == STRING && checkInteger(element) && checkComma == false) {
			checkComma = true;
			getListElement(List, i).setType(INTEGER);
		}
		else if (element.type() == SEP && checkComma == true && i != List.size() - commentElement - 1) {
			checkComma = false;
		}
		else {
			return false;
		}
	}
	return true;
}



Token getListElement(std::list<Token> List, int position) {
	std::list<Token>::iterator it = List.begin();
	for (int i = 0; i < position; i++) {
		++it;
	}
	return *it;
}
std::list<std::list<Token>> create2dDataArray(TokenList tokens) {
	std::list<std::list<Token>> atom2dList;
	std::list<Token> atomList;
	for (auto const& token : tokens) {
		if (token.type() == EOL) {
			atomList.push_back(token);
			//Reset List
			atom2dList.push_back(atomList);
			atomList.clear();
		}
		else {
			atomList.push_back(token);
		}
	}
	return atom2dList;
};
