#include"economics.h"

// Demography

Demography::Demography(KingdoomEconomics* master): all_people_(0),increase_people_(0),maximum_people_(0),fermers_people_(0),my_master_(master){};

void Demography::NextTurn(){
	// TODO:Decreasing people
	maximum_people_ = static_cast<unsigned>(static_cast<double>(my_master_->MyArea()) * ((static_cast<double>(my_master_->GetDensityLvl())/100.0) + 1.0));
	increase_people_ =( all_people_ ) / 20  ; //TODO: add Population growth science lvl
	increase_people_ = increase_people_ / 100 * my_master_->GetIncreasingLvl();
	if(all_people_ > maximum_people_) increase_people_ = (maximum_people_ - all_people_) / -10;
	// calculating incrase_people_
	if(all_people_ < maximum_people_ && (increase_people_ + all_people_) > maximum_people_){
	       	increase_people_ = maximum_people_ - all_people_;
	}else if(all_people_ >= maximum_people_) increase_people_ =0;
	IncreaseFermersPeople();
}

void Demography::IncreaseFermersPeople()
{
	//TODO: fermers always <= area of kingdom()
	all_people_+=increase_people_;
	fermers_people_ += increase_people_;
}

void Demography::DecreaseFermersPeople(unsigned decrease_count)
{
	//TODO: throw decreasing > fermers_people
	if(fermers_people_ < decrease_count) decrease_count = fermers_people_ ;
	fermers_people_ -= decrease_count;
}


// Gold
Gold::Gold(int count) : Resource(count, 10000)
{
}

// Food
Food::Food(int count) : Resource(count, 100)
{
}

// BaseCost
BaseCost::~BaseCost() {};

Resource& BaseCost::Buy() 
{ 
	Resource res(0, 1);
	return res; 
};

// UnitCost class

template<typename TypeResource>
UnitCost<TypeResource>::UnitCost(int buy, int consumption, int sell) :buy_(buy), consumption_(consumption), sell_(sell)
{
}

template<typename TypeResource>
Resource& UnitCost<TypeResource>::Buy()
{
	return buy_;
}

template<typename TypeResource>
Resource& UnitCost<TypeResource>::Consumption()
{
	return consumption_;
}

template<typename TypeResource>
Resource& UnitCost<TypeResource>::Sell()
{
	return sell_;
}

// KingdoomEconomics

KingdoomEconomics::KingdoomEconomics(EconomicsGameObj& master, unsigned my_id):gold_(10000),food_(10000000),nation_(Demography(this)),visiter_(*this,&VisitorBuySpecialist),my_id_(my_id),my_master_(master){};


unsigned KingdoomEconomics::MyId()
{
	return my_id_;
}

bool KingdoomEconomics::SellResourse(Resource& in, int count)
{
	//TODO: throw if in == gold_
	if(in.count_ < count) return false;
	Resource& gold = gold_;
	Resource temporary = in;
	temporary.count_ = count;
	gold = gold + temporary;
	in = in - count;	
	return true;
}

bool KingdoomEconomics::BuyResourse(Resource& in, int count)
{
	Resource& gold = gold_;
	Resource temporary = in;
	in.count_ = count;
	if( (gold - temporary).count_ < 0 ) return false;
	gold = gold - in.count_;
	in = in + count;	
	return true;

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

void KingdoomEconomics::VisitorBuySpecialist(KingdoomEconomics& eco, BaseCost& cost, int count)
{
	Resource& gld = eco.gold_; // Если написать в одну строку Resource& gld = .., wd=.. то gld - ref , а wd - НЕТ !!!!!!!
	Resource& wd = eco.food_;
	if (typeid(cost) == typeid(UnitCost<Gold>&)) {
		UnitCost<Gold>& castgld = static_cast<UnitCost<Gold>&>(cost);
		gld -= (castgld.Buy() * count);
	}
	if (typeid(cost) == typeid(UnitCost<Food>&)) {
		UnitCost<Food>& costwd = static_cast<UnitCost<Food>&>(cost);
		wd -= (costwd.Buy() * count);
	}
}

unsigned KingdoomEconomics::GetDensityLvl()
{ 
	return my_master_.GetDensityLvl(my_id_);
}

unsigned KingdoomEconomics::GetIncreasingLvl()
{ 
	return my_master_.GetIncreasingLvl(my_id_);
}

unsigned KingdoomEconomics::MyArea() {
	return my_master_.MyArea(my_id_);
}

void KingdoomEconomics::BuySpecialist(unsigned count)
{
	pikiner_.Accept(visiter_, count);
}

// EconomicsGameObj class
EconomicsGameObj::EconomicsGameObj(){};
EconomicsGameObj::~EconomicsGameObj(){};
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
	return map_obj_->AreaKingdoom(by_id);
}

unsigned EconomicsGameObj::GetDensityLvl(unsigned by_id){
	return science_obj_->GetKingdoomScience(by_id).GetDensityLvl();
}
unsigned EconomicsGameObj::GetIncreasingLvl(unsigned by_id){
	return science_obj_->GetKingdoomScience(by_id).GetIncreasingLvl();
}

Specialist::Specialist():gold{ UnitCost<Gold>(100, 2, 0) }, food{ UnitCost<Food>(5, 1, 5) }, gold_(gold), food_(food)
{
}
