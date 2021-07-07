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
	EXPECT_THROW(scienceGameObj.GetKingdoomScience(0), VectorUtException);
	scienceGameObj.AddKingdoom(0);
	KingdoomScience* localKingdoom = scienceGameObj.GetKingdoomScience(0);
	EXPECT_EQ(localKingdoom->GetMyId(), 0);
}

TEST(ScienceTestCase, KingdomGetCountSpecialists)
{
	ScienceGameObj scienceGameObj;
	scienceGameObj.AddKingdoom(0);
	KingdoomScience* localKingdoom = scienceGameObj.GetKingdoomScience(0);
	EXPECT_EQ(localKingdoom->GetCountAllSpecialists(),0);
	localKingdoom->ChangeFreeSpecialists(10);
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
	KingdoomScience* localKingdoom = scienceGameObj.GetKingdoomScience(0);
	localKingdoom->ChangeFreeSpecialists(10);
	localKingdoom->ChangeCountSpec_DensetyPeople(15);
	EXPECT_EQ(localKingdoom->GetCountSpec_DensetyPeople(), 10);
	EXPECT_EQ(localKingdoom->GetFreeSpecialist(), 0);
	localKingdoom->ChangeFreeSpecialists(15);
	localKingdoom->ChangeCountSpec_Harvesting(5);
	EXPECT_EQ(localKingdoom->GetCountSpec_Harvesting(), 5);
	EXPECT_EQ(localKingdoom->GetFreeSpecialist(), 10);
	localKingdoom->ChangeCountSpec_IncreasePeople(20);
	EXPECT_EQ(localKingdoom->GetCountSpec_IncreasePeople(), 10);
	EXPECT_EQ(localKingdoom->GetFreeSpecialist(), 0);
	localKingdoom->ChangeFreeSpecialists(10);
	localKingdoom->ChangeCountSpec_Science(20);
	EXPECT_EQ(localKingdoom->GetCountSpec_Science(), 10);
	EXPECT_EQ(localKingdoom->GetFreeSpecialist(), 0);
	localKingdoom->ChangeFreeSpecialists(20);
	localKingdoom->ChangeCountSpec_SellingRes(20);
	EXPECT_EQ(localKingdoom->GetCountSpec_SellingRes(), 20);
	EXPECT_EQ(localKingdoom->GetFreeSpecialist(), 0);
	localKingdoom->ChangeFreeSpecialists(10);
	localKingdoom->ChangeCountSpec_WarCraft(10);
	EXPECT_EQ(localKingdoom->GetCountSpec_WarCraft(), 10);
	EXPECT_EQ(localKingdoom->GetFreeSpecialist(), 0);
	EXPECT_EQ(localKingdoom->GetCountAllSpecialists(), 65);
}

TEST(ScienceTestCase, KingdoomGetSubjectScienceLvl_return_0) {
	ScienceGameObj scienceGameObj;
	scienceGameObj.AddKingdoom(0);
	KingdoomScience* localKingdoom = scienceGameObj.GetKingdoomScience(0);
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
	SubjectScience science(&the_science,"test");
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
	SubjectScience science(&the_science, "test");
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

TEST(KingdoomScienceTestCase, WarCraftLvlUp_after_ScienceLvlUp)
{
	KingdoomScience kingdoom(0);
	kingdoom.ChangeFreeSpecialists(610 + 87);
	kingdoom.ChangeCountSpec_Science(610);
	kingdoom.ChangeCountSpec_WarCraft(87);
	kingdoom.NextTurn();
	EXPECT_EQ(5, kingdoom.GetScienceLvl());
	std::pair<unsigned, unsigned> test666_1 = std::make_pair<unsigned, unsigned>(0, 160);
	EXPECT_EQ(test666_1, kingdoom.GetProgress_Science());
	EXPECT_EQ(1, kingdoom.GetWarcraftLvl());
	std::pair<unsigned, unsigned> test666_2 = std::make_pair<unsigned, unsigned>(0, 110);
	EXPECT_EQ(test666_2, kingdoom.GetProgress_WarCraft());
	// repeat
	KingdoomScience kingdoom1(1);
	kingdoom1.ChangeFreeSpecialists(610 + 87);
	kingdoom1.ChangeCountSpec_Science(610);
	kingdoom1.ChangeCountSpec_WarCraft(87);
	kingdoom1.NextTurn();
	EXPECT_EQ(5, kingdoom1.GetScienceLvl());
	EXPECT_EQ(test666_1, kingdoom1.GetProgress_Science());
	EXPECT_EQ(1, kingdoom1.GetWarcraftLvl());
	EXPECT_EQ(test666_2, kingdoom1.GetProgress_WarCraft());
}

TEST(KingdoomScienceTestCase, Test_access_by_pointer)
{
	KingdoomScience* kingdoom0 = new KingdoomScience(0);
	kingdoom0->ChangeFreeSpecialists(610 + 87);
	kingdoom0->ChangeCountSpec_Science(610);
	kingdoom0->ChangeCountSpec_WarCraft(87);
	kingdoom0->NextTurn();
	EXPECT_EQ(5, kingdoom0->GetScienceLvl());
	std::pair<unsigned, unsigned> test666_1 = std::make_pair<unsigned, unsigned>(0, 160);
	EXPECT_EQ(test666_1, kingdoom0->GetProgress_Science());
	EXPECT_EQ(1, kingdoom0->GetWarcraftLvl());
	std::pair<unsigned, unsigned> test666_2 = std::make_pair<unsigned, unsigned>(0, 110);
	EXPECT_EQ(test666_2, kingdoom0->GetProgress_WarCraft());
	delete kingdoom0;
}

TEST(KingdoomScienceTestCase, Test_copy_constr)
{
	KingdoomScience kingdoom1(0);
	KingdoomScience kingdoom(kingdoom1);
	kingdoom.ChangeFreeSpecialists(610 + 87);
	kingdoom.ChangeCountSpec_Science(610);
	kingdoom.ChangeCountSpec_WarCraft(87);
	kingdoom.NextTurn();
	EXPECT_EQ(5, kingdoom.GetScienceLvl());
	std::pair<unsigned, unsigned> test666_1 = std::make_pair<unsigned, unsigned>(0, 160);
	EXPECT_EQ(test666_1, kingdoom.GetProgress_Science());
	EXPECT_EQ(1, kingdoom.GetWarcraftLvl());
	std::pair<unsigned, unsigned> test666_2 = std::make_pair<unsigned, unsigned>(0, 110);
	EXPECT_EQ(test666_2, kingdoom.GetProgress_WarCraft());
}
TEST(KingdoomScienceTestCase, Test_vector_of_KingdScience)
{
	std::vector<KingdoomScience> v_kingdoom;
	v_kingdoom.push_back(KingdoomScience(0));
	v_kingdoom.push_back(KingdoomScience(1));
	v_kingdoom.push_back(KingdoomScience(2));
	auto it = v_kingdoom.begin();
	KingdoomScience *kingdoom0 = &(*it);
	KingdoomScience* kingdoom1 = &(*it++);
	KingdoomScience* kingdoom2 = &(*it++);
	kingdoom0->ChangeFreeSpecialists(610 + 87);
	kingdoom0->ChangeCountSpec_Science(610);
	kingdoom0->ChangeCountSpec_WarCraft(87);
	kingdoom0->NextTurn();
	EXPECT_EQ(5, kingdoom0->GetScienceLvl());
	std::pair<unsigned, unsigned> test666_1 = std::make_pair<unsigned, unsigned>(0, 160);
	EXPECT_EQ(test666_1, kingdoom0->GetProgress_Science());
	EXPECT_EQ(1, kingdoom0->GetWarcraftLvl());
	std::pair<unsigned, unsigned> test666_2 = std::make_pair<unsigned, unsigned>(0, 110);
	EXPECT_EQ(test666_2, kingdoom0->GetProgress_WarCraft());
}
TEST(ScienceGameObjTestCase, CreationTest) 
{
	ScienceGameObj science_gameobj;
	science_gameobj.AddKingdoom(0);
	EXPECT_EQ(0, science_gameobj.GetKingdoomScience(0)->GetMyId());
}

TEST(ScienceGameObjTestCase, NextTurnTest) {
	ScienceGameObj science_gameobj;
	science_gameobj.AddKingdoom(0);
	KingdoomScience* kingd0 = science_gameobj.GetKingdoomScience(0);
	kingd0->ChangeFreeSpecialists(100);
	kingd0->ChangeCountSpec_Science(999);
	science_gameobj.NextTurn();
	EXPECT_EQ(100, kingd0->GetCountSpec_Science());
	EXPECT_EQ(1, kingd0->GetScienceLvl());
	std::pair<unsigned, unsigned> test0 = std::make_pair<unsigned, unsigned>(0, 110);
	EXPECT_EQ(test0, kingd0->GetProgress_Science());
}
TEST(ScienceGameObjTestCase, NextTurnTestforThreeKingdooms) {
	ScienceGameObj science_gameobj;
	science_gameobj.AddKingdoom(0);
	science_gameobj.AddKingdoom(13);
	science_gameobj.AddKingdoom(666);
	EXPECT_EQ(0, science_gameobj.GetKingdoomScience(0)->GetMyId());
	EXPECT_EQ(13, science_gameobj.GetKingdoomScience(13)->GetMyId());
	EXPECT_EQ(666, science_gameobj.GetKingdoomScience(666)->GetMyId());
	KingdoomScience* kingd0 = science_gameobj.GetKingdoomScience(0);
	KingdoomScience* kingd13 = science_gameobj.GetKingdoomScience(13);
	KingdoomScience* kingd666 = science_gameobj.GetKingdoomScience(666);
	kingd0->ChangeFreeSpecialists(610); // 610 scienist up science lvl to 5
	kingd13->ChangeFreeSpecialists(100);
	kingd666->ChangeFreeSpecialists(610+87); // 610 scienist up science lvl to 5 & 87 scienist up warcraft to 1 lvl

	kingd0->ChangeCountSpec_Science(610);
	kingd13->ChangeCountSpec_Science(100);
	kingd666->ChangeCountSpec_Science(610);
	kingd666->ChangeCountSpec_WarCraft(87);

	science_gameobj.NextTurn();
	EXPECT_EQ(5, kingd0->GetScienceLvl());
	std::pair<unsigned, unsigned> test0 = std::make_pair<unsigned, unsigned>(0, 160);
	EXPECT_EQ(test0, kingd0->GetProgress_Science());

	EXPECT_EQ(1, kingd13->GetScienceLvl());
	std::pair<unsigned, unsigned> test13 = std::make_pair<unsigned, unsigned>(0, 110);
	EXPECT_EQ(test13, kingd13->GetProgress_Science());

	EXPECT_EQ(5, kingd666->GetScienceLvl());
	std::pair<unsigned, unsigned> test666_1 = std::make_pair<unsigned, unsigned>(0, 160);
	EXPECT_EQ(test666_1, kingd666->GetProgress_Science());
	EXPECT_EQ(1, kingd666->GetWarcraftLvl());
	std::pair<unsigned, unsigned> test666_2 = std::make_pair<unsigned, unsigned>(0, 110);
	EXPECT_EQ(test666_2, kingd666->GetProgress_WarCraft());
}