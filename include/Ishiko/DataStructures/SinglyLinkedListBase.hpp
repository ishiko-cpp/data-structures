// SPDX-FileCopyrightText: 2005-2024 Xavier Leclercq
// SPDX-License-Identifier: BSL-1.0

#ifndef GUARD_ISHIKO_CPP_DATASTRUCTURES_SINGLYLINKEDLISTBASE_HPP
#define GUARD_ISHIKO_CPP_DATASTRUCTURES_SINGLYLINKEDLISTBASE_HPP

namespace Ishiko
{
    template<class Node>
    class SinglyLinkedListBase
    {
    public:
        ~SinglyLinkedListBase() noexcept;

        bool isEmpty() const noexcept;
        Node* head() noexcept;

        template<typename Callable>
        void traverse(Callable&& callable) const;

        void setHead(Node* node) noexcept;
        void insert(Node* new_node, Node* previous_node);

    private:
        Node* m_head = nullptr;
    };
}

template<class Node>
Ishiko::SinglyLinkedListBase<Node>::~SinglyLinkedListBase() noexcept
{
    delete m_head;
}

template<class Node>
bool Ishiko::SinglyLinkedListBase<Node>::isEmpty() const noexcept
{
    return (m_head == nullptr);
}

template<class Node>
Node* Ishiko::SinglyLinkedListBase<Node>::head() noexcept
{
    return m_head;
}

template<typename Node>
template<typename Callable>
void Ishiko::SinglyLinkedListBase<Node>::traverse(Callable&& callable) const
{
    Node* current_node = m_head;
    while (current_node)
    {
        callable(current_node->data());
        current_node = current_node->nextNode();
    }
}

template<class Node>
void Ishiko::SinglyLinkedListBase<Node>::setHead(Node* node) noexcept
{
    m_head = node;
}


template<typename Node>
void Ishiko::SinglyLinkedListBase<Node>::insert(Node* new_node, Node* previous_node)
{
    new_node->setNextNode(previous_node->nextNode());
    previous_node->setNextNode(new_node);
}

#endif
