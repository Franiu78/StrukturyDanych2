#include <iostream>
#include "heap.h"
#include <string>

int main() {
    HeapPriorityQueue<int> queue;

    queue.push(3, 3);
    queue.push(1, 1);
    queue.push(5, 5);

    std::cout << "Peek: " << queue.peek() << "\n"; // 1

    queue.changePriority(5, 0);
    std::cout << "Peek after priority change: " << queue.peek() << "\n"; // 5
    queue.print();
    while (!queue.empty()) {
        std::cout << "Pop: " << queue.peek() << "\n";
        queue.pop();
    }

    return 0;
}
