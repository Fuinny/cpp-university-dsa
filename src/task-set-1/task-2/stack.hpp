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
    char peek() const;
    void pop();
    void push(char user_value);
private:
    std::size_t top;
    std::size_t size;
    char* values;
};
