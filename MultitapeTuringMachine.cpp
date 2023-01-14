#include "MultitapeTuringMachine.h"


MultitapeTuringMachine::MultitapeTuringMachine(const MultitapeGraph& transitions_, std::string state) : 
transitions(transitions_), startState(state){}

void MultitapeTuringMachine::operate(std::vector<DLL<char>>& tapes){
    int numOfTapes = tapes.size();
    std::vector<SingletapeGraph> graphs = separateGraph(numOfTapes);
    for(int i = 0; i < numOfTapes; ++i){
        TuringMachine tm(graphs[i], startState);
        tm.operate(tapes[i]);
    }
}

std::vector<SingletapeGraph> MultitapeTuringMachine::separateGraph(int numOfTapes){
    std::vector<SingletapeGraph> result;
    for(int i = 0; i < numOfTapes; ++i){
        SingletapeGraph newGraph;
        MultitapeGraph::GraphIterator iter = transitions.begin();
        for(; iter != transitions.end(); ++iter){
            newGraph.addVertex(*iter);
            std::vector<MultitapeGraph::Edge> edges = iter.getEdges();
            for(auto edge : edges){
                newGraph.addVertex(edge.dest);
                newGraph.addEdge(*iter, edge.dest, edge.data[i]);
            }
        }
        result.push_back(newGraph);
    }
    return result;
}

DLL<char> MultitapeTuringMachine::operateAsSingle(const std::vector<DLL<char>>& tapes){
    DLL<std::pair<char, std::string>> tape = concatinateTapes(tapes);
    
    int halts = tapes.size();
    DLL<std::pair<char, std::string>>::Iterator iter;

    //we will iterate over and over the tape until all of the states for the subtapes are halt
    while(halts > 0){
        int tapeCount = 0;
        for(iter = tape.begin(); iter != tape.end(); ++iter){

            //shows that we will be operating on the next subtape
            if((*iter).first == '#'){
                ++tapeCount;
                continue;
            }

            //we have encountered a marked cell
            if((*iter).second != "-"){

                //getting the state from the mark
                std::string stateMark = (*iter).second;

                //unmarking the current cell
                (*iter).second = "-";

                //one of the 'machines' has halted
                if(stateMark == "halt"){
                    --halts;
                    continue;
                }

                //finding the edges from the encountered state mark
                std::vector<MultitapeGraph::Edge> edges = transitions[stateMark];

                //searching for the corresponding transition
                for(auto edge : edges){
                    if((*iter).first == edge.data[tapeCount].startSymbol){
                        (*iter).first = edge.data[tapeCount].endSymbol;

                        if(edge.data[tapeCount].command == 'L'){
                            --iter;

                            //checking if we have reached the end of the current subtape. 
                            //If so, it means that the transition requires adding a new blank cell.
                            if((*iter).first == '#'){
                                tape.insertBefore(iter->next, {'_', "-"});
                                ++iter;
                            }
                        }
                        if(edge.data[tapeCount].command == 'R'){
                            ++iter;

                            if((*iter).first == '#'){
                                tape.insertBefore(iter.operator->(), {'_', "-"});
                                --iter;
                            }
                        }
                        //marking the current cell with the destination state for this subtape
                        (*iter).second = edge.dest;
                        break;
                    }
                }
            }
        }
    }

    DLL<char> result;
    for(std::pair<char, std::string> cell : tape){
        result.pushBack(cell.first);
    }
    return result;
}

DLL<std::pair<char, std::string>> MultitapeTuringMachine::concatinateTapes(const std::vector<DLL<char>>& tapes){
    DLL<std::pair<char, std::string>> result;
    for(DLL<char> tape : tapes){
        DLL<char>::Iterator iter = tape.begin();
        result.pushBack({*iter, startState});
        ++iter;
        while(iter != tape.end()){
            result.pushBack({*iter, "-"});
            ++iter;
        }
        result.pushBack({'#', "-"});
    }
    return result;
}
