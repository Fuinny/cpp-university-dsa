#include "hash-table.hpp"

#include <fstream>
#include <iostream>
#include <limits>
#include <string>

int main() {
    std::ifstream file("users.txt");

    if (!file) {
        std::cerr << "Error! Could not open users.txt file!\n";
        return 1;
    }

    HashTable hash_table(100);
    std::string username {}, password {};

    while (file >> username >> password) {
        hash_table.insert(username, password);
    }

    int user_choice {};
    bool is_exit_requested {false};

    do {
        std::cout << "1. Display all elements\n"
            "2. Insert new element\n"
            "3. Remove element\n"
            "4. Login\n"
            "5. Exit\n";
        std::cout << "\nEnter your choice: ";
        std::cin >> user_choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (user_choice) {
            case 1:
                hash_table.display();
                break;
            case 2: {
                std::string input_user {}, input_password {};

                std::cout << "\nEnter username: ";
                std::cin >> input_user;
                std::cout << "Enter password: ";
                std::cin >> input_password;

                hash_table.insert(input_user, input_password);

                std::cout << "\nDone! User has been successfully added!\n\n";
                break;
            }
            case 3: {
                std::string input_user {};

                std::cout << "\nEnter username: ";
                std::cin >> input_user;

                hash_table.remove(input_user);
                break;
            }
            case 4: {
                std::string input_user {}, input_password {};

                std::cout << "\nEnter username: ";
                std::cin >> input_user;
                std::cout << "Enter password: ";
                std::cin >> input_password;

                std::string stored_password {hash_table.get(input_user)};

                if (stored_password.empty()) {
                    std::cout << "\nUsername not found!\n\n";
                } else if (stored_password == input_password) {
                    std::cout << "\nLogin successfull!\n\n";
                } else {
                    std::cout << "\nIncorrect password!\n\n";
                }
                break;
            }
            case 5:
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
