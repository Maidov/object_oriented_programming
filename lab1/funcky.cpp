#include <iostream>
#include <cmath>

int countSetBits(int n) {
    int count = 0;
    while (n > 0) {
        n = n & (n - 1);
        count++;
    }
    return count;
}

int count1From0to(int n) {
    if (n > 0){
        int firstPower = std::log2(n);
        int digits = firstPower + 1;
        int left_piece = n - pow(2, firstPower);
        n -= (left_piece + 1);
        
        int power = std::log2(n);
        int count = (pow(2, power + 1)/2)*(power + 1);
        return count + 1 + left_piece + count1From0to(left_piece);
    } else {
        return 0;
    }
}

int funky(int b, int a){
    return count1From0to(a) - count1From0to(b) + countSetBits(b);
}
