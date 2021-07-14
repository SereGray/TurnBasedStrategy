#include "units.h"


Unit::Unit(UnitCost<Gold> gold, UnitCost<Food> food) :gold_{ gold }, food_{ food }, r_gold_(gold_), r_food_(food_)
{
}


//

UnitsInterface::~UnitsInterface() {};
/* pure virtual ?
std::vector<Unit&> UnitsInterface::GetUnits()
{
	// empty
}


void UnitsInterface::ChangeCountOfUnits(Unit& unit,int count)
{
	// empty
}
*/