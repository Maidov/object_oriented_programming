#include "funcky.h"
using namespace std;

int funky(int a, int b)
{
    int total = 0;
    for (int i = a; i < b + 1; i++)
    {
        int counter = 0;
        int num = i;
        while (num)
        {
            counter += (num % 2);
            num /= 2;
        }
        total += counter;
    }
    return total;
}