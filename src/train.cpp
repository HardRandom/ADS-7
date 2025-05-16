// Copyright 2021 NNTU-CS
#include "train.h"
#include <stdexcept>

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
  if (first) {
    Car* currentCar = first->next;
    while (currentCar != first) {
      Car* tempCar = currentCar;
      currentCar = currentCar->next;
      delete tempCar;
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
  if (!first) return 0;
  Car* currentCar = first->next;
  int trainLength = 1;
  while (currentCar != first) {
    currentCar = currentCar->next;
    ++trainLength;
  }
  bool originalLightState = first->light;
  countOp = 0;
  int requiredIterations = originalLightState ? (trainLength + 1) : 2;
  for (int i = 0; i < requiredIterations; ++i) {
    first->light = !first->light;
    const Car* current = first;
    for (int j = 0; j < trainLength; ++j) {
      current = current->next;
      ++countOp;
    }
  }
  first->light = originalLightState;
  return trainLength;
}

int Train::getOpCount() {
  return countOp;
}
