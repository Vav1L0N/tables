#pragma once
#include <stdexcept>
#include <algorithm>

template <class K, class T>
class UnorderedTable {
	std::pair<K, T>* data;
	size_t size;
	size_t cap;
public:
	void resize() {
		cap *= 2;
		std::pair<K, T>* data1 = new std::pair<K, T>[cap] {};
		std::copy(data, data + size, data1);
		delete[] data;
		data = data1;
	}
	UnorderedTable() {
		size = 0;
		cap = 10;
		data = new std::pair<K, T>[cap] {};
	}
	~UnorderedTable() {
		delete[] data;
		data = nullptr;
	}
	T find(const K& key) {
		for (size_t i = 0; i < size; i++)
		{
			if (data[i].first == key) return data[i].second;
		}
		throw std::invalid_argument("The key was not found. He, probably, doesn't exist.");
	}
	void del(const K& key) {
		size_t i;
		for (i = 0; i < size; i++)
		{
			if (data[i].first == key) break;
		}
		if (size > 0) {
			size--;
			data[i] = data[size];
		};
	}
	void add(const K& key, const T& data_1) {
		for (size_t i = 0; i < size; i++)
		{
			if (data[i].first == key) throw std::invalid_argument("The element with this key already exists.");
		}
		if (size == cap) resize();
		data[size++] = std::pair<K, T>{ key,data_1 };
	}
};
