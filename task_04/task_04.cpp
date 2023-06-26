/*
 * Task 4:
 * В текстовом файле дана последовательность чисел.
 * Написать рекурсивную подпрограмму, которая вычисляет среднее арифметическое элементов непустого однонаправленного списка.
 * Используя эту подпрограмму. вычислить среднее арифметическое чисел заданной последовательности.
*/

#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task_04/numbers.txt" // Имя входного файла

using namespace std; //Подключаем пространство имен

struct ListElement { // Структура для элемента списка
    int value; // значение
    ListElement *next = NULL; // указатель на следующий элемент
};

void print_list(ListElement *first_element) { //Функция вывода списка на экран
    cout << "List elements:" << endl;
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    int total_amount = 0; // Количество элементов в списке
    while (iter_element != NULL) { //Пока не дойдем до первого элемента
        cout << "| " << iter_element->value << endl; // Выводим на экран элемент
        total_amount++; // Увеличиваем число элментов на один
        iter_element = iter_element->next; //Переходим на след элмент
    }
    cout << "+amount: " << total_amount << endl; //Печатаем количество
}

float find_average_number_recursion(ListElement *element, int sum = 0, int quantity = 0) { // Функция для подсчета средне арифметического числа
    if (element == NULL) { // Базовый случай рекурсии (Если список кончился)
        return (sum + .0) / quantity; // Возвращаем средне арифметическое число
    }

    return find_average_number_recursion(element->next, sum + element->value, quantity + 1); // Вызываем эту функцию
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

    while (not input_file.eof()) { // Читаем файл до тех пор, пока он не закончится
        ListElement *new_element = new ListElement; // создаем указатель на новый элемент и  выделяем под него память
        input_file >> new_element->value; // Читаем из файла новое значение и записываем ее в структуру
        iter_element->next = new_element; // добавляем ссылку на следующий элемент

        iter_element = iter_element->next; // переходим на новый элемент
    }

    first_element = first_element->next; // Убираем заглавное звено

    print_list(first_element); // Выводим список

    float average_number = find_average_number_recursion(first_element); // Вызываем функцию подсчета средне арифметического

    cout << "Average number is " << average_number << endl; // Выводим средне арифметическое число

    return 0;
}
