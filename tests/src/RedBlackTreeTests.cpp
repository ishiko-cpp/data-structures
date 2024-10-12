// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "RedBlackTreeTests.hpp"
#include "Ishiko/DataStructures/RedBlackTree.hpp"

using namespace Ishiko;

RedBlackTreeTests::RedBlackTreeTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "RedBlackTree tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void RedBlackTreeTests::ConstructorTest1(Test& test)
{
    RedBlackTree<int> tree;

    ISHIKO_TEST_FAIL_IF_NEQ(tree.size(), 0);
    ISHIKO_TEST_PASS();
}
