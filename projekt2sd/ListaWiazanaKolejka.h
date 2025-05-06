#ifndef LISTA_WIAZANA_KOLEJKA_H
#define LISTA_WIAZANA_KOLEJKA_H

#include <iostream>

struct NodeP {
    int dane;       
    int priorytet;   
    NodeP* next;   
    NodeP(int wart, int pro);
    void showValue() const;
};

class PriorityQ {
private:
    NodeP* head;
    NodeP* end;
    int counter;

public:

    PriorityQ();
    ~PriorityQ();
    bool isEmpty() const;
    int size() const;
    void push(int wart, int pro);
    void pop();
    int peek() const;
    bool changeP(int wart, int newPro);
    void show() const;
};

#endif 