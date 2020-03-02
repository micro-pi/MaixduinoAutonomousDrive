#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "../Module.h"

template <class T>
class CircularQueue {
private:
  T *values;
  uint16_t size;
  int16_t rear;
  int16_t front;

public:
  CircularQueue(const uint16_t size);
  virtual ~CircularQueue(void);

  bool enQueue(T &value);
  bool deQueue(T &value);
};

#endif