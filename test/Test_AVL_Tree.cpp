#include "gtest.h"
#include "AVL-Tree.h"
using namespace std;

TEST(AVLTreeTable, can_create_table) {
	ASSERT_NO_THROW(AVLTreeTable T);
}
TEST(AVLTreeTable, can_copy_table) {
	AVLTreeTable T;
	ASSERT_NO_THROW(AVLTreeTable T1(T));
}
TEST(AVLTreeTable, can_add_an_element) {
	AVLTreeTable T;
	ASSERT_NO_THROW(T.add("pol", Polynomial("1+x+x^2")););
}
TEST(AVLTreeTable, can_find_an_element) {
	string str = "pol";
	AVLTreeTable T;
	T.add("pol", Polynomial("1+x+x^2"));
	ASSERT_NO_THROW(T.find(str));
}
TEST(AVLTreeTable, copy_table_have_own_memory) {
	string str = "pol";
	AVLTreeTable T;
	AVLTreeTable T1(T);
	T1.add("pol", Polynomial("1+x+x^2"));
	ASSERT_ANY_THROW(T.find(str));
}
TEST(AVLTreeTable, search_and_add_are_correct) {
	string str = "pol";
	Polynomial P("1+x+x^2");
	AVLTreeTable T;
	T.add("pol", P);
	EXPECT_EQ(T.find(str).repr(), P.repr());
}
TEST(AVLTreeTable, can_clear) {
	AVLTreeTable T;
	T.add("pol", Polynomial("1+x+x^2"));
	ASSERT_NO_THROW(T.clear("pol"));
}
TEST(AVLTreeTable, clear_is_correct) {
	string str = "pol";
	AVLTreeTable T;
	T.add("pol", Polynomial("1+x+x^2"));
	T.clear("pol");
	ASSERT_ANY_THROW(T.find(str));
}
