#pragma once
#include<iostream>
using namespace std;
template<class T>

class list
{
private:
	struct Node 
	{
		T data = T();
		Node* next = nullptr;
	};

	size_t sz;
	Node* head;
	Node* tail;

public:
	list() 
	{
		sz = 0;
		head = new Node;
		tail = head;
	}

	list(const list& other) 
	{
		sz = other.sz;
		head = new Node;
		Node* cur = head;
		Node* tmp = other.head;
		while (tmp->next!=nullptr) 
		{
			cur->next = new Node{ tmp->next->data,nullptr };
			cur = cur->next;
			tmp = tmp->next;
		}
		tail = cur;
	}

	~list() 
	{
		Node* cur = head;
		Node* tmp;
		while (cur->next != nullptr) 
		{
			tmp = cur->next;
			delete cur;
			cur = tmp;
		}
	}

	list& operator =(const list& other)
	{
		if (this == &other) 
		{
			return *this;
		}
		sz = other.sz;
		Node* cur = head;
		Node* tmp;
		while (cur->next != nullptr) 
		{
			tmp = cur->next;
			delete cur;
			cur = tmp;
		}
		head = new Node;
		cur = head;
		tmp = other.head;
		while (tmp->next!=nullptr) 
		{
			cur->next = new Node{ tmp->next->data,nullptr };
			cur = cur->next;
			tmp = tmp->next;
		}
		tail = cur;
		return *this;
	}

	const size_t size() const 
	{
		return sz;
	}

	const bool isEmpty() const 
	{
		return !sz;
	}

	void push(const T elem) 
	{
		Node* cur = head;
		Node* tmp = new Node;
		tmp->data = elem;
		bool isTail = true;
		while (cur->next != nullptr) 
		{
			if (cur->next->data < elem) 
			{
				isTail = false;
				break;
			}
			cur = cur->next;
		}
		tmp->next = cur->next;
		cur->next = tmp;
		if (isTail) {
			tail = tmp;
		}
		sz++;
	}

	void pop(size_t ind) 
	{
		if (ind >= sz) 
		{
			throw out_of_range("index bigger the size!");
		}
		sz--;
		Node* cur = head;
		for (size_t i = 0; i < ind; i++) 
		{
			cur = cur->next;
		}
		Node* next = cur->next;
		if (next == tail) 
		{
			delete next;
			cur->next = nullptr;
			tail = cur;
			return;
		}
		cur->next = next->next;
		delete next;
	}

	

	T& operator[](size_t ind) 
	{
		Node* cur = head->next;
		while (ind != 0 && cur->next != nullptr) 
		{
			cur = cur->next;
			ind--;
		}
		return cur->data;
	}
	T& at(size_t ind)
	{
		if (ind >= sz)
		{
			throw out_of_range("index bigger then size!");
		}
		return this->operator[](ind);
	}

	bool operator ==(const list& other) const
	{
		Node* cur = head;
		Node* oth = other.head;
		while (cur->next != nullptr) 
		{
			if ((oth->next == nullptr) || (cur->data != oth->data))
			{
				return false;
			}
			cur=cur->next;
			oth=oth->next;
		}
		return true;
	}

	bool operator !=(const list& other) const 
	{
		return !(this==other);
	}

	class iterator 
	{
	private:
		Node* cur;
	public:
		iterator(Node* node) { cur = node; }
		iterator(const iterator& other) { cur = other.cur; }
		T& operator * () { return cur->data; }
		bool operator ==(iterator s) { return cur == s.cur; }
		bool operator != (iterator s) { return cur != s.cur; }
		iterator& operator ++() 
		{
			cur = cur->next;
			return *this;
		}
		iterator& operator ++(int) 
		{
			cur = cur->next;
			return *this;
		}
	};

	iterator begin() const 
	{
		return iterator(head->next);
	}
	iterator end() const 
	{
		return iterator(nullptr);
	}
};
