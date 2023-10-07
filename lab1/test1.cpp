#include <gtest/gtest.h>
#include "funcky.h"

TEST(test_01, basic_test_set)
{
    ASSERT_TRUE(funky(2, 7) == 11);
}

TEST(test_02, basic_test_set)
{
    ASSERT_TRUE(funky(2, 2) == 1);
}

TEST(test_03, basic_test_set)
{
    ASSERT_TRUE(funky(0, 0) == 0);
}

TEST(test_04, basic_test_set)
{
    ASSERT_TRUE(funky(0, 1) == 1);
}

TEST(test_05, basic_test_set)
{
    ASSERT_TRUE(funky(2, 3) == 3);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
