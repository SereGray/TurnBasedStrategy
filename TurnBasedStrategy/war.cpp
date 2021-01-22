#include "war.h"

void General::Workout()
{
	action_ = 2;
	//skill_float_ += ((intelegence_ / 10) * (spirit_ / 100));
	//skill_ = static_cast<unsigned>(skill_float_);
}

void General::Study()
{
	
	action_ = 1;
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

Kingdoom_defense::Kingdoom_defense(unsigned my_number)
	:solders_(10), solder_force_(1.0), my_n_ = (my_number)
{
}
