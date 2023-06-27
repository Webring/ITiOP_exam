/*
 * Task 18:
 * В текстовом файле дана последовательность чисел.
 * Написать подпрограмму, которая проверяет, упорядочена ли по убыванию последовательность действительных чисел,
 * хранящаяся в однонаправленном списке. Используя эту подпрограмму преобразовать заданную последовательность следующим образом,
 * если она упорядочена, то, не нарушая упорядоченности, вставить в нее элемент со значением р, иначе удалить элемент с номером k.
 */
#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task_18/numbers.txt" // Имя входного файла

using namespace std; //Подключаем пространство имен

struct ListElement { // Структура для элемента списка
    float value; // значение
    ListElement *next = NULL; // указатель на следующий элемент
};

void print_list(ListElement *first_element) { //Функция вывода списка на экран
    cout << "List elements:" << endl;
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    int total_amount = 0; // Количество элементов в списке
    while (iter_element != NULL) { //ПОка не кончится список
        cout << total_amount + 1 << ") " << iter_element->value << endl; // Выводим на экран элемент
        total_amount++; // Увеличиваем число элментов на один
        iter_element = iter_element->next; //Переходим на след элмент
    }
    cout << "+amount: " << total_amount << endl; //Печатаем количество
}

bool is_decreasing_sequence(ListElement *first_element) {
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    while (iter_element->next != NULL) { //ПОка не кончится список
        if (iter_element->value <= iter_element->next->value) {
            return false;
        }
        iter_element = iter_element->next;
    }
    return true;
}

bool delete_element_by_id(ListElement *first_element, int id) {
    int current_id = 1;
    ListElement *temp_element; // указатель на удаляемый элемнт
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    while (iter_element->next != NULL) { //ПОка не кончится список
        if (current_id == id) {
            temp_element = iter_element->next; //Запоминаем элемент
            iter_element->next = iter_element->next->next; // Меняем связи в списке
            delete temp_element; // Удаляем элемент
            return true;
        }

        current_id++;
        iter_element = iter_element->next;
    }
    return false;
}

void insert_element(ListElement *first_element, float value) {
    ListElement *new_element = new ListElement;
    new_element->value = value;

    if (first_element->next != NULL and value >= first_element->next->value) {
        new_element->next = first_element->next;
        first_element->next = new_element;
        return;
    }

    ListElement *iter_element = first_element->next; // Создаем указатель и выделяем под данные память
    while (iter_element->next != NULL) { //ПОка не кончится список
        if (value <= iter_element->value and value >= iter_element->next->value) {
            new_element->next = iter_element->next;
            iter_element->next = new_element;
            return;
        }
        iter_element = iter_element->next;
    }

    iter_element->next = new_element;
}

bool file_is_empty(ifstream &file) {
    return file.peek() == ifstream::traits_type::eof(); // Если следующий доступный для чтения символ равен символу конца файла
}

int main() {
    ifstream input_file(INPUT_FILE_PATH); // открываем файл для чтения

    if (not input_file.is_open()) { // Если файл не открыт
        cout << "Can't open input file" << endl; //Выводим сообщение об ошибке
        return 0; // Завершаем работу программы
    }

    if (file_is_empty(input_file)) { // Проверяем файл на пустоту
        cout << "file is empty" << endl; //Выводим сообщение об ошибке
        return 0; // Завершаем работу программы
    }

    ListElement *first_element, *iter_element; // Создаем указатели на элементы списка: Начало списка и элемент для перебора
    first_element = iter_element = new ListElement; // Выделяем под них память


    while (not input_file.eof()) { // Читаем файл до тех пор, пока он не закончится
        ListElement *new_element = new ListElement; // создаем указатель на новый элемент и  выделяем под него память
        input_file >> new_element->value; // Читаем из файла новое значение и записываем ее в структуру
        iter_element->next = new_element; // добавляем элемент в список

        iter_element = iter_element->next; // переходим на новый элемент
    }

    print_list(first_element->next); // Выводим список в консоль


    if (is_decreasing_sequence(first_element->next)) {
        float new_value;

        cout << "Is decreasing sequence" << endl;

        cout << "Enter a number to insert: " << endl;
        cin >> new_value;

        insert_element(first_element, new_value);
        print_list(first_element->next);

    } else {
        int id_to_delete;

        cout << "Is not decreasing sequence" << endl;
        cout << "Enter number id to delete: " << endl;
        cin >> id_to_delete;
        if (delete_element_by_id(first_element, id_to_delete)) {
            cout << "Deletion success" << endl;
            print_list(first_element->next); // Выводим список в консоль
        } else {
            cout << "Invalid ID!!!" << endl;
        }
    }

    return 0;
}