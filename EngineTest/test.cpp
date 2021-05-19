#include "pch.h"
#include <vector>
#include "../TurnBasedStrategy/engine.h"

// добавление объектных файлов для компановщика https://docs.microsoft.com/ru-ru/visualstudio/test/how-to-use-microsoft-test-framework-for-cpp?view=vs-2019#object_files

class fake_game_obj : public EngineGameObjInterface {
	EngineGameObjInterface* another;
	static unsigned counter;
	unsigned num_;
public:
	fake_game_obj();
	virtual void SetInterface(std::vector<EngineGameObjInterface*> list_in);
	bool IsTakeAnother();
	unsigned GetNum();
};

unsigned fake_game_obj::counter = 0;

fake_game_obj::fake_game_obj() :another(this), num_(counter) {
	++counter;
}

void fake_game_obj::SetInterface(std::vector<EngineGameObjInterface*> list_in) {
	another = list_in[0];
}

bool fake_game_obj::IsTakeAnother()
{
	if (dynamic_cast<fake_game_obj*>(another)->GetNum() != num_) return true;
	return false;
}

unsigned fake_game_obj::GetNum()
{
	return num_;
}


TEST(EngineTests, ExampleTest) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST(EnginePolimorphTests, SetInterfaceTest){
	fake_game_obj f1;
	fake_game_obj f2;
	std::vector<EngineGameObjInterface*> vEGameObjs;
	vEGameObjs.push_back(&f1);
	vEGameObjs.push_back(&f2);
	f2.SetInterface(vEGameObjs);
	EXPECT_TRUE(f2.IsTakeAnother());
}
