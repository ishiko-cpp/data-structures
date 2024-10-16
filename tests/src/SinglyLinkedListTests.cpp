// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "SinglyLinkedListTests.hpp"
#include "Ishiko/DataStructures/SinglyLinkedList.hpp"

using namespace Ishiko;

SinglyLinkedListTests::SinglyLinkedListTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "SinglyLinkedList tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void SinglyLinkedListTests::ConstructorTest1(Test& test)
{
    SinglyLinkedList<int> list;

    ISHIKO_TEST_PASS();
}
