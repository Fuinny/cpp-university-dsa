#pragma once

#include <cstddef>

class Stack {
public:
    ~Stack();
    Stack(const Stack& other_stack);
    Stack& operator=(const Stack& other_stack);
    explicit Stack(std::size_t user_size);
    bool is_full() const;
    bool is_empty() const;
    int peek() const;
    void pop();
    void push(int user_value);
private:
    std::size_t top;
    std::size_t size;
    int* values;
};
