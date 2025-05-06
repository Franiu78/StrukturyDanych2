#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <fstream>
#include <string>
#include "heap.h"
#include "ListaWiazanaKolejka.h"

using namespace std;
using namespace std::chrono;

// Funkcja generująca losowe wartości
int getRandomValue(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(min, max);
}

// Funkcja zapisująca wyniki testów do pliku CSV
void saveResultsToCSV(const vector<int>& sizes, 
                     const vector<vector<long long>>& heapResults,
                     const vector<vector<long long>>& linkedResults) {
    
    ofstream csvFile("wyniki_testow_kolejek.csv");
    
    if (!csvFile.is_open()) {
        cerr << "Błąd: Nie można otworzyć pliku do zapisu wyników!" << endl;
        return;
    }
    
    // Nagłówki kolumn
    csvFile << "Rozmiar,Heap-Push,LinkedList-Push,Heap-Pop,LinkedList-Pop,Heap-Peek,"
           << "LinkedList-Peek,Heap-ChangePriority,LinkedList-ChangeP,Heap-Size,LinkedList-Size\n";
    
    // Zapisz dane
    for (size_t i = 0; i < sizes.size(); i++) {
        csvFile << sizes[i];
        
        for (int j = 0; j < 5; j++) {  // 5 operacji
            csvFile << "," << heapResults[i][j]
                   << "," << linkedResults[i][j];
        }
        csvFile << "\n";
    }
    
    csvFile.close();
    cout << "Wyniki zapisane do pliku 'wyniki_testow_kolejek.csv'" << endl;
}

int main() {
    cout << "===== TESTY WYDAJNOSCI KOLEJEK PRIORYTETOWYCH =====" << endl;
    
    // Liczba testów dla każdej operacji
    int numTests = 100;
    
    // Testujemy różne rozmiary kolejek
    vector<int> sizes = {100, 1000, 10000, 50000};
    
    // Wektory do przechowywania wyników
    vector<vector<long long>> heapResults(sizes.size(), vector<long long>(5, 0));
    vector<vector<long long>> linkedResults(sizes.size(), vector<long long>(5, 0));
    
    for (size_t i = 0; i < sizes.size(); i++) {
        int size = sizes[i];
        cout << "\n===================================" << endl;
        cout << "Testy dla rozmiaru: " << size << endl;
        cout << "===================================" << endl;
        
        HeapPriorityQueue<int> heapQueue;
        PriorityQ linkedQueue;
        
        long long totalTime;
        auto start = high_resolution_clock::now();
        auto stop = high_resolution_clock::now();
        
        // Najpierw wypełniamy obie kolejki tą samą zawartością
        vector<pair<int, int>> elements;
        for (int j = 0; j < size; j++) {
            int value = j;
            int priority = rand() % 100 + 1;  // Losowy priorytet od 1 do 100
            elements.push_back({value, priority});
        }
        
        for (const auto& elem : elements) {
            heapQueue.push(elem.first, elem.second);
            linkedQueue.push(elem.first, elem.second);
        }
        
        // Test 1: push (dodawanie elementu)
        totalTime = 0;
        for (int j = 0; j < numTests; j++) {
            int value = size + j;
            int priority = rand() % 100 + 1;  // Losowy priorytet od 1 do 100
            
            start = high_resolution_clock::now();
            heapQueue.push(value, priority);
            stop = high_resolution_clock::now();
            totalTime += duration_cast<nanoseconds>(stop - start).count();
            
            // Usuwamy dodany element, aby utrzymać rozmiar kolejki
            if (j < numTests - 1) {
                const int peekValue = heapQueue.peek();
                heapQueue.pop();
            }
        }
        heapResults[i][0] = totalTime / numTests;
        cout << "Heap dodaj element (push): " << heapResults[i][0] << " ns" << endl;
        
        totalTime = 0;
        for (int j = 0; j < numTests; j++) {
            int value = size + j;
            int priority = rand() % 100 + 1;  // Losowy priorytet od 1 do 100
            
            start = high_resolution_clock::now();
            linkedQueue.push(value, priority);
            stop = high_resolution_clock::now();
            totalTime += duration_cast<nanoseconds>(stop - start).count();
            
            // Usuwamy dodany element, aby utrzymać rozmiar kolejki
            if (j < numTests - 1) {
                linkedQueue.pop();
            }
        }
        linkedResults[i][0] = totalTime / numTests;
        cout << "LinkedList dodaj element (push): " << linkedResults[i][0] << " ns" << endl;
        
        // Test 2: pop (usuwanie elementu)
        // Najpierw dodajemy element, żeby mieć co usunąć
        totalTime = 0;
        for (int j = 0; j < numTests; j++) {
            int value = 2 * size + j;
            int priority = rand() % 100 + 1;  // Losowy priorytet od 1 do 100
            heapQueue.push(value, priority);
            
            start = high_resolution_clock::now();
            heapQueue.pop();
            stop = high_resolution_clock::now();
            totalTime += duration_cast<nanoseconds>(stop - start).count();
        }
        heapResults[i][1] = totalTime / numTests;
        cout << "Heap usun element (pop): " << heapResults[i][1] << " ns" << endl;
        
        totalTime = 0;
        for (int j = 0; j < numTests; j++) {
            int value = 2 * size + j;
            int priority = rand() % 100 + 1;  // Losowy priorytet od 1 do 100
            linkedQueue.push(value, priority);
            
            start = high_resolution_clock::now();
            linkedQueue.pop();
            stop = high_resolution_clock::now();
            totalTime += duration_cast<nanoseconds>(stop - start).count();
        }
        linkedResults[i][1] = totalTime / numTests;
        cout << "LinkedList usun element (pop): " << linkedResults[i][1] << " ns" << endl;
        
        // Test 3: peek (podglądanie elementu)
        totalTime = 0;
        for (int j = 0; j < numTests; j++) {
            start = high_resolution_clock::now();
            const int value = heapQueue.peek();
            stop = high_resolution_clock::now();
            totalTime += duration_cast<nanoseconds>(stop - start).count();
        }
        heapResults[i][2] = totalTime / numTests;
        cout << "Heap podglad elementu (peek): " << heapResults[i][2] << " ns" << endl;
        
        totalTime = 0;
        for (int j = 0; j < numTests; j++) {
            start = high_resolution_clock::now();
            const int value = linkedQueue.peek();
            stop = high_resolution_clock::now();
            totalTime += duration_cast<nanoseconds>(stop - start).count();
        }
        linkedResults[i][2] = totalTime / numTests;
        cout << "LinkedList podglad elementu (peek): " << linkedResults[i][2] << " ns" << endl;
        
        // Test 4: changePriority/changeP (zmiana priorytetu)
        totalTime = 0;
        for (int j = 0; j < numTests; j++) {
            int valueToChange = elements[j % elements.size()].first;
            int newPriority = rand() % 100 + 1;  // Losowy priorytet od 1 do 100
            
            start = high_resolution_clock::now();
            heapQueue.changePriority(valueToChange, newPriority);
            stop = high_resolution_clock::now();
            totalTime += duration_cast<nanoseconds>(stop - start).count();
        }
        heapResults[i][3] = totalTime / numTests;
        cout << "Heap zmiana priorytetu (changePriority): " << heapResults[i][3] << " ns" << endl;
        
        totalTime = 0;
        for (int j = 0; j < numTests; j++) {
            int valueToChange = elements[j % elements.size()].first;
            int newPriority = rand() % 100 + 1;  // Losowy priorytet od 1 do 100
            
            start = high_resolution_clock::now();
            linkedQueue.changeP(valueToChange, newPriority);
            stop = high_resolution_clock::now();
            totalTime += duration_cast<nanoseconds>(stop - start).count();
        }
        linkedResults[i][3] = totalTime / numTests;
        cout << "LinkedList zmiana priorytetu (changeP): " << linkedResults[i][3] << " ns" << endl;
        
        // Test 5: size (sprawdzanie rozmiaru)
        totalTime = 0;
        for (int j = 0; j < numTests; j++) {
            start = high_resolution_clock::now();
            size_t queueSize = heapQueue.size();
            stop = high_resolution_clock::now();
            totalTime += duration_cast<nanoseconds>(stop - start).count();
        }
        heapResults[i][4] = totalTime / numTests;
        cout << "Heap sprawdzanie rozmiaru (size): " << heapResults[i][4] << " ns" << endl;
        
        totalTime = 0;
        for (int j = 0; j < numTests; j++) {
            start = high_resolution_clock::now();
            int queueSize = linkedQueue.size();
            stop = high_resolution_clock::now();
            totalTime += duration_cast<nanoseconds>(stop - start).count();
        }
        linkedResults[i][4] = totalTime / numTests;
        cout << "LinkedList sprawdzanie rozmiaru (size): " << linkedResults[i][4] << " ns" << endl;
    }
    
    // Zapisz wyniki do pliku CSV
    saveResultsToCSV(sizes, heapResults, linkedResults);
    
    return 0;
}