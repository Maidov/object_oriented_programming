#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <random>
#include "battlefield.h"

// PROTOTYPE GLOBAL

// std::mutex Mutex;
// struct checker{
//     std::string phase = "NULL";
//     std::map<std::string, bool> old_state;
//     std::map<std::string, bool> save_state;
// };
// auto now() { return std::chrono::steady_clock::now(); }
// auto awake_time()
// {
//     using std::chrono::operator""ms;
//     return now() + 1000ms;
// }


int holyRand() {
    // Используем генератор случайных чисел и распределение
    static std::random_device rd;  // Инициализация генератора случайных чисел
    static std::mt19937 gen(rd());  // Инициализация Mersenne Twister генератора
    static std::uniform_int_distribution<int> distribution(1, 1000);  // Равномерное распределение от 1 до 100
    return distribution(gen);  // Генерация случайного числа
}

int main() {
    // OLD MAIN

    // File i/o
    // std::ifstream file("123.txt");
    // std::ofstream file1("out.txt");
    // std::shared_ptr<DruidFactory> fD = std::make_shared<DruidFactory>();
    // std::shared_ptr<NPC> druid = fD->create("coolDroo",10,20);
    // druid->save(file1);
    // //main
    // std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    // btf->fillRandomly(time(NULL), 3,6,9);
    // std::shared_ptr<ObserverBattlefieldOstream> obsO = std::make_shared<ObserverBattlefieldOstream>();
    // std::shared_ptr<ObserverBattlefieldFile> obsF = std::make_shared<ObserverBattlefieldFile>();
    // btf->attachObs(obsF);
    // btf->attachObs(obsO);
    // for (int i = 0; i < 5; i++)
    // {
    //     btf->battle(3,50);
    //     btf->removeDeadmen();
    //     std::cout << *btf;
    // }
    
    // PROTOTYPE (with non-specified classes (auto))
    
    // std::map<std::string, bool> state{{"moved", false}, {"fighted", false}, {"done", false}, {"finish", false}};
    // auto awake = awake_time();
    // auto start_time = std::chrono::steady_clock::now();
    // std::vector<checker> v;
    // auto lambdaMove = [](std::vector<checker> &v, std::map<std::string, bool> &state, std::chrono::_V2::steady_clock::time_point &awake)
    // {
    //     while (!state["finish"]){
    //         std::lock_guard<std::mutex> lock(Mutex);
    //         if ((state["moved"] == false) && (state["finish"] == false)){
    //             auto old = state;
    //             awake = awake_time();
    //             state["moved"] = true;
    //             state["done"] = false;
    //             checker new_check{"move", old, state};
    //             v.push_back(new_check);
    //         }
    //     }
    // };
    // auto lambdaFight = [](std::vector<checker> &v, std::map<std::string, bool> &state)
    // {
    //     while (!state["finish"]){
    //         std::lock_guard<std::mutex> lock(Mutex);
    //         if ((state["moved"] == true) && (state["fighted"] == false) && (state["finish"] == false)){
    //             auto old = state;
    //             state["fighted"] = true;
    //             checker new_check{"fight", old, state};
    //             v.push_back(new_check);
    //         }
    //     }
    // };
    // auto lambdaMap = [](std::vector<checker> &v, std::map<std::string, bool> &state, std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration> &awake, std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration> start)
    // {
    //     while (!state["finish"]){
    //         std::lock_guard<std::mutex> lock(Mutex);
    //         if ((state["moved"] == true) && (state["fighted"] == true) && (state["done"] == false) && (state["finish"] == false)){
    //             auto old = state;
    //             state["fighted"] = false;
    //             state["moved"] = false;
    //             state["done"] = true;
    //             std::this_thread::sleep_until(awake);
    //             {
    //             using std::chrono::operator""ms;
    //             if (now() > start + 5000ms){
    //                 state["finish"] = true;
    //             }
    //             }
    //             checker new_check{"print_map", old, state};
    //             v.push_back(new_check);
    //         }
    //     }
    // };
    // std::thread moveTh(lambdaMove, ref(v), ref(state), ref(awake));
    // std::thread fightTh(lambdaFight, ref(v), ref(state));
    // std::thread mainTh(lambdaMap, ref(v), ref(state), ref(awake), start_time);
    // moveTh.join();
    // fightTh.join();
    // mainTh.join();
    // auto duration = std::chrono::seconds(30);
    // while (true) {
    //     std::thread moveTh(moving);
    //     std::thread fightTh(fighting);
    //     auto current_time = std::chrono::steady_clock::now();
    //     auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time);
    //     if (elapsed_time >= duration) {
    //         break;
    //     }
    //     // std::this_thread::sleep_for(std::chrono::seconds(1));
    // }
    // for (auto &&i : v)
    // {
    //     std::cout << i.phase << "\n";
    //     std::cout << ">--   m:" << i.old_state["moved"] << " f:" << i.old_state["fighted"] << " p:" << i.old_state["done"] << " X:" << i.old_state["finish"] <<"\n";
    //     std::cout << "<--   m:" << i.save_state["moved"] << " f:" << i.save_state["fighted"] << " p:" << i.save_state["done"]  << " X:" << i.save_state["finish"] << "\n\n";
    // }
    // auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now() - start_time);
    // std::cout << elapsed_ms.count() << "ms";

    // Create 50 npc
    // Battle - 30 sec
    // z


    // main
   
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    std::shared_ptr<ObserverBattlefieldOstream> obsO = std::make_shared<ObserverBattlefieldOstream>();
    btf->attachObs(obsO);
    btf->fillRandomly(16,16,18);
    btf->battle();



}   