/*
 * Task 3:
 * В текстовом файле дана последовательность чисел.
 * Написать подпрограмму, которая находит среднее арифметическое неотрицательных элементов двунаправленного списка.
 * Используя эту подпрограмму, вычислить среднее арифметическое заданной последовательности.
 */

#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task_03/numbers.txt" // Имя входного файла

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
    while (iter_element != NULL) { //Пока не дойдем до первого элемента
        cout << "| " << iter_element->value << endl; // Выводим на экран элемент
        total_amount++; // Увеличиваем число элментов на один
        iter_element = iter_element->next; //Переходим на след элмент
    }
    cout << "+amount: " << total_amount << endl; //Печатаем количество
}

float find_average_number(ListElement *first_element) { // Функция для подсчета средне арифметического числа
    ListElement *iter_element = first_element; // Создаем указатель на первый элемент
    int number_of_numbers = 0; // Количество чисел
    int numbers_sum = 0; // Сумма чисел

    while (iter_element != NULL) { //Пока текущий элемент не равен нулю
        if (iter_element->value >= 0) { // Если число неотрицательно
            numbers_sum += iter_element->value; // К сумме добавляем само число
            number_of_numbers += 1; // К количеству добавляем 1
        }
        iter_element = iter_element->next; // Переходим на следующий элемент
    }

    if (number_of_numbers == 0) { // Если количество равно 0
        return -1; // Возвращаем -1
    }

    return (numbers_sum + .0) / number_of_numbers; // Возвращаем средне арифметическое число
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
        new_element->previous = iter_element;

        iter_element = iter_element->next; // переходим на новый элемент
    }

    first_element = first_element->next; // Убираем заглавное звено

    print_list(first_element); // Выводим список

    float average_number = find_average_number(first_element); // Вызываем функцию подсчета средне арифметического

    if (average_number > 0) { // Если число получилось найти
        cout << "Average number is " << average_number << endl;
    } else { // Если не получилось вычислить число (Количество чисел = 0)
        cout << "ERROR! Average number can't be calculated!" << endl;
    }


    return 0;
}
