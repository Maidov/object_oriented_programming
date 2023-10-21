#include "include/point.h"
#include "include/figure.h"
#include "include/rhombus.h"
#include "include/pentagon.h"
#include "include/hexagon.h"
#include "include/fcollection.h"
#include "src/helper.cpp"
#include "src/point.cpp"
#include "src/figure.cpp"
#include "src/rhombus.cpp"
#include "src/pentagon.cpp"
#include "src/hexagon.cpp"
#include "src/fcollection.cpp"
#include <gtest/gtest.h>

/*
        ______________________________________________
        |-------------| POINT |-----------------|   +
        |---------------------------------------|-----
        |  default constructor                  |   +
        |  constructor from db db               |   +
        |  operator==                           |   +
        |  operator+=                           |   +
        |  operator=                            |   +
        |  double value check                   |   +
        |_______________________________________|_____
        |------------| PENTAGON |---------------|   +   
        |---------------------------------------|-----
        |  constructor from all dots            |   +
        |----|  exeptions                       |   + 
        |  size                                 |   +
        |  getTag                               |   +
        |  getGCenter                           |   +
        |  operator Double                      |   +
        |  operator==                           |   +
        |  operator= copy                       |   +
        |  operator= move                       |   +
        |_______________________________________|_____
        |-------------| HEXAGON |---------------|   +
        |---------------------------------------|-----
        |  constructor from all dots            |   +
        |----|  exeptions                       |   +
        |  size                                 |   +
        |  getTag                               |   +
        |  getGCenter                           |   +
        |  operator Double                      |   +
        |  operator==                           |   +
        |  operator= copy                       |   +
        |  operator= move                       |   +
        |_______________________________________|_____
        |-------------| RHOMBUS |---------------|
        |---------------------------------------|-----
        |  constructor from all dots            |
        |----|  exeptions                       |
        |  size                                 |
        |  getTag                               |
        |  getGCenter                           |
        |  operator Double                      |
        |----|  exeptions                       |
        |  operator==                           |
        |----|  exeptions                       |
        |  operator= copy                       |
        |----|  exeptions                       |
        |  operator= move                       |
        |----|  exeptions                       |
        |_______________________________________|_____
        |----------| F-COLLECTION |-------------|
        |---------------------------------------|-----
        |  constructor from all dots            |
        |----|  exeptions                       |
        |  size                                 |
        |  getTag                               |
        |_______________________________________|
*/

TEST(POINT, defaultConstructor)
{
    point a;
    point b{0, 0};
    EXPECT_TRUE(a == b);
}

TEST(POINT, II_IntConstructor)
{
    point b{4, 5};
    EXPECT_TRUE(((b.x == 4) && (b.y == 5)));
}

TEST(POINT, operatorEqual)
{
    point a{2, 2};
    point b{1, 1};
    EXPECT_TRUE(!(a == b));
}

TEST(POINT, operatorEqual2)
{
    point a{1, 0};
    point b{0, 1};
    EXPECT_TRUE(!(a == b));
}

TEST(POINT, operatorEqual3)
{
    point a{55, 2};
    point b{55, 2};
    EXPECT_TRUE((a == b));
}

TEST(POINT, operatorNotEqual)
{
    point a{2, 2};
    point b{1, 1};
    EXPECT_TRUE((a != b));
}

TEST(POINT, operatorNotEqual2)
{
    point a{1, 0};
    point b{0, 1};
    EXPECT_TRUE((a != b));
}

TEST(POINT, operatorNotEqual3)
{
    point a{55, 2};
    point b{55, 2};
    EXPECT_TRUE(!(a != b));
}

TEST(POINT, operatorCopy)
{
    point a{55, 2};
    point b{11, 4};
    b = a;
    EXPECT_TRUE(b == a);
}

TEST(POINT, doubleValue)
{
    point a{55.12345, 2.12345};
    point b{55.12345678, 2.12345788};
    EXPECT_TRUE(a == b);
}

TEST(POINT, doubleValue1)
{
    point a{55.12345, 2.12345};
    point b{55.12346678, 2.12345788};
    EXPECT_TRUE(a != b);
}

TEST(PENTAGON, AllDotsConstructor)
{
    int flag = 0;
    double a1x = 100, a1y = 80, a2x = -30, a2y = -50;
    point b0, b1, b2, b3, b4;
    for (int i = 0; i < 40; i++)
    {
        a1x -= i;
        a2x += i;
        a1y += i;
        a2y -= i;
        point center{a1x, a1y}, dot{a2x, a2y};
        Pentagon A(center, dot);
        b0 = A.getDots()[0];
        b1 = A.getDots()[1];
        b2 = A.getDots()[2];
        b3 = A.getDots()[3];
        b4 = A.getDots()[4];
        try
        {
            Pentagon B0({b0, b1, b2, b3, b4});
            Pentagon B1({b1, b2, b3, b4, b0});
            Pentagon B2({b2, b3, b4, b0, b1});
            Pentagon B3({b3, b4, b0, b1, b2});
            Pentagon B4({b4, b0, b1, b2, b3});
        }
        catch(const std::underflow_error& e)
        {
            flag += 1;
            break;
        }
    }

    EXPECT_TRUE(flag == 0);
}

TEST(PENTAGON, ZeroAreaFigure)
{
    point b0{1234, 456};

    EXPECT_THROW(Pentagon A({b0, b0, b0, b0, b0}), std::underflow_error);
}

TEST(PENTAGON, WrongDotsOrder)
{
    point b0, b1, b2, b3, b4;
    point center{12, 34}, dot{-56, -78};
    Pentagon A(center, dot);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];

    EXPECT_THROW(Pentagon A({b1, b0, b2, b3, b4}), std::underflow_error);
}

TEST(PENTAGON, WrongDots)
{
    point b0, b1, b2, b3, b4;
    point center{12, 34}, dot{-56, -78};
    Pentagon A(center, dot);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];
    b4.x += 1;

    EXPECT_THROW(Pentagon A({b0, b1, b2, b3, b4}), std::underflow_error);
}

TEST(PENTAGON, tag)
{
    point b0, b1, b2, b3, b4;
    point center{12, 34}, dot{-56, -78};
    Pentagon A(center, dot);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];
    Pentagon B({b0, b1, b2, b3, b4});

    EXPECT_TRUE(B.getTag() == "PENTAGON");
}

TEST(PENTAGON, GCenter)
{
    point b0, b1, b2, b3, b4;
    point center{12, 34}, dot{-56, -78};
    Pentagon A(center, dot);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];
    Pentagon B({b0, b1, b2, b3, b4});

    EXPECT_TRUE(dbEqual(distance(B.getGCenter(), center), 0));
}


TEST(PENTAGON, operatorDouble_Aka_AREA)
{
    point b0, b1, b2, b3, b4;
    point center{12, 34}, dot{56, 78};
    Pentagon A(center, dot);
    double TrueArea =  5 * pow(distance(center, dot), 2) * sin((2*M_PI)/5) * 0.5;
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];
    Pentagon B({b0, b1, b2, b3, b4});
    EXPECT_TRUE(dbEqual(TrueArea, double(B)));
}

TEST(PENTAGON, operatorEqualTrue)
{
    int flag = 0;
    double a1x = 123, a1y = 45, a2x = -67, a2y = -89;
    point b0, b1, b2, b3, b4;
    for (int i = 0; i < 66; i++)
    {
        a1x -= i;
        a2x += i;
        a1y += i;
        a2y -= i;
        point center{a1x, a1y}, dot{a2x, a2y};
        Pentagon A(center, dot);
        b0 = A.getDots()[0];
        b1 = A.getDots()[1];
        b2 = A.getDots()[2];
        b3 = A.getDots()[3];
        b4 = A.getDots()[4];

        Pentagon B0({b0, b1, b2, b3, b4});
        Pentagon B1({b1, b2, b3, b4, b0});
        Pentagon B2({b2, b3, b4, b0, b1});
        Pentagon B3({b3, b4, b0, b1, b2});
        Pentagon B4({b4, b0, b1, b2, b3});

        if (!((B0 == A) &&
              (B1 == A) &&
              (B2 == A) &&
              (B3 == A) &&
              (B4 == A) &&
              (B0 == B1) &&
              (B1 == B2) &&
              (B2 == B3) &&
              (B3 == B4) &&
              (B4 == B0) &&
              (B0 == B0))) {
                flag += 1;
                break;
              }

    }
    EXPECT_TRUE(flag == 0);
}

TEST(PENTAGON, operatorEqualTrue2)
{
    int flag = 0;
    point b0, b1, b2, b3, b4;
    point c0, c1, c2, c3, c4;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{0, 1};
    Pentagon A1(center1, dot1);
    Pentagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    Pentagon B({b0, b1, b2, b3, b4});
    Pentagon C({c0, c1, c2, c3, c4});
    EXPECT_TRUE(C == B);
}

TEST(PENTAGON, operatorEqualFalse)
{
    int flag = 0;
    point b0, b1, b2, b3, b4;
    point c0, c1, c2, c3, c4;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{0, 1.05};
    Pentagon A1(center1, dot1);
    Pentagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    Pentagon B({b0, b1, b2, b3, b4});
    Pentagon C({c0, c1, c2, c3, c4});
    EXPECT_TRUE(!(C == B));
}

TEST(PENTAGON, operatorEqualFalse2)
{
    int flag = 0;
    point b0, b1, b2, b3, b4;
    point c0, c1, c2, c3, c4, c5;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{1, 0};
    Pentagon A1(center1, dot1);
    Hexagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    c5 = A2.getDots()[5];
    Pentagon B({b0, b1, b2, b3, b4});
    Hexagon C({c0, c1, c2, c3, c4, c5});
    EXPECT_TRUE(!(C == B));
}

TEST(PENTAGON, operatorCopy)
{
    int flag = 0;
    point b0, b1, b2, b3, b4;
    point c0, c1, c2, c3, c4, c5;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{5, 0};
    Pentagon A1(center1, dot1);
    Pentagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    c5 = A2.getDots()[5];
    Pentagon B({b0, b1, b2, b3, b4});
    Pentagon C({c0, c1, c2, c3, c4});
    Pentagon D({c0, c1, c2, c3, c4});
    C = B;

    EXPECT_TRUE(((!(B == D)) && (B == C)));
}

TEST(PENTAGON, operatorMove)
{
    int flag = 0;
    point b0, b1, b2, b3, b4;
    point c0, c1, c2, c3, c4, c5;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{5, 0};
    Pentagon A1(center1, dot1);
    Pentagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    c5 = A2.getDots()[5];
    Pentagon B({b0, b1, b2, b3, b4});
    Pentagon C({c0, c1, c2, c3, c4});
    Pentagon D({c0, c1, c2, c3, c4});
    B = std::move(C);

    EXPECT_TRUE(B == D);
}

TEST(HEXAGON, AllDotsConstructor)
{
    int flag = 0;
    double a1x = 100, a1y = 80, a2x = -30, a2y = -50;
    point b0, b1, b2, b3, b4, b5;
    for (int i = 0; i < 40; i++)
    {
        a1x -= i;
        a2x += i;
        a1y += i;
        a2y -= i;
        point center{a1x, a1y}, dot{a2x, a2y};
        Hexagon A(center, dot);
        b0 = A.getDots()[0];
        b1 = A.getDots()[1];
        b2 = A.getDots()[2];
        b3 = A.getDots()[3];
        b4 = A.getDots()[4];
        b5 = A.getDots()[5];
        try
        {
            Hexagon B0({b0, b1, b2, b3, b4, b5});
            Hexagon B1({b1, b2, b3, b4, b5, b0});
            Hexagon B2({b2, b3, b4, b5, b0, b1});
            Hexagon B3({b3, b4, b5, b0, b1, b2});
            Hexagon B4({b4, b5, b0, b1, b2, b3});
            Hexagon B4({b5, b0, b1, b2, b3, b4});
        }
        catch(const std::underflow_error& e)
        {
            flag += 1;
            break;
        }
    }

    EXPECT_TRUE(flag == 0);
}

TEST(HEXAGON, ZeroAreaFigure)
{
    point b0{1234, 456};

    EXPECT_THROW(Hexagon A({b0, b0, b0, b0, b0, b0}), std::underflow_error);
}

TEST(HEXAGON, WrongDotsOrder)
{
    point b0, b1, b2, b3, b4, b5;
    point center{12, 34}, dot{-56, -78};
    Hexagon A(center, dot);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];
    b5 = A.getDots()[5];

    EXPECT_THROW(Hexagon A({b1, b0, b2, b3, b4, b5}), std::underflow_error);
}

TEST(HEXAGON, WrongDots)
{
    point b0, b1, b2, b3, b4, b5;
    point center{12, 34}, dot{-56, -78};
    Hexagon A(center, dot);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];
    b5 = A.getDots()[5];
    b4.x += 1;

    EXPECT_THROW(Hexagon A({b0, b1, b2, b3, b4, b5}), std::underflow_error);
}

TEST(HEXAGON, tag)
{
    point b0, b1, b2, b3, b4, b5;
    point center{12, 34}, dot{-56, -78};
    Hexagon A(center, dot);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];
    Hexagon B({b0, b1, b2, b3, b4, b5});

    EXPECT_TRUE(B.getTag() == "PENTAGON");
}

TEST(HEXAGON, GCenter)
{
    point b0, b1, b2, b3, b4, b5;
    point center{12, 34}, dot{-56, -78};
    Hexagon A(center, dot);
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];
    b5 = A.getDots()[5];
    Hexagon B({b0, b1, b2, b3, b4, b5});

    EXPECT_TRUE(dbEqual(distance(B.getGCenter(), center), 0));
}


TEST(HEXAGON, operatorDouble_Aka_AREA)
{
    point b0, b1, b2, b3, b4, b5;
    point center{12, 34}, dot{56, 78};
    Hexagon A(center, dot);
    double TrueArea =  5 * pow(distance(center, dot), 2) * sin((2*M_PI)/5) * 0.5;
    b0 = A.getDots()[0];
    b1 = A.getDots()[1];
    b2 = A.getDots()[2];
    b3 = A.getDots()[3];
    b4 = A.getDots()[4];
    b5 = A.getDots()[5];
    Hexagon B({b0, b1, b2, b3, b4, b5});
    EXPECT_TRUE(dbEqual(TrueArea, double(B)));
}

TEST(HEXAGON, operatorEqualTrue)
{
    int flag = 0;
    double a1x = 123, a1y = 45, a2x = -67, a2y = -89;
    point b0, b1, b2, b3, b4, b5;
    for (int i = 0; i < 66; i++)
    {
        a1x -= i;
        a2x += i;
        a1y += i;
        a2y -= i;
        point center{a1x, a1y}, dot{a2x, a2y};
        Hexagon A(center, dot);
        b0 = A.getDots()[0];
        b1 = A.getDots()[1];
        b2 = A.getDots()[2];
        b3 = A.getDots()[3];
        b4 = A.getDots()[4];
        b5 = A.getDots()[5];

        Hexagon B0({b0, b1, b2, b3, b4, b5});
        Hexagon B1({b1, b2, b3, b4, b5, b0});
        Hexagon B2({b2, b3, b4, b5, b0, b1});
        Hexagon B3({b3, b4, b5, b0, b1, b2});
        Hexagon B4({b4, b5, b0, b1, b2, b3});
        Hexagon B5({b5, b0, b1, b2, b3, b4});

        if (!((B0 == A) &&
              (B1 == A) &&
              (B2 == A) &&
              (B3 == A) &&
              (B4 == A) &&
              (B5 == A) &&
              (B0 == B1) &&
              (B1 == B2) &&
              (B2 == B3) &&
              (B3 == B4) &&
              (B4 == B5) &&
              (B5 == B0) &&
              (B0 == B0))) {
                flag += 1;
                break;
              }

    }
    EXPECT_TRUE(flag == 0);
}

TEST(HEXAGON, operatorEqualTrue2)
{
    int flag = 0;
    point b0, b1, b2, b3, b4, b5;
    point c0, c1, c2, c3, c4, c5;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{0, 1};
    Hexagon A1(center1, dot1);
    Hexagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];
    b5 = A1.getDots()[5];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    c5 = A2.getDots()[5];
    Hexagon B({b0, b1, b2, b3, b4, b5});
    Hexagon C({c0, c1, c2, c3, c4, c5});
    EXPECT_TRUE(C == B);
}

TEST(HEXAGON, operatorEqualFalse)
{
    int flag = 0;
    point b0, b1, b2, b3, b4, b5;
    point c0, c1, c2, c3, c4, c5;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{0, 1.05};
    Hexagon A1(center1, dot1);
    Hexagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];
    b5 = A1.getDots()[5];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    c5 = A2.getDots()[5];
    Hexagon B({b0, b1, b2, b3, b4, b5});
    Hexagon C({c0, c1, c2, c3, c4, c5});
    EXPECT_TRUE(!(C == B));
}

TEST(HEXAGON, operatorEqualFalse2)
{
    int flag = 0;
    point b0, b1, b2, b3, b4;
    point c0, c1, c2, c3, c4, c5;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{1, 0};
    Hexagon A1(center1, dot1);
    Pentagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    c5 = A2.getDots()[5];
    Pentagon B({b0, b1, b2, b3, b4});
    Hexagon C({c0, c1, c2, c3, c4, c5});
    EXPECT_TRUE(!(C == B));
}

TEST(HEXAGON, operatorCopy)
{
    int flag = 0;
    point b0, b1, b2, b3, b4, b5;
    point c0, c1, c2, c3, c4, c5;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{5, 0};
    Hexagon A1(center1, dot1);
    Hexagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];
    b5 = A1.getDots()[5];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    c5 = A2.getDots()[5];
    Hexagon B({b0, b1, b2, b3, b4, b5});
    Hexagon C({c0, c1, c2, c3, c4, c5});
    Hexagon D({c0, c1, c2, c3, c4, c5});
    C = B;

    EXPECT_TRUE(((!(B == D)) && (B == C)));
}

TEST(HEXAGON, operatorMove)
{
    int flag = 0;
    point b0, b1, b2, b3, b4, b5;
    point c0, c1, c2, c3, c4, c5;
    point center1{0, 0}, dot1{1, 0};
    point center2{0, 0}, dot2{5, 0};
    Hexagon A1(center1, dot1);
    Hexagon A2(center2, dot2);
    b0 = A1.getDots()[0];
    b1 = A1.getDots()[1];
    b2 = A1.getDots()[2];
    b3 = A1.getDots()[3];
    b4 = A1.getDots()[4];
    b5 = A1.getDots()[5];

    c0 = A2.getDots()[0];
    c1 = A2.getDots()[1];
    c2 = A2.getDots()[2];
    c3 = A2.getDots()[3];
    c4 = A2.getDots()[4];
    c5 = A2.getDots()[5];
    Hexagon B({b0, b1, b2, b3, b4, b5});
    Hexagon C({c0, c1, c2, c3, c4, c5});
    Hexagon D({c0, c1, c2, c3, c4, c5});
    B = std::move(C);

    EXPECT_TRUE(B == D);
}














int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
