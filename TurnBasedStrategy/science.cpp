#include "science.h"
//#include <memory>

TheScience::TheScience(std::string nameScience) 
{
	name = nameScience;
	progress = 0;
	progressLimit = 100;
	scienistForce = 1.0;
	scienceLvl = 0;
}


float TheScience::Scienist_force()
{
	return 0.0f;
}

void TheScience::Increase(unsigned scienist_count)
{
	progress_ = progress_ + static_cast<unsigned>(scienist_count * scienist_force_);
	if (progress_ > progress_limit_) 
	{
		++science_lvl_;
		progress_ = progress_ - progress_limit_;
		progress_limit_ += progress_limit_ / 20; // add 20 % to limit
	}
}

unsigned TheScience::GetCountSpecialists()
{
	return 0;
}

void TheScience::AddScienist()
{
}

KingdoomScience::KingdoomScience()
{
	
}

unsigned KingdoomScience::GetCountSpecialists()
{
	return 0;
}

void KingdoomScience::NextTurn()
{
	// двигаюсь по списку научных объектов
	// высчитываю новое значение прогесса
	// если прогрес больше чем макс то поднимаю уровень и переношу избыточный прогресс на следующий уровень
}

std::string KingdoomScience::GetSummariesString()
{
	return std::string();
}

void SubjectScience::Increase(unsigned scienist_count)
{
}

KingdoomScience& Science_game_obj::GetScience_from_Kingdom(unsigned kingdom_id)
{
	// TODO: вставьте здесь оператор return
}

void Science_game_obj::SaveState()
{
}

void Science_game_obj::LoadState()
{
}

void Science_game_obj::CreateState(unsigned num_players, unsigned map_size)
{
}

void Science_game_obj::NextTurn()
{
}
