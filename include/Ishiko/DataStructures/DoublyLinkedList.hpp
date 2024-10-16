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
        public:
            Node(const DataType& data);
            ~Node() noexcept;

            const Node* previousNode() const noexcept;
            Node* previousNode() noexcept;
            void setPreviousNode(Node* node) noexcept;
            const Node* nextNode() const noexcept;
            Node* nextNode() noexcept;
            void setNextNode(Node* node) noexcept;

            const DataType& data() const noexcept;
            DataType& data() noexcept;

        private:
            Node* m_previous_node = nullptr;
            Node* m_next_node = nullptr;
            DataType m_data;
        };

        DoublyLinkedList() noexcept = default;
        ~DoublyLinkedList() noexcept;

        bool isEmpty() const noexcept;
        Node* head();
        Node* head(Error& error) noexcept;

        void setHead(const DataType& data);
        void setHead(const DataType& data, Error& error) noexcept;
        Node* insertAfter(const DataType& data, Node* previous_node);
        Node* insertBefore(const DataType& data, Node* next_node);

    private:
        static void linkNodes(Node* start_node, Node* end_node) noexcept;

        Node* m_head = nullptr;
    };
}

template<typename DataType>
Ishiko::DoublyLinkedList<DataType>::Node::Node(const DataType& data)
    : m_data(data)
{
}

template<typename DataType>
Ishiko::DoublyLinkedList<DataType>::Node::~Node() noexcept
{
    delete m_next_node;
}

template<typename DataType>
const typename Ishiko::DoublyLinkedList<DataType>::Node*
Ishiko::DoublyLinkedList<DataType>::Node::previousNode() const noexcept
{
    return m_previous_node;
}

template<typename DataType>
typename Ishiko::DoublyLinkedList<DataType>::Node* Ishiko::DoublyLinkedList<DataType>::Node::previousNode() noexcept
{
    return m_previous_node;
}

template<typename DataType>
void Ishiko::DoublyLinkedList<DataType>::Node::setPreviousNode(Node* node) noexcept
{
    m_previous_node = node;
}

template<typename DataType>
const typename Ishiko::DoublyLinkedList<DataType>::Node*
Ishiko::DoublyLinkedList<DataType>::Node::nextNode() const noexcept
{
    return m_next_node;
}

template<typename DataType>
typename Ishiko::DoublyLinkedList<DataType>::Node* Ishiko::DoublyLinkedList<DataType>::Node::nextNode() noexcept
{
    return m_next_node;
}

template<typename DataType>
void Ishiko::DoublyLinkedList<DataType>::Node::setNextNode(Node* node) noexcept
{
    m_next_node = node;
}

template<typename DataType>
const DataType& Ishiko::DoublyLinkedList<DataType>::Node::data() const noexcept
{
    return m_data;
}

template<typename DataType>
DataType& Ishiko::DoublyLinkedList<DataType>::Node::data() noexcept
{
    return m_data;
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


template<typename DataType>
void Ishiko::DoublyLinkedList<DataType>::setHead(const DataType& data)
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
void Ishiko::DoublyLinkedList<DataType>::setHead(const DataType& data, Error& error) noexcept
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

template<typename DataType>
typename Ishiko::DoublyLinkedList<DataType>::Node*
Ishiko::DoublyLinkedList<DataType>::insertAfter(const DataType& data, Node* previous_node)
{
    Node* new_node = new Node(data);
    Node* next_node = previous_node->nextNode();
    if (next_node)
    {
        linkNodes(new_node, next_node);
    }
    linkNodes(previous_node, new_node);
    return new_node;
}

template<typename DataType>
typename Ishiko::DoublyLinkedList<DataType>::Node*
Ishiko::DoublyLinkedList<DataType>::insertBefore(const DataType& data, Node* next_node)
{
    Node* new_node = new Node(data);
    Node* previous_node = next_node->previousNode();
    if (previous_node)
    {
        linkNodes(previous_node, new_node);
    }
    else
    {
        m_head = new_node;
    }
    linkNodes(new_node, next_node);
    return new_node;
}

template<typename DataType>
void Ishiko::DoublyLinkedList<DataType>::linkNodes(Node* start_node, Node* end_node) noexcept
{
    start_node->setNextNode(end_node);
    end_node->setPreviousNode(start_node);
}

#endif
