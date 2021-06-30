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