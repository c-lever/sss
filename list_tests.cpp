#include <iostream>
#include <list>
#include <gtest/gtest.h>

TEST(List, Success) {
    std::list<int> TestedList;
    const size_t expected_empty_list_size = 0;
    ASSERT_EQ(TestedList.size(), expected_empty_list_size);

    const int push_backed_value = 10;
    const int expected_list_size = 1;
    TestedList.push_back(push_backed_value);
    
    ASSERT_FALSE(TestedList.empty());
    ASSERT_EQ(TestedList.size(), expected_list_size);

    ASSERT_EQ(TestedList.front(), push_backed_value); 
}

TEST(List, ChekingPushBack) {
    std::list<int> TestedList;
    const size_t WrongListSize = 2;
    const size_t CorrectListSize = 0;

    ASSERT_EQ(TestedList.size(), CorrectListSize);

    TestedList.push_back(10);
    ASSERT_FALSE(TestedList.empty());
    ASSERT_EQ(TestedList.size(), 1);
}

TEST(List, CheckingPop) {
    std::list<char> TestedList;
    const char N_Letter = 'N';
    const char M_Letter = 'M';
    TestedList.push_back(N_Letter);
    ASSERT_EQ(TestedList.size(), 1);
    TestedList.pop_back();
    ASSERT_TRUE(TestedList.empty());

    TestedList.push_back(M_Letter);
    ASSERT_FALSE(TestedList.empty());
    ASSERT_EQ(TestedList.size(), 1);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}