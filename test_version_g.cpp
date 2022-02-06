#include "lib.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "myalocator.h"
#include "unlist.h"
#include <map>
#include <vector>
#include <iostream>



class TestUnList : public ::testing::Test
{
protected:
  TestUnList()
  {

  }
  ~TestUnList(){}
  void SetUp() override
  {
    for(std::size_t i = size_now; i < size_end; ++i)
      mylist.push_back(i);
  }
  void TearDown() override
  {
 
  }
  const std::size_t size_now = 0;
  const std::size_t size_end = 10;
  otus::unlist<int> mylist;
  
};

TEST(testVersionGoogle, testValidVersion) {

  EXPECT_GT(version(), 0);
}

TEST_F(TestUnList, testUnlistIterator)
{
  using ::testing::AllOf;
  using ::testing::Ge;
  using ::testing::Le;

  for(auto it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_THAT(*it, AllOf(Ge(size_now), Le(size_end)));
}

TEST_F(TestUnList, TestUnListSize)
{
  EXPECT_TRUE(size_end == mylist.size());
}