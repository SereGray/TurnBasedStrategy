#include "pch.h"

TEST(AdjacentListTesting, OnePoint) {
	AdjacentList adj(1, 1);
	EXPECT_EQ(1, adj.Size());
}

TEST(AdjacentListTesting, NinePointsSquare) {
	AdjacentList adj(3, 3);
	EXPECT_EQ(9, adj.Size());
}

TEST(AdjacentListTesting, BigMapPoints) {
	AdjacentList adj1(10, 5);
	EXPECT_EQ(2, adj1[9].adjacent_points.size());
	EXPECT_EQ(3, adj1[19].adjacent_points.size());
	EXPECT_EQ(4, adj1[18].adjacent_points.size());
	EXPECT_EQ(2, adj1[49].adjacent_points.size());
}

TEST(AdjacentListTesting, BigMapPointsManualAdjacentPointsCheck) {
	AdjacentList adj1(5, 3);
	EXPECT_EQ(1, adj1[0].adjacent_points[0]);
	EXPECT_EQ(0 + 5, adj1[0].adjacent_points[1]);
	EXPECT_EQ(0, adj1[5].adjacent_points[0]);
	EXPECT_EQ(6, adj1[5].adjacent_points[1]);
	EXPECT_EQ(10, adj1[5].adjacent_points[2]);
	EXPECT_EQ(9, adj1[14].adjacent_points[0]);
	EXPECT_EQ(13, adj1[14].adjacent_points[1]);
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
	MapGameObj game_map(3, 3); // 3 x 3  1 kingdoom
	game_map.AddKingdom(0);
	EXPECT_EQ(1, game_map.list_kingdoms_.size());
}

TEST(PapTestCreateMap, CreateMap9x9x2) {
	MapGameObj game_map(9, 9); // 9 x 9  2 kingdoom
	game_map.AddKingdom(0);
	game_map.AddKingdom(1);
	EXPECT_EQ(2, game_map.list_kingdoms_.size());
}

TEST(PapTestCreateMap, CreateMap3x3x10_) {
	MapGameObj game_map(3, 3);
	for (int i = 0; i < 10; ++i) {
		game_map.AddKingdom(i);
	}
	EXPECT_EQ(3*3, game_map.list_kingdoms_.size());
}

TEST(MapTestCreateMap, Compare_Kingdom_StartPos_With_Its_MapPoints) {
	MapGameObj game_map(3, 3);
	for (int i = 0; i < 9; ++i) {
		game_map.AddKingdom(i);
	}
	for (int i = 0; i < 9; ++i) {
		EXPECT_EQ(game_map.adjacent_list_[game_map.list_kingdoms_[i].list_v[0]].N_owner, game_map.list_kingdoms_[i].GetMyId());  // ¹ owner of start point == id owner
	}
}