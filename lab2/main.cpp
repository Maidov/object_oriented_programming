#include <iostream>
#include "six.h"
using namespace std;

int main(){

    try {
        Six x1 {"555"};
        Six x2 {"111"};
        cout << x1 + x2 << endl;
    } catch(std::exception &ex){
        cerr << "exception: " << ex.what() << std::endl;
    }

    return 1;
}
