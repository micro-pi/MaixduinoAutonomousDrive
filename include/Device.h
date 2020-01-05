#ifndef DEVICE_H
#define DEVICE_H

/**
 * The base class for all the devices that will be added
 */
class Device {
public:
  /**
   * @brief Base function to init device
   */
  virtual void begin(void) = 0;
};

#endif