#include "stack.hpp"

#include <cstddef>
#include <iostream>
#include <limits>

int main() {
    constexpr std::size_t STACK_SIZE {32}; // 32-bit binary representation.

    int user_number {};
    bool is_input_correct {false};

    do {
        std::cout << "Enter a number: ";
        if (std::cin >> user_number && std::cin.peek() == '\n') {
            if (user_number < 0) {
                std::cerr << "Error! Only non-negative numbers are allowed!\n";
            } else {
                is_input_correct = true;
            }
        } else {
            std::cerr << "Error! Please enter valid value.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!is_input_correct);

    if (user_number == 0) {
        std::cout << "Binary: 0\n";
        return 0;
    }

    Stack stack(STACK_SIZE);

    while (user_number > 0) {
        if (stack.is_full()) {
            std::cerr << "Warning! Binary value truncated to " << STACK_SIZE << " least-significant bits.\n";
            break;
        }
        stack.push(user_number % 2);
        user_number /= 2;
    }

    std::cout << "Binary: ";
    while (!stack.is_empty()) {
        std::cout << stack.peek();
        stack.pop();
    }
    std::cout << '\n';

    return 0;
}
