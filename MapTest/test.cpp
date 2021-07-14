#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(MapTest_Debug, CreateMap10x10x2) {
	MapGameObj game_map(10, 10, 2); // 3 x 3  kingdoom
	EXPECT_EQ(2, game_map.list_kingdoms_.size());
}