#pragma once
#include "npc.h"

class Druid : public NPC {
    public:
        Druid(std::string npcName, const int &x, const int &y);

        bool accept(std::shared_ptr<NPC> defender) override;
};

class VisitorDruid: public Visitor {
    public: 
        bool visit(std::shared_ptr<NPC> defender) override;
};

class DruidFactory : public Factory {
    public:
        std::shared_ptr<NPC> create(std::string npcName, int x, int y) override;
        std::shared_ptr<NPC> create(std::istream &is) override;
        std::shared_ptr<NPC> create(std::ifstream &ifs) override;
};