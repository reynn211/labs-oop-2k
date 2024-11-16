#pragma once
#include <iterator>

template<typename T>
struct Node {
    T data;
    Node* next;
};

template<typename T>
class ForwardListIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

private:
    Node<T>* current_;

public:
    explicit ForwardListIterator(Node<T>* node) : current_(node) {}

    reference operator*() { return current_->data; }
    pointer operator->() { return &current_->data; }

    ForwardListIterator& operator++() {
        current_ = current_->next;
        return *this;
    }

    ForwardListIterator operator++(int) {
        ForwardListIterator tmp = *this;
        current_ = current_->next;
        return tmp;
    }

    bool operator==(const ForwardListIterator& other) const {
        return current_ == other.current_;
    }

    bool operator!=(const ForwardListIterator& other) const {
        return !(*this == other);
    }
}; 