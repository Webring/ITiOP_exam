/*
 * Task 16 (реализация 1):
 * В текстовом файле дана последовательность символов, оканчивающаяся точкой.
 * Написать подпрограмму, которая печатает эту последовательность в обратном порядке.
 * Используя эту подпрограмму, напечатать заданную последовательность.
 *
 * Тут используется односвязный ациклический список и рекурсивный вывод списка
 */
#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task_16/test.txt" // Имя входного файла

using namespace std; //Подключаем пространство имен

struct ListElement { // Структура для элемента списка
    char value; // значение
    ListElement *next = NULL; // указатель на следующий элемент
};

void print_list(ListElement *first_element) { //Функция вывода списка на экран
    cout << "List elements:" << endl;
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    while (iter_element != NULL) { //ПОка не кончится список
        cout << "| " << iter_element->value << endl; // Выводим на экран элемент
        iter_element = iter_element->next; //Переходим на след элмент
    }
}

void reverse_recursion_print_list(ListElement *element) { // Рекурсивный вывод списка в обратном порядке
    if (element == nullptr) { // Базовый случай рекурсии (Если список кончился)
        return;
    }

    reverse_recursion_print_list(element->next); // Вызываем эту же функцию

    cout << "| " << element->value << endl; // Печатаем элемент
}

void reverse_print_list(ListElement *first_element) { // Просто функция обертка для reverse_recursion_print_list
    cout << "Reverse list:" << endl;
    reverse_recursion_print_list(first_element);
}

bool file_is_empty(ifstream &file) { // Проверка файла на пустоту
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
    while (input_file.get(readed_symbol) and readed_symbol != '.') { // Читаем файл до тех пор, пока он не закончится или не дойдет до точки
        ListElement *new_element = new ListElement; // создаем указатель на новый элемент и  выделяем под него память
        new_element->value = readed_symbol; // Записываем прочтенное значение в структуру
        iter_element->next = new_element; // добавляем элемент в список

        iter_element = iter_element->next; // переходим на новый элемент
    }

    first_element = first_element->next; //Удаляем заглавное звено

    print_list(first_element); // Выводим список в консоль
    reverse_print_list(first_element);

    return 0;
}