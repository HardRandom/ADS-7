#include "train.h"

Train::Train() : countOp(0), first(nullptr), tail(nullptr) {}

void Train::addCar(bool light)
{
  if (first) {
    Car* newCar = new Car{light, first, tail};
	tail->next = newCar;
	tail = newCar;
	first->prev = tail;
  } else {
      Car* newCar = new Car;
	  newCar->light = true;
	  newCar->next = newCar;
	  newCar->prev = newCar;
      tail = newCar;
	  first = newCar;
	}
}

int Train::getLength()
{
  if (first == nullptr) return 0;
  countOp = 0;
  int steps = 0;
  Car* current = first;
  bool first_light = first->light;
  while (true) {
    current = current->next;
    countOp++;
    steps++;
    if (current->light == first_light) {
      current->light = !first_light;
      int buffer = steps;
      while (steps) {
        steps--;
        current = current->prev;
        countOp++;
      }
    if (current->light != first_light)
      return buffer;
    }
  }
}

int Train::getOpCount()
{
  return countOp;
}

Train::~Train()
{
  while (first != tail) {
    first = first->next;
    delete first->prev;
  }
  delete first;
}
