// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#include "BinaryTreeTests.hpp"
#include "Ishiko/DataStructures/BinaryTree.hpp"
#include <string>

using namespace Ishiko;

BinaryTreeTests::BinaryTreeTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "BinaryTree tests", context)
{
    append<HeapAllocationErrorsTest>("Constructor test 1", ConstructorTest1);
    append<HeapAllocationErrorsTest>("Constructor test 2", ConstructorTest2);
    append<HeapAllocationErrorsTest>("setRoot test 1", SetRootTest1);
    append<HeapAllocationErrorsTest>("setRoot test 2", SetRootTest2);
    append<HeapAllocationErrorsTest>("setRoot test 3", SetRootTest3);
    append<HeapAllocationErrorsTest>("setRoot test 4", SetRootTest4);
    append<HeapAllocationErrorsTest>("insertLeft test 1", InsertLeftTest1);
    append<HeapAllocationErrorsTest>("insertLeft test 2", InsertLeftTest2);
    append<HeapAllocationErrorsTest>("insertRight test 1", InsertRightTest1);
    append<HeapAllocationErrorsTest>("insertRight test 2", InsertRightTest2);
    append<HeapAllocationErrorsTest>("doInorderTraversal test 1", DoInorderTraversalTest1);
    append<HeapAllocationErrorsTest>("doInorderTraversal test 2", DoInorderTraversalTest2);
    append<HeapAllocationErrorsTest>("doInorderTraversal test 3", DoInorderTraversalTest3);
    append<HeapAllocationErrorsTest>("rotateLeft test 1", RotateLeftTest1);
    append<HeapAllocationErrorsTest>("rotateLeft test 2", RotateLeftTest2);
    append<HeapAllocationErrorsTest>("rotateRight test 1", RotateRightTest1);
    append<HeapAllocationErrorsTest>("rotateRight test 2", RotateRightTest2);
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

void BinaryTreeTests::ConstructorTest2(Test& test)
{
    BinaryTree<std::string> tree;

    ISHIKO_TEST_FAIL_IF_NOT(tree.isEmpty());

    Error error;
    BinaryTree<std::string>::Node* node = tree.root(error);

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
    ISHIKO_TEST_FAIL_IF_NEQ(node->parentNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->data(), 5);
    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::SetRootTest2(Test& test)
{
    Error error;

    BinaryTree<int> tree;
    tree.setRoot(5, error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF(tree.isEmpty());

    BinaryTree<int>::Node* node = tree.root(error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_ABORT_IF_EQ(node, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->parentNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->data(), 5);
    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::SetRootTest3(Test& test)
{
    BinaryTree<std::string> tree;
    tree.setRoot("root");

    ISHIKO_TEST_FAIL_IF(tree.isEmpty());

    Error error;
    BinaryTree<std::string>::Node* node = tree.root(error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_ABORT_IF_EQ(node, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->parentNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->data(), "root");
    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::SetRootTest4(Test& test)
{
    Error error;

    BinaryTree<std::string> tree;
    tree.setRoot("root", error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_FAIL_IF(tree.isEmpty());

    BinaryTree<std::string>::Node* node = tree.root(error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_ABORT_IF_EQ(node, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->parentNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(node->data(), "root");
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
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->leftChildNode(), left_child_node);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node->parentNode(), root_node);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node->rightChildNode(), nullptr);
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
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->leftChildNode(), left_child_node_1);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_1->parentNode(), root_node);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_1->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_1->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_1->data(), 3);

    BinaryTree<int>::Node* left_child_node_2 = tree.insertLeft(7, root_node);

    ISHIKO_TEST_ABORT_IF_EQ(left_child_node_2, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->leftChildNode(), left_child_node_2);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_2->parentNode(), root_node);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_2->leftChildNode(), left_child_node_1);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_2->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_2->data(), 7);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_1->parentNode(), left_child_node_2);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_1->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_1->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_1->data(), 3);

    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::InsertRightTest1(Test& test)
{
    BinaryTree<int> tree;
    tree.setRoot(5);

    Error error;
    BinaryTree<int>::Node* root_node = tree.root(error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_ABORT_IF_EQ(root_node, nullptr);

    BinaryTree<int>::Node* right_child_node = tree.insertRight(3, root_node);

    ISHIKO_TEST_ABORT_IF_EQ(right_child_node, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->rightChildNode(), right_child_node);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node->parentNode(), root_node);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node->data(), 3);
    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::InsertRightTest2(Test& test)
{
    BinaryTree<int> tree;
    tree.setRoot(5);

    Error error;
    BinaryTree<int>::Node* root_node = tree.root(error);

    ISHIKO_TEST_FAIL_IF(error);
    ISHIKO_TEST_ABORT_IF_EQ(root_node, nullptr);

    BinaryTree<int>::Node* right_child_node_1 = tree.insertRight(3, root_node);

    ISHIKO_TEST_ABORT_IF_EQ(right_child_node_1, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->rightChildNode(), right_child_node_1);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_1->parentNode(), root_node);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_1->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_1->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_1->data(), 3);

    BinaryTree<int>::Node* right_child_node_2 = tree.insertRight(7, root_node);

    ISHIKO_TEST_ABORT_IF_EQ(right_child_node_2, nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->rightChildNode(), right_child_node_2);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_2->parentNode(), root_node);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_2->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_2->rightChildNode(), right_child_node_1);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_2->data(), 7);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_1->parentNode(), right_child_node_2);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_1->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_1->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_1->data(), 3);

    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::DoInorderTraversalTest1(Test& test)
{
    BinaryTree<int> tree;

    size_t called = 0;

    tree.doInorderTraversal(
        [&called](int data)
        {
            ++called;
        }
    );

    ISHIKO_TEST_FAIL_IF_NEQ(called, 0);
    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::DoInorderTraversalTest2(Test& test)
{
    BinaryTree<int> tree;
    tree.setRoot(5);

    std::vector<int> output;

    tree.doInorderTraversal(
        [&output](int data)
        {
            output.push_back(data);
        }
    );

    ISHIKO_TEST_FAIL_IF_NEQ(output, std::vector<int>({5}));
    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::DoInorderTraversalTest3(Test& test)
{
    BinaryTree<int> tree;
    tree.setRoot(5);
    tree.insertLeft(3, tree.root());
    tree.insertRight(7, tree.root());

    std::vector<int> output;

    tree.doInorderTraversal(
        [&output](int data)
        {
            output.push_back(data);
        }
    );

    ISHIKO_TEST_FAIL_IF_NEQ(output, std::vector<int>({3, 5, 7}));
    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::RotateLeftTest1(Test& test)
{
    BinaryTree<int> tree;
    tree.setRoot(5);
    BinaryTree<int>::Node* root_node = tree.root();
    BinaryTree<int>::Node* right_child_node = tree.insertRight(7, root_node);

    tree.rotateLeft(root_node);

    ISHIKO_TEST_FAIL_IF_NEQ(tree.root(), right_child_node);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node->parentNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node->leftChildNode(), root_node);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node->data(), 7);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->parentNode(), right_child_node);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->data(), 5);
    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::RotateLeftTest2(Test& test)
{
    BinaryTree<int> tree;
    tree.setRoot(5);
    BinaryTree<int>::Node* root_node = tree.root();
    BinaryTree<int>::Node* right_child_node_1 = tree.insertRight(7, root_node);
    BinaryTree<int>::Node* right_child_node_2 = tree.insertRight(9, right_child_node_1);

    tree.rotateLeft(right_child_node_1);

    ISHIKO_TEST_FAIL_IF_NEQ(tree.root(), root_node);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->rightChildNode(), right_child_node_2);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->data(), 5);

    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_2->parentNode(), root_node);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_2->leftChildNode(), right_child_node_1);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_2->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_2->data(), 9);

    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_1->parentNode(), right_child_node_2);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_1->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_1->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(right_child_node_1->data(), 7);
    
    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::RotateRightTest1(Test& test)
{
    BinaryTree<int> tree;
    tree.setRoot(5);
    BinaryTree<int>::Node* root_node = tree.root();
    BinaryTree<int>::Node* left_child_node = tree.insertLeft(3, root_node);

    tree.rotateRight(root_node);

    ISHIKO_TEST_FAIL_IF_NEQ(tree.root(), left_child_node);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node->parentNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node->rightChildNode(), root_node);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node->data(), 3);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->parentNode(), left_child_node);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->data(), 5);
    ISHIKO_TEST_PASS();
}

void BinaryTreeTests::RotateRightTest2(Test& test)
{
    BinaryTree<int> tree;
    tree.setRoot(5);
    BinaryTree<int>::Node* root_node = tree.root();
    BinaryTree<int>::Node* left_child_node_1 = tree.insertLeft(3, root_node);
    BinaryTree<int>::Node* left_child_node_2 = tree.insertLeft(1, left_child_node_1);

    tree.rotateRight(left_child_node_1);

    ISHIKO_TEST_FAIL_IF_NEQ(tree.root(), root_node);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->leftChildNode(), left_child_node_2);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(root_node->data(), 5);

    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_2->parentNode(), root_node);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_2->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_2->rightChildNode(), left_child_node_1);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_2->data(), 1);

    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_1->parentNode(), left_child_node_2);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_1->leftChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_1->rightChildNode(), nullptr);
    ISHIKO_TEST_FAIL_IF_NEQ(left_child_node_1->data(), 3);

    ISHIKO_TEST_PASS();
}
