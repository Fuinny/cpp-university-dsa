#include "hash-table.hpp"

#include <fstream>
#include <iostream>
#include <string>

int main() {
    HashTable::HashType type;
    int selected_hash {};

    std::cout << "Select hash algorithm:\n"
            "1. ETH\n"
            "2. GNU-CPP\n"
            "3. GNU-CC1\n";
    std::cout << "\nEnter your choice: ";
    std::cin >> selected_hash;

    switch (selected_hash) {
    case 1:
        type = HashTable::HashType::ETH;
        break;
    case 2:
        type = HashTable::HashType::GNU_CPP;
        break;
    case 3:
        type = HashTable::HashType::GNU_CC1;
        break;
    }

    HashTable hash_table(100);

    std::ifstream file("users.txt");
    std::string user, pass;

    while (file >> user >> pass) {
        hash_table.insert(type, user, pass);
    }

    file.close();

    std::cout << "From 100 buckets in hash table " << hash_table.get_fullness() << " are empty.\n";

    return 0;
}
