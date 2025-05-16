// Copyright 2021 NNTU-CS
#include "train.h"
#include <iostream>

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
    if (!first) return 0;

    Car* start = first;
    start->light = true;  // помечаем начальный вагон
    countOp++;

    int steps = 1;  // начинаем с 1, т.к. уже сделали шаг

    while (true) {
        // Идём вперёд на `steps` шагов
        Car* current = start;
        for (int i = 0; i < steps; i++) {
            current = current->next;
            countOp++;
        }

        // Если свет включён — выключаем и возвращаемся
        if (current->light) {
            current->light = false;
            countOp++;

            // Возвращаемся на `steps` шагов назад
            for (int i = 0; i < steps; i++) {
                current = current->prev;
                countOp++;
            }

            // Проверяем, выключен ли свет в стартовом вагоне
            if (!current->light) {
                return steps;  // нашли длину поезда
            } else {
                steps++;  // увеличиваем счётчик и повторяем
            }
        } else {
            steps++;  // если свет выключен, продолжаем идти дальше
        }
    }
}

int Train::getOpCount() const {
    return countOp;
}
