#include <iostream>
#include <random>
#include "finnecore.h" // FinneCore.h
#include <thread>
#include <chrono>

void Engine() {
    std::cout << "FinneEngine --- Network" << std::endl;

    // Przykładowe użycie rand()
    int randomVal = rand();
    std::cout << "Random value: " << randomVal << std::endl;

    std::string result = FinnecoreGet("Beta 1.0", "Disable");
    std::cout << result << std::endl;
}
 
void NetworkAddapterEngine() {
    int randomVal = rand();
    std::cout << "Network Server ID: " << randomVal << std::endl;
}

void CPUhalt() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // zatrzymuje na 1 sekundę
}


int main() {
    NetworkAddapterEngine();
    std::cout << "=== FinneEngine ===" << std::endl;

    Engine();  // zamiast wywoływać main() wewnątrz Engine()

    std::cout << "=== FinneEngine ===" << std::endl;
    while (true) {
        CPUhalt();
    }
    std::cout << "Exit in code 1" << std::endl;

    return 1;
}
