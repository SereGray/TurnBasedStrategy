#include"../TurnBasedStrategy/engine.h"

#ifndef FAKE_GAME_OBJ
#define FAKE_GAME_OBJ

class fake_game_obj: public EngineGameObjInterface{
	EngineGameObjInterface* another;
	static unsigned counter;
	public:
	fake_game_obj(){++counter;};
	virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in); 
};
unsigned fake_game_obj::counter = 0;

#endif
