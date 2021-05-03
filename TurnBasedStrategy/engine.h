// Вызов методов к.и. чер ез вирт функц
// Создает игру - запускает к.и. и
// Определяет какой из игроков ходит

//TODO: сортировку в порядке значимости при расчете хода ( например сначала война-армия, потом
//	территория, потом население, потом посев-экономика, потом наука
//TODO: взаимодействие игр. объектов
//	получение параметров
//	типовые: карта-изменение границ в рез боя
//		армия-изменение боеспособности в рез повышения уровня науки
//		изменние количества солдат(едениц) в рез хоз деятельности(экономика)
//		изм кол-ва ученых ...
//		экономика-выращено зерна в рез засеивания территории
#ifndef ENGINE
#define ENGINE

#include<vector>
#include"tbs_interface.h"
#include<string>
#include"science.h"
#include"war.h"
#include"map.h"
#include"economics.h"
// список игоровых объектов

// метод NextTurn : обход игровых объектов по списку и вызов метода NextTurnObj
// вызов игровых объектов как потомков EngineInterface и вызов их метода NextTurn

// метод GameLoop : бесконечного игрового цикла


// класс взаимодействия игровых объектов движка между собой
class EngineGameObjInterface {
	virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in);  // получаю игровые объекты исп RTTI
	virtual void NextTurn();
	virtual void SaveState();
	virtual void LoadState();
	virtual void CreateState(unsigned num_players, unsigned map_size);
	virtual std::string GetSummariesString(); // сводки за предыдущий ход
	public:
	virtual ~EngineGameObjInterface();
};

EngineGameObjInterface::~EngineGameObjInterface(){}; 

class Engine: public TbsInterface{
public:
	ScienceGameObj science_game_obj_;
	void NextTurn(); // запускает цепочку расчетов следующего 
#endif
};

