#ifndef UNITS
#define UNITS

#include"resource.h"

struct Specialist {
	unsigned count_;
	UnitCost<Gold> gold_;
	UnitCost<Food> food_;
	BaseCost& r_gold_;
	BaseCost& r_food_;
	Specialist(UnitCost<Gold> gold, UnitCost<Food> food);
	template<class Visitor>
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


#endif UNITS
