#pragma once
#include <iostream>
#include <fstream>

template<class T>
class DLL{
private:
    struct Node{
        T data;
        Node* prev;
        Node* next;
    };

    Node* first;
    Node* last;

    void copy(const DLL<T>&);
    void erase();

public:
    DLL() : first(nullptr), last(nullptr) {};

    DLL(const DLL<T>& other);
    DLL<T>& operator=(const DLL<T>&);

    ~DLL();

    void pushFront(const T&);
    void pushBack(const T&);
    void insertBefore(Node*, const T&);

    const T& operator[](int) const;
    int size() const;

    void print() const;

    friend std::ostream& operator<<(std::ostream& output, const DLL& list){   
        Node* curr = list.first;
        while(curr != nullptr){
            output << curr->data;
            curr = curr->next;
        }   
        output << "\n";
        return output;
    }

    void readFromTxtFile(std::string);

    class Iterator{
    friend class DLL;

    private:
        Node* current;
        DLL* list;

        Iterator(Node* node, DLL* list_) : current(node), list(list_){}

    public:
        Iterator() : current(nullptr), list(nullptr){}

        Iterator& operator++();
        Iterator& operator--();
        bool operator!=(const Iterator&) const;
        T& operator*();
        Node* operator->();
    };

    Iterator begin();
    Iterator end();
};

template<class T>
void DLL<T>::copy(const DLL<T>& other){
    if(other.first == nullptr)
        return;
    first = new Node{other.first->data, nullptr, nullptr};

    Node* curr = first;
    Node* otherCurr = other.first->next;

    while(otherCurr != nullptr){
        curr->next = new Node{otherCurr->data, curr, nullptr};
        curr = curr->next;
        otherCurr = otherCurr->next;
    }
    last = curr;
}

template<class T>
void DLL<T>::erase(){        
    Node* temp;
    while(first != nullptr){
        temp = first;
        first = first->next;
        delete temp;
    }
    last = nullptr;
}

template<class T>
DLL<T>::DLL(const DLL<T>& other){
    copy(other);
}

template<class T>
DLL<T>& DLL<T>::operator=(const DLL<T>& other){
    if(this != &other){
        erase();
        copy(other);
    }
    return *this;
}

template<class T>
DLL<T>::~DLL(){
    erase();
}

template<class T>
void DLL<T>::pushFront(const T& data){
    if(first == nullptr){
        first = new Node{data, nullptr, nullptr};
        last = first;
        return;
    }
    Node* newNode = new Node{data, nullptr, first};
    first->prev = newNode;
    first = newNode;
}

template<class T>
void DLL<T>::pushBack(const T& data){
    if(first == nullptr){
        first = new Node{data, nullptr, nullptr};
        last = first;
        return;
    }

    last->next = new Node{data, last, nullptr};
    last = last->next;
}

template<class T>
void DLL<T>::insertBefore(DLL<T>::Node* node, const T& data){
    if(node == nullptr){
        pushBack(data);
        return;
    }
    if(node == first){
        pushFront(data);
        return;
    }
    DLL<T>::Node* curr = first;

    while(curr->next != node){
        curr = curr->next;                                                                               
    }
    Node* newNode = new Node{data, curr, curr->next};
    curr->next->prev = newNode;
    curr->next = newNode;
}

template<class T>
const T& DLL<T>::operator[](int index) const{
    if(index < 0){
        throw std::invalid_argument("Index should be positive number"); 
    }
    if(first == nullptr){
        throw std::out_of_range("List is empty");
    }
    Node* curr = first;
    while(index > 0){
        if(curr == nullptr){
            throw std::out_of_range("Index out of range");
        }
        curr = curr->next;
        --index;
    }
    return curr->data;
}

template<class T>
int DLL<T>::size() const{
    Node* curr = first;
    int count = 0;
    while(curr != nullptr){
        ++count;
        curr = curr->next;
    } 
    return count;
}

template<class T>
void DLL<T>::print()const{
    if(first == nullptr){
        std::cout << "nullptr" << std::endl;
        return;
    }
    Node* curr = first;
    while(curr != nullptr){
        T data = curr->data == ' ' ? '_' : curr->data;
        std::cout << data << " ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

template<class T>
typename DLL<T>::Iterator& DLL<T>::Iterator::operator++(){
    if(current != nullptr){
        current = current->next;
    }
    return *this;
}

template<class T>
typename DLL<T>::Iterator& DLL<T>::Iterator::operator--(){
    if(current != nullptr){
        current = current->prev;
    }
    return *this;
}

template<class T>
bool DLL<T>::Iterator::operator!=(const DLL<T>::Iterator& other) const{
    return current != other.current;
}

template<class T>        
T& DLL<T>::Iterator::operator*(){
    if(current == nullptr){
        throw std::out_of_range("Iterator out of range.");
    }
    return current->data;
}

template<class T>
typename DLL<T>::Node* DLL<T>::Iterator::operator->(){
    return current;
}

template<class T>
typename DLL<T>::Iterator DLL<T>::begin(){
    return typename DLL<T>::Iterator(first, this);
}

template<class T>
typename DLL<T>::Iterator DLL<T>::end(){
    return typename DLL<T>::Iterator(nullptr, this);
}
template<class T>
void DLL<T>::readFromTxtFile(std::string filename){
    std::ifstream input(filename);
    if(!input)
        throw std::invalid_argument("Stream not in good condition, cannot read");

    std::string tape;
    getline(input, tape);
    for(char c : tape){
        if(c == '\t')
            continue;
        pushBack(c);
    }
    
    input.close();
}