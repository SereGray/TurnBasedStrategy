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

	class FixationGeneral: public ::testing::Test {
		
		void SetUp() override {
			Defense* d = new Defense;
			kd = new Kingdoom_defense(0, *d);
		}
		void TearDown() override {
			delete kd;
			delete d;
		}

	protected:
		Defense* d = nullptr;
		Kingdoom_defense* kd = nullptr;

	};

	TEST_F(FixationGeneral, Fixation_addGeneral_and_Die) {
		EXPECT_EQ(kd->v_general_.size(), 0);
		kd->AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(kd->v_general_.size(), 1);
		kd->v_general_[0].Dead();
		EXPECT_EQ(kd->v_general_.size(), 0);
	}
}