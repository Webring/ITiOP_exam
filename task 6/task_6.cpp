/*
 * Task 6:
 * В текстовом файле дана последовательность чисел.
 * Написать подпрограмму, которая в однонаправленном списке оставляет
 * только последнее вхождение заданного элемента.
 * Используя эту подпрограмму, преобразовать заданную последовательность
 * */
#include <iostream>
#include "fstream"

#define INPUT_FILE_PATH "../task 6/numbers.txt" // Имя входного файла
#define DELETE_FAILED 0 // костанта состояния для удаления элемента
#define VALUE_NOT_FOUND -1 // костанта состояния для удаления элемента

using namespace std; //Подключаем пространство имен

struct ListElement { // Структура для элемента списка
    int value; // значение
    ListElement *next = NULL; // указатель на следующий элемент
};

void print_list(ListElement *first_element) { //Функция вывода списка на экран
    ListElement *iter_element = first_element->next; // Создаем указатель и выделяем под данные память
    int total_amount = 0; // Количество элементов в списке
    while (iter_element != NULL) { //ПОка не кончится список
        cout << "| " << iter_element->value << endl; // Выводим на экран элемент
        total_amount++; // Увеличиваем число элментов на один
        iter_element = iter_element->next; //Переходим на след элмент
    }
    cout << "+amount: " << total_amount << endl; //Печатаем количество
}

ListElement *find_last_element_with_value(ListElement *first_element, int value) { //Функция поиска последнего вхождения элемента в список
    ListElement *iter_element = first_element; // Создаем указатель и выделяем под данные память
    ListElement *answer_element_pointer = NULL;// Создаем указатель для элемента ответа и выделяем под данные память
    while (iter_element != NULL) { //ПОка не кончится список
        if (iter_element->value == value) { //ПРоверяем тот ли элемент, что ищем
            answer_element_pointer = iter_element; //Записываем указатель в переменную
        }
        iter_element = iter_element->next;//Переходим на след элмент
    }
    return answer_element_pointer; // ВОзвращаем ответ
}

int delete_not_last_elements(ListElement *first_element, int value) { // Функция удаления не последних вхождений
    ListElement *last_element = find_last_element_with_value(first_element, value); //Получаем номер полсденего вхождения

    if (last_element == NULL) { // Проверяем, что такое число в списке есть
        return VALUE_NOT_FOUND; // Возвращаем ошибку
    }

    int number_of_deleted_values = 0; //Количество удаленых элементов

    ListElement *iter_element = first_element;// Создаем указатель и выделяем под данные память
    ListElement *temp_element; // указатель на удаляемый элемнт
    while (iter_element->next != NULL) {//ПОка не кончится список
        if (iter_element->next->value == value and iter_element->next != last_element) { //Если нашли не последнее вхождение
            temp_element = iter_element->next; //Запоминаем элемент
            iter_element->next = iter_element->next->next; // Меняем связи в списке
            delete temp_element; // Удаляем элемент

            number_of_deleted_values++; // Увеличиваем количество
        } else {
            iter_element = iter_element->next; // переходим на следующий элемент
        }
    }

    return number_of_deleted_values; // ВОзвращаем количество удаленых элментов
}

int main() {
    ifstream input_file(INPUT_FILE_PATH); // открываем файл для чтения

    if (not input_file.is_open()) { // Если файл не открыт
        cout << "Can't open input file" << endl; //Выводим сообщение об ошибке
        return 0; // Завершаем работу программы
    }

    if (input_file.peek() == ifstream::traits_type::eof()) { // Проверяем файл на пустоту
        cout << "file is empty" << endl; //Выводим сообщение об ошибке
        return 0; // Завершаем работу программы
    }

    ListElement *first_element, *iter_element; // Создаем указатели на элементы списка: Начало списка и элемент для перебора
    first_element = iter_element = new ListElement; // Выделяем под них память



    while (not input_file.eof()) { // Читаем файл до тех пор, пока он не закончится
        ListElement *new_element = new ListElement; // создаем указатель на новый элемент и  выделяем под него память
        input_file >> new_element->value; // Читаем из файла новое значение и записываем ее в структуру
        iter_element->next = new_element; // добавляем элемент в список

        iter_element = iter_element->next; // переходим на новый элемент
    }

    //first_element = first_element->next; // убераем заглавное звено

    int number_to_delete; // Переменная для хранения числа для удаления

    print_list(first_element); // Выводим список в консоль
    cout << "Number to delete?" << endl;
    cin >> number_to_delete; // Спрашиваем число
    int delete_result = delete_not_last_elements(first_element, number_to_delete); // Удаляем число из списка
    if (delete_result == VALUE_NOT_FOUND) { // Если число не найдено
        cout << "Value '" << number_to_delete << "' not found!" << endl;
    } else if (delete_result == DELETE_FAILED) { // Если элементы не были удалены
        cout << "Deleted not executed, because it's unique value" << endl;
        print_list(first_element);// Выводим список в консоль
    } else {
        cout << "Delete success" << endl;
        print_list(first_element);// Выводим список в консоль
    }

    return 0;
}