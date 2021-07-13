#include"economics.h"

// Demography

Demography::Demography(): all_people_(0),increase_people_(0),maximum_people_(0),fermers_people_(0){};

void Demography::NextTurn(unsigned area, unsigned increasing_lvl, unsigned densety_lvl){
	maximum_people_ = std::round(static_cast<double>(area) * ((static_cast<double>(densety_lvl)/100.0) + 1.0));
	increase_people_ =( all_people_ ) / 20  ; //TODO: add Population growth science_ lvl
	increase_people_ = std::round(static_cast<double>(increase_people_) *((static_cast<double>(increasing_lvl) / 10.0) + 1.0));
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



// KingdoomEconomics

KingdoomEconomics::KingdoomEconomics(EconomicsGameObj& master, unsigned my_id):gold_(10000),food_(10000000),\
nation_(Demography()), profit_gold_(0),consumption_gold_(0),increase_resourse_(0),consumption_resourse_(0),\
visiter_(*this,&VisitorChangeCountSpecialists),my_id_(my_id),my_master_(master){};


unsigned KingdoomEconomics::GetMyId()
{
	return my_id_;
}

bool KingdoomEconomics::SellResourse(Resource& in, int count)
{
	if (count <= 0) return false;
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
	if (count <= 0) return false;
	Resource& gold = gold_;
	Resource temporary = in;
	in.count_ = count;
	if( (gold - temporary).count_ < 0 ) return false;
	gold = gold - in.count_;
	in = in + count;	
	return true;

}

void KingdoomEconomics::NextTurn()
{
	nation_.NextTurn(MyArea(),GetIncreasingLvl(),GetDensityLvl());
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

// TODO: check typeid(cost) if there are no matches
// TODO: check input
// TODO: test
bool KingdoomEconomics::VisitorChangeCountSpecialists(KingdoomEconomics& eco, BaseCost& cost, int count)
{
	Resource& gld = eco.gold_, &wd = eco.food_;
	if (count > 0) {
		if (typeid(cost) == typeid(UnitCost<Gold>&)) {
			UnitCost<Gold>& costgld = static_cast<UnitCost<Gold>&>(cost);
			if ((gld - costgld.Buy() * count).count_ < 0) return false;

		}
		if (typeid(cost) == typeid(UnitCost<Food>&)) {
			UnitCost<Food>& costwd = static_cast<UnitCost<Food>&>(cost);
			if ((wd - costwd.Buy() * count).count_ < 0) return false;
			wd -= (costwd.Buy() * count);
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

void KingdoomEconomics::ChangeCountSpecialists(Specialist& spec,unsigned count)
{
	//TODO reg spec-s
	spec.Accept(visiter_, count);	
}

// EconomicsGameObj class
EconomicsGameObj::EconomicsGameObj(){};
EconomicsGameObj::~EconomicsGameObj(){}

KingdoomEconomics* EconomicsGameObj::GetKingdoomEconomics(unsigned by_id)
{
	return GetObjFromVectorUt(by_id, v_economics_);
}
void EconomicsGameObj::AddKingdomEconomics(unsigned by_id)
{
	v_economics_.push_back(KingdoomEconomics(*this,by_id));
}
;
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
	return science_obj_->GetKingdoomScience(by_id)->GetDensityLvl();
}
unsigned EconomicsGameObj::GetIncreasingLvl(unsigned by_id){
	return science_obj_->GetKingdoomScience(by_id)->GetIncreasingLvl();
}
