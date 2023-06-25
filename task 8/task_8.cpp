/*
 * Task 8:
 * В текстовом файле дана последовательность чисел.
 * Написать подпрограмму поиска k-го элемента однонаправленного циклического списка,
 * считая, что k - номер элемент, а нумерация начинается с 1 от 1-го элемента списка.
 * Учесть возможную некорректность задания k. Используя эту подпрограмму
 * вычислить разность элементов заданной последовательности с номерами x и у.
*/

#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task 8/numbers.txt" // Имя входного файла

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

ListElement *get_element_by_index(ListElement *first_element, int index) {
    ListElement *iter_element = first_element; // Создаем указатель для перебора и приравниваем его к указателю первого элемента
    int iter_index = 1; // Индекс текущего перебираемого элемента
    do {
        if (iter_index == index) { // Если это нужный по счету элемент
            return iter_element; // Возвращаем элемент
        }

        iter_index++; // Увеличиваем индекс на 1
        iter_element = iter_element->next;  // Переходим на следующий элемент
    } while (iter_element != first_element); // Пока не дойдем до первого элемента

    return nullptr; // Если элемент не найден, то возвращаем нулевой указатель
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

    first_element = first_element->next; // Удаляем заглавное звено
    iter_element->next = first_element; // Зацикливаем список

    print_list(first_element); // Выводим список

    int first_element_index, second_element_index; // Переменные для храниения нужных индексов элементов

    cout << "First element index:" << endl;
    cin >> first_element_index; //Спрашиваем Индеккс
    ListElement *first_number_element = get_element_by_index(first_element, first_element_index); // Получаем указатель на элемент
    if (first_number_element == nullptr) { // Если указатель нулевой, значит элемент не найден
        cout << "Invalid element index!" << endl;
        return 0;
    }

    cout << "Second element index:" << endl;
    cin >> second_element_index; //Спрашиваем Индеккс
    ListElement *second_number_element = get_element_by_index(first_element, second_element_index); // Получаем указатель на элемент
    if (second_number_element == nullptr) { // Если указатель нулевой, значит элемент не найден
        cout << "Invalid element index" << endl;
        return 0;
    }

    int first_number = first_number_element->value; // Получаем значения из элементов списка
    int second_number = second_number_element->value;

    cout << "First number (X): " << first_number << endl; // Выводим в консоль полученные числа
    cout << "Second number (Y): " << second_number << endl;
    cout << "X - Y = " << first_number - second_number << endl; // Считаем и выводим результат на экран

    return 0;
}
