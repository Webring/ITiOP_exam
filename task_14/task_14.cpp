/*
 * Task 14 (Реализация с ООП):
 * В текстовом файле дана последовательность натуральных чисел, оканчивающаяся нулем.
 * Используя очередь с приоритетом напечатать числа последовательности по возрастанию.
 */
#include <iostream>
#include "fstream"
#include "priority_queue.h"

#define INPUT_FILE_PATH "../task_14/numbers.txt" // Имя входного файла


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

    PriorityQueue priority_queue;

    int number;
    while (not input_file.eof()){
        input_file >> number;

        if (number == 0) break;

        priority_queue.add(number);
    }

    //priority_queue.print();

    while (not priority_queue.is_empty()){
        cout << priority_queue.get() << endl;
    }

    return 0;
}