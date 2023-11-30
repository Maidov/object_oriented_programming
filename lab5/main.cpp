#include "array.h"
#include "allocator.h"
#include <map>
#include <vector>
#include <algorithm>
#include <time.h>

int fact(int dig) {
    int res = 1;
    
    for (int i = 1; i <= dig; ++i) {
        res *= i; 
    }

    return res;
}



bool has(std::map<int, int, std::less<int>, PoolAllocator<std::pair<const int, int>>>& m, int element){
    if (m.find(element) != m.end()) return true;
    return false;
}

const int get_random_from(int a, int b){
    return (rand() % (b - a + 1)) + a;
}

int main()
{
    std::srand(time(NULL));
    const size_t initialSize = get_random_from(10000, 20000);
    const size_t elementsToRemove = get_random_from(1000, 9000);
    const size_t additionalElements = get_random_from(1000, 9000);

    std::map<int, int, std::less<int>, PoolAllocator<std::pair<const int, int>>> m;
    for (size_t i = 0; i < 10; ++i) {
        m[i] = fact(i);
    }

    for (const auto &p : m) {
        std::cout << "Key: " << p.first << " Value: " << p.second << '\n';
    }

    std::cout << "\tSTART\n";

    std::map<int, int, std::less<int>, PoolAllocator<std::pair<const int, int>>> test_map;
    for (size_t i = 0; i < initialSize; ++i) {
        test_map[i] = i;
    }
    std::cout << "Map size after initial insertion: " << test_map.size() << std::endl;
    // In map now [1 ... InitialSize]
    // Elem: 10k ~ 20k 

    std::cout << elementsToRemove << " elements will be removed" << std::endl;
    for (size_t i = 0; i < elementsToRemove; ++i) {
        test_map.erase(i);
    }
    std::cout << "Map size after removal: " << test_map.size() << std::endl;
    // In map now [elementsToRemove ... InitialSize]
    // Elem: 1k ~ 19k
    // elementsToRemove: 1k ~ 9k
    // InitialSize: 10k ~ 20k

    std::cout << "Trying to add " << additionalElements << " elements" << std::endl;
    int addCounter = 0;
    int passCouter = 0;
    for (size_t i = 0; i < additionalElements; ++i) {
        if (has(test_map, i)) {
            passCouter += 1;
        }
        else{
            addCounter += 1;
            test_map[i] = i;
        }
    }
    std::cout << "Map size after additional insertion: " << test_map.size() << std::endl;
    std::cout << "Added " << addCounter << " elements" << std::endl;
    std::cout << passCouter << " elements were already in map and were skipped" << std::endl;
    std::cout << "Add elements to the end of number series based on number of skipped elements" << std::endl;
    for (size_t i = initialSize + 1; i < initialSize + passCouter + 1; i++)
    {
        test_map[i] = i;
    }
    std::cout << "Map finale size: " << test_map.size() << std::endl;

    
    std::cout << "\tEND\n";
}