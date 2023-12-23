#pragma once
#include "point.h"
#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <fstream>
enum TypeNPC {
    UNKNOWN = 0,
    ORC = 1,
    DRUID = 2,
    SQUIRREL = 3
};

class Visitor;

class NPC {
    private:
        std::string _name = "defaultName"; 
        TypeNPC _type = TypeNPC::UNKNOWN;
        point _coords{-1, -1};
        bool alive = false;
    public:

        NPC();
        NPC(std::string npcName, TypeNPC type, const point &coords);
        NPC(std::string npcName, TypeNPC type, const int &x, const int &y);

        TypeNPC type() const;
        point coords() const;
        bool is_alive() const;
        std::string name() const;

        virtual bool accept(std::shared_ptr<NPC> other) = 0;
        friend std::ostream &operator<<(std::ostream &os, NPC &npc);

        void kill();
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
        virtual bool visit(std::shared_ptr<NPC> defender) = 0;
};
