// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_DOUBLYLINKEDLIST_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_DOUBLYLINKEDLIST_HPP

#include "DataStructuresErrorCategory.hpp"
#include <Ishiko/Errors.hpp>

namespace Ishiko
{
    template<typename DataType>
    class DoublyLinkedList
    {
    public:
        class Node
        {
        };

        DoublyLinkedList() noexcept = default;
        ~DoublyLinkedList() noexcept;

        bool isEmpty() const noexcept;
        Node* head();
        Node* head(Error& error) noexcept;

    private:
        Node* m_head = nullptr;
    };
}

template<typename DataType>
Ishiko::DoublyLinkedList<DataType>::~DoublyLinkedList() noexcept
{
    delete m_head;
}

template<typename DataType>
bool Ishiko::DoublyLinkedList<DataType>::isEmpty() const noexcept
{
    return (m_head == nullptr);
}

template<typename DataType>
typename Ishiko::DoublyLinkedList<DataType>::Node* Ishiko::DoublyLinkedList<DataType>::head()
{
    if (m_head == nullptr)
    {
        Throw(DataStructuresErrorCategory::Value::node_does_not_exist, "Linked list is empty", __FILE__, __LINE__);
    }
    return m_head;
}

template<typename DataType>
typename Ishiko::DoublyLinkedList<DataType>::Node* Ishiko::DoublyLinkedList<DataType>::head(Error& error) noexcept
{
    if (m_head == nullptr)
    {
        Fail(DataStructuresErrorCategory::Value::node_does_not_exist, "Linked list is empty", __FILE__, __LINE__,
            error);
    }
    return m_head;
}

#endif
