// #define DOCTEST_CONFIG_IMPLEMENT
// #include "doctest.h"
// #include "MultitapeTuringMachine.h"

// // using MultitapeGraph = Graph<std::string, std::vector<typename TuringMachine::Transition>>;
// // using SingletapeGraph = Graph<std::string, TuringMachine::Transition>;

// MultitapeGraph makeTransitionsForMTM();
// std::vector<DLL<char>> makeTapes();

// TEST_CASE("Test operate"){
//     MultitapeGraph transitions = makeTransitionsForMTM();
//     std::vector<DLL<char>> tapes = makeTapes();

//     MultitapeTuringMachine MTM(transitions, "Q0");
//     MTM.operate(tapes);

//     std::vector<std::string> expected = {"110_\n", "yxy_\n", "baaa_\n"};

//     for(int i = 0; i < 3; ++i){
//         std::stringstream ss;
//         ss << tapes[i];
//         CHECK(ss.str() == expected[i]);
//     }
// }

// TEST_CASE("Test separating graph"){
//     MultitapeGraph multitapeGraph = makeTransitionsForMTM();
//     MultitapeTuringMachine MTM(multitapeGraph, "Q0");

//     std::vector<SingletapeGraph> graphs = MTM.separateGraph(3);

//     CHECK(graphs[0]["Q0"][1].data.startSymbol == '1');
//     CHECK(graphs[1]["Q0"][1].data.startSymbol == 'y');
//     CHECK(graphs[2]["Q0"][1].data.startSymbol == 'b');    
    
//     CHECK(graphs[0]["Q1"][0].data.endSymbol == '0');
//     CHECK(graphs[1]["Q1"][0].data.endSymbol == 'x');
//     CHECK(graphs[2]["Q1"][0].data.endSymbol == 'a');

//     CHECK(graphs[0]["Q0"][2].dest == "Q1");
//     CHECK(graphs[1]["Q0"][2].dest == "Q1");
//     CHECK(graphs[2]["Q0"][2].dest == "Q1");
// }

// TEST_CASE("Test concatinating tapes"){
//     std::vector<DLL<char>> tapes = makeTapes();
//     MultitapeTuringMachine MTM(MultitapeGraph(), "A");

//     DLL<std::pair<char,std::string>> result;
//     result = MTM.concatinateTapes(tapes);   

//     std::string resultStr;
//     for(std::pair<char, std::string> cell : result){
//         resultStr += cell.first;
//     }

//     CHECK(resultStr == "101#yxx#bbb#");
// }

// TEST_CASE("Test operate as singletape machine function"){
//     MultitapeGraph transitions = makeTransitionsForMTM();
//     std::vector<DLL<char>> tapes = makeTapes();
//     MultitapeTuringMachine MTM(transitions, "Q0");

//     DLL<char> result;
//     result = MTM.operateAsSingle(tapes);

//     std::stringstream ss;
//     ss << result;

//     CHECK(ss.str() == "110_#yxy_#baaa_#\n");
// }

// int main(){
//     doctest::Context().run();
// }

// std::vector<DLL<char>> makeTapes(){
//     DLL<char> tape1;
//     tape1.pushBack('1');
//     tape1.pushBack('0');
//     tape1.pushBack('1');

//     DLL<char> tape2;
//     tape2.pushBack('y');
//     tape2.pushBack('x');
//     tape2.pushBack('x');

//     DLL<char> tape3;
//     tape3.pushBack('b');
//     tape3.pushBack('b');
//     tape3.pushBack('b');

//     return {tape1, tape2, tape3};
// }

// MultitapeGraph makeTransitionsForMTM(){
//     Graph<std::string, std::vector<TuringMachine::Transition>> result;
//     result.addVertex("Q0");
//     result.addVertex("Q1");
//     result.addVertex("halt");

//     TuringMachine::Transition tr1ForTape1{'0', '0', 'R'};
//     TuringMachine::Transition tr1ForTape2{'x', 'x', 'R'};
//     TuringMachine::Transition tr1ForTape3{'a', 'a', 'R'};

//     result.addEdge("Q0", "Q0", {tr1ForTape1, tr1ForTape2, tr1ForTape3});

//     TuringMachine::Transition tr2ForTape1{'1', '1', 'R'};
//     TuringMachine::Transition tr2ForTape2{'y', 'y', 'R'};
//     TuringMachine::Transition tr2ForTape3{'b', 'b', 'R'};

//     result.addEdge("Q0", "Q0", {tr2ForTape1, tr2ForTape2, tr2ForTape3});

//     TuringMachine::Transition tr31{'_', '_', 'L'};

//     result.addEdge("Q0", "Q1", {tr31, tr31, tr31});

//     TuringMachine::Transition tr4ForTape1{'1', '0', 'L'};
//     TuringMachine::Transition tr4ForTape2{'y', 'x', 'L'};
//     TuringMachine::Transition tr4ForTape3{'b', 'a', 'L'};

//     result.addEdge("Q1", "Q1", {tr4ForTape1, tr4ForTape2, tr4ForTape3});

//     TuringMachine::Transition tr5ForTape1{'_', '1', 'S'};
//     TuringMachine::Transition tr5ForTape2{'_', 'y', 'S'};
//     TuringMachine::Transition tr5ForTape3{'_', 'b', 'S'};

//     result.addEdge("Q1", "halt", {tr5ForTape1, tr5ForTape2, tr5ForTape3});

//     TuringMachine::Transition tr6ForTape1{'0', '1', 'S'};
//     TuringMachine::Transition tr6ForTape2{'x', 'y', 'S'};
//     TuringMachine::Transition tr6ForTape3{'a', 'b', 'S'};

//     result.addEdge("Q1", "halt", {tr6ForTape1, tr6ForTape2, tr6ForTape3});
//     return result;
// }