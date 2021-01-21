#include "war.h"

void General::Workout()
{
	skill_float_ += ((intelegence_ / 10) * (spirit_ / 100));
	skill_ = static_cast<unsigned>(skill_float_);
}

void General::Study()
{
	++intelegence_;
}

General::General(std::string name, unsigned skill, unsigned spirit, unsigned intelegence, unsigned age): skill_(skill), intelegence_(intelegence), spirit_(spirit), age_(age), name_(name)
{
	skill_float_ = static_cast<float>(skill);	
}

void Kingdoom_defense::AddSolder(unsigned count)
{
	solders_+=count;	
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
