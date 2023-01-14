#include "DLL.h"
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

class A{
    DLL<int> l;
public:
    A(const DLL<int>& l_) : l(l_){}

    void f(){
        DLL<int>::Iterator iter = l.begin();
        ++iter;
        l.pushFront(100);
        *iter = 20;
    }

    void printL() const{
        l.print();
    }
};

// std::vector<std::string> read_states(std::ifstream& in){
//     std::vector<std::string> states;
//     char c;
//     while(c != ']'){
//         in >> c;
//         if(c == '{'){
//             std::string state;
//             getline(in, state, '}');
//             states.push_back(state);
//             getline(in, state);
//         }
//     }
//     return states;
// }

// int main(){
    // DLL<int> l;
    // l.pushBack(1);
    // l.pushBack(2);
    // l.pushBack(3);
    // l.pushBack(4);
    // l.pushBack(5);
    // l.pushBack(6);

    // std::ofstream out("tape.txt");
    // out << l; 
    // out.close();

    // std::ifstream in("tape.txt");
    // DLL<char> list;
    // list.readFromTxtFile(in);
    // in.close();
    // std::cout << list;

//     // A a(l);
//     // a.f();
//     // a.printL();

    // std::ifstream in("graph.txt");
    // std::vector<std::string> states = read_states(in);
    // std::cout << states.size() << std::endl;
    // for(std::string state : states){
    //     std::cout << state << std::endl;
    // }

    // std::unordered_map<std::string, std::vector<int>> um;
    // std::vector<int> nums1 = {1,2,3};
    // std::vector<int> nums2 = {4,5};
    // std::vector<int> nums3 = {6};
    // um["A"] = nums1;
    // um["B"] = nums2;
    // um["C"] = nums3;
    // std::unordered_map<std::string, std::vector<int>>::const_iterator i = um.begin();
    // for(auto i = um.begin(); i != um.end(); ++i){
    //     std::cout << i->first << ": ";
    //     std::vector<int> nums = i->second;
    //     for(int num : nums){
    //         std::cout << num << " ";
    //     }
    //     std::cout << '\n';
    // }

//     std::string filename = "AL";
//     std::ifstream in(filename);
//     if(!in){
//         char msg[] = "Cannot open \"" + filename + "\" for writing";
//         std::cout << msg << std::endl;
//         throw msg.data();
//     }

    // std::ifstream in("graph.txt");
    // std::string s;
    // getline(in, s);
    // getline(in, s);
    // getline(in, s);
    // getline(in, s);
    // getline(in, s, '>');
    // char c;
    // in >> c;
    // std::cout << c << std::endl;
    // in >> c;
    // std::cout << c << std::endl;hy
// }