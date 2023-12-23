#include "squirrel.h"

Squirrel::Squirrel(std::string npcName, const int &x, const int &y) : NPC{npcName, SQUIRREL, x, y} {}

bool Squirrel::accept(std::shared_ptr<NPC> defender) {
    VisitorSquirrel v;
    return v.visit(defender);
}

bool VisitorSquirrel::visit(std::shared_ptr<NPC> defender) {
    return false;
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