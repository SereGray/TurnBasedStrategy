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
