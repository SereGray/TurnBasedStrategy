#include "science.h"
#include <cmath>
#include <iostream>
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

TheScience& TheScience::operator()(const TheScience& other)
{
	progress_ = other.progress_;
	progress_limit_ = other.progress_limit_;
	scienist_force_ = other.scienist_force_;
	count_scienist_ = other.count_scienist_;
	scienist_lvl_ = other.scienist_lvl_;
	science_lvl_ = other.science_lvl_;
	name_ = other.name_;
	return *this;
}



void TheScience::NextTurn()
{
	progress_ = progress_ + static_cast<unsigned>(std::round((count_scienist_ * scienist_force_)));
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

int TheScience::GetCountSpecialists()
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




SubjectScience& SubjectScience::operator()(TheScience* base_science, const SubjectScience& other)
{
	pbase_science_ = base_science;
	progress_ = other.progress_;
	progress_limit_ = other.progress_limit_;
	scienist_force_ = other.scienist_force_;
	count_scienist_ = other.count_scienist_;
	scienist_lvl_ = other.scienist_lvl_;
	science_lvl_ = other.science_lvl_;
	name_ = other.name_;
	return *this;
}

void SubjectScience::NextTurn()
{
	scienist_force_ = pbase_science_->GetScienistForce();
	progress_ = progress_ + static_cast<unsigned>(std::round((count_scienist_ * scienist_force_)));
	while (progress_ >= progress_limit_)
	{
		++science_lvl_;
		progress_ = progress_ - progress_limit_;
		progress_limit_ += progress_limit_ / 10; // add 10 % to limit
	}
}

// KingdoomScience

unsigned KingdoomScience::GetMyId() const
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

void KingdoomScience::ChangeFreeSpecialists(int count)
{
	if (count < 0 && free_scienists_ - std::abs(count) > 0) {
		free_scienists_ += count;
	}
	else if (count < 0 && free_scienists_ - std::abs(count) <= 0) {
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
	int count_scienist = sub_science.GetCountSpecialists();
	if (count < 0 && count_scienist - std::abs(count) > 0) {
		sub_science.ChangeCountSpecialists(count);
		free_scienists_ -= count;
	}
	else if (count < 0 && count_scienist - std::abs(count) <=0 ){
		sub_science.ChangeCountSpecialists( count_scienist * (-1));
		free_scienists_ += count_scienist;
	}
	else if (count >= 0 && free_scienists_ - std::abs(count) > 0) {
		sub_science.ChangeCountSpecialists(count);
		free_scienists_ -= count;
	}
	else if (count >= 0 && free_scienists_ - std::abs(count) <=0 ) {
		sub_science.ChangeCountSpecialists(free_scienists_);
		free_scienists_ = 0;
	}
}

unsigned KingdoomScience::GetCountSpecialists(TheScience& sub_science)
{
	return sub_science.GetCountSpecialists();
}

KingdoomScience::KingdoomScience(const KingdoomScience& other)
{
	science_(other.science_);
	densety_people_(&science_,other.densety_people_);
	increase_people_(&science_, other.increase_people_);
	harvesting_(&science_, other.harvesting_);
	selling_res_ (&science_, other.selling_res_);
	war_craft_(&science_, other.war_craft_);
	free_scienists_ =other.free_scienists_;
	my_id_ = other.GetMyId();
}


void KingdoomScience::NextTurn()
{
	science_.NextTurn();
	densety_people_.NextTurn();
	increase_people_.NextTurn();
	harvesting_.NextTurn();
	selling_res_.NextTurn();
	war_craft_.NextTurn();
	// �������� �� ������ ������� ��������
	// ���������� ����� �������� ��������
}

std::string KingdoomScience::GetSummariesString()
{
	return std::string();
}

void KingdoomScience::ResetAllSpecialist()
{
	ChangeCountSpec_Science(science_.GetCountSpecialists() * (-1));
	ChangeCountSpec_DensetyPeople(densety_people_.GetCountSpecialists() * (-1));
	ChangeCountSpec_IncreasePeople(increase_people_.GetCountSpecialists() * (-1));
	ChangeCountSpec_Harvesting(harvesting_.GetCountSpecialists() * (-1));
	ChangeCountSpec_SellingRes(selling_res_.GetCountSpecialists() * (-1));
	ChangeCountSpec_WarCraft(war_craft_.GetCountSpecialists() * (-1));
}


std::pair<unsigned, unsigned> KingdoomScience::GetProgress_DensetyPeople()
{
	return densety_people_.GetProgress();
}

std::pair<unsigned, unsigned> KingdoomScience::GetProgress_Science()
{
	return science_.GetProgress();
}

std::pair<unsigned, unsigned> KingdoomScience::GetProgress_IncreasePeople()
{
	return increase_people_.GetProgress();
}

std::pair<unsigned, unsigned> KingdoomScience::GetProgress_Harvesting()
{
	return harvesting_.GetProgress();
}

std::pair<unsigned, unsigned> KingdoomScience::GetProgress_SellingRes()
{
	return selling_res_.GetProgress();
}

std::pair<unsigned, unsigned> KingdoomScience::GetProgress_WarCraft()
{
	return war_craft_.GetProgress();
}

// ������� ������ �����
//class ScienceGameObj

ScienceGameObj::ScienceGameObj() {}

ScienceGameObj::~ScienceGameObj() {}

KingdoomScience* ScienceGameObj::GetKingdoomScience(unsigned by_id)
{
	return GetObjFromVectorUt(by_id, v_kingdom_science);
}

void ScienceGameObj::AddKingdoom(unsigned by_id)
{
	v_kingdom_science.push_back(KingdoomScience(by_id));
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
	for (auto &kingd : v_kingdom_science)
	{
		kingd.NextTurn();
	}
}


