#include "TuringMachine.h"

void readTransition(std::ifstream&, Graph<std::string,TuringMachine::Transition>&);

bool TuringMachine::Transition::operator==(const TuringMachine::Transition& other) const{
    return startSymbol == other.startSymbol && endSymbol == other.endSymbol && command == other.command;
}

TuringMachine::TuringMachine(){
    transitions.addVertex("halt");
}

TuringMachine::TuringMachine(const Graph<std::string, Transition>& transitions_, const std::string& startState_) : 
    transitions(transitions_){
        setStartState(startState_);
        transitions.addVertex("halt");
};

const std::string& TuringMachine::getStartState() const{
    return startState;
}
const std::string& TuringMachine::getCurrentState() const{
    return currentState;
}

void TuringMachine::setStartState(std::string startState_){
    if(startState_ == "" || startState_ == "\n" || startState_ == "\t" || startState_ == " "){
        throw std::invalid_argument("Invalid start state");
    }
    startState = startState_;
    currentState = startState;
}

void TuringMachine::operate(DLL<char>& tape){
    //getting the edges from the start state
    std::vector<Graph<std::string, Transition>::Edge> edges = transitions[startState];
    std::string nextKey;
    //setting the head of the machine to the begging of the tape
    head = tape.begin();

    //traversing the graph until halt state is reached or a vertex from which no edges begin 
    while(nextKey != "halt" && edges.size() != 0){
        bool isFound = false;

        //searching for the transition which first symbol corresponds to the tape symbol currently under the head
        for(int i = 0; i < edges.size() && !isFound; ++i){
            if(edges[i].data.startSymbol == *head){

                //writing the corresponding second symbol on the tape
                *head = edges[i].data.endSymbol;

                if(edges[i].data.command == 'R'){
                    //it the command requires going to the right, but the end of the tape has been reached, we add a blank cell
                    if(head->next == nullptr){
                        tape.pushBack('_');
                    }
                    ++head;
                }

                if(edges[i].data.command == 'L'){
                    //same but on the left side
                    if(head->prev == nullptr){
                        tape.pushFront('_');
                    }
                    --head;
                }
                //getting the next state vertex to which we should move
                nextKey = edges[i].dest;
                //setting the machine current state to the next state
                currentState = nextKey;
                isFound = true;
            }
        }
        if(!isFound){
            throw std::invalid_argument("Turing machine is not constructed correctly for this entry tape");
        }
        //getting the transitions from the next state
        edges = transitions[nextKey];
    }
}

void TuringMachine::composition(TuringMachine& firstMachine, TuringMachine& secondMachine, DLL<char>& entryTape){
    //the first machine operates over the entry tape
    firstMachine.operate(entryTape);
    try{
        //the second machine operates over the result tape
        secondMachine.operate(entryTape);
    }
    catch(std::invalid_argument){
        //if the second machine is not built to operate over tape, which the first machine has changed, an exception is thrown 
        throw std::invalid_argument("Composition of the two machines is impossible");
    }
}

void TuringMachine::branching(TuringMachine& forTrue, TuringMachine& forFalse, TuringMachine& acceptor, DLL<char>& entryTape){
    acceptor.operate(entryTape);

    if(acceptor.currentState == "Accept"){
        forTrue.operate(entryTape);
    }
    else if(acceptor.currentState == "Reject"){
        forFalse.operate(entryTape);
    }
    else{
        throw std::invalid_argument("Acceptor turing machine not constructed correctly for branching.");
    }

    std::ofstream output("branching_of_turing_machines.txt");
    output << entryTape << std::endl;
    output.close();
}

void TuringMachine::whileLoop(TuringMachine& acceptor, TuringMachine& executor, DLL<char>& entryTape){
    while(true){
        acceptor.operate(entryTape);
        if(acceptor.getCurrentState() == "Reject"){
            break;
        }
        if(acceptor.getCurrentState() == "Accept"){
            executor.operate(entryTape);
            continue;
        }
        throw std::invalid_argument("Acceptor turing machine not constructed correctly for while loop.");
    }
}

void TuringMachine::writeInTxtFile(std::string filename) const{
    std::ofstream output(filename);
    if(!output){
        std::string msg = "Cannot open \"" + filename + "\" for writing";
        std::cout << msg << std::endl;
        throw msg;
    }

    output << "Turing Machine(\nstart state:" << startState << "\ntransitions:[\n";

    Graph<std::string, Transition>::GraphIterator iter = transitions.begin();
    for(iter = transitions.begin(); iter != transitions.end(); ++iter){
        std::vector<Graph<std::string, Transition>::Edge> currEdges = iter.getEdges();
        for(Graph<std::string, Transition>::Edge edge : currEdges){
            output << '\t' << edge.data.startSymbol << " {" << *iter << "} -> " 
            << edge.data.endSymbol << " {" << edge.dest << "} " << edge.data.command << '\n';
        }
    }

    //another way of iterating over the graph:

    // for(std::string state : transitions){
    //     std::vector<Graph<std::string, Transition>::Edge> currEdges = transitions[state];
    //     for(Graph<std::string, Transition>::Edge edge : currEdges){
    //         output << '\t' << edge.data.startSymbol << " {" << state << "} -> " 
    //         << edge.data.endSymbol << " {" << edge.dest << "} " << edge.data.command << '\n';
    //     }
    // }

    output << "])\n";
    output.close();
}

void TuringMachine::readFromTxtFile(std::string filename){
    std::ifstream input(filename);
    if(!input){
        std::string msg = "Cannot open \"" + filename + "\" for reading";
        std::cout << msg << std::endl;
        throw msg;
    }

    std::string startState, buffer;

    //reading "Turing Machine(\nstart state:"
    getline(input, buffer);
    getline(input, buffer, ':');

    getline(input, startState);
    
    //reading "\ntransitions:[\n"
    getline(input, buffer);
    
    while(true){
        try{
            readTransition(input, transitions);
        }

        //the function throws two messages, one, indicating all of the transitions 
        //are read (or the end of the file was reached), and one if invalid command symbol was encountered
        catch(std::string msg){
            if(msg == "No more transitions to read"){
                break;
            }
            else{
                throw std::invalid_argument(msg);
            }
        }
    }

    //reading "])\n"
    getline(input, buffer);

    setStartState(startState);

    input.close();
}

void readTransition(std::ifstream& input, Graph<std::string,TuringMachine::Transition>& graph){
    char c;
    char startSymbol;
    char endSymbol;
    char command;
    std::string buffer;
    std::string startState;
    std::string destState;

    //if ']' is reached, all of the transitions from the file are read and this information is passed to the calling function
    if(input.peek() == ']' || input.peek() == '\n' || !input){
        std::string msg = "No more transitions to read";
        throw msg;
    }

    //reading start symbol
    input >> startSymbol;
    
    //reading " {"
    input >> c;

    //reading startState
    getline(input, startState, '}');
    
    //reading " ->"
    getline(input, buffer, '>');

    //reading end symbol
    input >> endSymbol;
    
    //reading " {"
    input >> c;
    
    //reading destination state
    getline(input, destState, '}');

    //reading command symbol
    input >> command;
    
    //reading new line
    getline(input, buffer);
    
    if(command != 'L' && command != 'R' && command != 'S'){
        throw "Invalid command symbol, should be 'L/'R'/'S'";
    }
    
    TuringMachine::Transition transition{startSymbol, endSymbol, command};
    graph.addVertex(startState);
    graph.addVertex(destState);
    graph.addEdge(startState, destState, transition);
}

void TuringMachine::printHeadPosition(){
    if(head.operator->() != nullptr)
        std::cout << *head << std::endl;
    else
        std::cout << "nullptr" << std::endl;
}
