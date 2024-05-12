#pragma once
#include "Polynomial.h"
#include <algorithm>
#include <stdexcept>

class HashTable {
	std::pair<short int, std::pair<std::string, Polynomial>>* data;
	/*short int is the status of an element, which indicates the status of that element in the table. In this case, the following values are used:
0 (null) - the element is empty (does not contain data).
1 (deleted) - the item has been deleted, but the cell is still in use.
2 (contented) - the element contains data.*/

	size_t cap, q;

	size_t hash(const std::string& s) const noexcept {
		size_t res = 0;
		for (size_t i = 0; i < s.size(); i++) {
			res += size_t(s[i]) * (i + 1);
		}
		return res % cap;
	};

	void rebuild() {
		std::pair<short int, std::pair<std::string, Polynomial>>* data1 = new std::pair<short int, std::pair<std::string, Polynomial>> [cap * 2 + 1] {};
		size_t tmp = cap;
		cap *= 2;
		cap++;
		q *= 2;
		std::swap(data, data1);
		for (size_t i = 0; i < tmp; i++) {
			add(data1[i].second);
		}
		delete[] data1;
	};

public:
	HashTable() {
		cap = 10;
		q = 2;
		data = new std::pair<short int, std::pair<std::string, Polynomial>>[cap] {};
	};

	~HashTable() {
		delete[] data;
		data = nullptr;
	};

	void add(const std::pair<std::string, Polynomial>& p) {
		add(p.first, p.second);
	};

	void del(const std::string& s) {
		size_t h = hash(s);
		do {
			if (data[h].second.first == s && data[h].first == 2) {
				data[h].first = 1;
				return;
			}
			else h = (h + q) % cap;
		} while (h != hash(s) && data[h].first);
	};

	Polynomial find(const std::string& s) {
		size_t h = hash(s);
		do {
			if (data[h].second.first == s && data[h].first == 2) return data[h].second.second;
			else h = (h + q) % cap;
		} while (h != hash(s) && data[h].first);
		throw std::invalid_argument("The key was not found. He, probably, doesn't exist.");
	};

	void add(const std::string& s, const Polynomial& P) {
		try {
			find(s);
		}
		catch (std::exception& e) {
			size_t h = hash(s);
			while (data[h].first == 2) {
				do {
					h = (h + q) % cap;
				} while (data[h].first == 2 && h != hash(s));
				if (data[h].first == 2 && h == hash(s)) {
					rebuild();
					h = hash(s);
				};
			};
			data[h] = std::pair<short int, std::pair<std::string, Polynomial>>(2, std::pair<std::string, Polynomial>(s, P));
			return;
		}
		throw std::invalid_argument("The element with this key already exists.");
	};

};