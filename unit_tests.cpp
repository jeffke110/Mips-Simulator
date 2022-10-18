#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "lexer.hpp"
#include "dataGrammar.hpp"
#include "textGrammar.hpp"
#include "parser.hpp"

#include <string>
#include <sstream>
#include <map>


TEST_CASE("Quote test case", "[lexer]") {

    {
        std::string input = "\" (,=hello=,) \"";
        std::istringstream iss(input);

        TokenList tl = tokenize(iss);
        REQUIRE(tl.size() == 3);
    }
}
TEST_CASE("Parantheses test case: two", "[lexer]") {

    {
        //Assuming there is always going to be an endline
        std::string input = "(((\n";
        std::istringstream iss(input);

        TokenList tl = tokenize(iss);
        REQUIRE(tl.size() == 4);
        REQUIRE(tl.back() != Token(ERROR, 0));

        std::cout << "Parantheses test case: two" << std::endl;
        std::cout << "------------------------------------" << std::endl;
        for (auto const& i : tl) {
            std::cout << i << std::endl;
        }
        std::cout << std::endl;
    }
}
TEST_CASE("Parantheses test case: three", "[lexer]") {

    {
        //Assuming there is always going to be an endline
        //error token replaces \n (EOL) token
        std::string input = ")))\n";
        std::istringstream iss(input);

        TokenList tl = tokenize(iss);
        REQUIRE(tl.size() == 4);
        REQUIRE(tl.back() != Token(ERROR, 0));
    }
}
TEST_CASE("Parantheses test case: four", "[lexer]") {

    {
        //Assuming there is always going to be an endline
        //error token replaces \n (EOL) token
        std::string input = "))()\n";
        std::istringstream iss(input);

        TokenList tl = tokenize(iss);
        REQUIRE(tl.size() == 5);
        REQUIRE(tl.back() != Token(ERROR, 0));


    }
}
TEST_CASE("Parantheses test case: five", "[lexer]") {

    {
        //Assuming there is always going to be an endline
        //error token replaces \n (EOL) token
        std::string input = "Token(TokenType t, const std::string & v): type(t), value(v) {};\n";
        std::istringstream iss(input);

        TokenList tl = tokenize(iss);
        REQUIRE(tl.size() == 22);

    }
}
TEST_CASE("Comment Test case: six", "[lexer]") {

    {
        //Assuming there is always going to be an endline
        //error token replaces \n (EOL) token
        std::string input = "( ) # (comments)\n";
        std::istringstream iss(input);

      
        TokenList tl = tokenize(iss);



        REQUIRE(tl.size() == 5);
    }
}

