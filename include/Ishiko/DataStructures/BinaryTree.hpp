// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_BINARYTREE_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_BINARYTREE_HPP

#include "DataStructuresErrorCategory.hpp"
#include <Ishiko/Errors.hpp>
#include <memory>

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
            Node(Node* left_node, const DataType& data);
            ~Node() noexcept;

            const Node* leftNode() const noexcept;
            Node* leftNode() noexcept;
            void setLeftNode(Node* node) noexcept;

            const DataType& data() const noexcept;
            DataType& data() noexcept;

        private:
            Node* m_left_node = nullptr;
            DataType m_data;
        };

        BinaryTree() noexcept = default;
        ~BinaryTree() noexcept;

        bool isEmpty() const noexcept;
        Node* root(Error& error) noexcept;

        void setRoot(const DataType& data);
        Node* insertLeft(const DataType& data, Node* parent_node);

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
Ishiko::BinaryTree<DataType>::Node::Node(Node* left_node, const DataType& data)
    : m_left_node{left_node}, m_data{data}
{
}

template<typename DataType>
Ishiko::BinaryTree<DataType>::Node::~Node() noexcept
{
    delete m_left_node;
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
typename Ishiko::BinaryTree<DataType>::Node* Ishiko::BinaryTree<DataType>::insertLeft(const DataType& data,
    Node* parent_node)
{
    Node* existing_left_node = parent_node->leftNode();
    Node* new_node = new Node{existing_left_node, data};
    parent_node->setLeftNode(new_node);
    return new_node;
}

#endif
