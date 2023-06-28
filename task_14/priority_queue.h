#include "iostream"

using namespace std;

struct PriorityQueue {
    struct Element { // Структура для элемента очереди
        int key; // значение
        Element *next = nullptr; // указатель на следующий элемент
    };

    Element *main;

    PriorityQueue(){
        main = new Element;
    };

    bool is_empty();

    void add(int element);

    int get();

    void print();
};

