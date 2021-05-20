#include "pch.h"
#include "../TurnBasedStrategy/resource.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(ResourceBase, ConstructCall_withZeroCost){
	Resource res0 = Resource(0,0);
	EXPECT_EQ(res0.cost_conventional_units,1);
}

TEST(ResourceBase, OperatorAssigment_callDividingByZer0){
	Resource res0 = Resource(0,0);
	Resource res10 = Resource(10,10);
	res0=res10;
	EXPECT_EQ(res0.count_,100);
}

TEST(ResourceBase, ConstructCall){
	Resource res10 = Resource(1,10);
	Resource res5 = Resource(1,5);
	EXPECT_EQ(res10.cost_conventional_units , 10);
	EXPECT_EQ(res5.cost_conventional_units, 5);
}

TEST(ResourceBase, OperatorAssigment){
	Resource res10 = Resource(10,10);
	Resource res5 = Resource(10,5);
	res5 = res10;
	EXPECT_EQ(res5.count_ , 20);
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
	EXPECT_EQ(res5.count_ , 40);

}

TEST(ResourceOperatorOverloading, Operator_sum_assig){
	Resource res10 = Resource(10,10);
	res10 += res10 ;
	EXPECT_EQ(res10.count_ , 20);
}

TEST(ResourceOperatorOverloading, Operator_minus){
	Resource res10 = Resource(10,10);
	Resource res5 = Resource(10,5);
	res5 = res10 - res10;
	EXPECT_EQ(res5.count_, 0);
}

TEST(ResourceOperatorOverloading, Operator_minus_assig){
	Resource res10 = Resource(10,10);
	res10 -= res10 ;
	EXPECT_EQ(res10.count_ , 0);
}

TEST(ResourceOperatorOverloading, Operator_sum_int){
	Resource res10 = Resource(10,10);
	res10 = res10 + 5;
	EXPECT_EQ(res10.count_ , 15);
}

TEST(ResourceOperatorOverloading, Operator_minus_int){
	Resource res10 = Resource(10,10);
	res10 = res10 - 5;
	EXPECT_EQ(res10.count_ , 5);
}

TEST(ResourceOperatorOverloading, Operator_pref_inc){
	Resource res10 = Resource(10,10);
	Resource ress=++res10;
	EXPECT_EQ(res10.count_ , 11);
	EXPECT_EQ(ress.count_,11);
}

TEST(ResourceOperatorOverloading, Operator_post_int){
	Resource res10 = Resource(10,10);
	Resource ress = res10++;
	EXPECT_EQ(res10.count_ , 11);
	EXPECT_EQ(ress.count_,10);
	ress = res10;
	EXPECT_EQ(ress.count_, 11);
}

TEST(ResourceOperatorOverloading, Operator_post_dec){
	Resource res10 = Resource(10,10);
	Resource ress = res10--;
	EXPECT_EQ(res10.count_ , 9);
	EXPECT_EQ(ress.count_,10);
	ress = res10;
	EXPECT_EQ(ress.count_, 9);
}

TEST(ResourceOperatorOverloading, Operator_pred_dec){
	Resource res10 = Resource(10,10);
	Resource ress = --res10;
	EXPECT_EQ(res10.count_ ,9 );
	EXPECT_EQ(ress.count_,9);
}

class Gold_ut: public Resource{
	public:
		Gold_ut(unsigned count):Resource(count,10000){};
};

class Wood_ut: public Resource{
	public:
		Wood_ut(unsigned count):Resource(count,100){};
};

TEST(ResourceArchTest,OneGoldConvertToHundredWood){
	Gold_ut gold = Gold_ut(1);
	Wood_ut wood = Wood_ut(0);
	Resource& g = gold;
	Resource& w = wood;
	w = g;
	EXPECT_EQ(wood.count_,100);
}

class Cost_ut{
	public:
		int buy_,consumption_,sell_; //in 0.01
		Cost_ut(int buy, int consumption, int sell):buy_(buy),consumption_(consumption),sell_(sell){};
};

