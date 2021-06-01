#include<functional>
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

TEST(ResourceOperatorOverloading, Operator_sum2){
	Resource res10 = Resource(10,10);
	res10 = res10 + res10;
	EXPECT_EQ(res10.count_,20);
	Resource res10_2 = Resource(13,10);
	res10 = res10 + res10_2;
	EXPECT_EQ(res10.count_,33);
}

TEST(ResourceOperatorOverloading, Operator_sum_assig){
	Resource res10 = Resource(12,10);
	res10 += res10 ;
	EXPECT_EQ(res10.count_ , 24);
}

TEST(ResourceOperatorOverloading, Operator_minus){
	Resource res10 = Resource(13,10);
	Resource res5 = Resource(13,5);
	Resource res10_2 = Resource(0 ,10);
	EXPECT_EQ((res10_2 -res5).count_,-6);
	res10_2 = res10_2 - res5;
	EXPECT_EQ(res10_2.count_, -6);
	res5 = res10 - res5;
	EXPECT_EQ(res5.count_, 12);//TODO: DOUBLE TO INT mayby 13
	EXPECT_EQ(res10.count_,13);
	res10 = res5;
	EXPECT_EQ(res10.count_,6);

}

TEST(ResourceOperatorOverloading, Operator_minus2){
	Resource res10 = Resource(10,10);
	Resource res5 = Resource(30,10);
	res5 = res5 - res10;
	EXPECT_EQ(res5.count_, 20);

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

TEST(ResourceOperatorOverloading, Operator_multiple_int){
	Resource res7(1,7);
	res7 = res7 * 10;
	EXPECT_EQ(res7.count_, 10);
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

TEST(ResourceArchTest,GoldMinusGold){
	Gold_ut gold = Gold_ut(10);
	Gold_ut gold2 = Gold_ut(2);
	Resource& g1 = gold;
	Resource& g2 =gold2;
	//EXPECT_TRUE(false)<<"g1 count"<< g1.count_;
	g1 = g1 - g2;
	EXPECT_EQ(gold.count_, 8)<<" g1 count"<< g1.count_<<" g2.count_"<<g2.count_;
	g1 -=g2;
	EXPECT_EQ(gold.count_, 6);
}

// Error
/*TEST(ResourceArchTest, OneGoldConvertToHundredWoodWithoutBase){
	Gold_ut gold = Gold_ut(1);
	Wood_ut wood = Wood_ut(0);
	wood = gold;
	EXPECT_EQ(wood.count_,100);

}*/
class Base_cost {
	public:
	virtual ~Base_cost();
	virtual Resource& Buy();
};
Base_cost::~Base_cost(){};
Resource& Base_cost::Buy(){};
template<typename T_res>
class Cost_ut: public Base_cost{
	public:
		T_res buy_,consumption_,sell_; //in 0.01
	public:
		Cost_ut(int buy, int consumption, int sell):buy_(buy),consumption_(consumption),sell_(sell){};
		Resource& Buy() override {return buy_;};
		Resource& Consumpt(){return consumption_;};
		Resource& Sell(){return sell_;};
};

TEST(ResourceArchTest, SpecialistCostSystemTest){
	Gold_ut g = Gold_ut(100);
	Wood_ut w = Wood_ut(500);
	Resource& gold =g;
	Cost_ut<Gold_ut> Pikiner = Cost_ut<Gold_ut>(10,1,-1);	
	Cost_ut<Gold_ut> Boat = Cost_ut<Gold_ut>(50,25,-25);
	EXPECT_EQ(gold.count_,100);
	// Buying 3 pikiners
	for(int i=0;i<3;++i){
		gold = gold - Pikiner.Buy();
	}
	EXPECT_EQ(gold.count_,70);
	// Sell 2 pikiners
	gold = gold - Pikiner.Sell();
        gold = gold - Pikiner.Sell();	
	EXPECT_EQ(gold.count_, 72);
	// consumption at 5 times 1 pikines
	for(int i=0;i<5;++i){
		gold = gold - Pikiner.Consumpt();
	}
	EXPECT_EQ(gold.count_, 67);
}

class spec{
	public:
	Cost_ut<Gold_ut> gold;
	Cost_ut<Wood_ut> wood;
	Base_cost& gold_, wood_;
		spec() :gold{Cost_ut<Gold_ut>(10, 2, 0)}, wood{Cost_ut<Wood_ut>(5, 1, 5)},gold_(gold), wood_(wood) {};
		template<typename Visitor>
		void Accept(Visitor f,unsigned count=1) {
			f(gold_,count);
			f(wood_, count);
		};
};
class eco;
struct Visiter{
	eco& e_;
	void (*ptrFunct_)(eco&,Base_cost&, int);
	Visiter(eco& e,void (*ptrFunct)(eco&,Base_cost&, int)):e_(e),ptrFunct_(ptrFunct){};
	void operator()(Base_cost& cost, int count){
		ptrFunct_(e_,cost,count);
	}
};

class eco{
	public:
	int i;
	Gold_ut gold_;
	Wood_ut wood_;
	spec pikiner_;
	Visiter visiter_;
	eco(int gold, int wood):i(50),gold_(gold),wood_(wood), visiter_(Visiter(*this,&BuySpec)){};
	void BuyS(unsigned count){
		pikiner_.Accept(visiter_,count);
	}
	static void BuySpec(eco& e, Base_cost& cost, int count){
		Resource& gld = e.gold_, wood = e.wood_;
		if(typeid(cost) == typeid(Cost_ut<Gold_ut>)){ 
			Cost_ut<Gold_ut>& castgld = static_cast<Cost_ut<Gold_ut>&>(cost);
			gld -= (castgld.Buy() * count); 
		}
		if(typeid(cost) == typeid(Cost_ut<Wood_ut>)){ 
			Cost_ut<Wood_ut>& castgld = static_cast<Cost_ut<Wood_ut>&>(cost);
			wood -= (castgld.Buy() * count); 
		}

	}

};
TEST(ResourceArchTest, byingSpec){
	eco e = eco(100,300);
	spec pikiner;
	e.BuyS(1);	
	EXPECT_EQ(e.gold_.count_,90);
	EXPECT_EQ(e.wood_.count_,295);
}
