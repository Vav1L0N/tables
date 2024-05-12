#include "gtest.h"
#include "UnorderedTable.h"
#include "Polynomial.h"
#include <string>


TEST(UnorderedTable, can_add_an_element) {
	UnorderedTable<std::string, Polynomial> T;
	ASSERT_NO_THROW(T.add("pol", Polynomial("1+x+x^2")));
}

TEST(UnorderedTable, can_find_an_element) {
	UnorderedTable<std::string, Polynomial> T;
	T.add("pol", Polynomial("1+x+x^2"));
	ASSERT_NO_THROW(T.find("pol"));
}

TEST(UnorderedTable, throws_when_cant_find_an_element) {
	UnorderedTable<std::string, Polynomial> T;
	ASSERT_ANY_THROW(T.find("pol"));
}

TEST(UnorderedTable, find_correct_element) {
	UnorderedTable<std::string, Polynomial> T;
	Polynomial p("1+x+x^2");
	T.add("pol", p);
	EXPECT_EQ(p.repr(), T.find("pol").repr());
}

TEST(UnorderedTable, can_delete_element) {
	UnorderedTable<std::string, Polynomial> T;
	Polynomial p = Polynomial("1+x+x^2");
	T.add("pol", p);
	ASSERT_NO_THROW(T.del("pol"));
}

TEST(UnorderedTable, delete_is_correct) {
	UnorderedTable<std::string, Polynomial> T;
	Polynomial p = Polynomial("1+x+x^2");
	T.add("pol", p);
	T.del("pol");
	ASSERT_ANY_THROW(T.find("pol"));
}