#include "linked-list.hpp"

#include <iostream>
#include <string>

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
        Node* new_node {
            new Node(other_current_node->name,
                other_current_node->surname,
                other_current_node->value)
        };

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
        Node* new_node {
            new Node(other_current_node->name,
                other_current_node->surname,
                other_current_node->value)
        };

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
        std::cout << temp_node->name << ' ' << temp_node->surname << ' ' << temp_node->value << '\n';
        temp_node = temp_node->next;
    }
    std::cout << '\n';
}

void LinkedList::append(const std::string& user_name, const std::string& user_surname, int user_value) {
    Node* new_node {new Node(user_name, user_surname, user_value)};

    if (is_empty()) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

void LinkedList::remove(const std::string& user_name, const std::string& user_surname) {
    if (is_empty()) {
        std::cerr << "Error! Linked list is empty!\n";
        return;
    } else if (head->name == user_name && head->surname == user_surname) {
        Node* temp_node {head};
        head = head->next;
        delete temp_node;
        if (!head) {
            tail = nullptr;
        }
    } else {
        Node* prev_node {head};
        Node* temp_node {head->next};

        while (temp_node) {
            if (temp_node->name == user_name && temp_node->surname == user_surname) {
                prev_node->next = temp_node->next;
                if (temp_node == tail) {
                    tail = prev_node;
                }
                delete temp_node;
                return;
            } else {
                prev_node = temp_node;
                temp_node = temp_node->next;
            }
        }

        std::cerr << "Error! No such student in the list!\n";
    }
}

void LinkedList::sort(LinkedList::SortField sort_field, LinkedList::SortOrder sort_order) {
    if (is_empty() || !head->next) {
        return;
    }

    bool swapped {false};

    do {
        swapped = false;

        Node* prev_node {nullptr};
        Node* current_node {head};

        while (current_node && current_node->next) {
            Node* next_node {current_node->next};

            bool should_swap {false};

            switch (sort_field) {
                case SortField::Name:
                    should_swap = (sort_order == SortOrder::ASC)
                        ? current_node->name > current_node->next->name
                        : current_node->name < current_node->next->name;
                    break;
                case SortField::Surname:
                    should_swap = (sort_order == SortOrder::ASC)
                        ? current_node->surname > current_node->next->surname
                        : current_node->surname < current_node->next->surname;
                    break;
                case SortField::Value:
                    should_swap = (sort_order == SortOrder::ASC)
                        ? current_node->value > current_node->next->value
                        : current_node->value < current_node->next->value;
                    break;
            }

            if (should_swap) {
                current_node->next = next_node->next;
                next_node->next = current_node;

                if (prev_node) {
                    prev_node->next = next_node;
                } else {
                    head = next_node;
                }

                prev_node = next_node;
                swapped = true;
            } else {
                prev_node = current_node;
                current_node = current_node->next;
            }
        }
    } while (swapped);

    tail = head;

    while (tail->next) {
        tail = tail->next;
    }
}
