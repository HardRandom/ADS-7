// Copyright 2021 NNTU-CS
#include "Train.h"
#include <iostream>
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
    countOp = 1;          
    int steps = 1;
    while (true) {
        // Идём вперёд на `steps` шагов
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
                start->light = true; 
                countOp++;
            }
        } else {
            steps++;
        }
    }
}

int Train::getOpCount() const {
    return countOp;
}
