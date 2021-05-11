#include"fake_game_obj.h"

fake_game_obj::fake_game_obj(){
	++counter;
}

void fake_game_obj::SetInterface(std::vector<EngineGameObjInterface*> list_in){
	another = list_in[0];
}
