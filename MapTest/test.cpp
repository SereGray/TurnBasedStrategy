#include "pch.h"

TEST(AdjacentListTesting, OnePoint) 
{
	AdjacentList adj(1, 1);
	EXPECT_EQ(1, adj.Size());
}

TEST(AdjacentListTesting, NinePointsSquare) 
{
	AdjacentList adj(3, 3);
	EXPECT_EQ(9, adj.Size());
}

TEST(AdjacentListTesting, BigMapPoints) 
{
	AdjacentList adj1(10, 5);
	EXPECT_EQ(2, adj1[9].adjacent_points.size());
	EXPECT_EQ(3, adj1[19].adjacent_points.size());
	EXPECT_EQ(4, adj1[18].adjacent_points.size());
	EXPECT_EQ(2, adj1[49].adjacent_points.size());
}

TEST(AdjacentListTesting, BigMapPointsManualAdjacentPointsCheck)
{
	AdjacentList adj1(5, 3);
	EXPECT_EQ(1, adj1[0].adjacent_points[0]);
	EXPECT_EQ(0 + 5, adj1[0].adjacent_points[1]);
	EXPECT_EQ(0, adj1[5].adjacent_points[0]);
	EXPECT_EQ(6, adj1[5].adjacent_points[1]);
	EXPECT_EQ(10, adj1[5].adjacent_points[2]);
	EXPECT_EQ(9, adj1[14].adjacent_points[0]);
	EXPECT_EQ(13, adj1[14].adjacent_points[1]);
}

TEST(KingdomMapTesting, GetMyId) 
{
	KingdomMap king(0, 0);
	EXPECT_EQ(0, king.GetMyId());
	KingdomMap king3(0, 3);
	EXPECT_EQ(3, king3.GetMyId());
}
TEST(KingdomMapTesting, MyArea) 
{
	KingdomMap kingMap(0, 0);
	for (unsigned i = 1; i < 10; ++i) {
		kingMap.list_v.push_back(i);
	}
	EXPECT_EQ(10, kingMap.MyArea());
}

TEST(KingdomMapTesting, RefreshBorders_1point)
{
	AdjacentList adj(3, 3);
	adj[0].N_owner = 0;
	KingdomMap kingd(0, 0);
	kingd.RefreshBorders(adj);
	EXPECT_EQ(1, kingd.borders.size());
	EXPECT_EQ(0, kingd.borders[0]);
}

TEST(KingdomMapTesting, RefreshBorders_2points_in_borders) 
{
	AdjacentList adj(3, 3);
	adj[0].N_owner = 0;
	adj[1].N_owner = 0;
	adj[3].N_owner = 0;
	KingdomMap kingd(0, 0);
	kingd.list_v.push_back(1);
	kingd.list_v.push_back(3);
	kingd.RefreshBorders(adj);
	EXPECT_EQ(2, kingd.borders.size());
	EXPECT_EQ(1, kingd.borders[0]);
	EXPECT_EQ(3, kingd.borders[1]);
}

TEST(KingdomMapTesting, RefreshBorders_3points_in_borders) 
{
	AdjacentList adj(3, 3);
	adj[0].N_owner = 0;
	adj[3].N_owner = 0;
	adj[6].N_owner = 0;
	KingdomMap kingd(0, 0);
	kingd.list_v.push_back(3);
	kingd.list_v.push_back(6);
	kingd.RefreshBorders(adj);
	EXPECT_EQ(3, kingd.borders.size());
	EXPECT_EQ(0, kingd.borders[0]);
	EXPECT_EQ(3, kingd.borders[1]);
	EXPECT_EQ(6, kingd.borders[2]);
}

TEST(KingdomMapTesting, RefreshBorders_4points_in_borders) 
{
	AdjacentList adj(9, 9);
	adj[50].N_owner = 0;
	adj[51].N_owner = 0;
	adj[49].N_owner = 0;
	adj[59].N_owner = 0;
	KingdomMap kingd(50, 0);
	kingd.list_v.push_back(51);
	kingd.list_v.push_back(49);
	kingd.list_v.push_back(59);
	kingd.RefreshBorders(adj);
	EXPECT_EQ(4, kingd.borders.size());
	EXPECT_EQ(50, kingd.borders[0]);
	EXPECT_EQ(51, kingd.borders[1]);
	EXPECT_EQ(49, kingd.borders[2]);
	EXPECT_EQ(59, kingd.borders[3]);
}
TEST(MapGameObjCreateMap, CreateMap3x3x1) 
{
	MapGameObj game_map(3, 3, 1); // 3 x 3  1 kingdoom
	game_map.AddKingdom(0);
	EXPECT_EQ(1, game_map.list_kingdoms_.size());
}

TEST(MapGameObjCreateMap, CreateMap9x9x2) 
{
	MapGameObj game_map(9, 9, 1); // 9 x 9  2 kingdoom
	game_map.AddKingdom(0);
	game_map.AddKingdom(1);
	EXPECT_EQ(2, game_map.list_kingdoms_.size());
}

TEST(MapGameObjCreateMap, CreateMap3x3x10_) 
{
	MapGameObj game_map(3, 3, 1);
	for (int i = 0; i < 10; ++i) {
		game_map.AddKingdom(i);
	}
	EXPECT_EQ(3*3, game_map.list_kingdoms_.size());
}

TEST(MapGameObjCreateMap, Compare_Kingdom_StartPos_With_Its_MapPoints) 
{
	MapGameObj game_map(3, 3, 1);
	for (int i = 0; i < 9; ++i) {
		game_map.AddKingdom(i);
	}
	for (int i = 0; i < 9; ++i) {
		EXPECT_EQ(game_map.adjacent_list_[game_map.list_kingdoms_[i].list_v[0]].N_owner, game_map.list_kingdoms_[i].GetMyId());  // ¹ owner of start point == id owner
	}
}

TEST(MapGameObjGenerateMap, GenerateMap) 
{
	MapGameObj game_map(3, 3, 1);
	game_map.AddKingdom(0);
	game_map.AddKingdom(1);
	game_map.GenerateMap();
}