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

	TEST_F(FixationGeneral, addGeneral_and_Die) {
		EXPECT_EQ(kd->v_general_.size(), 0);
		kd->AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(kd->v_general_.size(), 1);
		kd->v_general_[0].Dead();
		EXPECT_EQ(kd->v_general_.size(), 0);
	}

	TEST_F(FixationGeneral, GenMyId_Equals_Kingdoom_v_genera_Index) {
		General::SetNullId();
		EXPECT_EQ(kd->v_general_.size(), 0);
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(id, 0);
		EXPECT_EQ(kd->v_general_.size(), 1)<<" size != 1";
		EXPECT_EQ(kd->GetIndexOfGeneral(id), 0) << " index of General !=0";
		EXPECT_TRUE(kd->v_general_[kd->GetIndexOfGeneral(id)].GetMyId() == id);
		id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_TRUE(kd->v_general_[kd->GetIndexOfGeneral(id)].GetMyId() == id);
	}
	TEST_F(FixationGeneral, MyId_Equals_Kingdoom_v_genera_Index_after_Dead_one) {
		General::SetNullId();
		EXPECT_EQ(kd->v_general_.size(), 0);
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		kd->v_general_[kd->GetIndexOfGeneral(id)].Dead();
		id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		unsigned dead_id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		kd->v_general_[kd->GetIndexOfGeneral(dead_id)].Dead();
		EXPECT_TRUE(kd->v_general_[kd->GetIndexOfGeneral(id)].GetMyId() == id);
	}
	TEST_F(FixationGeneral, Twice_addGeneral_and_Twice_Die_byId) {
		General::SetNullId();
		EXPECT_EQ(kd->v_general_.size(), 0);
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(kd->v_general_.size(), 1);
		kd->v_general_[kd->GetIndexOfGeneral(id)].Dead();
		EXPECT_EQ(kd->v_general_.size(), 0);
		id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(kd->v_general_.size(), 1);
		kd->v_general_[kd->GetIndexOfGeneral(id)].Dead();
		EXPECT_EQ(kd->v_general_.size(), 0);
	}
}