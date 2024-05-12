#pragma once
#include "stack.h"
#include <algorithm>

template <class K, class T>
class OrderedTable {
	struct Node {
		K key;
		T data;
		Node* l, * r;
		int h;
		Node(K key_, T data_, Node* l_ = nullptr, Node* r_ = nullptr, int h_ = 1) : key(key_), data(data_), l(l_), r(r_), h(h_) {};
		int diff() {
			if (l && r) return (l->h - r->h);
			if (l == nullptr && r) return -r->h;
			if (l && r == nullptr) return l->h;
			return 0;
		}
		void count_height() {
			if (l && r) h = std::max(l->h, r->h) + 1;
			else if (l == nullptr && r) h = r->h + 1;
			else  if (l && r == nullptr) h = l->h + 1;
			else h = 1;
		}
	};
	Node* head;
	void srt(Node* nd, Node* top) noexcept {
		if (top) {
			if (top->l == nd) {
				std::swap(top->l, nd->l->r);
				std::swap(top->l, nd->l);
				nd->count_height();
				top->l->count_height();
			}
			else {
				std::swap(top->r, nd->l->r);
				std::swap(top->r, nd->l);
				nd->count_height();
				top->r->count_height();
			}
		}
		else {
			std::swap(head, nd->l->r);
			std::swap(head, nd->l);
			nd->count_height();
			head->count_height();
		}
	}
	void slt(Node* nd, Node* top) noexcept {
		if (top) {
			if (top->l == nd) {
				std::swap(top->l, nd->r->l);
				std::swap(top->l, nd->r);
				nd->count_height();
				top->l->count_height();
			}
			else {
				std::swap(top->r, nd->r->l);
				std::swap(top->r, nd->r);
				nd->count_height();
				top->r->count_height();
			}
		}
		else {
			std::swap(head, nd->r->l);
			std::swap(head, nd->r);
			nd->count_height();
			head->count_height();
		}
	}
	void brt(Node* nd, Node* top) noexcept {
		slt(nd->l, nd);
		srt(nd, top);
	}
	void blt(Node* nd, Node* top) noexcept {
		srt(nd->r, nd);
		slt(nd, top);
	}
public:
	OrderedTable() {
		head = nullptr;
	}
	~OrderedTable() {
		TDynamicStack<Node*> S;
		Node* nd = head;
		S.Push(nd);
		while (!S.IsEmpty()) {
			nd = S.Pop();
			if (nd) {
				S.Push(nd->r);
				S.Push(nd->l);
				delete nd;
			}
		}
		head = nullptr;
	}
	void add(K key_, T data_) {
		if (head) {
			TDynamicStack<Node*> S;
			S.Push(nullptr);
			S.Push(head);
			while (S.Peek()) {
				if (key_ > S.Peek()->key) S.Push(S.Peek()->r);
				else if (key_ < S.Peek()->key) S.Push(S.Peek()->l);
				else throw std::invalid_argument("In this table already exist element with this key");
			}
			S.Pop();
			if (key_ > S.Peek()->key) S.Peek()->r = new Node{ key_,data_ };
			else S.Peek()->l = new Node{ key_, data_ };
			Node* nd = S.Pop();
			size_t oldh;
			while (nd) {
				oldh = nd->h;
				nd->count_height();
				if (nd->diff() == -2) {
					if (nd->r->diff() == -1) slt(nd, S.Peek());
					else blt(nd, S.Peek());
					break;
				}
				else if (nd->diff() == 2) {
					if (nd->l->diff() == 1) srt(nd, S.Peek());
					else brt(nd, S.Peek());
					break;
				}
				else if (nd->h == oldh) break;
				nd = S.Pop();
			}
		}
		else head = new Node{ key_,data_ };
	}
	T find(const K& key_) {
		Node* nd = head;
		while (nd && nd->key != key_) {
			if (key_ > nd->key) nd = nd->r;
			else nd = nd->l;
		}
		if (nd) return nd->data;
		throw std::invalid_argument("The key was not found. He, probably, doesn't exist.");
	}
	void del(const K& key_) {
		TDynamicStack<Node*> S;
		S.Push(nullptr);
		S.Push(head);
		while (S.Peek() && S.Peek()->key != key_) {
			if (key_ > S.Peek()->key) S.Push(S.Peek()->r);
			else S.Push(S.Peek()->l);
		}
		if (S.Peek()) {
			Node* nd = S.Peek();
			if (nd->r) {
				S.Push(nd->r);
				while (S.Peek()->l) {
					S.Push(S.Peek());
				}
				nd->data = S.Peek()->data;
				nd->key = S.Peek()->key;
				nd = S.Peek();
				S.Pop();
				if (S.Peek()->l == nd) S.Peek()->l = nd->r;
				else S.Peek()->r = nd->r;
				delete nd;
			}
			else {
				if (nd == head) {
					head = head->l;
					delete nd;
					return;
				}
				S.Pop();
				if (S.Peek()->l == nd) S.Peek()->l = nd->l;
				else S.Peek()->r = nd->l;
				delete nd;
			};
			nd = S.Pop();
			bool fl = true;
			size_t oldh;
			while (nd && fl) {
				oldh = nd->h;
				nd->count_height();
				if (nd->diff() == -2) {
					fl = nd->r->diff();
					if (nd->r->diff() == 0 || nd->r->diff() == -1) slt(nd, S.Peek());
					else blt(nd, S.Peek());
				}
				else if (nd->diff() == 2) {
					fl = nd->l->diff();
					if (nd->l->diff() == 0 || nd->l->diff() == 1) srt(nd, S.Peek());
					else brt(nd, S.Peek());
				}
				else if (nd->h == oldh) break;
				nd = S.Pop();
			}
		}
	}
};
