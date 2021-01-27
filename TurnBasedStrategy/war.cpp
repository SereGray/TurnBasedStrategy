#include "war.h"
#include <cmath>

void General::Workout()
{
	action_ = 2;
	//skill_float_ += ((intelegence_ / 10) * (spirit_ / 100));
	//skill_ = static_cast<unsigned>(skill_float_);
	// TODO: return solders
}

void General::Study()
{
	
	action_ = 1;
	// TODO : return solders
}

void General::Defense(unsigned count_defenders)
{
	action_ = 3;
	count_solders_ = count_defenders;
}

void General::NextTurn()
{
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

General::General(std::string name, unsigned skill, unsigned spirit, unsigned speed_, unsigned intelegence, unsigned age): skill_(skill), intelegence_(intelegence), spirit_(spirit), speed_(speed), age_(age), name_(name)
{
	skill_float_ = static_cast<float>(skill);	
}

void General::AttackTo(unsigned count_attack, unsigned number_kingd)
{
	count_solders_ = count_attack;
}

void General::Rest()
{
	action_ = 0;
}

void Kingdoom_defense::AddSolder(unsigned count)
{
	solders_+=count;	
}

unsigned Kingdoom_defense::GetCountSpecialists()
{
	return solders_;
}

void Kingdoom_defense::AddGeneral(std::string name, unsigned skill, unsigned intelegence, unsigned age)
{
	General new_general(name, skill, 100, intelegence, age);
	this->vGeneral_list.push_back(new_general);
}

void Defense::CreateState(unsigned num_players, unsigned map_size)
{
	for (unsigned i = 0; i < num_players; ++i) {
		Kingdoom_defense kingd(i);
		vkingdoom_def.push_back(kingd);
	}
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

Kingdoom_defense::Kingdoom_defense(unsigned my_number)
	:solders_(10), solder_force_(1.0), my_n_ = (my_number)
{
}
