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
	uint32_t increase_people_;  
	uint64_t maximum_people_; 
	uint64_t fermers_people_;// общее количество людей занятых в экономике
	Demography(KingdoomEconomics* master);
	void NextTurn();
private:
	Demography()=default;
	KingdoomEconomics* my_master_ = nullptr;
	void IncreaseFermersPeople(); // функция прироста населения(новые люди автоматически фермеры)
	void DecreaseFermersPeople(unsigned decrease_count); // функция убыли фермеров (наняли в качестве спец)
};

// Gold class
class Gold : public Resource {
public:
	Gold(int);
};

// Eat class
class Food : public Resource {
public:
	Food(int);
};

//
class BaseCost {
public:
	virtual ~BaseCost();
	virtual Resource& Buy();
};

template<typename TypeResource>
class UnitCost : public BaseCost {
public:
	TypeResource buy_, consumption_, sell_; //in 0.01
public:
	UnitCost(int buy, int consumption, int sell);
	Resource& Buy() override;
	Resource& Consumption(); 
	Resource& Sell();
};

class Specialist {
public:
	UnitCost<Gold> gold;
	UnitCost<Food> food;
	BaseCost& gold_;
	BaseCost& food_;
	Specialist();
	template<typename Visitor>
	void Accept(Visitor f, unsigned count = 1) {
		f(gold_, count);
		f(food_, count);
	};
};

// 
class KingdoomEconomics {
public:
	KingdoomEconomics(EconomicsGameObj& master, unsigned my_id);
	Gold gold_;
	Food food_;
	Demography nation_; // 
	//uint64_t gold_; // накапливаемый ресурс
	uint64_t profit_gold_; // прибыль на следующий ход ??
	uint64_t consumption_gold_; // расход
	uint64_t resourse;  // ненакапливаемый ресурс -- в данном случае еда (зерно)
	uint64_t increase_resourse_;
	uint64_t consumption_resourse_; //  выработка и потребление ресурса 

	void SellResourse();
	void BuyResourse();
	void CostToCropsResourse();
	void BuyThing();  // solder, scienist, General ...
	unsigned GetDensityLvl();
	void BuySpecialist(unsigned);
	unsigned MyArea();
private:
	struct Visiter {
		KingdoomEconomics& e_;
		void (*ptrFunct_)(KingdoomEconomics&, BaseCost&, int);
		Visiter(KingdoomEconomics& e, void (*ptrFunct)(KingdoomEconomics&, BaseCost&, int)) :e_(e), ptrFunct_(ptrFunct) {};
		void operator()(BaseCost& cost, int count) {
			ptrFunct_(e_, cost, count);
		}
	};
	Specialist pikiner_; //test
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
	static void VisitorBuySpecialist(KingdoomEconomics& eco, BaseCost& cost, int count);
};

class EconomicsGameObj : public EngineGameObjInterface{
	std::vector<KingdoomEconomics> v_economics_;
	ScienceGameObj* science_obj_ = nullptr;
	MapGameObj* map_obj_ = nullptr;	
	virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in);
	void SaveState();
	void LoadState();
	void CreateState(unsigned num_players, unsigned map_size);
	void NextTurn();
	public:
	EconomicsGameObj();
	~EconomicsGameObj();
	KingdoomEconomics& GetKingdoomEconomics(unsigned by_id);
	unsigned MyArea(unsigned by_id);
	unsigned GetDensityLvl(unsigned by_id);

};	
#endif


