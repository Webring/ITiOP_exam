#include "table.h"

void Table::init(int n) {
    number_of_rows = 0;
    max_number_of_rows = n;
    rows = new Row[n];
}

bool Table::is_full() {
    return number_of_rows == max_number_of_rows;
}

void Table::set(int index, char code[CODE_LENGTH], char name[NAME_LENGTH], float average_score) {
    if (index < 0 and index >= max_number_of_rows) throw out_of_range("Not correct index");

    Row new_row;
    strcpy(new_row.code, code);
    strcpy(new_row.name, name);
    new_row.average_score = average_score;

    rows[index] = new_row;
}

void Table::add_row_to_back(char code[CODE_LENGTH], char name[NAME_LENGTH], float average_score) {
    if (is_full()) throw out_of_range("Table is full");

    set(number_of_rows, code, name, average_score);

    number_of_rows++;
}

int Table::bin_search(char code[CODE_LENGTH], bool *flag) {
    int left = 0;
    int mid;
    int right = number_of_rows - 1;

    while (left <= right) {
        mid = (left + right) / 2;

        if (strcmp(rows[mid].code, code) == 0) {
            if (flag != NULL) *flag = true;
            return mid;
        }

        if (strcmp(rows[mid].code, code) < 0) { // ||
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (flag != NULL) *flag = false;
    return mid;
}

void Table::add_row(char code[CODE_LENGTH], char name[NAME_LENGTH], float average_score) {
    bool succes_flag = false;

    if (number_of_rows == 0) {
        add_row_to_back(code, name, average_score);
        return;
    }

    int index = bin_search(code, &succes_flag);

    cout << index << endl;

    if (is_full()) throw out_of_range("Table is full");

    int modificator = ((index == 0 or index == number_of_rows - 1) and strcmp(rows[index].code, code) > 0);

    for (int i = number_of_rows; i > index + modificator; i--) {
        rows[i] = rows[i - 1];
    }

    number_of_rows++;

    set(index + modificator, code, name, average_score);
}

/*
//�� �����������
int Table::bin_search(char code[CODE_LENGTH], bool *flag) {
    int left = 0;
    int mid;
    int right = number_of_rows - 1;

    while (left <= right) {
        mid = (left + right) / 2;

        if (strcmp(rows[mid].code, code) == 0) {
            if (flag != NULL) *flag = true;
            return mid;
        }

        if (strcmp(rows[mid].code, code) > 0) { // ||
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (flag != NULL) *flag = false;
    return mid;
}

void Table::add_row(char code[CODE_LENGTH], char name[NAME_LENGTH], float average_score) {
    bool succes_flag = false;

    if (number_of_rows == 0) {
        add_row_to_back(code, name, average_score);
        return;
    }

    int index = bin_search(code, &succes_flag);

    if (is_full()) throw out_of_range("Table is full");

    if (index == number_of_rows - 1 and strcmp(rows[index].code, code) < 0) { // ||
        add_row_to_back(code, name, average_score);
    } else {
        for (int i = number_of_rows; i > index; i--) {
            rows[i] = rows[i - 1];
        }

        number_of_rows++;

        set(index, code, name, average_score);
    }

}*/

void Table::import_from_file(ifstream &file) {
    if (not file.is_open()) throw invalid_argument("File not opened");

    char code[CODE_LENGTH];
    char name[NAME_LENGTH];
    float average_score;

    while (not file.eof()) {
        file >> code >> name >> average_score;
        add_row(code, name, average_score);
    }
}

void Table::print() {
    cout << "ID\t\t\tName\t\tScore" << endl;
    for (int row_id = 0; row_id < number_of_rows; row_id++) {
        for (int i = 0; i < strlen(rows[row_id].code); i++) {
            cout << rows[row_id].code[i];
        }
        cout << "\t\t";
        for (int i = 0; i < strlen(rows[row_id].name); i++) {
            cout << rows[row_id].name[i];
        }
        cout << "\t\t" << rows[row_id].average_score << endl;
    }
}