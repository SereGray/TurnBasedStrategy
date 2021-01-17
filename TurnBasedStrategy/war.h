#ifndef WAR 
#define WAR
#include<string>
#include"engine.h"
#include<vector>

// правила войны
// расчет сражений
class General
{
unsigned skill_;  // max 100
unsigned intelegence; // max 100
unsigned spirit_; // max 100
unsigned age_;   // max 100
unsigned action_;  // 0 - rest, 1 - study,2- workout, 3- defense, 4 ... attack to kingdom
unsigned target_;  // number kingdom to attack
unsigned count_solders_;
std::string name_;
void Workout();
void Study();
void Defense(unsigned count_defenders);

};

class Defense: public EngineGameObjInterface 
{
	std::vector<General> vGeneral_list;
	General landaun_; // default bad general 
	unsigned solders_;
	float solder_force_;	
void NextTurn();
unsigned GetCountSpecialists();
float GetSolderForce();
void AddGeneral();
};

#endif
