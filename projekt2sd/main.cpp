#include <iostream>
#include "heap.h"
#include <string>

int main() {
    HeapPriorityQueue<std::string> queue;

    queue.push("A", 3);
    queue.push("B", 1);
    queue.push("C", 5);

    std::cout << "Peek: " << queue.peek() << "\n"; // B

    queue.changePriority("C", 0);
    std::cout << "Peek after priority change: " << queue.peek() << "\n"; // C

    while (!queue.empty()) {
        std::cout << "Pop: " << queue.peek() << "\n";
        queue.pop();
    }

    return 0;
}
