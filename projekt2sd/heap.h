#ifndef HEAP_H
#define HEAP_H

#include <vector>

template <typename T>
struct Element {
    int priority;
    T value;

    bool operator<(const Element<T>& other) const;
    bool operator>(const Element<T>& other) const;
};

template <typename T>
class HeapPriorityQueue {
private:
    std::vector<Element<T>> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void push(const T& value, int priority);
    void pop();
    const T& peek() const;
    size_t size() const;
    bool empty() const;
    bool changePriority(const T& value, int newPriority);
};

#endif // HEAP_H
