#include "TuringMachine.h"
#include "MultitapeTuringMachine.h"

MultitapeGraph makeTransitionsForMTM();
std::vector<DLL<char>> makeTapesForMTM();

void operate(){
    TuringMachine tm;
    DLL<char> tape;

    tm.readFromTxtFile("addition.txt");
    tape.readFromTxtFile("addition_tape.txt");

    tm.operate(tape);
    std::cout << tape;
    std::cout << "head position: ";
    tm.printHeadPosition();
}

void composition(){
    TuringMachine firstMachine, secondMachine;
    DLL<char> tape;

    firstMachine.readFromTxtFile("turing_machine.txt");
    secondMachine.readFromTxtFile("turn_to_ab.txt");
    tape.readFromTxtFile("tape.txt");

    TuringMachine::composition(firstMachine, secondMachine, tape);
        
    std::ofstream output("composition_of_turing_machines.txt");
    output << tape << std::endl;
    output.close();
}

void branching(){
    TuringMachine forTrue, forFalse, acceptor;
    DLL<char> tape;

    forTrue.readFromTxtFile("decrement_by_one.txt");
    forFalse.readFromTxtFile("increment_by_one.txt");
    acceptor.readFromTxtFile("check_if_less_than_10.txt");
    tape.readFromTxtFile("binNumber.txt");

    TuringMachine::branching(forTrue, forFalse, acceptor, tape);
    
    std::ofstream output("branching_of_turing_machines.txt");
    output << tape << std::endl;
    output.close();
}

void whileLoop(){
    TuringMachine acceptor, executor;
    DLL<char> tape;

    executor.readFromTxtFile("increment_by_one.txt");
    acceptor.readFromTxtFile("check_if_less_than_10.txt");
    tape.readFromTxtFile("binNumber.txt");

    TuringMachine::whileLoop(acceptor, executor, tape);
    
    std::ofstream output("while_loop_turing_machines.txt");
    output << tape << std::endl;
    output.close();
}

void operationOfMultitapeTM(){
    MultitapeGraph transitions = makeTransitionsForMTM();
    std::vector<DLL<char>> tapes = makeTapesForMTM();

    MultitapeTuringMachine multitapeTM(transitions, "Q0");

    multitapeTM.operate(tapes);

    std::ofstream output("multitape_turing_machine_tapes.txt");
    for(DLL<char> tape : tapes){
        output << tape;
    }
    output.close();
}

void operation_of_multitape_TM_as_singletape(){
    MultitapeGraph transitions = makeTransitionsForMTM();
    std::vector<DLL<char>> tapes = makeTapesForMTM();

    MultitapeTuringMachine multitapeTM(transitions, "Q0");

    DLL<char> tape = multitapeTM.operateAsSingle(tapes);

    std::ofstream output("multitape_turing_machine_single_tape.txt");
    output << tape;
    output.close();
}


int main(){
    // operate();
    // composition();
    // branching();
    // whileLoop();
    // operationOfMultitapeTM();
    // operation_of_multitape_TM_as_singletape();
}


std::vector<DLL<char>> makeTapesForMTM(){
    DLL<char> tape1;
    tape1.pushBack('1');
    tape1.pushBack('0');
    tape1.pushBack('1');

    DLL<char> tape2;
    tape2.pushBack('y');
    tape2.pushBack('x');
    tape2.pushBack('x');

    DLL<char> tape3;
    tape3.pushBack('b');
    tape3.pushBack('b');
    tape3.pushBack('b');

    return {tape1, tape2, tape3};
}

Graph<std::string, std::vector<TuringMachine::Transition>> makeTransitionsForMTM(){
    Graph<std::string, std::vector<TuringMachine::Transition>> result;
    result.addVertex("Q0");
    result.addVertex("Q1");
    result.addVertex("halt");

    TuringMachine::Transition tr1ForTape1{'0', '0', 'R'};
    TuringMachine::Transition tr1ForTape2{'x', 'x', 'R'};
    TuringMachine::Transition tr1ForTape3{'a', 'a', 'R'};

    result.addEdge("Q0", "Q0", {tr1ForTape1, tr1ForTape2, tr1ForTape3});

    TuringMachine::Transition tr2ForTape1{'1', '1', 'R'};
    TuringMachine::Transition tr2ForTape2{'y', 'y', 'R'};
    TuringMachine::Transition tr2ForTape3{'b', 'b', 'R'};

    result.addEdge("Q0", "Q0", {tr2ForTape1, tr2ForTape2, tr2ForTape3});

    TuringMachine::Transition tr31{'_', '_', 'L'};

    result.addEdge("Q0", "Q1", {tr31, tr31, tr31});

    TuringMachine::Transition tr4ForTape1{'1', '0', 'L'};
    TuringMachine::Transition tr4ForTape2{'y', 'x', 'L'};
    TuringMachine::Transition tr4ForTape3{'b', 'a', 'L'};

    result.addEdge("Q1", "Q1", {tr4ForTape1, tr4ForTape2, tr4ForTape3});

    TuringMachine::Transition tr5ForTape1{'_', '1', 'S'};
    TuringMachine::Transition tr5ForTape2{'_', 'y', 'S'};
    TuringMachine::Transition tr5ForTape3{'_', 'b', 'S'};

    result.addEdge("Q1", "halt", {tr5ForTape1, tr5ForTape2, tr5ForTape3});

    TuringMachine::Transition tr6ForTape1{'0', '1', 'S'};
    TuringMachine::Transition tr6ForTape2{'x', 'y', 'S'};
    TuringMachine::Transition tr6ForTape3{'a', 'b', 'S'};

    result.addEdge("Q1", "halt", {tr6ForTape1, tr6ForTape2, tr6ForTape3});
    return result;
}
