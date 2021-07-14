#include "pch.h"
#include"../TurnBasedStrategy/units.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(Debug_UnitTestCase, CreationTest) {
	UnitCost<Gold> gold(1, 1, 1);
	UnitCost<Food> food(3, 3, 3);
	Unit unit_(gold,food);
}

class FakeKingdom {
	struct Visiter {
		FakeKingdom& e_;
		bool (*ptrFunct_)(FakeKingdom&, BaseCost&, int);
		Visiter(FakeKingdom& e, bool (*ptrFunct)(FakeKingdom&, BaseCost&, int)) :e_(e), ptrFunct_(ptrFunct) {};
		bool operator()(BaseCost& cost, int count) {
			return ptrFunct_(e_, cost, count);
		}
	};

	Visiter visiter_;

	static bool VisitorChangeCountSpecialists_Empty(FakeKingdom& eco, BaseCost& cost, int count) {
		Resource& gld = eco.gold_, & wd = eco.food_;
		if (count > 0) {
			if (typeid(cost) == typeid(UnitCost<Gold>&)) {
				UnitCost<Gold>& costgld = static_cast<UnitCost<Gold>&>(cost);
				if ((gld - costgld.Buy() * count).count_ < 0) return false;

			}
			if (typeid(cost) == typeid(UnitCost<Food>&)) {
				UnitCost<Food>& costwd = static_cast<UnitCost<Food>&>(cost);
				if ((wd - costwd.Buy() * count).count_ < 0) return false;
			}
			if (typeid(cost) == typeid(UnitCost<Gold>&)) {
				UnitCost<Gold>& costgld = static_cast<UnitCost<Gold>&>(cost);
				gld -= (costgld.Buy() * count);
			}
			if (typeid(cost) == typeid(UnitCost<Food>&)) {
				UnitCost<Food>& costwd = static_cast<UnitCost<Food>&>(cost);
				wd -= (costwd.Buy() * count);
			}
			return true;
		}
		if (count < 0) {
			if (typeid(cost) == typeid(UnitCost<Gold>&)) {
				UnitCost<Gold>& costgld = static_cast<UnitCost<Gold>&>(cost);
				gld += (costgld.Sell() * count);
			}
			if (typeid(cost) == typeid(UnitCost<Food>&)) {
				UnitCost<Food>& costwd = static_cast<UnitCost<Food>&>(cost);
				wd -= (costwd.Sell() * count);
			}
			return true;
		}
		return true;
	}
public:
	Gold gold_;
	Food food_;
	FakeKingdom(int gold, int food): gold_(gold), food_(food),visiter_(*this, &VisitorChangeCountSpecialists_Empty) {};
	bool BuyUnit(Unit& in, unsigned count) { return in.Accept(visiter_, count); };
};

TEST(Debug_UnitTestCase, CreationTestWithFakeKingdom) {
	UnitCost<Gold> gold(1, 1, 1);
	UnitCost<Food> food(3, 3, 3);
	Unit unit(gold, food);
	FakeKingdom fkingdom(1000,1000);
	EXPECT_TRUE(fkingdom.BuyUnit(unit, 1));
	EXPECT_EQ(999, fkingdom.gold_.count_);
	EXPECT_EQ(997, fkingdom.food_.count_);
}

class Iron : public Resource {
public:
	Iron(int in) :Resource(in, 10) {};
};

class Pikiner : public Unit {
public:
	Pikiner(UnitCost<Gold> gold, UnitCost<Food> food, UnitCost<Iron> iron) : Unit::Unit(gold, food), iron_(iron), r_iron_(iron_) {};
private:
	UnitCost<Iron> iron_;
	BaseCost& r_iron_;

	template<class Visitor> // visitor pattern - visitor buy/sell units in kingdom economics undependent regardless of the number of types of resources
	bool Accept(Visitor f, unsigned count) {
		if (!f(r_gold_, count)) {
			return false;
		}
		if (!f(r_food_, count)) {
			return false;
		}
		if (!f(r_iron_, count)) {
			return false;
		}
		return true;
	};
};

TEST(UnitTestCase, UnitWithAdditionalCosts) 
{
	UnitCost<Gold> gold(1, 1, 1);
	UnitCost<Food> food(3, 3, 3);
	UnitCost<Iron> iron(4, 3, 2);
	Pikiner pikiner(gold, food, iron);
	FakeKingdom fkingdom(1000, 1000);
	EXPECT_TRUE(fkingdom.BuyUnit(pikiner, 1));
	EXPECT_EQ(999, fkingdom.gold_.count_);
	EXPECT_EQ(997, fkingdom.food_.count_);
	Unit unit(gold, food);
	EXPECT_TRUE(fkingdom.BuyUnit(unit, 1));
	EXPECT_EQ(998, fkingdom.gold_.count_);
	EXPECT_EQ(994, fkingdom.food_.count_);
}

TEST(UnitTestCase, BuyUnitWithNoMoney) {
	UnitCost<Gold> gold(1, 1, 1);
	UnitCost<Food> food(3, 3, 3);
	Unit unit(gold, food);
	FakeKingdom fkingdom(0, 1000);
	EXPECT_FALSE(fkingdom.BuyUnit(unit, 1));
	EXPECT_EQ(0, fkingdom.gold_.count_);
	EXPECT_EQ(1000, fkingdom.food_.count_);
}