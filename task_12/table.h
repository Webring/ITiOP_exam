#include <iostream>
#include "string.h"
#include "fstream"

#define CODE_LENGTH 11
#define NAME_LENGTH 26

using namespace std;

struct Table {
    struct Row {
        char code[CODE_LENGTH];
        char name[NAME_LENGTH];
        float average_score;
    };

    int max_number_of_rows = 0;
    int number_of_rows = 0;
    Row *rows;

    void init(int n);

    Table(int n) {
        init(n);
    }

    bool is_full();

    void set(int index, char code[CODE_LENGTH], char name[NAME_LENGTH], float average_score);

    void add_row_to_back(char code[CODE_LENGTH], char name[NAME_LENGTH], float average_score);

    int bin_search(char code[CODE_LENGTH], bool *flag = NULL);

    void add_row(char code[CODE_LENGTH], char name[NAME_LENGTH], float average_score);

    void import_from_file(ifstream &file);

    void print();

};
