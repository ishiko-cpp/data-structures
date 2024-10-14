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
    append<HeapAllocationErrorsTest>("insertLeft test 1", InsertLeftTest1);
    append<HeapAllocationErrorsTest>("insertLeft test 2", InsertLeftTest2);
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
    ISHIKO_TEST_ABORT_IF_EQ(node, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->data(), 5);
    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::InsertLeftTest1(Test& test)
{
    BinaryTree<int> tree;
    tree.setRoot(5);

    Error error;
    BinaryTree<int>::Node* root_node = tree.root(error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_ABORT_IF_EQ(root_node, nullptr);

    BinaryTree<int>::Node* left_child_node = tree.insertLeft(3, root_node);

    ISHIKO_TEST_ABORT_IF_EQ(left_child_node, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->leftNode(), left_child_node);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node->data(), 3);
    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::InsertLeftTest2(Test& test)
{
    BinaryTree<int> tree;
    tree.setRoot(5);

    Error error;
    BinaryTree<int>::Node* root_node = tree.root(error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_ABORT_IF_EQ(root_node, nullptr);

    BinaryTree<int>::Node* left_child_node_1 = tree.insertLeft(3, root_node);

    ISHIKO_TEST_ABORT_IF_EQ(left_child_node_1, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->leftNode(), left_child_node_1);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_1->data(), 3);

    BinaryTree<int>::Node* left_child_node_2 = tree.insertLeft(7, root_node);

    ISHIKO_TEST_ABORT_IF_EQ(left_child_node_2, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->leftNode(), left_child_node_2);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_2->leftNode(), left_child_node_1);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_2->data(), 7);

    ISHIKO_TEST_PASS();
}
