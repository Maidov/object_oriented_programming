#pragma once
#include "npc.h"
#include "fstream"
#include "ctime"
#include "druid.h"
#include "squirrel.h"
#include "orc.h"

#define ESPILON 0.001
#define BTF_SIZE 500
namespace Commands {
    const int LOSE = 0;
    const int WIN = 1;
    const int BATTLE_END = 3;
    const int BATTLE_START = 2;
}

struct Observer;

class Battlefield {
    public:
        Battlefield();

        friend std::ostream &operator<<(std::ostream &os, Battlefield &btf);

        void attachObs(std::shared_ptr<Observer> observer);
        void detachObs(std::shared_ptr<Observer> observer);
        void notify(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender, int win);

        void fillRandomly(size_t seed, size_t orcs, size_t druids, size_t squirrels);
        void placeHero(std::shared_ptr<NPC> npc);
        void removeHero(std::shared_ptr<NPC> npc);
        void removeDeadmen();

        std::list<std::shared_ptr<NPC>> npc();
        void battle(size_t rounds, double distance);
    private:
        std::pair<int, int> _size;
        std::list<std::shared_ptr<NPC>> _npcList;
        std::list<std::shared_ptr<Observer>> _observers;
};


struct Observer : public std::enable_shared_from_this<Observer> {
    virtual void battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) = 0;
    virtual void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) = 0;
    virtual void battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) = 0;
};

class ObserverBattlefieldOstream : public Observer {
    public:
        void battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) override;
        void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override;
        void battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) override;
};

class ObserverBattlefieldFile : public Observer {
    public:
        ObserverBattlefieldFile();
        ~ObserverBattlefieldFile();
        void battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) override;
        void fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override;
        void battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> _npcList) override;
    private:
        std::ofstream file;
};