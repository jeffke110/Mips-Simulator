#include "textGrammar.hpp"
#include "dataGrammar.hpp"
#include "lexer.hpp"
#include "token.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>


//<register> SEP <register> SEP <source>
std::vector <std::string> RsRsSlist = {
		"add","addu",
		"sub","subu",
		"mul", "mulo","mulou",
		"rem", "remu",
		"and", "nor", "or", "xor", "div", "divu",
};
//<register> SEP <register>
std::vector <std::string> RsRlist = {
		"mult", "multu",
		"div", "divu",
		"abs", "neg", "negu", "move",
};
//<register> SEP <source>
std::vector <std::string> RsSlist = {
		"not",
};
//<register>
std::vector <std::string> RList = {
		"mfhi", "mflo", "mthi", "mtlo",
};
//<register> SEP <immediate>
std::vector <std::string> RsIlist = {
		"li"
};
//Register Map
std::vector <std::string> registerList = {
		"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2","$a3",
		"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
		"$s0","$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
		"$t8", "$t9", "$k0","$k1", "$gp", "$sp", "$fp", "$ra",
		"$0", "$1", "$2","$3", "$4", "$5", "$6", "$7", "$8", "$9",
		"$10", "$11", "$12","$13", "$14", "$15", "$16", "$17", "$18", "$19",
		"$20", "$21", "$22","$23", "$24", "$25", "$26", "$27", "$28", "$29", "$30", "$31",
};


bool searchInputList(std::vector <std::string> list, std::string input) {
	for (unsigned int i = 0; i < list.size(); i++) {
		if (input == list[i]) {
			return true;
		}
	}
	return false;
}
bool checkRsRsSInstruction(std::list<Token> List) {
	//<isntruction> <register> SEP <register> SEP <source>
	if (List.size() == 7) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token registerTwo = getListElement(List, 3);
		Token sepTwo = getListElement(List, 4);
		Token source = getListElement(List, 5);
		//EOL
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && registerTwo.type() == STRING && sepTwo.type() == SEP && source.type() == STRING && getListElement(List, 6).type() == EOL) {
			if (searchInputList(RsRsSlist, instruction.value()) && searchInputList(registerList, registerOne.value()) && searchInputList(registerList, registerTwo.value())) {
				return true;
			}
			return false;
		}
		return false;
	//check for comment
	}else if (List.size() == 8) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token registerTwo = getListElement(List, 3);
		Token sepTwo = getListElement(List, 4);
		Token source = getListElement(List, 5);
		//EOL
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && registerTwo.type() == STRING && sepTwo.type() == SEP && source.type() == STRING && getListElement(List, 6).type() == COMMENT && getListElement(List, 7).type() == EOL) {
			if (searchInputList(RsRsSlist, instruction.value()) && searchInputList(registerList, registerOne.value()) && searchInputList(registerList, registerTwo.value())) {
			return true;
			}
			return false;
		}
		return false;
	}

	return false;
}
bool checkRsRInstruction(std::list<Token> List) {
	//<isntruction> <register> SEP <register>
	if (List.size() == 5) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token registerTwo = getListElement(List, 3);
		//EOL
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && registerTwo.type() == STRING && getListElement(List, 4).type() == EOL) {
			if (searchInputList(RsRlist, instruction.value()) && searchInputList(registerList, registerOne.value()) && searchInputList(registerList, registerTwo.value())) {
				return true;
			}
			return false;
		}
		return false;

	}
	//check for comment
	else if (List.size() == 6) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token registerTwo = getListElement(List, 3);

		//EOL
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && registerTwo.type() == STRING && getListElement(List, 4).type() == COMMENT && getListElement(List, 5).type() == EOL) {
			if (searchInputList(RsRlist, instruction.value()) && searchInputList(registerList, registerOne.value()) && searchInputList(registerList, registerTwo.value())) {
				return true;
			}
			return false;
		}
		return false;
	}

	return false;




}
bool checkRsSInstruction(std::list<Token> List) {
	//<register> SEP <source>
	if (List.size() == 5) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token source = getListElement(List, 3);
		//EOL
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && source.type() == STRING && getListElement(List, 4).type() == EOL) {
			if (searchInputList(RsSlist, instruction.value()) && searchInputList(registerList, registerOne.value())) {
				return true;
			}
			return false;
		}
		return false;

	}
	//check for comment
	else if (List.size() == 6) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token source = getListElement(List, 3);

		//EOL
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && source.type() == STRING && getListElement(List, 4).type() == COMMENT && getListElement(List, 5).type() == EOL) {
			if (searchInputList(RsSlist, instruction.value()) && searchInputList(registerList, registerOne.value())) {
				return true;
			}
			return false;
		}
		return false;
	}

	return false;

}
bool checkRsIInstruction(std::list<Token> List) {
	//<register> SEP <immediate>
	if (List.size() == 5) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token immediate = getListElement(List, 3);
		//EOL
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && immediate.type() == STRING && getListElement(List, 4).type() == EOL) {
			if (searchInputList(RsIlist, instruction.value()) && searchInputList(registerList, registerOne.value())) {
				return true;
			}
			return false;
		}
		return false;

	}
	//check for comment
	else if (List.size() == 6) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		Token sepOne = getListElement(List, 2);
		Token immediate = getListElement(List, 3);

		//EOL
		if (instruction.type() == STRING && registerOne.type() == STRING && sepOne.type() == SEP && immediate.type() == STRING && getListElement(List, 4).type() == COMMENT && getListElement(List, 5).type() == EOL) {
			if (searchInputList(RsIlist, instruction.value()) && searchInputList(registerList, registerOne.value())) {
				return true;
			}
			return false;
		}
		return false;
	}

	return false;


}
bool checkRInstruction(std::list<Token> List) {
	//<isntruction> <register>
	if (List.size() == 3) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);

		//EOL
		if (instruction.type() == STRING && registerOne.type() == STRING && getListElement(List, 2).type() == EOL) {
			if (searchInputList(RList, instruction.value()) && searchInputList(registerList, registerOne.value())) {
				return true;
			}
			return false;
		}
		return false;

	}
	//check for comment
	else if (List.size() == 4) {
		Token instruction = getListElement(List, 0);
		Token registerOne = getListElement(List, 1);
		//EOL
		if (instruction.type() == STRING && registerOne.type() == STRING && getListElement(List, 2).type() == COMMENT && getListElement(List, 3).type() == EOL) {
			if (searchInputList(RList, instruction.value()) && searchInputList(registerList, registerOne.value())) {
				return true;
			}
			return false;
		}
		return false;
	}

	return false;
}



