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
}

void SinglyLinkedListTests::ConstructorTest1(Test& test)
{
    SinglyLinkedList<int> list;

    ISHIKO_TEST_FAIL_IF_NOT(list.isEmpty());

    Error error;
    SinglyLinkedList<int>::Node* node = list.head(error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(node, nullptr);

    ISHIKO_TEST_PASS();
}

void SinglyLinkedListTests::SetHeadTest1(Test& test)
{
    SinglyLinkedList<int> list;
    list.setHead(5);

    ISHIKO_TEST_FAIL_IF(list.isEmpty());

    Error error;
    SinglyLinkedList<int>::Node* node = list.head(error);

    ISHIKO_TEST_FAIL_IF(error);
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

    SinglyLinkedList<int>::Node* node = list.head(error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_ABORT_IF_EQ(node, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->nextNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->data(), 5);
    ISHIKO_TEST_PASS();
}
