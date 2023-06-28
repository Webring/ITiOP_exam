#include "iostream"

using namespace std;

struct PriorityQueue {
    struct Element { // ��������� ��� �������� �������
        int key; // ��������
        Element *next = nullptr; // ��������� �� ��������� �������
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

