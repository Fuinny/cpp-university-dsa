#pragma once

class LinkedList {
public:
    ~LinkedList();
    LinkedList(const LinkedList& other_list);
    LinkedList& operator=(const LinkedList& other_list);
    explicit LinkedList();
    bool is_empty() const;
    double average() const;
    void display() const;
    void append(int user_value);
private:
    struct Node {
        int value;
        Node* next;
        Node(int v) : value(v), next(nullptr) {}
        Node(const Node& other_node) = delete;
        Node& operator=(const Node& other_node) = delete;
    };
    Node* head;
    Node* tail;
};
