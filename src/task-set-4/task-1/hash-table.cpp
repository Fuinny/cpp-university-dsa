#include "hash-table.hpp"

#include <cstddef>
#include <iostream>
#include <string>

HashTable::~HashTable() {
    for (std::size_t i {0}; i < capacity; ++i) {
        Metadata* current_metadata {table[i]};

        while (current_metadata) {
            Metadata* temp_metadata {current_metadata};
            current_metadata = current_metadata->next;
            delete temp_metadata;
        }
    }

    delete[] table;
}

HashTable::HashTable(const HashTable& other_table) : table(new Metadata*[other_table.capacity]), capacity(other_table.capacity) {
    for (std::size_t i {0}; i < other_table.capacity; ++i) {
        Metadata* other_current_metadata {other_table.table[i]};
        Metadata* tail {nullptr};

        while (other_current_metadata) {
            Metadata* new_metadata {new Metadata(other_current_metadata->key, other_current_metadata->value)};

            if (!table[i]) {
                table[i] = new_metadata;
                tail = new_metadata;
            } else {
                tail->next = new_metadata;
                tail = new_metadata;
            }

            other_current_metadata = other_current_metadata->next;
        }
    }
}

HashTable& HashTable::operator=(const HashTable& other_table) {
    if (this == &other_table) {
        return *this;
    }

    for (std::size_t i {0}; i < capacity; ++i) {
        Metadata* current_metadata {table[i]};

        while (current_metadata) {
            Metadata* temp_metadata {current_metadata};
            current_metadata = current_metadata->next;
            delete temp_metadata;
        }
    }

    delete[] table;

    capacity = other_table.capacity;
    table = new Metadata*[capacity];

    for (std::size_t i {0}; i < capacity; ++i) {
        Metadata* other_current_metadata {other_table.table[i]};
        Metadata* tail {nullptr};

        while (other_current_metadata) {
            Metadata* new_metadata {new Metadata(other_current_metadata->key, other_current_metadata->value)};

            if (!table[i]) {
                table[i] = new_metadata;
                tail = new_metadata;
            } else {
                tail->next = new_metadata;
                tail = new_metadata;
            }

            other_current_metadata = other_current_metadata->next;
        }
    }

    return *this;
}

HashTable::HashTable(std::size_t user_size) : table(new Metadata*[user_size]), capacity(user_size) {
    for (std::size_t i {0}; i < capacity; ++i) {
        table[i] = nullptr;
    }
}

void HashTable::display() const {
    std::cout << '\n';

    for (std::size_t i {0}; i < capacity; ++i) {
        Metadata* current_metadata {table[i]};

        while (current_metadata) {
            std::cout << current_metadata->key << '\n';
            current_metadata = current_metadata->next;
        }
    }

    std::cout << '\n';
}

void HashTable::remove(const std::string& key) {
    std::size_t index {hash_function(key)};
    Metadata* current_metadata {table[index]};
    Metadata* prev_metadata {nullptr};

    while (current_metadata) {
        if (current_metadata->key == key) {
            if (prev_metadata) {
                prev_metadata->next = current_metadata->next;
            } else {
                table[index] = current_metadata->next;
            }
            delete current_metadata;
            std::cout << "\nDone! User \"" << key << "\" was successfully deleted!\n\n";
            return;
        }
        prev_metadata = current_metadata;
        current_metadata = current_metadata->next;
    }

    std::cerr << "Warning! Key " << key << " not found, nothing deleted.\n";
}

void HashTable::insert(const std::string& key, const std::string& value) {
    std::size_t index {hash_function(key)};
    Metadata* current_metadata {table[index]};

    while (current_metadata) {
        if (current_metadata->key == key) {
            current_metadata->value = value;
            return;
        } else {
            current_metadata = current_metadata->next;
        }
    }

    Metadata* new_metadata {new Metadata(key, value)};
    new_metadata->next = table[index];
    table[index] = new_metadata;
}

std::string HashTable::get(const std::string& key) const {
    std::size_t index {hash_function(key)};
    Metadata* current_metadata {table[index]};

    while (current_metadata) {
        if (current_metadata->key == key) {
            return current_metadata->value;
        } else {
            current_metadata = current_metadata->next;
        }
    }

    return {};
}

std::size_t HashTable::hash_function(const std::string& key) const {
    std::size_t h {0};

    for (char currrent_char : key) {
        h = (h << 2) + static_cast<unsigned char>(currrent_char);
    }

    return h %  capacity;
}
