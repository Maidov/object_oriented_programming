#include "npc.h"

NPC::NPC() : _coords{0,0} {}

NPC::NPC(std::string npcName, TypeNPC type, const point &coords,  const int &attackRange, const int &movementRange) : _name{npcName}, _coords{coords}, _type(type), alive(true), _rangeAttack{attackRange}, _rangeMove{movementRange} {}

NPC::NPC(std::string npcName, TypeNPC type, const int &x, const int &y, const int &attackRange, const int &movementRange) : _name{npcName}, _coords{x,y}, _type(type), alive(true), _rangeAttack{attackRange}, _rangeMove{movementRange} {}

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
    
    std::string status;
    if (npc.alive) {
        status = "alive";
    } else {
        status = "dead";
    }

    std::string this_type;
    switch (npc._type) {
    case ORC:
        this_type = "Orc";
        break;
    case SQUIRREL:
        this_type = "Squirrel";
        break;
    case DRUID:
        this_type = "Druid";
        break;
    default:
        throw std::logic_error("Unknown NPC type");
        break;
    }


    os << "| " << std::setw(3) << std::left << npc._coords.x << " | "
       << std::setw(3) << std::left << npc._coords.y << " | "
       << std::setw(5) << std::left << status << " | "
       << std::setw(10) << std::left << this_type << " | "
       << std::setw(30) << std::left << npc.name() << "\n";

    return os;
}


// NEW FUNCTIONALITY

int NPC::move_range() const{
    return _rangeMove;
}

int NPC::attack_range() const{
    return _rangeAttack;
}

void NPC::move(const int& moveX, const int& moveY) {
    if ((_coords.x + moveX >= 0) && (_coords.x + moveX < BTF_SIZE)) {
        _coords.x += moveX;
    }

    if ((_coords.y + moveY >= 0) && (_coords.y + moveY < BTF_SIZE)) {
        _coords.y += moveY;
    }
}

int NPC::holyRand() {
    // Используем генератор случайных чисел и распределение
    static std::random_device rd;  // Инициализация генератора случайных чисел
    static std::mt19937 gen(rd());  // Инициализация Mersenne Twister генератора
    static std::uniform_int_distribution<int> distribution(holyRand_DOWN, holyRand_UP);  // Равномерное распределение от 1 до 1000
    return distribution(gen);  // Генерация случайного числа
}