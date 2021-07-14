#include<functional>
#include "pch.h"
#include "../TurnBasedStrategy/resource.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(ResourceBase, ConstructCall_withZeroCost){
	Resource res0 = Resource(0,0);
	EXPECT_EQ(res0.cost_conventional_units_,1);
}

TEST(ResourceBase, OperatorAssigment_callDividingByZer0){
	Resource res0 = Resource(0,0);
	Resource res10 = Resource(10,10);
	res0=res10;
	EXPECT_EQ(res0.Count(),100);
}

TEST(ResourceBase, ConstructCall){
	Resource res10 = Resource(1,10);
	Resource res5 = Resource(1,5);
	EXPECT_EQ(res10.cost_conventional_units_ , 10);
	EXPECT_EQ(res5.cost_conventional_units_, 5);
}

TEST(ResourceBase, OperatorAssigment){
	Resource res10 = Resource(10,10);
	Resource res5 = Resource(10,5);
	res5 = res10;
	EXPECT_EQ(res5.Count(), 20);
}

TEST(ResourceOperatorOverloading, Operator_eq){
	Resource res10 = Resource(10,10);
	Resource res5 = Resource(10,5);
	EXPECT_FALSE(res10==res5);

}

TEST(ResourceOperatorOverloading, Operator_sum){
	Resource res10 = Resource(10,10);
	Resource res5 = Resource(10,5);
	res5 = res10 + res10;
	EXPECT_EQ(res5.Count(), 40);

}

TEST(ResourceOperatorOverloading, Operator_sum2){
	Resource res10 = Resource(10,10);
	res10 = res10 + res10;
	EXPECT_EQ(res10.Count(),20);
	Resource res10_2 = Resource(13,10);
	res10 = res10 + res10_2;
	EXPECT_EQ(res10.Count(),33);
}

TEST(ResourceOperatorOverloading, Operator_sum_assig){
	Resource res10 = Resource(12,10);
	res10 += res10 ;
	EXPECT_EQ(res10.Count(), 24);
}

TEST(ResourceOperatorOverloading, Operator_minus){
	Resource res10 = Resource(13,10);
	Resource res5 = Resource(13,5);
	Resource res10_2 = Resource(0 ,10);
	EXPECT_FLOAT_EQ((res10_2 - res5).count_,-6.5);
	res10_2 = res10_2 - res5;
	EXPECT_FLOAT_EQ(res10_2.count_, -6.5); 
	res5 = res10 - res5;
	EXPECT_FLOAT_EQ(res5.count_, 13);
	res10 = res5;
	EXPECT_EQ(res10.count_,6.5);

}

TEST(ResourceOperatorOverloading, Operator_minus2){
	Resource res10 = Resource(10,10);
	Resource res5 = Resource(30,10);
	res5 = res5 - res10;
	EXPECT_EQ(res5.Count(), 20);

}

TEST(ResourceOperatorOverloading, Operator_minus_assig){
	Resource res10 = Resource(10,10);
	res10 -= res10 ;
	EXPECT_EQ(res10.Count(), 0);
}

TEST(ResourceOperatorOverloading, Operator_sum_int){
	Resource res10 = Resource(10,10);
	res10 = res10 + 5;
	EXPECT_EQ(res10.Count(), 15);
}

TEST(ResourceOperatorOverloading, Operator_multiple_int){
	Resource res7(1,7);
	res7 = res7 * 10;
	EXPECT_EQ(res7.Count(), 10);
}

TEST(ResourceOperatorOverloading, Operator_minus_int){
	Resource res10 = Resource(10,10);
	res10 = res10 - 5;
	EXPECT_EQ(res10.Count(), 5);
}

TEST(ResourceOperatorOverloading, Operator_pref_inc){
	Resource res10 = Resource(10,10);
	Resource ress=++res10;
	EXPECT_EQ(res10.Count(), 11);
	EXPECT_EQ(ress.Count(),11);
}

TEST(ResourceOperatorOverloading, Operator_post_int){
	Resource res10 = Resource(10,10);
	Resource ress = res10++;
	EXPECT_EQ(res10.Count(), 11);
	EXPECT_EQ(ress.Count(),10);
	ress = res10;
	EXPECT_EQ(ress.Count(), 11);
}

TEST(ResourceOperatorOverloading, Operator_post_dec){
	Resource res10 = Resource(10,10);
	Resource ress = res10--;
	EXPECT_EQ(res10.Count(), 9);
	EXPECT_EQ(ress.Count(),10);
	ress = res10;
	EXPECT_EQ(ress.Count(), 9);
}

TEST(ResourceOperatorOverloading, Operator_pred_dec){
	Resource res10 = Resource(10,10);
	Resource ress = --res10;
	EXPECT_EQ(res10.Count() ,9 );
	EXPECT_EQ(ress.Count(),9);
}

TEST(ResourceOperatorOverloading, Operator_ConvUn_Base_Test) {
	Resource res3(10, 3);
	Resource res10(1, 10);
	EXPECT_EQ(3, (res3 - res10).cost_conventional_units_);
	EXPECT_EQ(10, (res10 - res3).cost_conventional_units_);
}
TEST(ResourceOperatorOverloading, RoundingTest) {
	Resource res3(10, 3);
	Resource res10(1, 10);
	EXPECT_NEAR(6.7f, (res3 - res10).count_,0.1);
	EXPECT_EQ(7, (res3 - res10).Count());
	EXPECT_FLOAT_EQ(-2.0, (res10-res3).count_);
	EXPECT_EQ(-2, (res10 - res3).Count()); // wrong rounding 1.9999 to 1
}

class Gold_ut: public Resource{
	public:
		Gold_ut(int count):Resource(count,10000){};
};

class Wood_ut: public Resource{
	public:
		Wood_ut(int count):Resource(count,100){};
};

TEST(ResourceArchTest,OneGoldConvertToHundredWood){
	Gold_ut gold = Gold_ut(1);
	Wood_ut wood = Wood_ut(0);
	Resource& g = gold;
	Resource& w = wood;
	w = g;
	EXPECT_EQ(wood.count_,100);
}

