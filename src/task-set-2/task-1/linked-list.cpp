#include "linked-list.hpp"

#include <iostream>

LinkedList::~LinkedList() {
    Node* current_node {head};

    while (current_node) {
        Node* next_node {current_node->next};
        delete current_node;
        current_node = next_node;
    }
}

LinkedList::LinkedList(const LinkedList& other_list) : head(nullptr), tail(nullptr) {
    Node* last_node {};
    Node* other_current_node {other_list.head};

    while (other_current_node) {
        Node* new_node {new Node(other_current_node->value)};

        if (!head) {
            head = new_node;
        } else {
            last_node->next = new_node;
        }

        last_node = new_node;
        other_current_node = other_current_node->next;
    }

    tail = last_node;
}

LinkedList& LinkedList::operator=(const LinkedList& other_list) {
    if (this == &other_list) {
        return *this;
    }

    Node* current_node {head};

    while (current_node) {
        Node* next_node {current_node->next};
        delete current_node;
        current_node = next_node;
    }

    head = tail = nullptr;

    Node* last_node {};
    Node* other_current_node {other_list.head};

    while (other_current_node) {
        Node* new_node {new Node(other_current_node->value)};

        if (!head) {
            head = new_node;
        } else {
            last_node->next = new_node;
        }

        last_node = new_node;
        other_current_node = other_current_node->next;
    }

    tail = last_node;

    return *this;
}

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {}

bool LinkedList::is_empty() const {
    return head == nullptr;
}

double LinkedList::average() const {
    if (is_empty()) {
        std::cerr << "Error! Linked list is empty!\n";
        return {};
    }

    int count {};
    double sum {};

    const Node* temp_node {head};

    while (temp_node) {
        sum += temp_node->value;
        ++count;
        temp_node = temp_node->next;
    }

    return sum / count;
}

void LinkedList::display() const {
    if (is_empty()) {
        std::cout << "Linked list is empty.\n";
        return;
    }

    const Node* temp_node {head};

    while (temp_node) {
        std::cout << temp_node->value << ' ';
        temp_node = temp_node->next;
    }
    std::cout << '\n';
}

void LinkedList::append(int user_value) {
    Node* new_node {new Node(user_value)};

    if (is_empty()) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}
