// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_BINARYTREE_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_BINARYTREE_HPP

#include "DataStructuresErrorCategory.hpp"
#include <Ishiko/Errors.hpp>
#include <Ishiko/Memory.hpp>

namespace Ishiko
{
    template<typename DataType>
    class BinaryTree
    {
    public:
        class Node
        {
        public:
            Node(const DataType& data);
            Node(Node* left_node, Node* right_node, const DataType& data);
            ~Node() noexcept;

            const Node* parentNode() const noexcept;
            Node* parentNode() noexcept;
            void setParentNode(Node* node) noexcept;
            const Node* leftNode() const noexcept;
            Node* leftNode() noexcept;
            void setLeftNode(Node* node) noexcept;
            const Node* rightNode() const noexcept;
            Node* rightNode() noexcept;
            void setRightNode(Node* node) noexcept;

            const DataType& data() const noexcept;
            DataType& data() noexcept;

        private:
            Node* m_parent_node = nullptr;
            Node* m_left_node = nullptr;
            Node* m_right_node = nullptr;
            DataType m_data;
        };

        BinaryTree() noexcept = default;
        ~BinaryTree() noexcept;

        bool isEmpty() const noexcept;
        Node* root();
        Node* root(Error& error) noexcept;

        template<typename Callable>
        void doInorderTraversal(Callable&& callable) const;

        template<typename Callable>
        void doInorderTraversal(const Node* parent_node, Callable&& callable) const;

        void setRoot(const DataType& data);
        void setRoot(const DataType& data, Error& error) noexcept;
        Node* insertLeft(const DataType& data, Node* parent_node);
        // TODO
        //Node* insertLeft(const DataType& data, Node* parent_node, Error& error) noexcept;
        Node* insertRight(const DataType& data, Node* parent_node);

        void rotateLeft(Node* node);
        void rotateRight(Node* node);

    private:
        Node* m_root = nullptr;
    };
}

template<typename DataType>
Ishiko::BinaryTree<DataType>::Node::Node(const DataType& data)
    : m_data{data}
{
}

template<typename DataType>
Ishiko::BinaryTree<DataType>::Node::Node(Node* left_node, Node* right_node, const DataType& data)
    : m_left_node(left_node), m_right_node(right_node), m_data(data)
{
}

template<typename DataType>
Ishiko::BinaryTree<DataType>::Node::~Node() noexcept
{
    delete m_left_node;
    delete m_right_node;
}

template<typename DataType>
const typename Ishiko::BinaryTree<DataType>::Node* Ishiko::BinaryTree<DataType>::Node::parentNode() const noexcept
{
    return m_parent_node;
}

template<typename DataType>
typename Ishiko::BinaryTree<DataType>::Node* Ishiko::BinaryTree<DataType>::Node::parentNode() noexcept
{
    return m_parent_node;
}

template<typename DataType>
void Ishiko::BinaryTree<DataType>::Node::setParentNode(Node* node) noexcept
{
    m_parent_node = node;
}

template<typename DataType>
const typename Ishiko::BinaryTree<DataType>::Node* Ishiko::BinaryTree<DataType>::Node::leftNode() const noexcept
{
    return m_left_node;
}

template<typename DataType>
typename Ishiko::BinaryTree<DataType>::Node* Ishiko::BinaryTree<DataType>::Node::leftNode() noexcept
{
    return m_left_node;
}

template<typename DataType>
void Ishiko::BinaryTree<DataType>::Node::setLeftNode(Node* node) noexcept
{
    m_left_node = node;
    if (node)
    {
        node->setParentNode(this);
    }
}

template<typename DataType>
const typename Ishiko::BinaryTree<DataType>::Node* Ishiko::BinaryTree<DataType>::Node::rightNode() const noexcept
{
    return m_right_node;
}

template<typename DataType>
typename Ishiko::BinaryTree<DataType>::Node* Ishiko::BinaryTree<DataType>::Node::rightNode() noexcept
{
    return m_right_node;
}

template<typename DataType>
void Ishiko::BinaryTree<DataType>::Node::setRightNode(Node* node) noexcept
{
    m_right_node = node;
    if (node)
    {
        node->setParentNode(this);
    }
}

template<typename DataType>
const DataType& Ishiko::BinaryTree<DataType>::Node::data() const noexcept
{
    return m_data;
}

template<typename DataType>
DataType& Ishiko::BinaryTree<DataType>::Node::data() noexcept
{
    return m_data;
}

template<typename DataType>
Ishiko::BinaryTree<DataType>::~BinaryTree() noexcept
{
    delete m_root;
}

template<typename DataType>
bool Ishiko::BinaryTree<DataType>::isEmpty() const noexcept
{
    return (m_root == nullptr);
}

template<typename DataType>
typename Ishiko::BinaryTree<DataType>::Node* Ishiko::BinaryTree<DataType>::root(Error& error) noexcept
{
    if (m_root == nullptr)
    {
        Fail(DataStructuresErrorCategory::Value::generic_error, "Binary tree is empty", __FILE__, __LINE__, error);
    }
    return m_root;
}

template<typename DataType>
typename Ishiko::BinaryTree<DataType>::Node* Ishiko::BinaryTree<DataType>::root()
{
    if (m_root == nullptr)
    {
        Throw(DataStructuresErrorCategory::Value::generic_error, "Binary tree is empty", __FILE__, __LINE__);
    }
    return m_root;
}

template <typename DataType>
template<typename Callable>
void Ishiko::BinaryTree<DataType>::doInorderTraversal(Callable&& callable) const
{
    if (m_root)
    {
        doInorderTraversal(m_root, std::forward<Callable>(callable));
    }
}

template <typename DataType>
template<typename Callable>
void Ishiko::BinaryTree<DataType>::doInorderTraversal(const Node* parent_node, Callable&& callable) const
{
    // TODO: get rid of recursions
    if (parent_node->leftNode())
    {
        doInorderTraversal(parent_node->leftNode(), callable);
    }
    callable(parent_node->data());
    if (parent_node->rightNode())
    {
        doInorderTraversal(parent_node->rightNode(), callable);
    }
}

template<typename DataType>
void Ishiko::BinaryTree<DataType>::setRoot(const DataType& data)
{
    if (m_root == nullptr)
    {
        m_root = new Node(data);
    }
    else
    {
        m_root->data() = data;
    }
}

template<typename DataType>
void Ishiko::BinaryTree<DataType>::setRoot(const DataType& data, Error& error) noexcept
{
    if (m_root == nullptr)
    {
        m_root = NewObject<Node>(error, data);
    }
    else
    {
        m_root->data() = data;
    }
}

template<typename DataType>
typename Ishiko::BinaryTree<DataType>::Node* Ishiko::BinaryTree<DataType>::insertLeft(const DataType& data,
    Node* parent_node)
{
    Node* existing_left_node = parent_node->leftNode();
    Node* new_node = new Node(existing_left_node, nullptr, data);
    parent_node->setLeftNode(new_node);
    if (existing_left_node)
    {
        existing_left_node->setParentNode(new_node);
    }
    return new_node;
}

template<typename DataType>
typename Ishiko::BinaryTree<DataType>::Node* Ishiko::BinaryTree<DataType>::insertRight(const DataType& data,
    Node* parent_node)
{
    Node* existing_right_node = parent_node->rightNode();
    Node* new_node = new Node(nullptr, existing_right_node, data);
    parent_node->setRightNode(new_node);
    if (existing_right_node)
    {
        existing_right_node->setParentNode(new_node);
    }
    return new_node;
}

template<typename DataType>
void Ishiko::BinaryTree<DataType>::rotateLeft(Node* node)
{
    Node* right_child_node = node->rightNode();
    if (!right_child_node)
    {
        // TODO: error
    }

    Node* parent_node = node->parentNode();
    if (parent_node)
    {
        if (parent_node->leftNode() == node)
        {
            parent_node->setLeftNode(right_child_node);
        }
        else
        {
            parent_node->setRightNode(right_child_node);
        }
    }
    else
    {
        m_root = right_child_node;
        right_child_node->setParentNode(nullptr);
    }
    node->setRightNode(right_child_node->leftNode());
    right_child_node->setLeftNode(node);
}

template<typename DataType>
void Ishiko::BinaryTree<DataType>::rotateRight(Node* node)
{
    Node* left_child_node = node->leftNode();
    if (!left_child_node)
    {
        // TODO: error
    }

    Node* parent_node = node->parentNode();
    if (parent_node)
    {
        if (parent_node->leftNode() == node)
        {
            parent_node->setLeftNode(left_child_node);
        }
        else
        {
            parent_node->setRightNode(left_child_node);
        }
    }
    else
    {
        m_root = left_child_node;
        left_child_node->setParentNode(nullptr);
    }
    node->setLeftNode(left_child_node->rightNode());
    left_child_node->setRightNode(node);
}

#endif
