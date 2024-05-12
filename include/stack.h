#pragma once
#include <iostream>
#include "gtest.h"
using namespace std;

template<typename T>
class TDynamicStack
{
	int top;
	size_t memSize;
	T* pMem;
public:

	TDynamicStack(size_t _memSize = 1) :top(-1), memSize(_memSize), pMem(nullptr) {
		if (memSize <= 0) throw invalid_argument("Size should be greater than 0");
		pMem = new T[memSize]();
	}

	TDynamicStack(TDynamicStack& stack) {
		top = stack.top;
		memSize = stack.memSize;
		pMem = new T[memSize];
		for (int i = 0; i < top + 1; i++) {
			pMem[i] = stack.pMem[i];
		}
	}

	~TDynamicStack() { delete[] pMem; }

	size_t size() const { return top + 1; }

	bool IsEmpty() const { return top == -1; }

	bool IsFull() const { return top == memSize - 1; }

	T Pop() {
		if (IsEmpty()) {
			throw out_of_range("Stack is empty");
		}
		return pMem[top--];
	}

	void Push(const T& val) {
		if (top == memSize - 1) {
			T* tmpMem = new T[memSize * 2];
			copy(pMem, pMem + memSize, tmpMem);
			delete[] pMem;
			pMem = tmpMem;
			memSize *= 2;
		}
		pMem[++top] = val;
	}

	T Peek() const {
		if (IsEmpty()) {
			throw out_of_range("Stack is empty");
		}
		return pMem[top];
	}

	int getmemSize()
	{
		return memSize;
	}
};