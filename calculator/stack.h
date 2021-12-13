#ifndef STACK_H
#define STACK_H
#include <iostream>
using namespace std;
template <class T>
class Stack
{
private:
	class elem
	{
	public:
		elem(T data, elem* next = NULL) :data(data), next(next) {}
		~elem() = default;
		void setNext(elem* newnext) { next = newnext; }
		elem* getNext() { return next; }
		T getData() { return data; }
	private:
		T data;
		elem* next;
	};

	elem* head;
public:
	Stack() {
		head = NULL;
	};

	~Stack() {
		while (!empty())
		{
			pop();
		}
	};

	void pop() {//delete
		if (empty())
		{
			throw out_of_range("No more elements");
		}
		else
		{
			elem* tmp = head;
			head = head->getNext();
			delete tmp;
		}
	};

	void push(T data) {//add
		elem* tmp = new elem(data);
		elem* cur = head;
		head = tmp;
		head->setNext(cur);

	};

	bool empty() {
		return head == nullptr;
	};

	T top() {//first element
		if (empty())
		{
			throw out_of_range("Empty");
		}
		else
		{
			return head->getData();
		}

	};
};

#endif