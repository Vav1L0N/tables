#pragma once
#include "Polynomial.h"
#include <vector>

class AVLTreeTable {
private:
	class Node {
	public:
		std::pair<std::string, Polynomial> data;
		Node* l;
		Node* r;
		int h = 0;
		Node(std::string name, Polynomial pol) : data(std::make_pair(name, pol)), l(nullptr), r(nullptr) {}
	};

	Node* head;

	Node* sh(std::string& name) {
		Node* cur = head;
		while (cur) {
			if (cur->data.first == name) {
				return cur;
			}
			cur = (name > cur->data.first) ? cur->r : cur->l;
		}
		throw std::logic_error("No such element in this table");
	}

	void TreeDestr(Node*& delv) {
		if (delv != nullptr) {
			TreeDestr(delv->l);
			TreeDestr(delv->r);
			delete delv;
			delv = nullptr;
		}
	}

	void seth(Node* x) {
		x->h = (x->l ? x->l->h : 0) - (x->r ? x->r->h : 0);
	}

	void rotateLeft(Node*& xparent, Node*& x) {
		bool l = (xparent && xparent->l && xparent->l == x);
		Node* y = x->r;
		x->r = y->l;
		y->l = x;
		if (!xparent) head = y;
		else (l ? xparent->l : xparent->r) = y;
		seth(x);
		seth(y);
	}

	void rotateRight(Node*& xparent, Node*& x) {
		bool l = (xparent && xparent->l && xparent->l == x);
		Node* y = x->l;
		x->l = y->r;
		y->r = x;
		if (!xparent) head = y;
		else (l ? xparent->l : xparent->r) = y;
		seth(x);
		seth(y);
	}

	void balanceTree(Node*& xparent, Node*& x, const std::vector<Node*>& path, int index) {
		if (index < 0) return;
		seth(path[index]);
		int b = balance(path[index]);
		if (b == 2) {
			if (balance(path[index]->l) >= 0) rotateRight(xparent, x);
			else rotateLeft(xparent, path[index]->l);
		}
		else if (b == -2) {
			if (balance(path[index]->r) <= 0) rotateLeft(xparent, x);
			else rotateRight(xparent, path[index]->r);
		}
		balanceTree(xparent, x, path, index - 1);
	}

public:
	AVLTreeTable() : head(nullptr) {}

	~AVLTreeTable() {
		TreeDestr(head);
	}
	std::vector<Node*> memoryfind(std::string name) {
		Node* cur = head;
		std::vector<Node*> path;
		while (cur) {
			if (cur->data.first == name) {
				path.push_back(cur);
				break;
			}
			if (name > cur->data.first) {
				path.push_back(cur);
				cur = cur->r;
			}
			else {
				path.push_back(cur);
				cur = cur->l;
			}
		}
		return path;
	};

	int balance(Node* nd) {
		if (nd->l == nullptr && nd->r == nullptr) {
			return 0;
		}
		else if (nd->l == nullptr && nd->r) {
			return -(nd->r->h + 1);
		}
		else if (nd->l && nd->r == nullptr) {
			return nd->l->h + 1;
		}
		else if (nd->l && nd->r) {
			return nd->l->h - nd->r->h;
		}
	};
	Polynomial find(std::string& name) {
		Node* cur = sh(name);
		return cur->data.second;
	}

	void add(std::string name, Polynomial pol) {
		if (!head) {
			head = new Node(name, pol);
		}
		else {
			try {
				find(name);
			}
			catch (std::logic_error& e) {
				Node* cur = head;
				std::vector<Node*> path;
				while (true) {
					path.push_back(cur);
					if (name < cur->data.first) {
						if (!cur->l) break;
						cur->h += 1;
						cur = cur->l;
					}
					else {
						if (!cur->r) break;
						cur->h += 1;
						cur = cur->r;
					}
				}
				(name < cur->data.first ? cur->l : cur->r) = new Node(name, pol);
				Node* xparent = nullptr;
				Node* x = nullptr;
				balanceTree(xparent, x, path, path.size() - 2);
			}
		}
	}

	void clear(std::string name) {
		try {
			find(name);
			std::vector<Node*> path = memoryfind(name);
			Node* cur = path[path.size() - 1];
			if (cur->r) {
				Node* delnd = cur;
				cur = cur->r;
				path.push_back(cur);
				while (cur->l) {
					cur = cur->l;
					path.push_back(cur);
				}
				Node* minval = path[path.size() - 1], * tmp = delnd;
				delnd->data = minval->data;
				minval->data = tmp->data;
				(minval->l == nullptr && minval->r == nullptr ? path[path.size() - 2]->l : minval->l ? path[path.size() - 2]->r : path[path.size() - 2]->r) = nullptr;
				delete minval;
			}
			else {
				if (path.size() == 1) head = path[0]->l;
				else (path[path.size() - 2]->l == cur ? path[path.size() - 2]->l : path[path.size() - 2]->r) = cur->l;
				delete cur;
			}
			Node* xparent = nullptr; 
			Node* x = nullptr; 
			balanceTree(xparent, x, path, path.size() - 2);
		}
		catch (std::logic_error& e) {
			return;
		}
	}
};
