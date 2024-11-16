#pragma once
#include <memory_resource>
#include <memory>
#include "forward_list_iterator.h"

template<typename T>
class ForwardList {
private:
    using Allocator = std::pmr::polymorphic_allocator<Node<T>>;
    using AllocTraits = std::allocator_traits<Allocator>;
    Node<T>* head_;
    Allocator alloc_;

public:
    using iterator = ForwardListIterator<T>;

    explicit ForwardList(std::pmr::memory_resource* resource = std::pmr::get_default_resource())
        : head_(nullptr), alloc_(resource) {}
    
    ~ForwardList() {
        clear();
    }

    void push_front(const T& value) {
        Node<T>* new_node = alloc_.allocate(1);
        try {
            AllocTraits::construct(alloc_, new_node);
            new_node->data = value;
            new_node->next = head_;
            head_ = new_node;
        } catch (...) {
            alloc_.deallocate(new_node, 1);
            throw;
        }
    }

    void pop_front() {
        if (head_) {
            Node<T>* old_head = head_;
            head_ = head_->next;
            AllocTraits::destroy(alloc_, old_head);
            alloc_.deallocate(old_head, 1);
        }
    }

    void clear() {
        while (head_) {
            pop_front();
        }
    }

    iterator begin() { return iterator(head_); }
    iterator end() { return iterator(nullptr); }
}; 