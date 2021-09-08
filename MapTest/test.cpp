#include "pch.h"

TEST(LineParamStruct, FixTest1) {
	LineParam line(-4, 3, 2, 7);
	EXPECT_EQ(4, line.A_);
	EXPECT_EQ(-6, line.B_);
	EXPECT_EQ(34, line.C_);
	EXPECT_FLOAT_EQ(0.66666669f, line.k_);
	EXPECT_FLOAT_EQ(5.6666667f, line.b_);
}


TEST(LineParamStruct, FixTest) {
	int Ax = 3, Ay = 2, Bx = -1, By = -1;
	LineParam line1(Ax,Ay,Bx,By);
	EXPECT_DOUBLE_EQ(0.75, line1.k_);
	EXPECT_DOUBLE_EQ(-0.25, line1.b_);
}

TEST(LineParamStruct, FixTest3) {
	int Ax = 2, Ay = 0, Bx = 7, By = 8;
	LineParam line1(Ax, Ay, Bx, By);
	EXPECT_DOUBLE_EQ(1.6000000238418579, line1.k_);
	EXPECT_DOUBLE_EQ(-3.2000000476837158, line1.b_);
}

TEST(LineParamStruct, FixTest4) {
	LineParam line1(3,0,-12.0);
	AdjacentList adj(11,22);
	std::vector<unsigned> line_path = GetPathByLine(line1, adj);
	EXPECT_FALSE(line_path.empty());
}
TEST(LineParamStruct, FixTest2) {
	int Ax = 3, Ay = 1, Bx = -8, By = -4;
	LineParam line1(Ax, Ay, Bx, By);
	EXPECT_DOUBLE_EQ(0.45454546809196472, line1.k_);
	EXPECT_DOUBLE_EQ(-0.36363637447357178, line1.b_);

}

TEST(LineParamStruct, MoveLine1) {
	int Ax = 2, Ay = 0, Bx = 7, By = 8;
	LineParam line1(Ax, Ay, Bx, By);
	LineParam new_line = line1 + 1;
	EXPECT_EQ(8,line1.A_);
	EXPECT_EQ(-5, line1.B_);
	EXPECT_EQ(-16, line1.C_);
	EXPECT_DOUBLE_EQ(1.6000000238418579, line1.k_);
	EXPECT_DOUBLE_EQ(-3.2000000476837158, line1.b_);
	//TODO: this
	EXPECT_EQ(8, new_line.A_);
	EXPECT_EQ(-5, new_line.B_);
	EXPECT_EQ(-24, new_line.C_);
	EXPECT_DOUBLE_EQ(1.6000000238418579, new_line.k_);
	EXPECT_DOUBLE_EQ(-4.8000001907348633, new_line.b_);
}

TEST(LineParamStruct, MoveLine2) {
	int Ax = 3, Ay = 1, Bx = -8, By = -4;
	LineParam line1(Ax, Ay, Bx, By);
	LineParam new_line = line1 + 1;
	EXPECT_EQ(-5, line1.A_);
	EXPECT_EQ(11, line1.B_);
	EXPECT_EQ(4, line1.C_);
	EXPECT_DOUBLE_EQ(0.45454546809196472, line1.k_);
	EXPECT_DOUBLE_EQ(-0.36363637447357178, line1.b_);
	//TODO: this
	EXPECT_EQ(-5, new_line.A_);
	EXPECT_EQ(11, new_line.B_);
	EXPECT_EQ(-7, new_line.C_);
	EXPECT_DOUBLE_EQ(0.45454546809196472, new_line.k_);
	EXPECT_DOUBLE_EQ(0.63636362552642822, new_line.b_);
}
TEST(LineParamGetCoordianteY, test_2x2)
{
	int Ax = 0, Ay = 0, Bx = 1, By = 1;
	LineParam line1(Ax, Ay, Bx, By);
	EXPECT_EQ(0, line1.GetCoordinateY(0));
	EXPECT_EQ(1, line1.GetCoordinateY(1));
}

TEST(LineParamGetCoordianteY, test_3x2)
{
	int Ax = 0, Ay = 0, Bx = 2, By = 1;
	LineParam line1(Ax, Ay, Bx, By);
	EXPECT_EQ(0, line1.GetCoordinateY(0));
	EXPECT_EQ(1, line1.GetCoordinateY(1));
	EXPECT_EQ(1, line1.GetCoordinateY(2));
}

TEST(LineParamGetCoordianteY, test_4x3)
{
	int Ax = 0, Ay = 0, Bx = 4, By = 3;
	LineParam line1(Ax, Ay, Bx, By);
	EXPECT_EQ(0, line1.GetCoordinateY(0));
	EXPECT_EQ(1, line1.GetCoordinateY(1));
	EXPECT_EQ(2, line1.GetCoordinateY(3));
	EXPECT_EQ(3, line1.GetCoordinateY(4));
}

TEST(LineParametGetCoordianteY, test_9x2)
{
	int Ax = 0, Ay = 0, Bx = 9, By = 1;
	LineParam line1(Ax, Ay, Bx, By);
	EXPECT_EQ(0, line1.GetCoordinateY(0));
	EXPECT_EQ(0, line1.GetCoordinateY(1));
	EXPECT_EQ(0, line1.GetCoordinateY(2));
	EXPECT_EQ(0, line1.GetCoordinateY(3));
	EXPECT_EQ(0, line1.GetCoordinateY(4));
	EXPECT_EQ(1, line1.GetCoordinateY(5));
	EXPECT_EQ(1, line1.GetCoordinateY(6));
	EXPECT_EQ(1, line1.GetCoordinateY(7));
	EXPECT_EQ(1, line1.GetCoordinateY(8));
	EXPECT_EQ(1, line1.GetCoordinateY(9));
}

TEST(LineParamGetCoordianteY, test_10x2)
{
	int Ax = 0, Ay = 0, Bx = 10, By = 1;
	LineParam line1(Ax, Ay, Bx, By);
	EXPECT_EQ(0, line1.GetCoordinateY(0));
	EXPECT_EQ(0, line1.GetCoordinateY(1));
	EXPECT_EQ(0, line1.GetCoordinateY(2));
	EXPECT_EQ(0, line1.GetCoordinateY(3));
	EXPECT_EQ(0, line1.GetCoordinateY(4));
	EXPECT_EQ(1, line1.GetCoordinateY(5));
	EXPECT_EQ(1, line1.GetCoordinateY(6));
	EXPECT_EQ(1, line1.GetCoordinateY(7));
	EXPECT_EQ(1, line1.GetCoordinateY(8));
	EXPECT_EQ(1, line1.GetCoordinateY(9));
	EXPECT_EQ(1, line1.GetCoordinateY(10));
}
TEST(LineParamGetCoordianteY, test_4x10)
{
	int Ax = 0, Ay = 0, Bx = 10, By = 4;
	LineParam line1(Ax, Ay, Bx, By);
	EXPECT_EQ(1, line1.GetCoordinateY(3));
	EXPECT_EQ(2, line1.GetCoordinateY(5));
	EXPECT_EQ(0, line1.GetCoordinateY(0));
	EXPECT_EQ(3, line1.GetCoordinateY(8));
	EXPECT_EQ(4, line1.GetCoordinateY(10));
}

TEST(GetFigureCenterFuncion, Two_points_horiz_center) {
	AdjacentList adj(2, 2);
	adj[0].owner_id_ = 0;
	adj[1].owner_id_ = 0;
	KingdomMap king(0, 0);
	king.list_v.push_back(1);
	EXPECT_FLOAT_EQ(0.5, GetFigureCenterOfMass(adj, &king).x_);
	EXPECT_FLOAT_EQ(0, GetFigureCenterOfMass(adj, &king).y_);
}

TEST(GetFigureCenterFuncion, Two_points_vertical_center) {
	AdjacentList adj(2, 2);
	adj[0].owner_id_ = 0;
	adj[2].owner_id_ = 0;
	KingdomMap king(0, 0);
	king.list_v.push_back(2);
	EXPECT_FLOAT_EQ(0, GetFigureCenterOfMass(adj, &king).x_);
	EXPECT_FLOAT_EQ(0.5, GetFigureCenterOfMass(adj, &king).y_);
}

TEST(GetFigureCenterFuncion, Four_points_center) {
	AdjacentList adj(2, 2);
	adj[0].owner_id_ = 0;
	adj[1].owner_id_ = 0;
	adj[2].owner_id_ = 0;
	adj[3].owner_id_ = 0;
	KingdomMap king(0, 0);
	king.list_v.push_back(1);
	king.list_v.push_back(2);
	king.list_v.push_back(3);
	EXPECT_FLOAT_EQ(0.5, GetFigureCenterOfMass(adj, &king).x_);
	EXPECT_FLOAT_EQ(0.5, GetFigureCenterOfMass(adj, &king).y_);
}

TEST(GetCoordOfCircleFuncion, FullTest1) 
{
	unsigned radius = 5;
	unsigned center_x = 6;
	unsigned center_y = 6;
	unsigned bound_x = 15;
	unsigned bound_y = 15;
	vector<pair<unsigned, unsigned>> coords = GetCoordOfCircle(radius, center_x, center_y, bound_x, bound_y);
	EXPECT_EQ(20, coords.size());
	for (auto p : coords) {
		EXPECT_TRUE(p.first < 15);
		EXPECT_TRUE(p.second < 15);
	}
	EXPECT_EQ(11, coords[0].first);
	EXPECT_EQ(6, coords[0].second);
	EXPECT_EQ(11, coords[1].first);
	EXPECT_EQ(7, coords[1].second);
	EXPECT_EQ(11, coords[2].first);
	EXPECT_EQ(8, coords[2].second);
	EXPECT_EQ(10, coords[3].first);
	EXPECT_EQ(9, coords[3].second);
	EXPECT_EQ(9, coords[4].first);
	EXPECT_EQ(10, coords[4].second);
	EXPECT_EQ(6, coords[5].first);
	EXPECT_EQ(11, coords[5].second);

	EXPECT_EQ(1, coords[6].first);
	EXPECT_EQ(6, coords[6].second);
	EXPECT_EQ(1, coords[7].first);
	EXPECT_EQ(7, coords[7].second);
	EXPECT_EQ(1, coords[8].first);
	EXPECT_EQ(8, coords[8].second);
	EXPECT_EQ(2, coords[9].first);
	EXPECT_EQ(9, coords[9].second);
	EXPECT_EQ(3, coords[10].first);
	EXPECT_EQ(10, coords[10].second);

	EXPECT_EQ(1, coords[11].first);
	EXPECT_EQ(5, coords[11].second);
	EXPECT_EQ(1, coords[12].first);
	EXPECT_EQ(4, coords[12].second);
	EXPECT_EQ(2, coords[13].first);
	EXPECT_EQ(3, coords[13].second);
	EXPECT_EQ(3, coords[14].first);
	EXPECT_EQ(2, coords[14].second);
	EXPECT_EQ(6, coords[15].first);
	EXPECT_EQ(1, coords[15].second);

	EXPECT_EQ(11, coords[16].first);
	EXPECT_EQ(5, coords[16].second);
	EXPECT_EQ(11, coords[17].first);
	EXPECT_EQ(4, coords[17].second);
	EXPECT_EQ(10, coords[18].first);
	EXPECT_EQ(3, coords[18].second);
	EXPECT_EQ(9, coords[19].first);
	EXPECT_EQ(2, coords[19].second);
};

TEST(GetCoordOfCircleFuncion, bounds_check)
{
	unsigned radius = 5;
	unsigned center_x = 6;
	unsigned center_y = 6;
	unsigned bound_x = 8;
	unsigned bound_y = 8;
	vector<pair<unsigned, unsigned>> coords = GetCoordOfCircle(radius, center_x, center_y, bound_x, bound_y);
	EXPECT_EQ(7, coords.size());
	for (auto p : coords) {
		EXPECT_TRUE(p.first < 8);
		EXPECT_TRUE(p.second < 8);
	}

};

TEST(GetCoordOfCircleFuncion, bounds_clipping_no_points_return)
{
	unsigned radius = 10;
	unsigned center_x = 4;
	unsigned center_y = 4;
	unsigned bound_x = 8;
	unsigned bound_y = 8;
	vector<pair<unsigned, unsigned>> coords = GetCoordOfCircle(radius, center_x, center_y, bound_x, bound_y);
	EXPECT_EQ(0, coords.size());
};
TEST(GetPathByLineFunction, BigDiagonalTest) {
	AdjacentList adj(6, 6);
	int x1 = 0, y1 = 0, x2 = 5, y2 = 5;
	LineParam line(x1,y1,x2,y2);
	vector<unsigned> path01 = GetPathByLine(line, adj);
	EXPECT_EQ(0, path01[0]);
	EXPECT_EQ(6, path01[1]);
	EXPECT_EQ(7, path01[2]);
	EXPECT_EQ(13, path01[3]);
	EXPECT_EQ(14, path01[4]);
	EXPECT_EQ(20, path01[5]);
	EXPECT_EQ(21, path01[6]);
	EXPECT_EQ(27, path01[7]);
	EXPECT_EQ(28, path01[8]);
	EXPECT_EQ(34, path01[9]);
	EXPECT_EQ(35, path01[10]);
}

TEST(GetPathByLineFunction, BigHorizontalLine) {
	AdjacentList adj(10, 1);
	int x1 = 0, y1 = 0, x2 = 10, y2 = 0;
	LineParam line(x1, y1, x2, y2);
	vector<unsigned> path01 = GetPathByLine(line, adj);
	EXPECT_EQ(0, path01[0]);
	EXPECT_EQ(1, path01[1]);
	EXPECT_EQ(2, path01[2]);
	EXPECT_EQ(3, path01[3]);
	EXPECT_EQ(4, path01[4]);
	EXPECT_EQ(5, path01[5]);
	EXPECT_EQ(6, path01[6]);
	EXPECT_EQ(7, path01[7]);
	EXPECT_EQ(8, path01[8]);
	EXPECT_EQ(9, path01[9]);
}


TEST(GetPathByLineFunction, BigVerticalLine) {
	AdjacentList adj(1, 10);
	int x1 = 0, y1 = 0, x2 = 0, y2 = 10;
	LineParam line(x1, y1, x2, y2);
	vector<unsigned> path01 = GetPathByLine(line, adj);
	EXPECT_EQ(0, path01[0]);
	EXPECT_EQ(1, path01[1]);
	EXPECT_EQ(2, path01[2]);
	EXPECT_EQ(3, path01[3]);
	EXPECT_EQ(4, path01[4]);
	EXPECT_EQ(5, path01[5]);
	EXPECT_EQ(6, path01[6]);
	EXPECT_EQ(7, path01[7]);
	EXPECT_EQ(8, path01[8]);
	EXPECT_EQ(9, path01[9]);
}

TEST(GetPathBetweenKingdoomsByLineFunction, Simple6x2Map) {
	AdjacentList adj(6, 2);
	adj[0].owner_id_ = 1;
	adj[2].owner_id_ = 0;
	adj[1].owner_id_ = 0;
	adj[4].owner_id_ = 0;
	adj[5].owner_id_ = 0;
	adj[6].owner_id_ = 0;
	adj[7].owner_id_ = 0;
	adj[8].owner_id_ = 0;
	adj[9].owner_id_ = 0;
	adj[10].owner_id_ = 0;
	adj[11].owner_id_ = 2;
	KingdomMap king0(0, 1);
	KingdomMap king1(11, 2);
	FigureCenter king0ctr = GetFigureCenterOfMass(adj, &king0);
	FigureCenter king1ctr = GetFigureCenterOfMass(adj, &king1);
	LineParam line(king0ctr.x_, king0ctr.y_, king1ctr.x_, king1ctr.y_);
	vector<unsigned> path_by_line = GetPathByLine(line, adj);
	vector<unsigned> path01 = GetPathBetweenKingdomsByLine(path_by_line, king0.GetMyId(), king1.GetMyId(), adj);
	EXPECT_EQ(0, path01[0]);
	EXPECT_EQ(1, path01[1]);
	EXPECT_EQ(2, path01[2]);
	EXPECT_EQ(8, path01[3]);
	EXPECT_EQ(9, path01[4]);
	EXPECT_EQ(10, path01[5]);
	EXPECT_EQ(11, path01[6]);
}

TEST(GetPathBetweenKingdoomsByLineFunction, Simple4x3Map) {
	AdjacentList adj(4, 3);
	adj[0].owner_id_ = 1;
	adj[2].owner_id_ = 0;
	adj[1].owner_id_ = 0;
	adj[4].owner_id_ = 0;
	adj[5].owner_id_ = 0;
	adj[6].owner_id_ = 0;
	adj[7].owner_id_ = 0;
	adj[8].owner_id_ = 0;
	adj[9].owner_id_ = 0;
	adj[10].owner_id_ = 0;
	adj[11].owner_id_ = 2;
	KingdomMap king0(0, 1);
	KingdomMap king1(11, 2);
	FigureCenter king0ctr = GetFigureCenterOfMass(adj, &king0);
	FigureCenter king1ctr = GetFigureCenterOfMass(adj, &king1);
	LineParam line(king0ctr.x_, king0ctr.y_, king1ctr.x_, king1ctr.y_);
	vector<unsigned> path_by_line = GetPathByLine(line, adj);
	vector<unsigned> path01 = GetPathBetweenKingdomsByLine(path_by_line, king0.GetMyId(), king1.GetMyId(), adj);
	EXPECT_EQ(0, path01[0]);
	EXPECT_EQ(4, path01[1]);
	EXPECT_EQ(5, path01[2]);
	EXPECT_EQ(6, path01[3]);
	EXPECT_EQ(10, path01.at(4));
	EXPECT_EQ(11, path01.at(5));
}

TEST(GetPathBetweenKingdoomsByLineFunction, Simple2x2Map) {
	AdjacentList adj(2, 2);
	adj[0].owner_id_ = 0;
	adj[2].owner_id_ = 0;
	adj[1].owner_id_ = 1;
	adj[3].owner_id_ = 1;
	KingdomMap king0(0, 0);
	KingdomMap king1(1, 1);
	FigureCenter king0ctr = GetFigureCenterOfMass(adj, &king0);
	FigureCenter king1ctr = GetFigureCenterOfMass(adj, &king1);
	LineParam line(king0ctr.x_, king0ctr.y_, king1ctr.x_, king1ctr.y_);
	vector<unsigned> path_by_line = GetPathByLine(line, adj);
	vector<unsigned> path01 = GetPathBetweenKingdomsByLine(path_by_line,king0.GetMyId(),king1.GetMyId(),adj);
	//EXPECT_TRUE(false);
	EXPECT_EQ(0, path01[0]);
	EXPECT_EQ(1, path01[1]);
}

TEST(GetPathBetweenKingdoomsByLineFunction, Simple4x3MapNoPath) {
	AdjacentList adj(4, 3);
	adj[0].owner_id_ = 1;
	adj[2].owner_id_ = 0;
	adj[1].owner_id_ = 0;
	adj[4].owner_id_ = 0;
	adj[5].owner_id_ = 0;
	adj[6].owner_id_ = 0;
	adj[7].owner_id_ = 0;
	adj[8].owner_id_ = 0;
	adj[9].owner_id_ = 0;
	adj[10].owner_id_ = 0;
	adj[11].owner_id_ = 2;
	KingdomMap king0(0, 1);
	KingdomMap king1(11, 2);
	FigureCenter king0ctr = GetFigureCenterOfMass(adj, &king0);
	FigureCenter king1ctr = GetFigureCenterOfMass(adj, &king1);
	LineParam line(king0ctr.x_, king0ctr.y_, king1ctr.x_, king1ctr.y_);
	line = line + 5;
	vector<unsigned> path_by_line = GetPathByLine(line, adj);
	vector<unsigned> path01 = GetPathBetweenKingdomsByLine(path_by_line, king0.GetMyId(), king1.GetMyId(), adj);
	EXPECT_TRUE(path01.empty());
	vector<unsigned>().empty();

}
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

TEST(KingdomMapNeighborVertexExist, smal_vector) {
	KingdomMapNeighbor neighbor(0, 0);
	neighbor.v_viewed_points_.push_back(1);
	neighbor.v_viewed_points_.push_back(2);
	EXPECT_TRUE(neighbor.VertexExist(0));
	EXPECT_TRUE(neighbor.VertexExist(1));
	EXPECT_TRUE(neighbor.VertexExist(2));
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
	adj[0].owner_id_ = 0;
	KingdomMap kingd(0, 0);
	kingd.RefreshBorders(adj);
	EXPECT_EQ(1, kingd.borders.size());
	EXPECT_EQ(0, kingd.borders[0]);
}

TEST(KingdomMapTesting, RefreshBorders_2points_in_borders) 
{
	AdjacentList adj(3, 3);
	adj[0].owner_id_ = 0;
	adj[1].owner_id_ = 0;
	adj[3].owner_id_ = 0;
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
	adj[0].owner_id_ = 0;
	adj[3].owner_id_ = 0;
	adj[6].owner_id_ = 0;
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
	adj[50].owner_id_ = 0;
	adj[51].owner_id_ = 0;
	adj[49].owner_id_ = 0;
	adj[59].owner_id_ = 0;
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

TEST(KingdomMapRefreshNeighbors, Two_kingd_small_map) 
{
	AdjacentList adj(3, 3);
	adj[0].owner_id_ = 0;
	adj[1].owner_id_ = 1;
	adj[2].owner_id_ = 1;
	adj[3].owner_id_ = 0;
	adj[4].owner_id_ = 1;
	adj[5].owner_id_ = 1;
	adj[6].owner_id_ = 0;
	adj[7].owner_id_ = 0;
	adj[8].owner_id_ = 1;
	KingdomMap king0(0, 0), king1(1, 1);
	king0.list_v.push_back(3); king0.list_v.push_back(6); king0.list_v.push_back(7);
	king1.list_v.push_back(2); king1.list_v.push_back(4); king1.list_v.push_back(5); king1.list_v.push_back(8);
	king0.RefreshBorders(adj);
	king1.RefreshBorders(adj);
	EXPECT_EQ(1, king0.v_neighbors_.size());
	EXPECT_EQ(3, king0.v_neighbors_[0].count_points_);
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

TEST(MapGameObjCreateMap, CreateMap3x3x9) 
{
	MapGameObj game_map(3, 3, 1);
	for (int i = 0; i < 9; ++i) {
		game_map.AddKingdom(i);
	}
	EXPECT_EQ(3*3, game_map.list_kingdoms_.size());
}

/*
TEST(MapGameObjGenerateMap, all_points_owner_check) 
{
	MapGameObj game_map(3, 3, 1);
	game_map.AddKingdom(0);
	game_map.AddKingdom(1);
	game_map.GenerateMap();
	for (auto pt : game_map.adjacent_list_) {
		EXPECT_TRUE(pt.owner_id_ >= 0); // all points have an owner
	}
}

TEST(MapGameObjGenerateMap, full_balance_check_with_even_points_count) {
	MapGameObj game_map(4, 4, 1);
	game_map.AddKingdom(0);
	game_map.AddKingdom(1);
	game_map.GenerateMap();
	EXPECT_TRUE(game_map.GetKingdomMap(0)->list_v.size() == game_map.GetKingdomMap(1)->list_v.size());
}
*/
TEST(MapGameObjGenerateMap, full_balance_check_with_even_points_count_byLineGeneration) {
	MapGameObj game_map(4, 4, 1);
	game_map.AddKingdom(0);
	game_map.AddKingdom(1);
	game_map.GenerateMapByLine();
	EXPECT_TRUE(game_map.GetKingdomMap(0)->list_v.size() == game_map.GetKingdomMap(1)->list_v.size());
}
/*
TEST(MapGameObjGenerateMap, full_balance_check_with_odd_points_count) {
	MapGameObj game_map(3, 3, 1);
	game_map.AddKingdom(0);
	game_map.AddKingdom(1);
	game_map.AddKingdom(2);
	game_map.GenerateMap();
	EXPECT_TRUE(game_map.GetKingdomMap(0)->list_v.size() == game_map.GetKingdomMap(1)->list_v.size());
	EXPECT_TRUE(game_map.GetKingdomMap(0)->list_v.size() == game_map.GetKingdomMap(2)->list_v.size());
}
*/

TEST(MapGameObjGenerateMap, full_balance_check_with_odd_points_count_byLineGeneration) {
	MapGameObj game_map(3, 3, 1);
	game_map.AddKingdom(0);
	game_map.AddKingdom(1);
	game_map.AddKingdom(2);
	game_map.GenerateMapByLine();
	EXPECT_TRUE(game_map.GetKingdomMap(0)->list_v.size() == game_map.GetKingdomMap(1)->list_v.size());
	EXPECT_TRUE(game_map.GetKingdomMap(0)->list_v.size() == game_map.GetKingdomMap(2)->list_v.size());
}
/*
TEST(MapGameObjGenerateMap, balance_check_with_odd_points_count_and_2kingdom) {
	MapGameObj game_map(3, 3, 1);
	game_map.AddKingdom(0);
	game_map.AddKingdom(1);
	game_map.GenerateMap();
	EXPECT_FALSE(game_map.GetKingdomMap(0)->list_v.size() == game_map.GetKingdomMap(1)->list_v.size());
	EXPECT_TRUE(game_map.GetKingdomMap(0)->list_v.size() - game_map.GetKingdomMap(1)->list_v.size() == 1); // KingdomMap with id=0 +1 point disbalanced
}
*/

TEST(MapGameObjGenerateMap, balance_check_with_odd_points_count_and_2kingdom_byLineGeneration) {
	MapGameObj game_map(3, 3, 1);
	game_map.AddKingdom(0);
	game_map.AddKingdom(1);
	game_map.GenerateMapByLine();
	EXPECT_FALSE(game_map.GetKingdomMap(0)->list_v.size() == game_map.GetKingdomMap(1)->list_v.size());
	EXPECT_TRUE(game_map.GetKingdomMap(0)->list_v.size() - game_map.GetKingdomMap(1)->list_v.size() == 1); // KingdomMap with id=0 +1 point disbalanced
}
/*
TEST(MapGameObjGenerateMap, generate_33x33_map)
{
	MapGameObj game_map(11, 22, 1);
	game_map.AddKingdom(0);
	game_map.AddKingdom(1);
	game_map.AddKingdom(2);
//	game_map.AddKingdom(3);
//	game_map.AddKingdom(4);
	game_map.GenerateMap();
	EXPECT_TRUE(true);
}
*/

TEST(MapGameObjGenerateMap, generate_11x22_map_byLineGeneration)
{
	MapGameObj game_map(11, 22, 1);
	game_map.AddKingdom(0);
	game_map.AddKingdom(1);
	game_map.AddKingdom(2);
	//	game_map.AddKingdom(3);
	//	game_map.AddKingdom(4);
	game_map.GenerateMapByLine();
	EXPECT_TRUE(game_map.GetKingdomMap(0)->list_v.size() >= 80);
	EXPECT_TRUE(game_map.GetKingdomMap(1)->list_v.size() >= 80);
	EXPECT_TRUE(game_map.GetKingdomMap(2)->list_v.size() >= 80);
}

TEST(MapGameObjGenerateMap, generate_33x33_map_byLineGeneration)
{
	MapGameObj game_map(33, 33, 1);
	game_map.AddKingdom(0);
	game_map.AddKingdom(1);
	game_map.AddKingdom(2);
	game_map.AddKingdom(3);
	game_map.AddKingdom(4);
	game_map.GenerateMapByLine();
	EXPECT_TRUE(game_map.GetKingdomMap(0)->list_v.size() >= 217);
	EXPECT_TRUE(game_map.GetKingdomMap(1)->list_v.size() >= 217);
	EXPECT_TRUE(game_map.GetKingdomMap(2)->list_v.size() >= 217);
	EXPECT_TRUE(game_map.GetKingdomMap(3)->list_v.size() >= 217);
	EXPECT_TRUE(game_map.GetKingdomMap(4)->list_v.size() >= 217);
}

/*
TEST(MapGameObjGenerateMap, generate_100x100_map_byLineGeneration)
{
	MapGameObj game_map(100, 100, 1);
	game_map.AddKingdom(0);
	game_map.AddKingdom(1);
	game_map.AddKingdom(2);
	game_map.AddKingdom(3);
	game_map.AddKingdom(4);
	game_map.AddKingdom(5);
	game_map.AddKingdom(6);
	game_map.AddKingdom(7);
	game_map.AddKingdom(8);
	game_map.AddKingdom(9);
	game_map.AddKingdom(10);
	game_map.AddKingdom(11);
	game_map.AddKingdom(12);
	game_map.AddKingdom(13);
	game_map.AddKingdom(14);
	game_map.AddKingdom(15);
	game_map.AddKingdom(16);
	game_map.GenerateMapByLine();
	EXPECT_TRUE(game_map.GetKingdomMap(0)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(1)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(2)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(3)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(4)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(5)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(6)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(7)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(8)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(9)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(10)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(11)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(12)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(13)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(14)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(15)->list_v.size() >= 588);
	EXPECT_TRUE(game_map.GetKingdomMap(16)->list_v.size() >= 588);

}
*/
/*
TEST(MapGameObjGenerateMap, generate_large_map)
{
	MapGameObj game_map(1000000000, 1000000000, 1);
	EXPECT_TRUE(true);
}


TEST(MapGameObjGenerateMap, balance_check_with_odd_points_and_even_count_kingdoms)
{
	MapGameObj game_map(33, 33, 1);
	for (int i = 0; i < 10; ++i) {
		game_map.AddKingdom(i);
	}
	game_map.GenerateMapByLine();
	for (int i = 1; i < 9; ++i) {
		EXPECT_TRUE(game_map.GetKingdomMap(i)->list_v.size() == game_map.GetKingdomMap(i + 1)->list_v.size());
	}
	EXPECT_TRUE(game_map.GetKingdomMap(0)->list_v.size() - game_map.GetKingdomMap(1)->list_v.size() == 1); // KingdomMap with id=0 +1 point disbalanced
}
*/

