
/*
 * Task 1:
 * В текстовом файле дана последовательность чисел.
 * Написать подпрограмму, которая меняет местами первый и последний элементы двунаправленного циклического списка.
 * Используя эту подпрограмму, преобразовать заданную последовательность
 * */

#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task_01/numbers.txt" // Имя входного файла

using namespace std; //Подключаем пространство имен

struct ListElement { // Структура для элемента списка
    int value; // значение
    ListElement *previous = NULL; // указатель на предыдущий элемент
    ListElement *next = NULL; // указатель на следующий элемент
};

void print_list(ListElement *first_element) { //Функция вывода списка на экран
    cout << "List elements:" << endl;
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    int total_amount = 0; // Количество элементов в списке
    while (iter_element != first_element or total_amount == 0) { //Пока не дойдем до первого элемента
        cout << "| " << iter_element->value << endl; // Выводим на экран элемент
        total_amount++; // Увеличиваем число элментов на один
        iter_element = iter_element->next; //Переходим на след элмент
    }
    cout << "+amount: " << total_amount << endl; //Печатаем количество
}

void swap_ends_elements(ListElement *first_element) { // Функция смены конечных элементов двусвязном зацикленном списке
    cout << "Swap ends of list" << endl;
    ListElement *last_element = first_element->previous; // Создаем указатель и выделяем под данные память

    //swap(a, b) меняет значения в переменных a и b местами

    // Решение 1 (более простое): swap(first_element->value, last_element->value); // меняем местами значения перменных

    // Решение 2 (вроде именно оно и нужно): Крутим вертим указателями)))
    swap(first_element->next, last_element->next); // Меняем местами указатели на следующие элементы
    swap(first_element->previous, last_element->previous); // Меняем местами указатели на предыдущие элементы
    swap(*first_element, *last_element); // Меняем расположение объектов в памяти
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
        new_element->previous = iter_element;

        iter_element = iter_element->next; // переходим на новый элемент
    }

    first_element = first_element->next; // Убираем заглавное звено

    first_element->previous = iter_element; // Зацикливаем двусвязный список по предыдущему элементу
    iter_element->next = first_element; // Зацикливаем двусвязный список по следущему элементу

    print_list(first_element); // Выводим список

    swap_ends_elements(first_element); // Меняем элементы

    print_list(first_element); // Выводим список
    return 0;
}