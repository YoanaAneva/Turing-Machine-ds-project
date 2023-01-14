// #define DOCTEST_CONFIG_IMPLEMENT
// #include "DLL.h"
// #include "doctest.h"

// TEST_CASE("Test push functions"){
//     DLL<int> list;
//     list.pushBack(2);
//     list.pushFront(1);

//     CHECK(list.size() == 2);
//     CHECK(list[0] == 1);
//     CHECK(list[1] == 2);
// }

// TEST_CASE("Test insert before function"){
//     DLL<int> list;
//     list.pushBack(1);
//     list.pushBack(2);
//     list.pushBack(4);
//     list.pushBack(5);

//     DLL<int>::Iterator iter = list.begin();
//     list.insertBefore(iter.operator->(), 0);

//     ++iter;
    
//     list.insertBefore(iter->next, 3);

//     ++iter;
//     ++iter;
//     ++iter;

//     list.insertBefore(iter->next, 6);

//     std::stringstream ss;
//     ss << list;
//     std::string expected = "0123456\n";
    
//     CHECK(ss.str() == expected);
// }

// TEST_CASE("Test Copy"){
//     DLL<int> list;
//     list.pushBack(1);
//     list.pushBack(2);
//     list.pushBack(3);
//     list.pushBack(4);

//     DLL<int> listCopy(list);

//     CHECK(listCopy.size() == list.size());
//     CHECK(listCopy[0] == 1);
//     CHECK(listCopy[2] == 3);
    
//     listCopy.pushBack(5);
//     CHECK(listCopy[4] == 5);
//     CHECK(listCopy.size() == 5);
//     CHECK(list.size() == 4);
// }

// TEST_CASE("Test assigment"){
//     DLL<int> list;
//     list.pushBack(1);
//     list.pushBack(2);
//     list.pushBack(3);
//     list.pushBack(4);

//     DLL<int> listCopy;
//     listCopy = list;

//     CHECK(listCopy.size() == list.size());
//     CHECK(listCopy[0] == 1);
//     CHECK(listCopy[2] == 3);
    
//     listCopy.pushBack(5);
//     CHECK(listCopy[4] == 5);
//     CHECK(listCopy.size() == 5);
//     CHECK(list.size() == 4); 
// }

// TEST_CASE("Test Iterator"){
//     DLL<int> list;
//     list.pushBack(10);
//     list.pushBack(20);
//     list.pushBack(30);
//     list.pushBack(40);

//     DLL<int>::Iterator iter(list.begin());
//     ++iter;
//     ++iter;
//     CHECK(*iter == 30);

//     --iter;
//     CHECK(*iter == 20);

//     *iter = 200;
//     CHECK(list[1] == 200);
// }

// TEST_CASE("Test operator<< and reading"){
//     DLL<char> list;
//     list.pushBack('a');
//     list.pushBack('b');
//     list.pushBack('c');
//     list.pushBack('d');

//     std::ofstream output("test_tape.txt");
//     output << list;
//     output.close();

//     DLL<char> list1;
//     list1.readFromTxtFile("test_tape.txt");

//     CHECK(list1[0] == 'a');
//     CHECK(list1[1] == 'b');
//     CHECK(list1[2] == 'c');
//     CHECK(list1[3] == 'd');
// }   

// int main(){
//     doctest::Context().run();
// }