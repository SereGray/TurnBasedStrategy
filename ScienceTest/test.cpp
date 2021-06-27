#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

//проверить AddKingdoom
TEST(ScienceTest, CreationTest) {
	ScienceGameObj scienceGameObj;
	EXPECT_TRUE(true);
}

TEST(ScienceTest, AddKingdoomTest) {
	ScienceGameObj scienceGameObj;
	EXPECT_THROW(scienceGameObj.GetKingdoom(0), VectorUtException);
	scienceGameObj.AddKingdoom(0);
	KingdoomScience* localKingdoom = scienceGameObj.GetKingdoom(0);
	EXPECT_EQ(localKingdoom->my_id_, 0);
}