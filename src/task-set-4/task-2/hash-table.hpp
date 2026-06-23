#pragma once

#include <cstddef>
#include <string>

class HashTable {
public:
    enum class HashType {
        ETH,
        GNU_CPP,
        GNU_CC1
    };
    ~HashTable();
    HashTable(const HashTable& other_table);
    HashTable& operator=(const HashTable& other_table);
    explicit HashTable(std::size_t user_size);
    void insert(HashType type, const std::string& key, const std::string& value);
    int get_fullness() const;
    std::size_t hash_function(HashType type, const std::string& key) const;
private:
    struct Metadata {
        std::string key;
        std::string value;
        Metadata* next;
        Metadata(const Metadata& other_metadata) = delete;
        Metadata& operator=(const Metadata& other_metadata) = delete;
        Metadata(const std::string& k, const std::string& v) : key(k), value(v) {}
    };
    Metadata** table;
    std::size_t capacity;
};
