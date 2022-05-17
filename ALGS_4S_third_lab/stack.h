#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <typename first_typename>

class Stack
{
private:
	// class Node for stack element storage
	class Node
	{
	public:
		first_typename value;
		Node* prev;
		Node(const first_typename element) :value(element), prev(0) {}
	};
	Node* current;
	size_t size_stack;
public:
	// Consrtructor of stack
	Stack() :current(0), size_stack(0) {}

	// Desrtructor of stack
	~Stack()
	{
		while (current)
			pop();
	}

	// add element to the stack
	void push(const first_typename element)
	{
		Node* temp = current;
		current = new Node(element);
		current->prev = temp;
		size_stack++;
	}

	// remove top element from the stack
	void pop()
	{
		if (size_stack) {
			Node* temp = current->prev;
			delete current;
			current = temp;
			size_stack--;
		}
		else {
			throw out_of_range("stack is empty");
		}
	}

	// get the element on the top of the stack
	first_typename top()
	{
		return current->value;
	}

	// check the stack's empty
	bool empty()
	{
		return !size_stack;
	}

	// get the size of the stack
	size_t size()
	{
		return size_stack;
	}
};


#endif