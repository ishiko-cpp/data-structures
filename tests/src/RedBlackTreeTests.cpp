// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "RedBlackTreeTests.hpp"

using namespace Ishiko;

RedBlackTreeTests::RedBlackTreeTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "RedBlackTree tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void RedBlackTreeTests::ConstructorTest1(Test& test)
{
    RedBlackTree tree;

    ISHIKO_TEST_PASS();
}
