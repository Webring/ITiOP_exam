#include <iostream>
#include "string.h"
#include "fstream"

#define INPUT_FILE_PATH "../task_13/words.txt"
#define OUTPUT_FILE_PATH "../task_13/words_result.txt"

using namespace std;

struct TreeElement {
    char *word = new char;
    TreeElement *left = NULL;
    TreeElement *right = NULL;
};

TreeElement *add_word_to_tree(TreeElement *tree_element, char *word) {
    if (tree_element == NULL) {
        tree_element = new TreeElement;
        strcpy(tree_element->word, word);
    }
    int compare_result = strcmp(word, tree_element->word);
    if (compare_result < 0)
        tree_element->left = add_word_to_tree(tree_element->left, word);
    else if (compare_result > 0)
        tree_element->right = add_word_to_tree(tree_element->right, word);
    return tree_element;
}

void preorder(TreeElement *tree_element, ofstream &stream) {
    if (tree_element == nullptr) return;
    stream << tree_element->word << endl;
    preorder(tree_element->left, stream);
    preorder(tree_element->right, stream);
}

void inorder(TreeElement *tree_element, ofstream &stream) {
    if (tree_element == nullptr) return;
    inorder(tree_element->left, stream);
    stream << tree_element->word << endl;
    inorder(tree_element->right, stream);
}

void postorder(TreeElement *tree_element, ofstream &stream) {
    if (tree_element == nullptr) return;
    postorder(tree_element->left, stream);
    postorder(tree_element->right, stream);
    stream << tree_element->word << endl;
}

int main() {
    ifstream input_file(INPUT_FILE_PATH);
    ofstream output_file(OUTPUT_FILE_PATH);

    if (not input_file.is_open()) {
        cout << "File not found" << endl;
        return 0;
    }

    char word[100];
    TreeElement *root = NULL;
    while (not input_file.eof()) {
        input_file >> word;
        root = add_word_to_tree(root, word);
    }

    inorder(root, output_file); //»спользу€ концевой обход выводим в алфавитном пор€дке

    return 0;
}