// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "DoublyLinkedListTests.hpp"
#include "Ishiko/DataStructures/DoublyLinkedList.hpp"

using namespace Ishiko;

DoublyLinkedListTests::DoublyLinkedListTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "DoublyLinkedList tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("setHead test 1", SetHeadTest1);
    append<HeapAllocationErrorsTest>("setHead test 2", SetHeadTest2);
    append<HeapAllocationErrorsTest>("insertAfter test 1", InsertAfterTest1);
}

void DoublyLinkedListTests::ConstructorTest1(Test& test)
{
    DoublyLinkedList<int> list;

    ISHIKO_TEST_FAIL_IF_NOT(list.isEmpty());

    Error error;
    DoublyLinkedList<int>::Node* node = list.head(error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(node, nullptr);

    ISHIKO_TEST_PASS();
}

void DoublyLinkedListTests::SetHeadTest1(Test& test)
{
    DoublyLinkedList<int> list;
    list.setHead(5);

    ISHIKO_TEST_FAIL_IF(list.isEmpty());

    Error error;
    DoublyLinkedList<int>::Node* node = list.head(error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_ABORT_IF_EQ(node, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->nextNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->data(), 5);
    ISHIKO_TEST_PASS();
}

void DoublyLinkedListTests::SetHeadTest2(Test& test)
{
    Error error;

    DoublyLinkedList<int> list;
    list.setHead(5, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF(list.isEmpty());

    DoublyLinkedList<int>::Node* node = list.head(error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_ABORT_IF_EQ(node, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->nextNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->data(), 5);
    ISHIKO_TEST_PASS();
}

void DoublyLinkedListTests::InsertAfterTest1(Test& test)
{
    DoublyLinkedList<int> list;
    list.setHead(5);

    Error error;
    DoublyLinkedList<int>::Node* head_node = list.head(error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_ABORT_IF_EQ(head_node, nullptr);

    DoublyLinkedList<int>::Node* next_node = list.insertAfter(3, head_node);

    ISHIKO_TEST_ABORT_IF_EQ(next_node, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(head_node->nextNode(), next_node);
    ISHIKO_TEST_FAIL_IF_NEQ(next_node->nextNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(next_node->data(), 3);
    ISHIKO_TEST_PASS();
}
