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


void TheScience::Increase(unsigned scienist_count)
{
	progress_ = progress_ + static_cast<unsigned>(scienist_count * scienist_force_);
	if (progress_ > progress_limit_) 
	{
		++scienceLvl_;
		progress_ = progress_ - progress_limit_;
		progress_limit_ += progress_limit_ / 20; // add 20 % to limit
	}
}

KingdoomScience::KingdoomScience()
{
	std::vector<std::string> scienseList = { "Densety People", "Increase People", "Harvesting","Selling Res", "War craft" };
	// TODO: 1) for in sciense_list ������� scienseList_vector
	// science_vector= add demography incrase, demography density,  ...
	// ��������� ���������, ������� ���������, ���� �����, ������� �����, ������� ����, �����
	for (std::string name_science : scienseList) {
		std::unique_ptr<TheScience> pointer(new SubjectScience(name_science));
		science_list_vector.push_back(pointer); // TODO: replace to moving 
	}
	science_list_vector.push_back(std::unique_ptr<TheScience>(new TheScience("Science")));
}

void KingdoomScience::NextTurn()
{
	// �������� �� ������ ������� ��������
	// ���������� ����� �������� ��������
	// ���� ������� ������ ��� ���� �� �������� ������� � �������� ���������� �������� �� ��������� �������
}
