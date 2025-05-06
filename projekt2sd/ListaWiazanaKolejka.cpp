#include <stdexcept>
#include "ListaWiazanaKolejka.h"

NodeP::NodeP(int wart, int pro) : dane(wart), priorytet(pro), next(nullptr) {}

void NodeP::showValue() const {
    std::cout << "(" << dane << ", priorytet: " << priorytet << ")";
}

PriorityQ::PriorityQ() : head(nullptr), end(nullptr), counter(0) {}

PriorityQ::~PriorityQ() {
    NodeP* curr = head;
    while (curr != nullptr) {
        NodeP* temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = nullptr;
    end = nullptr;
}

bool PriorityQ::isEmpty() const {
    return head == nullptr;
}

int PriorityQ::size() const {
    return counter;
}

void PriorityQ::push(int wart, int pro) {
    NodeP* newNode = new NodeP(wart, pro);

    if (isEmpty()) {
        head = end = newNode;
        counter++;
        return;
    }

    if (pro > head->priorytet) {
        newNode->next = head;
        head = newNode;
        counter++;
        return;
    }

    NodeP* current = head;
    while (current->next != nullptr && current->next->priorytet >= pro) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    if (current == end) {
        end = newNode;
    }

    counter++;
}

void PriorityQ::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Kolejka jest pusta!");
    }

    NodeP* temp = head;

    if (head == end) {
        head = end = nullptr;
    }
    else {
        head = head->next;
    }

    delete temp;
    counter--;
}

int PriorityQ::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Kolejka jest pusta!");
    }

    return head->dane;
}

bool PriorityQ::changeP(int wart, int newPro) {
    if (isEmpty()) {
        return false;
    }

    NodeP* current = head;
    NodeP* prev = nullptr;
    bool found = false;

    while (current != nullptr) {
        if (current->dane == wart) {
            found = true;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!found) {
        return false;
    }

    if (prev == nullptr) {
      
        head = current->next;
    }
    else {
        prev->next = current->next;
    }

    if (current == end) {
        end = prev;
    }

    int nodeData = current->dane;

    delete current;
    counter--;

    push(nodeData, newPro);

    return true;
}

void PriorityQ::show() const {
    if (isEmpty()) {
        std::cout << "Kolejka jest pusta." << std::endl;
        return;
    }

    std::cout << "Kolejka zawiera " << counter << " elementów: ";
    NodeP* curr = head;
    while (curr != nullptr) {
        curr->showValue();
        if (curr->next != nullptr) {
            std::cout << " -> ";
        }
        curr = curr->next;
    }
    std::cout << std::endl;
}