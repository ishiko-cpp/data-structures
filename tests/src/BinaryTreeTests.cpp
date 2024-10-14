// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "BinaryTreeTests.hpp"
#include "Ishiko/DataStructures/BinaryTree.hpp"

using namespace Ishiko;

BinaryTreeTests::BinaryTreeTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "BinaryTree tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
}

void BinaryTreeTests::ConstructorTest1(Test& test)
{
    BinaryTree<int> tree;

    ISHIKO_TEST_PASS();
}
