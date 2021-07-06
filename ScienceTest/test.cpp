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
	science.NextTurn();
	EXPECT_EQ(science.science_lvl_, 0);
	EXPECT_FLOAT_EQ(science.GetScienistForce(), 1.0f);
	std::pair<unsigned, unsigned> test_0_pair = std::make_pair<unsigned, unsigned>(0, 100);
	EXPECT_EQ(science.GetProgress(), test_0_pair);
	science.ChangeCountSpecialists(100);
	science.NextTurn();
	EXPECT_EQ(science.science_lvl_, 1);
	EXPECT_FLOAT_EQ(science.GetScienistForce(), 1.01f);
	std::pair<unsigned, unsigned> test_0_110_pair = std::make_pair<unsigned, unsigned>(0, 110);
	EXPECT_EQ(science.GetProgress(), test_0_110_pair);
	science.NextTurn();
	EXPECT_EQ(science.science_lvl_, 1);
	EXPECT_FLOAT_EQ(science.GetScienistForce(), 1.01f);
	std::pair<unsigned, unsigned> test_101_110_pair = std::make_pair<unsigned, unsigned>(101, 110);
	EXPECT_EQ(test_101_110_pair, science.GetProgress());
	science.NextTurn();
	EXPECT_EQ(science.science_lvl_, 2);
	EXPECT_FLOAT_EQ(science.GetScienistForce(), 1.03f);
	std::pair<unsigned, unsigned> test_92_121_pair = std::make_pair<unsigned, unsigned>(92, 121);
	EXPECT_EQ(test_92_121_pair, science.GetProgress());
}

TEST(TheScienceTestCase, TheScienceProgressBigUp) {
	TheScience science;
	science.ChangeCountSpecialists(610);
	science.NextTurn();
	EXPECT_EQ(5, science.science_lvl_);
	EXPECT_FLOAT_EQ(1.15f, science.GetScienistForce());
	std::pair<unsigned, unsigned> test = std::make_pair<unsigned, unsigned>(0, 160);
	EXPECT_EQ(test, science.GetProgress());
}

TEST(SubjectScienceTestCase, ProgressOverflow) {
	TheScience the_science;
	SubjectScience science(the_science,"test");
	EXPECT_EQ(science.science_lvl_, 0);
	science.NextTurn();
	EXPECT_EQ(science.science_lvl_, 0);
	EXPECT_FLOAT_EQ(science.GetScienistForce(), 1.0f);
	std::pair<unsigned, unsigned> test_0_pair = std::make_pair<unsigned, unsigned>(0, 100);
	EXPECT_EQ(science.GetProgress(), test_0_pair);
	science.ChangeCountSpecialists(100);
	science.NextTurn();
	EXPECT_EQ(science.science_lvl_, 1);
	EXPECT_FLOAT_EQ(science.GetScienistForce(), 1.0f);
	std::pair<unsigned, unsigned> test_0_110_pair = std::make_pair<unsigned, unsigned>(0, 110);
	EXPECT_EQ(science.GetProgress(), test_0_110_pair);
	science.NextTurn();
	EXPECT_EQ(science.science_lvl_, 1);
	EXPECT_FLOAT_EQ(science.GetScienistForce(), 1.0f);
	std::pair<unsigned, unsigned> test_101_110_pair = std::make_pair<unsigned, unsigned>(100, 110);
	EXPECT_EQ(test_101_110_pair, science.GetProgress());
	science.NextTurn();
	EXPECT_EQ(science.science_lvl_, 2);
	EXPECT_FLOAT_EQ(science.GetScienistForce(), 1.0f);
	std::pair<unsigned, unsigned> test_92_121_pair = std::make_pair<unsigned, unsigned>(90, 121);
	EXPECT_EQ(test_92_121_pair, science.GetProgress());
}

TEST(SubjectScienceTestCase, ProgressOverflowScienistForceChanged) {
	TheScience the_science;
	SubjectScience science(the_science, "test");
	the_science.ChangeCountSpecialists(610);
	the_science.NextTurn();
	EXPECT_FLOAT_EQ(1.15f, the_science.GetScienistForce());
	EXPECT_FLOAT_EQ(science.GetScienistForce(), 1.0f);
	science.ChangeCountSpecialists(100);
	science.NextTurn();
	EXPECT_EQ(science.science_lvl_, 1);
	EXPECT_EQ(100, science.GetCountSpecialists());
	EXPECT_FLOAT_EQ(science.GetScienistForce(), 1.15f);
	std::pair<unsigned, unsigned> test_15_110_pair = std::make_pair<unsigned, unsigned>(15, 110);
	EXPECT_EQ(science.GetProgress(), test_15_110_pair)<< std::round(1.1499999*100);
}

TEST(KingdoomScienceTestCase, Creation_Test) {
	KingdoomScience kingdoom(0);
	EXPECT_EQ(0, kingdoom.GetMyId());
	EXPECT_EQ(0, kingdoom.GetCountAllSpecialists());
	EXPECT_EQ(0, kingdoom.GetFreeSpecialist());
}

TEST(KingdoomScienceTestCase, FreeScienistCountTest)
{
	KingdoomScience kingdoom(0);
	kingdoom.ChangeCountSpec_DensetyPeople(100);
	EXPECT_EQ(0, kingdoom.GetFreeSpecialist());
	EXPECT_EQ(0, kingdoom.GetCountSpec_DensetyPeople());
	kingdoom.ChangeFreeSpecialists(100);
	EXPECT_EQ(100, kingdoom.GetFreeSpecialist());
	kingdoom.ChangeCountSpec_DensetyPeople(-1000);
	EXPECT_EQ(0, kingdoom.GetCountSpec_DensetyPeople());
	EXPECT_EQ(100, kingdoom.GetFreeSpecialist());
	kingdoom.ResetAllSpecialist();
	EXPECT_EQ(100, kingdoom.GetFreeSpecialist());
}

TEST(KingdoomScienceTestCase, ScienistCountTest)
{
	KingdoomScience kingdoom(0);
	kingdoom.ChangeFreeSpecialists(120);
	kingdoom.ChangeCountSpec_DensetyPeople(100);
	EXPECT_EQ(100, kingdoom.GetCountSpec_DensetyPeople());
	EXPECT_EQ(20, kingdoom.GetFreeSpecialist());
	kingdoom.ChangeCountSpec_DensetyPeople(-100);
	EXPECT_EQ(120, kingdoom.GetFreeSpecialist());
	EXPECT_EQ(0, kingdoom.GetCountSpec_DensetyPeople());
	kingdoom.ChangeCountSpec_Harvesting(100);
	EXPECT_EQ(100, kingdoom.GetCountSpec_Harvesting());
	EXPECT_EQ(20, kingdoom.GetFreeSpecialist());
	kingdoom.ChangeCountSpec_Harvesting(-100);
	EXPECT_EQ(0, kingdoom.GetCountSpec_Harvesting());
	EXPECT_EQ(120, kingdoom.GetFreeSpecialist());
	kingdoom.ChangeCountSpec_IncreasePeople(100);
	EXPECT_EQ(100, kingdoom.GetCountSpec_IncreasePeople());
	EXPECT_EQ(20, kingdoom.GetFreeSpecialist());
	kingdoom.ChangeCountSpec_IncreasePeople(-100);
	EXPECT_EQ(0, kingdoom.GetCountSpec_IncreasePeople());
	EXPECT_EQ(120, kingdoom.GetFreeSpecialist());
	kingdoom.ChangeCountSpec_Science(100);
	EXPECT_EQ(100, kingdoom.GetCountSpec_Science());
	EXPECT_EQ(20, kingdoom.GetFreeSpecialist());
	kingdoom.ChangeCountSpec_Science(-100);
	EXPECT_EQ(0, kingdoom.GetCountSpec_Science());
	EXPECT_EQ(120, kingdoom.GetFreeSpecialist());
	kingdoom.ChangeCountSpec_SellingRes(100);
	EXPECT_EQ(100, kingdoom.GetCountSpec_SellingRes());
	EXPECT_EQ(20, kingdoom.GetFreeSpecialist());
	kingdoom.ChangeCountSpec_SellingRes(-100);
	EXPECT_EQ(0, kingdoom.GetCountSpec_SellingRes());
	EXPECT_EQ(120, kingdoom.GetFreeSpecialist());
	kingdoom.ChangeCountSpec_WarCraft(100);
	EXPECT_EQ(100, kingdoom.GetCountSpec_WarCraft());
	EXPECT_EQ(20, kingdoom.GetFreeSpecialist());
	kingdoom.ChangeCountSpec_WarCraft(-100);
	EXPECT_EQ(0, kingdoom.GetCountSpec_WarCraft());
	EXPECT_EQ(120, kingdoom.GetFreeSpecialist());
}

TEST(KingdoomScienceTestCase, LvlUp_w100scienists)
{
	KingdoomScience kingdoom(0);
	std::pair<unsigned, unsigned> progress0(0, 110);
	kingdoom.ChangeFreeSpecialists(100);
	kingdoom.ChangeCountSpec_DensetyPeople(100);
	kingdoom.NextTurn();
	EXPECT_EQ(1, kingdoom.GetDensityLvl());
	EXPECT_EQ(progress0, kingdoom.GetProgress_DensetyPeople());
	kingdoom.ChangeCountSpec_DensetyPeople(-100);
	kingdoom.ChangeCountSpec_Harvesting(100);
	kingdoom.NextTurn();
	EXPECT_EQ(1, kingdoom.GetHarvestingLvl());
	EXPECT_EQ(progress0, kingdoom.GetProgress_Harvesting());
	kingdoom.ChangeCountSpec_Harvesting(-100);
	kingdoom.ChangeCountSpec_IncreasePeople(100);
	kingdoom.NextTurn();
	EXPECT_EQ(1, kingdoom.GetIncreasingLvl());
	EXPECT_EQ(progress0, kingdoom.GetProgress_IncreasePeople());
	kingdoom.ChangeCountSpec_IncreasePeople(-100);
	kingdoom.ChangeCountSpec_SellingRes(100);
	kingdoom.NextTurn();
	EXPECT_EQ(1, kingdoom.GetSellingResLvl());
	EXPECT_EQ(progress0, kingdoom.GetProgress_SellingRes());
	kingdoom.ChangeCountSpec_SellingRes(-100);
	kingdoom.ChangeCountSpec_WarCraft(100);
	kingdoom.NextTurn();
	EXPECT_EQ(1, kingdoom.GetWarcraftLvl());
	EXPECT_EQ(progress0, kingdoom.GetProgress_WarCraft());
	kingdoom.ChangeCountSpec_WarCraft(-100);
	kingdoom.ChangeCountSpec_Science(100);
	kingdoom.NextTurn();
	EXPECT_EQ(1, kingdoom.GetScienceLvl());
	EXPECT_EQ(progress0, kingdoom.GetProgress_Science());
	kingdoom.ChangeCountSpec_Science(-100);

	// science force now 1.01
	std::pair<unsigned, unsigned> progress101(101, 110);
	kingdoom.ChangeCountSpec_DensetyPeople(100);
	kingdoom.NextTurn();
	EXPECT_EQ(1, kingdoom.GetDensityLvl());
	EXPECT_EQ(progress101, kingdoom.GetProgress_DensetyPeople());
	kingdoom.ChangeCountSpec_DensetyPeople(-100);
	kingdoom.ChangeCountSpec_Harvesting(100);
	kingdoom.NextTurn();
	EXPECT_EQ(1, kingdoom.GetHarvestingLvl());
	EXPECT_EQ(progress101, kingdoom.GetProgress_Harvesting());
	kingdoom.ChangeCountSpec_Harvesting(-100);
	kingdoom.ChangeCountSpec_IncreasePeople(100);
	kingdoom.NextTurn();
	EXPECT_EQ(1, kingdoom.GetIncreasingLvl());
	EXPECT_EQ(progress101, kingdoom.GetProgress_IncreasePeople());
	kingdoom.ChangeCountSpec_IncreasePeople(-100);
	kingdoom.ChangeCountSpec_SellingRes(100);
	kingdoom.NextTurn();
	EXPECT_EQ(1, kingdoom.GetSellingResLvl());
	EXPECT_EQ(progress101, kingdoom.GetProgress_SellingRes());
	kingdoom.ChangeCountSpec_SellingRes(-100);
	kingdoom.ChangeCountSpec_SellingRes(-100);
	kingdoom.ChangeCountSpec_WarCraft(100);
	kingdoom.NextTurn();
	EXPECT_EQ(1, kingdoom.GetWarcraftLvl());
	EXPECT_EQ(progress101, kingdoom.GetProgress_WarCraft());
	kingdoom.ChangeCountSpec_WarCraft(-100);
}