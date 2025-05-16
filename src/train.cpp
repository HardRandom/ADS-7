// Copyright 2021 NNTU-CS
#include "train.h"
#include <iostream>

class Train {
private:
    struct Car {
        bool light;  // состояние лампочки (true = включена)
        Car* next;
        Car* prev;
    };
    int countOp;  // счётчик операций (переходов между вагонами)
    Car* first;   // указатель на первый вагон
public:
    Train() : countOp(0), first(nullptr) {}
    ~Train() {
        if (!first) return;
        Car* current = first;
        do {
            Car* temp = current;
            current = current->next;
            delete temp;
        } while (current != first);
    }
    void addCar(bool light) {
        Car* newCar = new Car{light, nullptr, nullptr};
        if (!first) {
            first = newCar;
            first->next = first;
            first->prev = first;
        } else {
            Car* last = first->prev;
            last->next = newCar;
            newCar->prev = last;
            newCar->next = first;
            first->prev = newCar;
        }
    }
    int getLength() {
        if (!first) return 0;
        Car* start = first;
        start->light = true;
        countOp++;
        int steps = 1;
        while (true) {
            Car* current = start;
            for (int i = 0; i < steps; i++) {
                current = current->next;
                countOp++;
            }
            if (current->light) {
                current->light = false;
                countOp++;
                for (int i = 0; i < steps; i++) {
                    current = current->prev;
                    countOp++;
                }
                if (!current->light) {
                    return steps;
                } else {
                    steps++;
                }
            } else {
                steps++;
            }
        }
    }
    int getOpCount() const {
        return countOp;
    }
};
