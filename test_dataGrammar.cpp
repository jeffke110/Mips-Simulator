#include "catch.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include "dataGrammar.hpp"
#include "textGrammar.hpp"
#include "parser.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <map>


TEST_CASE("Test Data Grammar: var1:	.word 1024 ", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: var1:	.word 1024 " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var1:	.word 1024 ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss)== true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: var2:	.half 12 ", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: var2:	.half 12   " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var2:	.half 12  \n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: var3:	.byte 0", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: var3:	.byte 0  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var3:	.byte 0 \n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: var4:	.byte 1, 2, 3, 4, 5", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: var4:	.byte 1, 2, 3, 4, 5 " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var4:	.byte 1, 2, 3, 4, 5 \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: var5:	.space 512    ", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: var5:	.space 512    " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var5:	.space 512   \n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: var6:	.ascii \"hello \" ", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: var6:	.ascii \"hello \"" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var6:	.ascii \"hello \"  \n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: var7:	.asciiz \"goodbye\" ", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: var7:	.asciiz \"goodbye\" " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var7:	.asciiz \"goodbye\"  \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: \n x: .word 1 \n y: .word 2 \n", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: \n x: .word 1 \n y: .word 2 \n " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "x: .word 1 \n y: .word 2 \n  ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: \n TRUE = 1 \n FALSE = 0 \n test1: .word TRUE \n test2: .word FALSE\n", "[data Grammar]") {
    {
        std::cout << "Test Data Grammar: \n TRUE = 1 \n FALSE = 0 \n test1: .word TRUE \n test2: .word FALSE\n " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "TRUE = 1 \n FALSE = 0 \n test1: .word TRUE \n test2: .word FALSE\n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: var1:	.word 1024 #comment ", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: var1:	.word 1024 #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var1:	.word 1024 #comment \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: var2:	.half 12 #comment", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: var2:	.half 12 #comment  " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var2:	.half 12 #comment \n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: var3:	.byte 0 #comment", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: var3:	.byte 0  #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var3:	.byte 0 #comment \n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: var4:	.byte 1, 2, 3, 4, 5 #comment", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: var4:	.byte 1, 2, 3, 4, 5 #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var4:	.byte 1, 2, 3, 4, 5 #comment \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: var5:	.space 512  #comment  ", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: var5:	.space 512   #comment " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var5:	.space 512  #comment \n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: var6:	.ascii \"hello \" #comment ", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: var6:	.ascii \"hello \"#comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var6:	.ascii \"hello \" #comment  \n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: var7:	.asciiz \"goodbye\" #comment ", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: var7:	.asciiz \"goodbye\" #comment " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var7:	.asciiz \"goodbye\" #comment\n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: \n x: .word 1 \n y: .word 2 #comment \n", "[data Grammar]") {

    {
        std::cout << "Test Data Grammar: \n x: .word 1 \n y: .word 2 #comment \n " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "x: .word 1 \n y: .word 2 #comment \n  ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: \n TRUE = 1 #comment \n FALSE = 0 \n test1: .word TRUE \n test2: .word FALSE #comment\n", "[data Grammar]") {
    {
        std::cout << "Test Data Grammar: \n TRUE = 1 #comment \n FALSE = 0 \n test1: .word TRUE \n test2: .word FALSE #comment\n " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "TRUE = 1 #comment \n FALSE = 0 \n test1: .word TRUE \n test2: .word FALSE #comment\n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: \n TRUE = 1 #comment \n FALSE = 0 \n test1: .half TRUE \n test2: .half FALSE #comment\n", "[data Grammar]") {
    {
        std::cout << "Test Data Grammar: \n TRUE = 1 #comment \n FALSE = 0 \n test1: .half TRUE \n test2: .half FALSE #comment\n " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "TRUE = 1 #comment \n FALSE = 0 \n test1: .half TRUE \n test2: .half FALSE #comment\n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: \n TRUE = 1 #comment \n FALSE = 0 \n test1: .byte TRUE \n test2: .byte FALSE #comment\n", "[data Grammar]") {
    {
        std::cout << "Test Data Grammar: \n TRUE = 1 #comment \n FALSE = 0 \n test1: .byte TRUE \n test2: .byte FALSE #comment\n " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "TRUE = 1 #comment \n FALSE = 0 \n test1: .byte TRUE \n test2: .byte FALSE #comment\n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: TRUE = 1 \n TRUE = 2 \n", "[data Grammar]") {
    {
        std::cout << "Test Data Grammar: TRUE = 1 \n TRUE = 2 \n " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "TRUE = 1 \n TRUE = 2 \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Data Grammar: var3:  \n var3: \n", "[data Grammar]") {
    {
        std::cout << "Test Data Grammar: var3:  \n var3:  \n " << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "var3: \n var3: \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseDataTest(iss) == false);
        std::cout << std::endl;
    }
}