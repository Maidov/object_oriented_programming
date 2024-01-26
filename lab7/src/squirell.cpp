#include "squirrel.h"

Squirrel::Squirrel(std::string npcName, const int &x, const int &y) : NPC{npcName, SQUIRREL, x, y, RANGE::AR_SQUIRREL, RANGE::MR_SQUIRREL} {}

bool Squirrel::accept(std::shared_ptr<NPC> defender) {
    VisitorSquirrel v;
    return v.visit(defender, BACKWARD_COMPATIBILITY);
}

bool VisitorSquirrel::visit(std::shared_ptr<NPC> defender, bool backward_compatibility) {
    if (!backward_compatibility){
        defender->kill();
        return true;
    } else {
        return false;
    }
}

std::shared_ptr<NPC> SquirrelFactory::create(std::string npcName, int x, int y) {
    std::shared_ptr<NPC> result = std::make_shared<Squirrel>(npcName, x, y);
    return result;
}

std::shared_ptr<NPC> SquirrelFactory::create(std::istream &is) {
    point tmp;
    is >> tmp.x; is >> tmp.y;
    std::string name_;
    is >> name_;
    std::shared_ptr<NPC> result = std::make_shared<Squirrel>(name_, tmp.x, tmp.y);
    return result;
}

std::shared_ptr<NPC> SquirrelFactory::create(std::ifstream &ifs) {
    int x; int y; int type;
    std::string name_;
    ifs >> x; ifs >> y; ifs >> type; ifs >> name_;
    std::shared_ptr<NPC> result = std::make_shared<Squirrel>(name_, x, y);
    return result;
}