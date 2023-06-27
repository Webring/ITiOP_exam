/*
 * Task 15:
 * В таблице хранится информация о результатах забега в кроссе.
 * Элемент таблицы имеет следующую структуру: номер спортсмена (целое), время старта (вещественное), время финиша (вещественное).
 * Найти номера трех призеров забега и их результаты.
 */

#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task_15/table.txt" // Имя входного файла

using namespace std; //Подключаем пространство имен

struct TableRow { // Структура для строки таблицы
    int id; // Номер участника
    float start_time; // Время готовки
    float end_time; // Оценка жюри
    TableRow *next = nullptr;
};

float get_time(TableRow *row) {
    return row->end_time - row->start_time;
}

void print_table_row(TableRow *row, int index) {
    if (row != nullptr) { // Если такой элемент существуем
        cout << index << ") " << row->id << "\t\t" << row->start_time << "\t\t"; // Выводим на экран элемент
        cout << row->end_time << "\t\t" << get_time(row) << endl;
    }
}

void print_table(TableRow *first_element) { //Функция вывода списка на экран
    cout << "Table:" << endl;
    cout << "   ID\t\tstart\t\tend\t\ttime" << endl;
    TableRow *iter_element = first_element; // Создаем указатель и выделяем под данные память
    int total_amount = 0; // Количество элементов в списке
    while (iter_element != NULL) { //ПОка не кончится список
        print_table_row(iter_element, total_amount + 1);
        total_amount++; // Увеличиваем число элментов на один
        iter_element = iter_element->next; //Переходим на след элмент
    }
    cout << "+amount: " << total_amount << endl; //Печатаем количество
}

bool check(TableRow *place_for_cheking, TableRow *current_row) { // Функция для проверки нужно ли заменять значение в переменной с максимумом или нет
    return (place_for_cheking == nullptr) or (get_time(current_row) < get_time(place_for_cheking));;
}

void print_winners(TableRow *first_element) {
    TableRow *first_place = nullptr; //Указатель на строку таблицы с первым по максимальности элементом.
    TableRow *second_place = nullptr; // Аналогично первому месту
    TableRow *third_place = nullptr;

    TableRow *iter_element = first_element; // Создаем указатель и выделяем под данные память

    while (iter_element != nullptr) { // Перебираем все строки таблицы
        if (check(first_place, iter_element)) { // если текущий элемент больше максимума, то
            third_place = second_place; // Сдвигаем все элементы на один вниз, тем самым освобождая первый элемент и туда записываем новое значение
            second_place = first_place;
            first_place = iter_element;
        } else if (check(second_place, iter_element)) {// если текущий элемент меньше максимума, но больше второго максимума
            third_place = second_place; // Сдвигаем второй элемент на третий и на второе место записываем новый элемент
            second_place = iter_element;
        } else if (check(third_place, iter_element)) { // Если меньше 1 и 2 место, но больше 3
            third_place = iter_element; // Записываем на 3 место новый элемент
        }
        iter_element = iter_element->next;
    }
    cout << "Winners: " << endl;
    cout << "   ID\t\tstart\t\tend\t\ttime" << endl;
    print_table_row(first_place, 1); // Выводим победные места
    print_table_row(second_place, 2);
    print_table_row(third_place, 3);

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

    TableRow *first_element, *iter_element; // Создаем указатели на элементы списка: Начало списка и элемент для перебора
    first_element = iter_element = new TableRow; // Выделяем под них память

    while (not input_file.eof()) { // Читаем файл до тех пор, пока он не закончится
        TableRow *new_element = new TableRow;
        input_file >> new_element->id >> new_element->start_time >> new_element->end_time; //Записываем в таблицу данные
        iter_element->next = new_element; // добавляем элемент в список

        iter_element = iter_element->next; // переходим на новый элемент
    }

    first_element = first_element->next;

    print_table(first_element); //Печатаем таблицу

    print_winners(first_element); //Печатаем победителей
    return 0;
}