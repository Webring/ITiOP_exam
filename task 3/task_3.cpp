/*
 * Task 3:
 * � ��������� ����� ���� ������������������ �����.
 * �������� ������������, ������� ������� ������� �������������� ��������������� ��������� ���������������� ������.
 * ��������� ��� ������������, ��������� ������� �������������� �������� ������������������.
 */

#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task 3/numbers.txt" // ��� �������� �����

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
    while (iter_element != NULL) { //���� �� ������ �� ������� ��������
        cout << "| " << iter_element->value << endl; // ������� �� ����� �������
        total_amount++; // ����������� ����� �������� �� ����
        iter_element = iter_element->next; //��������� �� ���� ������
    }
    cout << "+amount: " << total_amount << endl; //�������� ����������
}

float find_average_number(ListElement *first_element) { // ������� ��� �������� ������ ��������������� �����
    ListElement *iter_element = first_element; // ������� ��������� �� ������ �������
    int number_of_numbers = 0; // ���������� �����
    int numbers_sum = 0; // ����� �����

    while (iter_element != NULL) { //���� ������� ������� �� ����� ����
        if (iter_element->value >= 0) { // ���� ����� ��������������
            numbers_sum += iter_element->value; // � ����� ��������� ���� �����
            number_of_numbers += 1; // � ���������� ��������� 1
        }
        iter_element = iter_element->next; // ��������� �� ��������� �������
    }

    if (number_of_numbers == 0) { // ���� ���������� ����� 0
        return -1; // ���������� -1
    }

    return (numbers_sum + .0) / number_of_numbers; // ���������� ������ �������������� �����
}

bool file_is_empty(ifstream &file) { // �������� ����� �� �������
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

    print_list(first_element); // ������� ������

    float average_number = find_average_number(first_element); // �������� ������� �������� ������ ���������������

    if (average_number > 0) { // ���� ����� ���������� �����
        cout << "Average number is " << average_number << endl;
    } else { // ���� �� ���������� ��������� ����� (���������� ����� = 0)
        cout << "ERROR! Average number can't be calculated!" << endl;
    }


    return 0;
}
