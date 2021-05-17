#include"economics.h"

// Demography

Demography::Demography(Economics& master): all_people_(0),increase_people_(0),maximum_people_(0),fermers_people_(0),my_master_(&master){};

void Demography::NextTurn(){
	maximum_people_ = static_cast<unsigned>(static_cast<double>(my_master_->MyArea()) * ((static_cast<double>(my_master_->GetDensityLvl())/100.0) + 1.0));
	increase_people_ =( all_people_ * (my_master_->MyArea())) / 10 ;
	if(all_people_ < maximum_people_ && increase_people_ + all_people_ > maximum_people_){
	       	increase_people_ = maximum_people_ - all_people_;
	}else if(all_people_ >= maximum_people_) increase_people_ =0;
}

void Demography::IncreaseFermersPeople()
{
	all_people_+=increase_people_;
	fermers_people_ += increase_people_;
}

void Demography::DecreaseFermersPeople(unsigned decrease_count)
{
	fermers_people_ -= decrease_count;
}

// Economics

Economics::Economics(EconomicsGameObj& master, unsigned my_id):nation_(Demography(*this)),my_id_(my_id),my_master_(master){};

unsigned Economics::MyArea(){
	return my_master_.MyArea(my_id_);
}

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
	nation_.NextTurn();
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

unsigned Economics::GetDensityLvl(){ return my_master_.GetDensityLvl(my_id_);}

// EconomicsGameObj class
void EconomicsGameObj::SetInterface(std::vector<EngineGameObjInterface*> list_in)
{
for(EngineGameObjInterface* infc: list_in){
	if (typeid(*infc) == typeid(*science_obj_))
	{
		science_obj_ = dynamic_cast<Science_game_obj*>(infc);
	}
	if(typeid(*infc) == typeid(*map_obj_))
	{
		map_obj_ = dynamic_cast<Game_map_obj*>(infc);
	}
}
}

unsigned EconomicsGameObj::MyArea(unsigned by_id){
	return map_obj_->area_of(by_id);
}

unsigned EconomicsGameObj::GetDensityLvl(unsigned by_id){
	return science_obj_->GetKingdoomScience(by_id).GetDensityLvl();
}
