#include "gtest.h"
#include "OrderedTable.h"
#include "Polynomial.h"
#include <string>

TEST(OrderedTable, can_add_an_element) {
	OrderedTable<std::string, Polynomial> T;
	ASSERT_NO_THROW(T.add("pol", Polynomial("1+x+x^2")));
}

TEST(OrderedTable, can_find_an_element) {
	OrderedTable<std::string, Polynomial> T;
	T.add("pol", Polynomial("1+x+x^2"));
	ASSERT_NO_THROW(T.find("pol"));
}

TEST(OrderedTable, throws_when_cant_find_an_element) {
	OrderedTable<std::string, Polynomial> T;
	ASSERT_ANY_THROW(T.find("pol"));
}

TEST(OrderedTable, find_correct_element) {
	OrderedTable<std::string, Polynomial> T;
	Polynomial p = Polynomial("1+x+x^2");
	T.add("pol", p);
	EXPECT_EQ(p.repr(), T.find("pol").repr());
}

TEST(OrderedTable, can_delete_element) {
	OrderedTable<std::string, Polynomial> T;
	Polynomial p = Polynomial("1+x+x^2");
	T.add("pol", p);
	ASSERT_NO_THROW(T.del("pol"));
}

TEST(OrderedTable, delete_is_correct) {
	OrderedTable<std::string, Polynomial> T;
	Polynomial p = Polynomial("1+x+x^2");
	T.add("pol", p);
	T.del("pol");
	ASSERT_ANY_THROW(T.find("pol"));
}