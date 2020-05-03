#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include "../Module.h"

typedef struct {
  /**
   * Front
   */
  int16_t sonar1;

  /**
   * Right
   */
  int16_t sonar2;

  /**
   * Left
   */
  int16_t sonar3;

  /**
   * Back
   */
  int16_t sonar4;

  /**
   * Unused
   */
  int16_t sonar5;

  /**
   * Unused
   */
  int16_t sonar6;
} SonarsData;

class GlobalData : public Module {
private:
  SonarsData sonarsData;

public:
  /**
   * @brief Default constructor
   */
  GlobalData(const char *moduleName);
  ErrorCode initModule(void);
  void mainFunction(void);
  void setSonarsData(SonarsData &sonarsData);
  ~GlobalData(void);
};

#endif