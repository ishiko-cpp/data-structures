// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_SINGLYLINKEDLIST_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_SINGLYLINKEDLIST_HPP

#include "DataStructuresErrorCategory.hpp"
#include <Ishiko/Errors.hpp>
#include <Ishiko/Memory.hpp>

namespace Ishiko
{
    template<typename DataType>
    class SinglyLinkedList
    {
    public:
        class Node
        {
        public:
            Node(const DataType& data);
            ~Node() noexcept;

            const Node* nextNode() const noexcept;
            Node* nextNode() noexcept;
            void setNextNode(Node* node) noexcept;

            const DataType& data() const noexcept;
            DataType& data() noexcept;

        private:
            Node* m_next_node = nullptr;
            DataType m_data;
        };

        SinglyLinkedList() noexcept = default;
        ~SinglyLinkedList() noexcept;

        bool isEmpty() const noexcept;
        Node* head();
        Node* head(Error& error) noexcept;

        void setHead(const DataType& data);
        void setHead(const DataType& data, Error& error) noexcept;

    private:
        Node* m_head = nullptr;
    };
}

template<typename DataType>
Ishiko::SinglyLinkedList<DataType>::Node::Node(const DataType& data)
    : m_data(data)
{
}

template<typename DataType>
Ishiko::SinglyLinkedList<DataType>::Node::~Node() noexcept
{
    delete m_next_node;
}

template<typename DataType>
Ishiko::SinglyLinkedList<DataType>::~SinglyLinkedList() noexcept
{
    delete m_head;
}

template<typename DataType>
const typename Ishiko::SinglyLinkedList<DataType>::Node*
Ishiko::SinglyLinkedList<DataType>::Node::nextNode() const noexcept
{
    return m_next_node;
}

template<typename DataType>
typename Ishiko::SinglyLinkedList<DataType>::Node* Ishiko::SinglyLinkedList<DataType>::Node::nextNode() noexcept
{
    return m_next_node;
}

template<typename DataType>
void Ishiko::SinglyLinkedList<DataType>::Node::setNextNode(Node* node) noexcept
{
    m_next_node = node;
}

template<typename DataType>
const DataType& Ishiko::SinglyLinkedList<DataType>::Node::data() const noexcept
{
    return m_data;
}

template<typename DataType>
DataType& Ishiko::SinglyLinkedList<DataType>::Node::data() noexcept
{
    return m_data;
}

template<typename DataType>
bool Ishiko::SinglyLinkedList<DataType>::isEmpty() const noexcept
{
    return (m_head == nullptr);
}

template<typename DataType>
typename Ishiko::SinglyLinkedList<DataType>::Node* Ishiko::SinglyLinkedList<DataType>::head()
{
    if (m_head == nullptr)
    {
        Throw(DataStructuresErrorCategory::Value::node_does_not_exist, "Linked list is empty", __FILE__, __LINE__);
    }
    return m_head;
}

template<typename DataType>
typename Ishiko::SinglyLinkedList<DataType>::Node* Ishiko::SinglyLinkedList<DataType>::head(Error& error) noexcept
{
    if (m_head == nullptr)
    {
        Fail(DataStructuresErrorCategory::Value::node_does_not_exist, "Linked list is empty", __FILE__, __LINE__,
            error);
    }
    return m_head;
}

template<typename DataType>
void Ishiko::SinglyLinkedList<DataType>::setHead(const DataType& data)
{
    if (m_head == nullptr)
    {
        m_head = new Node(data);
    }
    else
    {
        m_head->data() = data;
    }
}

template<typename DataType>
void Ishiko::SinglyLinkedList<DataType>::setHead(const DataType& data, Error& error) noexcept
{
    if (m_head == nullptr)
    {
        m_head = NewObject<Node>(error, data);
    }
    else
    {
        m_head->data() = data;
    }
}

#endif
