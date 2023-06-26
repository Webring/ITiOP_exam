/*
 * Task 10:
 * В текстовом файле дана последовательность вещественных чисел.
 * Написать подпрограмму, которая находит сумму последнего и предпоследнего элементов однонаправленного списка.
 * Используя эту подпрограмму, вычислить сумму двух последних элементов заданной последовательности.
 * Учесть возможность отсутствия этих элементов.
*/

#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task_10/numbers.txt" // Имя входного файла

using namespace std; //Подключаем пространство имен

struct ListElement { // Структура для элемента списка
    int value; // значение
    ListElement *next = nullptr; // указатель на следующий элемент
};

void print_list(ListElement *first_element) { //Функция вывода списка на экран
    cout << "List elements:" << endl;
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    while (iter_element != nullptr) {//Пока не закончится список
        cout << "| " << iter_element->value << endl; // Выводим на экран элемент
        iter_element = iter_element->next; //Переходим на след элмент
    }
}

int sum_last_elements(ListElement *first_element, bool *success_flag) { // Функция для подсчета суммы
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    while (iter_element != NULL) { // Пока не кончится список
        if (iter_element->next != nullptr and iter_element->next->next == nullptr) { // Если впереди остался один элемент
            cout << "last numbers is " << iter_element->value << " and " << iter_element->next->value << endl; // Выводим сообщение о находке
            *success_flag = true; // Устанавливаем флаг для обозначения успеха
            return iter_element->value + iter_element->next->value; // возвращаем сумму
        }
        iter_element = iter_element->next; // Переходим на следущий элемент
    }
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

    // Список с загланым звеном
    ListElement *first_element, *iter_element; // Создаем указатели на элементы списка: Начало списка и элемент для перебора
    first_element = iter_element = new ListElement; // Выделяем под них память

    while (not input_file.eof()) { // Читаем файл до тех пор, пока он не закончится
        ListElement *new_element = new ListElement; // создаем указатель на новый элемент и  выделяем под него память
        input_file >> new_element->value; // Читаем из файла новое значение и записываем ее в структуру
        iter_element->next = new_element; // добавляем ссылку на следующий элемент

        iter_element = iter_element->next; // переходим на новый элемент
    }

    first_element = first_element->next; // Удаляем заглавное звено

    print_list(first_element); // Выводим список

    bool success_flag = false; // Создаем флаг для обозночения успешного выполнения операции
    int sum = sum_last_elements(first_element, &success_flag); // Вызываем функцию подсчета суммы
    if (success_flag) { // Если успешно, то выводим сумму
        cout << "sum = " << sum << endl;
    } else { // Иначе выводим ошибку
        cout << "Sequence length < 2" << endl;
    }

    return 0;
}
