#include "pch.h"
#include "../TurnBasedStrategy/war.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

namespace GeneralNameSpace {

	TEST(GeneralClassTest, GeneralConstructor_addGeneral) {
		Defense d;
		Kingdoom_defense kd(0,d);
		kd.AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(kd.v_general_.size(), 1);
	}
}