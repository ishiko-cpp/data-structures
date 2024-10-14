// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "BinaryTreeTests.hpp"
#include "Ishiko/DataStructures/BinaryTree.hpp"

using namespace Ishiko;

BinaryTreeTests::BinaryTreeTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "BinaryTree tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("setRoot test 1", SetRootTest1);
}

void BinaryTreeTests::ConstructorTest1(Test& test)
{
    BinaryTree<int> tree;

    ISHIKO_TEST_FAIL_IF_NOT(tree.isEmpty());

    Error error;
    BinaryTree<int>::Node* node = tree.root(error);

    ISHIKO_TEST_FAIL_IF_NOT(error);
    ISHIKO_TEST_FAIL_IF_NEQ(node, nullptr);
    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::SetRootTest1(Test& test)
{
    BinaryTree<int> tree;
    tree.setRoot(5);

    ISHIKO_TEST_FAIL_IF(tree.isEmpty());

    Error error;
    BinaryTree<int>::Node* node = tree.root(error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF_EQ(node, nullptr);
    ISHIKO_TEST_PASS();
}
