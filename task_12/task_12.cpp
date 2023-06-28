/*
 * Task 12:
 * � ����� ���������� �������� ������������� �� �������� ����� ������� ���������� ����:
 * ���� �������� (10 ��������), ��� �������� (25 ��������), ������� ���� (������������).
 * ���� �������� � ���� ��������. ���� ������� ���������� ���������� �� �������.
 * ���������� ��������� �� ��������� 100. ��������� �������� �����, �������� � ������� ��� ���� �������.
 */

#include <iostream>
#include "fstream"
#include "table.h"

#define INPUT_FILE_PATH "../task_12/table.txt" // ��� �������� �����

using namespace std; //���������� ������������ ����

bool file_is_empty(ifstream &file) {
    return file.peek() == ifstream::traits_type::eof(); // ���� ��������� ��������� ��� ������ ������ ����� ������� ����� �����
}

int main() {
    ifstream input_file(INPUT_FILE_PATH); // ��������� ���� ��� ������

    if (not input_file.is_open()) { // ���� ���� �� ������
        cout << "Can't open input file" << endl; //������� ��������� �� ������
        return 0; // ��������� ������ ���������
    }

    if (file_is_empty(input_file)) { // ��������� ���� �� �������
        cout << "file is empty" << endl; //������� ��������� �� ������
        return 0; // ��������� ������ ���������
    }

    Table students_table(100);
    students_table.import_from_file(input_file);
    students_table.print();

    cout << "Time to insert new element: " << endl; //STUDENT003 Bykov 99.9
    char code[CODE_LENGTH];
    char name[NAME_LENGTH];
    float average_score;
    cin >> code >> name >> average_score;
    students_table.add_row(code, name, average_score);
    students_table.print();


    return 0;
}