#include"economics.h"

// Demography

Demography::Demography(KingdoomEconomics& master): all_people_(0),increase_people_(0),maximum_people_(0),fermers_people_(0),my_master_(&master){};

void Demography::NextTurn(){
	maximum_people_ = static_cast<unsigned>(static_cast<double>(my_master_->MyArea()) * ((static_cast<double>(my_master_->GetDensityLvl())/100.0) + 1.0));
	increase_people_ =( all_people_ * (my_master_->MyArea())) / 10 ; //TODO: add Population growth science lvl
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

// KingdoomEconomics

KingdoomEconomics::KingdoomEconomics(EconomicsGameObj& master, unsigned my_id):nation_(Demography(*this)),my_id_(my_id),my_master_(master){};

unsigned KingdoomEconomics::MyArea(){
	return my_master_.MyArea(my_id_);
}

void KingdoomEconomics::SellResourse()
{
}

void KingdoomEconomics::BuyResourse()
{
}

void KingdoomEconomics::CostToCropsResourse()
{
}

void KingdoomEconomics::BuyThing()
{
}

void KingdoomEconomics::NextTurn()
{
	nation_.NextTurn();
}

std::string KingdoomEconomics::GetSummariesString()
{
	return std::string();
}

void KingdoomEconomics::ResourseConsumption()
{
}

uint64_t KingdoomEconomics::CalculationConsumption()
{
	return uint64_t();
}

uint64_t KingdoomEconomics::CalculationSpecialistSalary()
{
	return uint64_t();
}

uint32_t KingdoomEconomics::CalculationSpecialistHiring()
{
	return uint32_t();
}

unsigned KingdoomEconomics::GetDensityLvl(){ return my_master_.GetDensityLvl(my_id_);}

// EconomicsGameObj class
void EconomicsGameObj::SetInterface(std::vector<EngineGameObjInterface*> list_in)
{
for(EngineGameObjInterface* infc: list_in){
	if (typeid(*infc) == typeid(*science_obj_))
	{
		science_obj_ = dynamic_cast<ScienceGameObj*>(infc);
	}
	if(typeid(*infc) == typeid(*map_obj_))
	{
		map_obj_ = dynamic_cast<MapGameObj*>(infc);
	}
}
}

unsigned EconomicsGameObj::MyArea(unsigned by_id){
	return map_obj_->area_of(by_id);
}

unsigned EconomicsGameObj::GetDensityLvl(unsigned by_id){
	return science_obj_->GetKingdoomScience(by_id).GetDensityLvl();
}
