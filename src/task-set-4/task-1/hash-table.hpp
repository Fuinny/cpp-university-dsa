#pragma once

#include <cstddef>
#include <string>

class HashTable {
public:
    ~HashTable();
    HashTable(const HashTable& other_table);
    HashTable& operator=(const HashTable& other_table);
    explicit HashTable(std::size_t user_size);
    void display() const;
    void remove(const std::string& key);
    void insert(const std::string& key, const std::string& value);
    std::string get(const std::string& key) const;
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
    std::size_t hash_function(const std::string& key) const;
};
