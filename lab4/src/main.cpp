#include <iostream>
#include "point.h"
#include "array.h"
#include "hexagon.h"
#include "pentagon.h"
#include "rhombus.h"
#include <cmath>

using namespace std;


int main() {
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
    arrt2.pushBack(figure3);
    cout << arrt;
    cout << arrt2;
}

