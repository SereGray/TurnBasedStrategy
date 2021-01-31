/*
* Экономика хранит данные о количестве людей(населении) количестве фермеров в них, количестве зерна в кор-е, количестве золота,
* Реализует расход/доход зерна и золота
* Предоставляе т методы посева и сбора урожая, обмена на золото, покупку ученых, солдат (в обмен на фермеров и золото)
*/
#ifndef ECONOMICS
#define ECONOMICS
#include"tbs_interface.h"
#include"engine.h"
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
	uint64_t all_people_; // общее количество людей TODO: расчитыватся ??
	uint32_t increase_people_;  
	uint64_t maximum_people_; 
	uint64_t fermers_people_;// общее количество людей занятых в экономике
	
private:
	void TncreaseFermersPeople(); // функция прироста населения(новые люди автоматически фермеры)
	void DecreaseFermersPeople(); // функция убыли фермеров (наняли в качестве спец)
};

class Economics : public TbsInterface, public EngineGameObjInterface {
public:
	Demography nation_; // 
	uint64_t gold_; // накапливаемый ресурс
	uint64_t profit_gold_; // прибыль на следующий ход ??
	uint64_t consumption_gold_; // расход
	uint64_t resourse;  // ненакапливаемый ресурс -- в данном случае еда (зерно)
	uint64_t increase_resourse_;
	uint64_t consumption_resourse_; //  выработка и потребление ресурса 
	void SellResourse();
	void BuyResourse();
	void CostToCropsResourse();
	void BuyThing();  // solder, scienist, General ...
private:
	void NextTurn(); //  вычет расходов из бюджета
	std::string GetSummariesString();
	void ResourseConsumption();   // 1 man eat 1 resourse (corn)
	uint64_t CalculationConsumption(); // здесь расчет расходов золота на содержание    
	uint64_t CalculationSpecialistSalary(); // расчет стоимости специалиста 
	//( чем больше ученых тем дороже их содержать (логарифмическая зависимость?)) по основанию ~3
	uint32_t CalculationSpecialistHiring(); // стоимость найма зависит от количества уже работающих
};
#endif
