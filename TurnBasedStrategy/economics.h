#ifndef ECONOMICS
#define ECONOMICS
#include"TbsInterface.h"
#include"Engine.h"
//
// модель экономики: (+демографии)
// посев доступного зерна (из остатков или покупного)
// на доступной территории
// доступным количеством крестьян
// продажа выращенного зерна
// покупка ученых солдат генералов ...
// 
// демография:
//прирост крестьян
//доступный максимум
class Demography {
public:
	uint64_t all_people; // общее количество людей TODO: расчитыватся ??
	uint32_t increase_people;  
	uint64_t maximum_people; 
	uint64_t fermers_people;// общее количество людей занятых в экономике
	
private:
	void increaseFermersPeople(); // функция прироста населения
	void decreaseFermersPeople(); // функция 
};

class Economics : public TbsInterface, public EngineInterface {
public:
	uint64_t gold; // накапливаемый ресурс
	uint64_t profit_gold; // прибыль на следующий ход ??
	uint64_t consumption_gold; // расход
	uint64_t resourse;  // ненакапливаемый ресурс -- в данном случае еда (зерно)
	uint64_t increase_resourse;
	uint64_t consumption_resourse; //  выработка и потребление ресурса 
	void SellResourse();
	void BuyResourse();
	void BuyThing();
private:
	void NextTurn(); //  вычет расходов из бюджета
	uint64_t CalculationConsumption(); // здесь расчет расходов на содержание    
	uint64_t CalculationSpecialistSalary(); // расчет стоимости специалиста 
	//( чем больше ученых тем дороже их содержать (логарифмическая зависимость?))
	uint32_t CalculationSpecialistHiring(); // стоимость найма зависит от количества уже работающих
};
#endif
