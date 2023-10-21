#include <iostream>
#include "src/helper.cpp"
#include "fcollection.h"
#include "figure.h"
#include "hexagon.h"
#include "pentagon.h"
#include "rhombus.h"
using namespace std;

// OPTION 21
// Romb -- 5ti ugolnik -- 6ti ugolnik

int main(){

    try {
        point b {1, 0};
        point c {50, 1};
        Rhombus A(c, b, 0.5);
        point a0, a1, a2, a3, a4, a5;

        // cout << A.getGCenter();

        a0 = A.getDots()[0];
        a1 = A.getDots()[1];
        a2 = A.getDots()[2];
        a3 = A.getDots()[3];
        // a4 = A.getDots()[4];
        // a5 = A.getDots()[5];
        // a5.x = A.getDots()[5].x;
        Rhombus B({a0, a1, a2, a3});
        cout << dbEqual(0, distance(B.getGCenter(), A.getGCenter()));

    } catch(std::exception &ex){
        cerr << "exception: " << ex.what() << std::endl;
    }

    return 1;
}
