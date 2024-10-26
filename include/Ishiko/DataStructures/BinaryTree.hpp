// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_BINARYTREE_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_BINARYTREE_HPP

#include "DataStructuresErrorCategory.hpp"
#include "DataTypeTraits.hpp"
#include <Ishiko/Errors.hpp>
#include <Ishiko/Memory.hpp>

namespace Ishiko
{
    template<typename DataType, typename DataTypeTraits = DataTypeTraits<DataType>>
    class BinaryTree
    {
    public:
        class Node
        {
        public:
            Node(const DataType& data);
            Node(const DataType& data, Error& error) noexcept;
            ~Node() noexcept;

            const Node* parentNode() const noexcept;
            Node* parentNode() noexcept;
            void setParentNode(Node* node) noexcept;
            const Node* leftChildNode() const noexcept;
            Node* leftChildNode() noexcept;
            void setLeftChildNode(Node* node) noexcept;
            const Node* rightChildNode() const noexcept;
            Node* rightChildNode() noexcept;
            void setRightChildNode(Node* node) noexcept;

            const DataType& data() const noexcept;
            DataType& data() noexcept;

        private:
            Node* m_parent_node = nullptr;
            Node* m_left_child_node = nullptr;
            Node* m_right_child_node = nullptr;
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
        static void linkLeftNode(Node* parent_node, Node* left_node) noexcept;
        static void linkRightNode(Node* parent_node, Node* right_node) noexcept;

        Node* m_root = nullptr;
    };
}

template<typename DataType, typename DataTypeTraits>
Ishiko::BinaryTree<DataType, DataTypeTraits>::Node::Node(const DataType& data)
    : m_data(data)
{
}

template<typename DataType, typename DataTypeTraits>
Ishiko::BinaryTree<DataType, DataTypeTraits>::Node::Node(const DataType& data, Error& error) noexcept
    : m_data(DataTypeTraits::Copy(data, error))
{
}

template<typename DataType, typename DataTypeTraits>
Ishiko::BinaryTree<DataType, DataTypeTraits>::Node::~Node() noexcept
{
    delete m_left_child_node;
    delete m_right_child_node;
}

template<typename DataType, typename DataTypeTraits>
const typename Ishiko::BinaryTree<DataType, DataTypeTraits>::Node*
Ishiko::BinaryTree<DataType, DataTypeTraits>::Node::parentNode() const noexcept
{
    return m_parent_node;
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::BinaryTree<DataType, DataTypeTraits>::Node*
Ishiko::BinaryTree<DataType, DataTypeTraits>::Node::parentNode() noexcept
{
    return m_parent_node;
}

template<typename DataType, typename DataTypeTraits>
void Ishiko::BinaryTree<DataType, DataTypeTraits>::Node::setParentNode(Node* node) noexcept
{
    m_parent_node = node;
}

template<typename DataType, typename DataTypeTraits>
const typename Ishiko::BinaryTree<DataType, DataTypeTraits>::Node*
Ishiko::BinaryTree<DataType, DataTypeTraits>::Node::leftChildNode() const noexcept
{
    return m_left_child_node;
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::BinaryTree<DataType, DataTypeTraits>::Node*
Ishiko::BinaryTree<DataType, DataTypeTraits>::Node::leftChildNode() noexcept
{
    return m_left_child_node;
}

template<typename DataType, typename DataTypeTraits>
void Ishiko::BinaryTree<DataType, DataTypeTraits>::Node::setLeftChildNode(Node* node) noexcept
{
    m_left_child_node = node;
}

template<typename DataType, typename DataTypeTraits>
const typename Ishiko::BinaryTree<DataType, DataTypeTraits>::Node*
Ishiko::BinaryTree<DataType, DataTypeTraits>::Node::rightChildNode() const noexcept
{
    return m_right_child_node;
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::BinaryTree<DataType, DataTypeTraits>::Node*
Ishiko::BinaryTree<DataType, DataTypeTraits>::Node::rightChildNode() noexcept
{
    return m_right_child_node;
}

template<typename DataType, typename DataTypeTraits>
void Ishiko::BinaryTree<DataType, DataTypeTraits>::Node::setRightChildNode(Node* node) noexcept
{
    m_right_child_node = node;
}

template<typename DataType, typename DataTypeTraits>
const DataType& Ishiko::BinaryTree<DataType, DataTypeTraits>::Node::data() const noexcept
{
    return m_data;
}

template<typename DataType, typename DataTypeTraits>
DataType& Ishiko::BinaryTree<DataType, DataTypeTraits>::Node::data() noexcept
{
    return m_data;
}

template<typename DataType, typename DataTypeTraits>
Ishiko::BinaryTree<DataType, DataTypeTraits>::~BinaryTree() noexcept
{
    delete m_root;
}

template<typename DataType, typename DataTypeTraits>
bool Ishiko::BinaryTree<DataType, DataTypeTraits>::isEmpty() const noexcept
{
    return (m_root == nullptr);
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::BinaryTree<DataType, DataTypeTraits>::Node* Ishiko::BinaryTree<DataType, DataTypeTraits>::root()
{
    if (m_root == nullptr)
    {
        Throw(DataStructuresErrorCategory::Value::node_does_not_exist, "Binary tree is empty", __FILE__, __LINE__);
    }
    return m_root;
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::BinaryTree<DataType, DataTypeTraits>::Node*
Ishiko::BinaryTree<DataType, DataTypeTraits>::root(Error& error) noexcept
{
    if (m_root == nullptr)
    {
        Fail(DataStructuresErrorCategory::Value::node_does_not_exist, "Binary tree is empty", __FILE__, __LINE__,
            error);
    }
    return m_root;
}

template<typename DataType, typename DataTypeTraits>
template<typename Callable>
void Ishiko::BinaryTree<DataType, DataTypeTraits>::doInorderTraversal(Callable&& callable) const
{
    if (m_root)
    {
        doInorderTraversal(m_root, std::forward<Callable>(callable));
    }
}

template<typename DataType, typename DataTypeTraits>
template<typename Callable>
void Ishiko::BinaryTree<DataType, DataTypeTraits>::doInorderTraversal(const Node* parent_node, Callable&& callable) const
{
    // TODO: get rid of recursions
    if (parent_node->leftChildNode())
    {
        doInorderTraversal(parent_node->leftChildNode(), callable);
    }
    callable(parent_node->data());
    if (parent_node->rightChildNode())
    {
        doInorderTraversal(parent_node->rightChildNode(), callable);
    }
}

template<typename DataType, typename DataTypeTraits>
void Ishiko::BinaryTree<DataType, DataTypeTraits>::setRoot(const DataType& data)
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

template<typename DataType, typename DataTypeTraits>
void Ishiko::BinaryTree<DataType, DataTypeTraits>::setRoot(const DataType& data, Error& error) noexcept
{
    if (m_root == nullptr)
    {
        m_root = NewObject<Node>(error, data, error);
    }
    else
    {
        m_root->data() = data;
    }
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::BinaryTree<DataType, DataTypeTraits>::Node*
Ishiko::BinaryTree<DataType, DataTypeTraits>::insertLeft(const DataType& data, Node* parent_node)
{
    Node* existing_left_node = parent_node->leftChildNode();
    Node* new_node = new Node(data);
    linkLeftNode(new_node, existing_left_node);
    linkLeftNode(parent_node, new_node);
    return new_node;
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::BinaryTree<DataType, DataTypeTraits>::Node*
Ishiko::BinaryTree<DataType, DataTypeTraits>::insertRight(const DataType& data, Node* parent_node)
{
    Node* existing_right_node = parent_node->rightChildNode();
    Node* new_node = new Node(data);
    linkRightNode(new_node, existing_right_node);
    linkRightNode(parent_node, new_node);
    return new_node;
}

template<typename DataType, typename DataTypeTraits>
void Ishiko::BinaryTree<DataType, DataTypeTraits>::rotateLeft(Node* node)
{
    Node* right_child_node = node->rightChildNode();
    if (!right_child_node)
    {
        Throw(DataStructuresErrorCategory::Value::right_child_node_does_not_exist,
            "Left rotation requires a right child node", __FILE__, __LINE__);
    }

    Node* parent_node = node->parentNode();
    if (parent_node)
    {
        if (parent_node->leftChildNode() == node)
        {
            linkLeftNode(parent_node, right_child_node);
        }
        else
        {
            linkRightNode(parent_node, right_child_node);
        }
    }
    else
    {
        m_root = right_child_node;
        right_child_node->setParentNode(nullptr);
    }
    linkRightNode(node, right_child_node->leftChildNode());
    linkLeftNode(right_child_node, node);
}

template<typename DataType, typename DataTypeTraits>
void Ishiko::BinaryTree<DataType, DataTypeTraits>::rotateRight(Node* node)
{
    Node* left_child_node = node->leftChildNode();
    if (!left_child_node)
    {
        Throw(DataStructuresErrorCategory::Value::left_child_node_does_not_exist,
            "Right rotation requires a left child node", __FILE__, __LINE__);
    }

    Node* parent_node = node->parentNode();
    if (parent_node)
    {
        if (parent_node->leftChildNode() == node)
        {
            linkLeftNode(parent_node, left_child_node);
        }
        else
        {
            linkRightNode(parent_node, left_child_node);
        }
    }
    else
    {
        m_root = left_child_node;
        left_child_node->setParentNode(nullptr);
    }
    linkLeftNode(node, left_child_node->rightChildNode());
    linkRightNode(left_child_node, node);
}

template<typename DataType, typename DataTypeTraits>
void Ishiko::BinaryTree<DataType, DataTypeTraits>::linkLeftNode(Node* parent_node, Node* left_node) noexcept
{
    parent_node->setLeftChildNode(left_node);
    if (left_node)
    {
        left_node->setParentNode(parent_node);
    }
}

template<typename DataType, typename DataTypeTraits>
void Ishiko::BinaryTree<DataType, DataTypeTraits>::linkRightNode(Node* parent_node, Node* right_node) noexcept
{
    parent_node->setRightChildNode(right_node);
    if (right_node)
    {
        right_node->setParentNode(parent_node);
    }
}

#endif
