#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(MapTest_Debug, CreateMap3x3x1) {
	MapGameObj game_map(3, 3, 1); // 3 x 3  1 kingdoom
	EXPECT_EQ(1, game_map.list_kingdoms_.size());
}

TEST(MapTest_Debug, CreateMap9x9x2) {
	MapGameObj game_map(9, 9, 2); // 9 x 9  2 kingdoom
	EXPECT_EQ(2, game_map.list_kingdoms_.size());
}