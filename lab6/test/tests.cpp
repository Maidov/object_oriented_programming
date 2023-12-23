#include <gtest/gtest.h>
#include <vector>
#include "battlefield.h"

TEST(FactoryTest, TEST_01) {
    std::shared_ptr<DruidFactory> fD = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fD->create("testname", 10,20);
    ASSERT_TRUE(druid->type() == DRUID && druid->coords().x == 10 && druid->coords().y == 20);
}

TEST(FactoryTest, TEST_02) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("testname", 10,20);
    ASSERT_TRUE(orc->type() == ORC && orc->coords().x == 10 && orc->coords().y == 20);
}

TEST(FactoryTest, TEST_03) {
    std::shared_ptr<Factory> fD = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fD->create("testname", 10,20);
    ASSERT_TRUE(squirrel->type() == SQUIRREL && squirrel->coords().x == 10 && squirrel->coords().y == 20);
}

TEST(BattleCheck, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fO->create("testname", 10,20);
    ASSERT_TRUE(!squirrel->accept(orc));
}

TEST(BattleCheck, TEST_02) {
    std::shared_ptr<Factory> fD = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fO->create("testname", 10,20);
    ASSERT_TRUE(!squirrel->accept(orc) && !orc->accept(squirrel));
}

TEST(BattleCheck, TEST_03) {
    std::shared_ptr<Factory> fD = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("testname", 10,20);
    std::cout << druid->accept(squirrel) << ' ' << !squirrel->accept(druid) << std::endl;
    ASSERT_TRUE(druid->accept(squirrel) && !squirrel->accept(druid));
}

TEST(BattleCheck, TEST_04) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("testname", 10,20);
    ASSERT_TRUE(!druid->accept(orc) && orc->accept(druid));
}

TEST(Kill, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("testname", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fS->create("testname", 10,20);
    orc->kill(); druid->kill(); squirrel->kill();
    ASSERT_TRUE(!orc->is_alive() && !druid->is_alive() && !squirrel->is_alive());
}

TEST(Distance, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("testname", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fS->create("testname", 30,20);
    ASSERT_TRUE(fabs(squirrel->npcDistance(druid) - 20) < ESPILON);
}

TEST(Distance, TEST_02) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("testname", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fS->create("testname", -30, -20);
    ASSERT_TRUE(fabs(squirrel->npcDistance(druid) - 56.568) < ESPILON);
}

TEST(BattlefieldTEST, TEST_01) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("testname", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fS->create("testname", -30,-20);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(orc);
    btf->placeHero(druid);
    btf->placeHero(squirrel);
    ASSERT_TRUE(btf->npc().size() == 3);
}

TEST(BattlefieldTEST, TEST_02) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("testname", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fS->create("testname", 10,20);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(orc);
    btf->placeHero(druid);
    btf->placeHero(squirrel);
    ASSERT_NO_THROW(btf->battle(1,2));
}

TEST(BattlefieldTEST, TEST_03) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("testname", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fS->create("testname", 10,20);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->placeHero(orc);
    btf->placeHero(druid);
    btf->placeHero(squirrel);
    btf->battle(1,2);
    btf->removeDeadmen();
    ASSERT_TRUE(btf->npc().size() == 2);
}

TEST(BattlefieldTEST, TEST_04) {
    std::shared_ptr<Factory> fD = std::make_shared<OrcFactory>();
    std::shared_ptr<NPC> orc = fD->create("testname", 10,20);
    std::shared_ptr<Factory> fO = std::make_shared<DruidFactory>();
    std::shared_ptr<NPC> druid = fO->create("testname", 10,20);
    std::shared_ptr<Factory> fS = std::make_shared<SquirrelFactory>();
    std::shared_ptr<NPC> squirrel = fS->create("testname", 10,20);
    std::shared_ptr<Battlefield> btf = std::make_shared<Battlefield>();
    btf->fillRandomly(1,10,10,10);
    ASSERT_TRUE(btf->npc().size()==30);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}