#include "science.h"
//#include <memory>

TheScience::TheScience(std::string nameScience) : name = nameScience
{
	progress = 0;
	progressLimit = 100;
	scienistForce = 1.0;
	scienceLvl = 0;
}

void TheScience::Increase(unsigned scienist_count)
{
}

ScienseObject::ScienseObject()
{
	std::vector<std::string> scienseList = { "Densety People", "Increase People", "Harvesting","Selling Res", "War craft", "Science" };
	// TODO: 1) for in scienseList создать scienseList_vector
	// science_vector= add demography incrase, demography density,  ...
	// плотность населения, прирост населения, сбор зерна, продажа зерна, военное дело, наука
	for (std::string name_science : scienseList) {
		std::unique_ptr<TheScience> pointer(new SubjectScience(name_science));
		scienceList_vector.push_back(pointer); // TODO: replace to moving 
	}
}
