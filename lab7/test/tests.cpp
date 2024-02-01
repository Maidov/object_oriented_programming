#include <gtest/gtest.h>
#include <vector>
#include "battlefield.h"

#

TEST(FactoryTest, TEST_01) {
    std::shared_ptr<DruidFactory> fD = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fD->create("Тестов Тест", 10,20);
    ASSERT_TRUE(druid->type() == DRUID && druid->coords().x == 10 && druid->coords().y == 20);
}

TEST(FactoryTest, TEST_02) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("Тестов Тест", 10,20);
    ASSERT_TRUE(orc->type() == ORC && orc->coords().x == 10 && orc->coords().y == 20);
}

TEST(FactoryTest, TEST_03) {
    std::shared_ptr<Factory> fD = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fD->create("Тестов Тест", 10,20);
    ASSERT_TRUE(squirrel->type() == SQUIRREL && squirrel->coords().x == 10 && squirrel->coords().y == 20);
}

TEST(BattleCheck, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fD->create("Тестов Тест", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fO->create("Тестов ТТТТ", 10,20);
    ASSERT_NO_THROW(!squirrel->accept(orc));
}

TEST(BattleCheck, TEST_02) {
    std::shared_ptr<Factory> fD = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fD->create("Тестов Тест", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fO->create("Тестов ТТТТ", 10,20);
    std::shared_ptr<VisitorOrc> v1 = std::make_shared<VisitorOrc>();
    std::shared_ptr<VisitorSquirrel> v2 = std::make_shared<VisitorSquirrel>();
    ASSERT_NO_THROW(!squirrel->accept(orc) && !orc->accept(squirrel));
}

TEST(BattleCheck, TEST_03) {
    std::shared_ptr<Factory> fD = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fD->create("Тестов Тест", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("Тестов ТТТТ", 10,20);
    ASSERT_NO_THROW(druid->accept(squirrel) && !squirrel->accept(druid));
}

TEST(BattleCheck, TEST_04) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("Тестов Тест", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("Тестов ТТТТ", 10,20);
    ASSERT_NO_THROW(!druid->accept(orc) && orc->accept(druid));
}

TEST(Kill, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("Тестов Тест", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("Тестов ТТТТ", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fS->create("Тестов ТоТо", 10,20);
    orc->kill(); druid->kill(); squirrel->kill();
    ASSERT_TRUE(!orc->is_alive() && !druid->is_alive() && !squirrel->is_alive());
}

TEST(Distance, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("Тестов Тест", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("Тестов ТТТТ", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fS->create("Тестов ТоТо", 30,20);
    ASSERT_TRUE(fabs(squirrel->npcDistance(druid) - 20) < ESPILON);
}

TEST(Distance, TEST_02) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("Тестов Тест", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("Тестов ТТТТ", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fS->create("Тестов ТоТо", -30,-20);
    ASSERT_TRUE(fabs(squirrel->npcDistance(druid) - 56.568) < ESPILON);
}

TEST(BattlefieldTEST, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("Тестов Тест", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("Тестов ТТТТ", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fS->create("Тестов ТоТо", -30,-20);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(orc);
    btf->placeHero(druid);
    btf->placeHero(squirrel);
    ASSERT_TRUE(btf->npc().size() == 3);
}

TEST(BattlefieldTEST, TEST_02) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("Тестов Тест", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("Тестов ТТТТ", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fS->create("Тестов ТоТо", 10,20);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(orc);
    btf->placeHero(druid);
    btf->placeHero(squirrel);
    ASSERT_NO_THROW(btf->battle());
}

TEST(BattlefieldTEST, TEST_04) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("Тестов Тест", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("Тестов ТТТТ", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fS->create("Тестов ТоТо", 10,20);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->fillRandomly(10,10,10);
    ASSERT_TRUE(btf->npc().size()==30);
}


TEST(NPCmoveTEST, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("Тестов Тест", 0, 0);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(orc);
    orc->move(10, 10);
    bool check = false;
    for (auto &&npc : btf->npc())
    {
        if ((npc->coords().x == 10) && (npc->coords().y == 10)) check = true;
    }
    
    ASSERT_TRUE(check);
}

TEST(NPCmoveTEST, TEST_02) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("Тестов Тест", 10, 10);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(orc);
    orc->move(-10,-10);
    bool check = false;
    for (auto &&npc : btf->npc())
    {
        if ((npc->coords().x == 0) && (npc->coords().y == 0)) check = true;
    }
    
    ASSERT_TRUE(check);
}

TEST(NPCmoveTEST, TEST_03) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("Тестов Тест", 10, 10);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(orc);
    orc->move(-20,-11);
    bool check = false;
    for (auto &&npc : btf->npc())
    {

        if ((npc->coords().x == 10) && (npc->coords().y == 10)) check = true;
    }
    
    ASSERT_TRUE(check);
}

TEST(NPCmoveTEST, TEST_04) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("Тестов Тест", BTF_SIZE-1, BTF_SIZE-1);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(orc);
    orc->move(1,1);
    bool check = false;
    for (auto &&npc : btf->npc())
    {
        if ((npc->coords().x == BTF_SIZE-1) && (npc->coords().y == BTF_SIZE-1)) check = true;
    }
    
    ASSERT_TRUE(check);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}