// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_DOUBLYLINKEDLIST_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_DOUBLYLINKEDLIST_HPP

#include "DataStructuresErrorCategory.hpp"
#include "DataTypeTraits.hpp"
#include <Ishiko/Errors.hpp>

namespace Ishiko
{
    template<typename DataType, typename DataTypeTraits = DataTypeTraits<DataType>>
    class DoublyLinkedList
    {
    public:
        class Node
        {
        public:
            Node(const DataType& data);
            Node(const DataType& data, Error& error) noexcept;
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

        template<typename Callable>
        void traverse(Callable&& callable) const;

        void setHead(const DataType& data);
        void setHead(const DataType& data, Error& error) noexcept;
        Node* insertAfter(const DataType& data, Node* previous_node);
        Node* insertBefore(const DataType& data, Node* next_node);

    private:
        static void linkNodes(Node* start_node, Node* end_node) noexcept;

        Node* m_head = nullptr;
    };
}

template<typename DataType, typename DataTypeTraits>
Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node::Node(const DataType& data)
    : m_data(data)
{
}

template<typename DataType, typename DataTypeTraits>
Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node::Node(const DataType& data, Error& error) noexcept
    : m_data(DataTypeTraits::Copy(data, error))
{
}

template<typename DataType, typename DataTypeTraits>
Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node::~Node() noexcept
{
    delete m_next_node;
}

template<typename DataType, typename DataTypeTraits>
const typename Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node*
Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node::previousNode() const noexcept
{
    return m_previous_node;
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node*
Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node::previousNode() noexcept
{
    return m_previous_node;
}

template<typename DataType, typename DataTypeTraits>
void Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node::setPreviousNode(Node* node) noexcept
{
    m_previous_node = node;
}

template<typename DataType, typename DataTypeTraits>
const typename Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node*
Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node::nextNode() const noexcept
{
    return m_next_node;
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node*
Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node::nextNode() noexcept
{
    return m_next_node;
}

template<typename DataType, typename DataTypeTraits>
void Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node::setNextNode(Node* node) noexcept
{
    m_next_node = node;
}

template<typename DataType, typename DataTypeTraits>
const DataType& Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node::data() const noexcept
{
    return m_data;
}

template<typename DataType, typename DataTypeTraits>
DataType& Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node::data() noexcept
{
    return m_data;
}

template<typename DataType, typename DataTypeTraits>
Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::~DoublyLinkedList() noexcept
{
    delete m_head;
}

template<typename DataType, typename DataTypeTraits>
bool Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::isEmpty() const noexcept
{
    return (m_head == nullptr);
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node*
Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::head()
{
    if (m_head == nullptr)
    {
        Throw(DataStructuresErrorCategory::Value::node_does_not_exist, "Linked list is empty", __FILE__, __LINE__);
    }
    return m_head;
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node*
Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::head(Error& error) noexcept
{
    if (m_head == nullptr)
    {
        Fail(DataStructuresErrorCategory::Value::node_does_not_exist, "Linked list is empty", __FILE__, __LINE__,
            error);
    }
    return m_head;
}

template<typename DataType, typename DataTypeTraits>
template<typename Callable>
void Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::traverse(Callable&& callable) const
{
    Node* current_node = m_head;
    while (current_node)
    {
        callable(current_node->data());
        current_node = current_node->nextNode();
    }
}

template<typename DataType, typename DataTypeTraits>
void Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::setHead(const DataType& data)
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

template<typename DataType, typename DataTypeTraits>
void Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::setHead(const DataType& data, Error& error) noexcept
{
    if (m_head == nullptr)
    {
        m_head = NewObject<Node>(error, data, error);
    }
    else
    {
        m_head->data() = data;
    }
}

template<typename DataType, typename DataTypeTraits>
typename Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node*
Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::insertAfter(const DataType& data, Node* previous_node)
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

template<typename DataType, typename DataTypeTraits>
typename Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::Node*
Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::insertBefore(const DataType& data, Node* next_node)
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

template<typename DataType, typename DataTypeTraits>
void Ishiko::DoublyLinkedList<DataType, DataTypeTraits>::linkNodes(Node* start_node, Node* end_node) noexcept
{
    start_node->setNextNode(end_node);
    end_node->setPreviousNode(start_node);
}

#endif
