#include <cmath>
#include <cstdio>

#include <Utils.hpp>

void Utils::handleExit(int signal) {
    printf("\nChatbot: Auto-saved before exit. Goodbye!");
    exit(signal);
}

void Utils::sigmoid(double* x, int size) {
    for (int i = 0; i < size; i++) {
        x[i] = 1 / (1 + exp(-x[i]));
    }
}
