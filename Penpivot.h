#ifndef Penpivot_h
#define Penpivot_h

#include "Arduino.h"
#include <AccelStepper.h>
#include <AFMotor.h>

class Penpivot
{
  public:
    Penpivot(int stepsForFullRotation, float leftWheelDiameter, float rightWheelDiameter, float turtleDiameter);

    void initiate();

    void pivotLeft(float deg);
    void pivotRight(float deg);
    void goFowards(float mm);
	void goBackwards(float mm);
    bool hasFinishedCurrrentMove();
    void continueMove();
   
  private:
    int translateAngleToStepperSteps(float angle);
    float leftStepsToTurn(float deg);
    float rightStepsToTurn(float deg);
    float leftDistanceToSteps(float mm);
    float rightDistanceToSteps(float mm);

    int _leftPosition;
    int _rightPosition;

    // how far to go for one full rotation
    int _stepsForFullRotation = 2048;
    
    // wheel diameters
    float _leftWheelDiameter;
    float _rightWheelDiameter;
    // turtle diameter
    float _turtleDiameter;

    // these are calculated at instantiation time
    float _leftWheelTravelPerTurn;
	float _rightWheelTravelPerTurn;
	float _turtleTravelPerTurn;

	AF_Stepper * _motor1;
	AF_Stepper * _motor2;

	AccelStepper * _stepper1;
	AccelStepper * _stepper2;

	void forwardstep1();
	void backwardstep1();
	void forwardstep2();
	void backwardstep2();
};

#endif