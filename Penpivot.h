#ifndef Penpivot_h
#define Penpivot_h

#include "Arduino.h"
class Penpivot
{
  public:
    Penpivot();
    void pivotLeft(float deg);
    void pivotRight(float deg);
   
  private:
    int translateAngleToStepperSteps(float angle);
    
};

#endif