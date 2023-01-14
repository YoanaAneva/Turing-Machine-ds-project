#pragma once
#include "graph.h"
#include "DLL.h"

class TuringMachine{
public:
    struct Transition{
        char startSymbol;
        char endSymbol;
        char command;

        void print() const{
            std::cout << startSymbol << " " <<  endSymbol << " " << command  << " " << std::endl;
        }

        bool operator==(const Transition&) const;
    };

private:
    Graph<std::string, Transition> transitions;
    std::string startState;
    std::string currentState;
    DLL<char>::Iterator head;

public:
    TuringMachine();
    TuringMachine(const Graph<std::string, Transition>& transitions_, const std::string& startState_);

    void setStartState(std::string state);

    const std::string& getStartState() const;
    const std::string& getCurrentState() const;

    void operate(DLL<char>&);

    static void composition(TuringMachine&, TuringMachine&, DLL<char>&);
    static void branching(TuringMachine&, TuringMachine&, TuringMachine&, DLL<char>&);
    static void whileLoop(TuringMachine&, TuringMachine&, DLL<char>&);

    void writeInTxtFile(std::string filename) const;
    void readFromTxtFile(std::string filename);

    void printHeadPosition();
};