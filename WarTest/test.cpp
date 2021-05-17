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
	protected:
		void SetUp() override {
			Defense* d = new Defense;
			kd = new Kingdoom_defense(0, *d);
		}
		void TearDown() override {
			delete kd;
			delete d;
		}
		Defense* d = nullptr;
		Kingdoom_defense* kd = nullptr;

	};

	// Сделать 2 функции ( <- эта показывает всех солдат, включая тех что у генералов) и 2ая поазывающая свободных
	TEST_F(FixationGeneral, AddGeneralAndGetGeneralByGetGeneral) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		General& gen = kd->GetGeneral(id);
		EXPECT_EQ(gen.GetMaster(), kd);
	}

	TEST_F(FixationGeneral, AddGeneralAndGetGeneralByDirectAcces) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		General& gen = kd->v_general_[kd->GetIndexOfGeneral(id)];
		EXPECT_EQ(gen.GetMaster(), kd);
	}
	TEST_F(FixationGeneral, AddGeneralAndDie) {
		EXPECT_EQ(kd->v_general_.size(), 0);
		kd->AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(kd->v_general_.size(), 1);
		kd->v_general_[0].Dead();
		EXPECT_EQ(kd->v_general_.size(), 0);
	}

	TEST_F(FixationGeneral, GenMyIdEqualsKingdoomGeneraIndex) {
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
	TEST_F(FixationGeneral, MyIdEqualsKingdoom_v_generalIndexAfterDeadOne) {
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
	TEST_F(FixationGeneral, TwiceAddGeneralAndTwiceDie) {
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

	//TODO : Генерал может атаковать самого себя
	TEST_F(FixationGeneral, AddSoldersDecreaseSolders) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		kd->AddSolder(100);
		EXPECT_EQ(kd->GetCountSpecialists(),100); // TODO:Сделать 2 функции ( <- эта показывает всех солдат, включая тех что у генералов) и 2ая поазывающая свободных
		General& gen = kd->GetGeneral(id);
		EXPECT_EQ(gen.count_solders_, 0);
		gen.AttackTo(100, 0); // attack self ?
		EXPECT_EQ(gen.count_solders_, 100);
		EXPECT_EQ(kd->GetCountSpecialists(), 0);
		gen.Rest();
		EXPECT_EQ(gen.count_solders_, 0);
		EXPECT_EQ(kd->GetCountSpecialists(), 100);
	}

	TEST_F(FixationGeneral, GeneralActionChanging_AtackToWorkout) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		kd->AddSolder(100);
		General& gen = kd->GetGeneral(id);
		EXPECT_EQ(gen.count_solders_, 0);
		gen.AttackTo(100, 0); // attack to itself?
		EXPECT_EQ(gen.count_solders_, 100);
		EXPECT_EQ(gen.action_, 4);
		gen.Workout();
		EXPECT_EQ(gen.count_solders_, 0);
		EXPECT_EQ(gen.action_, 2);
	}

	TEST_F(FixationGeneral, GeneralActionChanging_DefenseToRest) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		kd->AddSolder(100);
		General& gen = kd->GetGeneral(id);
		gen.Defense(90);
		EXPECT_EQ(gen.count_solders_, 90);
		EXPECT_EQ(kd->GetCountSpecialists(), 10);
		EXPECT_EQ(gen.action_, 3);
		gen.Rest();
		EXPECT_EQ(gen.count_solders_, 0);
		EXPECT_EQ(kd->GetCountSpecialists(), 100);
		EXPECT_EQ(gen.action_, 0);
	}

	TEST_F(FixationGeneral, GeneralNextTurn_Rest) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		kd->AddSolder(100);
		General& gen = kd->GetGeneral(id);
		gen.spirit_ = 10;
		EXPECT_EQ(gen.spirit_, 10);
		EXPECT_EQ(gen.age_, 10);
		EXPECT_EQ(gen.intelegence_, 10);
		EXPECT_EQ(gen.skill_, 10);
		EXPECT_EQ(gen.speed_, 10);
		EXPECT_EQ(gen.action_, 0);
		gen.NextTurn();
		EXPECT_GT(gen.spirit_, 10);
		EXPECT_EQ(gen.spirit_, 15);
		EXPECT_EQ(gen.age_, 11);
		EXPECT_EQ(gen.intelegence_, 10);
		EXPECT_EQ(gen.skill_, 10);
		EXPECT_EQ(gen.speed_, 10);
		EXPECT_EQ(gen.action_, 0);
	}


	TEST_F(FixationGeneral, GeneralNextTurn_Study) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		kd->AddSolder(100);
		General& gen = kd->GetGeneral(id);
		gen.spirit_ = 70;
		gen.Study();
		EXPECT_EQ(gen.spirit_, 70);
		EXPECT_EQ(gen.age_, 10);
		EXPECT_EQ(gen.intelegence_, 10);
		EXPECT_EQ(gen.skill_, 10);
		EXPECT_EQ(gen.speed_, 10);
		EXPECT_EQ(gen.action_, 1);
		gen.NextTurn();
		EXPECT_EQ(gen.spirit_, 68);
		EXPECT_EQ(gen.age_, 11);
		EXPECT_EQ(gen.intelegence_, 11);
		EXPECT_EQ(gen.skill_, 10);
		EXPECT_EQ(gen.speed_, 10);
		EXPECT_EQ(gen.action_, 1);
	}
	TEST_F(FixationGeneral, GeneralNextTurn_Workout) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		kd->AddSolder(100);
		General& gen = kd->GetGeneral(id);
		gen.spirit_ = 70;
		gen.Workout();
		EXPECT_EQ(gen.spirit_, 70);
		EXPECT_EQ(gen.age_, 10);
		EXPECT_EQ(gen.intelegence_, 10);
		EXPECT_EQ(gen.skill_, 10);
		EXPECT_EQ(gen.speed_, 10);
		EXPECT_EQ(gen.action_, 2);
		gen.NextTurn();
		EXPECT_EQ(gen.spirit_, 68);
		EXPECT_EQ(gen.age_, 11);
		EXPECT_EQ(gen.intelegence_, 10);
		EXPECT_EQ(gen.skill_, static_cast<unsigned>(10.0 + ((gen.intelegence_ / 10) * (gen.spirit_ / 100))));
		EXPECT_EQ(gen.speed_, 10);
		EXPECT_EQ(gen.action_, 2);
	}

	TEST_F(FixationGeneral, GeneralNextTurn_Defense) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		kd->AddSolder(100);
		General& gen = kd->GetGeneral(id);
		gen.spirit_ = 70;
		gen.Defense(80);
		EXPECT_EQ(gen.spirit_, 70);
		EXPECT_EQ(gen.age_, 10);
		EXPECT_EQ(gen.intelegence_, 10);
		EXPECT_EQ(gen.skill_, 10);
		EXPECT_EQ(gen.speed_, 10);
		EXPECT_EQ(gen.action_, 3);
		gen.NextTurn();
		EXPECT_EQ(gen.spirit_, 66);
		EXPECT_EQ(gen.age_, 11);
		EXPECT_EQ(gen.intelegence_, 10);
		EXPECT_EQ(gen.skill_, 10);
		EXPECT_EQ(gen.speed_, 10);
		EXPECT_EQ(gen.action_, 3);
	}
}