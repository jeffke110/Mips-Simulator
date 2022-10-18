#include "catch.hpp"
#include "lexer.hpp"
#include "dataGrammar.hpp"
#include "textGrammar.hpp"
#include "parser.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>


TEST_CASE("Parse Text Grammar Test Case (RsRsS): add $t0, $t1, $t2", "[parse]") {

    {
        std::cout << std::endl;
        std::cout << "Parser.cpp file" << std::endl;
        std::cout << std::endl;
        
        std::cout << "Parse Text Grammar Test Case (RsRsS): add $t0, $t1, $t2" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "add $t0, $t1, $t2 \n ";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);
        REQUIRE(parseObject.instructionList.empty() == false);
        REQUIRE(parseObject.instructionList.size() == 1);

        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;
        
        REQUIRE(firstInstruction.lineNumber == 1);
        REQUIRE(firstInstruction.type == RsRsS);
        REQUIRE(firstInstruction.name == "add");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "$9");
        REQUIRE(arguments.at(1).getType() == Register);
        REQUIRE(arguments.at(2).getValue() == "$10");
        REQUIRE(arguments.at(2).getType() == Register);
        
        std::cout << std::endl;
    }
}
TEST_CASE("Parse Text Grammar Test Case (RsRsS): add $t0, $t1, 12", "[parse]") {

    {

        std::cout << "Parse Text Grammar Test Case (RsRsS):  add $t0, $t1, 12" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "add $t0, $t1, 12 \n ";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);
        REQUIRE(parseObject.instructionList.empty() == false);
        REQUIRE(parseObject.instructionList.size() == 1);

        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;

        REQUIRE(firstInstruction.lineNumber == 1);
        REQUIRE(firstInstruction.type == RsRsS);
        REQUIRE(firstInstruction.name == "add");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "$9");
        REQUIRE(arguments.at(1).getType() == Register);
        REQUIRE(arguments.at(2).getValue() == "12");
        REQUIRE(arguments.at(2).getType() == integerImmediate);

        std::cout << std::endl;
    }
}
TEST_CASE("Parse Text Grammar Test Case (RsR): mult $t2, $t0", "[parse]") {

    {

        std::cout << "Parse Text Grammar Test Case (RsR): mult $t2, $t0" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "add $t0, $t1, 12 \n mult 	$t0, $t1 \n";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);
        REQUIRE(parseObject.instructionList.empty() == false);
        REQUIRE(parseObject.instructionList.size() == 2);

        instruction secondInstruction = parseObject.instructionList.at(1);
        std::vector<argument> arguments = secondInstruction.instructionArguments;

        REQUIRE(secondInstruction.lineNumber == 2);
        REQUIRE(secondInstruction.type == RsR);
        REQUIRE(secondInstruction.name == "mult");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "$9");
        REQUIRE(arguments.at(1).getType() == Register);

        std::cout << std::endl;
    }
}
TEST_CASE("Parse Text Grammar Test Case (RsS): not $t2, source", "[parse]") {

    {

        std::cout << "Parse Text Grammar Test Case (RsS): not $t2, source" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "add $t0, $t1, 12 \n mult $t0, $t1 \n not $t0, $t1 \n not $t0, 13 \n";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);
        REQUIRE(parseObject.instructionList.empty() == false);
        REQUIRE(parseObject.instructionList.size() == 4);

        instruction thirdInstruction = parseObject.instructionList.at(2);
        std::vector<argument> arguments = thirdInstruction.instructionArguments;

        REQUIRE(thirdInstruction.lineNumber == 3);
        REQUIRE(thirdInstruction.type == RsS);
        REQUIRE(thirdInstruction.name == "not");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "$9");
        REQUIRE(arguments.at(1).getType() == Register);


        instruction fourthInstruction = parseObject.instructionList.at(3);
        std::vector<argument> argument1 = fourthInstruction.instructionArguments;

        REQUIRE(fourthInstruction.lineNumber == 4);
        REQUIRE(fourthInstruction.type == RsS);
        REQUIRE(fourthInstruction.name == "not");
        REQUIRE(argument1.at(0).getValue() == "$8");
        REQUIRE(argument1.at(0).getType() == Register);
        REQUIRE(argument1.at(1).getValue() == "13");
        REQUIRE(argument1.at(1).getType() == integerImmediate);


        std::cout << std::endl;
    }
}
TEST_CASE("Parse Text Grammar Test Case (RsI):  li $t0, immediate", "[parse]") {

    {

        std::cout << "Parse Text Grammar Test Case (RsI):  li $t0, 13" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "li $t0, 13 \n ";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);
        REQUIRE(parseObject.instructionList.empty() == false);
        REQUIRE(parseObject.instructionList.size() == 1);

        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;

        REQUIRE(firstInstruction.lineNumber == 1);
        REQUIRE(firstInstruction.type == RsI);
        REQUIRE(firstInstruction.name == "li");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "13");
        REQUIRE(arguments.at(1).getType() == integerImmediate);
        std::cout << std::endl;
    }
}
TEST_CASE("Parse Text Grammar Test Case (R):  mfhi $t1", "[parse]") {

    {

        std::cout << "Parse Text Grammar Test Case (R):  mfhi $t1" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "mfhi $t1 \n ";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);
        REQUIRE(parseObject.instructionList.empty() == false);
        REQUIRE(parseObject.instructionList.size() == 1);

        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;

        REQUIRE(firstInstruction.lineNumber == 1);
        REQUIRE(firstInstruction.type == R);
        REQUIRE(firstInstruction.name == "mfhi");
        REQUIRE(arguments.at(0).getValue() == "$9");
        REQUIRE(arguments.at(0).getType() == Register);

        std::cout << std::endl;
    }
}
TEST_CASE("Parse Text Grammar Test Case (RsSsL):  beq $t0, $t1, Label", "[parse]") {

    {
        //'beq' <register> SEP <source> SEP <label>
        std::cout << "Parse Text Grammar Test Case (RsSsL):  beq $t0, $t1, Label" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "label: \n beq $t0, $t1, label \n ";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);
        REQUIRE(parseObject.labelsMap.empty() == false);
        REQUIRE(parseObject.labelsMap.size() == 1);
        REQUIRE(parseObject.labelsMap.find("label")->second.isTextLabel == true);
        REQUIRE(parseObject.labelsMap.find("label")->first == "label");
        REQUIRE(parseObject.instructionList.empty() == false);
        REQUIRE(parseObject.instructionList.size() == 1);

        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;

        REQUIRE(firstInstruction.lineNumber == 2);
        REQUIRE(firstInstruction.type == RsSsL);
        REQUIRE(firstInstruction.name == "beq");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "$9");
        REQUIRE(arguments.at(1).getType() == Register);
        REQUIRE(arguments.at(2).getValue() == "label");
        REQUIRE(arguments.at(2).getType() == Label);

        std::cout << std::endl;
    }
}
TEST_CASE("Parse Text Grammar Test Case (RsM):  lw ", "[parse]") {

    {

        std::cout << "Parse Text Grammar Test Case (RsM):  lw " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "label: \n lw $t0, $t1 \n lw $t0, label \n lw $t0, 3($t0)  \n";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);
        REQUIRE(parseObject.labelsMap.empty() == false);
        REQUIRE(parseObject.labelsMap.size() == 1);
        REQUIRE(parseObject.labelsMap.find("label")->second.isTextLabel == true);
        REQUIRE(parseObject.labelsMap.find("label")->first == "label");

        REQUIRE(parseObject.instructionList.empty() == false);
        REQUIRE(parseObject.instructionList.size() == 3);

        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;

        REQUIRE(firstInstruction.lineNumber == 2);
        REQUIRE(firstInstruction.type == RsM);
        REQUIRE(firstInstruction.name == "lw");
        REQUIRE(arguments.at(0).getValue() == "$8");
        REQUIRE(arguments.at(0).getType() == Register);
        REQUIRE(arguments.at(1).getValue() == "$9");
        REQUIRE(arguments.at(1).getType() == Register);

        instruction secondInstruction = parseObject.instructionList.at(1);
        std::vector<argument> argumentsOne = secondInstruction.instructionArguments;

        REQUIRE(secondInstruction.lineNumber == 3);
        REQUIRE(secondInstruction.type == RsM);
        REQUIRE(secondInstruction.name == "lw");
        REQUIRE(argumentsOne.at(0).getValue() == "$8");
        REQUIRE(argumentsOne.at(0).getType() == Register);
        REQUIRE(argumentsOne.at(1).getValue() == "label");
        REQUIRE(argumentsOne.at(1).getType() == Label);


        instruction thirdInstruction = parseObject.instructionList.at(2);
        std::vector<argument> argumentsTwo = thirdInstruction.instructionArguments;

        REQUIRE(thirdInstruction.lineNumber == 4);
        REQUIRE(thirdInstruction.type == RsM);
        REQUIRE(thirdInstruction.name == "lw");
        REQUIRE(argumentsTwo.at(0).getValue() == "$8");
        REQUIRE(argumentsTwo.at(0).getType() == Register);
        REQUIRE(argumentsTwo.at(1).getValue() == "$8");
        REQUIRE(argumentsTwo.at(1).getType() == Register);
        REQUIRE(argumentsTwo.at(2).getValue() == "3");
        REQUIRE(argumentsTwo.at(2).getType() == Offset);

        std::cout << std::endl;
    }
}
TEST_CASE("Parse Text Grammar Test Case (Jump):  j", "[parse]") {

    {

        std::cout << "Parse Text Grammar Test Case (Jump):  j" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = "label: \n j label \n ";
        std::istringstream iss(input);
        Parser parseObject;
        parseObject.parseTextTest(iss);
        REQUIRE(parseObject.instructionList.empty() == false);
        REQUIRE(parseObject.instructionList.size() == 1);

        instruction firstInstruction = parseObject.instructionList.at(0);
        std::vector<argument> arguments = firstInstruction.instructionArguments;

        REQUIRE(firstInstruction.lineNumber == 2);
        REQUIRE(firstInstruction.type == Jump);
        REQUIRE(firstInstruction.name == "j");
        REQUIRE(arguments.at(0).getValue() == "label");
        REQUIRE(arguments.at(0).getType() == Label);

        std::cout << std::endl;
    }
}
TEST_CASE("Parse Function Test Case : PASS test00", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS test00.asm" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "       var1: .word 1024             # int var1 = 1024 \n"
            "       var2: .half 12               # short var2 = 12 \n"
            "        var3: .byte 0                # char var3 = 0 \n"
            "      var4: .byte 1, 2, 3, 4, 5, 6, 7, 8  # var4 = { 1,2,3,4,5,6,7,8 } \n"
            " var5: .space 512             # reserve 512 bytes \n "
            "    var6: .ascii \"hello\" \n"
            "   var7: .asciiz \"goodbye\" \n"
            "  .text \n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS test01", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS test01.asm" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n "
            "LENGTH = 1024 \n"
            "arr: .space LENGTH \n"
            ".text \n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS test02", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS test02.asm" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            " avar: .word 	0 \n"
            " bvar: .half	1 \n"
            " cvar: .byte	3 \n"
            " .text \n"
            " main: \n"
            " li $t0, 45 \n"
            " lw $t1, avar \n"
            " lh $t2, bvar \n"
            " lb $t2, cvar \n"
            " sw $t1, avar \n"
            " sh $t2, bvar \n"
            " sb $t2, cvar \n"
            " move $t0, $0 \n";

        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS test03", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS test03.asm" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "x: .word	1 \n"
            "y: .word	1 \n"
            "z: .space 	4 \n"
            ".text \n"
            "main: \n"
            "lw 	$t0, x \n"
            "lw 	$t1, y \n"
            "add 	$t2, $t0, $t1 \n"
            "add 	$t2, $t0, 2 \n"
            "addu 	$t2, $t0, $t1 \n"
            "addu 	$t2, $t0, 2 \n"
            "sub 	$t2, $t0, $t1 \n"
            "sub 	$t2, $t0, 2 \n"
            "subu 	$t2, $t0, $t1 \n"
            "subu 	$t2, $t0, 2 \n"
            "mul 	$t2, $t0, $t1 \n"
            "mul 	$t2, $t0, 2 \n"
            "mulo 	$t2, $t0, $t1 \n"
            "mulo 	$t2, $t0, 2 \n"
            "mulou 	$t2, $t0, $t1 \n"
            "mulou 	$t2, $t0, 2 \n"
            "mult	$t0, $t1 \n"
            "multu	$t0, $t1 \n"
            "div 	$t2, $t0, $t1 \n"
            "div 	$t2, $t0, 2 \n"
            "divu 	$t2, $t0, $t1 \n"
            "divu 	$t2, $t0, 2 \n"
            "div	$t0, $t1 \n"
            "divu	$t0, $t1 \n"
            "rem 	$t2, $t0, $t1 \n"
            "rem 	$t2, $t0, 2 \n"
            "remu 	$t2, $t0, $t1 \n"
            "remu 	$t2, $t0, 2 \n"
            "abs	$t0, $t1 \n"
            "neg	$t0, $t1 \n"
            "negu	$t0, $t1 \n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS test04", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS test04.asm" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "TRUE = 1 \n"
            "FALSE = 0 \n"
            "test1: .word TRUE \n"
            "test2: .word FALSE \n"
            ".text \n"
            "main: \n"
            "lw	$t0, test1 \n"
            "lw	$t1, test2 \n"
            "and $t2, $t0, $t1 \n"
            "and $t2, $t0, TRUE \n"
            "nor	$t2, $t0, $t1 \n"
            "nor	$t2, $t0, TRUE \n"
            "not $t2, $t0 \n"
            "not $t2, $t0 \n"
            "or $t2, $t0, $t1 \n"
            "or $t2, $t0, TRUE \n"
            "xor $t2, $t0, $t1 \n"
            "xor $t2, $t0, TRUE \n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS test05", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS test05.asm" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "x: .word 1 \n"
            "y: .word 2 \n"
            ".text \n"
            "main: \n"
            "lw $t0, x \n"
            "lw $t1, y \n"
            "beq $t0, $t0, next1 \n"
            "next1: \n"
            "bne $t0, $t1, next2 \n"
            "next2: \n"
            "blt $t0, $t1, next3 \n"
            "next3: \n"
            "ble $t0, $t0, next4 \n"
            "next4: \n"
            "bgt $t1, $t0, next5 \n"
            "next5: \n"
            "bge $t0, $t0, next6 \n"
            "next6: \n"
            "end: \n"
            "j	end \n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS test06", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS test06.asm" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "n: .word 10 \n"
            "sumOfSquares: .word 0 \n"
            ".text \n"
            "main: \n"
            "lw $t0, n \n"
            "li $t1, 1 \n"
            "li $t2, 0 \n"
            "sumLoop: \n"
            "mul $t3, $t1, $t1 \n"
            "add $t2, $t2, $t3 \n"
            "add $t1, $t1, 1 \n"
            "ble $t1, $t0, sumLoop \n"
            "sw  $t2, sumOfSquares \n"
            "end: \n"
            "j end \n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS test07", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS test07" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            ".text \n"
            "main: \n"
            "sw $1, $0 \n"
            "sw $at, $zero \n"
            "sw $2, $0 \n"
            "sw $v0, $zero \n"
            "sw $3, $0 \n"
            "sw $v1, $zero \n"
            "sw $4, $0 \n"
            "sw $a0, $zero \n"
            "sw $5, $0 \n"
            "sw $a1, $zero \n"
            "sw $6, $0 \n"
            "sw $a2, $zero \n"
            "sw $7, $0 \n"
            "sw $a3, $zero \n"
            "sw $8, $0 \n"
            "sw $t0, $zero \n"
            "sw $9, $0 \n"
            "sw $t1, $zero \n"
            "sw $10, $0 \n"
            "sw $t2, $zero \n"
            "sw $11, $0 \n"
            "sw $t3, $zero \n"
            "sw $12, $0 \n"
            "sw $t4, $zero \n"
            "sw $13, $0 \n"
            "sw $t5, $zero \n"
            "sw $14, $0 \n"
            "sw $t6, $zero \n"
            "sw $15, $0 \n"
            "sw $t7, $zero \n"
            "sw $16, $0 \n"
            "sw $s0, $zero \n"
            "sw $17, $0 \n"
            "sw $s1, $zero \n"
            "sw $18, $0 \n"
            "sw $s2, $zero \n"
            "sw $19, $0 \n"
            "sw $s3, $zero \n"
            "sw $20, $0 \n"
            "sw $s4, $zero \n"
            "sw $21, $0 \n"
            "sw $s5, $zero \n"
            "sw $22, $0 \n"
            "sw $s6, $zero \n"
            "sw $23, $0 \n"
            "sw $s7, $zero \n"
            "sw $24, $0 \n"
            "sw $t8, $zero \n"
            "sw $25, $0 \n"
            "sw $t9, $zero \n"
            "sw $26, $0 \n"
            "sw $k0, $zero \n"
            "sw $27, $0 \n"
            "sw $k1, $zero \n"
            "sw $28, $0 \n"
            "sw $gp, $zero \n"
            "sw $29, $0 \n"
            "sw $sp, $zero \n"
            "sw $30, $0 \n"
            "sw $fp, $zero \n"
            "sw $31, $0 \n"
            "sw $ra, $zero \n"
            "end: \n"
            "j end \n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
        mipsParser.printParseDetails();
    }
}
TEST_CASE("Parse Function Test Case : PASS test08", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS test08" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "str: .ascii	\"hello\" \n"
            ".text\n"
            "main:\n"
            "lb $t8, str\n"
            "la $t0, str\n"
            "lb $t1, ($t0)\n"
            "lb $t2, 1($t0)\n"
            "lb $t3, 2($t0)\n"
            "lb $t4, 3($t0)\n"
            "lb $t5, 4($t0)\n"
            "end:	nop\n"
            "j end\n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : FAIL test00", "[parse]") {

    {
        std::cout << "Parse Function Test Case : FAIL test00" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "n: .word 10 \n"
            "sumOfSquares: .word 0 \n"
            ".text \n"
            "main: \n"
            "lw $t0, n \n"
            "li $t1, 1 \n"
            "li $t2, 0 \n"
            "sumLoop: \n"
            "mul $t3, $t1, $t1, 20 \n"
            "add $t2, $t2, $t3 \n"
            "add $t1, $t1, 1 \n"
            "ble $t1, $t0, sumLoop \n"
            "sw  $t2, sumOfSquares \n"
            "end: \n"
            "j end \n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == false);
    }
}
TEST_CASE("Parse Function Test Case : FAIL test01", "[parse]") {

    {
        std::cout << "Parse Function Test Case : FAIL test01" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "n: .word 10 \n"
            "++++: .word 0 \n"
            ".text \n"
            "main: \n"
            "lw $t0, n \n"
            "li $t1, 1 \n"
            "li $t2, 0 \n"
            "sumLoop: \n"
            "mul $t3, $t1, $t1 \n"
            "add $t2, $t2, $t3 \n"
            "add $t1, $t1, 1 \n"
            "ble $t1, $t0, sumLoop \n"
            "sw  $t2, sumOfSquares \n"
            "end: \n"
            "j end \n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == false);
    }
}
TEST_CASE("Parse Function Test Case : FAIL test02", "[parse]") {

    {
        std::cout << "Parse Function Test Case : FAIL test02" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "TRUE = 1 \n"
            "FALSE = 0 \n"
            "test1: .word TRUE \n"
            "test2: .word FALSE \n"
            ".text \n"
            "main: \n"
            "lw	$t0, test1 \n"
            "lw	$t1, test2 \n"
            "and $t2, $t0, $t1 \n"
            "and $t2, $t0, TRUE, TRUE \n"
            "nor	$t2, $t0, $t1 \n"
            "nor	$t2, $t0, TRUE \n"
            "not $t2, $t0 \n"
            "not $t2, $t0 \n"
            "or $t2, $t0, $t1 \n"
            "or $t2, $t0, TRUE \n"
            "xor $t2, $t0, $t1 \n"
            "xor $t2, $t0, TRUE \n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == false);
    }
}
TEST_CASE("Parse Function Test Case : FAIL test03", "[parse]") {

    {
        std::cout << "Parse Function Test Case : FAIL test03" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "TRUE = 1 \n"
            "FALSE = 0 boooooo\n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == false);
    }
}
TEST_CASE("Parse Function Test Case : FAIL test04", "[parse]") {

    {
        std::cout << "Parse Function Test Case : FAIL test04" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "n: .word 10 \n"
            "sumOfSquares: .word 0 \n"
            ".text \n"
            "main: \n"
            "lw $t0, n \n"
            "li $t1, 1 \n"
            "li $t2, 0 \n"
            "sumLoop: \n"
            "mul $t3, $t1, $t1 \n"
            "add $t2, $t2, $t3 \n"
            "add $t1, $t1, 1 \n"
            "ble $t1, $t0, sumLoop AHHHHH\n"
            "sw  $t2, sumOfSquares \n"
            "end: \n"
            "j end \n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == false);
    }
}
TEST_CASE("Parse Function Test Case : FAIL test05", "[parse]") {

    {
        std::cout << "Parse Function Test Case : FAIL test05" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "n: .word 10 \n"
            "sumOfSquares: .word 0 \n"
            ".text \n"
            "main: \n"
            "lw $t0, n \n"
            "li $t1, 1 what \n"
            "li $t2, 0 \n"
            "sumLoop: \n"
            "mul $t3, $t1, $t1 \n"
            "add $t2, $t2, $t3 \n"
            "add $t1, $t1, 1 \n"
            "ble $t1, $t0, sumLoop\n"
            "sw  $t2, sumOfSquares \n"
            "end: \n"
            "j end \n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == false);
    }
}
TEST_CASE("Parse Function Test Case : PASS vm00", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS vm00" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            ".text \n"
            "main: j main \n";

        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS vm01", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS vm01" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
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


        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS vm02", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS vm02" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "r1: .space 4 \n"
            "r2: .space 12 \n"
            "r3: .space 4 \n"
            "var: .word 7 \n"
            ".text \n"
            "main: \n"
            "la $t0, r2 \n"
            "lw $t1, var  \n"
            "sw $t1, 0 \n"
            "sw $t1, $t0 \n"
            "sw $t1, 4($t0) \n"
            "sw $t1, 8(r2) \n"
            "sw $t1, r3 \n";

        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS vm03", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS vm03" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "A = 0 \n"
            "B = 1 \n"
            "C = 2 \n"
            "D = 4 \n"
            ".text \n"
            "main: \n"
            "li $t0, 100 \n"
            "li $t1, A \n"
            "li $t2, B \n"
            "li $t3, C \n"
            "li $t4, D \n";

        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS vm04", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS vm04" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "VALUE = -1234 \n"
            ".text \n"
            "main: \n"
            "li $t0, VALUE \n"
            "move $t1, $t0 \n"
            "move $t2, $t1 \n"
            "move $t3, $t2 \n"
            "move $t4, $t3 \n"
            "move $t5, $t4 \n"
            "move $t6, $t5 \n"
            "move $t7, $t6 \n";
        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS vm05", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS vm05" << std::endl;
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
    }
}
TEST_CASE("Parse Function Test Case : PASS vm06", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS vm06" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "VALUE = 12 \n"
            "var: .word 31 \n"
            ".text \n"
            "main: \n"
            "lw $t0, var \n"
            "addu $t1, $t0, VALUE # 31 + 12 = 43 \n"
            "addu $t2, $t1, $t0 # 43 + 31 = 74 \n";

        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS vm07", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS vm07" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "VALUE = 2 \n"
            "var1: .word 1 \n"
            "var2: .word 12 \n"
            "var3: .word -1 \n"
            ".text \n"
            "main: \n"
            "lw $t0, var1 \n"
            "lw $t1, var2 \n"
            "lw $t2, var3 \n"
            "sub $t3, $t0, VALUE # 1 - 2 = -1 \n"
            "sub $t4, $t1, $t0 # 12 - 1 = 11 \n"
            "sub $t5, $t2, VALUE #  - 1 - 2 = -3 \n";

        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS vm08", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS vm08" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "VALUE = 2 \n"
            "var1: .word 1 \n"
            "var2: .word 12 \n"
            "var3: .word -1 \n"
            ".text \n"
            "main: \n"
            "lw $t0, var1 \n"
            "lw $t1, var2 \n"
            "lw $t2, var3 \n"
            "subu $t3, $t0, VALUE # 1 - 2 = -1 = 4294967295 \n"
            "subu $t4, $t1, $t0 # 12 - 1 = 11 \n"
            "subu $t5, $t2, VALUE #  - 1 - 2 = -3 = 4294967293 \n";

        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS vm09", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS vm09" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string input = ".data \n"
            "VALUE = 4 \n"
            "VALUE2 = -4 \n"
            "var1: .word 2 \n"
            "var2: .word -2 \n"
            "var3: .word 1073741824 #  = 2 ^ 30 \n"
            ".text \n"
            "main: \n"
            "lw $t0, var1 \n"
            "li $t1, VALUE \n"
            "mult $t0, $t1 # 2 * 4 = 8 \n"
            "mflo $t8 \n"
            "mfhi $t9 \n"
            "lw $t0, var2 \n"
            "lw $t1, var1 \n"
            "mult $t0, $t1 #  - 2 * 2 = -4 \n"
            "mflo $t8 \n"
            "mfhi $t9 \n"
            "lw $t0, var3 \n"
            "li $t1, VALUE \n"
            "mult $t0, $t1 # 1073741824 * 4 = 4294967296 (overflow) \n"
            "mflo $t8 \n"
            "mfhi $t9 \n"
            "lw $t0, var3 \n"
            "li $t1, VALUE2 \n"
            "mult $t0, $t1 # 1073741824 * -4 = -4294967296 (overflow) \n"
            "mflo $t8 \n"
            "mfhi $t9 \n";

        std::istringstream iss(input);
        Parser mipsParser;
        REQUIRE(mipsParser.parse(iss) == true);
    }
}
TEST_CASE("Parse Function Test Case : PASS vm10", "[parse]") {

    {
        std::cout << "Parse Function Test Case : PASS vm10" << std::endl;
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
    }
}