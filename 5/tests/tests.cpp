#include <gtest/gtest.h>
#include "fixed_memory_resource.h"
#include "forward_list.h"
#include <string>

struct TestStruct {
    int x;
    double y;
    std::string z;

    bool operator==(const TestStruct& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

class FixedMemoryResourceTest : public ::testing::Test {
protected:
    FixedMemoryResource resource{1024};
};

TEST_F(FixedMemoryResourceTest, AllocateAndDeallocate) {
    void* p1 = resource.allocate(64);
    ASSERT_NE(p1, nullptr);

    void* p2 = resource.allocate(128);
    ASSERT_NE(p2, nullptr);
    ASSERT_NE(p1, p2);

    resource.deallocate(p1, 64);
    void* p3 = resource.allocate(64);
    ASSERT_NE(p3, nullptr);
    ASSERT_EQ(p1, p3);
}

TEST_F(FixedMemoryResourceTest, ThrowsOnOverallocation) {
    EXPECT_THROW({
        [[maybe_unused]] void* ptr = resource.allocate(2048);
    }, std::bad_alloc);
}

class ForwardListTest : public ::testing::Test {
protected:
    FixedMemoryResource resource{1024};
    ForwardList<int> list{&resource};
};

TEST_F(ForwardListTest, PushFrontAndIterate) {
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    std::vector<int> expected{3, 2, 1};
    std::vector<int> actual;
    
    for (const auto& value : list) {
        actual.push_back(value);
    }

    ASSERT_EQ(actual, expected);
}

TEST_F(ForwardListTest, PopFront) {
    list.push_front(1);
    list.push_front(2);
    
    list.pop_front();
    
    std::vector<int> expected{1};
    std::vector<int> actual;
    
    for (const auto& value : list) {
        actual.push_back(value);
    }

    ASSERT_EQ(actual, expected);
}

TEST_F(ForwardListTest, Clear) {
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    
    list.clear();
    
    ASSERT_EQ(list.begin(), list.end());
}

TEST(ForwardListComplexTest, TestStructOperations) {
    FixedMemoryResource resource(1024);
    ForwardList<TestStruct> list(&resource);

    TestStruct s1{1, 1.1, "one"};
    TestStruct s2{2, 2.2, "two"};
    
    list.push_front(s1);
    list.push_front(s2);

    std::vector<TestStruct> expected{s2, s1};
    std::vector<TestStruct> actual;
    
    for (const auto& value : list) {
        actual.push_back(value);
    }

    ASSERT_EQ(actual, expected);
}

TEST(IteratorTest, ForwardIteratorRequirements) {
    FixedMemoryResource resource(1024);
    ForwardList<int> list(&resource);
    
    list.push_front(1);
    list.push_front(2);

    auto it = list.begin();
    
    ASSERT_EQ(*it, 2);
    
    ++it;
    ASSERT_EQ(*it, 1);
    
    auto it2 = list.begin();
    auto it3 = it2++;
    ASSERT_EQ(*it3, 2);
    ASSERT_EQ(*it2, 1);
    
    ASSERT_TRUE(list.begin() != list.end());
    it = list.begin();
    ++it;
    ++it;
    ASSERT_TRUE(it == list.end());
}

TEST(MemoryLeakTest, NoLeaksOnDestruction) {
    FixedMemoryResource* resource = new FixedMemoryResource(1024);
    {
        ForwardList<TestStruct> list(resource);
        list.push_front({1, 1.1, "test1"});
        list.push_front({2, 2.2, "test2"});
    }
    void* p = resource->allocate(1024);
    ASSERT_NE(p, nullptr);
    resource->deallocate(p, 1024);
    delete resource;
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 