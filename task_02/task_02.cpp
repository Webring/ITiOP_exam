/*
 * Task 2 (решение работает проверяет вхождение при зацикленности списков, те последовательность 123 входит в 2341):
 * В текстовом файле даны две последовательности символов, разделенные пробелом.
 * Написать подпрограмму, которая для двух однонаправленных циклических списков S1 и S2 проверяет, входит ли список S1 в список S2.
 * Используя эту подпрограмму проверить входит ли первая последовательность во вторую, если не входит, добавить список S1 к списку S2.
 */
#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task_02/test.txt" // Имя входного файла

using namespace std; //Подключаем пространство имен

struct ListElement { // Структура для элемента списка
    char value; // значение
    ListElement *next = NULL; // указатель на следующий элемент
};

void print_list(ListElement *first_element, int id) { //Функция вывода списка на экран
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    cout << "Line " << id << ": ";
    do { //ПОка не кончится список
        cout << iter_element->value; // Выводим на экран элемент
        iter_element = iter_element->next; //Переходим на след элмент
    } while (iter_element != first_element);
    cout << endl;
}

bool is_sub_sequence(ListElement *main_sequence, ListElement *sub_sequence) {
    ListElement *iter_main_element = main_sequence; // Создаем указатель и выделяем под данные память
    do { //ПОка не кончится список
        bool success = true;
        ListElement *new_iter_main_element = iter_main_element; // Создаем указатель и выделяем под данные память
        ListElement *iter_sub_element = sub_sequence; // Создаем указатель и выделяем под данные память
        do { //ПОка не кончится список
            if (new_iter_main_element->value != iter_sub_element->value) {
                success = false;
                break;
            }
            new_iter_main_element = new_iter_main_element->next;
            iter_sub_element = iter_sub_element->next; //Переходим на след элмент
        } while (iter_sub_element != sub_sequence);

        if (success) {
            return true;
        }

        iter_main_element = iter_main_element->next; //Переходим на след элмент
    } while (iter_main_element != main_sequence);
    return false;
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

    ListElement *first_element_of_first_sequence, *first_element_of_second_sequence, *iter_element, *end_of_first_sequence;
    first_element_of_second_sequence = new ListElement;
    first_element_of_first_sequence = iter_element = new ListElement; // Выделяем под них память

    char symbol;
    while (input_file.get(symbol)) { // Читаем файл до тех пор, пока он не закончится
        ListElement *new_element = new ListElement; // создаем указатель на новый элемент и выделяем под него память
        new_element->value = symbol; // Читаем из файла новое значение и записываем ее в структуру

        if (symbol == ' ') {
            first_element_of_first_sequence = first_element_of_first_sequence->next;
            iter_element->next = first_element_of_first_sequence;
            end_of_first_sequence = iter_element;
            iter_element = first_element_of_second_sequence;
        } else {
            iter_element->next = new_element; // добавляем элемент в список
            iter_element = iter_element->next; // переходим на новый элемент
        }

    }

    first_element_of_second_sequence = first_element_of_second_sequence->next;
    iter_element->next = first_element_of_second_sequence;


    if (first_element_of_first_sequence == nullptr or first_element_of_second_sequence->next == nullptr) {
        cout << "One line is empty" << endl;
        return 0;
    }

    print_list(first_element_of_first_sequence, 1);
    print_list(first_element_of_second_sequence, 2);

    if (is_sub_sequence(first_element_of_second_sequence, first_element_of_first_sequence)) {
        cout << "Line 1 is sub sequence line 2" << endl;
    } else {
        cout << "Line 1 is NOT sub sequence line 2" << endl;
        iter_element->next = first_element_of_first_sequence;
        end_of_first_sequence->next = first_element_of_second_sequence;
        print_list(first_element_of_second_sequence, 3);
    }

    return 0;
}