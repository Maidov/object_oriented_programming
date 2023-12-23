#include "orc.h"

Orc::Orc(std::string npcName, const int &x, const int &y) : NPC{npcName, ORC, x, y} {}

bool Orc::accept(std::shared_ptr<NPC> defender) {
    VisitorOrc v;
    return v.visit(defender);
}

bool VisitorOrc::visit(std::shared_ptr<NPC> defender) {
    if (defender->type() == DRUID) {
        defender->kill();
        return true;
    } else {
        return false;
    }
}

std::shared_ptr<NPC> OrcFactory::create(std::string npcName, int x, int y) {
    std::shared_ptr<NPC> result = std::make_shared<Orc>(npcName, x, y);
    return result;
}

std::shared_ptr<NPC> OrcFactory::create(std::istream &is) {
    point tmp;
    is >> tmp.x; is >> tmp.y;
    std::string name_;
    is >> name_;
    std::shared_ptr<NPC> result = std::make_shared<Orc>(name_, tmp.x, tmp.y);
    return result;
}

std::shared_ptr<NPC> OrcFactory::create(std::ifstream &ifs) {
    int x; int y; int type;
    std::string name_;
    ifs >> x; ifs >> y; ifs >> type; ifs >> name_;
    std::shared_ptr<NPC> result = std::make_shared<Orc>(name_, x, y);
    return result;
}