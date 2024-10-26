// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "SinglyLinkedListTests.hpp"
#include "Ishiko/DataStructures/SinglyLinkedList.hpp"

using namespace Ishiko;

SinglyLinkedListTests::SinglyLinkedListTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "SinglyLinkedList tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("setHead test 1", SetHeadTest1);
    append<HeapAllocationErrorsTest>("setHead test 2", SetHeadTest2);
    append<HeapAllocationErrorsTest>("insert test 1", InsertTest1);
    append<HeapAllocationErrorsTest>("traverse test 1", TraverseTest1);
    append<HeapAllocationErrorsTest>("traverse test 2", TraverseTest2);
    append<HeapAllocationErrorsTest>("traverse test 3", TraverseTest3);
}

void SinglyLinkedListTests::ConstructorTest1(Test& test)
{
    SinglyLinkedList<int> list;

    ISHIKO_TEST_FAIL_IF_NOT(list.isEmpty());

    SinglyLinkedList<int>::Node* node = list.head();

    ISHIKO_TEST_FAIL_IF_NEQ(node, nullptr);

    ISHIKO_TEST_PASS();
}

void SinglyLinkedListTests::SetHeadTest1(Test& test)
{
    SinglyLinkedList<int> list;
    list.setHead(5);

    ISHIKO_TEST_FAIL_IF(list.isEmpty());

    SinglyLinkedList<int>::Node* node = list.head();

    ISHIKO_TEST_ABORT_IF_EQ(node, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->nextNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->data(), 5);
    ISHIKO_TEST_PASS();
}

void SinglyLinkedListTests::SetHeadTest2(Test& test)
{
    Error error;

    SinglyLinkedList<int> list;
    list.setHead(5, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF(list.isEmpty());

    SinglyLinkedList<int>::Node* node = list.head();

    ISHIKO_TEST_ABORT_IF_EQ(node, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->nextNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->data(), 5);
    ISHIKO_TEST_PASS();
}

void SinglyLinkedListTests::InsertTest1(Test& test)
{
    SinglyLinkedList<int> list;
    list.setHead(5);

    SinglyLinkedList<int>::Node* head_node = list.head();

    ISHIKO_TEST_ABORT_IF_EQ(head_node, nullptr);

    SinglyLinkedList<int>::Node* next_node = list.insert(3, head_node);

    ISHIKO_TEST_ABORT_IF_EQ(next_node, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(head_node->nextNode(), next_node);
    ISHIKO_TEST_FAIL_IF_NEQ(next_node->nextNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(next_node->data(), 3);
    ISHIKO_TEST_PASS();
}

void SinglyLinkedListTests::TraverseTest1(Test& test)
{
    SinglyLinkedList<int> list;

    size_t called = 0;

    list.traverse(
        [&called](int data)
        {
            ++called;
        }
    );

    ISHIKO_TEST_FAIL_IF_NEQ(called, 0);
    ISHIKO_TEST_PASS();
}

void SinglyLinkedListTests::TraverseTest2(Test& test)
{
    SinglyLinkedList<int> list;
    list.setHead(5);

    std::vector<int> output;

    list.traverse(
        [&output](int data)
        {
            output.push_back(data);
        }
    );

    ISHIKO_TEST_FAIL_IF_NEQ(output, std::vector<int>({5}));
    ISHIKO_TEST_PASS();
}

void SinglyLinkedListTests::TraverseTest3(Test& test)
{
    SinglyLinkedList<int> list;
    list.setHead(5);
    list.insert(9, list.head());
    list.insert(7, list.head());

    std::vector<int> output;

    list.traverse(
        [&output](int data)
        {
            output.push_back(data);
        }
    );

    ISHIKO_TEST_FAIL_IF_NEQ(output, std::vector<int>({5, 7, 9}));
    ISHIKO_TEST_PASS();
}
