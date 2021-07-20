#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST(KingdomMapTesting, GetMyId) {
	KingdomMap king(0, 0);
	EXPECT_EQ(0, king.GetMyId());
	KingdomMap king3(0, 3);
	EXPECT_EQ(3, king3.GetMyId());
}
TEST(KingdomMapTesting, MyArea) {
	KingdomMap kingMap(0, 0);
	for (unsigned i = 1; i < 10; ++i) {
		kingMap.list_v.push_back(i);
	}
	EXPECT_EQ(10, kingMap.MyArea());
}
TEST(PapTestCreateMap, CreateMap3x3x1) {
	MapGameObj game_map(3, 3, 1); // 3 x 3  1 kingdoom
	EXPECT_EQ(1, game_map.list_kingdoms_.size());
}

TEST(PapTestCreateMap, CreateMap9x9x2) {
	MapGameObj game_map(9, 9, 2); // 9 x 9  2 kingdoom
	EXPECT_EQ(2, game_map.list_kingdoms_.size());
}

TEST(PapTestCreateMap, CreateMap3x3x4_) {
	MapGameObj game_map(3, 3, 10);
	EXPECT_EQ(0, game_map.list_kingdoms_.size());
}