#include "units.h"

Specialist::Specialist(UnitCost<Gold> gold, UnitCost<Food> food) :gold_{ UnitCost<Gold>(100, 2, 0) }, food_{ UnitCost<Food>(5, 1, 5) }, r_gold_(gold_), r_food_(food_)
{
}

