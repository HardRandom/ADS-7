// Copyright 2021 NNTU-CS
#include "train.h"
#include <stdexcept>

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (!first) return;
    Car* current = first;
    do {
        Car* temp = current;
        current = current->next;
        delete temp;
    } while (current != first);
}
void Train::addCar(bool light) {
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
int Train::getLength() {
    Car* start = first;
    start->light = true;
    int steps = 1;
    while (true) {
        Car* current = start;
        for (int i = 0; i < steps; i++) {
            current = current->next;
            countOp++;
        }
        if (current->light) {
            current->light = false;
            if (current != start) {
                for (int i = 0; i < steps; i++) {
                    current = current->prev;
                    countOp++;
                }
            }
            if (current == start && !current->light) {
                return steps;
            } else {
                steps++;
                start->light = true;
            }
        } else {
            steps++;
        }
    }
}
int Train::getOpCount() const {
    return countOp;
}
