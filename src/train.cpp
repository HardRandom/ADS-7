// Copyright 2021 NNTU-CS
#include "train.h"
#include <stdexcept>

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
    if (first) {
        Car* currentCar = first->next;
        while (currentCar != first) {
            Car* carToDelete = currentCar;
            currentCar = currentCar->next;
            delete carToDelete;
        }
        delete first;
    }
}
void Train::addCar(bool light) {
    Car* newCar = new Car{light, nullptr, nullptr};
    if (!first) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else {
        Car* lastCar = first->prev;
        lastCar->next = newCar;
        newCar->prev = lastCar;
        newCar->next = first;
        first->prev = newCar;
    }
}
int Train::getLength() {
    if (!first) throw std::logic_error("Поезд пуст");
    if (first->next == first) throw std::logic_error("Минимум 2 вагона");
    Car* currentCar = first->next;
    int trainLength = 1;
    while (currentCar != first) {
        currentCar = currentCar->next;
        ++trainLength;
    }
    bool originalLightState = first->light;
    countOp = 0;
    int requiredIterations = originalLightState ? (trainLength + 1) : 2;
    for (int iteration = 0; iteration < requiredIterations; ++iteration) {
        first->light = !first->light;
        const Car* currentCarPtr = first;
        for (int step = 0; step < trainLength; ++step) {
            currentCarPtr = currentCarPtr->next;
            ++countOp;
        }
    }
    first->light = originalLightState;
    return trainLength;
}
int Train::getOpCount() const {
    return countOp;
}
