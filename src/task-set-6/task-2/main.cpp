#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void print_tape(const std::vector<char>& tape, std::size_t head) {
    for (std::size_t i {0}; i < tape.size(); ++i) {
        if (i == head) {
            std::cout << '[' << tape[i] << ']';
        } else {
            std::cout << tape[i];
        }
    }
    std::cout << '\n';
}

int main() {
    std::string filename;
    std::cout << "Enter the filename (with file extension): ";
    std::cin >> filename;

    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error! Cannot open file " << filename << '\n';
    }

    std::string line;
    getline(file, line);
    file.close();

    std::vector<char> tape {};

    int separator_count {};
    for (char c : line) {
        if (c == '1' || c == '0' || c == '_') {
            tape.push_back(c);
            if (c == '0') {
                ++separator_count;
            }
        } else {
            std::cerr << "Error! Invalid characters in tape: " << c << '\n';
            return 1;
        }
    }

    if (separator_count != 1) {
        std::cerr << "Error! Tape must contain exactly one separator!\n";
        return 1;
    }

    if (tape.back() != '_') {
        tape.push_back('_');
    }

    std::size_t needle {0};

    std::cout << "Loaded tape: ";
    print_tape(tape, needle);
    std::cout << '\n';

    while (true) {
        while (tape[needle] == '1') {
            print_tape(tape, needle);
            ++needle;
        }

        if (tape[needle + 1] == '_') {
            break;
        }

        tape[needle] = '1';
        print_tape(tape, needle);

        ++needle;

        while (tape[needle] == '1') {
            print_tape(tape, needle);

            if (tape[needle + 1] == '_') {
                tape[needle] = '_';
                print_tape(tape, needle);
                break;
            }

            ++needle;
        }

        needle = 0;
    }

    int result = 0;

    for (char c : tape) {
        if (c == '1') {
            result++;
        }
    }

    std::cout << "\nFinal tape:\n";
    print_tape(tape, needle);
    std::cout << "\nResult (sum) = " << result << '\n';

    return 0;
}
