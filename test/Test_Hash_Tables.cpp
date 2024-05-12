#include "gtest.h"
#include "Hash-Table.h"
#include "Polynomial.h"
#include <string>

TEST(HashTable, can_create_hash_table) {
	ASSERT_NO_THROW(HashTable T);
}

TEST(HashTable, can_add_an_element) {
	HashTable T;
	ASSERT_NO_THROW(T.add("pol", Polynomial("1+x+x^2")));
}

TEST(HashTable, can_find_an_element) {
	HashTable T;
	T.add("pol", Polynomial("1+x+x^2"));
	ASSERT_NO_THROW(T.find("pol"));
}

TEST(HashTable, throws_when_cant_find_an_element) {
	HashTable T;
	ASSERT_ANY_THROW(T.find("pol"));
}

TEST(HashTable, find_correct_element) {
	HashTable T;
	Polynomial p = Polynomial("1+x+x^2");
	T.add("pol", p);
	EXPECT_EQ(p.repr(), T.find("pol").repr());
}

TEST(HashTable, can_delete) {
	HashTable T;
	Polynomial p = Polynomial("1+x+x^2");
	T.add("pol", p);
	ASSERT_NO_THROW(T.del("pol"));
}

TEST(HashTable, delete_is_correct) {
	HashTable T;
	Polynomial p = Polynomial("1+x+x^2");
	T.add("pol", p);
	T.del("pol");
	ASSERT_ANY_THROW(T.find("pol"));
}