/*
 * Task 20:
 * В файле дана информация записавшихся на прием к врачу: фамилия (15 символов), возраст (целое).
 * В списке не более 12 пациентов. На каждого пациента врач тратит 20 минут.
 * Определить, сколько ждать в очереди пациенту с фамилией str1,
 * если в кабинет врача зашел пациент с фамилией str2 (значения str1 и str2 вводить с клавиатуры).
 */

#include <iostream>
#include "fstream"
#include "string.h"

#define INPUT_FILE_PATH "../task_20/queue.txt" // Имя входного файла

using namespace std; //Подключаем пространство имен

struct ListElement { // Структура для элемента списка
    char surname[15]; // Фамилия
    int age; // Возраст
    ListElement *next = NULL; // указатель на следующий элемент
};

void print_table(ListElement *first_element) { //Функция вывода таблицы на экран
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    cout << "Queue: " << endl;
    cout << "  Name\t\t\tAge" << endl;
    while (iter_element != NULL) { //Пока не дойдем до первого элемента
        cout << "V " << iter_element->surname << "\t\t" << iter_element->age << " y.o." << endl; // Выводим на экран элемент
        iter_element = iter_element->next; //Переходим на след элмент
    }
}

// Подсчет времени ожидания
int calc_time_before_reception(ListElement *first_element, char waiting_patient[15], char came_in_patient[15]) {
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    int minutes = -1; // Количество минут ожидания равно -1
    while (iter_element != NULL) { //Пока не дойдем до конца списка
        if (strcmp(iter_element->surname, waiting_patient) == 0) {
            // Если это пациент, который ожидает приема, то обнуляем число минут (Значит первый пациент найден)
            minutes = 0;
        }

        if (strcmp(iter_element->surname, came_in_patient) == 0) {
            // Если нашли второго пациента, то возвращаем время ожидание
            return minutes;
        }

        if (minutes >= 0) { // Если ожидающий пациент найден, то добавляем 20 минут к времни ожидания
            minutes += 20;
        }

        iter_element = iter_element->next; // Переходим на новое звено
    }

    return -1 - (minutes >= 0); // Тут хитрая конструкция возвращающая -1, если ждущий пациент не найден и -2, если зашедший пациент не найден
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

    ListElement *first_element, *iter_element; // Создаем указатели на элементы списка: Начало списка и элемент для перебора
    first_element = iter_element = new ListElement; // Выделяем под них память

    while (not input_file.eof()) { // Читаем файл до тех пор, пока он не закончится
        ListElement *new_element = new ListElement; // создаем указатель на новый элемент и выделяем под него память
        input_file >> new_element->surname >> new_element->age; // Читаем из файла новое значение и записываем ее в структуру
        iter_element->next = new_element; // добавляем ссылку на следующий элемент

        iter_element = iter_element->next; // переходим на новый элемент
    }

    first_element = first_element->next; // Убираем заглавное звено

    print_table(first_element); // Печатаем таблицу

    char waiting_patient[15]; // Переменные для хранения фамилий пациентов
    char came_in_patient[15];

    cout << "Waiting patient surname:" << endl;
    cin >> waiting_patient; // Спрашиваем имена пациентов
    cout << "Now came in patient surname:" << endl;
    cin >> came_in_patient;

    int minutes = calc_time_before_reception(first_element, waiting_patient, came_in_patient); // Считаем время ожидания в минутах

    if (minutes >= 0) { // Если смогли посчитать, то выводим в красивом виде время ожидания
        cout << "Waiting time: " << minutes / 60 << " Hours " << minutes % 60 << " Minutes " << endl;
    } else if (minutes == -1) { // если не найден ожидающий пациент
        cout << "Waiting patient not found" << endl;
    } else if (minutes == -2) { // Если не найден только что зашедший пациент
        cout << "Came in patient not found" << endl;
    }
    return 0;
}