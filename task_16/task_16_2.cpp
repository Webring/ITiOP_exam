/*
 * Task 16 (реализация 2):
 * В текстовом файле дана последовательность символов, оканчивающаяся точкой.
 * Написать подпрограмму, которая печатает эту последовательность в обратном порядке.
 * Используя эту подпрограмму, напечатать заданную последовательность.
 *
 * Тут используется циклический двусвязный список
 */
#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task_16/test.txt" // Имя входного файла

using namespace std; //Подключаем пространство имен

struct ListElement { // Структура для элемента списка
    char value; // значение
    ListElement *next = NULL; // указатель на следующий элемент
    ListElement *previous = NULL; // указатель на предыдущий элемент
};

void print_list(ListElement *first_element) { //Функция вывода списка на экран
    cout << "Line: ";
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    do {
        cout << iter_element->value; // Выводим на экран элемент
        iter_element = iter_element->next; //Переходим на след элмент
    } while (iter_element != first_element); //ПОка не дойдем до первого элемента
    cout << endl;
}

void reverse_print_list(ListElement *first_element) { //Функция вывода списка на экран в обратном порядке
    cout << "Reversed line: ";
    ListElement *last_element = first_element->previous; //Получаем указатель на последний элемент
    ListElement *iter_element = last_element; // Создаем указатель и выделяем под данные память
    do {
        cout << iter_element->value; // Выводим на экран элемент
        iter_element = iter_element->previous; //Переходим на пред элемент
    } while (iter_element != last_element); //ПОка не дойдем до последнего элемента
    cout << endl;
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
        new_element->previous = iter_element; // В новый элемент добавляем ссылку на предыдущий элемент
        iter_element->next = new_element; // добавляем элемент в список

        iter_element = iter_element->next; // переходим на новый элемент
    }

    first_element = first_element->next; //Удаляем заглавное звено
    first_element->previous = iter_element; // Зацикливаем список
    iter_element->next = first_element;

    print_list(first_element); // Выводим список в консоль
    reverse_print_list(first_element);

    return 0;
}