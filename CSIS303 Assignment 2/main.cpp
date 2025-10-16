//main.cpp


//1. A singly linked list that stores strings (animal names). It lets you add, remove, insert and find animals
//2. A stack that stores integers using a vector using pop, push, top, average and empty



#include <iostream>
#include "declarations.h"
#include <cstddef>


LinkedList animals;

//Linked List function definitions

//This function prints everything in the linked list
void LinkedList::print_list() const {
    Node* current = head; // start from the head of the list
    std::cout << "Updated List: ";
    //loop through all nodes until the end
    while (current != nullptr) {
        std::cout << current->data;  //print the animal name stored in this node
        if (current->next != nullptr) { //if not at the last node
            std::cout << " -> ";
        }
        current = current->next;        //move to the next node
    }
    std::cout << std::endl;
}

//Adds new node at front of list
void LinkedList::push_front(const std::string& item) {
    Node* new_node = new Node(item, head); //make new node that points to old head
    head = new_node;                       //new node is the head
    if (tail == nullptr) {                 //if list was empty before
        tail = new_node;                     //update tail pointer
    }
    num_items++;
}

//adds new node at end of list
void LinkedList::push_back(const std::string& item) {
    Node* new_node = new Node(item, nullptr);
    if (tail != nullptr) {
        tail->next = new_node;                  //connect old tail to new node
        tail = new_node;                        //update tail pointer
    }
    num_items++;
}

//removes node at the front 
void LinkedList::pop_front() {
    Node* removed_node = head; //save the node we’re deleting
    head = head->next;         //move head pointer to next node
    delete removed_node;       //delete old head node
    num_items--;
}

//removes node at end
void LinkedList::pop_back() {
    Node* prev = head;
    //find the node right before the tail
    while (prev->next != tail) {
        prev = prev->next;
    }
    delete tail;          //delete the current tail
    tail = prev;          //tail now points to previous node
    tail->next = nullptr;
    --num_items;
}

//returns animal in first node
const std::string& LinkedList::front() const {
    return head->data;
}

//returns animal in last node
const std::string& LinkedList::back() const {
    return tail->data;
}

//checks if list is empty
bool LinkedList::empty() const {
    return num_items == 0; // true if there are no items
}

//inserts a new node at index
void LinkedList::insert(size_t index, const std::string& item) {
    Node* new_node = new Node(item);

    //if adding to the front
    if (index == 0) {
        new_node->next = head;
        head = new_node;
    }
    //adding anywhere else
    else {
        Node* current = head;
        //move to the node right before target spot
        for (size_t i = 0; i < index - 1 && current->next != nullptr; ++i) {
            current = current->next;
        }
        //connect the new node into the list
        new_node->next = current->next;
        current->next = new_node;

        //if we inserted at the end, update tail
        if (new_node->next == nullptr) {
            tail = new_node;
        }
    }
    ++num_items;
    std::cout << "Inserted " << item << " at index " << index << std::endl;
}

//Removes node at index
bool LinkedList::remove(size_t index) {
    //if removing the first item
    if (index == 0) {
        pop_front();
        return true;
    }

    //move to the node just before the one we want to delete
    Node* current = head;
    for (size_t i = 0; i < index - 1 && current->next != nullptr; ++i) {
        current = current->next;
    }

    //if we can't find the node nothing is deleted
    if (current->next == nullptr) {
        return false;
    }

    //unlink the node we’re deleting
    Node* ptr = current->next;
    current->next = current->next->next;
    delete ptr;  //delete the unwanted node
    --num_items;

    //if we deleted the last node, update tail
    if (current->next == nullptr) {
        tail = current;
    }
    return true;
}

//returns total number of nodes 
size_t LinkedList::size() const {
    return num_items;
}

//fnds index of animal name 
size_t LinkedList::find(const std::string& item) const {
    Node* current = head;
    size_t index = 0;
    while (current != nullptr) {
        if (current->data == item) { //found animal name
            return index;
        }
        current = current->next;
        ++index;
    }
    //if not found
    return num_items;
}

//vector functions

//checks if stack is empty
bool Stack::empty() {
    return data.empty();
}

//adds number to the top
void Stack::push(int value) {
    data.push_back(value);
}

//removes the number on top
void Stack::pop() {
    if (data.empty()) {
        std::cout << "Stack is empty, nothing to pop." << std::endl;
    }
    else {
        data.pop_back();
    }
}

//returns the number currently at the top
int Stack::top() {
    return data.back();
}

//finds avg of numbers in stack
double Stack::average() {
    int sum = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        sum += data[i];
    }
    return sum / data.size();
}

//prints numbers bottom to top
void Stack::print() {
    std::cout << "Stack from bottom to top: ";
    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}


//main program

int main() {
    std::string input;
    size_t position;

    // checks if list is empty
    if (animals.empty()) {
        std::cout << "The linked list is empty " << std::endl;
    }
    else {
        std::cout << "The linked list is not empty " << std::endl;
    }

    // ask user to add three animals at the front
    std::cout << "Add three animals to the list (one per input): " << std::endl;

    for (int i = 0; i < 3; i++) {
        std::getline(std::cin, input);
        std::cout << "Pushed to front of list: " << input << std::endl;
        animals.push_front(input);
    }

    animals.print_list();

    // ask user to add two animals at the back
    std::cout << "Add two more animals to the list (one per input): " << std::endl;
    for (int i = 0; i < 2; i++) {
        std::getline(std::cin, input);
        std::cout << "Pushed to back of list: " << input << std::endl;
        animals.push_back(input);
    }
    animals.print_list();

    // remove first and last animals from the list
    std::cout << "Removing animal at the front of the list: " << animals.front() << std::endl;
    animals.pop_front();

    std::cout << "Removing animal at the back of the list: " << animals.back() << std::endl;
    animals.pop_back();

    animals.print_list();

    // lets user insert a new animal at index
    std::cout << "Enter the name of an animal to insert: " << std::endl;
    std::getline(std::cin, input);

    std::cout << "Enter the index to insert the animal at: " << std::endl;
    std::cin >> position;

    animals.insert(position, input);
    animals.print_list();

    // lets user remove an animal at index
    std::cout << "Enter the index of the animal to remove: " << std::endl;
    std::cin >> position;

    if (animals.remove(position)) {
        std::cout << "Removed animal at index " << position << std::endl;
    }
    else {
        std::cout << "No animal at index " << position << std::endl;
    }
    animals.print_list();

    // lets user search for a specific animal name, returns index
    std::string target;
    std::cin.ignore(100, '\n');
    std::cout << "Enter an animal to find: ";
    std::getline(std::cin, target);

    size_t pos = animals.find(target);

    if (pos == animals.size()) {
        std::cout << target << " was not found in the list." << std::endl;
    }
    else {
        std::cout << target << " was found at index " << pos << std::endl;
    }

    // checks if list is empty
    if (animals.empty()) {
        std::cout << "The linked list is empty" << std::endl;
    }
    else {
        std::cout << "The linked list is not empty " << std::endl;
    }


    //stack

    Stack numList;
    std::cout << "Now creating a stack" << std::endl;

    //checks if stack is empty
    if (numList.empty()) {
        std::cout << "The stack is empty" << std::endl;
    }
    else {
        std::cout << "The stack is not empty" << std::endl;
    }

    //pushes 5 numbers and popping twice in a stack
    numList.push(5);
    numList.push(10);
    numList.push(15);
    numList.pop();
    numList.push(20);
    numList.push(25);
    numList.pop();
    std::cout << "Pushing 5, 10, 15, popping once, pushing 20, 25, then popping once:" << std::endl;
    numList.print();

    //shows number on top and the average of the stack
    std::cout << "Number on top: " << numList.top() << std::endl;
    std::cout << "Average: " << numList.average() << std::endl;

    //checks if the stack is empty
    if (numList.empty()) {
        std::cout << "The stack is empty" << std::endl;
    }
    else {
        std::cout << "The stack is not empty" << std::endl;
    }
}