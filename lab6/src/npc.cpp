#include "npc.h"

NPC::NPC() : _coords{0,0} {}

NPC::NPC(std::string npcName, TypeNPC type, const point &coords) : _name{npcName}, _coords{coords}, _type(type), alive(true) {}

NPC::NPC(std::string npcName, TypeNPC type, const int &x, const int &y) : _name{npcName}, _coords{x,y}, _type(type), alive(true) {}

TypeNPC NPC::type() const{
    return this->_type;
}

point NPC::coords() const{
    return this->_coords;
}

std::string NPC::name() const {
    return this->_name;
};

void NPC::save(std::ofstream &ofs) {
    ofs << this->_coords.x << ' ' << this->_coords.y << ' ' << this->type() << ' ' << this->name();
}

void NPC::load(std::ifstream &ifs) {
    int x,y,type;
    std::string name_;
    ifs >> x;
    ifs >> y;
    ifs >> type;
    ifs >> name_;
    _coords.x = x;
    _coords.y = y;
    _type = TypeNPC(type);
    _name = name_;
    alive = true;
}

bool NPC::is_alive() const{
    return this->alive;
}

void NPC::kill(){
    this->alive = false;
}

double NPC::npcDistance(const std::shared_ptr<NPC> other) const{
    return distance(_coords, other->_coords);
}

std::ostream &operator<<(std::ostream &os, NPC &npc) {
    os << "| x = " << npc._coords.x << ", y = " << npc._coords.y << " | ";
    if (npc.alive) {
        os << "alive | ";
    } else {
        os << "dead | ";
    }
    switch (npc._type) {
    case ORC:
        os << "Orc | ";
        break;
    case SQUIRREL:
        os << "Squirrel | ";
        break;
    case DRUID:
        os << "Druid | ";
        break;
    default:
        throw std::logic_error("Unknown NPC type");
        break;
    }
    os << npc._name  << std::endl;
    return os;
}
