#include <iostream>
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
        point a {1, 3};
        point b {5, 0};
        point c {99, 100};
        Rhombus A(a, b, 0.5);
        Pentagon C(a, b);
        Pentagon D(a, c);
        point a0, a1, a2, a3, a4, a5;

        cout << A;

        a0.x = A.getDots()[0].x;
        a1.x = A.getDots()[1].x;
        a2.x = A.getDots()[2].x;
        a3.x = A.getDots()[3].x;
        // a4.x = A.getDots()[4].x;
        // a5.x = A.getDots()[5].x;
        
        a0.y = A.getDots()[0].y;
        a1.y = A.getDots()[1].y;
        a2.y = A.getDots()[2].y;
        a3.y = A.getDots()[3].y;
        // a4.y = A.getDots()[4].y;
        // a5.y = A.getDots()[5].y;

        Rhombus B{a2, a1, a0, a3};
        
        FigureCollection array;
        array.pushBack(&B);
        array.pushBack(&D);
        array.pushBack(&C);
        array.pushBack(&A);

        cout << "\n\nGREAT VERTICAL PRINT\n\n";
        cout << array;
        cout << "\n\nGREAT AFTER PRINT\n\n";
        array.remove(1);
        cout << "\n\nGO\n\n";
        cout << array;

    } catch(std::exception &ex){
        cerr << "exception: " << ex.what() << std::endl;
    }

    return 1;
}
