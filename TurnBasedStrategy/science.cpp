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



void TheScience::NextTurn()
{
	progress_ = progress_ + static_cast<unsigned>(count_scienist_ * scienist_force_);
	while(progress_ >= progress_limit_) 
	{
		++science_lvl_;
		progress_ = progress_ - progress_limit_;
		progress_limit_ += progress_limit_ / 10; // add 10 % to limit
		scienist_force_ = scienist_force_ + science_lvl_ * 0.01f;
	}
}

float TheScience::GetScienistForce()
{
	return scienist_force_;
}

unsigned TheScience::GetCountSpecialists()
{
	return count_scienist_;
}

void TheScience::ChangeCountSpecialists(int count)
{
	count_scienist_ += count;
}

std::pair<unsigned, unsigned> TheScience::GetProgress()
{
	return std::pair<unsigned, unsigned>(std::make_pair(progress_,progress_limit_));
}

// SubjectScience

void SubjectScience::NextTurn()
{
	scienist_force_ = pbase_science_.GetScienistForce();
	progress_ = progress_ + static_cast<unsigned>(count_scienist_ * scienist_force_);
	while (progress_ >= progress_limit_)
	{
		++science_lvl_;
		progress_ = progress_ - progress_limit_;
		progress_limit_ += progress_limit_ / 10; // add 10 % to limit
	}
}

// KingdoomScience

unsigned KingdoomScience::GetMyId()
{
	return my_id_;
}

unsigned KingdoomScience::GetCountAllSpecialists()
{
	return free_scienists_ + science_.GetCountSpecialists() + densety_people_.GetCountSpecialists() + \
		increase_people_.GetCountSpecialists() + harvesting_.GetCountSpecialists() + selling_res_.GetCountSpecialists()\
		+ war_craft_.GetCountSpecialists(); 
}
unsigned KingdoomScience::GetScienceLvl()
{
	return science_.science_lvl_;
}

unsigned KingdoomScience::GetHarvestingLvl()
{
	return harvesting_.science_lvl_;
}

unsigned KingdoomScience::GetSellingResLvl()
{
	return selling_res_.science_lvl_;
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

void KingdoomScience::ChangeCountSpec_DensetyPeople(int count)
{
	ChangeCountSpecialist(densety_people_, count);
}

void KingdoomScience::ChangeCountSpec_Science(int count) 
{
	ChangeCountSpecialist(science_, count);
}

void KingdoomScience::ChangeCountSpec_IncreasePeople(int count) 
{
	ChangeCountSpecialist(increase_people_, count);
}

void KingdoomScience::ChangeCountSpec_Harvesting(int count) 
{
	ChangeCountSpecialist(harvesting_, count);
}

void KingdoomScience::ChangeCountSpec_SellingRes(int count) 
{
	ChangeCountSpecialist(selling_res_, count);
}

void KingdoomScience::ChangeCountSpec_WarCraft(int count)
{
	ChangeCountSpecialist(war_craft_, count);
}

void KingdoomScience::ChangeFreeSpecialist(int count)
{
	if (count < 0 && free_scienists_ > count) {
		free_scienists_ += count;
	}
	else if (count < 0 && free_scienists_ <= count) {
		free_scienists_ = 0;
	}
	else if (count >= 0) {
		free_scienists_ += count;
	}
}


unsigned KingdoomScience::GetCountSpec_DensetyPeople()
{
	return GetCountSpecialists(densety_people_);
}

unsigned KingdoomScience::GetCountSpec_Science()
{
	return GetCountSpecialists(science_);
}

unsigned KingdoomScience::GetCountSpec_IncreasePeople()
{
	return GetCountSpecialists(increase_people_);
}

unsigned KingdoomScience::GetCountSpec_Harvesting()
{
	return GetCountSpecialists(harvesting_);
}

unsigned KingdoomScience::GetCountSpec_SellingRes()
{
	return GetCountSpecialists(selling_res_);
}

unsigned KingdoomScience::GetCountSpec_WarCraft()
{
	return GetCountSpecialists(war_craft_);
}

unsigned KingdoomScience::GetFreeSpecialist()
{
	return free_scienists_;
}


void KingdoomScience::ChangeCountSpecialist(TheScience& sub_science, int count)
{
	unsigned count_scienist = sub_science.GetCountSpecialists();
	if (count < 0 && count_scienist > count) {
		sub_science.ChangeCountSpecialists(count);
		free_scienists_ -= count;
	}
	else if (count < 0 && count_scienist < count) {
		sub_science.ChangeCountSpecialists( count_scienist * (-1));
		free_scienists_ += count_scienist;
	}
	else if (count >= 0 && free_scienists_ > count) {
		sub_science.ChangeCountSpecialists(count);
		free_scienists_ -= count;
	}
	else if (count >= 0 && free_scienists_ <= count) {
		sub_science.ChangeCountSpecialists(free_scienists_);
		free_scienists_ = 0;
	}
}

unsigned KingdoomScience::GetCountSpecialists(TheScience& sub_science)
{
	return sub_science.GetCountSpecialists();
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


