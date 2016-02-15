#include "gtest/gtest.h"

#include "Vector2.h"
#include "MyMath.h"

TEST(Vector2Test, Constructor)
{
    Vector2 v1(2,2);
    EXPECT_NEAR(2, v1.x, Math::EPSILON);
    EXPECT_NEAR(2, v1.y, Math::EPSILON);
}

TEST(Vector2Test, CopyConstructor)
{
    Vector2 v1(5, 5);
    Vector2 v2(v1);
    EXPECT_NEAR(v1.x, v2.x, Math::EPSILON);
    EXPECT_NEAR(v1.y, v2.y, Math::EPSILON);
}

TEST(Vector2Test, Set)
{
    Vector2 v1(5, 4);

    EXPECT_NEAR(5, v1.x, Math::EPSILON);
    EXPECT_NEAR(4, v1.y, Math::EPSILON);
}

TEST(Vector2Test, OperatorAddition)
{
    Vector2 v1;
    Vector2 v2;
    v2 = v1 + Vector2(5, 6);

    EXPECT_NEAR(v1.x + 5, v2.x, Math::EPSILON);
    EXPECT_NEAR(v1.y + 6, v2.y, Math::EPSILON);
}

TEST(Vector2Test, OperatorSubtraction)
{
    Vector2 v1;
    Vector2 v2;
    v2 = v1 - Vector2(5, 6);

    EXPECT_NEAR(v1.x - 5, v2.x, Math::EPSILON);
    EXPECT_NEAR(v1.y - 6, v2.y, Math::EPSILON);
}

TEST(Vector2Test, OperatorSubtraction_void)
{
    Vector2 v1(6, 7);
    v1 = -v1;
    EXPECT_NEAR(-6, v1.x, Math::EPSILON);
    EXPECT_NEAR(-7, v1.y, Math::EPSILON);

}

TEST(Vector2Test, OperationMultiply)
{
    Vector2 v1(3, 2);
    v1 = v1 * 2;
    EXPECT_NEAR(6, v1.x, Math::EPSILON);
    EXPECT_NEAR(4, v1.y, Math::EPSILON);

}

TEST(Vector2Test, OperationLength)
{
    Vector2 v1(4, 3);
    EXPECT_NEAR(5, v1.Length(), Math::EPSILON);
}

TEST(Vector2Test, OperationDot)
{
    Vector2 v1(6, 5);
    Vector2 v2(4, 2);
    EXPECT_EQ(34, v1.Dot(v2));
}

TEST(Vector2Test, Normalized)
{
    Vector2 v1(4, 5);
    v1 = v1.Normalized();
    EXPECT_NEAR(0.62469, v1.x, Math::EPSILON);
    EXPECT_NEAR(0.78086, v1.y, Math::EPSILON);

}