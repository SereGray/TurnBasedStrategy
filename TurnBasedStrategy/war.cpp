#include "war.h"

void General::Workout()
{
	skill_float_ += ((intelegence / 10) * (spirit / 100));
	skill = static_cast<unsigned> skill_float_;
}

void General::Study()
{
	++intelegence;
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
