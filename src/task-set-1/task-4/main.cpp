#include <cctype>
#include <cstddef>
#include <iostream>
#include <limits>
#include <stack>
#include <string>

int main() {
    std::string user_input {};
    bool is_input_correct {false};

    do {
        std::cout << "Enter a word: ";
        if (std::cin >> user_input && std::cin.peek() == '\n') {
            if (user_input.empty()) {
                std::cerr << "Error! Input cannot be an empty string!\n";
            } else {
                is_input_correct = true;
            }
        } else {
            std::cerr << "Error! Please enter valid value.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!is_input_correct);

    std::stack<char> stack;

    for (char current_char : user_input) {
        if (std::isalpha(static_cast<unsigned char>(current_char))) {
            stack.push(static_cast<char>(std::tolower(static_cast<unsigned char>(current_char))));
        }
    }

    if (stack.empty()) {
        std::cerr << "Error! Input consists of non-alphabetic characters!\n";
        return 1;
    }

    std::size_t i {0};
    while (!stack.empty()) {
        if (std::tolower(user_input[i]) != stack.top()) {
            std::cout << "Word is not a palindrome.\n";
            return 0;
        }
        ++i;
        stack.pop();
    }

    std::cout << "Word is a palindrome.\n";

    return 0;
}
