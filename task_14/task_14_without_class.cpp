/*
 * Task 14 (Реализация без ООП):
 * В текстовом файле дана последовательность натуральных чисел, оканчивающаяся нулем.
 * Используя очередь с приоритетом напечатать числа последовательности по возрастанию.
 */
#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task_14/numbers.txt" // Имя входного файла

using namespace std; //Подключаем пространство имен

struct Element { // Структура для элемента очереди
    int key; // значение
    Element *next = nullptr; // указатель на следующий элемент
};


bool is_empty_queue(Element *main) {
    return main->next == nullptr;
}

void print(Element *main) {
    if (is_empty_queue(main)) {
        cout << "Queue is empty" << endl;
        return;
    }

    cout << "Queue:" << endl;
    Element *iter_element = main->next;
    while (iter_element != nullptr) {
        cout << " V\t" << iter_element->key << "\tV " << endl;
        iter_element = iter_element->next;
    }
}


int get(Element *main) {
    if (not is_empty_queue(main)) {
        Element *temp = main->next;
        main->next = main->next->next;
        return temp->key;
    }
}

void add(Element *main, int new_value) {
    Element *new_element = new Element;
    new_element->key = new_value;

    if (is_empty_queue(main)) {
        main->next = new_element;
        return;
    }

    Element *iter_element = main;
    while (iter_element->next != nullptr) {
        if (iter_element->next->key > new_value) {
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

    Element *main = new Element;

    int number;
    while (not input_file.eof()) {
        input_file >> number;

        if (number == 0) break;

        add(main, number);
    }

    print(main);

    return 0;
}