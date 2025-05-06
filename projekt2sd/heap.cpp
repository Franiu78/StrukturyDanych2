#include "heap.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

using namespace std;
template <typename T>
bool Element<T>::operator<(const Element<T>& other) const {
    return priority < other.priority;
}

template <typename T>
bool Element<T>::operator>(const Element<T>& other) const {
    return priority > other.priority;
}

template <typename T>
void HeapPriorityQueue<T>::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index] < heap[parent]) {
            swap(heap[index], heap[parent]);
            index = parent;
        }
        else break;
    }
}

template <typename T>
void HeapPriorityQueue<T>::heapifyDown(int index) {
    int size = heap.size();
    while (index < size) {
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        int smallest = index;

        if (left < size && heap[left] < heap[smallest]) smallest = left;
        if (right < size && heap[right] < heap[smallest]) smallest = right;

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            index = smallest;
        }
        else break;
    }
}

template <typename T>
void HeapPriorityQueue<T>::push(const T& value, int priority) {
    heap.push_back({ priority, value });
    heapifyUp(heap.size() - 1);
}

template <typename T>
void HeapPriorityQueue<T>::pop() {
    if (heap.empty()) throw out_of_range("Queue is empty");
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
}

template <typename T>
const T& HeapPriorityQueue<T>::peek() const {
    if (heap.empty()) throw out_of_range("Queue is empty");
    return heap[0].value;
}

template <typename T>
size_t HeapPriorityQueue<T>::size() const {
    return heap.size();
}

template <typename T>
bool HeapPriorityQueue<T>::empty() const {
    return heap.empty();
}

template <typename T>
bool HeapPriorityQueue<T>::changePriority(const T& value, int newPriority) {
    for (size_t i = 0; i < heap.size(); ++i) {
        if (heap[i].value == value) {
            int oldPriority = heap[i].priority;
            heap[i].priority = newPriority;
            if (newPriority < oldPriority) heapifyUp(i);
            else heapifyDown(i);
            return true;
        }
    }
    return false;
}

template <typename T>
void HeapPriorityQueue<T>::print() const {
    cout << "Queue contents:\n";
    for (const auto& elem : heap) {
        cout << "(" << elem.value << ", " << elem.priority << ")\n";
    }
}


// Instancjowanie szablonu dla typów, których u¿yjesz:
template class HeapPriorityQueue<int>;
template struct Element<int>;
