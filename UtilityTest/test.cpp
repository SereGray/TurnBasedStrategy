#include "pch.h"
#include "../TurnBasedStrategy/utility.h"


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

class TestObj {
	unsigned my_id_;
public:
	TestObj(unsigned id) :my_id_(id) {};
	unsigned GetMyId() { return my_id_; };
};

TEST(utilityTestCase, OneObjVector) {
	std::vector<TestObj> test_vector({ TestObj(0), });
	TestObj test_obj = GetObjFromVectorUt(0, test_vector);
	EXPECT_EQ(test_obj.GetMyId(), 0);
	test_vector.push_back(TestObj(1));
	test_obj = GetObjFromVectorUt(1, test_vector);
	EXPECT_EQ(test_obj.GetMyId(), 1);
}