// declarations.h

#ifndef DECLARATIONS_H_
#define DECLARATIONS_H_
#include <stdexcept>
#include <string>
#include <cstddef>
#include <vector> 

struct Node {

	std::string data;
	Node* next;

	Node(const std::string& data_item, Node* next_ptr = nullptr) : data(data_item), next(next_ptr) {}
};

class LinkedList {
private:
	Node* head;
	Node* tail;
	int num_items;

public:
	LinkedList() : head(nullptr), tail(nullptr), num_items(0) {}

	size_t find(const std::string& item) const;
	size_t size() const;

	void print_list() const;
	void push_front(const std::string& item);
	void push_back(const std::string& item);
	void pop_front();
	void pop_back();
	void insert(size_t index, const std::string& item);
	bool remove(size_t index);

	const std::string& front() const;
	const std::string& back() const;
	bool empty() const;
};

class Stack {
private:
	std::vector<int> data;

public:
	bool empty();
	void push(int value);
	void pop();
	int top();
	double average();
	void print();
};

#endif