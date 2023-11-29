#include "array.h"
#include "allocator.h"
#include <map>
#include <vector>
#include <algorithm>

int fact(int dig) {
    int res = 1;
    
    for (int i = 1; i <= dig; ++i) {
        res *= i; 
    }

    return res;
}

int main() {



    // Используем Vector с аллокатором MyAllocator
    Vector<int> myVec;
    const int g = 5;
    for (size_t i = 0; i < 10; ++i) {
        myVec.push_back(g);
    }


    for (auto it = myVec.begin(); it != myVec.end(); it++){
        std::cout << *it << "\n";
    }

    std::cout << "\n";

    std::map<int, int, std::less<int>, PoolAllocator<std::pair<const int, int>>> test;
    for (size_t i = 0; i < 10; ++i) {
        test[i] = fact(i);
    }

    for (const auto &p : test) {
        std::cout << "Key: " << p.first << " Value: " << p.second << '\n';
    }




    // Используем функцию std::copy, ожидающую forward-итераторы
    std::vector<int> destination;
    std::copy(myVec.begin(), myVec.end(), std::back_inserter(destination));
    // Выводим элементы из нового контейнера
    std::cout << "Copied elements: \n";
    for (const auto& element : destination) {
        std::cout << element << " --\n";
    }
    std::cout << std::endl;

    std::cout << "\n";
    std::cout << *std::find(myVec.begin(), myVec.end(), 6);
    return 0;
}
