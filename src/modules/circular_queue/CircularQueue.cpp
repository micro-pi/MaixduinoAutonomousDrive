#include "CircularQueue.h"

template <class T>
CircularQueue<T>::CircularQueue(const uint16_t size) {
  if (size > 0) {
    values = new T[size];
  } else {
    values = nullptr;
  }
  this->size = size;
  this->front = -1;
  this->rear = -1;
}

template <class T>
CircularQueue<T>::~CircularQueue(void) {
  if (nullptr != values) {
    delete[] values;
  }
}

template <class T>
bool CircularQueue<T>::enQueue(T &value) {
  if ((front == 0 && rear == size - 1) || (rear == (front - 1) % (size - 1))) {
    return false;
  } else if (front == -1) {
    front = 0;
    rear = 0;
    values[rear] = value;
  } else if (rear == size - 1 && front != 0) {
    rear = 0;
    values[rear] = value;
  } else {
    rear++;
    values[rear] = value;
  }

  return true;
}

template <class T>
bool CircularQueue<T>::deQueue(T &value) {
  if (front == -1) {
    return false;
  }

  value = values[front];
  if (front == rear) {
    front = -1;
    rear = -1;
  } else if (front == size - 1) {
    front = 0;
  } else {
    front++;
  }

  return true;
}

/*
 * In order not to edit this file every time you need to add a new template!
 */
#include "CircularQueueTemplates.h"
