// #define DOCTEST_CONFIG_IMPLEMENT
// #include "doctest.h"
// #include "TuringMachine.h"

// Graph<std::string, TuringMachine::Transition> makeTestGraph();
// DLL<char> makeTestTape();
// DLL<char> makeBinNumTape();

// TEST_CASE("Test initialization"){
//     Graph<std::string, TuringMachine::Transition> transitions;
//     TuringMachine tm(transitions, "-");
     
//     CHECK(tm.getStartState() == "-");

//     tm.setStartState("A");

//     CHECK(tm.getStartState() == "A");
//     CHECK(tm.getCurrentState() == "A");
// }

// TEST_CASE("Test operate function"){
//     Graph<std::string, TuringMachine::Transition> transitions = makeTestGraph();
//     DLL<char> tape = makeTestTape();

//     TuringMachine tm(transitions, "A");

//     tm.operate(tape);

//     std::stringstream ss;
//     ss << tape;

//     CHECK(ss.str() == "xxxyyy\n");
// }

// TEST_CASE("Test composition"){
//     TuringMachine tmFirst, tmSecond;

//     tmFirst.readFromTxtFile("increment_by_one.txt");
//     tmSecond.readFromTxtFile("turn_to_xy.txt");

//     //1010
//     DLL<char> binNum = makeBinNumTape();

//     //1010 -> 1011 -> yxyy
//     TuringMachine::composition(tmFirst, tmSecond, binNum);

//     std::stringstream ss;
//     ss << binNum;
    
//     CHECK(ss.str() == "yxyy_\n");
// }

// TEST_CASE("Test branching"){
//     TuringMachine forTrue, forFalse, acceptor;
//     DLL<char> binNum = makeBinNumTape();

//     forTrue.readFromTxtFile("increment_by_one.txt");
//     forFalse.readFromTxtFile("decrement_by_one.txt");
//     acceptor.readFromTxtFile("check_if_less_than_10.txt");

//     //check(1010) -> False -> 1001
//     TuringMachine::branching(forTrue, forFalse, acceptor, binNum);

//     std::stringstream ss;
//     ss << binNum;

//     CHECK(ss.str() == "1001_\n");
// }

// TEST_CASE("Test while loop"){
//     TuringMachine acceptor, executor;

//     acceptor.readFromTxtFile("check_if_less_than_10.txt");
//     executor.readFromTxtFile("increment_by_one.txt");
    
//     DLL<char> binNum;
//     binNum.pushBack('1');
//     binNum.pushBack('0');
//     binNum.pushBack('1');

//     TuringMachine::whileLoop(acceptor, executor, binNum);

//     std::stringstream ss;
//     ss << binNum;

//     CHECK(ss.str() == "1010_\n");
// }

// DLL<char> makeBinNumTape(){
//     DLL<char> tape;
//     tape.pushBack('1');
//     tape.pushBack('0');
//     tape.pushBack('1');
//     tape.pushBack('0');

//     return tape;
// }

// DLL<char> makeTestTape(){
//     DLL<char> tape;
//     tape.pushBack('0');
//     tape.pushBack('0');
//     tape.pushBack('0');
//     tape.pushBack('1');
//     tape.pushBack('1');
//     tape.pushBack('1');

//     return tape;
// }

// Graph<std::string, TuringMachine::Transition> makeTestGraph(){
//     Graph<std::string, TuringMachine::Transition> g;
//     g.addVertex("A");
//     g.addVertex("B");
//     g.addVertex("C");
//     g.addVertex("halt");

//     TuringMachine::Transition t1{'0', 'x', 'R'};
//     g.addEdge("A", "B", t1);
//     TuringMachine::Transition t2{'y', 'y', 'S'};
//     g.addEdge("A", "halt", t2);
//     TuringMachine::Transition t3{'0', '0', 'R'};
//     g.addEdge("B", "B", t3);
//     TuringMachine::Transition t4{'y', 'y', 'R'};
//     g.addEdge("B", "B", t4);
//     TuringMachine::Transition t5{'1', 'y', 'L'};
//     g.addEdge("B", "C", t5);
//     TuringMachine::Transition t6{'0', '0', 'L'};
//     g.addEdge("C", "C", t6);
//     TuringMachine::Transition t7{'y', 'y', 'L'};
//     g.addEdge("C", "C", t7);
//     TuringMachine::Transition t8{'x', 'x', 'R'};
//     g.addEdge("C", "A", t8);

//     return g;
// }

// int main(){
//     doctest::Context().run();
// }