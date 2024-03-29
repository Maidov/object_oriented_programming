#include <chrono>
#include <thread>
#include "battlefield.h"


Battlefield::Battlefield() : _size(BTF_SIZE,BTF_SIZE), _npcList(), _observers() {}

void Battlefield::attachObs(std::shared_ptr<Observer> obs) {
    _observers.push_back(obs);
}

void Battlefield::detachObs(std::shared_ptr<Observer> obs) {
    if (!_observers.remove(obs)) {
        throw std::logic_error("Observer not in observer list");
    }
}

void Battlefield::fillRandomly(size_t orcs, size_t druids, size_t squirrels) {
    std::vector<std::string> namesList = {"Арнульф", "Бернард", "Бенедикт", "Вальтер", "Вильгельм", "Генри", "Исаак", "Джон", "Давид", "Карл", "Ричард", "Роберт", "Томас", "Уильям", "Уолтер", "Филипп", "Флавий", "Хью", "Ян", "Феофан"};
    std::vector<std::string> sureNamesList = {"Смелый", "Отважный", "Хитрый", "Удачливый", "Черный", "Белый", "Храбрый", "Великий", "Короткий", "Щедрый", "Меткий", "Кровавый", "Мудрый", "Милостивый", "Безумный", "Алчный", "Жадный", "Коварный", "Ясный", "Темный"};
    std::shared_ptr<Factory> factoryD = std::make_shared<DruidFactory>();
    std::shared_ptr<Factory> factoryO = std::make_shared<OrcFactory>();
    std::shared_ptr<Factory> factoryS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> orcNPC;
    std::shared_ptr<NPC> squirrelNPC;
    std::shared_ptr<NPC> druidNPC;
    size_t c_sq = 0, c_d = 0, c_o = 0;
    while(c_d < druids || c_sq < squirrels || c_o < orcs) {
        std::string rndName = namesList[holyRand() % namesList.size()];
        std::string rndSureName = sureNamesList[holyRand() % sureNamesList.size()];
        std::string medival = rndName + " " + rndSureName;
        switch (holyRand() % 3 + 1) {
            case DRUID:
                if (c_d < druids) {
                    druidNPC = factoryD->create(medival, holyRand() % BTF_SIZE, holyRand() % BTF_SIZE);
                    this->placeHero(druidNPC);
                    c_d++;
                }
                break;
            case SQUIRREL:
                if (c_sq < squirrels) {
                    squirrelNPC = factoryS->create(medival, holyRand() % BTF_SIZE, holyRand() % BTF_SIZE);
                    this->placeHero(squirrelNPC);
                    c_sq++;
                }
                break;
            case ORC:
                if (c_o < orcs) {
                    orcNPC = factoryO->create(medival, rand() % BTF_SIZE, rand() % BTF_SIZE);
                    this->placeHero(orcNPC);
                    c_o++;
                }
                break;
            default:
                break;
        }
    }
}

void Battlefield::notify(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender, int cmd, ...) {
    int aRoll=-1, dRoll=-1;
    va_list args;
    va_start(args, cmd);
    aRoll = va_arg(args, int);
    dRoll = va_arg(args, int);
    va_end(args);
    
    switch (cmd) {
        case Commands::FAIL:
            for (auto obs: _observers) {
                obs->fight(attacker, defender, cmd);
            }
            break;
        case Commands::KILL:
            for (auto obs: _observers) {
                obs->fight(attacker, defender, cmd);
            }
            break;
        case Commands::BATTLE_START:
            for (auto obs: _observers) {
                obs->battleStart(this->_size, this->_npcList);
            }
            break;
        case Commands::BATTLE_END:
            for (auto obs: _observers) {
                obs->battleEnd(this->_size, this->_npcList);
            }
            break;
        case Commands::ROLL:
            for (auto obs: _observers) {
                obs->roll(attacker, aRoll, defender, dRoll);
            }
            break;
        default:
            throw std::logic_error("Unknown notify");
        }
}

void Battlefield::placeHero(std::shared_ptr<NPC> npc) {
    if (npc->coords().x < BTF_SIZE && npc->coords().y < BTF_SIZE) _npcList.push_back(npc);
}

void Battlefield::removeDeadmen() {
    _npcList.erase(std::remove_if(_npcList.begin(), _npcList.end(), [](std::shared_ptr<NPC> npc) {return !npc->is_alive(); }), _npcList.end());
}

void Battlefield::removeHero(std::shared_ptr<NPC> npc) {
    if (!_npcList.remove(npc)) {
        throw std::logic_error("NPC not on battlefield");
    }
}

std::list<std::shared_ptr<NPC>> Battlefield::npc() {
    return _npcList;
}

void Battlefield::battle_old(size_t rounds, double distance) {
    this->notify(nullptr, nullptr, Commands::BATTLE_START);
    for (size_t i = 0; i < rounds; ++i) {
        for (auto attacker : _npcList) {
            bool success1;
            bool success2;
            for (auto defender : _npcList) {
                if (attacker != defender && attacker->is_alive() && defender->is_alive() && distance > defender->npcDistance(attacker)) {
                    success1 = attacker->accept(defender);
                    this->notify(attacker, defender, success1);
                    success2 = defender->accept(attacker);
                    this->notify(defender, attacker, success2);
                }
            }
        }
        distance+=distance;
    }
    this->notify(nullptr, nullptr, Commands::BATTLE_END);
}

void ObserverBattlefieldOstream::battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> npcList) {
    std::cout << std::endl << "-------- Battle started --------" << std::endl;
    std::cout << "There are " << npcList.size() << " fighters." << std::endl;
    for (auto npc: npcList) {
        std::cout << *npc;
    }
    std::cout << std::endl;
}

void ObserverBattlefieldOstream::battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> npcList) {
    std::cout << std::endl << "-------- Battle ended --------" << std::endl;
    std::cout << "There was " << npcList.size() << " fighters." << std::endl;
    for (auto npc: npcList) {
        std::cout << *npc;
    }
    std::cout << std::endl;
}


void ObserverBattlefieldOstream::fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) {
    if (win) {
        std::cout << std::endl << "Murder --------" << std::endl;
        std::cout << "Attacker: " << *attacker << "Defender: " << *defender << std::endl;
    } else {
        std::cout << std::endl << "Failed attack attempt --------" << std::endl;
        std::cout << "Attacker: " << *attacker << "Defender: " << *defender << std::endl;
    }
}

ObserverBattlefieldFile::ObserverBattlefieldFile() {
    const time_t tm = time(nullptr);
    char buf[64];
    strftime(buf, std::size(buf), "%d.%m.%Y-%H.%M.%S", localtime(&tm));
    file.open("../log/log_" + std::string(buf) + ".txt");
}

ObserverBattlefieldFile::~ObserverBattlefieldFile() {
    file.close();
}

void ObserverBattlefieldFile::fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) {
    if (win) {
        file << '\n' << "Murder --------" << '\n';
        file << "Attacker: " << *attacker << "Defender: " << *defender << '\n';
    } else {
        file << '\n' << "Failed attack attempt --------" << '\n';
        file << "Attacker: " << *attacker << "Defender: " << *defender << '\n';
    }
}

void ObserverBattlefieldFile::battleStart(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> npcList) {
    file << std::endl << "-------- Battle started --------" << std::endl;
    file << "There are " << npcList.size() << " fighters." << std::endl;
    for (auto npc: npcList) {
        file << *npc;
    }
    file << std::endl;
}

void ObserverBattlefieldFile::battleEnd(const std::pair<int,int> &size, const std::list<std::shared_ptr<NPC>> npcList) {
    file << std::endl << "-------- Battle ended --------" << std::endl;
    file << "There was " << npcList.size() << " fighters." << std::endl;
    for (auto npc: npcList) {
        file << *npc;
    }
    file << std::endl;
}




// NEW FUNCTIONALITY


void Observer::roll(const std::shared_ptr<NPC> attacker, const int aRoll, const std::shared_ptr<NPC>& defender, const int dRoll){
    std::cout << attacker->name() << ":--->  [" << aRoll << "vs" << dRoll << "]  |---:" << defender->name();
}



int Battlefield::holyRand() {
    // Используем генератор случайных чисел и распределение
    static std::random_device rd;  // Инициализация генератора случайных чисел
    static std::mt19937 gen(rd());  // Инициализация Mersenne Twister генератора
    static std::uniform_int_distribution<int> distribution(holyRand_DOWN, holyRand_UP);  // Равномерное распределение от 1 до 1000
    return distribution(gen);  // Генерация случайного числа
}

std::chrono::_V2::steady_clock::time_point Battlefield::now() { return std::chrono::steady_clock::now(); }

std::chrono::_V2::steady_clock::time_point Battlefield::awake_time()
{
    using std::chrono::operator""ms;
    return now() + 1000ms;
}

std::ostream &operator << (std::ostream &os, Battlefield &btf) {
    std::vector<std::vector<char>> field(BTF_SIZE, std::vector<char>(BTF_SIZE, '.'));
    char icon = '.';
    for (const auto& npc : btf._npcList) {
        if ((npc->coords().x >= 0) && (npc->coords().x < BTF_SIZE) && (npc->coords().y >= 0) && (npc->coords().y < BTF_SIZE)) {
            if (npc->is_alive()){
                const TypeNPC npcType = npc->type();
                switch (npcType)
                {
                case TypeNPC::DRUID:
                    icon = 'D';
                    break;
                case TypeNPC::ORC:
                    icon = 'O';
                    break;
                case TypeNPC::SQUIRREL:
                    icon = 'S';
                    break;
                default:
                    break;
                }
            } else {
                if (DISPLAY_DEAD){
                    const TypeNPC npcType = npc->type();
                    switch (npcType)
                    {
                    case TypeNPC::DRUID:
                        icon = 'd';
                        break;
                    case TypeNPC::ORC:
                        icon = 'b';
                        break;
                    case TypeNPC::SQUIRREL:
                        icon = 's';
                        break;
                    default:
                        break;
                    }
                } else {
                    icon = '.';
                }
            }
            field[npc->coords().y][npc->coords().x] = icon;
        }
    }
    if (MAP){
        for (int i = 0; i < BTF_SIZE; ++i) {
            for (int j = 0; j < BTF_SIZE; ++j) {
                os << field[i][j];
            }
            os << '\n';
        }
        os << '\n';
    }
    return os;
}




void Battlefield::battle() {
    std::cout << *this;
    this->notify(nullptr, nullptr, Commands::BATTLE_START);
    std::map<std::string, bool> state{{"moved", false}, {"fighted", false}, {"done", false}, {"finish", false}};
    std::chrono::_V2::steady_clock::time_point awake = awake_time();
    auto start_time = std::chrono::steady_clock::now();

    auto lambdaMove = [this](std::map<std::string, bool> &state, std::chrono::_V2::steady_clock::time_point &awake)
    {
        while (!state["finish"]){
            std::lock_guard<std::mutex> lock(Mutex);
            if ((state["moved"] == false) && (state["finish"] == false)){
                awake = this->awake_time();

                for (auto npc: _npcList) {
                    if (npc->is_alive()) {
                        int moveX = -npc->move_range() + (npc->holyRand() % (2 * npc->move_range()));
                        int remaining_movement = npc->move_range() - abs(moveX);
                        int moveY = (-1 + (npc->holyRand() % 2)*2) * remaining_movement;
                        npc->move(moveX, moveY);
                    }
                }

                for (auto attacker : _npcList) {
                    bool success1;
                    for (auto defender : _npcList) {
                        if ((attacker != defender) && (attacker->attack_range() > defender->npcDistance(attacker)) && (defender->is_alive()) && (attacker->is_alive())) {
                            duel new_duel;
                            new_duel.attacker = attacker;
                            new_duel.defender = defender;
                            _duelsList.push_back(new_duel);
                        }
                    }
                }

                state["moved"] = true;
                state["done"] = false;
            }
        }
    };

    auto lambdaFight = [this](std::map<std::string, bool> &state)
    {
        while (!state["finish"]){
            std::lock_guard<std::mutex> lock(Mutex);
            if ((state["moved"] == true) && (state["fighted"] == false) && (state["finish"] == false)){
                for (auto &&d : _duelsList)
                {
                    int defence = (d.defender->holyRand() % DICE_SIZE) + 1;
                    int attack = (d.attacker->holyRand() % DICE_SIZE) + 1;
                    if (INFO) notify(d.attacker, d.defender, Commands::ROLL, attack, defence);
                    if (attack > defence){
                        if (INFO) notify(d.attacker, d.defender, Commands::KILL);
                        d.attacker->accept(d.defender);
                    } else {
                        if (INFO) notify(d.attacker, d.defender, Commands::FAIL);
                    }
                }


                state["fighted"] = true;
            }
        }
    };
    auto lambdaMap = [this](std::map<std::string, bool> &state, std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration> &awake, std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::_V2::steady_clock::duration> start)
    {
        while (!state["finish"]){
            std::lock_guard<std::mutex> lock(Mutex);
            if ((state["moved"] == true) && (state["fighted"] == true) && (state["done"] == false) && (state["finish"] == false)){
                std::cout << *this;

                state["fighted"] = false;
                state["moved"] = false;
                state["done"] = true;
                std::this_thread::sleep_until(awake);
                {
                    using std::chrono::operator""ms;
                    if (this->now() > start + FIGHT_DURATION){
                        state["finish"] = true;
                    }
                }
            }
        }
    };

    std::thread moveTh(lambdaMove, ref(state), ref(awake));
    std::thread fightTh(lambdaFight, ref(state));
    std::thread mainTh(lambdaMap, ref(state), ref(awake), start_time);

    moveTh.join();
    fightTh.join();
    mainTh.join();
    
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now() - start_time);
    std::cout << elapsed_ms.count() << "ms";
    this->notify(nullptr, nullptr, Commands::BATTLE_END);
    std::cout << *this;
    
}