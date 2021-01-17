#ifndef ECONOMICS
#define ECONOMICS
#include"tbs_interface.h"
#include"engine.h"
// модель экономики: (+демографии)
// посев доступного зерна (из остатков или покупного)
// на доступной территории
// доступным количеством кресть€н
// продажа выращенного зерна
// покупка ученых солдат генералов ...
// 
// демографи€:
//прирост кресть€н
//доступный максимум
class Demography {
public:
	uint64_t all_people; // общее количество людей TODO: расчитыватс€ ??
	uint32_t increase_people;  
	uint64_t maximum_people; 
	uint64_t fermers_people;// общее количество людей зан€тых в экономике
	
private:
	void TncreaseFermersPeople(); // функци€ прироста населени€
	void DecreaseFermersPeople(); // функци€ 
};

class Economics : public TbsInterface, public EngineGameObjInterface {
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
	//( чем больше ученых тем дороже их содержать (логарифмическа€ зависимость?)) по основанию ~3
	uint32_t CalculationSpecialistHiring(); // стоимость найма зависит от количества уже работающих
};
#endif
