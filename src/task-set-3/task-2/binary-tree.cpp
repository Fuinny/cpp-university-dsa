#include "binary-tree.hpp"

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

BinaryTree::~BinaryTree() {
    recursive_destroy(root);
}

BinaryTree::BinaryTree(const BinaryTree& other_tree) {
    root = recursive_copy(other_tree.root);
}

BinaryTree& BinaryTree::operator=(const BinaryTree& other_tree) {
    if (this == &other_tree) {
        return *this;
    }

    recursive_destroy(root);
    root = recursive_copy(other_tree.root);

    return *this;
}

BinaryTree::BinaryTree() : root(nullptr) {};

void BinaryTree::insert(const std::string& data) {
    root = recursive_insert(root, data);
}

void BinaryTree::remove(const std::string& data) {
    root = recursive_remove(root, data);
}

void BinaryTree::display(DisplayOrder display_order) const {
    std::cout << '\n';

    switch (display_order) {
        case DisplayOrder::INORDER:
            recursive_display_inorder(root);
            break;
        case DisplayOrder::PREORDER:
            recursive_display_preorder(root);
            break;
        case DisplayOrder::POSTORDER:
            recursive_display_postorder(root);
            break;
    }

    std::cout << "\n\n";
}

void BinaryTree::export_to_graphviz() const {
    std::ofstream out("binary-tree.dot");
    out << "digraph BinaryTree {\n";
    recursive_save_graphviz_dot(root, out);
    out << "}\n";

    std::cout << "\nDone!\n";
    std::cout << "You can view the binary tree here: https://dreampuf.github.io/GraphvizOnline/\n\n";
}

void BinaryTree::display_statistics() const {
    int nodes {recursive_count_nodes(root)};
    int leaves {recursive_count_leaves(root)};
    int layers {recursive_count_layers(root)};
    int max_nodes {static_cast<int>(std::pow(2, layers)) - 1};
    double fullness {max_nodes > 0 ? 100.0 * nodes / max_nodes : 0.0};

    std::cout << '\n';
    std::cout << "Nodes: " << nodes << '\n';
    std::cout << "Leaves: " << leaves << '\n';
    std::cout << "Layers: " << layers << '\n';
    std::cout << "Maximum nodes in a perfect tree: " << max_nodes << '\n';
    std::cout << "Fullness: " << std::fixed << std::setprecision(2) << fullness << "%\n\n";
}

BinaryTree::Node* BinaryTree::recursive_copy(Node* start_node) const {
    if (!start_node) {
        return nullptr;
    }

    Node* new_node {new Node(start_node->data)};
    new_node->left = recursive_copy(start_node->left);
    new_node->right = recursive_copy(start_node->right);

    return new_node;
}

BinaryTree::Node* BinaryTree::recursive_insert(Node* current_node, const std::string& data) {
    if (!current_node) {
        return new Node(data);
    } else if (data == current_node->data) {
        current_node->count++;
    } else if (data < current_node->data) {
        current_node->left = recursive_insert(current_node->left, data);
    } else {
        current_node->right = recursive_insert(current_node->right, data);
    }

    return current_node;
}

BinaryTree::Node* BinaryTree::recursive_remove(Node* current_node, const std::string& data) {
    if (!current_node) {
        return nullptr;
    } else if (data < current_node->data) {
        current_node->left = recursive_remove(current_node->left, data);
    } else if (data > current_node->data) {
        current_node->right = recursive_remove(current_node->right, data);
    } else {
        if (!current_node->left) {
            Node* successor = current_node->right;
            delete current_node;
            return successor;
        } else if (!current_node->right) {
            Node* successor = current_node->left;
            delete current_node;
            return successor;
        } else {
            Node* successor = current_node->right;
            while (successor && successor->left) {
                successor = successor->left;
            }
            current_node->data = successor->data;
            current_node->right = recursive_remove(current_node->right, successor->data);
        }
    }

    return current_node;
}

void BinaryTree::recursive_destroy(Node* start_node) {
    if (!start_node) {
        return;
    }

    recursive_destroy(start_node->left);
    recursive_destroy(start_node->right);
    delete start_node;
}

void BinaryTree::recursive_display_inorder(Node* current_node) const {
    if (!current_node) {
        return;
    }

    recursive_display_inorder(current_node->left);
    std::cout << current_node->data << " (" << current_node->count << ") ";
    recursive_display_inorder(current_node->right);
}

void BinaryTree::recursive_display_preorder(Node* current_node) const {
    if (!current_node) {
        return;
    }

    std::cout << current_node->data << " (" << current_node->count << ") ";
    recursive_display_preorder(current_node->left);
    recursive_display_preorder(current_node->right);
}

void BinaryTree::recursive_display_postorder(Node* current_node) const {
    if (!current_node) {
        return;
    }

    recursive_display_postorder(current_node->left);
    recursive_display_postorder(current_node->right);
    std::cout << current_node->data << " (" << current_node->count << ") ";
}

void BinaryTree::recursive_save_graphviz_dot(Node* current_node, std::ofstream& out) const {
    if (!current_node) {
        return;
    }

    if (current_node->left) {
        out << "\"" << current_node->data << " (" << current_node->count << ")"
            << "\" -> \""
            << current_node->left->data << " (" << current_node->left->count << ")"
            << "\";\n";
    }

    if (current_node->right) {
        out << "\"" << current_node->data << " (" << current_node->count << ")"
            << "\" -> \""
            << current_node->right->data << " (" << current_node->right->count << ")"
            << "\";\n";
    }

    recursive_save_graphviz_dot(current_node->left, out);
    recursive_save_graphviz_dot(current_node->right, out);
}

int BinaryTree::recursive_count_nodes(Node* start_node) const {
    if (!start_node) {
        return 0;
    }

    return 1 + recursive_count_nodes(start_node->left) + recursive_count_nodes(start_node->right);
}

int BinaryTree::recursive_count_leaves(Node* start_node) const {
    if (!start_node) {
        return 0;
    } else if (!start_node->left && !start_node->right) {
        return 1;
    }

    return recursive_count_leaves(start_node->left) + recursive_count_leaves(start_node->right);
}

int BinaryTree::recursive_count_layers(Node* start_node) const {
    if (!start_node) {
        return 0;
    }

    return 1 + std::max(recursive_count_layers(start_node->left), recursive_count_layers(start_node->right));
}
