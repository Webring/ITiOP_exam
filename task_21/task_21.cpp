#include <iostream>
#include "string.h"
#include "fstream"

#define INPUT_FILE_PATH "../task_21/table.txt"

using namespace std;

struct TreeElement {
    float value;
    char *name = new char;
    TreeElement *left = NULL;
    TreeElement *right = NULL;
};

TreeElement *add_element_to_tree(TreeElement *tree_element, char *name, float value) {
    if (tree_element == NULL) {
        tree_element = new TreeElement;
        tree_element->value = value;
        strcpy(tree_element->name, name);
    }
    if (value < tree_element->value)
        tree_element->left = add_element_to_tree(tree_element->left, name, value);
    else if (value > tree_element->value)
        tree_element->right = add_element_to_tree(tree_element->right, name, value);
    return tree_element;
}


float preorder_search_max(TreeElement *root, float max_value = -1) {
    if (root == NULL) return max_value;

    max_value = max(max_value, root->value);

    return max(preorder_search_max(root->left, max_value), preorder_search_max(root->right, max_value));
}

void inorder(TreeElement *tree_element) {
    if (tree_element == nullptr) return;
    inorder(tree_element->left);
    cout << tree_element->value << " ";
    inorder(tree_element->right);
}

TreeElement *cut_max_root(TreeElement *tree_element, float needed_value, TreeElement *parent = nullptr) {
    if (tree_element == nullptr) return nullptr;

    if (tree_element->value == needed_value) {

        if (parent == nullptr) {
            return tree_element;
        }

        if (parent->left == tree_element) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }

        return tree_element;
    }

    TreeElement *left_tree = cut_max_root(tree_element->left, needed_value, tree_element);
    if (left_tree != nullptr) return left_tree;
    return cut_max_root(tree_element->right, needed_value, tree_element);
}

TreeElement *add_elements_from_tree_to_tree(TreeElement *to_tree, TreeElement *from_tree) {
    if (from_tree == nullptr) return to_tree;

    to_tree = add_element_to_tree(to_tree, from_tree->name, from_tree->value);

    to_tree = add_elements_from_tree_to_tree(to_tree, from_tree->left);
    return add_elements_from_tree_to_tree(to_tree, from_tree->right);
}

int main() {
    ifstream input_file(INPUT_FILE_PATH);

    if (not input_file.is_open()) {
        cout << "File not found" << endl;
        return 0;
    }

    float value;
    char name[100];
    TreeElement *root = NULL;
    while (not input_file.eof()) {
        input_file >> name >> value;
        root = add_element_to_tree(root, name, value);
    }

    cout << "Inorder:" << endl;
    inorder(root);
    cout << endl;

    float max_value = preorder_search_max(root);
    TreeElement *tree_with_max_value = cut_max_root(root, max_value);
    root = add_elements_from_tree_to_tree(root, tree_with_max_value->left);
    root = add_elements_from_tree_to_tree(root, tree_with_max_value->right);

    cout << "Inorder after:" << endl;
    inorder(root);

    return 0;
}