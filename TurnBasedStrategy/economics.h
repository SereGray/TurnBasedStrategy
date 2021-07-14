/*
* Экономика хранит данные о количестве людей(населении) количестве фермеров в них, количестве зерна в кор-е, количестве золота,
* Реализует расход/доход зерна и золота
* Предоставляе т методы посева и сбора урожая, обмена на золото, покупку ученых, солдат (в обмен на фермеров и золото)
*/
#ifndef ECONOMICS
#define ECONOMICS
#include"tbs_interface.h"
#include"engine.h"
#include"science.h"
#include"map.h"
#include"resource.h"
#include"units.h"
#include<map>

// модель экономики: (+демографии)
// посев доступного зерна (из остатков или покупного)
// на доступной территории
// доступным количеством крестьян
// продажа выращенного зерна
// покупка ученых солдат генералов ...
// 
class KingdoomEconomics;
class EconomicsGameObj;
// демография:
//прирост крестьян
//доступный максимум
class Demography {
public:
	uint64_t all_people_; // общее количество людей TODO: расчитыватся ??
	int32_t increase_people_;  
	uint64_t maximum_people_; 
	uint64_t fermers_people_;// общее количество людей занятых в экономике
	Demography();
	void NextTurn(unsigned area, unsigned increasing_lvl, unsigned densety_lvl);
private:


public:
	void IncreaseFermersPeople(); // функция прироста населения(новые люди автоматически фермеры)
	void DecreaseFermersPeople(unsigned decrease_count); // функция убыли фермеров (наняли в качестве спец)
};



class KingdoomEconomics {
public:
	KingdoomEconomics(EconomicsGameObj& master, unsigned my_id);
	Gold gold_; // накапливаемый ресурс
	Food food_;
	Demography nation_; // 
	int profit_gold_; // прибыль на следующий ход ??
	int consumption_gold_; // расход
	int increase_resourse_;
	int consumption_resourse_; //  выработка и потребление ресурса 

	bool SellResourse(Resource&,int);
	bool BuyResourse(Resource&,int);
	unsigned GetDensityLvl();
	unsigned GetIncreasingLvl();
	void ChangeCountSpecialists(Unit&, unsigned);
	unsigned MyArea();
	unsigned GetMyId();
private: 

	struct Visiter {
		KingdoomEconomics& e_;
		bool (*ptrFunct_)(KingdoomEconomics&, BaseCost&, int);
		Visiter(KingdoomEconomics& e, bool (*ptrFunct)(KingdoomEconomics&, BaseCost&, int)) :e_(e), ptrFunct_(ptrFunct) {};
		bool operator()(BaseCost& cost, int count) {
			return ptrFunct_(e_, cost, count);
		}
	};

	Visiter visiter_;
	unsigned my_id_;
	EconomicsGameObj& my_master_;
	void NextTurn(); //  вычет расходов из бюджета
	std::string GetSummariesString();
	void ResourseConsumption();   // 1 man eat 1 resourse (corn)
	uint64_t CalculationConsumption(); // здесь расчет расходов золота на содержание    
	uint64_t CalculationSpecialistSalary(); // расчет стоимости специалиста 
	//( чем больше ученых тем дороже их содержать (логарифмическая зависимость?)) по основанию ~3
	uint32_t CalculationSpecialistHiring(); // стоимость найма зависит от количества уже работающих
	static bool VisitorChangeCountSpecialists(KingdoomEconomics& eco, BaseCost& cost, int count);
};

class EconomicsGameObj : public EngineGameObjInterface{
	std::vector<KingdoomEconomics> v_economics_;
	ScienceGameObj* science_obj_ = nullptr;
	MapGameObj* map_obj_ = nullptr;	
	void SaveState();
	void LoadState();
	void CreateState(unsigned num_players, unsigned map_size);
	void NextTurn();
public:
	virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in);
	EconomicsGameObj();
	~EconomicsGameObj();
	KingdoomEconomics* GetKingdoomEconomics(unsigned by_id);
	void AddKingdomEconomics(unsigned by_id);
	unsigned MyArea(unsigned by_id);
	unsigned GetDensityLvl(unsigned by_id);
	unsigned GetIncreasingLvl(unsigned by_id);

};

#endif


