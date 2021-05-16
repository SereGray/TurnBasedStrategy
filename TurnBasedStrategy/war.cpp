#include "war.h"
#include <cmath>
#include <memory>
#include<algorithm>
#include<limits>

void General::Workout()
{
	action_ = 2;
	my_master_->AddSolder(count_solders_);
	count_solders_ = 0;
	target_ = MAXUINT;
}

void General::Study()
{
	
	action_ = 1;
	my_master_->AddSolder(count_solders_);
	count_solders_ = 0;
	target_ = MAXUINT;
}

void General::Defense(unsigned count_defenders)
{
	action_ = 3;
	count_solders_ = count_defenders;
	target_ = MAXUINT;
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
	case 1:
		++intelegence_;
	case 2:
		skill_float_ += ((intelegence_ / 10) * (spirit_ / 100));
		skill_ = static_cast<unsigned>(skill_float_);
		if (skill_ > 100) skill_ = 100;
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


General::General(Kingdoom_defense& my_master, std::string name, unsigned skill, unsigned spirit, unsigned speed_, unsigned intelegence \
	, unsigned age):my_master_(&my_master), skill_(skill), intelegence_(intelegence), spirit_(spirit), speed_(speed_), age_(age), action_(0), name_(name), target_ (MAXUINT), count_solders_(0) // TODO: check err 
{
	skill_float_ = static_cast<float>(skill);	
	my_id_ = my_master_->v_general_.size();
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
target_= MAXUINT;
my_id_ = MAXUINT;
}


void General::AttackTo(unsigned count_attack, unsigned number_kingd)
{
	count_solders_ = count_attack;
	target_ = number_kingd;
}

void General::Rest()
{
	action_ = 0;
	target_ = MAXUINT;
}


// Kingdoom defense

void Kingdoom_defense::DeleteGeneral(unsigned my_id){
	auto it = std::find_if(v_general_.begin(), v_general_.end(), [my_id](General& gen) {if (gen.GetMyId() == my_id)return true; return false; });
	if(it != v_general_.end()){
		v_general_.erase(it);
	}else{//TODO:err
	}
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

unsigned Kingdoom_defense::GetCountSpecialists()
{
	return solders_;
}

float Kingdoom_defense::GetSolderForce()
{
	unsigned lvl = master_.GetWarCraftLevel(my_id_); // TODO: test this
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
	master_.summaries_ += text + "\n";
}

std::string Kingdoom_defense::GetSummaryString()
{
	return std::string();
}


unsigned Kingdoom_defense::AddGeneral(std::string name, unsigned skill, unsigned intelegence,unsigned speed, unsigned age)
{
	General gen = General::CreateGeneral(*this, name, skill, intelegence, 100, speed, age);
	v_general_.push_back(gen);
	return gen.GetMyId();
}

void Kingdoom_defense::SetAttack(General& gen, unsigned target){
	gen.target_=target;
}

// Defense class

// this function for GetLocalWars() 
int Defense::SearchLocalWar(unsigned kingd1_number, unsigned kingd2_number) //return index in vector
{
	unsigned count = 0;
	for (std::pair<unsigned,unsigned> lw : vlocal_wars_) {
		if ((lw.first == kingd1_number && lw.second == kingd2_number) || (lw.first == kingd2_number && lw.second == kingd1_number)) return count;
		++count;
	}
	return MAXUINT; // error
}
std::pair<unsigned,unsigned> Defense::MaxSpeedGeneral(std::pair<unsigned,unsigned> kd) {
	std::pair<unsigned, unsigned> max_speed = std::make_pair(0,0);
	for (General g : vkingdoom_def_[kd.first].v_general_) {
		if (g.speed_ > max_speed.first) max_speed.first = g.speed_;
	};
	for (General g : vkingdoom_def_[kd.second].v_general_) {
		if (g.speed_ > max_speed.second) max_speed.second = g.speed_;
	};
	return max_speed;
}
void Defense::SortLocalWarsByGeneralSpeed()
{
	std::sort(vlocal_wars_.begin(), vlocal_wars_.end(), [this](std::pair<unsigned, unsigned> left, std::pair<unsigned, unsigned> right){
	std::pair<unsigned,unsigned> left_max_speed = MaxSpeedGeneral(left);
	std::pair<unsigned, unsigned> right_max_speed = MaxSpeedGeneral(right);
	if (left_max_speed.first < right_max_speed.first || left_max_speed.second < right_max_speed.first || left_max_speed.first < right_max_speed.second || left_max_speed.second < right_max_speed.second) return true;
	return false; });
}

bool Defense::LocalWarNoAttackers(std::vector<std::pair<unsigned, unsigned>>::iterator it)
{
	if(map_obj_->area_of(it->first)==0 || map_obj_->area_of(it->second)==0) return true; //проверка существования гос - ва
	for (General g : vkingdoom_def_[it->first].v_general_) {
		if (g.action_ == 4 && g.count_solders_ > 0) return false;   
	}
	for (General g : vkingdoom_def_[it->second].v_general_) {
		if (g.action_ == 4 && g.count_solders_ > 0) return false;
	}
	return true;
}

std::pair<General&, General&> Defense::GetPairBattleGeneral(std::vector<std::pair<unsigned,unsigned>>::iterator it)
{
	return make_pair(std::ref(vkingdoom_def_[it->first].GetSpeedestGeneral(it->second)),std::ref(vkingdoom_def_[it->second].GetSpeedestGeneral(it->first)));
}

//TODO: test
void Defense::SetInterface(std::vector<EngineGameObjInterface*> list_in){  // TODO:this получаю игровые объекты исп RTTI
	for(EngineGameObjInterface* infc: list_in){
	if(typeid(*infc) == typeid(*map_obj_))map_obj_ = dynamic_cast<Game_map_obj*>(infc);	
	if (typeid(*infc) == typeid(*science_obj))science_obj = dynamic_cast<Science_game_obj*>(infc);
	}
}
	
void Defense::GetLocalWars() {
	// TODO: refactor this 
	 // получаю список атакующих генералов
	for (Kingdoom_defense& kd : vkingdoom_def_) {
		for (General& gen : kd.v_general_) {
			if (gen.action_ == 4) {
				// если генерал атакует проверяю есть ли локальная война если есть то пропускаю
				// если нет то создаю
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

void Defense::ClearLocalWars()
{
	vlocal_wars_.clear();
}

void Defense::SaveState()
{
}

void Defense::LoadState()
{
}

void Defense::CreateState(unsigned num_players, unsigned map_size)
{
	for (unsigned i = 0; i < num_players; ++i) {
		Kingdoom_defense kingd(i,*this);
		vkingdoom_def_.push_back(kingd);
	}
}

void Defense::NextTurn()
{
	// создаем список локальных войн
	vlocal_wars_.clear();
	for(Kingdoom_defense& kd: vkingdoom_def_){
		kd.NextTurn();
	};
	GetLocalWars();
	// цикл пока есть атакующие генералы
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
			//				-- в зависимости от результата вызываем метод перераспределиения территории
			std::string summaries_battle  = map_obj_->ExchangeArea(res,battle_gen.first.GetMaster()->my_id_,battle_gen.first.count_solders_ , battle_gen.second.GetMaster()->my_id_ , battle_gen.second.count_solders_);
			//TODO add summaries
	}
}


//TODO: balance game Battle
// return 100 if first gen win, else -100. if no clear victory or drav return num betwen -100 and 100;
int Defense::Battle(General& attacker, General& defender)
{
	float attacker_force = attacker.GetSolderForce();
	float defender_force = defender.GetSolderForce();
	int res = 0;
	for (int i = 0; i < 3; ++i) {
		float attacker_k = (attacker.skill_ / 100) * (attacker.intelegence_ / 100) * (attacker.spirit_ / 100) * (attacker.speed_ / 100);
		float defender_k = (defender.skill_ / 100) * (defender.intelegence_ / 100) * (defender.spirit_ / 100) * (defender.speed_ / 100);
		float total_count_relation = (defender.count_solders_ * defender_k * defender_force) / (attacker.count_solders_ * attacker_k * attacker_force);
		if (total_count_relation < 0.1) { // полное превосходство атакующего
			res = 100;
			defender.count_solders_ = 0;
			break;
		}else if(total_count_relation > 10.0){ // полное превосходство защиты
			res = -100;
			attacker.count_solders_ = 0;
			break;
		}
		else { // некритическое превосходство
			// потери солдат в бою
			attacker.count_solders_ = attacker.count_solders_ * 70 / 100;
			defender.count_solders_ = defender.count_solders_ * 70 / 100;
			// усталость генералов ( чем меньше дух тем быстрее он падает)
			attacker.spirit_ = attacker.spirit_ - static_cast<unsigned>(log(110 - attacker.spirit_)) * 3;
			defender.spirit_ = attacker.spirit_ - static_cast<unsigned>(log(110 - attacker.spirit_)) * 3;
			attacker.skill_ += log(defender.count_solders_ + 1);
			defender.skill_ += log(attacker.count_solders_ + 1);
		}
	}
	return res;
}

unsigned Defense::GetWarCraftLevel(unsigned my_id_)
{
	return science_obj->GetKingdoomScience(my_id_).GetWarcraftLvl();
}

std::string Defense::GetSummariesString()
{
	return std::string();
}

Defense::~Defense() {

}
