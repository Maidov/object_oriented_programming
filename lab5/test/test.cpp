#include <gtest/gtest.h>
#include <vector>
#include "array.h"


TEST(AllocatorTest, TEST_01) {
    PoolAllocator<int> allocator;
    ASSERT_NO_THROW(allocator.allocate(1));
}

TEST(AllocatorTest, TEST_02) {
    PoolAllocator<int> allocator;
    int *tmp = allocator.allocate(1);
    ASSERT_NO_THROW(allocator.deallocate(tmp, 1));
}

TEST(AllocatorTest, TEST_03) {
    PoolAllocator<int> allocator;
    for (size_t i = 0; i < 30000; i++) {
        allocator.allocate();
    }
    ASSERT_ANY_THROW(allocator.allocate());
}

TEST(AllocatorTest, TEST_04) {
    PoolAllocator<int> allocator;
    int *tmp1 = allocator.allocate(1) + sizeof(int) * 2048;
    ASSERT_ANY_THROW(allocator.deallocate(tmp1, 1));
}

TEST(AllocatorTest, TEST_05) {
    PoolAllocator<int> allocator;
    int *tmp;
    for (size_t i = 0; i < 100; i++) {
        tmp = allocator.allocate(1);
    }
    ASSERT_NO_THROW(allocator.destroy(tmp));
}

TEST(VECTOR, Vector_Constructor) {
    ASSERT_NO_THROW(Vector<int> l;);
}

TEST(VECTOR, Vector_push_back_1) {
    Vector<int> l;
    l.push_back(1);
    ASSERT_TRUE(l[0] == 1);
}

TEST(VECTOR, Vector_push_back_2) {
    Vector<int> l;
    std::vector<int> m;
    for (size_t i = 0; i < 10; i++)
    {
        m.push_back(i);
        l.push_back(i);
    }
    bool flag = true;
    
    for (size_t i = 0; i < m.size(); i++)
    {
        if(m[i] != l[i]){flag = false; break;}
    }
    
    ASSERT_TRUE(flag);
}

TEST(VECTOR, Vector_get_size_1) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    ASSERT_TRUE(v.get_size() == 4);
}

TEST(VECTOR, Vector_get_size_2) {
    Vector<double> v;
    ASSERT_TRUE(v.get_size() == 0);
}

TEST(VECTOR, Vector_get_capacity_1) {
    Vector<double> v;
    ASSERT_TRUE(v.get_capacity() == 0);
}

TEST(VECTOR, Vector_get_capacity_2) {
    Vector<double> v;
    v.push_back(123);
    ASSERT_TRUE(v.get_capacity() == 1);
}

TEST(VECTOR, Vector_get_capacity_3) {
    Vector<double> v;
    v.push_back(123);
    v.push_back(12);
    v.push_back(1);
    ASSERT_TRUE(v.get_capacity() == 4);
}

TEST(VECTOR, Vector_clear) {
    Vector<double> v;
    v.push_back(123);
    v.push_back(12);
    v.push_back(1);
    v.clear();
    ASSERT_TRUE(v.get_size() == 0);
}

TEST(VECTOR, Vector_IndexOperator_1) {
    Vector<float> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(2);
    v.push_back(0);
    v.push_back(-9);
    ASSERT_TRUE(v[3] == 0);
}

TEST(VECTOR, Vector_IndexOperator_2) {
    Vector<float> v;
    v.push_back(1);
    ASSERT_TRUE(v[0] == 1);
}

TEST(VECTOR, Vector_IndexOperator_3) {
    Vector<float> v;
    for (size_t i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    ASSERT_TRUE(v[v.get_size() - 1] == 9);
}

TEST(VECTOR, Vector_remove_1) {
    Vector<float> v;
    v.push_back(1);
    v.remove(0);
    ASSERT_TRUE(v.get_size() == 0);
}

TEST(VECTOR, Vector_remove_2) {
    Vector<float> v;
    for (size_t i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    for (size_t i = 0; i < 9; i++)
    {
        v.remove(0);
    }
    ASSERT_TRUE(v.get_size() == 1);
}

TEST(VECTOR, Vector_remove_3) {
    Vector<float> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.remove(1);
    ASSERT_TRUE((v.get_size() == 2) and (v[0] == 1) and (v[1] == 3));
}


TEST(VECTOR, Vector_iterator_1) {
    Vector<int> v;
    v.push_back(123);
    v.push_back(12);
    v.push_back(1);
    size_t j = 0;
    bool flag = true;
    for (auto i = v.begin(); i != v.end(); ++i) {
        if (*i != v[j]) {
            flag = false;
        }
        j++;
    }
    ASSERT_TRUE(flag);
}

TEST(VECTOR, Vector_iterator_2) {
    Vector<int> v;
    const int a = 1;
    v.push_back(a);
    size_t j = 0;
    bool flag = true;
    for (auto i = v.cbegin(); i != v.cend(); i++) {
        if (*i != v[j]) {
            flag = false;
        }
        j++;
    }
    ASSERT_TRUE(flag);
}

TEST(VECTOR, Vector_iterator_3) {
    Vector<char> v;
    v.push_back('a');
    v.push_back('b');
    v.push_back('c');
    auto iter = v.begin();
    iter++;
    iter++;
    ASSERT_TRUE((*iter == 'c'));
}

TEST(VECTOR, Vector_iterator_4) {
    Vector<char> v;
    v.push_back('a');
    v.push_back('b');
    v.push_back('c');
    auto iter = v.begin();
    ASSERT_TRUE((*iter == 'a'));
}

TEST(VECTOR, Vector_iterator_5) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    auto iter1 = v.begin();
    auto iter2 = v.begin();
    ASSERT_TRUE(iter1 == iter2);
}

TEST(VECTOR, Vector_iterator_6) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    auto iter1 = v.begin();
    auto iter2 = v.begin();
    iter2++;
    ASSERT_TRUE(iter1 != iter2);
}

TEST(VECTOR, Vector_iterator_7) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    auto iter = v.begin();
    auto iter2 = v.begin();
    iter2++;
    iter2 = iter;
    ASSERT_TRUE(iter == iter2);
}

TEST(VECTOR, Vector_iterator_8) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    auto iter = v.begin();
    auto iter2 = v.begin();
    iter2++;
    ASSERT_TRUE(iter != iter2);
}

TEST(VECTOR, Vector_iterator_9) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    auto iter = v.end();
    auto iter2 = v.end();
    ASSERT_TRUE(iter == iter2);
}


TEST(VECTOR, Vector_iterator_10) {
    Vector<int> v;
    v.push_back(1);
    auto iter1 = v.cend();
    auto iter2 = v.cend();
    ASSERT_TRUE(iter1 == iter2);
}

TEST(VECTOR, Vector_iterator_11) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    auto iter1 = v.begin();
    auto iter2 = v.end();
    iter2 = iter1;
    ASSERT_TRUE(iter1 == iter2);
}

TEST(VECTOR, Vector_iterator_12) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    auto iter = v.begin();
    auto iterTMP = iter;
    auto iter2 = v.begin();
    iter2++;
    iter2 = std::move(iterTMP);
    ASSERT_TRUE(iter == iter2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}