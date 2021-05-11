#include "pch.h"
#include "fake_game_obj.h"
#include <vector>

TEST(EngineTests, ExampleTest) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST(EnginePolimorphTests, SetInterfaceTest){
	fake_game_obj f1;
	fake_game_obj f2;
	std::vector<EngineGameObjInterface*> vEGameObjs;
	vEGameObjs.push_back(f1);
	vEGameObjs.push_back(f2);
	f2.SetInterface(vEGameObjs);

}
