#ifndef UNITS
#define UNITS

#include<vector>

#include"resource.h"

struct Unit {
	unsigned count_;
	//TODO: vector<BaseCost&> costs
	//TODO: initialistion with variadic arg - BaseCost&
	UnitCost<Gold> gold_;
	UnitCost<Food> food_;
	BaseCost& r_gold_;
	BaseCost& r_food_;
	Unit(UnitCost<Gold> gold, UnitCost<Food> food);

	template<class Visitor> // visitor pattern - visitor buy/sell units in kingdom economics undependent regardless of the number of types of resources
	bool Accept(Visitor f, unsigned count) {
		if (!f(r_gold_, count)) {
			return false;
		}
		if (!f(r_food_, count)) {
			return false;
		}
		return true;
	};
};

class UnitsInterface
{
public:
	virtual ~UnitsInterface();
	virtual std::vector<Unit&> GetUnits()=0;
	virtual void ChangeCountOfUnits(Unit&, int)=0;
};

#endif UNITS
