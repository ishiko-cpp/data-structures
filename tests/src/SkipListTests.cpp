// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "SkipListTests.hpp"
#include "Ishiko/DataStructures/SkipList.hpp"
#include <random>

namespace
{
    size_t numLevels()
    {
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<> dis(0.0, 1.0);

        size_t numLevels = 1;
        while ((numLevels < 20) && (dis(gen) < 0.5))
        {
            ++numLevels;
        }
        return numLevels;
    }

    static size_t currentDummyLevel = 0;
    size_t dummyNumLevels()
    {
        static size_t levels[] = {2, 1, 4, 2};
        return levels[currentDummyLevel++];
    }
}

using namespace Ishiko;

SkipListTests::SkipListTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "SkipList tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("insert test 1", InsertTest1);
    append<HeapAllocationErrorsTest>("insert test 2", InsertTest2);
    append<HeapAllocationErrorsTest>("insert test 3", InsertTest3);
    append<HeapAllocationErrorsTest>("insert test 4", InsertTest4);
    append<HeapAllocationErrorsTest>("insert test 5", InsertTest5);
    append<HeapAllocationErrorsTest>("insert test 6", InsertTest6);
    append<HeapAllocationErrorsTest>("insert test 7", InsertTest7);
}

void SkipListTests::ConstructorTest1(Test& test)
{
    SkipList<int> list(numLevels);

    ISHIKO_TEST_FAIL_IF_NOT(list.isEmpty());

    SkipList<int>::Node* node = list.head();

    ISHIKO_TEST_FAIL_IF_NEQ(node, nullptr);

    ISHIKO_TEST_PASS();
}

void SkipListTests::InsertTest1(Test& test)
{
    currentDummyLevel = 0;
    SkipList<int> list(dummyNumLevels);
    list.insert(5);

    ISHIKO_TEST_FAIL_IF(list.isEmpty());

    SkipList<int>::Node* node = list.head();

    ISHIKO_TEST_ABORT_IF_EQ(node, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->nextNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->data(), 5);
    ISHIKO_TEST_FAIL_IF_NEQ(node->m_next_nodes.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(node->m_next_nodes[0], nullptr);
    ISHIKO_TEST_PASS();
}

void SkipListTests::InsertTest2(Test& test)
{
    currentDummyLevel = 0;
    SkipList<int> list(dummyNumLevels);
    list.insert(5);
    SkipList<int>::Node* node_r_2 = list.insert(7);

    ISHIKO_TEST_FAIL_IF(list.isEmpty());

    SkipList<int>::Node* node_1 = list.head();

    ISHIKO_TEST_ABORT_IF_EQ(node_1, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->data(), 5);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes[0], node_r_2);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes[1], node_r_2);

    SkipList<int>::Node* node_2 = node_1->nextNode();

    ISHIKO_TEST_ABORT_IF_EQ(node_2, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->data(), 7);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->nextNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes[0], nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes[1], nullptr);

    ISHIKO_TEST_PASS();
}

void SkipListTests::InsertTest3(Test& test)
{
    currentDummyLevel = 0;
    SkipList<int> list(dummyNumLevels);
    list.insert(5);
    SkipList<int>::Node* node_r_2 = list.insert(7);
    SkipList<int>::Node* node_r_3 = list.insert(9);

    ISHIKO_TEST_FAIL_IF(list.isEmpty());

    SkipList<int>::Node* node_1 = list.head();

    ISHIKO_TEST_ABORT_IF_EQ(node_1, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->data(), 5);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes[0], node_r_2);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes[1], node_r_2);

    SkipList<int>::Node* node_2 = node_1->nextNode();

    ISHIKO_TEST_ABORT_IF_EQ(node_2, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->data(), 7);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes[0], node_r_3);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes[1], nullptr);

    SkipList<int>::Node* node_3 = node_2->nextNode();

    ISHIKO_TEST_ABORT_IF_EQ(node_3, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->data(), 9);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->nextNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->m_next_nodes.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->m_next_nodes[0], nullptr);

    ISHIKO_TEST_PASS();
}

void SkipListTests::InsertTest4(Test& test)
{
    currentDummyLevel = 0;
    SkipList<int> list(dummyNumLevels);
    list.insert(5);
    SkipList<int>::Node* node_r_2 = list.insert(9);
    SkipList<int>::Node* node_r_3 = list.insert(7);

    ISHIKO_TEST_FAIL_IF(list.isEmpty());

    SkipList<int>::Node* node_1 = list.head();

    ISHIKO_TEST_ABORT_IF_EQ(node_1, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->data(), 5);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes[0], node_r_3);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes[1], node_r_2);

    SkipList<int>::Node* node_2 = node_1->nextNode();

    ISHIKO_TEST_ABORT_IF_EQ(node_2, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->data(), 7);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes[0], node_r_2);

    SkipList<int>::Node* node_3 = node_2->nextNode();

    ISHIKO_TEST_ABORT_IF_EQ(node_3, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->data(), 9);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->nextNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->m_next_nodes.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->m_next_nodes[0], nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->m_next_nodes[1], nullptr);

    ISHIKO_TEST_PASS();
}

void SkipListTests::InsertTest5(Test& test)
{
    currentDummyLevel = 0;
    SkipList<int> list(dummyNumLevels);
    list.insert(5);
    SkipList<int>::Node* node_r_2 = list.insert(9);
    SkipList<int>::Node* node_r_3 = list.insert(7);
    SkipList<int>::Node* node_r_4 = list.insert(9);

    ISHIKO_TEST_FAIL_IF(list.isEmpty());

    SkipList<int>::Node* node_1 = list.head();

    ISHIKO_TEST_ABORT_IF_EQ(node_1, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->data(), 5);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes[0], node_r_3);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes[1], node_r_2);

    SkipList<int>::Node* node_2 = node_1->nextNode();

    ISHIKO_TEST_ABORT_IF_EQ(node_2, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->data(), 7);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes[0], node_r_2);

    SkipList<int>::Node* node_3 = node_2->nextNode();

    ISHIKO_TEST_ABORT_IF_EQ(node_3, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->data(), 9);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->nextNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->m_next_nodes.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->m_next_nodes[0], nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->m_next_nodes[1], nullptr);

    ISHIKO_TEST_PASS();
}

void SkipListTests::InsertTest6(Test& test)
{
    currentDummyLevel = 0;
    SkipList<int> list(dummyNumLevels);
    SkipList<int>::Node* node_r_1 = list.insert(5);
    SkipList<int>::Node* node_r_2 = list.insert(7);
    SkipList<int>::Node* node_r_3 = list.insert(3);

    ISHIKO_TEST_FAIL_IF(list.isEmpty());

    SkipList<int>::Node* node_1 = list.head();

    ISHIKO_TEST_ABORT_IF_EQ(node_1, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->data(), 3);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes[0], node_r_1);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes[1], node_r_2);

    SkipList<int>::Node* node_2 = node_1->nextNode();

    ISHIKO_TEST_ABORT_IF_EQ(node_2, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->data(), 5);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes.size(), 1);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes[0], node_r_2);

    SkipList<int>::Node* node_3 = node_2->nextNode();

    ISHIKO_TEST_ABORT_IF_EQ(node_3, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->data(), 7);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->nextNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->m_next_nodes.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->m_next_nodes[0], nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_3->m_next_nodes[1], nullptr);

    ISHIKO_TEST_PASS();
}

void SkipListTests::InsertTest7(Test& test)
{
    currentDummyLevel = 0;
    SkipList<int> list(dummyNumLevels);
    SkipList<int>::Node* node_r_1 = list.insert(5);
    SkipList<int>::Node* node_r_2 = list.insert(3);

    ISHIKO_TEST_FAIL_IF(list.isEmpty());

    SkipList<int>::Node* node_1 = list.head();

    ISHIKO_TEST_ABORT_IF_EQ(node_1, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->data(), 3);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes[0], node_r_1);
    ISHIKO_TEST_FAIL_IF_NEQ(node_1->m_next_nodes[1], node_r_1);

    SkipList<int>::Node* node_2 = node_1->nextNode();

    ISHIKO_TEST_ABORT_IF_EQ(node_2, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->data(), 5);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes.size(), 2);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes[0], nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node_2->m_next_nodes[1], nullptr);

    ISHIKO_TEST_PASS();
}
