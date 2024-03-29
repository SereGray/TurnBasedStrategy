#include "war.h"
#include <cmath>
#include <memory>
#include<algorithm>
#include<limits>

unsigned General::next_general_id = 0;
void General::Workout()
{
	action_ = 2;
	GetMaster()->AddSolder(count_solders_);
	count_solders_ = 0;
	target_ = UINT_MAX;
}

void General::Study()
{
	
	action_ = 1;
	GetMaster()->AddSolder(count_solders_);
	count_solders_ = 0;
	target_ = UINT_MAX;
}

void General::Defense(unsigned count_defenders)
{
	action_ = 3;
	count_solders_ = count_defenders;
	GetMaster()->DecreaseSolders(count_defenders);
	target_ = UINT_MAX;
}

void General::NextTurn()
{
	if(action_ == 5) return;
	++age_;
	if (age_ > 50) {
		if (rand() % 10 < 1) {
			this->Dead();
			return;
		}
	}
	switch (action_)
	{
	case 0:
		spirit_ += 5;
		if (spirit_ > 100)spirit_ = 100;
		break;
	case 1:
		++intelegence_;
		if (spirit_ > 2)
		{
			spirit_ -= 2;
		}
		else
		{
			spirit_ = 0;
		}
		break;
	case 2:
		skill_float_ += ((intelegence_ / 10) * (spirit_ / 100));
		skill_ = static_cast<unsigned>(skill_float_);
		if (skill_ > 100) skill_ = 100;
		if (spirit_ > 2) 
		{
			spirit_ -= 2;
		}
		else
		{
			spirit_ = 0;
		}
		break;
	case 3:
		if (spirit_ > 4)
		{
			spirit_ -= 4;
		}
		else
		{
			spirit_ = 0;
		}
		break;
	default:
		break;
	}
}


void General::Dead()
{
	// add summary
	my_master_->AddSummaryString("General " + name_ + " is dead died at an advanced age ");
	my_master_->DeleteGeneral(my_id_);
	// call destroyer object
	action_ = 5;
	General::~General();
}

Kingdoom_defense* General::GetMaster()
{
	return my_master_;
}

float General::GetSolderForce()
{
	return GetMaster()->GetSolderForce();
}

unsigned General::GetMyId()
{
	return my_id_;
}

unsigned General::GetNextId()
{
	return next_general_id;
}




General::General(Kingdoom_defense& my_master, std::string name, unsigned skill, unsigned intelegence, unsigned spirit, unsigned speed, \
	unsigned age):my_master_(&my_master), skill_(skill), intelegence_(intelegence), spirit_(spirit), speed_(speed), age_(age), action_(0),\
	name_(name), target_ (UINT_MAX), count_solders_(0) // TODO: check err 
{
	skill_float_ = static_cast<float>(skill);	
	my_id_ = next_general_id++;
}

void General::SetNullId()
{
	next_general_id = 0;
}

General General::CreateGeneral(Kingdoom_defense& my_master, std::string name, unsigned skill, unsigned intelegence, unsigned spirit, unsigned speed, unsigned age)
{
	General gen =General(my_master, name,  skill,  intelegence,  spirit,  speed,  age);
	return gen;
}

General::General(Kingdoom_defense& my_master):my_master_(&my_master)
{
skill_=0;
intelegence_=0;
spirit_=0;
speed_=0;
age_=0;
name_="landaun";
target_= UINT_MAX;
my_id_ = UINT_MAX;
}


void General::AttackTo(unsigned count_attack, unsigned number_kingd)
{
	action_ = 4;
	count_solders_ = count_attack;
	GetMaster()->DecreaseSolders(count_attack);
	target_ = number_kingd;
}

void General::Rest()
{
	action_ = 0;
	GetMaster()->AddSolder(count_solders_);
	count_solders_ = 0;
	target_ = UINT_MAX;
}


// Kingdoom defense

void Kingdoom_defense::DeleteGeneral(unsigned by_id){
	auto it = std::find_if(v_general_.begin(), v_general_.end(), [by_id](General& gen) {if (gen.GetMyId() == by_id)return true; return false; });
	if(it != v_general_.end()){
		v_general_.erase(it);
	}else{//TODO:err
	}
}

General& Kingdoom_defense::GetGeneral(unsigned by_id)
{
	auto it = std::find_if(v_general_.begin(), v_general_.end(), [by_id](General& gen) {if (gen.GetMyId() == by_id)return true; return false; });
	if (it != v_general_.end()) {
		return *it;
	}
	else { /*err*/ };
	return *it;
}

unsigned Kingdoom_defense::GetIndexOfGeneral(unsigned by_id)
{
	auto it = std::find_if(v_general_.begin(), v_general_.end(), [by_id](General& gen) {if (gen.GetMyId() == by_id)return true; return false; });
	if (it != v_general_.end()) {
		return static_cast<unsigned>(std::distance(v_general_.begin(), it));
	}
	else { 
		/*err*/ 
		return UINT_MAX; // crash . . . TODO: this
	};
	
}

Kingdoom_defense::Kingdoom_defense(unsigned my_number, WarGameObj& master) :solders_(0), solder_force_(1.0), \
my_id_(my_number), master_(&master), landaun_(*this)
{
}

General& Kingdoom_defense::GetSpeedestGeneral(unsigned target)
{
	long long speed = -1;
	unsigned count=0;
	long long index=-1; // if has no General - err
	for(General g: v_general_){
		if(g.speed_>speed && g.target_ == target && g.count_solders_ > 0){  // TODO: check exceptions if solders==0 
			index = count;
			speed = g.speed_;
		}
		++count;
	}
	if (speed == -1) return landaun_; // TODO: check
	return v_general_[index];
}

void Kingdoom_defense::AddSolder(unsigned count)
{
	solders_+=count;	
}

void Kingdoom_defense::DecreaseSolders(unsigned count)
{
	solders_ -= count;
}

unsigned Kingdoom_defense::GetCountFreeSpecialists()
{
	return solders_;
}

float Kingdoom_defense::GetSolderForce()
{
	unsigned lvl = master_->GetWarCraftLevel(my_id_); // TODO: test this
	return 1.0f + (lvl / 10);
}

//TODO: this
void Kingdoom_defense::NextTurn()
{
	for (General& gen : v_general_) {
		gen.NextTurn(); // start next turn general
	}
}

void Kingdoom_defense::AddSummaryString(std::string text)
{
	master_->summaries_ += text + "\n";
}

std::string Kingdoom_defense::GetSummaryString()
{
	return std::string();
}


unsigned Kingdoom_defense::AddGeneral(std::string name, unsigned skill, unsigned intelegence, unsigned speed, unsigned age)
{
	General gen = General::CreateGeneral(*this, name, skill, intelegence, 100, speed, age);
	v_general_.push_back(gen);
	return gen.GetMyId();
}

void Kingdoom_defense::SetAttack(General& gen, unsigned solders, unsigned target){
	gen.AttackTo(solders, target);
}

// WarGameObj class

// this function for GetLocalWars() 
int WarGameObj::SearchLocalWar(unsigned kingd1_number, unsigned kingd2_number) //return index in vector
{
	unsigned count = 0;
	for (std::pair<unsigned,unsigned> lw : vlocal_wars_) {
		if ((lw.first == kingd1_number && lw.second == kingd2_number) || (lw.first == kingd2_number && lw.second == kingd1_number)) return count;
		++count;
	}
	return UINT_MAX; // error
}
std::pair<unsigned,unsigned> WarGameObj::MaxSpeedGeneral(std::pair<unsigned,unsigned> kd) {
	std::pair<unsigned, unsigned> max_speed = std::make_pair(0,0);
	for (General g : vkingdoom_def_[kd.first].v_general_) {
		if (g.speed_ > max_speed.first) max_speed.first = g.speed_;
	};
	for (General g : vkingdoom_def_[kd.second].v_general_) {
		if (g.speed_ > max_speed.second) max_speed.second = g.speed_;
	};
	return max_speed;
}
void WarGameObj::SortLocalWarsByGeneralSpeed()
{
	std::sort(vlocal_wars_.begin(), vlocal_wars_.end(), [this](std::pair<unsigned, unsigned> left, std::pair<unsigned, unsigned> right){
	std::pair<unsigned,unsigned> left_max_speed = MaxSpeedGeneral(left);
	std::pair<unsigned, unsigned> right_max_speed = MaxSpeedGeneral(right);
	if (left_max_speed.first < right_max_speed.first || left_max_speed.second < right_max_speed.first || left_max_speed.first < right_max_speed.second || left_max_speed.second < right_max_speed.second) return true;
	return false; });
}

bool WarGameObj::LocalWarNoAttackers(std::vector<std::pair<unsigned, unsigned>>::iterator it)
{
	if(map_obj_->AreaKingdom(it->first)==0 || map_obj_->AreaKingdom(it->second)==0) return true; //�������� ������������� ��� - ��
	for (General g : vkingdoom_def_[it->first].v_general_) {
		if (g.action_ == 4 && g.count_solders_ > 0) return false;   
	}
	for (General g : vkingdoom_def_[it->second].v_general_) {
		if (g.action_ == 4 && g.count_solders_ > 0) return false;
	}
	return true;
}

std::pair<General&, General&> WarGameObj::GetPairBattleGeneral(std::vector<std::pair<unsigned,unsigned>>::iterator it)
{
	return make_pair(std::ref(vkingdoom_def_[it->first].GetSpeedestGeneral(it->second)),std::ref(vkingdoom_def_[it->second].GetSpeedestGeneral(it->first)));
}

//TODO: test
void WarGameObj::SetInterface(std::vector<EngineGameObjInterface*> list_in){  // TODO:this ������� ������� ������� ��� RTTI
	for(EngineGameObjInterface* infc: list_in){
	if(typeid(*infc) == typeid(*map_obj_))map_obj_ = dynamic_cast<MapGameObj*>(infc);	
	if (typeid(*infc) == typeid(*science_obj))science_obj = dynamic_cast<ScienceGameObj*>(infc);
	}
}
	
void WarGameObj::GetLocalWars() {
	// TODO: refactor this 
	 // ������� ������ ��������� ���������
	for (Kingdoom_defense& kd : vkingdoom_def_) {
		for (General& gen : kd.v_general_) {
			if (gen.action_ == 4) {
				// ���� ������� ������� �������� ���� �� ��������� ����� ���� ���� �� ���������
				// ���� ��� �� ������
				int found = SearchLocalWar(kd.my_id_, gen.target_);
				if (found < 0) {
					// new localwar
					//vlocal_wars_.push_back(make_pair(std::ref(kd), std::ref(vkingdoom_def_[gen.target_]))); TODO: not work
					vlocal_wars_.push_back(std::make_pair(kd.my_id_, gen.target_));

				}
			}
		}
	}

}

void WarGameObj::ClearLocalWars()
{
	vlocal_wars_.clear();
}

void WarGameObj::SaveState()
{
}

void WarGameObj::LoadState()
{
}

void WarGameObj::CreateState(unsigned num_players, unsigned map_size)
{
	for (unsigned i = 0; i < num_players; ++i) {
		Kingdoom_defense kingd(i,*this);
		vkingdoom_def_.push_back(kingd);
	}
}

void WarGameObj::NextTurn()
{
	// ������� ������ ��������� ����
	vlocal_wars_.clear();
	for(Kingdoom_defense& kd: vkingdoom_def_){
		kd.NextTurn();
	};
	GetLocalWars();
	// ���� ���� ���� ��������� ��������
	while(!vlocal_wars_.empty()) // TODO: where q_local_wars_.empty() ?
	{	
			// sort attack & defense generals by speeed
			SortLocalWarsByGeneralSpeed();
			// get iterator to first local war
			auto it = vlocal_wars_.begin();
			// take first figth generals( sorted by speed of general) 
			std::pair<General&,General&>  battle_gen = GetPairBattleGeneral(it);// take generals by iterator
			int res = Battle(battle_gen.first, battle_gen.second);//TODO:res?
			// if local war has no attacers destroy then vector.clean()
			if (!LocalWarNoAttackers(it)) vlocal_wars_.erase(it); // clear ?
			//				-- � ����������� �� ���������� �������� ����� ������������������ ����������
			std::string summaries_battle  = map_obj_->ExchangeArea(res,battle_gen.first.GetMaster()->my_id_,battle_gen.first.count_solders_ , battle_gen.second.GetMaster()->my_id_ , battle_gen.second.count_solders_);
			//TODO add summaries
	}
}


//TODO: balance game Battle
// TODO: add generals characteristics rise after battle
// return 100 if first gen win, else -100. if no clear victory or drav return num betwen -100 and 100;
int WarGameObj::Battle(General& attacker, General& defender)
{
	float attacker_force = attacker.GetSolderForce();
	float defender_force = defender.GetSolderForce();
	int res = 0;
	for (int i = 0; i < 3; ++i) {
		float attacker_k = (attacker.skill_ / 100) * (attacker.intelegence_ / 100) * (attacker.spirit_ / 100) * (attacker.speed_ / 100);
		float defender_k = (defender.skill_ / 100) * (defender.intelegence_ / 100) * (defender.spirit_ / 100) * (defender.speed_ / 100);
		float total_count_relation = (defender.count_solders_ * defender_k * defender_force) / (attacker.count_solders_ * attacker_k * attacker_force);
		if (total_count_relation < 0.1) { // ������ ������������� ����������
			res = 100;
			defender.count_solders_ = 0;
			break;
		}else if(total_count_relation > 10.0){ // ������ ������������� ������
			res = -100;
			attacker.count_solders_ = 0;
			break;
		}
		else { // ������������� �������������
			// ������ ������ � ���
			attacker.count_solders_ = attacker.count_solders_ * 70 / 100;
			defender.count_solders_ = defender.count_solders_ * 70 / 100;
			// ��������� ��������� ( ��� ������ ��� ��� ������� �� ������)
			attacker.spirit_ = attacker.spirit_ - std::lround(log(110 - attacker.spirit_)) * 3;
			defender.spirit_ = attacker.spirit_ - std::lround(log(110 - attacker.spirit_)) * 3;
			attacker.skill_ += std::lround(log(defender.count_solders_ + 1));
			defender.skill_ += std::lround(log(attacker.count_solders_ + 1));
		}
	}
	return res;
}

unsigned WarGameObj::GetWarCraftLevel(unsigned my_id_)
{
	return science_obj->GetKingdoomScience(my_id_)->GetWarcraftLvl();
}

std::string WarGameObj::GetSummariesString()
{
	return std::string();
}

WarGameObj::~WarGameObj() {

}
