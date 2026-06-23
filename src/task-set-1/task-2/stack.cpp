#include "stack.hpp"

#include <cstddef>
#include <iostream>

Stack::~Stack() {
    delete[] values;
}

Stack::Stack(const Stack& other_stack) : top(other_stack.top), size(other_stack.size), values(new char[size]) {
    for (std::size_t i {0}; i < top; ++i) {
        values[i] = other_stack.values[i];
    }
}

Stack& Stack::operator=(const Stack& other_stack) {
    if (this == &other_stack) {
        return *this;
    }

    delete[] values;

    top = other_stack.top;
    size = other_stack.size;
    values = new char[size];

    for (std::size_t i {0}; i < top; ++i) {
        values[i] = other_stack.values[i];
    }

    return *this;
}

Stack::Stack(std::size_t user_size) : top(0), size(user_size), values(new char[size]) {}

bool Stack::is_full() const {
    return top == size;
}

bool Stack::is_empty() const {
    return top == 0;
}

char Stack::peek() const {
    if (is_empty()) {
        std::cerr << "Error! Stack is already empty!\n";
        return {};
    }

    return values[top - 1];
}

void Stack::pop() {
    if (is_empty()) {
        std::cerr << "Error! Stack is already empty!\n";
        return;
    }

    --top;
}

void Stack::push(char user_value) {
    if (is_full()) {
        std::cerr << "Error! Stack is already full!\n";
        return;
    }

    values[top++] = user_value;
}
