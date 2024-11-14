// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_REDBLACKTREE_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_REDBLACKTREE_HPP

namespace Ishiko
{
    template<class ValueType>
    class RedBlackTree
    {
    public:
        class Node
        {
        };

        RedBlackTree() noexcept = default;
        ~RedBlackTree() noexcept;

        void insert(const ValueType& value);

        size_t size() const noexcept;

    private:
        size_t m_size = 0;
        Node* m_root = nullptr;
    };
}

template<class ValueType>
Ishiko::RedBlackTree<ValueType>::~RedBlackTree() noexcept
{
    delete m_root;
}

template<class ValueType>
void Ishiko::RedBlackTree<ValueType>::insert(const ValueType& value)
{
}

template<class ValueType>
size_t Ishiko::RedBlackTree<ValueType>::size() const noexcept
{
    return m_size;
}

#endif
