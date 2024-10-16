// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "DoublyLinkedListTests.hpp"
#include "Ishiko/DataStructures/DoublyLinkedList.hpp"

using namespace Ishiko;

DoublyLinkedListTests::DoublyLinkedListTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "DoublyLinkedList tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
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
