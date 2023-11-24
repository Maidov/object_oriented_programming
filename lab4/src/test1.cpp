#include <iostream>
#include "point.h"
#include "array.h"
#include "hexagon.h"
#include "pentagon.h"
#include "rhombus.h"
#include <cmath>
#include <gtest/gtest.h>



TEST(test_01, create_test_set) {
    point<int> a2{1, 0}, b2{0, 5}, c2{-1, 0}, d4{0, -5};
    EXPECT_NO_THROW(Rhombus<int> (a2, b2, c2, d4));
}

TEST(test_02, create_test_set) {
    point<double> a2{1, 0}, b2{0, 5}, c2{-1, 0}, d4{0, -5};
    EXPECT_NO_THROW(Rhombus<double> (a2, b2, c2, d4));
}

TEST(test_03, create_test_set) {
    point<float> a1{9.8000000, 6.5000000}, b1{6.7732051, 12.1425626}, c1{0.3732051, 12.3425626}, d1{-3.0000000, 6.9000000}, e1{0.0267949, 1.2574374}, f1{6.4267949, 1.0574374};
    EXPECT_NO_THROW(Hexagon<float> (a1, b1, c1, d1, e1, f1));
}

TEST(test_04, create_test_set) {
    point<double> a1{9.8000000, 6.5000000}, b1{6.7732051, 12.1425626}, c1{0.3732051, 12.3425626}, d1{-3.0000000, 6.9000000}, e1{0.0267949, 1.2574374}, f1{6.4267949, 1.0574374};
    EXPECT_NO_THROW(Hexagon<double> (a1, b1, c1, d1, e1, f1));
}

TEST(test_05, create_test_set) {
    point<double> a{1.00000, 1.00000}, b{-0.64204, 1.26007}, c{-1.39680, -0.22123}, d{-0.22123, -1.39680}, e{1.26007, -0.64204};
    EXPECT_NO_THROW((Pentagon<double> (a, b, c, d, e)));
}

TEST(test_06, create_test_set) {
    point<float> a{1.00000, 1.00000}, b{-0.64204, 1.26007}, c{-1.39680, -0.22123}, d{-0.22123, -1.39680}, e{1.26007, -0.64204};
    EXPECT_NO_THROW((Pentagon<float> (a, b, c, d, e)));
}

TEST(PointOperatorEqual, SamePointEquality) {
    point<double> p1 = {1.0, 2.0};
    point<double> p2 = {1.0, 2.0};
    EXPECT_TRUE(p1 == p2);
}

TEST(PointOperatorEqual, DifferentPointsInequality) {
    point<double> p1 = {1.0, 2.0};
    point<double> p2 = {3.0, 4.0};
    EXPECT_FALSE(p1 == p2);
}

TEST(PointOperatorLess, LessThan) {
    point p1 = {1.0, 2.0};
    point p2 = {3.0, 4.0};
    EXPECT_TRUE(p1 < p2);
}

TEST(PointOperatorLess, GreaterThan) {
    point p1 = {3.0, 4.0};
    point p2 = {1.0, 2.0};
    EXPECT_FALSE(p1 < p2);
}

TEST(PointDistance, CalculatingDistance) {
    point p1 = {0.0, 0.0};
    point p2 = {3.0, 4.0};
    EXPECT_DOUBLE_EQ(Distance(p1, p2), 5.0);
}

TEST(Area, PENTAGON) {
    point<double> a{1.00000, 1.00000}, b{-0.64204, 1.26007}, c{-1.39680, -0.22123}, d{-0.22123, -1.39680}, e{1.26007, -0.64204};
    Pentagon<double> P(a, b, c, d, e);
    std::cout << double(P);
    EXPECT_TRUE(dbEqual(double(P), 4.75528));
}

TEST(Area, HEXAGON) {
    point<double> a1{9.8000000, 6.5000000}, b1{6.7732051, 12.1425626}, c1{0.3732051, 12.3425626}, d1{-3.0000000, 6.9000000}, e1{0.0267949, 1.2574374}, f1{6.4267949, 1.0574374};
    Hexagon<double> H(a1, b1, c1, d1, e1, f1);
    std::cout << double(H);
    EXPECT_TRUE(dbEqual(double(H), 106.5211246));
}

TEST(Area, RHOMBUS) {
    point<int> a2{1, 0}, b2{0, 1}, c2{-1, 0}, d2{0, -1};
    Rhombus<int> R(a2, b2, c2, d2);
    EXPECT_TRUE(dbEqual(double(R), 2.0));
}


TEST(FigureArray, AddAndRemoveFigures) {
    point<double> a{1.00000, 1.00000}, b{-0.64204, 1.26007}, c{-1.39680, -0.22123}, d{-0.22123, -1.39680}, e{1.26007, -0.64204};
    point<double> a1{9.8000000, 6.5000000}, b1{6.7732051, 12.1425626}, c1{0.3732051, 12.3425626}, d1{-3.0000000, 6.9000000}, e1{0.0267949, 1.2574374}, f1{6.4267949, 1.0574374};
    point<int> a2{1, 0}, b2{0, 5}, c2{-1, 0}, d4{0, -5};
    DynamicArray<std::shared_ptr<Figure<double>>> arrt;
    DynamicArray<std::shared_ptr<Figure<int>>> arrt2;
    std::shared_ptr<Figure<double>> figure1 = std::make_shared<Pentagon<double>>(a, b, c, d, e);
    std::shared_ptr<Figure<double>> figure2 = std::make_shared<Hexagon<double>>(a1, b1, c1, d1, e1, f1);
    std::shared_ptr<Figure<int>> figure3 = std::make_shared<Rhombus<int>>(a2, b2, c2, d4);

    arrt.pushBack(figure1);
    arrt.pushBack(figure2);
    EXPECT_EQ(arrt.getSize(), 2);   
    arrt.remove(1);
    EXPECT_EQ(arrt.getSize(), 1);
}

TEST(FigureArray, SumAreas) {
    point<double> a{1.00000, 1.00000}, b{-0.64204, 1.26007}, c{-1.39680, -0.22123}, d{-0.22123, -1.39680}, e{1.26007, -0.64204};
    point<double> a1{9.8000000, 6.5000000}, b1{6.7732051, 12.1425626}, c1{0.3732051, 12.3425626}, d1{-3.0000000, 6.9000000}, e1{0.0267949, 1.2574374}, f1{6.4267949, 1.0574374};
    point<double> a2{1, 0}, b2{0, 1}, c2{-1, 0}, d4{0, -1};
    DynamicArray<std::shared_ptr<Figure<double>>> arrt;
    std::shared_ptr<Figure<double>> figure1 = std::make_shared<Pentagon<double>>(a, b, c, d, e);
    std::shared_ptr<Figure<double>> figure2 = std::make_shared<Hexagon<double>>(a1, b1, c1, d1, e1, f1);
    std::shared_ptr<Figure<double>> figure3 = std::make_shared<Rhombus<double>>(a2, b2, c2, d4);

    arrt.pushBack(figure1);
    arrt.pushBack(figure2);
    arrt.pushBack(figure3);
    double SUM = 106.5211246 + 2 + 4.75528;
    EXPECT_TRUE(dbEqual(findSumAreas(arrt), SUM));
}



int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
    return 0;
}