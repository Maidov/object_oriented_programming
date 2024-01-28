#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <random>
#include "battlefield.h"

int holyRand() {
    // Используем генератор случайных чисел и распределение
    static std::random_device rd;  // Инициализация генератора случайных чисел
    static std::mt19937 gen(rd());  // Инициализация Mersenne Twister генератора
    static std::uniform_int_distribution<int> distribution(1, 1000);  // Равномерное распределение от 1 до 100
    return distribution(gen);  // Генерация случайного числа
}

int main() {
   
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    std::shared_ptr<ObserverBattlefieldOstream> obsO = std::make_shared<ObserverBattlefieldOstream>();
    btf->attachObs(obsO);
    btf->fillRandomly(16,16,18);
    btf->battle();

}   