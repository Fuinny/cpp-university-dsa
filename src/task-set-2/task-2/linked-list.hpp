#pragma once

#include <string>

class LinkedList {
public:
    enum class SortField {
        Name,
        Surname,
        Value
    };
    enum class SortOrder {
        ASC,
        DESC
    };
    ~LinkedList();
    LinkedList(const LinkedList& other_list);
    LinkedList& operator=(const LinkedList& other_list);
    explicit LinkedList();
    bool is_empty() const;
    double average() const;
    void display() const;
    void append(const std::string& user_name, const std::string& user_surname, int user_value);
    void remove(const std::string& user_name, const std::string& user_surname);
    void sort(SortField sort_field, SortOrder sort_order);
private:
    struct Node {
        std::string name;
        std::string surname;
        int value;
        Node* next;
        Node(std::string n, std::string s, int v) : name(n), surname(s), value(v), next(nullptr) {}
        Node(const Node& other_node) = delete;
        Node& operator=(const Node& other_node) = delete;
    };
    Node* head;
    Node* tail;
};
