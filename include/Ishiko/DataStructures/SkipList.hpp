// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_SKIPLIST_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_SKIPLIST_HPP

#include "SinglyLinkedListBase.hpp"
#include <vector>

namespace Ishiko
{
    template<typename DataType>
    class SkipList
    {
    public:
        class Node
        {
        public:
            Node(const DataType& data) noexcept;
            ~Node() noexcept;

            const Node* nextNode() const noexcept;
            Node* nextNode() noexcept;
            void setNextNode(Node* node) noexcept;

            const DataType& data() const noexcept;
            DataType& data() noexcept;

        public:
            std::vector<Node*> m_next_nodes;

        private:
            DataType m_data;
        };

        SkipList(size_t (*get_random_level)()) noexcept;
        ~SkipList() noexcept = default;

        bool isEmpty() const noexcept;
        Node* head() noexcept;

        std::vector<Node*> find(const DataType& data) noexcept;

        Node* insert(const DataType& data);

    private:
        SinglyLinkedListBase<Node> m_list_impl;
        size_t (*m_get_random_level)() = nullptr;
    };
}

template<typename DataType>
Ishiko::SkipList<DataType>::Node::Node(const DataType& data) noexcept
    : m_data(data)
{
    m_next_nodes.push_back(nullptr);
}

template<typename DataType>
Ishiko::SkipList<DataType>::Node::~Node() noexcept
{
    delete m_next_nodes[0];
}

template<typename DataType>
const typename Ishiko::SkipList<DataType>::Node* Ishiko::SkipList<DataType>::Node::nextNode() const noexcept
{
    return m_next_nodes[0];
}

template<typename DataType>
typename Ishiko::SkipList<DataType>::Node* Ishiko::SkipList<DataType>::Node::nextNode() noexcept
{
    return m_next_nodes[0];
}

template<typename DataType>
void Ishiko::SkipList<DataType>::Node::setNextNode(Node* node) noexcept
{
    m_next_nodes[0] = node;
}

template<typename DataType>
const DataType& Ishiko::SkipList<DataType>::Node::data() const noexcept
{
    return m_data;
}

template<typename DataType>
DataType& Ishiko::SkipList<DataType>::Node::data() noexcept
{
    return m_data;
}

template<typename DataType>
Ishiko::SkipList<DataType>::SkipList(size_t(*get_random_level)()) noexcept
    : m_get_random_level(get_random_level)
{
}

template<typename DataType>
bool Ishiko::SkipList<DataType>::isEmpty() const noexcept
{
    return m_list_impl.isEmpty();
}

template<typename DataType>
typename Ishiko::SkipList<DataType>::Node* Ishiko::SkipList<DataType>::head() noexcept
{
    return m_list_impl.head();
}

template<typename DataType>
std::vector<typename Ishiko::SkipList<DataType>::Node*> Ishiko::SkipList<DataType>::find(const DataType& data) noexcept
{
    std::vector<Node*> previous_nodes;

    Node* head = m_list_impl.head();
    if (head)
    {
        size_t level = head->m_next_nodes.size() - 1;
        Node* current_node = head;
        while (true)
        {
            Node* next_node = current_node->m_next_nodes[level];
            if (next_node && (next_node->data() <= data))
            {
                current_node = next_node;
            }
            else if (level == 0)
            {
                previous_nodes.insert(previous_nodes.begin(), current_node);
                break;
            }
            else
            {
                previous_nodes.insert(previous_nodes.begin(), current_node);
                --level;
            }
        }
    }

    return previous_nodes;
}

template<typename DataType>
typename Ishiko::SkipList<DataType>::Node* Ishiko::SkipList<DataType>::insert(const DataType& data)
{
    Node* head = m_list_impl.head();
    if (!head)
    {
        Node* new_node = new Node(data);
        m_list_impl.setHead(new_node);
        return new_node;
    }
    else if (data < head->data())
    {
        Node* new_node = new Node(data);
        size_t levels = m_get_random_level();
        if (levels > head->m_next_nodes.size())
        {
            m_list_impl.head()->m_next_nodes.resize(levels, nullptr);
        }

        m_list_impl.setHead(new_node);
        new_node->m_next_nodes = head->m_next_nodes;

        head->m_next_nodes.resize(levels);

        for (size_t i = 0; i < head->m_next_nodes.size(); ++i)
        {
            head->m_next_nodes[i] = new_node->m_next_nodes[i];
            new_node->m_next_nodes[i] = head;
        }

        return new_node;
    }
    else
    {
        std::vector<Node*> previous_nodes = find(data);
        if (previous_nodes[0]->data() == data)
        {
            return previous_nodes[0];
        }
        Node* new_node = new Node(data);
        size_t levels = m_get_random_level();
        if (levels > previous_nodes.size())
        {
            head->m_next_nodes.resize(levels, nullptr);
            previous_nodes.resize(levels, head);
        }
        new_node->m_next_nodes.resize(levels);
        for (size_t i = 0; i < new_node->m_next_nodes.size(); ++i)
        {
            new_node->m_next_nodes[i] = previous_nodes[i]->m_next_nodes[i];
            previous_nodes[i]->m_next_nodes[i] = new_node;
        }
        return new_node;
    }
}

#endif
