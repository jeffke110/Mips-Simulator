#include "catch.hpp"
#include "lexer.hpp"
#include "dataGrammar.hpp"
#include "textGrammar.hpp"
#include "parser.hpp"
#include "virtualMachine.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <map>


TEST_CASE("Virtual Machine: add $t0, $t1, $t2", "[parse]") {

    {
        std::cout << "Virtual Machine: add $t0, $t1, $t2" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "add $t0, $t1, $t2 \n ";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);

    }
}
TEST_CASE("memref store function test: lw $t0, $t1", "[parse]") {

    {
        std::cout << "memref function test: lw $t0, $t1 " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "lw $t0, $t1 \n";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);

        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;

        REQUIRE(firstInstruction.lineNumber == 1);
        REQUIRE(firstInstruction.type == RsM);
        REQUIRE(firstInstruction.name == "lw");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "$9");
        REQUIRE(arguments.at(1).getType() == Register);
    }
}
TEST_CASE("memref store function test: lw $t0, label", "[parse]") {

    {
        std::cout << "memref function test: lw $t0, label " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "label: \n lw $t0, label \n";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);

        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;

        REQUIRE(firstInstruction.lineNumber == 2);
        REQUIRE(firstInstruction.type == RsM);
        REQUIRE(firstInstruction.name == "lw");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "label");
        REQUIRE(arguments.at(1).getType() == Label);
    }
}
TEST_CASE("memref store function test: lw $t0, 1", "[parse]") {

    {
        std::cout << "memref function test: lw $t0, 1 " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "lw $t0, 1 \n";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);

        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;

        REQUIRE(firstInstruction.lineNumber == 1);
        REQUIRE(firstInstruction.type == RsM);
        REQUIRE(firstInstruction.name == "lw");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "1");
        REQUIRE(arguments.at(1).getType() == integerImmediate);
    }
}
TEST_CASE("memref store function test: constant lw $t0, constant", "[parse]") {

    {
        std::cout << "memref function test: constant lw $t0, constant" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n constant = 1 \n .text \n lw $t0, constant \n";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parse(iss);
        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;

        REQUIRE(firstInstruction.lineNumber == 4);
        REQUIRE(firstInstruction.type == RsM);
        REQUIRE(firstInstruction.name == "lw");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "constant");
        REQUIRE(arguments.at(1).getType() == Constant);
    }
}
TEST_CASE("memref store function test: constant lw $t0, 3(constant)", "[parse]") {

    {
        std::cout << "memref function test: constant lw $t0, 3(constant)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n constant = 1 \n .text \n lw $t0, 3(constant) \n";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parse(iss);
        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;

        REQUIRE(firstInstruction.lineNumber == 4);
        REQUIRE(firstInstruction.type == RsM);
        REQUIRE(firstInstruction.name == "lw");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "constant");
        REQUIRE(arguments.at(1).getType() == Constant);
        REQUIRE(arguments.at(2).getValue() == "3");
        REQUIRE(arguments.at(2).getType() == Offset);
    }
}
TEST_CASE("memref store function test: constant lw $t0, (constant)", "[parse]") {

    {
        std::cout << "memref function test: constant lw $t0, (constant)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n constant = 1 \n .text \n lw $t0, (constant) \n";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parse(iss);
        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;
        REQUIRE(firstInstruction.lineNumber == 4);
        REQUIRE(firstInstruction.type == RsM);
        REQUIRE(firstInstruction.name == "lw");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "constant");
        REQUIRE(arguments.at(1).getType() == Constant);
    }
}
TEST_CASE("memref store function test: lw $t0, 4(label)", "[parse]") {

    {
        std::cout << "memref function test: lw $t0, 4(label)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "label: \n lw $t0, 4(label) \n";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);
        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;
        REQUIRE(firstInstruction.lineNumber == 2);
        REQUIRE(firstInstruction.type == RsM);
        REQUIRE(firstInstruction.name == "lw");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "label");
        REQUIRE(arguments.at(1).getType() == Label);
        REQUIRE(arguments.at(2).getValue() == "4");
        REQUIRE(arguments.at(2).getType() == Offset);
    }
}
TEST_CASE("memref store function test: lw $t0, (label)", "[parse]") {

    {
        std::cout << "memref function test: lw $t0, (label)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "label: \n lw $t0, (label) \n";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);
        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;
        REQUIRE(firstInstruction.lineNumber == 2);
        REQUIRE(firstInstruction.type == RsM);
        REQUIRE(firstInstruction.name == "lw");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "label");
        REQUIRE(arguments.at(1).getType() == Label);
    }
}
TEST_CASE("memref store function test: lw $t0, 8($t0)", "[parse]") {

    {
        std::cout << "memref function test: lw $t0, 8($t0)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "lw $t0, 8($t0)\n";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);
        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;
        REQUIRE(firstInstruction.lineNumber == 1);
        REQUIRE(firstInstruction.type == RsM);
        REQUIRE(firstInstruction.name == "lw");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "$8");
        REQUIRE(arguments.at(1).getType() == Register);
        REQUIRE(arguments.at(2).getValue() == "8");
        REQUIRE(arguments.at(2).getType() == Offset);
    }
}
TEST_CASE("memref store function test: lw $t0, ($t0)", "[parse]") {

    {
        std::cout << "memref function test: lw $t0, ($t0)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "lw $t0, ($t0)\n";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);
        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;
        REQUIRE(firstInstruction.lineNumber == 1);
        REQUIRE(firstInstruction.type == RsM);
        REQUIRE(firstInstruction.name == "lw");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "$8");
        REQUIRE(arguments.at(1).getType() == Register);
    }
}
TEST_CASE("memref store function test: lw $t0, error($t0) ERROR test", "[parse]") {

    {
        std::cout << "memref function test: lw $t0, error($t0)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "lw $t0, error($t0) \n";
        std::istringstream iss(input);
        Parser parseObject;
        //parseObject.parseTextTest(iss);
        REQUIRE(parseObject.parseTextTest(iss) == false);
        //parseObject.printParseDetails();
       
    }
}
TEST_CASE("memref store function test: lw $t0, ($t0), ERROR test", "[parse]") {

    {
        std::cout << "memref function test: lw $t0, ($t0), " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "lw $t0, ($t0), \n";
        std::istringstream iss(input);
        Parser parseObject;
        //parseObject.parseTextTest(iss);
        REQUIRE(parseObject.parseTextTest(iss) == false);
        //parseObject.printParseDetails();

    }

}
TEST_CASE("memref store function test: given test case ", "[parse]") {

    {
        std::cout << "memref function test: given test case " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "str: .asciiz \"hello world!\" \n"
            ".text \n"
            "main: \n" 
            "lb $t0, str # load 'h'\n"
            "lb $t1, 1(str) # load 'e'\n"
            "lb $t2, 2(str) # load 'l'\n"
            "lb $t3, 3(str) # load 'l'\n"
            "lb $t4, 4(str) # load 'o'\n";
        std::istringstream iss(input);
        Parser parseObject;
        //parseObject.parseTextTest(iss);
        REQUIRE(parseObject.parse(iss) == true);
        //parseObject.printParseDetails();

    }
}
TEST_CASE("Virtual Machine: add function ", "[parse]") {

    {
        std::cout << "Virtual Machine: add function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "add $11, $9, $10 \n"  // 3
            "add $12, $11, 1 \n"  // 4
            "add $13, $11, CONSTANT \n";// 5
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        //set register values
        int32_t one = 1;
        int32_t two = 2;
        environment.registersMap.find("$9")->second = one;
        environment.registersMap.find("$10")->second = two;
        //---------------------------------------------
        environment.setMaps(parseObject);
        REQUIRE(environment.add_Instruction(environment.instructionList.front()) == true); 
        REQUIRE(environment.add_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);
        REQUIRE(environment.registersMap.find("$11")->second == 3);
        REQUIRE(environment.registersMap.find("$12")->second == 4);
        REQUIRE(environment.registersMap.find("$13")->second == 5);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: addu function ", "[parse]") {

    {
        std::cout << "Virtual Machine: addu function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "addu $11, $9, $10 \n"  // 3
            "addu $12, $11, 1 \n"  // 4
            "addu $13, $11, CONSTANT \n";// 5
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        //set register values
        int32_t one = 1;
        int32_t two = 2;
        environment.registersMap.find("$9")->second = one;
        environment.registersMap.find("$10")->second = two;
        //---------------------------------------------
        environment.setMaps(parseObject);
        REQUIRE(environment.addu_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.addu_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);
        REQUIRE(environment.registersMap.find("$11")->second == 3);
        REQUIRE(environment.registersMap.find("$12")->second == 4);
        REQUIRE(environment.registersMap.find("$13")->second == 5);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: sub function ", "[parse]") {

    {
        std::cout << "Virtual Machine: sub function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "sub $11, $9, $10 \n"  // 3
            "sub $12, $9, 3 \n"  // 4
            "sub $13, $9, CONSTANT \n";// 5
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        //set register values
        int32_t one = 10;
        int32_t two = 3;
        environment.registersMap.find("$9")->second = one;
        environment.registersMap.find("$10")->second = two;
        //---------------------------------------------
        
        
        
        environment.setMaps(parseObject);
        REQUIRE(environment.sub_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.sub_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);
        REQUIRE(environment.registersMap.find("$11")->second == 7);
        REQUIRE(environment.registersMap.find("$12")->second == 7);
        REQUIRE(environment.registersMap.find("$13")->second == 7);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: subu function ", "[parse]") {

    {
        std::cout << "Virtual Machine: subu function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "sub $11, $9, $10 \n"  // 3
            "sub $12, $9, 3 \n"  // 4
            "sub $13, $9, CONSTANT \n";// 5
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        //set register values
        int32_t one = 10;
        int32_t two = 3;
        environment.registersMap.find("$9")->second = one;
        environment.registersMap.find("$10")->second = two;
        //---------------------------------------------
        
        
        
        environment.setMaps(parseObject);
        REQUIRE(environment.subu_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.subu_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);
        REQUIRE(environment.registersMap.find("$11")->second == 7);
        REQUIRE(environment.registersMap.find("$12")->second == 7);
        REQUIRE(environment.registersMap.find("$13")->second == 7);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: mult function ", "[parse]") {

    {
        std::cout << "Virtual Machine: mult function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "mult $11, $9 \n"
            "mult $10, $9 \n";
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        //set register values
        int32_t one = 3;
        int32_t two = 10;
        environment.registersMap.find("$9")->second = one;
        environment.registersMap.find("$10")->second = two;
        //---------------------------------------------
        
        
        
        environment.setMaps(parseObject);
        REQUIRE(environment.mult_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.registersMap.find("$hi")->second == 0);
        REQUIRE(environment.registersMap.find("$lo")->second == 0);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.registersMap.find("$hi")->second == 0);
        REQUIRE(environment.registersMap.find("$lo")->second == 30);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: multu function ", "[parse]") {

    {
        std::cout << "Virtual Machine: mult function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "multu $11, $9 \n"
            "multu $10, $9 \n";
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        //set register values
        int32_t one = 3;
        int32_t two = 10;
        environment.registersMap.find("$9")->second = one;
        environment.registersMap.find("$10")->second = two;
        //---------------------------------------------
        
        
        
        environment.setMaps(parseObject);
        REQUIRE(environment.multu_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.registersMap.find("$hi")->second == 0);
        REQUIRE(environment.registersMap.find("$lo")->second == 0);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.registersMap.find("$hi")->second == 0);
        REQUIRE(environment.registersMap.find("$lo")->second == 30);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: div function ", "[parse]") {

    {
        std::cout << "Virtual Machine: div function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "div $11, $13 \n" //testing divide by zero
            "div $9, $10 \n";
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        //set register values
        int32_t one = 23;
        int32_t two = 5;
        environment.registersMap.find("$9")->second = one;
        environment.registersMap.find("$10")->second = two;
        //---------------------------------------------
        
        
        
        environment.setMaps(parseObject);
        REQUIRE(environment.div_Instruction(environment.instructionList.front()) == false);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.registersMap.find("$hi")->second == 3);
        REQUIRE(environment.registersMap.find("$lo")->second == 4);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: divu function ", "[parse]") {

    {
        std::cout << "Virtual Machine: div function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "divu $11, $13 \n" // test divide by zero case
            "divu $9, $10 \n";
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        //set register values
        int32_t one = 23;
        int32_t two = 5;
        environment.registersMap.find("$9")->second = one;
        environment.registersMap.find("$10")->second = two;
        //---------------------------------------------
        
        
        
        environment.setMaps(parseObject);
        REQUIRE(environment.divu_Instruction(environment.instructionList.front()) == false);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.registersMap.find("$hi")->second == 3);
        REQUIRE(environment.registersMap.find("$lo")->second == 4);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: and function ", "[parse]") {

    {
        std::cout << "Virtual Machine: and function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 5 \n"
            ".text \n"
            "main: \n"
            "and $11, $9, $10 \n"   // $11 = 5
            "and $12, $9, 5 \n"     // $12 = 5
            "and $13, $9, CONSTANT \n";  // $13 = 5
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        //set register values
        int32_t one = 15;
        int32_t two = 5;
        environment.registersMap.find("$9")->second = one;
        environment.registersMap.find("$10")->second = two;
        //---------------------------------------------
        
        
        
        environment.setMaps(parseObject);
        REQUIRE(environment.and_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.and_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);
        REQUIRE(environment.registersMap.find("$11")->second == 5);
        REQUIRE(environment.registersMap.find("$12")->second == 5);
        REQUIRE(environment.registersMap.find("$13")->second == 5);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: nor function ", "[parse]") {

    {
        std::cout << "Virtual Machine: nor function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 13 \n"
            ".text \n"
            "main: \n"
            "nor $11, $9, $10 \n"  //$11 = -30
            "nor $12, $9, 13 \n"   
            "nor $13, $9, CONSTANT \n";
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        //set register values
        int32_t one = 20;
        int32_t two = 13;
        environment.registersMap.find("$9")->second = one;
        environment.registersMap.find("$10")->second = two;
        //---------------------------------------------
        
        
        
        environment.setMaps(parseObject);
        //test instruction function
        REQUIRE(environment.nor_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.nor_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);
        REQUIRE(environment.registersMap.find("$11")->second == -30);
        REQUIRE(environment.registersMap.find("$12")->second == -30);
        REQUIRE(environment.registersMap.find("$13")->second == -30);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: or function ", "[parse]") {

    {
        std::cout << "Virtual Machine: or function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 13 \n"
            ".text \n"
            "main: \n"
            "or $11, $9, $10 \n"  //$11 = 25
            "or $12, $9, 13 \n"
            "or $13, $9, CONSTANT \n";
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        //set register values
        int32_t one = 20;
        int32_t two = 13;
        environment.registersMap.find("$9")->second = one;
        environment.registersMap.find("$10")->second = two;
        //---------------------------------------------
        
        
        
        environment.setMaps(parseObject);
        //test instruction function
        REQUIRE(environment.or_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.or_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);
        REQUIRE(environment.registersMap.find("$11")->second == 29);
        REQUIRE(environment.registersMap.find("$12")->second == 29);
        REQUIRE(environment.registersMap.find("$13")->second == 29);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: xor function ", "[parse]") {

    {
        std::cout << "Virtual Machine: xor function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 13 \n"
            ".text \n"
            "main: \n"
            "xor $11, $9, $10 \n"  //$11 = 25
            "xor $12, $9, 13 \n"
            "xor $13, $9, CONSTANT \n";
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        //set register values
        int32_t one = 20;
        int32_t two = 13;
        environment.registersMap.find("$9")->second = one;
        environment.registersMap.find("$10")->second = two;
        //---------------------------------------------
        
        
        
        environment.setMaps(parseObject);
        //test instruction function
        REQUIRE(environment.xor_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.xor_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);
        REQUIRE(environment.registersMap.find("$11")->second == 25);
        REQUIRE(environment.registersMap.find("$12")->second == 25);
        REQUIRE(environment.registersMap.find("$13")->second == 25);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: not function ", "[parse]") {

    {
        std::cout << "Virtual Machine: not function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 4294901760 \n"
            ".text \n"
            "main: \n"
            "not $11, $9 \n"  //$11 = -30
            "not $12, 4294901760 \n"
            "not $13, CONSTANT \n";
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        //set register values
        int32_t one = 4294901760;
        environment.registersMap.find("$9")->second = one;
        //---------------------------------------------
        
        
        
        environment.setMaps(parseObject);
        //test instruction function
        REQUIRE(environment.not_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.not_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);
        REQUIRE(environment.registersMap.find("$11")->second == 65535);
        REQUIRE(environment.registersMap.find("$12")->second == 65535);
        REQUIRE(environment.registersMap.find("$13")->second == 65535);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: lw function (Constant and Integers)", "[parse]") {

    {
        std::cout << "Virtual Machine: lw function  (Constant and Integers)  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 12 \n"
            ".text \n"
            "main: \n"
            "lw $9, 10 \n"
            "lw $10, 1(10) \n"
            "lw $11, CONSTANT \n"
            "lw $12, 1(CONSTANT) \n"
            "lw $13, (14) \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        environment.lw_Instruction(environment.instructionList.front());
        environment.lw_Instruction(environment.instructionList.at(1));
        environment.lw_Instruction(environment.instructionList.at(2));
        environment.lw_Instruction(environment.instructionList.at(3));
        environment.executeInstruction(environment.instructionList.back());
        REQUIRE(environment.registersMap.find("$9")->second == 10);
        REQUIRE(environment.registersMap.find("$10")->second == 11);
        REQUIRE(environment.registersMap.find("$11")->second == 12);
        REQUIRE(environment.registersMap.find("$12")->second == 13);
        REQUIRE(environment.registersMap.find("$13")->second == 14);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: lw function (Labels)", "[parse]") {
    {
        std::cout << "Virtual Machine: lw function (Labels)  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "var6: .byte 1, 2, 3, 4, 5, 6, 7, 8 \n"
            "CONSTANT = 12 \n"
            ".text \n"
            "main: \n"
            "add $9, $10, $zero \n"
            "label: \n"
            "lw $11, label \n"
            "lw $12, 1(label) \n"
            "lw $12, 100(label) \n"     //out of bounds
            "lw $12, 100(notfound) \n"; //label cannot be found

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        environment.add_Instruction(environment.instructionList.front());
        environment.lw_Instruction(environment.instructionList.at(1));
        environment.lw_Instruction(environment.instructionList.at(2));
        REQUIRE(environment.lw_Instruction(environment.instructionList.at(3)) == false);
        REQUIRE(environment.lw_Instruction(environment.instructionList.at(4)) == false);
        //environment.lw_Instruction(environment.instructionList.back());
        
        REQUIRE(environment.registersMap.find("$11")->second == 84148994);
        REQUIRE(environment.registersMap.find("$12")->second == 100992003);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: lw function (Registers)", "[parse]") {

    {
        std::cout << "Virtual Machine: lw function (Registers)  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "var6: .byte 1, 2, 3, 4, 5, 6, 7, 8 \n"
            "CONSTANT = 12 \n"
            ".text \n"
            "main: \n"
            "add $9, $10, 2 \n"
            "add $10, $10, 100 \n"
            "label: \n"
            "lw $11, $9 \n"
            "lw $12, 1($9) \n"
            "lw $13, 100($9) \n" //out of bounds
            "lw $13, $10 \n"; //out of bounds

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        environment.add_Instruction(environment.instructionList.front());
        environment.add_Instruction(environment.instructionList.at(1));
        environment.lw_Instruction(environment.instructionList.at(2));
        environment.lw_Instruction(environment.instructionList.at(3));
        REQUIRE(environment.lw_Instruction(environment.instructionList.at(4)) == false);
        REQUIRE(environment.lw_Instruction(environment.instructionList.at(5)) == false);
        //REQUIRE(environment.lw_Instruction(environment.instructionList.at(3)) == false);
        //REQUIRE(environment.lw_Instruction(environment.instructionList.at(4)) == false);
        //environment.lw_Instruction(environment.instructionList.back());

        REQUIRE(environment.registersMap.find("$11")->second == 100992003);
        REQUIRE(environment.registersMap.find("$12")->second == 117835012);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: la function (Constant and Integers)", "[parse]") {

    {
        std::cout << "Virtual Machine: la function  (Constant and Integers)  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 12 \n"
            ".text \n"
            "main: \n"
            "la $9, 10 \n"
            "la $10, 1(10) \n"
            "la $11, CONSTANT \n"
            "la $12, 1(CONSTANT) \n"
            "la $13, (14) \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        environment.la_Instruction(environment.instructionList.front());
        environment.la_Instruction(environment.instructionList.at(1));
        environment.la_Instruction(environment.instructionList.at(2));
        environment.executeInstruction(environment.instructionList.at(3));
        environment.la_Instruction(environment.instructionList.back());
        REQUIRE(environment.registersMap.find("$9")->second == 10);
        REQUIRE(environment.registersMap.find("$10")->second == 11);
        REQUIRE(environment.registersMap.find("$11")->second == 12);
        REQUIRE(environment.registersMap.find("$12")->second == 13);
        REQUIRE(environment.registersMap.find("$13")->second == 14);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: la function (Labels)", "[parse]") {
    {
        std::cout << "Virtual Machine: la function (Labels)  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "var6: .byte 1, 2, 3, 4, 5, 6, 7, 8 \n"
            "CONSTANT = 12 \n"
            ".text \n"
            "main: \n"
            "add $9, $10, $zero \n"
            "label: \n"
            "lw $11, label \n"
            "lw $12, 1(label) \n"
            "lw $12, 100(label) \n"     //out of bounds
            "lw $12, 100(notfound) \n"; //label cannot be found

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        environment.add_Instruction(environment.instructionList.front());
        environment.la_Instruction(environment.instructionList.at(1));
        environment.la_Instruction(environment.instructionList.at(2));
        REQUIRE(environment.la_Instruction(environment.instructionList.at(3)) == false);
        REQUIRE(environment.la_Instruction(environment.instructionList.at(4)) == false);
        //environment.lw_Instruction(environment.instructionList.back());

        REQUIRE(environment.registersMap.find("$11")->second == 1);
        REQUIRE(environment.registersMap.find("$12")->second == 2);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: la function (Registers)", "[parse]") {

    {
        std::cout << "Virtual Machine: la function (Registers)  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "var6: .byte 1, 2, 3, 4, 5, 6, 7, 8 \n"
            "CONSTANT = 12 \n"
            ".text \n"
            "main: \n"
            "add $9, $10, 2 \n"
            "add $10, $10, 100 \n"
            "label: \n"
            "la $11, $9 \n"
            "la $12, 1($9) \n"
            "la $13, 100($9) \n" //out of bounds
            "la $13, $10 \n"; //out of bounds

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        environment.add_Instruction(environment.instructionList.front());
        environment.add_Instruction(environment.instructionList.at(1));
        environment.la_Instruction(environment.instructionList.at(2));
        environment.la_Instruction(environment.instructionList.at(3));
        REQUIRE(environment.la_Instruction(environment.instructionList.at(4)) == false);
        REQUIRE(environment.la_Instruction(environment.instructionList.at(5)) == false);
        //REQUIRE(environment.lw_Instruction(environment.instructionList.at(3)) == false);
        //REQUIRE(environment.lw_Instruction(environment.instructionList.at(4)) == false);
        //environment.lw_Instruction(environment.instructionList.back());

        REQUIRE(environment.registersMap.find("$11")->second == 2);
        REQUIRE(environment.registersMap.find("$12")->second == 3);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: sw function", "[parse]") {
    //'sw'   <register> SEP <memref>
    {
        std::cout << "Virtual Machine: sw function  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "var6: .space 20 \n"
            "CONSTANT = 5 \n"
            ".text \n"
            "main: \n"
            "li $10, 10 \n"
            "li $9, 4 \n"
            "sw $9, 1 \n"
            "sw $9, CONSTANT \n"
            "sw $9, $10 \n"
            "sw $9, 20 \n"; //out of bounds

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.li_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.sw_Instruction(environment.instructionList.at(2)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(3)) == true);
        REQUIRE(environment.sw_Instruction(environment.instructionList.at(4)) == true);
        REQUIRE(environment.sw_Instruction(environment.instructionList.at(5)) == false);
        //REQUIRE(environment.mult_Instruction(environment.instructionList.at(2)) == true);
        //REQUIRE(environment.mflo_Instruction(environment.instructionList.at(3)) == true);
        //environment.printParseDetails();

        //REQUIRE(environment.registersMap.find("$9")->second == 2);
        //REQUIRE(environment.registersMap.find("$10")->second == 3);
        //REQUIRE(environment.registersMap.find("$11")->second == 6);
        //REQUIRE(environment.registersMap.find("$lo")->second == 6);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: sw function (offset)", "[parse]") {
    //'sw'   <register> SEP <memref>
    {
        std::cout << "Virtual Machine: sw function  (offset)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "var6: .space 20 \n"
            "CONSTANT = 5 \n"
            ".text \n"
            "main: \n"
            "li $10, 10 \n"
            "li $9, 4 \n"
            "sw $9, 1(1) \n"
            "sw $9, 1(CONSTANT) \n"
            "sw $9, 1($10) \n"
            "sw $9, 1(20) \n"; //out of bounds

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.li_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.sw_Instruction(environment.instructionList.at(2)) == true);
        REQUIRE(environment.sw_Instruction(environment.instructionList.at(3)) == true);
        REQUIRE(environment.sw_Instruction(environment.instructionList.at(4)) == true);
        REQUIRE(environment.sw_Instruction(environment.instructionList.at(5)) == false);
        //environment.printParseDetails();
    }
}
TEST_CASE("Virtual Machine: li function", "[parse]") {
    //'li'   <register> SEP <immediate>
    {
        std::cout << "Virtual Machine: li function  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 12 \n"
            ".text \n"
            "main: \n"
            "li $9, 2 \n"
            "li $10, CONSTANT \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(1)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 2);
        REQUIRE(environment.registersMap.find("$10")->second == 12);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: move function", "[parse]") {
    //'move' <register> SEP <register>
    {
        std::cout << "Virtual Machine: move function  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 2 \n"
            "li $10, CONSTANT \n"
            "move $10, $9 \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
       
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.li_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);
        
        REQUIRE(environment.registersMap.find("$9")->second == 3);
        REQUIRE(environment.registersMap.find("$10")->second == 2);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: mfhi function", "[parse]") {
    //'mfhi' <register>
    {
        std::cout << "Virtual Machine: mfhi function  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 30000000 \n"
            ".text \n"
            "main: \n"
            "li $9, 10000 \n"
            "li $10, CONSTANT \n"
            "mult $9, $10 \n"
            "mfhi $11 \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.li_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.mult_Instruction(environment.instructionList.at(2)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(3)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 10000);
        REQUIRE(environment.registersMap.find("$10")->second == 30000000);
        REQUIRE(environment.registersMap.find("$11")->second == 69);
        REQUIRE(environment.registersMap.find("$hi")->second == 69);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: mflo function", "[parse]") {
    //'mflo' <register>
    {
        std::cout << "Virtual Machine: mflo function  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 2 \n"
            "li $10, CONSTANT \n"
            "mult $9, $10 \n"
            "mflo $11 \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.li_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.mult_Instruction(environment.instructionList.at(2)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(3)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 2);
        REQUIRE(environment.registersMap.find("$10")->second == 3);
        REQUIRE(environment.registersMap.find("$11")->second == 6);
        REQUIRE(environment.registersMap.find("$lo")->second == 6);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: beq function (with Registers)", "[parse]") {
    //'beq' < register > SEP <register> SEP <label>
    {
        std::cout << "Virtual Machine: beq function (with Registers)  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "li $10, 1 \n"
            "beq $9, $10, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.li_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 1);
        REQUIRE(environment.registersMap.find("$10")->second == 1);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: beq function (with immediate int)", "[parse]") {
    //'beq' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: beq function (with immediate int) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "beq $9, 1, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.beq_Instruction(environment.instructionList.at(1)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 1);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: beq function (with constant)", "[parse]") {
    //'beq' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: beq function (with constant) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 1 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "beq $9, CONSTANT, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.beq_Instruction(environment.instructionList.at(1)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 1);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: beq function (with errors)", "[parse]") {
    //'beq' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: beq function (with errors) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 1 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "beq $9, CONSTANT, hello \n"
            "beq $9, CONSTANT, more \n"
            "more: \n" ;

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.beq_Instruction(environment.instructionList.at(1)) == false);
        REQUIRE(environment.beq_Instruction(environment.instructionList.at(2)) == false);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: bne function (with Registers)", "[parse]") {
    //'bne' < register > SEP <register> SEP <label>
    {
        std::cout << "Virtual Machine: bne function (with Registers)  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "li $10, 2 \n"
            "bne $9, $10, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.li_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 1);
        REQUIRE(environment.registersMap.find("$10")->second == 2);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: bne function (with immediate int)", "[parse]") {
    //'bne' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: bne function (with immediate int) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "bne $9, 2, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.bne_Instruction(environment.instructionList.at(1)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 1);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: bne function (with constant)", "[parse]") {
    //'bne' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: bne function (with constant) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "bne $9, CONSTANT, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.bne_Instruction(environment.instructionList.at(1)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 1);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: bne function (with errors)", "[parse]") {
    //'bne' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: bne function (with errors) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "bne $9, CONSTANT, hello \n"
            "bne $9, CONSTANT, more \n"
            "more: \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.bne_Instruction(environment.instructionList.at(1)) == false);
        REQUIRE(environment.bne_Instruction(environment.instructionList.at(2)) == false);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: blt function (with Registers)", "[parse]") {
    //'blt' < register > SEP <register> SEP <label>
    {
        std::cout << "Virtual Machine: blt function (with Registers)  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "li $10, 2 \n"
            "blt $9, $10, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.li_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 1);
        REQUIRE(environment.registersMap.find("$10")->second == 2);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: blt function (with immediate int)", "[parse]") {
    //'blt' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: blt function (with immediate int) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "blt $9, 2, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.blt_Instruction(environment.instructionList.at(1)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 1);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: blt function (with constant)", "[parse]") {
    //'blt' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: blt function (with constant) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "blt $9, CONSTANT, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.blt_Instruction(environment.instructionList.at(1)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 1);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: blt function (with errors)", "[parse]") {
    //'blt' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: blt function (with errors) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "blt $9, CONSTANT, hello \n"
            "blt $9, CONSTANT, more \n"
            "more: \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.blt_Instruction(environment.instructionList.at(1)) == false);
        REQUIRE(environment.blt_Instruction(environment.instructionList.at(2)) == false);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: ble function (with Registers)", "[parse]") {
    //'ble' < register > SEP <register> SEP <label>
    {
        std::cout << "Virtual Machine: ble function (with Registers)  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "li $10, 2 \n"
            "ble $9, $10, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.li_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 1);
        REQUIRE(environment.registersMap.find("$10")->second == 2);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: ble function (with immediate int)", "[parse]") {
    //'ble' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: ble function (with immediate int) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 2 \n"
            "other: \n"
            "ble $9, 2, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.ble_Instruction(environment.instructionList.at(1)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 2);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: ble function (with constant)", "[parse]") {
    //'ble' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: ble function (with constant) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "ble $9, CONSTANT, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.ble_Instruction(environment.instructionList.at(1)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 1);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: ble function (with errors)", "[parse]") {
    //'ble' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: ble function (with errors) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "li $9, 1 \n"
            "other: \n"
            "ble $9, CONSTANT, hello \n"
            "ble $9, CONSTANT, more \n"
            "more: \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.ble_Instruction(environment.instructionList.at(1)) == false);
        REQUIRE(environment.ble_Instruction(environment.instructionList.at(2)) == false);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: bgt function (with Registers)", "[parse]") {
    //'bgt' < register > SEP <register> SEP <label>
    {
        std::cout << "Virtual Machine: bgt function (with Registers)  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 4 \n"
            "other: \n"
            "li $10, 2 \n"
            "bgt $9, $10, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.li_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 4);
        REQUIRE(environment.registersMap.find("$10")->second == 2);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: bgt function (with immediate int)", "[parse]") {
    //'bgt' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: bgt function (with immediate int) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 4 \n"
            "other: \n"
            "bgt $9, 2, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.bgt_Instruction(environment.instructionList.at(1)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 4);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: bgt function (with constant)", "[parse]") {
    //'bgt' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: bgt function (with constant) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "li $9, 4 \n"
            "other: \n"
            "bgt $9, CONSTANT, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.bgt_Instruction(environment.instructionList.at(1)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 4);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: bgt function (with errors)", "[parse]") {
    //'bgt' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: bgt function (with errors) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "li $9, 4 \n"
            "other: \n"
            "bgt $9, CONSTANT, hello \n"
            "bgt $9, CONSTANT, more \n"
            "more: \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.bgt_Instruction(environment.instructionList.at(1)) == false);
        REQUIRE(environment.bgt_Instruction(environment.instructionList.at(2)) == false);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: bge function (with Registers)", "[parse]") {
    //'bge' < register > SEP <register> SEP <label>
    {
        std::cout << "Virtual Machine: bge function (with Registers)  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 2 \n"
            "other: \n"
            "li $10, 2 \n"
            "bge $9, $10, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.li_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 2);
        REQUIRE(environment.registersMap.find("$10")->second == 2);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: bge function (with immediate int)", "[parse]") {
    //'bge' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: bge function (with immediate int) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 4 \n"
            "other: \n"
            "bge $9, 2, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.bge_Instruction(environment.instructionList.at(1)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 4);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: bge function (with constant)", "[parse]") {
    //'bge' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: bge function (with constant) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "li $9, 4 \n"
            "other: \n"
            "bge $9, CONSTANT, other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.bge_Instruction(environment.instructionList.at(1)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 4);
        REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: bge function (with errors)", "[parse]") {
    //'bge' <register> SEP <immediate int> SEP <label>
    {
        std::cout << "Virtual Machine: bge function (with errors) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "li $9, 4 \n"
            "other: \n"
            "bge $9, CONSTANT, hello \n"
            "bge $9, CONSTANT, more \n"
            "more: \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.bge_Instruction(environment.instructionList.at(1)) == false);
        REQUIRE(environment.bge_Instruction(environment.instructionList.at(2)) == false);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: j function (with Registers)", "[parse]") {
    //j <label>
    {
        std::cout << "Virtual Machine: j function (with Registers)  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 3 \n"
            ".text \n"
            "main: \n"
            "li $9, 2 \n"
            "other: \n"
            "li $10, 2 \n"
            "j other \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        REQUIRE(environment.li_Instruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);

        REQUIRE(environment.registersMap.find("$9")->second == 2);
        REQUIRE(environment.registersMap.find("$10")->second == 2);
        //REQUIRE(environment.registersMap.find("$pc")->second == 1);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: j function (with errors)", "[parse]") {
    //j <label>
    {
        std::cout << "Virtual Machine: j function (with errors) " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "li $9, 4 \n"
            "other: \n"
            "j more \n"
            "more: \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        
        
        
        environment.setMaps(parseObject);

        //environment.printParseDetails();
        //REQUIRE(environment.li_Instruction(environment.instructionList.front()) == true);
        //REQUIRE(environment.j_Instruction(environment.instructionList.at(1)) == false);
        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: check main label function", "[parse]") {
    //j <label>
    {
        std::cout << "Virtual Machine: check main label function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "li $9, 4 \n"
            "other: \n"
            "j more \n"
            "more: \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        environment.setMaps(parseObject);

        REQUIRE(environment.checkMainLabel() == true);
    }
}
TEST_CASE("Virtual Machine: print count function", "[parse]") {
    //j <label>
    {
        std::cout << "Virtual Machine: check main label function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "li $9, 4 \n"
            "other: \n"
            "j more \n"
            "more: \n";

        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        environment.setMaps(parseObject);
        REQUIRE(environment.checkMainLabel() == true);
        environment.printCounter();
        environment.incrementCounter();

    }
}
TEST_CASE("Virtual Machine: nop function ", "[parse]") {

    {
        std::cout << "Virtual Machine: nop function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            ".text \n"
            "main: \n"
            "nop \n"
            "j next \n"
            "nop \n"
            "next: \n"
            "nop \n"
            "j main \n";
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;
        //---------------------------------------------
        
        
        
        environment.setMaps(parseObject);
        REQUIRE(environment.executeInstruction(environment.instructionList.front()) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(1)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(2)) == true);
        REQUIRE(environment.executeInstruction(environment.instructionList.at(3)) == true);

    }
}
TEST_CASE("Virtual Machine: user input function ", "[parse]") {

    {
        std::cout << "Virtual Machine: user input function " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "CONSTANT = 2 \n"
            "r1: .space 4 \n"
            "r2: .space 12 \n"
            "r3: .space 4 \n"
            "var: .word 7 \n"
            ".text \n"
            "main: \n"
            "add $11, $9, $10 \n"  // 3
            "add $12, $11, 1 \n"  // 4
            "add $13, $11, CONSTANT \n";// 5
        std::istringstream iss(input);
        Parser parseObject;
        REQUIRE(parseObject.parse(iss) == true);
        virtualMachine environment;

        //---------------------------------------------
        
        
        
        environment.setMaps(parseObject);
        REQUIRE(environment.userInputFunction("step") == false);
        REQUIRE(environment.userInputFunction("print $t0") == true);
        REQUIRE(environment.userInputFunction("print $tf0") == true);
        REQUIRE(environment.userInputFunction("print &0x00000001") == true);
        REQUIRE(environment.userInputFunction("print &0x005000001") == true);
        REQUIRE(environment.userInputFunction("status") == true);

        //environment.printRegisterMap();
    }
}
TEST_CASE("Virtual Machine: thread functionality one (test01.asm)", "[parse]") {

    {
        std::cout << "Virtual Machine: thread functionality one (test01.asm)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
       
        /*std::string input = ".data \n"
            ".space 8 \n"
            "var1: .word 1 \n"
            "var2: .word -2 \n"
            ".text \n"
            "main: \n"
            "la $t0, var1 \n"
            "lw $t1, 0 \n"
            "lw $t2, $t0 \n"
            "lw $t3, 4($t0) \n"
            "lw $t4, 4(var1) \n"
            "lw $t5, var2 \n";

        */
        std::string input = ".data \n"
            "n: .word 10 \n"
            "sumOfSquares: .word 0 \n"
            ".text \n"
            "main: \n"
            "lw $t0, n \n"
            "li $t1, 1 \n"
            "li $t2, 0 \n"
            "sumLoop: \n"
            "mult $t1, $t1 \n"
            "mflo $t3 \n"
            "add $t2, $t2, $t3 \n"
            "add $t1, $t1, 1 \n"
            "ble $t1, $t0, sumLoop \n"
            "sw  $t2, sumOfSquares \n"
            "end: \n"
            "j end \n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
        virtualMachine environment;
        environment.setMaps(mipsParser);
        REQUIRE(environment.userInputFunction("run") == true);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        REQUIRE(environment.userInputFunction("break") == true);
        //REQUIRE(environment.registersMap.find("$8")->second == 8);
        //REQUIRE(environment.registersMap.find("$10")->second == 1);

    }
}
TEST_CASE("Virtual Machine: thread functionality two (test5.asm)", "[parse]") {

    {
        std::cout << "Virtual Machine: thread functionality two (test5.asm)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "VALUE = -1 \n"
            "var: .word 1 \n"
            ".text \n"
            "main: \n"
            "lw $t0, var \n"
            "add $t1, $t0, VALUE \n"
            "add $t2, $t1, $t0 \n";


        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
        virtualMachine environment;
        environment.setMaps(mipsParser);
        REQUIRE(environment.userInputFunction("run") == true);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        REQUIRE(environment.userInputFunction("break") == true);
        REQUIRE(environment.registersMap.find("$pc")->second == 3);
        REQUIRE(environment.registersMap.find("$8")->second == 1);
        REQUIRE(environment.registersMap.find("$10")->second == 1);

    }
}
TEST_CASE("Virtual Machine: thread functionality three (test10.asm)", "[parse]") {

    {
        std::cout << "Virtual Machine: thread functionality three (test10.asm)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "VALUE = 4\n"
            "var1: .word 2 \n"
            "var2: .word 1073741824 #  = 2 ^ 30 \n"
            ".text \n"
            "main: \n"
            "lw $t0, var1 \n"
            "li $t1, VALUE \n"
            "mult $t0, $t1 # 2 * 4 = 8 \n"
            "mflo $t8 \n"
            "mfhi $t9 \n"
            "lw $t0, var2 \n"
            "li $t1, VALUE \n"
            "mult $t0, $t1 # 1073741824 * 4 = 4294967296 (overflow) \n"
            "mflo $t8 \n"
            "mfhi $t9 \n";

        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
        virtualMachine environment;
        environment.setMaps(mipsParser);
        REQUIRE(environment.userInputFunction("run") == true);
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        REQUIRE(environment.userInputFunction("break") == true);
        REQUIRE(environment.registersMap.find("$pc")->second == 10);
        REQUIRE(environment.registersMap.find("$hi")->second == 1);
        REQUIRE(environment.registersMap.find("$8")->second == 1073741824);
        REQUIRE(environment.registersMap.find("$9")->second == 4);
        REQUIRE(environment.registersMap.find("$25")->second == 1);

    }
}
