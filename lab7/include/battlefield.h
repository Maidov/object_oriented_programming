#pragma once
#include "npc.h"
#include "fstream"
#include "ctime"
#include "druid.h"
#include "squirrel.h"
#include "orc.h"
#include <chrono>
#include <map>
#include <string>
#include <cstdarg>
#include <mutex>
#include <thread>


namespace Commands {
    const int FAIL = 0;
    const int KILL = 1;
    const int BATTLE_START = 2;
    const int BATTLE_END = 3;
    const int ROLL = 4;
};


struct Observer;

class Battlefield {
    public:
        Battlefield();

        friend std::ostream &operator<<(std::ostream &os, Battlefield &btf);

        void attachObs(std::shared_ptr<Observer> observer);
        void detachObs(std::shared_ptr<Observer> observer);
        void notify(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender, int win, ...);

        void fillRandomly(size_t orcs, size_t druids, size_t squirrels);
        void placeHero(std::shared_ptr<NPC> npc);
        void removeHero(std::shared_ptr<NPC> npc);
        void removeDeadmen();
        int holyRand();

        std::list<std::shared_ptr<NPC>> npc();
        void battle();
        void battle_old(size_t rounds, double distance);
    private:
        struct checker{
            std::string phase = "NULL";
            std::map<std::string, bool> old_state;
            std::map<std::string, bool> save_state;
        };

        struct duel{
            std::shared_ptr<NPC> defender;
            std::shared_ptr<NPC> attacker;
        };

        std::list<duel> _duelsList;
        std::mutex Mutex;
        std::chrono::_V2::steady_clock::time_point now();
        std::chrono::_V2::steady_clock::time_point awake_time();
        std::pair<int, int> _size;
        std::list<std::shared_ptr<NPC>> _npcList;
        std::list<std::shared_ptr<Observer>> _observers;
};


struct Observer : public std::enable_shared_from_this<Observer> {
    virtual void roll(const std::shared_ptr<NPC> attacker, const int aRoll, const std::shared_ptr<NPC>& defender, const int dRoll);
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