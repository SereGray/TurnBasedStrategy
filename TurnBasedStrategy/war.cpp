#include "war.h"
#include <cmath>
#include <memory>

void General::Workout()
{
	action_ = 2;
	my_master_.AddSolder(count_solders_);
	count_solders_ = 0;
	target_ = MAXUINT;
}

void General::Study()
{
	
	action_ = 1;
	my_master_.AddSolder(count_solders_);
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
	++age_;
	if (age > 50) {
		if (rand() % 10 < 1) {
			this.Dead();
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
	my_master_.AddSummaryString("General " + name_ + " is dead died at an advanced age ");
	// call destroyer object
	General::~General();
}

General::General(Kingdoom_defense& my_master, std::string name, unsigned skill, unsigned spirit, unsigned speed_, unsigned intelegence, unsigned age,unsigned id):my_master_(my_master), ID_(id), skill_(skill), intelegence_(intelegence), spirit_(spirit), speed_(speed_), age_(age), name_(name), target_ = MAXUINT // TODO: check err 
{
	skill_float_ = static_cast<float>(skill);	
}

General::General(Kingdoom_defense& my_master):my_master_(my_master)
{
skill_=0;
intelegence_=0;
spirit_=0;
speed_=0;
age_=0;
name_="landaun";
target_=MAXUINT;
ID_=MAXUINT;
//TODO:ID?
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
	unsigned lvl = master.GetScience_from_Kingdom(my_n_).war_craft.science_lvl; // TODO: test this
	return 1.0f + (lvl / 10);
}

void Kingdoom_defense::NextTurn()
{
	for (General& gen : vgeneral_list) {
		gen.NextTurn();
	}
}

void Kingdoom_defense::AddSummaryString(string text)
{
	master_.summaries_ += text + "\n";
}

Kingdoom_defense::Kingdoom_defense(unsigned my_number, Defense& master): master_(master), solders_(0), solder_force_(1.0), my_n_(my_number), landaun_(*this, "landaun", 10, 1, 70, 1, 0)
{
	// TODO: check
}

void Kingdoom_defense::AddGeneral(std::string name, unsigned skill, unsigned intelegence,unsigned speed, unsigned age)
{
	General new_general(*this,name, skill, intelegence,100, speed, age);
	unsigned id=master_.map_general.AddGeneral(new_general);
	this->vgeneral_id.push_back(new_general);

}


// Local_war struct
//TODO: this
std::pair<General&, General&> LocalWar::GetPairBattleGeneral()  // выдача первой пары проверка условия наличия солдат(если нет солдат выкинуть из атакующих) 
{
	General& speedy_general = GetMaxSpeedGeneral();
//TODO:	if(speedy_general == landaun) exception
	while(!q_local_wars_.empty() || speedy_general.count_solders_==0){
		//delete current general from atacers vector
		auto it_found = find();
		// if first & second kd has no atackers delete localwar	
		speedy_general = GetMaxSpeedGeneral();
	}

}


// ListLocalWar class

// TODO: sort ?
General& ListLocalWar::GetMaxSpeedGeneral() // сортировка по скорости и нахождение самого быстрого генерала
// поиск быстрых генералов среди атакующих так и среди защищающихся
{
	General landaun;
	General& speedy_General=landaun;
	for (LocalWar lw : v_local_wars_) { 
		for (General ataker_general : lw.first_kd_attacers_) {
			if (ataker_general.speed_ > speedy_General.speed_) {
				speedy_General = ataker_general;
			}
		}
		for (General ataker_genera : lw.second_kd_attacers_) {
			if (ataker_genera > speedy_General.speed_) {
				speedy_General = ataker_general;
			}
		}
	}
return landoun;
}

bool ListLocalWar::AttackersEmpty()
{
	//TODO:this
};

vector<LocalWar> ListLocalWar::GetLocalWars() {
	// TODO: test
	 // получаю список атакующих генералов
	for (Kingdoom_defense& kd : vkingdoom_def) {
		for (General& gen : kd.vgeneral_list) {
			if (gen.action_ == 4) {
				// если генерал атакует проверяю есть ли локальная война если есть то пропускаю
				// если нет то создаю
				int found = SearchLocalWar(kd.my_n_, gen.target_);
				if (found > 0) {
					// add to exist
					// if kd is first in pair add to first gen atacers else to second
					if (kd.my_n_ == q_local_wars_[found].ref_to_kingd_defense_.first.my_n_) {
						v_local_wars_[found].first_kd_attacers_.push_back(gen);
					}
					else v_local_wars_[found].second_kd_attacers_.push_back(gen);
				}
				else {
					// new localwar
					LocalWar new_local_war(kd, vkingdoom_def[gen.target_]);
					v_local_wars_.push_back(new_local_war);
				}
			}
		}
	}

}

int ListLocalWar::SearchLocalWar(unsigned kingd1_number, unsigned kingd2_number) {
	//TODO: this
}


// this function for GetLocalWars() 
int ListLocalWar::SearchLocalWar(unsigned kingd1_number, unsigned kingd2_number) 
{
	unsigned count = 0;
	for(LocalWar lw: q_local_wars_){
	if((lw.first_kd_attacers_==kingd1_number && lw.second_kd_attacers_ == kingd2_number) || (lw.first_kd_attacers_ == kingd2_number && lw.second_kd_attacers_ ==kingd1_number)) return count;
	return -1;	
}

// Defense class

void Defense::SaveState()
{
}

void Defense::LoadState()
{
}

void Defense::CreateState(unsigned num_players, unsigned map_size)
{
	for (unsigned i = 0; i < num_players; ++i) {
		Kingdoom_defense kingd(i);
		vkingdoom_def.push_back(kingd);
	}
}

void Defense::NextTurn()
{
	// создаем список локальных войн
	list_local_wars_.clear();
	list_local_wars_.GetLocalWars();
	// цикл пока есть атакующие генералы
	while(list_local_wars_.v_local_wars_.empty()) // TODO: where q_local_wars_.empty() ?

	{	
	// проводим бои take first local war ( sorted by speed of general) 
	std::pair<General&,General&>  battle_gen = q_local_wars_.first().GetPairBattleGeneral();
	int res = Battle(battle_gen.first,battle_gen.first.my_master_.solder_force_, battle_gen.second, battle_gen.second.my_master_.solder_force_); //TODO: hide solder_force_

	//				-- в зависимости от результата вызываем метод перераспределиения территории
//TODO: Exchange area
	}
}

unsigned Defense::GetCountSpecialists()
{
	return 0;
}

//TODO: balance game Battle
int Defense::Battle(General& attacker, float attacker_force, General& defender, float defender_force)
{
	int res = 0;
	for (int i = 0; i < 3; ++i) {
		float attacker_k = (attacker.skill_ / 100) * (attacker.intelegence_ / 100) * (attacker.spirit_ / 100) * (attacker.speed_ / 100);
		float defener_k = (defender.skill_ / 100) * (defender.intelegence_ / 100) * (defender.spirit_ / 100) * (defender.speed_ / 100);
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

std::string Defense::GetSummariesString()
{
	return std::string();
}

Defense::Defense()
{

}

Kingdoom_defense::Kingdoom_defense(unsigned my_number)
	:solders_(10), solder_force_(1.0), my_n_ = (my_number)
{
}
