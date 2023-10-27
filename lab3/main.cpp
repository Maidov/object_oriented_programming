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
        point center1{0, 0}, center2{3.4, 6.7}, center3{123, 456};
        point dot1{1, 1}, dot2{9.8, 6.5}, dot3{987, 321};
        Pentagon P(center1, dot1);
        Hexagon H(center2, dot2);
        Rhombus R(center3, dot3, 0.123);

        Pentagon Pinput;
        Hexagon Hinput;
        Rhombus Rinput;

        cout << " V Pentagon for your input V\n";
        cout << P;
        cout << "Or just copy this: 1.00000 1.00000 -0.64204 1.26007 -1.39680 -0.22123 -0.22123 -1.39680 1.26007 -0.64204\n";
        cout << "Input dots: ";
        cin >> Pinput;
        cout << "Equal Figures: " << (P == Pinput) << "\n";
        cout << "Wanna skip other inputs? (Y/N)\n";
        char c;
        cin >> c;
        if (c == 'Y'){
            Hinput = H;
            Rinput = R;
        } else {
            cout << " V Hexagon for your input V\n";
            cout << H;
            cout << "Or just copy this: 9.8000000 6.5000000 6.7732051 12.1425626 0.3732051 12.3425626 -3.0000000 6.9000000 0.0267949 1.2574374 6.4267949 1.0574374\n";
            cout << "Input dots: ";
            cin >> Hinput;

            cout << " V Rhombus for your input V\n";
            cout << R;
            cout << "Or just copy this: 987 321 139.605 562.272 -741 591 106.395 349.728\n";
            cout << "Input dots: ";
            cin >> Rinput;
        }

        FigureCollection FC;
        FC.pushBack(&Pinput);
        FC.pushBack(&Hinput);
        FC.pushBack(&Rinput);

        FC.displayGCenters();
        cout << "\n";
        FC.displayAreas();
        cout << "\n";
        cout << "SUM AREA = " << FC.getAllArea();
        cout << "\n";
        cout << FC;



    } catch(std::exception &ex){
        cerr << "exception: " << ex.what() << std::endl;
    }

    return 1;
}
