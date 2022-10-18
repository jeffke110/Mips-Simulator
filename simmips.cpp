// implement entry point for simmips here
#include "lexer.hpp"
#include "parser.hpp"
#include "textGrammar.hpp"
#include "dataGrammar.hpp"
#include "virtualMachine.hpp"
#include "virtual_machine_gui.hpp"

#include <QApplication>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void textUserInterface(char* argv[]) {
    std::ifstream fileArgument;
    std::string argument_string(argv[1]);
    fileArgument.open(argv[1]);
    if (!fileArgument.is_open()) {
        std::cerr << "Error:0: no file exists " << std::endl;
        exit(EXIT_FAILURE);
    }
    Parser mipsParser;
    if (mipsParser.parse(fileArgument)) {
        virtualMachine environment;
        environment.setMaps(mipsParser);
        //environment.printParseDetails();
        if (environment.checkMainLabel()) {
            std::string inputInterface;
            while (inputInterface != "quit") {
                std::cout << "simmips> ";
                std::getline(std::cin, inputInterface);
                while (environment.userInputFunction(inputInterface) && inputInterface != "quit") {
                    std::cout << "simmips> ";
                    std::getline(std::cin, inputInterface);
                }
                if (inputInterface == "quit") {
                }
                else {
                    if (unsigned(environment.pcRegister->second) >= environment.instructionList.size()) {
                        environment.printCounter();
                    }
                    else {
                        environment.executeInstruction(environment.instructionList.at(environment.pcRegister->second));
                        environment.printCounter();
                    }
                }
            }
            exit(EXIT_SUCCESS);
        }
        else {
            std::cerr << "Error:0: no main in text file" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else {
        exit(EXIT_FAILURE);
    }
}
int main(int argc,char *argv[])
{

    if (argv[1] && !argv[2] && argc > 1) {
        textUserInterface(argv);
    }
    else if (argv[1] && argv[2] && argc > 1) {
        std::ifstream fileArgument;
        std::string argumentOne(argv[1]);
        std::string argumentTwo(argv[2]);
        QApplication app(argc, argv);
        VirtualMachineGUI gui;
        if (argumentOne == "--gui") {
            gui.load(argv[2]);
        }
        else if (argumentTwo == "--gui") {
            gui.load(argv[1]);
        }
        else {
            std::cerr << "Error:0: no --gui parameter" << std::endl;
            exit(EXIT_FAILURE);
        }
        gui.show();
        return app.exec();

    }
    else {
        std::cerr << "Error:0: Too many arguments" << std::endl;
        exit(EXIT_FAILURE);
    }


    return 0;
}

