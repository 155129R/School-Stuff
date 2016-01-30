#include "gtest/gtest.h"

#include "MathUtility.h"

//Tests factorial for zero
TEST(FactorialTest, HandlesZeroInput){
    EXPECT_EQ(1, factorial(0));
}

//Tests factorial of positive numbers/
TEST(FactorialTest, HandlesPositiveInput){
    EXPECT_EQ(1, factorial(1));
    EXPECT_EQ(2, factorial(2));
    EXPECT_EQ(6, factorial(3));
    EXPECT_EQ(40320, factorial(8)) <<"Factorial(8) error";
}