#include "parser.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include "dataGrammar.hpp"
#include "textGrammar.hpp"
#include "virtualMachine.hpp"


//init virtual machine methods
void virtualMachine::initializeRegisters(void)
{
	registersMap.emplace("$0", 0);
	registersMap.emplace("$1", 0);
	registersMap.emplace("$2", 0);
	registersMap.emplace("$3", 0);
	registersMap.emplace("$4", 0);
	registersMap.emplace("$5", 0);
	registersMap.emplace("$6", 0);
	registersMap.emplace("$7", 0);
	registersMap.emplace("$8", 0);
	registersMap.emplace("$9", 0);
	registersMap.emplace("$10", 0);
	registersMap.emplace("$11", 0);
	registersMap.emplace("$12", 0);
	registersMap.emplace("$13", 0);
	registersMap.emplace("$14", 0);
	registersMap.emplace("$15", 0);
	registersMap.emplace("$16", 0);
	registersMap.emplace("$17", 0);
	registersMap.emplace("$18", 0);
	registersMap.emplace("$19", 0);
	registersMap.emplace("$20", 0);
	registersMap.emplace("$21", 0);
	registersMap.emplace("$22", 0);
	registersMap.emplace("$23", 0);
	registersMap.emplace("$24", 0);
	registersMap.emplace("$25", 0);
	registersMap.emplace("$26", 0);
	registersMap.emplace("$27", 0);
	registersMap.emplace("$28", 0);
	registersMap.emplace("$29", 0);
	registersMap.emplace("$30", 0);
	registersMap.emplace("$31", 0);
	registersMap.emplace("$pc", 0);
	registersMap.emplace("$hi", 0);
	registersMap.emplace("$lo", 0);
}
void virtualMachine::setMaps(Parser mipsParser) {
	constantsMap = mipsParser.constantsMap;
	labelsMap = mipsParser.labelsMap;
	instructionList = mipsParser.instructionList;
	memoryLayout = mipsParser.memoryLayout;
}
void virtualMachine::getRegisterMapSize(void) {
	std::cout << "GET SIZE: " << registersMap.size() << std::endl;
}
std::string virtualMachine::convertRegister(std::string inputString)
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

//user thread methods
void virtualMachine::runThreadProcess(void) {
	// run through each stepp
	bool checkendoffile = true;
	while (threadRunning) {
		while (!messageQueue.empty()) {
			if (errorMessage.empty() && checkEndOfFile() && checkendoffile) {
				if ((pcRegister->second) == (int32_t)instructionList.size() - 1) {
					checkendoffile = false;
					executeInstruction(instructionList.at(pcRegister->second));
				}
				else {
					executeInstruction(instructionList.at(pcRegister->second));
				}	
			}
		}
		checkendoffile = true;
	}
}

//user input methods
void virtualMachine::checkJoinable(void) {
	if (errorMessage.empty() && checkEndOfFile()) {
		executeInstruction(instructionList.at(pcRegister->second));
	}
	else {
		throw std::invalid_argument(" thread lock error");
	}
}
bool virtualMachine::checkMainLabel(void) {
	std::unordered_map<std::string, labelType>::iterator findMainLabel = labelsMap.find("main");
	if (findMainLabel != labelsMap.end()) {
		return true;
	}
	else {
		std::cerr << "Error:" << 0 << ": No main label found" << std::endl;
		return false;
	}
}
bool virtualMachine::userInputFunction(std::string inputInterface) {
		//print $r
		if (inputInterface.substr(0, 7) == "print $") {
			if (messageQueue.empty()) {
				std::string registerInput = inputInterface.substr(6, inputInterface.size());
				//check register
				std::vector<std::string>::iterator findRegister = std::find(registerList.begin(), registerList.end(), registerInput);
				if (findRegister != registerList.end()) {
					registerInput = convertRegister(registerInput);
					std::unordered_map<std::string, int32_t>::iterator getRegisterValue = registersMap.find(registerInput);
					printf("0x%08x\n", getRegisterValue->second);
				}
				//invalid input error
				else {
					std::cerr << "Error: invalid register input" << std::endl;
				}
			}
			else {
				std::cerr << "Error: process is currently running" << std::endl;
			}
		}
		else if (inputInterface.substr(0, 7) == "print &") {
			if (messageQueue.empty()) {
				std::string indexInput = inputInterface.substr(7, inputInterface.size());
				size_t convertedIndex = stol(indexInput, nullptr, 16);
				//check size
				if (convertedIndex < memoryLayout.size()) {
					int32_t hexConverted = (int32_t)(std::stol(memoryLayout[convertedIndex], nullptr, 16));
					printf("0x%02x\n", hexConverted);
				}
				//invalid input error
				else {
					std::cerr << "Error: Memory out of bounds" << std::endl;
				}
			}
			else {
				std::cerr << "Error: process is currently running" << std::endl;
			}
		}
		else if (inputInterface == "run"){
			//run function
			if (messageQueue.empty() && errorMessage.empty() && checkEndOfFile()) {
				isGettingMessage = true;
				messageQueue.push("run");	
			}
			else {
				std::cerr << "Error: process is currently running or end of file" << std::endl;
			}
		}
		else if (inputInterface == "break"){
			//break function
			if(!messageQueue.empty()) {
				std::string temp = "";
				messageQueue.wait_and_pop(temp);
				isGettingMessage = false;
				printCounter();
			}
			else {
				std::cerr << "Error: no process is currently running" << std::endl;
			}
			
		}
		else if (inputInterface == "step") {
			if (messageQueue.empty()) {
				return false;
			}
			else {
				std::cerr << "Error: process is currently running" << std::endl;
			}
		}
		else if (inputInterface == "status") {
			if (!errorMessage.empty()) {
				std::cerr << errorMessage << std::endl;
			}
		}
		else if (inputInterface == "quit") {
			while(!messageQueue.empty()) {
				std::string temp = "";
				messageQueue.try_pop(temp);
			}
			threadRunning = false;
		}
		else {
			std::cerr << "Error: unknown command." << std::endl;
		}
	
	return true;
}
bool virtualMachine::executeInstruction(instruction inputInstruction) {
	if (inputInstruction.name == "nop") {
		incrementCounter();
	}
	else if (inputInstruction.name == "add") {
		if (add_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "addu") {
		if (addu_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "sub") {
		if (sub_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "subu") {
		if (subu_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "mult") {
		if (mult_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "multu") {
		if (multu_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "div") {
		if (div_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "divu") {
		if (divu_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "and") {
		if (and_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "nor") {
		if (nor_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "or") {
		if (or_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "xor") {
		if (xor_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "not") {
		if (not_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "beq") {
		if (beq_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "bne") {
		if (bne_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "blt") {
		if (blt_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "ble") {
		if (ble_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "bgt") {
		if (bgt_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "bge") {
		if (bge_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "j") {
		if (j_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "lw") {
		if (lw_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "la") {
		if (la_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "sw") {
		if (sw_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "li") {
		if (li_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "move") {
		if (move_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "mfhi") {
		if (mfhi_Instruction(inputInstruction) == false) { return false; }
	}
	else if (inputInstruction.name == "mflo") {
		if (mflo_Instruction(inputInstruction) == false) { return false; }
	}
	else {
		std::cerr << "Error:" << inputInstruction.lineNumber << ": execute instruction (cannot execute that instruction)" << std::endl;
		return false;
	}
	return true;
}
void virtualMachine::incrementCounter(void) {
	if (checkEndOfFile()) {
		int32_t addOne = pcRegister->second + 1;
		pcRegister->second = addOne;
	}
}
void virtualMachine::printCounter(void) {
	std::unordered_map<std::string, int32_t>::iterator gePCValue = registersMap.find("$pc");
	printf("0x%08x\n", gePCValue->second);
}
bool virtualMachine::checkEndOfFile(void) {
	if ((pcRegister->second) >= (int32_t)instructionList.size()) {
		return false;
	}
	else {
		return true;
	}
}

// instruction methods
bool virtualMachine::add_Instruction(instruction inputInstruction) {
	//add_s  =	'add'   <register> SEP <register> SEP <source> 
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument registerTwo = arguments.at(1);
	argument source = arguments.back();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(registerTwo.getValue());
	int32_t registerTwoValue = registerTwoContent->second;
	int32_t sourceValue;
	//source = Register
	if (source.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
		sourceValue = sourceContent->second;
	}
	//source = integer
	else if (source.getType() == integerImmediate) {
		sourceValue = (int32_t)stoll(source.getValue());
	}
	//source = constant
	else if (source.getType() == Constant) {
		sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
	}
	//check overflow
	if ((registerTwoValue + sourceValue < bit32Min) || (registerTwoValue + sourceValue > bit32Max)) {
		errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": (add) 2s complement overflow error";
		std::cerr << errorMessage << std::endl;
		return false;
	} else {
		registerOneContent->second = registerTwoValue + sourceValue;
		incrementCounter();
	}
	//printRegisterMap();
	return true;
}
bool virtualMachine::addu_Instruction(instruction inputInstruction) {
	//add_u  =	'addu'  <register> SEP <register> SEP <source>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument registerTwo = arguments.at(1);
	argument source = arguments.back();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(registerTwo.getValue());
	int32_t registerTwoValue = registerTwoContent->second;
	int32_t sourceValue;
	//source = Register
	if (source.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
		sourceValue = sourceContent->second;
	}
	//source = integer
	else if (source.getType() == integerImmediate) {
		sourceValue = (int32_t)stoll(source.getValue());
	}
	//source = constant
	else if (source.getType() == Constant) {
		sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
	}
	registerOneContent->second = (uint32_t)(registerTwoValue + sourceValue);
	incrementCounter();
	return true;
}
bool virtualMachine::sub_Instruction(instruction inputInstruction) {
	//sub_s  =	'sub'   <register> SEP <register> SEP <source>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument registerTwo = arguments.at(1);
	argument source = arguments.back();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(registerTwo.getValue());
	int32_t registerTwoValue = registerTwoContent->second;
	int32_t sourceValue;
	//source = Register
	if (source.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
		sourceValue = sourceContent->second;
	}
	//source = integer
	else if (source.getType() == integerImmediate) {
		sourceValue = (int32_t)stoll(source.getValue());
	}
	//source = constant
	else if (source.getType() == Constant) {
		sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
	}
	//check overflow
	if ( (registerTwoValue - sourceValue) < bit32Min || (registerTwoValue - sourceValue) > bit32Max ) {
		errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": (sub) 2s complement overflow error";
		std::cerr << errorMessage << std::endl;
		return false;
	}
	else {
		registerOneContent->second = (registerTwoValue - sourceValue);
		incrementCounter();
	}
	//printRegisterMap();
	return true;

}
bool virtualMachine::subu_Instruction(instruction inputInstruction) {
	//sub_u  =	'subu'  <register> SEP <register> SEP <source>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument registerTwo = arguments.at(1);
	argument source = arguments.back();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(registerTwo.getValue());
	int32_t registerTwoValue = registerTwoContent->second;
	int32_t sourceValue;
	//source = Register
	if (source.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
		sourceValue = sourceContent->second;
	}
	//source = integer
	else if (source.getType() == integerImmediate) {
		sourceValue = (int32_t)stoll(source.getValue());
	}
	//source = constant
	else if (source.getType() == Constant) {
		sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
	}
	registerOneContent->second = (uint32_t)(registerTwoValue - sourceValue);
	incrementCounter();
	return true;
}
bool virtualMachine::mult_Instruction(instruction inputInstruction) {
	//mult_s =	'mult'  <register> SEP <register>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument registerTwo = arguments.back();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(registerTwo.getValue());
	int32_t registerOneValue = registerOneContent->second;
	int32_t registerTwoValue = registerTwoContent->second;
	std::bitset<32> registerOnebits(registerOneValue);
	std::bitset<32> registerTwobits(registerTwoValue);
	uint32_t convertedRegisterOne;
	uint32_t convertedRegisterTwo;
	//2's complement
	if (registerOnebits[31] == 1) {
		convertedRegisterOne = (uint32_t)(~(registerOneValue)) + 1;
	} else {
		convertedRegisterOne = (uint32_t)(registerOneValue);
	}
	if (registerTwobits[31] == 1) {
		convertedRegisterTwo = (uint32_t)(~(registerTwoValue)) + 1;
	} else {
		convertedRegisterTwo = (uint32_t)(registerTwoValue);
	}
	//-------------------store in $lo, $hi-------------------------------
	std::unordered_map<std::string, int32_t>::iterator registerHi = registersMap.find("$hi");
	std::unordered_map<std::string, int32_t>::iterator registerLo = registersMap.find("$lo");
	uint64_t multipliedValue = (uint64_t)(convertedRegisterOne) * (uint64_t)(convertedRegisterTwo);
	uint32_t integerHi;
	uint32_t integerLo;
	if (registerOnebits[31] != registerTwobits[31]) { multipliedValue = (uint64_t)(~(multipliedValue)) + 1; }
	integerHi = (uint32_t)((multipliedValue & 0xffffffff00000000) >> 32);
	integerLo = (uint32_t)(multipliedValue & 0x00000000ffffffff);
	//--------------------------------------------------------------------
	registerHi->second = integerHi;
	registerLo->second = integerLo; 
	incrementCounter();
	return true;
}
bool virtualMachine::multu_Instruction(instruction inputInstruction) {
	//mult_u =	'multu' <register> SEP <register>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument registerTwo = arguments.back();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(registerTwo.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerHi = registersMap.find("$hi");
	std::unordered_map<std::string, int32_t>::iterator registerLo = registersMap.find("$lo");
	int32_t registerOneValue = registerOneContent->second;
	int32_t registerTwoValue = registerTwoContent->second;
	uint64_t multipliedValue = (uint64_t)(registerOneValue) * (uint64_t)(registerTwoValue);
	uint32_t integerHi = (uint32_t)((multipliedValue & 0xffffffff00000000) >> 32);
	uint32_t integerLo = (uint32_t)(multipliedValue & 0x00000000ffffffff);
	registerHi->second = integerHi; 
	registerLo->second = integerLo;
	incrementCounter();
	return true;
}
bool virtualMachine::div_Instruction(instruction inputInstruction) {
	//div2_s =	'div'   <register> SEP <register>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument registerTwo = arguments.back();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(registerTwo.getValue());
	int32_t registerOneValue = registerOneContent->second;
	int32_t registerTwoValue = registerTwoContent->second;
	std::bitset<32> registerOnebits(registerOneValue);
	std::bitset<32> registerTwobits(registerTwoValue);
	uint32_t convertedRegisterOne;
	uint32_t convertedRegisterTwo;
	//2's complement
	if (registerOnebits[31] == 1) {
		convertedRegisterOne = (uint32_t)(~(registerOneValue)) + 1;
	}
	else {
		convertedRegisterOne = (uint32_t)(registerOneValue);
	}
	if (registerTwobits[31] == 1) {
		convertedRegisterTwo = (uint32_t)(~(registerTwoValue)) + 1;
	}
	else {
		convertedRegisterTwo = (uint32_t)(registerTwoValue);
	}
	//-------------------store in $lo, $hi-------------------------------
	if (convertedRegisterTwo != 0) {
		std::unordered_map<std::string, int32_t>::iterator registerHi = registersMap.find("$hi");
		std::unordered_map<std::string, int32_t>::iterator registerLo = registersMap.find("$lo");
		uint32_t divideValue = (uint32_t)(convertedRegisterOne) / (uint32_t)(convertedRegisterTwo);
		if (registerOnebits[31] != registerTwobits[31]) { divideValue = (uint32_t)(~(divideValue)) + 1; }
		int32_t divisionRemainder = (registerOneValue) % (registerTwoValue);
		if (divisionRemainder < 0) { divisionRemainder *= -1; };
		registerHi->second = divisionRemainder;
		registerLo->second = divideValue;
		incrementCounter();
	}
	else {
		//errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": (div) cannot divide register by zero";
		incrementCounter();
		//std::cerr << errorMessage << std::endl;
		return false;
	}
	//--------------------------------------------------------------------
	return true;
}
bool virtualMachine::divu_Instruction(instruction inputInstruction) {
	//div2_u =	'divu'  <register> SEP <register>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument registerTwo = arguments.back();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(registerTwo.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerHi = registersMap.find("$hi");
	std::unordered_map<std::string, int32_t>::iterator registerLo = registersMap.find("$lo");
	int32_t registerOneValue = registerOneContent->second;
	int32_t registerTwoValue = registerTwoContent->second;
	if (registerTwoValue != 0) {
		uint32_t divideValue = (uint32_t)(registerOneValue) / (uint32_t)(registerTwoValue);
		uint32_t divisionRemainder = (uint32_t)(registerOneValue) % (uint32_t)(registerTwoValue);
		registerHi->second = divisionRemainder;
		registerLo->second = divideValue;
		incrementCounter();
		return true;
	}else {
		errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": (divu) cannot divide register by zero";
		incrementCounter();
		//std::cerr << errorMessage << std::endl;
		return false;
	}
	return true;

}

bool virtualMachine::and_Instruction(instruction inputInstruction) {
	//'and' <register> SEP <register> SEP <source>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument registerTwo = arguments.at(1);
	argument source = arguments.back();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(registerTwo.getValue());
	int32_t registerTwoValue = registerTwoContent->second;
	int32_t sourceValue;
	//source = Register
	if (source.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
		sourceValue = sourceContent->second;
	}
	//source = integer
	else if (source.getType() == integerImmediate) {
		sourceValue = (int32_t)stoll(source.getValue());
	}
	//source = constant
	else if (source.getType() == Constant) {
		sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
	}
	registerOneContent->second = (registerTwoValue & sourceValue);
	incrementCounter();
	return true;
}
bool virtualMachine::nor_Instruction(instruction inputInstruction) {
	//'nor' <register> SEP <register> SEP <source>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument registerTwo = arguments.at(1);
	argument source = arguments.back();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(registerTwo.getValue());
	int32_t registerTwoValue = registerTwoContent->second;
	int32_t sourceValue;
	//source = Register
	if (source.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
		sourceValue = sourceContent->second;
	}
	//source = integer
	else if (source.getType() == integerImmediate) {
		sourceValue = (int32_t)stoll(source.getValue());
	}
	//source = constant
	else if (source.getType() == Constant) {
		sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
	}
	registerOneContent->second = ~(registerTwoValue | sourceValue);
	incrementCounter();
	return true;
}
bool virtualMachine::or_Instruction(instruction inputInstruction) {
	//'or'  <register> SEP <register> SEP <source>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument registerTwo = arguments.at(1);
	argument source = arguments.back();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(registerTwo.getValue());
	int32_t registerTwoValue = registerTwoContent->second;
	int32_t sourceValue;
	//source = Register
	if (source.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
		sourceValue = sourceContent->second;
	}
	//source = integer
	else if (source.getType() == integerImmediate) {
		sourceValue = (int32_t)stoll(source.getValue());
	}
	//source = constant
	else if (source.getType() == Constant) {
		sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
	}
	registerOneContent->second = (registerTwoValue | sourceValue);
	incrementCounter();
	return true;
}
bool virtualMachine::xor_Instruction(instruction inputInstruction) {
	//'xor' <register> SEP <register> SEP <source>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument registerTwo = arguments.at(1);
	argument source = arguments.back();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(registerTwo.getValue());
	int32_t registerTwoValue = registerTwoContent->second;
	int32_t sourceValue;
	//source = Register
	if (source.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
		sourceValue = sourceContent->second;
	}
	//source = integer
	else if (source.getType() == integerImmediate) {
		sourceValue = (int32_t)stoll(source.getValue());
	}
	//source = constant
	else if (source.getType() == Constant) {
		sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
	}
	registerOneContent->second = ((registerTwoValue) ^ sourceValue);
	incrementCounter();
	return true;
}
bool virtualMachine::not_Instruction(instruction inputInstruction) {
	//'not' <register> SEP <source>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument source = arguments.back();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	int32_t sourceValue;
	//source = Register
	if (source.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
		sourceValue = sourceContent->second;
	}
	//source = integer
	else if (source.getType() == integerImmediate) {
		sourceValue = (int32_t)stoll(source.getValue());
	}
	//source = constant
	else if (source.getType() == Constant) {
		sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
	}
	registerOneContent->second = ~(sourceValue);
	incrementCounter();
	return true;
}

bool virtualMachine::beq_Instruction(instruction inputInstruction) {
	//'beq' < register > SEP <source> SEP <label>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument source = arguments.at(1);
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	int32_t registerOneValue = registerOneContent->second;
	int32_t sourceValue;

	//source = Register
	if (source.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
		sourceValue = sourceContent->second;
	}
	//source = integer
	else if (source.getType() == integerImmediate) {
		sourceValue = (int32_t)stoll(source.getValue());
	}
	//source = constant
	else if (source.getType() == Constant) {
		sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
	}
	argument labelArgument = arguments.back();
	std::unordered_map<std::string, labelType>::iterator label = labelsMap.find(labelArgument.getValue());
	if ((label != labelsMap.end())) {
		labelType labelDetails = label->second;
		if ((int32_t)(labelDetails.instructionIndex) < (int32_t)instructionList.size()) {
			if (registerOneValue == sourceValue) {
				pcRegister->second = labelDetails.instructionIndex;
				//printCounter();
			}
			else {
				incrementCounter();
			}
		}
		else {
			errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": beq (label index is more than the instruction size)";
			std::cerr << errorMessage << std::endl;
			return false;
		}
	} else {
		errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": beq (label not found)";
		std::cerr << errorMessage << std::endl;
		return false;
	}
	return true;

}
bool virtualMachine::bne_Instruction(instruction inputInstruction) {
	//'bne' < register > SEP <source> SEP <label>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument source = arguments.at(1);
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	int32_t registerOneValue = registerOneContent->second;
	int32_t sourceValue;

	//source = Register
	if (source.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
		sourceValue = sourceContent->second;
	}
	//source = integer
	else if (source.getType() == integerImmediate) {
		sourceValue = (int32_t)stoll(source.getValue());
	}
	//source = constant
	else if (source.getType() == Constant) {
		sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
	}
	argument labelArgument = arguments.back();
	std::unordered_map<std::string, labelType>::iterator label = labelsMap.find(labelArgument.getValue());
	if ((label != labelsMap.end())) {
		labelType labelDetails = label->second;
		if ((int32_t)(labelDetails.instructionIndex) < (int32_t)instructionList.size()) {
			if (registerOneValue != sourceValue) {
				pcRegister->second = labelDetails.instructionIndex;
				//printCounter();
			}
			else {
				incrementCounter();
			}
		}
		else {
			errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": bne (label index is more than the instruction size)";
			std::cerr << errorMessage << std::endl;
			return false;
		}
	}
	else {
		errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": bne (label not found)";
		std::cerr << errorMessage << std::endl;
		return false;
	}
	return true;

}
bool virtualMachine::blt_Instruction(instruction inputInstruction) {
	//'blt' < register > SEP <source> SEP <label>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument source = arguments.at(1);
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	int32_t registerOneValue = registerOneContent->second;
	int32_t sourceValue;

	//source = Register
	if (source.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
		sourceValue = sourceContent->second;
	}
	//source = integer
	else if (source.getType() == integerImmediate) {
		sourceValue = (int32_t)stoll(source.getValue());
	}
	//source = constant
	else if (source.getType() == Constant) {
		sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
	}
	argument labelArgument = arguments.back();
	std::unordered_map<std::string, labelType>::iterator label = labelsMap.find(labelArgument.getValue());
	if ((label != labelsMap.end())) {
		labelType labelDetails = label->second;
		if ((int32_t)(labelDetails.instructionIndex) < (int32_t)instructionList.size()) {
			if (registerOneValue < sourceValue) {
				pcRegister->second = labelDetails.instructionIndex;
				//printCounter();
			}
			else {
				incrementCounter();
			}
		}
		else {
			errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": blt (label index is more than the instruction size)";
			std::cerr << errorMessage << std::endl;
			return false;
		}
	}
	else {
		errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": blt (label not found)";
		std::cerr << errorMessage << std::endl;
		return false;
	}
	return true;

}
bool virtualMachine::ble_Instruction(instruction inputInstruction) {
	//'ble' < register > SEP <source> SEP <label>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument source = arguments.at(1);
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	int32_t registerOneValue = registerOneContent->second;
	int32_t sourceValue;

	//source = Register
	if (source.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
		sourceValue = sourceContent->second;
	}
	//source = integer
	else if (source.getType() == integerImmediate) {
		sourceValue = (int32_t)stoll(source.getValue());
	}
	//source = constant
	else if (source.getType() == Constant) {
		sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
	}
	argument labelArgument = arguments.back();
	std::unordered_map<std::string, labelType>::iterator label = labelsMap.find(labelArgument.getValue());
	if ((label != labelsMap.end())) {
		labelType labelDetails = label->second;
		if ((int32_t)(labelDetails.instructionIndex) < (int32_t)instructionList.size()) {
			if (registerOneValue <= sourceValue) {
				pcRegister->second = labelDetails.instructionIndex;
				//printCounter();
			}
			else {
				incrementCounter();
			}
		}
		else {
			errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": ble (label index is more than the instruction size)";
			std::cerr << errorMessage << std::endl;
			return false;
		}
	}
	else {
		errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": ble (label not found)";
		std::cerr << errorMessage << std::endl;
		return false;
	}
	return true;

}
bool virtualMachine::bgt_Instruction(instruction inputInstruction) {
	//'bgt' < register > SEP <source> SEP <label>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument source = arguments.at(1);
std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
int32_t registerOneValue = registerOneContent->second;
int32_t sourceValue;

//source = Register
if (source.getType() == Register) {
	std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
	sourceValue = sourceContent->second;
}
//source = integer
else if (source.getType() == integerImmediate) {
	sourceValue = (int32_t)stoll(source.getValue());
}
//source = constant
else if (source.getType() == Constant) {
	sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
}
argument labelArgument = arguments.back();
std::unordered_map<std::string, labelType>::iterator label = labelsMap.find(labelArgument.getValue());
if ((label != labelsMap.end())) {
	labelType labelDetails = label->second;
	if ((int32_t)(labelDetails.instructionIndex) < (int32_t)instructionList.size()) {
		if (registerOneValue > sourceValue) {
			pcRegister->second = labelDetails.instructionIndex;
			//printCounter();
		}
		else {
			incrementCounter();
		}
	}
	else {
		errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": bgt (label index is more than the instruction size)";
		std::cerr << errorMessage << std::endl;
		return false;
	}
}
else {
	errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": bgt (label not found)";
	std::cerr << errorMessage << std::endl;
	return false;
}
return true;

}
bool virtualMachine::bge_Instruction(instruction inputInstruction) {
	//'bge' < register > SEP <source> SEP <label>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument source = arguments.at(1);
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	int32_t registerOneValue = registerOneContent->second;
	int32_t sourceValue;

	//source = Register
	if (source.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator sourceContent = registersMap.find(source.getValue());
		sourceValue = sourceContent->second;
	}
	//source = integer
	else if (source.getType() == integerImmediate) {
		sourceValue = (int32_t)stoll(source.getValue());
	}
	//source = constant
	else if (source.getType() == Constant) {
		sourceValue = (int32_t)stoll(constantsMap.find(source.getValue())->second);
	}
	argument labelArgument = arguments.back();
	std::unordered_map<std::string, labelType>::iterator label = labelsMap.find(labelArgument.getValue());
	if ((label != labelsMap.end())) {
		labelType labelDetails = label->second;
		if ((int32_t)(labelDetails.instructionIndex) < (int32_t)instructionList.size()) {
			if (registerOneValue >= sourceValue) {
				pcRegister->second = labelDetails.instructionIndex;
				//printCounter();
			}
			else {
				incrementCounter();
			}
		}
		else {
			errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": bge (label index is more than the instruction size)";
			std::cerr << errorMessage << std::endl;
			return false;
		}
	}
	else {
		errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": bge (label not found)";
		std::cerr << errorMessage << std::endl;
		return false;
	}
	return true;

}
bool virtualMachine::j_Instruction(instruction inputInstruction) {
	//'j' <label>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument labelArgument = arguments.front();
	std::unordered_map<std::string, labelType>::iterator label = labelsMap.find(labelArgument.getValue());
	if ((label != labelsMap.end())) {
		labelType labelDetails = label->second;
		if ((int32_t)(labelDetails.instructionIndex) == 1){
			pcRegister->second = 0;
			//printCounter();
		}
		else if ((int32_t)(labelDetails.instructionIndex) <= (int32_t)instructionList.size()) {
			pcRegister->second = labelDetails.instructionIndex;
			//printCounter();
		}
		else {
			errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": jump (label index is more than the instruction size)";
			std::cerr << errorMessage << std::endl;
			return false;
		}
	}
	else {
		errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": jump (label not found)";
		std::cerr << errorMessage << std::endl;
		return false;
	}
	return true;
}

bool virtualMachine::lw_Instruction(instruction inputInstruction) {
	//'lw'   <register> SEP <memref> (offset)
	// <label> | <immediate> | <register>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument memref = arguments.at(1);
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	int32_t memrefValue;
	int32_t offsetValue;
	if (arguments.size() == 3) {
		offsetValue = (int32_t)stoll(arguments.back().getValue());
	}
	//memref = label
	if (memref.getType() == Label) {
		std::unordered_map<std::string, labelType>::iterator label = labelsMap.find(memref.getValue());
		//check and find label
		if ((label != labelsMap.end())) {
			labelType labelDetails = label->second;
			size_t index = labelDetails.instructionIndex;
			//no offset condition
			if (((int32_t)(labelDetails.instructionIndex + 3) < (int32_t)memoryLayout.size()) && arguments.size() == 2) {
				std::string data = memoryLayout[index + 3] + memoryLayout[index + 2] + memoryLayout[index + 1] + memoryLayout[index];
				memrefValue = (int32_t)stoll(data, nullptr, 16);
			}//offset condition
			else if (((int32_t)(labelDetails.instructionIndex + offsetValue + 3) < (int32_t)memoryLayout.size()) && arguments.size() == 3) {
				index = index + offsetValue;
				std::string data = memoryLayout[index + 3] + memoryLayout[index + 2] + memoryLayout[index + 1] + memoryLayout[index];
				memrefValue = (int32_t)stoll(data, nullptr, 16);
			}
			//index out of bounds
			else {
				errorMessage =  "Error:" + std::to_string(inputInstruction.lineNumber) + ": lw (index out of bounds)";
				std::cerr << errorMessage << std::endl;
				return false;
			}
		}
		//no label condition
		else {
			errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": lw (label not found)";
			std::cerr << errorMessage << std::endl;
			return false;
		}
	}
	//memref = Register
	else if (memref.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(memref.getValue());
		int32_t index = registerTwoContent->second;

		if (arguments.size() == 2) {
			//check out of bounds
			if (index + 3 < (int32_t)memoryLayout.size()) {
				std::string data = memoryLayout[index + 3] + memoryLayout[index + 2] + memoryLayout[index + 1] + memoryLayout[index];
				memrefValue = (int32_t)stoll(data, nullptr, 16);
			}
			else {
				errorMessage =  "Error:" + std::to_string(inputInstruction.lineNumber) + ": lw (index out of bounds)";
				std::cerr << errorMessage << std::endl;
				return false;
			}
		}
		//offset condition
		else {
			//check out of bounds
			if (index + offsetValue + 3 < (int32_t)memoryLayout.size()) {
				index = index + offsetValue;
				std::string data = memoryLayout[index + 3] + memoryLayout[index + 2] + memoryLayout[index + 1] + memoryLayout[index];
				memrefValue = (int32_t)stoll(data, nullptr, 16);
			}
			else {
				errorMessage =  "Error:" + std::to_string(inputInstruction.lineNumber) + ": lw (index out of bounds)";
				std::cerr << errorMessage << std::endl;
				return false;
			}
		}
	}
	//memref = integer
	else if (memref.getType() == integerImmediate) {
		//no offset
		if (arguments.size() == 2) {
			memrefValue = (int32_t)stoll(memref.getValue());
		}
		//offset condition
		else {
			memrefValue = (int32_t)stoll(memref.getValue()) + offsetValue;
		}
	}
	//memref = constant
	else if (memref.getType() == Constant) {
		//no offset
		if (arguments.size() == 2) {
			memrefValue = (int32_t)stoll(constantsMap.find(memref.getValue())->second);
		}
		//offset condition
		else {
			memrefValue = (int32_t)stoll(constantsMap.find(memref.getValue())->second) + offsetValue;
		}
	}
	
	registerOneContent->second = memrefValue;
	incrementCounter();
	return true;
	
}
bool virtualMachine::la_Instruction(instruction inputInstruction) {
	//'la'   <register> SEP <memref>
	// <label> | <immediate> | <register>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument memref = arguments.at(1);
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	int32_t memrefValue;
	int32_t offsetValue;
	if (arguments.size() == 3) {
		offsetValue = (int32_t)stoll(arguments.back().getValue());
	}
	//memref = label
	if (memref.getType() == Label) {
		std::unordered_map<std::string, labelType>::iterator label = labelsMap.find(memref.getValue());
		//check and find label
		if ((label != labelsMap.end())) {
			labelType labelDetails = label->second;
			size_t index = labelDetails.instructionIndex;
			//no offset condition
			if (((int32_t)(labelDetails.instructionIndex + 3) < (int32_t)memoryLayout.size()) && arguments.size() == 2) {
				memrefValue = index;
			}//offset condition
			else if (((int32_t)(labelDetails.instructionIndex + offsetValue + 3) < (int32_t)memoryLayout.size()) && arguments.size() == 3) {
				index = index + offsetValue;
				memrefValue = index;
			}
			//index out of bounds
			else {
				errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": la (index out of bounds)";
				std::cerr << errorMessage << std::endl;
				return false;
			}
		}
		//no label condition
		else {
			errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": la (label not found)";
			std::cerr << errorMessage << std::endl;
			return false;
		}
	}
	//memref = Register
	else if (memref.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(memref.getValue());
		int32_t index = registerTwoContent->second;

		if (arguments.size() == 2) {
			//check out of bounds
			if (index + 3 < (int32_t)memoryLayout.size()) {
				memrefValue = index;
			}
			else {
				errorMessage =  "Error:" + std::to_string(inputInstruction.lineNumber) + ": la (index out of bounds)";
				std::cerr << errorMessage << std::endl;
				return false;
			}
		}
		//offset condition
		else {
			//check out of bounds
			if (index + offsetValue + 3 < (int32_t)memoryLayout.size()) {
				index = index + offsetValue;
				memrefValue = index;
			}
			else {
				errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": la (index out of bounds)";
				std::cerr << errorMessage << std::endl;
				return false;
			}
		}
	}
	//memref = integer
	else if (memref.getType() == integerImmediate) {
		//no offset
		if (arguments.size() == 2) {
			memrefValue = (int32_t)stoll(memref.getValue());
		}
		//offset condition
		else {
			memrefValue = (int32_t)stoll(memref.getValue()) + offsetValue;
		}
	}
	//memref = constant
	else if (memref.getType() == Constant) {
		//no offset
		if (arguments.size() == 2) {
			memrefValue = (int32_t)stoll(constantsMap.find(memref.getValue())->second);
		}
		//offset condition
		else {
			memrefValue = (int32_t)stoll(constantsMap.find(memref.getValue())->second) + offsetValue;
		}
	}

	registerOneContent->second = memrefValue;
	incrementCounter();
	return true;

}
bool virtualMachine::sw_Instruction(instruction inputInstruction) {
	//store_word = 'sw' < register > SEP <memref>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument memref = arguments.at(1);
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	size_t memrefValue;
	size_t offsetValue;
	if (arguments.size() == 3) {
		offsetValue = (int32_t)stoll(arguments.back().getValue());
	}
	//memref = Label
	if (memref.getType() == Label) {
		std::unordered_map<std::string, labelType>::iterator label = labelsMap.find(memref.getValue());
		if ((label != labelsMap.end())) {
			labelType labelDetails = label->second;
			memrefValue = labelDetails.instructionIndex;
		}		
		//no label condition
		else {
			errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": sw (label not found)";
			std::cerr << errorMessage << std::endl;
			return false;
		}

	//memref = Register
	}
	else if (memref.getType() == Register) {
		std::unordered_map<std::string, int32_t>::iterator memrefContent = registersMap.find(memref.getValue());
		memrefValue = memrefContent->second;
	}
	//memref = integer
	else if (memref.getType() == integerImmediate) {
		memrefValue = (int32_t)stoll(memref.getValue());
	}
	//memref = constant
	else if (memref.getType() == Constant) {
		memrefValue = (int32_t)stoll(constantsMap.find(memref.getValue())->second);
	}
	std::stringstream stream; 
	std::string storeValue;
	stream << std::setfill('0') << std:: setw(8) << std::hex << registerOneContent->second;
	storeValue = stream.str();
	
	if (arguments.size() == 2) {
		if ((memrefValue + 3 < memoryLayout.size())) {
			memoryLayout[memrefValue + 3] = storeValue.substr(0, 2);
			memoryLayout[memrefValue + 2] = storeValue.substr(2, 2);
			memoryLayout[memrefValue + 1] = storeValue.substr(4, 2);
			memoryLayout[memrefValue] = storeValue.substr(6, 2);
		
		}
		else {
			errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) + ": sw (index out of bounds)";
			std::cerr << errorMessage << std::endl;
			return false;
		}
	}
	//offset condition
	else {
		if ((memrefValue + offsetValue + 3 < memoryLayout.size())) {
			memrefValue = memrefValue + offsetValue;
			memoryLayout[memrefValue + 3] = storeValue.substr(0, 2);
			memoryLayout[memrefValue + 2] = storeValue.substr(2, 2);
			memoryLayout[memrefValue + 1] = storeValue.substr(4, 2);
			memoryLayout[memrefValue] = storeValue.substr(6, 2);
		}
		else {
			errorMessage = "Error:" + std::to_string(inputInstruction.lineNumber) +  ": sw (index out of bounds)";
			std::cerr << errorMessage << std::endl;
			return false;
		}
	}
	incrementCounter();
	return true;
}
bool virtualMachine::li_Instruction(instruction inputInstruction) {
	//'li'   <register> SEP <immediate>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument immediate = arguments.back();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	int32_t immediateValue;
	//source = integer
	if (immediate.getType() == integerImmediate) {
		immediateValue = (int32_t)stoll(immediate.getValue());
	}
	//source = constant
	else if (immediate.getType() == Constant) {
		immediateValue = (int32_t)stoll(constantsMap.find(immediate.getValue())->second);
	}
	registerOneContent->second = immediateValue;
	incrementCounter();
	return true;


}
bool virtualMachine::move_Instruction(instruction inputInstruction) {
	//'move' <register> SEP <register>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	argument registerTwo = arguments.at(1);
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerTwoContent = registersMap.find(registerTwo.getValue());
	int32_t temp = registerOneContent->second;
	registerOneContent->second = registerTwoContent->second;
	registerTwoContent->second = temp;
	incrementCounter();
	return true;
}
bool virtualMachine::mfhi_Instruction(instruction inputInstruction) {
	//'mfhi' <register>
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerHi = registersMap.find("$hi");
	registerOneContent->second = registerHi->second;
	incrementCounter();
	return true;
}
bool virtualMachine::mflo_Instruction(instruction inputInstruction) {
	//'mflo' < register >
	std::vector<argument> arguments = inputInstruction.instructionArguments;
	argument registerOne = arguments.front();
	std::unordered_map<std::string, int32_t>::iterator registerOneContent = registersMap.find(registerOne.getValue());
	std::unordered_map<std::string, int32_t>::iterator registerLo = registersMap.find("$lo");
	registerOneContent->second = registerLo->second;
	incrementCounter();
	return true;

}

void virtualMachine::printRegisterMap(void){
	for (auto& it : registersMap) {
		if (it.second != 0) {
			std::cout << "Register: " << it.first << " Value: " << it.second << std::endl;
			printf("0x%08x\n", it.second);
		}
	}

}
void virtualMachine::printParseDetails(void) {

	if (instructionList.size() > 0) {
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
	}
	if (labelsMap.size() > 0) {
		std::cout << "List of Labels:" << std::endl;
		for (auto pair : labelsMap) {
			if (pair.second.isTextLabel) {
				std::cout << "{ " << pair.first << ": Type(TextLabel) index(" << pair.second.instructionIndex << ") }\n";
			}
			else {
				std::cout << "{ " << pair.first << ": Type(DataLabel)  index(" << pair.second.instructionIndex << ") }\n";
			}

		}
	}
	if (constantsMap.size() > 0) {
		//std::unordered_map<std::string, std::string> constantsMap;
		std::cout << "List of Constants:" << std::endl;
		for (auto pair : constantsMap) {
			std::cout << "{ " << pair.first << ": " << pair.second << " }\n";
		}
	}
	if (memoryLayout.size() > 0) {
		std::cout << "Memory Layout:" << std::endl;
		for (std::string memorySlot : memoryLayout) {
			std::cout << memorySlot << std::endl;
		}
	}




}
