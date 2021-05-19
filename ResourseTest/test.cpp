#include "pch.h"
#include "../TurnBasedStrategy/resourse.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(ResourseBase, ConstructCall_withZeroCost){
	Resourse res0 = Resourse(0,0);
	EXPECT_EQ(res0.cost_conventional_units,1);
}

TEST(ResourseBase, OperatorAssigment_callDividingByZer0){
	Resourse res0 = Resourse(0,0);
	Resourse res10 = Resourse(10,10);
	res0=res10;
	EXPECT_EQ(res0.count_,100);
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

TEST(ResourseOperatorOverloading, Operator_eq){
	Resourse res10 = Resourse(10,10);
	Resourse res5 = Resourse(10,5);
	EXPECT_FALSE(res10==res5);

}

TEST(ResourseOperatorOverloading, Operator_sum){
	Resourse res10 = Resourse(10,10);
	Resourse res5 = Resourse(10,5);
	res5 = res10 + res10;
	EXPECT_EQ(res5.count_ , 40);

}

TEST(ResourseOperatorOverloading, Operator_sum_assig){
	Resourse res10 = Resourse(10,10);
	res10 += res10 ;
	EXPECT_EQ(res10.count_ , 20);
}

TEST(ResourseOperatorOverloading, Operator_minus){
	Resourse res10 = Resourse(10,10);
	Resourse res5 = Resourse(10,5);
	res5 = res10 - res10;
	EXPECT_EQ(res5.count_, 0);
}

TEST(ResourseOperatorOverloading, Operator_minus_assig){
	Resourse res10 = Resourse(10,10);
	res10 -= res10 ;
	EXPECT_EQ(res10.count_ , 0);
}

TEST(ResourseOperatorOverloading, Operator_sum_int){
	Resourse res10 = Resourse(10,10);
	res10 = res10 + 5;
	EXPECT_EQ(res10.count_ , 15);
}

TEST(ResourseOperatorOverloading, Operator_minus_int){
	Resourse res10 = Resourse(10,10);
	res10 = res10 - 5;
	EXPECT_EQ(res10.count_ , 5);
}

TEST(ResourseOperatorOverloading, Operator_pref_inc){
	Resourse res10 = Resourse(10,10);
	Resourse ress=++res10;
	EXPECT_EQ(res10.count_ , 11);
	EXPECT_EQ(ress.count_,11);
}

TEST(ResourseOperatorOverloading, Operator_post_int){
	Resourse res10 = Resourse(10,10);
	Resourse ress = res10++;
	EXPECT_EQ(res10.count_ , 11);
	EXPECT_EQ(ress.count_,11);
}

TEST(ResourseOperatorOverloading, Operator_post_dec){
	Resourse res10 = Resourse(10,10);
	Resourse ress = res10--;
	EXPECT_EQ(res10.count_ , 9);
	EXPECT_EQ(ress.count_,9);
}

TEST(ResourseOperatorOverloading, Operator_pred_dec){
	Resourse res10 = Resourse(10,10);
	Resourse ress = --res10;
	EXPECT_EQ(res10.count_ ,9 );
	EXPECT_EQ(ress.count_,9);
}
