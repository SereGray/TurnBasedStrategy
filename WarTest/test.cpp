#include "pch.h"
#include "../TurnBasedStrategy/war.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

namespace DefenseTestNameSpace {

	TEST(GeneralClassTest, GeneralConstructor_addGeneral) {
		Defense d;
		Kingdoom_defense kd(0,d);
		kd.AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(kd.v_general_.size(), 1);
	}

	
}

namespace GeneralTestNameSpace {
	class Fake_Kingdoom_defense {
	public:
		Fake_Kingdoom_defense()=default;
	};
	// have a static member 
	class GeneralFixation : public ::testing::Test {
		Fake_Kingdoom_defense kd;
	};
}