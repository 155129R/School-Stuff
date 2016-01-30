#include "gtest/gtest.h"

#include "Vector2.h"
#include "MyMath.h"

TEST(Vector2Test, Constructor){
    Vector2 v1;
    EXPECT_NEAR(0, v1.x, Math::EPSILON);
    EXPECT_NEAR(0, v1.y, Math::EPSILON);
}