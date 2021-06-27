#include "science.h"
//#include <memory>



TheScience::TheScience(std::string nameScience) 
{
	name_ = nameScience;
	progress_ = 0;
	progress_limit_ = 100;
	scienist_force_ = 1.0;
	count_scienist_ = 0;
	science_lvl_ = 0;
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


// KingdoomScience

unsigned KingdoomScience::GetMyId()
{
	return my_id_;
}

unsigned KingdoomScience::GetCountSpecialists()
{
	return 0;
}

unsigned KingdoomScience::GetWarcraftLvl()
{
	return war_craft_.science_lvl_;
}

unsigned KingdoomScience::GetDensityLvl()
{
	return densety_people_.science_lvl_;
}	

unsigned KingdoomScience::GetIncreasingLvl()
{
	return increase_people_.science_lvl_;
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

// игровой объект наука
//class ScienceGameObj

ScienceGameObj::ScienceGameObj() {}

ScienceGameObj::~ScienceGameObj() {}

KingdoomScience& ScienceGameObj::GetKingdoomScience(unsigned kingdom_id)
{
	return v_kingdom_science[kingdom_id];
}

void ScienceGameObj::AddKingdoom(unsigned by_id)
{
	v_kingdom_science.push_back(KingdoomScience(by_id));
}

//TODO: return ref
KingdoomScience* ScienceGameObj::GetKingdoom(unsigned by_id)
{
	return GetObjFromVectorUt(by_id, v_kingdom_science);
}

void ScienceGameObj::SetInterface(std::vector<EngineGameObjInterface*> list_in)
{
}

void ScienceGameObj::SaveState()
{
}

void ScienceGameObj::LoadState()
{
}

void ScienceGameObj::CreateState(unsigned num_players, unsigned map_size)
{
}

void ScienceGameObj::NextTurn()
{
}


