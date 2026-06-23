#pragma once

#include <fstream>
#include <string>

class BinaryTree {
public:
    enum DisplayOrder {
        INORDER,
        PREORDER,
        POSTORDER
    };
    ~BinaryTree();
    BinaryTree(const BinaryTree& other_tree);
    BinaryTree& operator=(const BinaryTree& other_tree);
    explicit BinaryTree();
    void insert(const std::string& data);
    void remove(const std::string& data);
    void display(DisplayOrder display_order) const;
    void export_to_graphviz() const;
private:
    struct Node {
        int count;
        std::string data;
        Node* left;
        Node* right;
        Node(std::string d) : count(1), data(d), left(nullptr), right(nullptr) {};
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
    };
    Node* root;
    Node* recursive_copy(Node* start_node) const;
    Node* recursive_insert(Node* current_node, const std::string& data);
    Node* recursive_remove(Node* current_node, const std::string& data);
    void recursive_destroy(Node* start_node);
    void recursive_display_inorder(Node* current_node) const;
    void recursive_display_preorder(Node* current_node) const;
    void recursive_display_postorder(Node* current_node) const;
    void recursive_save_graphviz_dot(Node* current_node, std::ofstream& out) const;
};
