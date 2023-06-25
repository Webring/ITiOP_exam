/*
 * Task 5:
 * В текстовом файле дана последовательность чисел.
 * Написать рекурсивную подпрограмму, которая находит максимальный элемент непустого однонаправленного списка.
 * Используя эту подпрограмму, удалить из заданной последовательности все элементы со значениями меньше максимального.
*/

#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task 5/numbers.txt" // Имя входного файла

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

int find_maximum_value(ListElement *element, int maximum_value = 0, bool is_first = true) { // Функция для подсчета средне арифметического числа
    if (element == NULL) { // Базовый случай рекурсии (Если список кончился)
        return maximum_value; // Возвращаем максимальный элемент
    }

    return find_maximum_value(element->next, max(maximum_value, element->value), false); // Вызываем эту функцию
}

void delete_no_maximum_numbers(ListElement *first_element) { // Функция удаления не максимальных элементов
    int maximum_number = find_maximum_value(first_element->next); //Ищем максимальное число
    cout << "Maximum number is " << maximum_number << endl;
    ListElement *iter_element = first_element; // создаем указатель на перебираемый элемент равен указателю на первый элемент
    ListElement *temp_element; // указатель на удаляемый элемнт
    while (iter_element->next != NULL) {//ПОка не кончится список
        if (iter_element->next->value != maximum_number) { //Если не максимальный элемент
            temp_element = iter_element->next; //Запоминаем элемент
            iter_element->next = iter_element->next->next; // Меняем связи в списке
            delete temp_element; // Удаляем элемент
        } else {
            iter_element = iter_element->next; // переходим на следующий элемент
        }
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

    print_list(first_element->next); // Выводим список

    delete_no_maximum_numbers(first_element); // Удаляем не максимальные элементы

    print_list(first_element->next); // Выводим список

    return 0;
}
