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


TEST_CASE("Test Text Grammar: PASS add 	$t2, $t0, $t1 ", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: add 	$t2, $t0, $t1" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "add 	$t2, $t0, $t1 \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: FAIL add 	$t2, $t0,  \n", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: FAIL add 	$t2, $t0,  \n" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "add 	$t2, $t0, \n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        //parseObject.printParseDetails();
        REQUIRE(parseObject.parseTextTest(iss) == false);
      
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: add 	$t2, $t0, 2 ", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: add 	$t2, $t0, 2" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "add 	$t2, $t0, 2 \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: mul 	$t2, $t0, $t1 ", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: mul 	$t2, $t0, $t1" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "mul 	$t2, $t0, $t1 \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: mulo 	$t2, $t0, $t1 ", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: mulo $t2, $t0, $t1" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "mulo 	$t2, $t0, $t1 \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: rem 	$t2, $t0, $t1", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: rem 	$t2, $t0, $t1" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "rem 	$t2, $t0, $t1 \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: abs	$t0, $t1", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: abs	$t0, $t1" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "abs	$t0, $t1 \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: sw $1, $0", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: sw $1, $0" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "sw $1, $0 \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: sw $s1, $zero", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: sw $s1, $zero" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "sw $s1, $zero \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: lb $t1, ($t0)", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: lb $t1, ($t0)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "lb $t1, ($t0) \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: lb $t2, 1($t0)", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: lb $t2, 1($t0)" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "lb $t2, 1($t0) \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: mult $t1, $t2", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: mult $t1, $t2" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "mult $t1, $t2 \n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: not $t3, $t2", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: not $t3, $t2" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "not $t3, $t2\n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: not $t3, 1", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: not $t3, 1" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "not $t3, 1\n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: mflo $t1", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: mflo $t1" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "mflo $t1\n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: li $t1, 1", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: li $t1, 1" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "mflo $t1\n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: searchInputList", "[data Grammar]") {

    {
        std::vector <std::string> registerList = {
        "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2","$a3",
        "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
        "$s0","$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
        "$t8", "$t9", "$k0","$k1", "$gp", "$sp", "$fp", "$ra",
        "$0", "$1", "$2","$3", "$4", "$5", "$6", "$7", "$8", "$9",
        "$10", "$11", "$12","$13", "$14", "$15", "$16", "$17", "$18", "$19",
        "$20", "$21", "$22","$23", "$24", "$25", "$26", "$27", "$28", "$29", "$30", "$31",
        };
        std::cout << "Test Text Grammar: searchInputList" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        REQUIRE(searchInputList(registerList, "$t3") == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: label: nop ", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: label: nop" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "label: nop\n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: PASS add 	$t2, $t0, $t1 #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: add 	$t2, $t0, $t1 #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "add 	$t2, $t0, $t1 #comment \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: add 	$t2, $t0, 2  #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: add 	$t2, $t0, 2 #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "add 	$t2, $t0, 2 #comment \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: mul 	$t2, $t0, $t1 #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: mul 	$t2, $t0, $t1 #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "mul 	$t2, $t0, $t1 #comment \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: mulo 	$t2, $t0, $t1 #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: mulo $t2, $t0, $t1 #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "mulo 	$t2, $t0, $t1 #comment \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: rem 	$t2, $t0, $t1 #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: rem 	$t2, $t0, $t1 #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "rem 	$t2, $t0, $t1 #comment \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: abs	$t0, $t1 #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: abs	$t0, $t1 #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "abs	$t0, $t1 #comment \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: sw $1, $0 #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: sw $1, $0 #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "sw $1, $0 #comment \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: sw $s1, $zero #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: sw $s1, $zero #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "sw $s1, $zero #comment \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: lb $t1, ($t0) #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: lb $t1, ($t0) #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "lb $t1, ($t0) #comment \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: lb $t2, 1($t0) #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: lb $t2, 1($t0) #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "lb $t2, 1($t0) #comment \n";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: mult $t1, $t2 #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: mult $t1, $t2 #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "mult $t1, $t2 #comment \n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: not $t3, $t2 #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: not $t3, $t2 #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "not $t3, $t2 #comment\n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: not $t3, 1 #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: not $t3, 1 #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "not $t3, 1 #comment \n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: mflo $t1 #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: mflo $t1 #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "mflo $t1  #comment\n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}
TEST_CASE("Test Text Grammar: li $t1, 1 #comment", "[data Grammar]") {

    {
        std::cout << "Test Text Grammar: li $t1, 1 #comment" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        std::string inputList = "mflo $t1 #comment \n ";
        std::istringstream iss(inputList);
        Parser parseObject;
        REQUIRE(parseObject.parseTextTest(iss) == true);
        std::cout << std::endl;
    }
}