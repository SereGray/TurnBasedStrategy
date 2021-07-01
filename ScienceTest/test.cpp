#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

//проверить AddKingdoom
TEST(ScienceTestCase, CreationTest) {
	ScienceGameObj scienceGameObj;
	EXPECT_TRUE(true);
}

TEST(ScienceTestCase, AddKingdoomTest) {
	ScienceGameObj scienceGameObj;
	EXPECT_THROW(scienceGameObj.GetKingdoom(0), VectorUtException);
	scienceGameObj.AddKingdoom(0);
	KingdoomScience* localKingdoom = scienceGameObj.GetKingdoom(0);
	EXPECT_EQ(localKingdoom->my_id_, 0);
}

TEST(ScienceTestCase, KingdomGetCountSpecialists)
{
	ScienceGameObj scienceGameObj;
	scienceGameObj.AddKingdoom(0);
	KingdoomScience* localKingdoom = scienceGameObj.GetKingdoom(0);
	EXPECT_EQ(localKingdoom->GetCountAllSpecialists(),0);
	localKingdoom->ChangeFreeSpecialist(10);
	EXPECT_EQ(localKingdoom->GetCountAllSpecialists(), 10);
	localKingdoom->ChangeCountSpec_DensetyPeople(15);
	EXPECT_EQ(localKingdoom->GetCountAllSpecialists(), 10);
	EXPECT_EQ(localKingdoom->GetCountSpec_DensetyPeople(), 10);
	EXPECT_EQ(localKingdoom->GetFreeSpecialist(), 0);
	localKingdoom->ChangeCountSpec_DensetyPeople(-15);
	EXPECT_EQ(localKingdoom->GetCountAllSpecialists(), 10);
	EXPECT_EQ(localKingdoom->GetCountSpec_DensetyPeople(), 0);
	EXPECT_EQ(localKingdoom->GetFreeSpecialist(), 10);
}

TEST(ScienceTestCase, KingdoomChangeSpecialists) {
	ScienceGameObj scienceGameObj;
	scienceGameObj.AddKingdoom(0);
	KingdoomScience* localKingdoom = scienceGameObj.GetKingdoom(0);
	localKingdoom->ChangeFreeSpecialist(10);
	localKingdoom->ChangeCountSpec_DensetyPeople(15);
	EXPECT_EQ(localKingdoom->GetCountSpec_DensetyPeople(), 10);
	EXPECT_EQ(localKingdoom->GetFreeSpecialist(), 0);
	localKingdoom->ChangeFreeSpecialist(15);
	localKingdoom->ChangeCountSpec_Harvesting(5);
	EXPECT_EQ(localKingdoom->GetCountSpec_Harvesting(), 5);
	EXPECT_EQ(localKingdoom->GetFreeSpecialist(), 10);
	localKingdoom->ChangeCountSpec_IncreasePeople(20);
	EXPECT_EQ(localKingdoom->GetCountSpec_IncreasePeople(), 10);
	EXPECT_EQ(localKingdoom->GetFreeSpecialist(), 0);
	localKingdoom->ChangeFreeSpecialist(10);
	localKingdoom->ChangeCountSpec_Science(20);
	EXPECT_EQ(localKingdoom->GetCountSpec_Science(), 10);
	EXPECT_EQ(localKingdoom->GetFreeSpecialist(), 0);
	localKingdoom->ChangeFreeSpecialist(20);
	localKingdoom->ChangeCountSpec_SellingRes(20);
	EXPECT_EQ(localKingdoom->GetCountSpec_SellingRes(), 20);
	EXPECT_EQ(localKingdoom->GetFreeSpecialist(), 0);
	localKingdoom->ChangeFreeSpecialist(10);
	localKingdoom->ChangeCountSpec_WarCraft(10);
	EXPECT_EQ(localKingdoom->GetCountSpec_WarCraft(), 10);
	EXPECT_EQ(localKingdoom->GetFreeSpecialist(), 0);
	EXPECT_EQ(localKingdoom->GetCountAllSpecialists(), 65);
}

TEST(ScienceTestCase, KingdoomGetSubjectScienceLvl_return_0) {
	ScienceGameObj scienceGameObj;
	scienceGameObj.AddKingdoom(0);
	KingdoomScience* localKingdoom = scienceGameObj.GetKingdoom(0);
	EXPECT_EQ(localKingdoom->GetDensityLvl(), 0);
	EXPECT_EQ(localKingdoom->GetScienceLvl(), 0);
	EXPECT_EQ(localKingdoom->GetIncreasingLvl(), 0);
	EXPECT_EQ(localKingdoom->GetIncreasingLvl(), 0);
	EXPECT_EQ(localKingdoom->GetSellingResLvl(), 0);
	EXPECT_EQ(localKingdoom->GetWarcraftLvl(), 0);
}

TEST(TheScienceTestCase, TheScienceProgressLimitOverFlow) {
	TheScience science;
	EXPECT_EQ(science.science_lvl_, 0);
	float force = science.NextTurn();
	EXPECT_EQ(science.science_lvl_, 0);
	EXPECT_FLOAT_EQ(force, 1.0f);
	std::pair<unsigned, unsigned> test_0_pair = std::make_pair<unsigned, unsigned>(0, 100);
	EXPECT_EQ(science.GetProgress(), test_0_pair);
	science.ChangeCountSpecialists(100);
	force = science.NextTurn();
	EXPECT_EQ(science.science_lvl_, 1);
	EXPECT_FLOAT_EQ(force, 1.01f);
	std::pair<unsigned, unsigned> test_0_110_pair = std::make_pair<unsigned, unsigned>(0, 110);
	EXPECT_EQ(science.GetProgress(), test_0_110_pair);
	force = science.NextTurn();
	EXPECT_EQ(science.science_lvl_, 1);
	EXPECT_FLOAT_EQ(force, 1.01f);
	std::pair<unsigned, unsigned> test_101_110_pair = std::make_pair<unsigned, unsigned>(101, 110);
	EXPECT_EQ(test_101_110_pair, science.GetProgress());
	force = science.NextTurn();
	EXPECT_EQ(science.science_lvl_, 2);
	EXPECT_FLOAT_EQ(force, 1.03f);
	std::pair<unsigned, unsigned> test_92_121_pair = std::make_pair<unsigned, unsigned>(92, 121);
	EXPECT_EQ(test_92_121_pair, science.GetProgress());
}

TEST(TheScienceTestCase, TheScienceProgressMonsterUp) {
	TheScience science;
	science.ChangeCountSpecialists(610);
	float force = science.NextTurn();
	EXPECT_EQ(5, science.science_lvl_);
	EXPECT_FLOAT_EQ(1.15f, force);
	std::pair<unsigned, unsigned> test = std::make_pair<unsigned, unsigned>(0, 160);
	EXPECT_EQ(test, science.GetProgress());
}