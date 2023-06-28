
/*
 * Task 09:
 * В текстовом файле дана последовательность чисел.
 * Написать подпрограмму, которая находит в односвязнном циклическом списке минимальный элемент.
 * Используя эту подпрограмму, в заданной последовательности все элементы с минимальным значением переместить в конец последовательности.
 */

#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task_09/numbers.txt" // Имя входного файла

using namespace std; //Подключаем пространство имен

struct ListElement { // Структура для элемента списка
    int value; // значение
    ListElement *next = NULL; // указатель на следующий элемент
};

void print_list(ListElement *first_element) { //Функция вывода списка на экран
    cout << "List elements:" << endl;
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    do {
        cout << "| " << iter_element->value << endl; // Выводим на экран элемент
        iter_element = iter_element->next; //Переходим на след элмент
    } while (iter_element != first_element); //Пока не дойдем до первого элемента
}

int get_minimum_element(ListElement *first_element) {
    ListElement *minimum_element = nullptr;
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    do {
        if (minimum_element == nullptr or minimum_element->value > iter_element->value) {
            minimum_element = iter_element;
        }
        iter_element = iter_element->next; //Переходим на след элмент
    } while (iter_element != first_element); //Пока не дойдем до первого элемента
    return minimum_element->value;
}

ListElement *get_last_element(ListElement *first_element) {
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    do {
        iter_element = iter_element->next; //Переходим на след элмент
    } while (iter_element->next != first_element); //Пока не дойдем до первого элемента
    return iter_element;
}

ListElement *move_minimum_element_to_end(ListElement *first_element) {
    int minimum_value = get_minimum_element(first_element);

    ListElement *last_element = get_last_element(first_element);
    last_element->next = nullptr;

    ListElement *first_element_of_new_sequence, *iter_element_of_new_sequence;
    iter_element_of_new_sequence = first_element_of_new_sequence = new ListElement;

    ListElement *iter_element, *temp_element, *main_chain = new ListElement; // Создаем указатель и выделяем под данные память
    main_chain->next = first_element;
    iter_element = main_chain;
    while (iter_element->next != nullptr) { //Пока не дойдем до первого элемента
        if (iter_element->next->value == minimum_value) {
            temp_element = iter_element->next;
            iter_element_of_new_sequence->next = iter_element->next;
            iter_element_of_new_sequence = iter_element_of_new_sequence->next;

            iter_element->next = iter_element->next->next; // Меняем связи в списке
            temp_element->next = nullptr;
        } else {
            iter_element = iter_element->next; // переходим на следующий элемент
        }
    }
    iter_element->next = first_element_of_new_sequence->next;
    iter_element_of_new_sequence->next = main_chain->next;
    return main_chain->next;
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
        iter_element->next = new_element; // добавляем ссылку на следующий элемент

        iter_element = iter_element->next; // переходим на новый элемент
    }

    first_element = first_element->next; // Убираем заглавное звено

    iter_element->next = first_element; // Зацикливаем двусвязный список по следущему элементу

    print_list(first_element); // Выводим список

    first_element = move_minimum_element_to_end(first_element); // Меняем элементы

    print_list(first_element); // Выводим список
    return 0;
}