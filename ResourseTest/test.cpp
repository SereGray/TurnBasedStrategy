#include "pch.h"
#include "../TurnBasedStrategy/resourse.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(ResourseBase, ConstructCall){
	Resourse res10 = Resourse(1,10);
	Resourse res5 = Resourse(1,5);
	EXPECT_EQ(res10.cost_conventional_units , 10);
	EXPECT_EQ(res5.cost_conventional_units, 5);
}

TEST(ResourseBase, OperatorAssigment){
	Resourse res10 = Resourse(10,10);
	Resourse res5 = Resourse(10,5);
	res5 = res10;
	EXPECT_EQ(res5.count_ , 20);
}

TEST(ResourseOperatorOverloading, Operator_sum){
	Resourse res10 = Resourse(10,10);
	Resourse res5 = Resourse(10,5);
	res5 = res10 + res10;
	EXPECT_EQ(res5.count_ , 40);

}
