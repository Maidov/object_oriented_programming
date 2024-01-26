#pragma once
#include "npc.h"

class Squirrel : public NPC {
    public:
        Squirrel(std::string npcName, const int &x, const int &y);

        bool accept(std::shared_ptr<NPC> defender) override;
};

class VisitorSquirrel: public Visitor {
    public: 
        bool visit(std::shared_ptr<NPC> defender, bool backward_compatibility) override;
};

class SquirrelFactory : public Factory {
    public:
        std::shared_ptr<NPC> create(std::string npcName, int x, int y) override;
        std::shared_ptr<NPC> create(std::istream &is) override;
        std::shared_ptr<NPC> create(std::ifstream &ifs) override;
};