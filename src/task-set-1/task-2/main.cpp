#include "stack.hpp"

#include <cstddef>
#include <iostream>
#include <limits>
#include <string>

int main() {
    constexpr std::size_t STACK_SIZE {64};

    std::string user_input {};
    bool is_input_correct {false};

    do {
        std::cout << "Enter a word: ";
        if (std::cin >> user_input && std::cin.peek() == '\n') {
            if (user_input.empty()) {
                std::cerr << "Error! Input cannot be an empty string!\n";
            } else {
                if (user_input.size() > STACK_SIZE) {
                    std::cerr << "Error! Input cannot be longer than " << STACK_SIZE << '\n';
                } else {
                    is_input_correct = true;
                }
            }
        } else {
            std::cerr << "Error! Please enter valid value.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!is_input_correct);

    Stack stack(STACK_SIZE);

    for (char current_char : user_input) {
        stack.push(current_char);
    }

    std::cout << "Reversed word: ";
    while (!stack.is_empty()) {
        std::cout << stack.peek();
        stack.pop();
    }
    std::cout << '\n';

    return 0;
}
