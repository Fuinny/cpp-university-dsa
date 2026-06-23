#include "binary-tree.hpp"

#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>

void normalize_string(std::string& input_string) {
    std::size_t size {};

    for (char current_char : input_string) {
        if (std::isalpha(static_cast<unsigned char>(current_char))) {
            input_string[size++] = static_cast<char>(std::tolower(static_cast<unsigned char>(current_char)));
        }
    }

    input_string.resize(size);
}

int main () {
    std::ifstream file("text.txt");

    if (!file) {
        std::cerr << "Error! Could not open text.txt file!\n";
        return 1;
    }

    BinaryTree word_tree;
    std::string current_word {};

    while (file >> current_word) {
        normalize_string(current_word);
        word_tree.insert(current_word);
    }

    file.close();

    int user_choice {};
    std::string user_input {};
    bool is_exit_requested {false};

    do {
        std::cout << "1. Insert element\n"
                << "2. Remove element\n"
                << "3. Display data (inorder)\n"
                << "4. Display data (preorder)\n"
                << "5. Display data (postorder)\n"
                << "6. Export BST to Graphviz dot file\n"
                << "7. Display BST statistics\n"
                << "8. Exit\n";
        std::cout << "\nEnter your choice: ";
        std::cin >> user_choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (user_choice) {
        case 1:
            std::cout << "\nEnter new data: ";
            std::cin >> user_input;
            normalize_string(user_input);
            word_tree.insert(user_input);
            std::cout << "\nDone! New data successfully added to BST!\n\n";
            break;
        case 2:
            std::cout << "\nEnter data to remove: ";
            std::cin >> user_input;
            normalize_string(user_input);
            word_tree.remove(user_input);
            std::cout << "\nDone! Data successfully removed from BST!\n\n";
            break;
        case 3:
            word_tree.display(BinaryTree::DisplayOrder::INORDER);
            break;
        case 4:
            word_tree.display(BinaryTree::DisplayOrder::PREORDER);
            break;
        case 5:
            word_tree.display(BinaryTree::DisplayOrder::POSTORDER);
            break;
        case 6:
            word_tree.export_to_graphviz();
            break;
        case 7:
            word_tree.display_statistics();
            break;
        case 8:
            is_exit_requested = true;
            break;
        default:
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    } while (!is_exit_requested);

    return 0;
}
