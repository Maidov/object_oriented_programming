#include "include/six.h"

#include <gtest/gtest.h>

/*
STANDART:
---| constructors
Default constructor               | +
Fill constructor                  | +
Initializer list constructor      | +
Copy string constructor           | +
Copy constructor                  | +
Move constructor                  | +
---| operators
operator=                         | +
operator==                        | +
operator>                         | +
operator<                         | +
operator+                         | +
operator-     +exceptions         | +
operator+=                        | +
operator-=    +exceptions         | +

EXTRA:
Initializing with leading zeros   | +
*/



TEST(test_01, defaultConstructor)
{
    Six x;
    std::string s;
    x.convertToString(s);
    EXPECT_TRUE(s == "");
}

TEST(test_01, fillConstructor)
{
    Six x(3, '5');
    std::string s;
    x.convertToString(s);
    EXPECT_TRUE(s == "555");
}

TEST(test_01, fillConstructor2)
{
    Six x(1, '1');
    std::string s;
    x.convertToString(s);
    EXPECT_TRUE(s == "1");
}


TEST(test_01, thorwFillConstructor)
{
    ASSERT_THROW(Six x(1, '6'), std::underflow_error);
}

TEST(test_01, initializerListConstructor)
{
    Six x{'1', '2', '3', '4', '5'};
    std::string s;
    x.convertToString(s);
    EXPECT_TRUE(s == "12345");
}

TEST(test_01, initializerListConstructor2)
{
    Six x{'3'};
    std::string s;
    x.convertToString(s);
    EXPECT_TRUE(s == "3");
}

TEST(test_01, throwInitializerListConstructor)
{
    
    ASSERT_THROW(Six x{'6'}, std::underflow_error);
}


TEST(test_01, copyStringConstructor)
{
    Six x("54321");
    std::string s;
    x.convertToString(s);
    EXPECT_TRUE(s == "54321");
}

TEST(test_01, throwCopyStringConstructor)
{    
    EXPECT_THROW(Six x("666"), std::underflow_error);
}

TEST(test_01, copyConstructor)
{
    Six x{"1250"};
    Six x2(x);
    std::string s;
    x2.convertToString(s);
    EXPECT_TRUE(s == "1250");
}

TEST(test_01, moveConstructor)
{
    Six x1{"12"};
    Six x2{"13"};
    Six x3(x1 + x2);
    std::string s;
    x3.convertToString(s);
    EXPECT_TRUE(s == "25");
}


TEST(test_02, operator_assignment)
{
    Six x1 {"12345"};
    Six x2;
    x2 = x1;
    std::string s1, s2;
    x1.convertToString(s1);
    x2.convertToString(s2);

    EXPECT_TRUE(s1 == s2);
}

TEST(test_02, operator_equal)
{
    Six x1{"12345"};
    Six x2{'1', '2', '3', '4', '5'};

    EXPECT_TRUE((x2 == x1) and (x1 == x2));
}

TEST(test_02, operator_equal2) // Different length
{
    Six x1 {'1', '0'};
    Six x2 {'1', '0', '0'};

    ASSERT_TRUE(((x1 == x2) == false) and ((x2 == x1) == false));
}

TEST(test_02, operator_equal3) // Different value and same length
{
    Six x1 {"12345"};
    Six x2 {"22345"};

    ASSERT_TRUE(((x1 == x2) == false) and ((x2 == x1) == false));
}

TEST(test_02, operator_more)
{
    Six x1 {"321"};
    Six x2 {"322"};

    ASSERT_TRUE(((x2 > x1) == true) and ((x1 > x2) == false));
}

TEST(test_02, operator_more2)
{
    Six x1 {"555"};
    Six x2 {"555"};

    ASSERT_TRUE(((x2 > x1) == false) and ((x1 > x2) == false));
}

TEST(test_02, operator_more3)
{
    Six x1 {"1234444"};
    Six x2 {"12344444"};

    ASSERT_TRUE(((x2 > x1) == true) and ((x1 > x2) == false));
}

TEST(test_02, operator_less)
{
    Six x1 {"321"};
    Six x2 {"322"};

    ASSERT_TRUE(((x2 < x1) == false) and ((x1 < x2) == true));
}

TEST(test_02, operator_less2)
{
    Six x1 {"555"};
    Six x2 {"555"};

    ASSERT_TRUE(((x2 < x1) == false) and ((x1 < x2) == false));
}

TEST(test_02, operator_less3)
{
    Six x1 {"1234444"};
    Six x2 {"12344444"};

    ASSERT_TRUE(((x2 < x1) == false) and ((x1 < x2) == true));
}

TEST(test_02, operator_plus)
{
    Six x1 {'1', '3', '2'};
    Six x2 {'1', '2', '4'};
    Six x3 {"300"};

    ASSERT_TRUE(((x1 + x2) == x3) and ((x2 + x1) == x3));
}

TEST(test_02, operator_plus2)
{
    Six x1 {"100000001"};
    Six x2 {"112345001"};
    Six x3 {"212345002"};

    ASSERT_TRUE(((x1 + x2) == x3) and ((x2 + x1) == x3));
}

TEST(test_02, operator_plus3)
{
    Six x1 {"1"};
    Six x2 {"12345"};
    Six x3 {"12350"};

    ASSERT_TRUE(((x1 + x2) == x3) and ((x2 + x1) == x3));
}

TEST(test_02, operator_plus4)
{
    Six x1 {"1"};
    Six x2 {"55555"};
    Six x3 {"100000"};

    ASSERT_TRUE(((x1 + x2) == x3) and ((x2 + x1) == x3));
}

TEST(test_02, operator_plus5)
{
    Six x1 {"5"};
    Six x2 {"10000"};
    Six x3 {"10005"};

    ASSERT_TRUE(((x1 + x2) == x3) and ((x2 + x1) == x3));
}

TEST(test_02, operator_plus6)
{
    Six x1 {'0'};
    Six x2 {"10000"};
    Six x3 {"10000"};

    ASSERT_TRUE(((x1 + x2) == x3) and ((x2 + x1) == x3));
}


TEST(test_02, operator_addition_with_assigment)
{
    Six x1 {'1', '0', '0', '5'};
    Six x2 {'1', '1', '2', '0'};
    Six x3 = x1 + x2;
    x1 += x2;

    ASSERT_TRUE((x1 == x3));
}

TEST(test_02, operator_addition_with_assigment2)
{
    Six x1 {'1'};
    Six x2 {'2'};
    Six x3 = x1 + x2;
    x1 += x2;

    ASSERT_TRUE((x1 == x3));
}

TEST(test_02, operator_addition_with_assigment3)
{
    Six x1 {"12345"};
    Six x2 {"54321"};
    Six x3 = x1 + x2;
    x1 += x2;

    ASSERT_TRUE((x1 == x3));
}

TEST(test_02, operator_addition_with_assigment4)
{
    Six x1 {"12"};
    Six x2 {"345"};
    Six x3 = x1 + x2;
    x1 += x2;

    ASSERT_TRUE((x1 == x3));
}

TEST(test_02, operator_addition_with_assigment5)
{
    Six x1 {"5555"};
    Six x2 {"1"};
    Six x3 = x1 + x2;
    x1 += x2;

    ASSERT_TRUE((x1 == x3));
}

TEST(test_02, operator_addition_with_assigment6)
{
    Six x1 {"5555"};
    Six x2 {"0"};
    Six x3 = x1 + x2;
    x1 += x2;

    ASSERT_TRUE((x1 == x3));
}

TEST(test_02, operator_addition_with_assigment7)
{
    Six x1 {"0"};
    Six x2 {"5555"};
    Six x3 = x1 + x2;
    x1 += x2;

    ASSERT_TRUE((x1 == x3));
}

TEST(test_02, operator_minus)
{
    Six x1 {"5555"};
    Six x2 {"1234"};
    Six x3 {"4321"};

    ASSERT_TRUE((x1 - x2) == x3);
}

TEST(test_02, operator_minus2)
{
    Six x1 {"1234"};
    Six x2 {"1115"};
    Six x3 {"115"};

    ASSERT_TRUE((x1 - x2) == x3);
}

TEST(test_02, operator_minus3)
{
    Six x1 {"10000"};
    Six x2 {"1"};
    Six x3 {"5555"};

    ASSERT_TRUE((x1 - x2) == x3);
}

TEST(test_02, operator_minus4)
{
    Six x1 {"10000"};
    Six x2 {"0"};
    Six x3 {"10000"};

    ASSERT_TRUE((x1 - x2) == x3);
}

TEST(test_02, operator_minus5)
{
    Six x1 {"10000"};
    Six x2 {"10000"};
    Six x3 {"0"};

    ASSERT_TRUE((x1 - x2) == x3);
}

TEST(test_02, operator_minus6)
{
    Six x1 {"5000"};
    Six x2 {"10000"};

    EXPECT_THROW(x1 - x2, std::underflow_error);
}

TEST(test_02, operator_minus7)
{
    Six x1 {"50000"};
    Six x2 {"50005"};

    EXPECT_THROW(x1 - x2, std::underflow_error);
}


TEST(test_02, operator_substruction_with_assignment)
{
    Six x1 {"5555"};
    Six x2 {"1234"};
    Six x3 = x1 - x2;

    ASSERT_TRUE((x1 -= x2) == x3);
}

TEST(test_02, ooperator_substruction_with_assignment2)
{
    Six x1 {"1234"};
    Six x2 {"1115"};
    Six x3 = x1 - x2;

    ASSERT_TRUE((x1 -= x2) == x3);
}

TEST(test_02, operator_substruction_with_assignment3)
{
    Six x1 {"10000"};
    Six x2 {"1"};
    Six x3 = x1 - x2;

    ASSERT_TRUE((x1 -= x2) == x3);
}

TEST(test_02, operator_substruction_with_assignment4)
{
    Six x1 {"10000"};
    Six x2 {"0"};
    Six x3 = x1 - x2;

    ASSERT_TRUE((x1 -= x2) == x3);
}

TEST(test_02, operator_substruction_with_assignment5)
{
    Six x1 {"10000"};
    Six x2 {"10000"};
    Six x3 = x1 - x2;

    ASSERT_TRUE((x1 -= x2) == x3);
}

TEST(test_02, operator_substruction_with_assignment6)
{
    Six x1 {"5000"};
    Six x2 {"10000"};

    EXPECT_THROW(x1 -= x2, std::underflow_error);
}

TEST(test_02, operator_substruction_with_assignment7)
{
    Six x1 {"50000"};
    Six x2 {"50005"};

    EXPECT_THROW(x1 -= x2, std::underflow_error);
}

TEST(test_03, LeadingZeros_fillConstructor)
{
    Six x(6, '0');
    std::string s;
    x.convertToString(s);
    EXPECT_TRUE(s == "0");
}

TEST(test_03, LeadingZeros_initializerListConstructor)
{
    Six x{'0', '0', '1', '2', '3', '4', '0', '5'};
    std::string s;
    x.convertToString(s);
    EXPECT_TRUE(s == "123405");
}

TEST(test_03, LeadingZeros_copyStringConstructor)
{
    Six x("00054300021000");
    std::string s;
    x.convertToString(s);
    EXPECT_TRUE(s == "54300021000");
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
