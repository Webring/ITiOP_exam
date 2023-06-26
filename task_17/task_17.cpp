/*
 * Task 17:
 * В конкурсе поваров было участников, n ≤ 50.
 * В таблице хранится информация о результатах конкурса.
 * Элемент таблицы имеет следующую структуру: номер участника, время приготовления блюда (вещественное), оценка жюри (целое число от 0 до 10).
 * Найти номера трех самых быстрых участников из тех, кто больше всего понравился жюри.
 */

#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task_17/table.txt" // Имя входного файла
#define MAX_NUMBER_OF_CHEFS 50

using namespace std; //Подключаем пространство имен

struct TableRow { // Структура для строки таблицы
    int id; // Номер участника
    float cook_time; // Время готовки
    int score; // Оценка жюри
};

int number_of_chefs = 0; // Число строк
TableRow rows[MAX_NUMBER_OF_CHEFS]; // Массив для хранения строк

void print_table_row(int row_id) {
    if (row_id >= 0 and row_id < number_of_chefs) { // Если такой элемент существуем
        cout << rows[row_id].id << "\t" << rows[row_id].cook_time << "\t" << rows[row_id].score << endl; // Печатаем строку таблицы
    }
}

void print_table() { //Функция вывода таблицы на экран
    cout << "Table:" << endl;
    cout << "id\ttime\tscore" << endl;
    for (int i = 0; i < number_of_chefs; i++) { // Перебираем все строчки таблицы
        print_table_row(i); // Выводим строку таблицы
    }
}

bool check(int place_id, int current_id) { // Функция для проверки нужно ли заменять значение в переменной с максимумом или нет
    bool first_part = (place_id == -1); //Если элемента в максимуме нет
    bool second_part = (rows[current_id].score > rows[place_id].score); // Если оценка нового элемента больше
    //Если оценки равны, но время меньше
    bool third_part = (rows[current_id].score == rows[place_id].score and rows[current_id].cook_time < rows[place_id].cook_time);
    return first_part or second_part or third_part;
}

void print_winners() {
    int first_place_id = -1; //Номер максимальной строки
    int second_place_id = -1; // Номер второй по максимальности строки
    int third_place_id = -1; // Номер третьей по максимальности строки
    for (int i = 0; i < number_of_chefs; i++) { // Перебираем все строки таблицы
        if (check(first_place_id, i)) { // если текущий элемент больше максимума, то
            third_place_id = second_place_id; // Сдвигаем все элементы на один вниз, тем самым освобождая первый элемент и туда записываем новое значение
            second_place_id = first_place_id;
            first_place_id = i;
        } else if (check(second_place_id, i)) {// если текущий элемент меньше максимума, но больше второго максимума
            third_place_id = second_place_id; // Сдвигаем второй элемент на третий и на второе место записываем новый элемент
            second_place_id = i;
        } else if (check(third_place_id, i)) { // Если меньше 1 и 2 место, но больше 3
            third_place_id = i; // Записываем на 3 место новый элемент
        }
    }
    cout << "Winners: " << endl;
    cout << "id\ttime\tscore" << endl;
    print_table_row(first_place_id); // Выводим победные места
    print_table_row(second_place_id);
    print_table_row(third_place_id);

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

    while (not input_file.eof()) { // Читаем файл до тех пор, пока он не закончится
        input_file >> rows[number_of_chefs].id >> rows[number_of_chefs].cook_time >> rows[number_of_chefs].score; //Записываем в таблицу данные
        number_of_chefs++; //Увеличиваем число строк в таблице на один
    }

    print_table(); //Печатаем таблицу

    print_winners(); //Печатаем победителей
    return 0;
}