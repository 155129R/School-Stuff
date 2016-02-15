#include "gtest/gtest.h"

#include "MathUtility.h"
//***********************************************************************FACTORIAL TESTS
//Tests factorial for zero
TEST(FactorialTest, HandlesZeroInput){
    EXPECT_EQ(1, factorial(0));
}

//Tests factorial of positive numbers
TEST(FactorialTest, HandlesPositiveInput){
    EXPECT_EQ(1, factorial(1)) << "Factorial(1) error";
    EXPECT_EQ(2, factorial(2)) << "Factorial(2) error";
    EXPECT_EQ(6, factorial(3)) << "Factorial(3) error";
    EXPECT_EQ(40320, factorial(8)) <<"Factorial(8) error";
}
//Tests factorial for negative numbers
TEST(FactorialTest, HandlesNegativeInput){
    EXPECT_EQ(-1, factorial(-1))<<"Factorial(-1) error";
    EXPECT_EQ(-1, factorial(-8)) << "Factorial(-8) error";
}
//***********************************************************************nCr TESTS
//Test nCr for positive input
TEST(nCrTest, HandlesPositiveInput){
    EXPECT_EQ(10, nCr(5, 2))<<"nCr(5,2) error";
    EXPECT_EQ(210, nCr(10, 6)) <<"nCr(10,6) error";

}
//Test nCr for negative input
TEST(nCrTest, HandlesNegativeInput){
    EXPECT_EQ(0, nCr(-5, -2)) << "nCr(-5,-2) error";
    EXPECT_EQ(0, nCr(-8, -10)) << "nCr(-8,-10) error";
}
//Test nCr for n negative input
TEST(nCrTest, Handles_n_NegativeInput){
    EXPECT_EQ(0, nCr(-5, 2)) << "nCr(-5,2) error";

}

//Test nCr for r negative input
TEST(nCrTest, Handles_r_NegativeInput){
    EXPECT_EQ(0, nCr(5, -2)) << "nCr(5,-2) error";

}

//Test nCr for 0 input
TEST(nCrTest, HandlesZeroInput){
    EXPECT_EQ(1, nCr(0, 0)) << "nCr(0,0) error";

}
//Test nCr for when n is 0
TEST(nCrTest, Handles_n_ZeroInput){
    EXPECT_EQ(0, nCr(0, 5)) << "nCr(0,5) error";

}

//Test nCr for when r is 0
TEST(nCrTest, Handles_r_ZeroInput){
    EXPECT_EQ(1, nCr(5, 0)) << "nCr(5,0) error";
    EXPECT_EQ(1, nCr(10, 0)) << "nCr(10,0) error";
}
//***********************************************************************nPr TESTS
//Test nPr for Positive input
TEST(nPrTest, HandlesPositiveInput){
    EXPECT_EQ(20, nPr(5,2))<<"nPr(5,2) error";
    EXPECT_EQ(151200, nPr(10, 6)) << "nPr(10, 6) error";

}

//Test nPr for Zero input
TEST(nPrTest, HandlesZeroInput){
    EXPECT_EQ(1, nPr(0, 0)) << "nPr(0,0) error";
}

//Test nPr for n Zero input
TEST(nPrTest, Handles_n_ZeroInput){
    EXPECT_EQ(1, nPr(0, 1)) << "nPr(0,1) error";
}

//Test nPr for r Zero input
TEST(nPrTest, Handles_r_ZeroInput){
    EXPECT_EQ(1, nPr(1, 0)) << "nPr(1,0) error";
}

//Test nPr for negative input
TEST(nPrTest, HandlesNegativeInput){
    EXPECT_EQ(0, nPr(-1, -1)) << "nPr(-1,-1) error";
}

//Test nPr for n negative input
TEST(nPrTest, Handles_n_NegativeInput){
    EXPECT_EQ(0, nPr(-1, 3)) << "nPr(-1,3) error";
}

//Test nPr for r negative input
TEST(nPrTest, Handles_r_NegativeInput){
    EXPECT_EQ(0, nPr(3, -1)) << "nPr(3,-1) error";
}
//***********************************************************************nTermAP TESTS
//Test nTermAP for positive input
TEST(nTermAP, HandlesPositiveInput){
    EXPECT_EQ(49, nTermAP(1, 6, 9)) << "nTermAP(1, 6, 9) error";
    EXPECT_EQ(62, nTermAP(5, 3, 20)) << "nTermAP(5, 3, 20) error";

}

//Test nTermAP for zero input
TEST(nTermAP, HandlesZeroInput){
    EXPECT_EQ(0, nTermAP(0, 0, 0)) << "nTermAP(1, 6, 9) error";
}
//Test nTermAP for a zero input
TEST(nTermAP, Handles_a_ZeroInput){
    EXPECT_EQ(10, nTermAP(0, 5, 3)) << "nTermAP(0, 5, 3) error";
}

//Test nTermAP for d zero input
TEST(nTermAP, Handles_d_ZeroInput){
    EXPECT_EQ(5, nTermAP(5, 0, 3)) << "nTermAP(5, 0, 3) error";
}

//Test nTermAP for n zero input
TEST(nTermAP, Handles_n_ZeroInput){
    EXPECT_EQ(2, nTermAP(5, 3, 0)) << "nTermAP(5, 3, 0) error";
}

//Test nTermAP for negative
TEST(nTermAP, HandlesNegativeInput){
    EXPECT_EQ(6, nTermAP(-3, -3, -2)) << "nTermAP(-3, -3, -2) error";
}

//Test nTermAP for a negative
TEST(nTermAP, Handles_a_NegativeInput){
    EXPECT_EQ(9, nTermAP(-3, 3, 5)) << "nTermAP(-3, 3, 5) error";
}

//Test nTermAP for n negative
TEST(nTermAP, Handles_n_NegativeInput){
    EXPECT_EQ(-15, nTermAP(3, 3, -5)) << "nTermAP(3, 3, -5) error";
}

//Test nTermAP for d negative
TEST(nTermAP, Handles_d_NegativeInput){
    EXPECT_EQ(-9, nTermAP(3, -3, 5)) << "nTermAP(3, -3, 5) error";
}

//***********************************************************************summationAP TESTS
//Test summationAP for positive input
TEST(summationAP, HandlesPositiveInput){
    EXPECT_EQ(225, summationAP(1, 6, 9))<<"summationAP(1, 6, 9) error";

}

//Test summationAP for zero input
TEST(summationAP, HandlesZeroInput){
    EXPECT_EQ(0, summationAP(0, 0, 0)) << "summationAP(0, 0, 0) error";

}

//Test summationAP for a zero input
TEST(summationAP, Handles_a_ZeroInput){
    EXPECT_EQ(216, summationAP(0, 6, 9)) << "summationAP(0, 6, 9) error";

}

//Test summationAP for a zero input
TEST(summationAP, Handles_d_ZeroInput){
    EXPECT_EQ(9, summationAP(1, 0, 9)) << "summationAP(1, 0, 9) error";

}

//Test summationAP for a zero input
TEST(summationAP, Handles_n_ZeroInput){
    EXPECT_EQ(0, summationAP(1, 6, 0)) << "summationAP(1, 6, 0) error";

}

//Test summationAP for negative input
TEST(summationAP, HandlesNegativeInput){
    EXPECT_EQ(-261, summationAP(-1, -6, -9)) << "summationAP(-1, -6, -9) error";

}

//Test summationAP for a negative input
TEST(summationAP, Handles_a_NegativeInput){
    EXPECT_EQ(207, summationAP(-1, 6, 9)) << "summationAP(-1, 6, 9) error";

}

//Test summationAP for d negative input
TEST(summationAP, Handles_d_NegativeInput){
    EXPECT_EQ(-207, summationAP(1, -6, 9)) << "summationAP(1, -6, 9) error";

}

//Test summationAP for n negative input
TEST(summationAP, Handles_n_NegativeInput){
    EXPECT_EQ(261, summationAP(1, 6, -9)) << "summationAP(1, 6, -9) error";

}

//***********************************************************************nTermGP TESTS
//Test nTermGP for positive input
TEST(nTermGP, HandlesPositiveInput){
    EXPECT_EQ(16, nTermGP(1, 2, 5)) << "nTermGP(1, 2, 5) error";

}
//Test nTermGP for Zero input
TEST(nTermGP, HandlesZeroInput){
    EXPECT_EQ(0, nTermGP(0, 0, 0)) << "nTermGP(0, 0, 0) error";

}

//Test nTermGP for a Zero input
TEST(nTermGP, Handles_a_ZeroInput){
    EXPECT_EQ(0, nTermGP(0, 2, 5)) << "nTermGP(0, 2, 5) error";

}

//Test nTermGP for r Zero input
TEST(nTermGP, Handles_r_ZeroInput){
    EXPECT_EQ(0, nTermGP(1, 0, 5)) << "nTermGP(1, 0, 5) error";

}

//Test nTermGP for n Zero input
TEST(nTermGP, Handles_n_ZeroInput){
    EXPECT_EQ(0, nTermGP(1, 2, 0)) << "nTermGP(1, 2, 0) error";
}

//Test nTermGP for negative input
TEST(nTermGP, HandlesNegativeInput){
    EXPECT_EQ(0, nTermGP(-1, -2, -9)) << "nTermGP(-1, -2, -9) error";
}

//Test nTermGP for a negative input
TEST(nTermGP, Handles_a_NegativeInput){
    EXPECT_EQ(-256, nTermGP(-1, 2, 9)) << "nTermGP(-1, 2, 9) error";
}

//Test nTermGP for r negative input
TEST(nTermGP, Handles_r_NegativeInput){
    EXPECT_EQ(256, nTermGP(1, -2, 9)) << "nTermGP(1, -2, 9) error";
}

//Test nTermGP for n negative input
TEST(nTermGP, Handles_n_NegativeInput){
    EXPECT_EQ(0, nTermGP(1, 2, -9)) << "nTermGP(1, 2, -9) error";
}
//***********************************************************************summationGP TESTS
//Test summationGP for negative input
TEST(summationGP, HandlesPositiveInput){
    EXPECT_EQ(511, summationGP(1, 2, 9)) << "summationGP(1, 2, 9) error";
}

//Test summationGP for negative input
TEST(summationGP, HandlesNegativeInput){
    EXPECT_EQ(0, summationGP(-1, -2, -9)) << "summationGP(-1, -2, -9) error";
}

//Test summationGP for a negative input
TEST(summationGP, Handles_a_NegativeInput){
    EXPECT_EQ(-511, summationGP(-1, 2, 9)) << "summationGP(-1, 2, 9) error";
}

//Test summationGP for r negative input
TEST(summationGP, Handles_r_NegativeInput){
    EXPECT_EQ(171, summationGP(1, -2, 9)) << "summationGP(1, -2, 9) error";
}

//Test summationGP for n negative input
TEST(summationGP, Handles_n_NegativeInput){
    EXPECT_EQ(-1, summationGP(1, 2, -9)) << "summationGP(1, 2, -9) error";
}

//Test summationGP for negative input
TEST(summationGP, HandlesZeroInput){
    EXPECT_EQ(0, summationGP(0, 0, 0)) << "summationGP(0, 0, 0) error";
}

//Test summationGP for a negative input
TEST(summationGP, Handles_a_ZeroInput){
    EXPECT_EQ(0, summationGP(0, 2, 9)) << "summationGP(0, 2, 9) error";
}

//Test summationGP for r negative input
TEST(summationGP, Handles_r_ZeroInput){
    EXPECT_EQ(1, summationGP(1, 0, 9)) << "summationGP(1, 0, 9) error";
}

//Test summationGP for n negative input
TEST(summationGP, Handles_n_ZeroInput){
    EXPECT_EQ(0, summationGP(1, 2, 0)) << "summationGP(1, 2, 0) error";
}