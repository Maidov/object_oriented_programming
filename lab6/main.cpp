
#include "battlefield.h"

int main() {
    std::ifstream file("123.txt");
    std::ofstream file1("out.txt");
    std::shared_ptr<DruidFactory> fD = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fD->create("coolDroo",10,20);
    druid->save(file1);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->fillRandomly(time(NULL), 3,6,9);
    std::shared_ptr<ObserverBattlefieldOstream> obsO = std::make_shared<ObserverBattlefieldOstream>();
    std::shared_ptr<ObserverBattlefieldFile> obsF = std::make_shared<ObserverBattlefieldFile>();
    btf->attachObs(obsF);
    btf->attachObs(obsO);
    for (int i = 0; i < 5; i++)
    {
        btf->battle(3,50);
        btf->removeDeadmen();
        std::cout << *btf;
    }
}   