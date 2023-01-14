#pragma once
#include "DLL.h"
#include "graph.h"
#include "TuringMachine.h"

using MultitapeGraph = Graph<std::string, std::vector<typename TuringMachine::Transition>>;
using SingletapeGraph = Graph<std::string, TuringMachine::Transition>;

class MultitapeTuringMachine{
private:
    Graph<std::string, std::vector<TuringMachine::Transition>> transitions;
    std::string startState;

public:
    MultitapeTuringMachine(const MultitapeGraph&, std::string);

    void operate(std::vector<DLL<char>>&);
    DLL<char> operateAsSingle(const std::vector<DLL<char>>&);

    std::vector<SingletapeGraph> separateGraph(int);
    DLL<std::pair<char, std::string>> concatinateTapes(const std::vector<DLL<char>>&);
};

