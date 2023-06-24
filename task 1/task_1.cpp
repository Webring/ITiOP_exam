/*
 * Task 1:
 * � ��������� ����� ���� ������������������ �����.
 * �������� ������������, ������� ������ ������� ������ � ��������� �������� ���������������� ������������ ������.
 * ��������� ��� ������������, ������������� �������� ������������������
 * */

#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task 1/numbers.txt" // ��� �������� �����

using namespace std; //���������� ������������ ����

struct ListElement { // ��������� ��� �������� ������
    int value; // ��������
    ListElement *previous = NULL; // ��������� �� ���������� �������
    ListElement *next = NULL; // ��������� �� ��������� �������
};

void print_list(ListElement *first_element) { //������� ������ ������ �� �����
    cout << "List elements:" << endl;
    ListElement *iter_element = first_element; // ������� ��������� � �������� ��� ������ ������
    int total_amount = 0; // ���������� ��������� � ������
    while (iter_element != first_element or total_amount == 0) { //���� �� ������ �� ������� ��������
        cout << "| " << iter_element->value << endl; // ������� �� ����� �������
        total_amount++; // ����������� ����� �������� �� ����
        iter_element = iter_element->next; //��������� �� ���� ������
    }
    cout << "+amount: " << total_amount << endl; //�������� ����������
}

void swap_ends_elements(ListElement *first_element) { // ������� ����� �������� ��������� ���������� ����������� ������
    cout << "Swap ends of list" << endl;
    ListElement *last_element = first_element->previous; // ������� ��������� � �������� ��� ������ ������

    //swap(a, b) ������ �������� � ���������� a � b �������

    // ������� 1 (����� �������): swap(first_element->value, last_element->value); // ������ ������� �������� ���������

    // ������� 2 (����� ������ ��� � �����): ������ ������ �����������)))
    swap(first_element->next, last_element->next); // ������ ������� ��������� �� ��������� ��������
    swap(first_element->previous, last_element->previous); // ������ ������� ��������� �� ���������� ��������
    swap(*first_element, *last_element); // ������ ������������ �������� � ������
}

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

    ListElement *first_element, *iter_element; // ������� ��������� �� �������� ������: ������ ������ � ������� ��� ��������
    first_element = iter_element = new ListElement; // �������� ��� ��� ������

    while (not input_file.eof()) { // ������ ���� �� ��� ���, ���� �� �� ����������
        ListElement *new_element = new ListElement; // ������� ��������� �� ����� ������� �  �������� ��� ���� ������
        input_file >> new_element->value; // ������ �� ����� ����� �������� � ���������� �� � ���������
        iter_element->next = new_element; // ��������� ������ �� ��������� �������
        new_element->previous = iter_element;

        iter_element = iter_element->next; // ��������� �� ����� �������
    }

    first_element = first_element->next; // ������� ��������� �����

    first_element->previous = iter_element; // ����������� ���������� ������ �� ����������� ��������
    iter_element->next = first_element; // ����������� ���������� ������ �� ��������� ��������

    print_list(first_element); // ������� ������

    swap_ends_elements(first_element); // ������ ��������

    print_list(first_element); // ������� ������
    return 0;
}