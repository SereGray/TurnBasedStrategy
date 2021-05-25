#include "pch.h"
#include "../TurnBasedStrategy/war.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

namespace GeneralNameSpace {

	TEST(GeneralClassTest, GeneralConstructor_addGeneral) {
		WarGameObj d;
		Kingdoom_defense kd(0, d);
		kd.AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(kd.v_general_.size(), 1);
	}

	class FixationKingdoom_defense : public ::testing::Test {
	protected:
		void SetUp() override {
			WarGameObj* d = new WarGameObj;
			kd = new Kingdoom_defense(0, *d);
		}
		void TearDown() override {
			delete kd;
			delete d;
		}
		WarGameObj* d = nullptr;
		Kingdoom_defense* kd = nullptr;

	};

	// Сделать 2 функции ( <- эта показывает всех солдат, включая тех что у генералов) и 2ая поазывающая свободных
	TEST_F(FixationKingdoom_defense, AddGeneralAndGetGeneralByGetGeneral) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		General& gen = kd->GetGeneral(id);
		EXPECT_EQ(gen.GetMaster(), kd);
	}

	TEST_F(FixationKingdoom_defense, AddGeneralAndGetGeneralByDirectAcces) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		General& gen = kd->v_general_[kd->GetIndexOfGeneral(id)];
		EXPECT_EQ(gen.GetMaster(), kd);
	}
	TEST_F(FixationKingdoom_defense, AddGeneralAndDie) {
		EXPECT_EQ(kd->v_general_.size(), 0);
		kd->AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(kd->v_general_.size(), 1);
		kd->v_general_[0].Dead();
		EXPECT_EQ(kd->v_general_.size(), 0);
	}
	
	TEST_F(FixationKingdoom_defense, GenMyIdEqualsKingdoomGeneraIndex) {
		General::SetNullId();
		EXPECT_EQ(kd->v_general_.size(), 0);
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(id, 0);
		EXPECT_EQ(kd->v_general_.size(), 1) << " size != 1";
		EXPECT_EQ(kd->GetIndexOfGeneral(id), 0) << " index of General !=0";
		EXPECT_TRUE(kd->v_general_[kd->GetIndexOfGeneral(id)].GetMyId() == id);
		id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_TRUE(kd->v_general_[kd->GetIndexOfGeneral(id)].GetMyId() == id);
	}
	TEST_F(FixationKingdoom_defense, MyIdEqualsKingdoom_v_generalIndexAfterDeadOne) {
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
	TEST_F(FixationKingdoom_defense, TwiceAddGeneralAndTwiceDie) {
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
	//TODO: add solders with no solders in Kingdoom
	TEST_F(FixationKingdoom_defense, AddSoldersDecreaseSolders) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		kd->AddSolder(100);
		EXPECT_EQ(kd->GetCountFreeSpecialists(), 100); // TODO:Сделать 2 функции ( <- эта показывает всех солдат, включая тех что у генералов) и 2ая поазывающая свободных
		General& gen = kd->GetGeneral(id);
		EXPECT_EQ(gen.count_solders_, 0);
		gen.AttackTo(100, 0); // attack self ?
		EXPECT_EQ(gen.count_solders_, 100);
		EXPECT_EQ(kd->GetCountFreeSpecialists(), 0);
		gen.Rest();
		EXPECT_EQ(gen.count_solders_, 0);
		EXPECT_EQ(kd->GetCountFreeSpecialists(), 100);
	}

	TEST_F(FixationKingdoom_defense, GeneralActionChanging_AtackToWorkout) {
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

	TEST_F(FixationKingdoom_defense, GeneralActionChanging_DefenseToRest) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		kd->AddSolder(100);
		General& gen = kd->GetGeneral(id);
		gen.Defense(90);
		EXPECT_EQ(gen.count_solders_, 90);
		EXPECT_EQ(kd->GetCountFreeSpecialists(), 10);
		EXPECT_EQ(gen.action_, 3);
		gen.Rest();
		EXPECT_EQ(gen.count_solders_, 0);
		EXPECT_EQ(kd->GetCountFreeSpecialists(), 100);
		EXPECT_EQ(gen.action_, 0);
	}

	TEST_F(FixationKingdoom_defense, GeneralNextTurn_Rest) {
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


	TEST_F(FixationKingdoom_defense, GeneralNextTurn_Study) {
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
	TEST_F(FixationKingdoom_defense, GeneralNextTurn_Workout) {
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

	TEST_F(FixationKingdoom_defense, GeneralNextTurn_Defense) {
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



	TEST_F(FixationKingdoom_defense, KingdoomLandaun ) {
		EXPECT_EQ(kd->landaun_.GetMyId(), MAXUINT);
		EXPECT_EQ(kd->landaun_.skill_, 0);
		EXPECT_EQ(kd->landaun_.intelegence_, 0);
		EXPECT_EQ(kd->landaun_.spirit_, 0);
		EXPECT_EQ(kd->landaun_.speed_, 0);
		EXPECT_EQ(kd->landaun_.age_, 0);
		EXPECT_EQ(kd->landaun_.name_,"landaun");
	}

	TEST_F(FixationKingdoom_defense, KingdoomDeleteGeneral) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(kd->v_general_.size(), 1);
		kd->DeleteGeneral(id);
		EXPECT_EQ(kd->v_general_.size(), 0);
	}

	TEST_F(FixationKingdoom_defense, KingdoomGetGeneral) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(kd->v_general_.size(), 1);
		General gen = kd->GetGeneral(id);
		EXPECT_EQ(gen.GetMyId(), id);
	}

	TEST_F(FixationKingdoom_defense, KingdoomGetIndexOfGeneral) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(kd->v_general_.size(), 1);
		unsigned index = kd->GetIndexOfGeneral(id);
		EXPECT_EQ(kd->v_general_[index].GetMyId(),id);
	}

	TEST_F(FixationKingdoom_defense, KingdoomGetSpeedestGeneral_RETURNLandaun) {
		EXPECT_EQ(kd->v_general_.size(), 0);
		General gen = kd->GetSpeedestGeneral(1); // - 1 random
		EXPECT_EQ(gen.GetMyId(), MAXUINT);
	}

	TEST_F(FixationKingdoom_defense, KingdoomGetSpeedestGeneral_RETURNSpeedest) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		unsigned id2 = kd->AddGeneral("speedlandaun", 10, 10, 20, 10);
		kd->AddSolder(20);
		kd->GetGeneral(id).AttackTo(10, 1);   // 10 solders
		kd->GetGeneral(id2).AttackTo(10, 1);
		EXPECT_EQ(kd->GetCountFreeSpecialists(), 0);
		EXPECT_EQ(kd->v_general_.size(), 2);
		General& gen = kd->GetSpeedestGeneral(1);
		EXPECT_EQ(gen.GetMyId(),id2);
		gen.Rest();
		EXPECT_EQ(gen.count_solders_, 0);
		gen = kd->GetSpeedestGeneral(1);
		EXPECT_EQ(gen.GetMyId(), id);
	}

	/*TEST_F(FixationKingdoom_defense, KingdoomGetSolderForce) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		EXPECT_EQ(kd->v_general_.size(), 1);
		kd->DeleteGeneral(id);
		EXPECT_EQ(kd->v_general_.size(), 0);
	}*/


}

	class FixationGeneralPrivate : public ::testing::Test {
	protected:
		void SetUp() override {
			WarGameObj* d = new WarGameObj;
			kd = new Kingdoom_defense(0, *d);
		}
		void TearDown() override {
			delete kd;
			delete d;
		}
		WarGameObj* d = nullptr;
		Kingdoom_defense* kd = nullptr;

	};

	TEST_F(FixationGeneralPrivate, GeneralSkillFloat) {
		unsigned id = kd->AddGeneral("landaun", 10, 10, 10, 10);
		kd->AddSolder(100);
		General& gen = kd->GetGeneral(id);
		EXPECT_EQ(gen.skill_float_, 10.0);
	}

	/*namespace ThreeKingdoomFixationNamespace {
		class ThreeKingdoomFixation : public ::testing::Test {
		protected:
			void SetUp() override {
				WarGameObj* d = new WarGameObj;
				kd0 = new Kingdoom_defense(0, *d);
				kd1 = new Kingdoom_defense(1, *d);
				kd2 = new Kingdoom_defense(2, *d);
			}
			void TearDown() override {
				delete kd0;
				delete kd1;
				delete kd2;
				delete d;
			}
			WarGameObj* d = nullptr;
			Kingdoom_defense* kd0 = nullptr;
			Kingdoom_defense* kd1 = nullptr;
			Kingdoom_defense* kd2 = nullptr;

		};

		TEST_F(ThreeKingdoomFixation, GetLocalWars) {
			unsigned id0 = kd0->AddGeneral("daun0", 0, 0, 5, 0);
			kd0->AddSolder(100);
			unsigned id1 = kd1->AddGeneral("daun1", 0, 0, 5, 0);
			kd1->AddSolder(100);
			unsigned id2 = kd2->AddGeneral("daun2", 0, 0, 5, 0);
			kd2->AddSolder(100);
			kd0->SetAttack(kd0->GetGeneral(id0), 50, 1);
			kd1->SetAttack(kd1->GetGeneral(id1), 50, 0);
			kd2->SetAttack(kd2->GetGeneral(id2), 50, 1);
		}
	}*/