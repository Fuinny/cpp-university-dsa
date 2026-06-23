#include "hash-table.hpp"

#include <cstddef>
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

void HashTable::insert(HashTable::HashType type, const std::string& key, const std::string& value) {
    std::size_t index {hash_function(type, key)};
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

int HashTable::get_fullness() const {
    int empty_buckets {};

    for (size_t i {0}; i < capacity; ++i) {
        if (table[i] == nullptr) {
            empty_buckets++;
        }
    }

    return empty_buckets;
}

std::size_t HashTable::hash_function(HashTable::HashType type, const std::string& key) const {
    std::size_t h {};

    switch (type) {
    case HashType::ETH:
        h = 1;
        for (char c : key) {
            unsigned char uc = static_cast<unsigned char>(c);
            h = uc * ((h % 257) + 1);
        }
        return h % capacity;

    case HashType::GNU_CPP:
        h = 0;
        for (char c : key) {
            unsigned char uc = static_cast<unsigned char>(c);
            h = 4 * h + uc;
        }
        h = h & 0x7FFFFFFF; // last 31 bits
        return h % capacity;

    case HashType::GNU_CC1:
        h = key.size();
        for (char c : key) {
            unsigned char uc = static_cast<unsigned char>(c);
            h = 613 * h + uc;
        }
        h = h & 0x3FFFFFFF; // last 30 bits
        return h % capacity;
    }

    return 0;
}
