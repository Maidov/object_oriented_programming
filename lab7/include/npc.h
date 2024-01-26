#pragma once
#include "point.h"
#include "constant.h"
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <iomanip>
#include <string>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <random>


enum TypeNPC {
    UNKNOWN = 0,
    ORC = 1,
    DRUID = 2,
    SQUIRREL = 3
};

namespace RANGE {
    const int AR_DRUID = 10;
    const int AR_ORC = 10;
    const int AR_SQUIRREL = 5;
    
    const int MR_DRUID = 10;
    const int MR_ORC = 20;
    const int MR_SQUIRREL = 5;

}


class Visitor;

class NPC {
    private:
        std::string _name = "defaultName"; 
        TypeNPC _type = TypeNPC::UNKNOWN;
        point _coords{-1, -1};
        int mobility = 0;
        bool alive = false;
        int _rangeAttack;
        int _rangeMove;
    public:

        NPC();
        NPC(std::string npcName, TypeNPC type, const point &coords, const int &attackRange, const int &movementRange);
        NPC(std::string npcName, TypeNPC type, const int &x, const int &y, const int &attackRange, const int &movementRange);

        TypeNPC type() const;
        point coords() const;
        bool is_alive() const;
        std::string name() const;
        int move_range() const;
        int attack_range() const;
        int holyRand();

        virtual bool accept(std::shared_ptr<NPC> other) = 0;
        friend std::ostream &operator<<(std::ostream &os, NPC &npc);

        void kill();
        void move(const int &X, const int &Y);
        double npcDistance(const std::shared_ptr<NPC> other) const;
        void save(std::ofstream &ofs);
        void load(std::ifstream &ifs);
};

class Factory {
    public:
        virtual std::shared_ptr<NPC> create(std::string npcName,int x, int y) = 0;
        virtual std::shared_ptr<NPC> create(std::istream &is) = 0;
        virtual std::shared_ptr<NPC> create(std::ifstream &ifs) = 0;
        ~Factory() = default;
};

class Visitor {
    friend class NPC;
    public: 
        virtual bool visit(std::shared_ptr<NPC> defender, bool backward_compatibility) = 0;
};
