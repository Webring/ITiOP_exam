#include "priority_queue.h"

bool PriorityQueue::is_empty() {
    return main->next == nullptr;
}

void PriorityQueue::print() {
    if (is_empty()) {
        cout << "Queue is empty" << endl;
        return;
    }

    cout << "Queue:" << endl;
    Element *iter_element = main->next;
    while (iter_element != nullptr) {
        cout << " V\t" << iter_element->key << "\tV " << endl;
        iter_element = iter_element->next;
    }
}


int PriorityQueue::get() {
    if (not is_empty()) {
        Element *temp = main->next;
        main->next = main->next->next;
        return temp->key;
    }
}

void PriorityQueue::add(int new_value) {
    Element *new_element = new Element;
    new_element->key = new_value;

    if (is_empty()) {
        main->next = new_element;
        return;
    }

    Element *iter_element = main;
    while (iter_element->next != nullptr) {
        if (iter_element->next->key > new_value) {
            new_element->next = iter_element->next;
            iter_element->next = new_element;
            return;
        }
        iter_element = iter_element->next;
    }

    iter_element->next = new_element;
}