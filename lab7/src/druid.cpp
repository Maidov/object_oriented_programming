#include "druid.h"

Druid::Druid(std::string npcName, const int &x, const int &y) : NPC{npcName, DRUID, x, y, RANGE::AR_DRUID, RANGE::MR_DRUID} {}

bool Druid::accept(std::shared_ptr<NPC> defender) {
    VisitorDruid v;
    return v.visit(defender, BACKWARD_COMPATIBILITY);
}

bool VisitorDruid::visit(std::shared_ptr<NPC> defender, bool backward_compatibility) {
    if ((defender->type() == SQUIRREL) || (!backward_compatibility)) {
        defender->kill();
        return true;
    } else {
        return false;
    }
}

std::shared_ptr<NPC> DruidFactory::create(std::string npcName, int x, int y) {
    std::shared_ptr<NPC> result = std::make_shared<Druid>(npcName, x, y);
    return result;
}

std::shared_ptr<NPC> DruidFactory::create(std::istream &is) {
    point tmp;
    is >> tmp.x; is >> tmp.y;
    std::string name_;
    is >> name_;
    std::shared_ptr<NPC> result = std::make_shared<Druid>(name_, tmp.x, tmp.y);
    return result;
}

std::shared_ptr<NPC> DruidFactory::create(std::ifstream &ifs) {
    int x; int y; int type;
    std::string name_;
    ifs >> x; ifs >> y; ifs >> type; ifs >> name_;
    std::shared_ptr<NPC> result = std::make_shared<Druid>(name_, x, y);
    return result;
}