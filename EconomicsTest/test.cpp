#include "pch.h"

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
}