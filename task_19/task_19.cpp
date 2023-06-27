/*
 * Task 19:
 * В текстовом файле дана последовательность символов, оканчивающаяся точкой.
 * Написать подпрограмму, которая проверяет, симметричен ли относительно его середины двусвязанный кольцевой список.
 * Используя эту подпрограмму, проверить, симметрична ли относительно ее середины заданная последовательность символов.
 */

#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task_19/test.txt" // Имя входного файла

using namespace std; //Подключаем пространство имен

struct ListElement { // Структура для элемента списка
    char value; // значение
    ListElement *previous = NULL; // указатель на предыдущий элемент
    ListElement *next = NULL; // указатель на следующий элемент
};

void print_list(ListElement *first_element) { //Функция вывода списка на экран
    cout << "Line: ";
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    do { //Пока не дойдем до первого элемента
        cout << iter_element->value; // Выводим на экран элемент
        iter_element = iter_element->next; //Переходим на след элмент
    } while (iter_element != first_element);
    cout << endl;
}

bool is_polindrome(ListElement *first_element) {
    ListElement *left_element = first_element;
    ListElement *right_element = first_element->previous;

    do {
        if (left_element->value != right_element->value) {
            return false;
        }
        left_element = left_element->next;
        right_element = right_element->previous;
    } while (left_element != right_element and left_element->previous != right_element);

    return true;
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

    char readed_symbol;
    while (input_file.get(readed_symbol) and readed_symbol != '.') { // Читаем файл до тех пор, пока он не закончится или до точки
        ListElement *new_element = new ListElement; // создаем указатель на новый элемент и  выделяем под него память
        new_element->value = readed_symbol; // Читаем из файла новое значение и записываем ее в структуру
        iter_element->next = new_element; // добавляем ссылку на следующий элемент
        new_element->previous = iter_element;

        iter_element = iter_element->next; // переходим на новый элемент
    }

    first_element = first_element->next; // Убираем заглавное звено

    if (first_element == nullptr) {
        cout << "Sequence is empty" << endl;
        return 0;
    }

    first_element->previous = iter_element; // Зацикливаем двусвязный список по предыдущему элементу
    iter_element->next = first_element; // Зацикливаем двусвязный список по следущему элементу

    print_list(first_element); // Выводим список

    if (is_polindrome(first_element)) {
        cout << "Is symmetric list" << endl;
    } else {
        cout << "Is not symmetric list" << endl;
    }

    return 0;
}