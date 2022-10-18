#include "lexer.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>

/*
NAME: Jeffrey Kedda
PROJECT: Milestone 2
DESCRIPTION: Lexing component with MIPS input
*/

// implement the tokenize function here
// currently it just always returns an empty TokenList
TokenList tokenize(std::istream& ins) {
	TokenList tokens;
	char c;
	std::string temp;
	std::size_t lineNumber = 1;
	std::size_t parenLineNumber = 1;
	std::size_t openParanMatch = 0;

	//finding ending dilmitter (", ), })
	bool inParan = false;   // toggled when encountering the ( character
	bool instring = false;  // toggled when encountering the " character
	bool isError = false;
	bool skipFirstLine = false;  //Case: when first char is '\n'

	//Lexing Loop
	while (ins.get(c)) {
		//COMMENT  
		if (c == '#' && !instring) {
			if (!temp.empty()) {
				tokens.emplace_back(STRING, lineNumber, temp);
				temp.clear();
			}
			do {
				temp.push_back(c);
				ins.get(c);

			} while ((c != '\n'));
			tokens.emplace_back(COMMENT, lineNumber, temp);
			temp.clear();
			tokens.emplace_back(EOL, lineNumber);
		}
		//SEP
		if (c == ',' && !instring) {
			skipFirstLine = true;
			if (!temp.empty()) {
				tokens.emplace_back(STRING, lineNumber, temp);
				temp.clear();
			}
			tokens.emplace_back(SEP, lineNumber);
		}
		//EQUAL
		else if ((c == '=') && !instring) {
			skipFirstLine = true;
			if (!temp.empty()) {
				tokens.emplace_back(STRING, lineNumber, temp);
				temp.clear();
			}
			tokens.emplace_back(EQUAL, lineNumber);
		}
		//OPEN
		else if ((c == '(') && !instring) {
			skipFirstLine = true;
			if (!temp.empty()) {
				tokens.emplace_back(STRING, lineNumber, temp);
				temp.clear();
			}
			inParan = true;
			parenLineNumber = lineNumber;
			tokens.emplace_back(OPEN_PAREN, lineNumber);
			openParanMatch++;

		}
		//CLOSED
		else if ((c == ')') && !instring) {
			skipFirstLine = true;
			if (!temp.empty()) {
				tokens.emplace_back(STRING, lineNumber, temp);
				temp.clear();
			}
			tokens.emplace_back(CLOSE_PAREN, lineNumber);
			openParanMatch--;
			if (openParanMatch == 0) {
				inParan = false;
			}
		}
		//First Quote
		else if (c == '"' && !instring) {
			skipFirstLine = true;
			instring = true;
			tokens.emplace_back(STRING_DELIM, lineNumber);
		}
		//Second Quote
		else if (c == '"' && instring) {
			skipFirstLine = true;
			instring = false;
			//if (!temp.empty()) {
			tokens.emplace_back(STRING, lineNumber, temp);
			temp.clear();
			//}
			tokens.emplace_back(STRING_DELIM, lineNumber);
		}
		//EOL
		else if (c == '\n' && skipFirstLine) {
			skipFirstLine = true;
			if (!temp.empty()) {
				tokens.emplace_back(STRING, lineNumber, temp);
				temp.clear();
			}
			//Quote Case
			if (instring) {
				std::string error = "Error: unmatched quote on line " + std::to_string(lineNumber);
				tokens.emplace_back(ERROR, lineNumber, error);
				isError = true;
				break;
			}

			// Paranthese Case
			if (inParan || openParanMatch != 0) {
				std::string error = "Error: unmatched paranthese on line " + std::to_string(parenLineNumber);
				tokens.emplace_back(ERROR, lineNumber, error);
				isError = true;
				break;

			}
			tokens.emplace_back(EOL, lineNumber);
			lineNumber++;

		}
		//if first char is \n, skip first line
		else if (c == '\n' && skipFirstLine == false) {
			lineNumber++;
		}
		//SPACE
		else if (std::isspace(c) && !instring) {
			skipFirstLine = true;
			if (!temp.empty()) {
				tokens.emplace_back(STRING, lineNumber, temp);
				temp.clear();
			}

		}
		//Append to String
		else {
			temp.push_back(c);
			skipFirstLine = true;
		}
	}

	//End string case
	if (!temp.empty() && isError == false) {
		tokens.emplace_back(STRING, lineNumber, temp);
		tokens.emplace_back(EOL, lineNumber);
		temp.clear();
	}

	//Print statements
	//std::cout << std::endl;
	//std::cout << "size: " << tokens.size() << std::endl;
	//for (auto const& i : tokens) {
	//	std::cout << i << std::endl;
	//}
	return tokens;


}
