#include "lib.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "myalocator.h"
#include "unlist.h"
#include <iostream>



class TestUnList : public ::testing::Test
{
protected:
 
  void SetUp() override
  {
    for(std::size_t i = size_now; i < size_end; ++i)
      mylist.push_back(i);
  }
  void TearDown() override
  {
    mylist.clear();
  }
  const std::size_t size_now = 0;
  const std::size_t size_end = 10;
  otus::unlist<int> mylist;
  
};

class TestUnListAllocator10Items : public ::testing::Test
{
protected:
  void SetUp() override
  {
    for(std::size_t i = size_now; i < size_end; ++i)
      mylist.push_back(i);
  }
  void TearDown() override
  {
    mylist.clear();
  }
  const std::size_t size_now = 0;
  const std::size_t size_end = 10;

  otus::unlist<int, otus::Myallocator<int, 10>> mylist;
  
};

TEST(testVersionGoogle, ValidVersion) {

  EXPECT_GT(version(), 0);
}

TEST_F(TestUnList, Iterator)
{
  using ::testing::AllOf;
  using ::testing::Ge;
  using ::testing::Le;

  for(auto it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_THAT(*it, AllOf(Ge(size_now), Le(size_end)));
}

TEST_F(TestUnList, PrefixPostfixIteratorElement)
{
  auto it = mylist.begin();
  ++it;
  EXPECT_EQ(*it, 1);
  it++;
  EXPECT_EQ(*it, 2);
}

TEST_F(TestUnList, Size)
{
  EXPECT_TRUE(size_end == mylist.size());
}

TEST_F(TestUnList, Clear)
{
  mylist.clear();
  EXPECT_TRUE(mylist.empty());
}

TEST_F(TestUnList, PopBack)
{
    for(std::size_t i = size_now; i < size_end; ++i)
      mylist.pop_front();
    
    EXPECT_TRUE(size_now == mylist.size());
}

TEST_F(TestUnList, PushBackPushFront)
{
    mylist.push_back(11);
    mylist.push_front(12);
    auto front = mylist.begin();
    auto back = front;
    for(std::size_t i = 0; i < mylist.size()-1; ++i)
        ++back;
    
    EXPECT_EQ(12, *front);
    EXPECT_EQ(11, *back);
}

TEST_F(TestUnListAllocator10Items, ThrowBad_allocateMaxSize)
{
  EXPECT_EQ(10, mylist.max_size());
  ASSERT_THROW(
    mylist.push_back(11),
    std::runtime_error
  );
}

TEST_F(TestUnListAllocator10Items, Iterator)
{
  using ::testing::AllOf;
  using ::testing::Ge;
  using ::testing::Le;

  for(auto it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_THAT(*it, AllOf(Ge(size_now), Le(size_end)));
}

TEST_F(TestUnListAllocator10Items, PrefixPostfixIteratorElement)
{
  auto it = mylist.begin();
  ++it;
  EXPECT_EQ(*it, 1);
  it++;
  EXPECT_EQ(*it, 2);
}

TEST_F(TestUnListAllocator10Items, Size)
{
  EXPECT_TRUE(size_end == mylist.size());
}

TEST_F(TestUnListAllocator10Items, Clear)
{
  mylist.clear();
  EXPECT_TRUE(mylist.empty());
}

TEST_F(TestUnListAllocator10Items, PopBack)
{
    for(std::size_t i = size_now; i < size_end; ++i)
      mylist.pop_front();
    
    EXPECT_TRUE(size_now == mylist.size());
}

TEST_F(TestUnListAllocator10Items, PushBackPushFront)
{
    mylist.clear();
    mylist.push_back(0);
    mylist.push_back(11);
    mylist.push_front(12);
    auto front = mylist.begin();
    auto back = front;
    for(std::size_t i = 0; i < mylist.size()-1; ++i)
        ++back;
    
    EXPECT_EQ(12, *front);
    EXPECT_EQ(11, *back);
}