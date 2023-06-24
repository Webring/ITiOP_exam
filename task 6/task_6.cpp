/*
 * Task 6:
 * � ��������� ����� ���� ������������������ �����.
 * �������� ������������, ������� � ���������������� ������ ���������
 * ������ ��������� ��������� ��������� ��������.
 * ��������� ��� ������������, ������������� �������� ������������������
 * */
#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task 6/numbers.txt" // ��� �������� �����
#define DELETE_FAILED 0 // �������� ��������� ��� �������� ��������
#define VALUE_NOT_FOUND -1 // �������� ��������� ��� �������� ��������

using namespace std; //���������� ������������ ����

struct ListElement { // ��������� ��� �������� ������
    int value; // ��������
    ListElement *next = NULL; // ��������� �� ��������� �������
};

void print_list(ListElement *first_element) { //������� ������ ������ �� �����
    ListElement *iter_element = first_element->next; // ������� ��������� � �������� ��� ������ ������
    int total_amount = 0; // ���������� ��������� � ������
    while (iter_element != NULL) { //���� �� �������� ������
        cout << "| " << iter_element->value << endl; // ������� �� ����� �������
        total_amount++; // ����������� ����� �������� �� ����
        iter_element = iter_element->next; //��������� �� ���� ������
    }
    cout << "+amount: " << total_amount << endl; //�������� ����������
}

ListElement *find_last_element_with_value(ListElement *first_element, int value) { //������� ������ ���������� ��������� �������� � ������
    ListElement *iter_element = first_element; // ������� ��������� � �������� ��� ������ ������
    ListElement *answer_element_pointer = NULL;// ������� ��������� ��� �������� ������ � �������� ��� ������ ������
    while (iter_element != NULL) { //���� �� �������� ������
        if (iter_element->value == value) { //��������� ��� �� �������, ��� ����
            answer_element_pointer = iter_element; //���������� ��������� � ����������
        }
        iter_element = iter_element->next;//��������� �� ���� ������
    }
    return answer_element_pointer; // ���������� �����
}

int delete_not_last_elements(ListElement *first_element, int value) { // ������� �������� �� ��������� ���������
    ListElement *last_element = find_last_element_with_value(first_element, value); //�������� ����� ���������� ���������

    if (last_element == NULL) { // ���������, ��� ����� ����� � ������ ����
        return VALUE_NOT_FOUND; // ���������� ������
    }

    int number_of_deleted_values = 0; //���������� �������� ���������

    ListElement *iter_element = first_element;// ������� ��������� � �������� ��� ������ ������
    ListElement *temp_element; // ��������� �� ��������� ������
    while (iter_element->next != NULL) {//���� �� �������� ������
        if (iter_element->next->value == value and iter_element->next != last_element) { //���� ����� �� ��������� ���������
            temp_element = iter_element->next; //���������� �������
            iter_element->next = iter_element->next->next; // ������ ����� � ������
            delete temp_element; // ������� �������

            number_of_deleted_values++; // ����������� ����������
        } else {
            iter_element = iter_element->next; // ��������� �� ��������� �������
        }
    }

    return number_of_deleted_values; // ���������� ���������� �������� ��������
}

int main() {
    ifstream input_file(INPUT_FILE_PATH); // ��������� ���� ��� ������

    if (not input_file.is_open()) { // ���� ���� �� ������
        cout << "Can't open input file" << endl; //������� ��������� �� ������
        return 0; // ��������� ������ ���������
    }

    if (input_file.peek() == ifstream::traits_type::eof()) { // ��������� ���� �� �������
        cout << "file is empty" << endl; //������� ��������� �� ������
        return 0; // ��������� ������ ���������
    }

    ListElement *first_element, *iter_element; // ������� ��������� �� �������� ������: ������ ������ � ������� ��� ��������
    first_element = iter_element = new ListElement; // �������� ��� ��� ������



    while (not input_file.eof()) { // ������ ���� �� ��� ���, ���� �� �� ����������
        ListElement *new_element = new ListElement; // ������� ��������� �� ����� ������� �  �������� ��� ���� ������
        input_file >> new_element->value; // ������ �� ����� ����� �������� � ���������� �� � ���������
        iter_element->next = new_element; // ��������� ������� � ������

        iter_element = iter_element->next; // ��������� �� ����� �������
    }

    //first_element = first_element->next; // ������� ��������� �����

    int number_to_delete; // ���������� ��� �������� ����� ��� ��������

    print_list(first_element); // ������� ������ � �������
    cout << "Number to delete?" << endl;
    cin >> number_to_delete; // ���������� �����
    int delete_result = delete_not_last_elements(first_element, number_to_delete); // ������� ����� �� ������
    if (delete_result == VALUE_NOT_FOUND) { // ���� ����� �� �������
        cout << "Value '" << number_to_delete << "' not found!" << endl;
    } else if (delete_result == DELETE_FAILED) { // ���� �������� �� ���� �������
        cout << "Deleted not executed, because it's unique value" << endl;
        print_list(first_element);// ������� ������ � �������
    } else {
        cout << "Delete success" << endl;
        print_list(first_element);// ������� ������ � �������
    }

    return 0;
}