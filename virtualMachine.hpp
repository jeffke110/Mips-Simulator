#ifndef VIRTUALMACHINE_HPP
#define VIRTUALMACHINE_HPP

#include "lexer.hpp"
#include "token.hpp"
#include "dataGrammar.hpp"
#include "textGrammar.hpp"
#include "message_queue.hpp"
#include "parser.hpp"
#include <iostream>
#include <istream>
#include <bitset>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <limits>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <stdexcept>
#include <atomic>

class virtualMachine {

private:
    std::vector <std::string> registerList = {
        "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2","$a3",
        "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
        "$s0","$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
        "$t8", "$t9", "$k0","$k1", "$gp", "$sp", "$fp", "$ra",
        "$0", "$1", "$2","$3", "$4", "$5", "$6", "$7", "$8", "$9",
        "$10", "$11", "$12","$13", "$14", "$15", "$16", "$17", "$18", "$19",
        "$20", "$21", "$22","$23", "$24", "$25", "$26", "$27", "$28", "$29", "$30", "$31", "$hi", "$lo", "$pc",

    };
    const int32_t bit32Min = std::numeric_limits<int32_t>::min();
    const int32_t bit32Max = std::numeric_limits<int32_t>::max();
    
    void initializeRegisters(void);
    std::string convertRegister(std::string inputString);
     

    //Threading init
    volatile bool isGettingMessage = false;
    void runThreadProcess(void);
    message_queue<std::string> messageQueue;
    mutable std::mutex print_mutex;
    std::thread mipsThread;
    bool  threadRunning;
    
public:

    virtualMachine() : mipsThread()
    {
        initializeRegisters(); 
        
        pcRegister = registersMap.find("$pc");
        threadRunning = true;
        mipsThread = std::thread(&virtualMachine::runThreadProcess, this);
    }
    ~virtualMachine() {
       threadRunning = false;
       if(mipsThread.joinable()) mipsThread.join();
    }

    void checkJoinable(void);
    bool userInputFunction(std::string inputInterface);
    bool executeInstruction(instruction inputInstruction);
    bool checkMainLabel(void);
    void setMaps(Parser mipsParser);
    void incrementCounter(void);
    void printCounter(void);
    bool checkEndOfFile(void);

    bool lw_Instruction(instruction inputInstruction);
    bool la_Instruction(instruction inputInstruction);
    bool sw_Instruction(instruction inputInstruction);
    bool li_Instruction(instruction inputInstruction);
    bool move_Instruction(instruction inputInstruction);
    bool mfhi_Instruction(instruction inputInstruction);
    bool mflo_Instruction(instruction inputInstruction);

    bool add_Instruction(instruction inputInstruction);
    bool addu_Instruction(instruction inputInstruction);
    bool sub_Instruction(instruction inputInstruction);
    bool subu_Instruction(instruction inputInstruction);
    bool mult_Instruction(instruction inputInstruction);
    bool multu_Instruction(instruction inputInstruction);
    bool div_Instruction(instruction inputInstruction);
    bool divu_Instruction(instruction inputInstruction);
    
    bool and_Instruction(instruction inputInstruction);
    bool nor_Instruction(instruction inputInstruction);
    bool or_Instruction(instruction inputInstruction);
    bool xor_Instruction(instruction inputInstruction);
    bool not_Instruction(instruction inputInstruction);
    
    bool beq_Instruction(instruction inputInstruction);
    bool bne_Instruction(instruction inputInstruction);
    bool blt_Instruction(instruction inputInstruction);
    bool ble_Instruction(instruction inputInstruction);
    bool bgt_Instruction(instruction inputInstruction);
    bool bge_Instruction(instruction inputInstruction);
    bool j_Instruction(instruction inputInstruction);

    void printRegisterMap(void);
    void getRegisterMapSize(void);
    void printParseDetails(void);
    std::string errorMessage;
    std::unordered_map<std::string, int32_t>::iterator pcRegister;
    std::unordered_map<std::string, int32_t> registersMap;
    std::unordered_map<std::string, labelType> labelsMap;
    std::unordered_map<std::string, std::string> constantsMap;
    std::vector<std::string> memoryLayout;
    std::vector<instruction> instructionList;
};


#endif