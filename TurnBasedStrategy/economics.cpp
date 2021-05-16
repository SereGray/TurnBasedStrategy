#include"economics.h"

// Demography
void Demography::TncreaseFermersPeople()
{
}

void Demography::DecreaseFermersPeople()
{
}

// Economics
void Economics::SellResourse()
{
}

void Economics::BuyResourse()
{
}

void Economics::CostToCropsResourse()
{
}

void Economics::BuyThing()
{
}

void Economics::NextTurn()
{
}

std::string Economics::GetSummariesString()
{
	return std::string();
}

void Economics::ResourseConsumption()
{
}

uint64_t Economics::CalculationConsumption()
{
	return uint64_t();
}

uint64_t Economics::CalculationSpecialistSalary()
{
	return uint64_t();
}

uint32_t Economics::CalculationSpecialistHiring()
{
	return uint32_t();
}

// EconomicsGameObj class
void EconomicsGameObj::SetInterface(std::vector<EngineGameObjInterface*> list_in)
{
for(EngineGameObjInterface* infc: list_in){
	if (typeid(*infc) == typeid(*science_obj_))
	{
		science_obj_ = dynamic_cast<Science_game_obj*>(infc);
	}
}
}

