// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_SINGLYLINKEDLIST_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_SINGLYLINKEDLIST_HPP

#include "DataStructuresErrorCategory.hpp"
#include "DataTypeTraits.hpp"
#include "SinglyLinkedListBase.hpp"
#include <Ishiko/Errors.hpp>
#include <Ishiko/Memory.hpp>

namespace Ishiko
{
    template<typename DataType, typename DataTypeTraits = DataTypeTraits<DataType>>
    class SinglyLinkedList
    {
    public:
        class Node
        {
        public:
            Node(const DataType& data);
            Node(const DataType& data, Error& error) noexcept;
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
        ~SinglyLinkedList() noexcept = default;

        bool isEmpty() const noexcept;
        Node* head() noexcept;

        template<typename Callable>
        void traverse(Callable&& callable) const;

        void setHead(const DataType& data);
        void setHead(const DataType& data, Error& error) noexcept;
        Node* insert(const DataType& data, Node* previous_node);

    private:
        SinglyLinkedListBase<Node> m_list_impl;
    };
}

template<typename DataType, typename DataTypeTraits>
Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::Node::Node(const DataType& data)
    : m_data(data)
{
}

template<typename DataType, typename DataTypeTraits>
Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::Node::Node(const DataType& data, Error& error) noexcept
    : m_data(DataTypeTraits::Copy(data, error))
{
}

template<typename DataType, typename DataTypeTraits>
Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::Node::~Node() noexcept
{
    delete m_next_node;
}

template<typename DataType, typename DataTypeTraits>
const typename Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::Node*
Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::Node::nextNode() const noexcept
{
    return m_next_node;
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::Node*
Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::Node::nextNode() noexcept
{
    return m_next_node;
}

template<typename DataType, typename DataTypeTraits>
void Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::Node::setNextNode(Node* node) noexcept
{
    m_next_node = node;
}

template<typename DataType, typename DataTypeTraits>
const DataType& Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::Node::data() const noexcept
{
    return m_data;
}

template<typename DataType, typename DataTypeTraits>
DataType& Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::Node::data() noexcept
{
    return m_data;
}

template<typename DataType, typename DataTypeTraits>
bool Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::isEmpty() const noexcept
{
    return m_list_impl.isEmpty();
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::Node*
Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::head() noexcept
{
    return m_list_impl.head();
}

template<typename DataType, typename DataTypeTraits>
template<typename Callable>
void Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::traverse(Callable&& callable) const
{
    m_list_impl.traverse(std::forward<Callable>(callable));
}

template<typename DataType, typename DataTypeTraits>
void Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::setHead(const DataType& data)
{
    Node* head = m_list_impl.head();
    if (head)
    {
        head->data() = data;
    }
    else
    {
        m_list_impl.setHead(new Node(data));
    }
}

template<typename DataType, typename DataTypeTraits>
void Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::setHead(const DataType& data, Error& error) noexcept
{
    Node* head = m_list_impl.head();
    if (head)
    {
        head->data() = data;
    }
    else
    {
        Node* new_head = NewObject<Node>(error, data, error);
        if (!error)
        {
            m_list_impl.setHead(new_head);
        }
    }
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::Node*
Ishiko::SinglyLinkedList<DataType, DataTypeTraits>::insert(const DataType& data, Node* previous_node)
{
    Node* new_node = new Node(data);
    m_list_impl.insert(new_node, previous_node);
    return new_node;
}

#endif
