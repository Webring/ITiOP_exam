/*
 * Task 12:
 * В файле содержатся элементы упорядоченной по убыванию ключа таблицы следующего вида:
 * Шифр студента (10 символов), ФИО студента (25 символов), Средний балл (вещественное).
 * Ключ элемента – шифр студента. Ключ таблицы однозначно определяет ее элемент.
 * Количество элементов не превышает 100. Используя бинарный поиск, включить в таблицу еще один элемент.
 */

#include <iostream>
#include "fstream"
#include "table.h"

#define INPUT_FILE_PATH "../task_12/table.txt" // Имя входного файла

using namespace std; //Подключаем пространство имен

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

    Table students_table(100);
    students_table.import_from_file(input_file);
    students_table.print();

    cout << "Time to insert new element: " << endl; //STUDENT003 Bykov 99.9
    char code[CODE_LENGTH];
    char name[NAME_LENGTH];
    float average_score;
    cin >> code >> name >> average_score;
    students_table.add_row(code, name, average_score);
    students_table.print();


    return 0;
}