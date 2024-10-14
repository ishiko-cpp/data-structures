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

            DataType m_data;
        };

        BinaryTree() noexcept = default;

        bool isEmpty() const noexcept;
        Node* root(Error& error) noexcept;

        void setRoot(const DataType& data);
        void insert(const DataType& data);

    private:
        std::unique_ptr<Node> m_root = nullptr;
    };
}

template<typename DataType>
Ishiko::BinaryTree<DataType>::Node::Node(const DataType& data)
    : m_data{data}
{
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
    return m_root.get();
}

template<typename DataType>
void Ishiko::BinaryTree<DataType>::setRoot(const DataType& data)
{
    if (m_root == nullptr)
    {
        m_root.reset(new Node{data});
    }
    else
    {
        m_root->m_data = data;
    }
}

template<typename DataType>
void Ishiko::BinaryTree<DataType>::insert(const DataType& data)
{
    // TODO
}

#endif
