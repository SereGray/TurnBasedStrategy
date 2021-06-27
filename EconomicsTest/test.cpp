#include "pch.h"
#include "../TurnBasedStrategy/economics.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

namespace KingdoomEconomicsTest {
	class KingdoomEconomicsFixation : public ::testing::Test {
	protected:
		void SetUp() override {
			master = new EconomicsGameObj;
			kd = new KingdoomEconomics(*master, 0);
		}
		void TearDown() override {
			delete kd;
			delete master;
		}

		EconomicsGameObj* master;
		KingdoomEconomics* kd;
	};

	TEST_F(KingdoomEconomicsFixation, CreatingTest) {
		EXPECT_EQ(kd->MyId(), 0);
	}
	
	// Demography testing
	TEST_F(KingdoomEconomicsFixation, DemographyIncreaseFermersPeople){
		kd->nation_.increase_people_ = 10;
		kd->nation_.IncreaseFermersPeople();
		EXPECT_EQ(kd->nation_.all_people_, 10)<<"first increasing";
		EXPECT_EQ(kd->nation_.fermers_people_, 10)<<"first increasing";
		kd->nation_.IncreaseFermersPeople();
		EXPECT_EQ(kd->nation_.all_people_, 20)<<"second increasing";
		EXPECT_EQ(kd->nation_.fermers_people_, 20) << "second increasing";
		kd->nation_.increase_people_ = -10;
		kd->nation_.IncreaseFermersPeople();
		EXPECT_EQ(kd->nation_.all_people_, 10)<<"after negative increasing";
		EXPECT_EQ(kd->nation_.fermers_people_, 10) <<"after negative increasing";
	}	

	TEST_F(KingdoomEconomicsFixation, DemographyDecreaseFermersPeople){
		kd->nation_.all_people_ = 10;
		kd->nation_.fermers_people_ = 10;
		EXPECT_EQ(kd->nation_.fermers_people_, 10)<<"after start";
		kd->nation_.DecreaseFermersPeople(1);
		EXPECT_EQ(kd->nation_.fermers_people_,9)<<"after decrease";
		kd->nation_.DecreaseFermersPeople(10);
		EXPECT_EQ(kd->nation_.fermers_people_,0)<<"after negative value test";
	}

	// KingdoomEconomics testing
	TEST_F(KingdoomEconomicsFixation, SellResourseTest){
		// by default kd gold 10`000 kd food 10`000`000
		kd->SellResourse(kd->food_,10000);
		EXPECT_EQ(kd->gold_.count_,10100);
	}

	TEST_F(KingdoomEconomicsFixation, SellResourse_BigOvercount){
		EXPECT_FALSE(kd->SellResourse(kd->food_,100000000));	
		kd->food_.count_ = 0;
		EXPECT_FALSE(kd->SellResourse(kd->food_,100000000));	
		kd->food_.count_= -1;
		EXPECT_FALSE(kd->SellResourse(kd->food_,100000000));	

	}

	TEST_F(KingdoomEconomicsFixation, BuyResourse_BigOvercount){
		EXPECT_FALSE(kd->BuyResourse(kd->food_,100000000));	
		kd->gold_.count_ = 0;
		EXPECT_FALSE(kd->BuyResourse(kd->food_,100000000));
		kd->gold_.count_ = -1;
		EXPECT_FALSE(kd->BuyResourse(kd->food_,100000000));
	}

	TEST_F(KingdoomEconomicsFixation, SellResourse_Overcount){
		EXPECT_FALSE(kd->SellResourse(kd->food_,10000001));	
	}

	TEST_F(KingdoomEconomicsFixation, BuyResourse_Overcount){
		EXPECT_FALSE(kd->BuyResourse(kd->food_,1000001));	
	}
	
}

namespace KingdoomEconomicsFakeNameSpace{
		
	class KingdoomEconomicsFakeFixation : public ::testing::Test {
	protected:
		void SetUp() override {
			master = new EconomicsGameObj();
			kd = new KingdoomEconomics(*master, 0);
			map = new MapGameObj(5, 5, 1); // 3 x 3  kingdoom
			science = new ScienceGameObj();
			science->AddKingdoom(0);
			master->SetInterface({ map, science });
		}
		void TearDown() override {
			delete kd;
			delete master;
			delete science;
			delete map;
		}

		ScienceGameObj* science;
		MapGameObj* map;
		EconomicsGameObj* master;
		KingdoomEconomics* kd;

	};

	TEST_F(KingdoomEconomicsFakeFixation, EmptyTest) {
		EXPECT_TRUE(true);
	}

	TEST_F(KingdoomEconomicsFakeFixation, CreatingTest){
		EXPECT_EQ(kd->MyId(),0);
	}

	TEST_F(KingdoomEconomicsFakeFixation, FakeAreaFakeDensityLvlTest){
		EXPECT_EQ(kd->MyArea(), 9);
		EXPECT_EQ(kd->GetDensityLvl(), 0);
	}
	
	// Demography testing
	
	/*TEST_F(KingdoomEconomicsFakeFixation, DemographyNextTurnIncreasingPeople){
		kd->area_ = 100;
		kd->density_ = 1;
		kd->nation_.all_people_ = 100;
		kd->nation_.NextTurn();
		EXPECT_EQ(kd->nation_.all_people_, 101);
		kd->nation_.all_people_ = 100;
		kd->area_ = 200;
		kd->nation_.NextTurn();
		EXPECT_EQ(kd->nation_.all_people_, 105);
	}	
	*/

}
