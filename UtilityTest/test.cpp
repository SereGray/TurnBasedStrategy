#include "pch.h"
#include "../TurnBasedStrategy/utility.h"


TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

struct TestObj {
	unsigned my_id_;
	unsigned var_;
	TestObj(unsigned id) :my_id_(id), var_(0) {};
	unsigned GetMyId() { return my_id_; };
};


template<typename T>
T* GetObjectTest(unsigned by_id, std::vector<T> &vect)
{
	return GetObjFromVectorUt(by_id, vect);
}
TEST(utilityTestCase, OneObjVector) {
	std::vector<TestObj> test_vector({ TestObj(0), });
	TestObj* test_obj = GetObjectTest(0, test_vector);
	EXPECT_EQ(test_obj->GetMyId(), 0);
	EXPECT_EQ(test_obj->var_, 0);
	test_obj->var_ = 1;
	test_obj = GetObjectTest(0, test_vector);
	EXPECT_EQ(test_obj->GetMyId(), 0);
	EXPECT_EQ(test_obj->var_, 1);
	test_vector.push_back(TestObj(1));
	test_obj = GetObjectTest(1, test_vector);
	EXPECT_EQ(test_obj->GetMyId(), 1);
	TestObj* test_obj2 = GetObjectTest(0, test_vector);
	test_obj2->my_id_ = 10;
	EXPECT_EQ(test_obj2->my_id_, 10);
	EXPECT_EQ(test_obj2->var_, 1);
	test_obj2 = GetObjectTest(10, test_vector);
	EXPECT_EQ(test_obj2->GetMyId(), 10);
	EXPECT_EQ(test_obj2->my_id_, 10);
	EXPECT_EQ(test_obj2->var_, 1);
	EXPECT_THROW(GetObjectTest(0,test_vector)->GetMyId(), VectorUtException);
}

