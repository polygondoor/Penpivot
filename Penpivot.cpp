#include "Arduino.h"
#include "Penpivot.h"

#include <AccelStepper.h>
#include <AFMotor.h>

Penpivot::Penpivot(int stepsForFullRotation, float leftWheelDiameter, float rightWheelDiameter, float turtleDiameter)
{
	// set the necessary values
	_stepsForFullRotation = stepsForFullRotation;
	_leftWheelDiameter = leftWheelDiameter;
	_rightWheelDiameter = rightWheelDiameter;
	_turtleDiameter = turtleDiameter;

	// now set the secondary values
	_leftWheelTravelPerTurn = _leftWheelDiameter * 3.1416;
	_rightWheelTravelPerTurn = _rightWheelDiameter * 3.1416;

	// the turtle central axis
	_turtleTravelPerTurn = _turtleDiameter * 3.1416;

	// Create the AF_Stepper objects
	_motor1 = new AF_Stepper(_stepsForFullRotation, 1);
	_motor2 = new AF_Stepper(_stepsForFullRotation, 2);

	// motor steps can be changed to SINGLE, DOUBLE or INTERLEAVE or MICROSTEP
	_stepper1 = new AccelStepper( _motor1->onestep(FORWARD, DOUBLE),  _motor1->onestep(BACKWARD, DOUBLE));
	_stepper2 = new AccelStepper( _motor2->onestep(BACKWARD, DOUBLE), _motor2->onestep(FORWARD, DOUBLE));

	// set maximum speeds
	_stepper1->setMaxSpeed(1000);
    _stepper2->setMaxSpeed(1000);
}

// Public Methods implementation

bool Penpivot::hasFinishedCurrrentMove()
{	
	return ( (_stepper1->distanceToGo() == 0) && (_stepper2->distanceToGo() == 0) );
	// return true;
}

void Penpivot::continueMove()
{	
    _stepper1->runSpeedToPosition();
    _stepper2->runSpeedToPosition();
}

void Penpivot::pivotLeft(float deg) {
  
  //      distance travelled by the wheel    /   how many turns of small wheel  * steps per turn
  _leftPosition  = leftStepsToTurn(deg);
  _rightPosition = rightStepsToTurn(deg);
  
  _stepper2->move( _leftPosition );
  _stepper2->setSpeed( -400 );
  _stepper1->move( _rightPosition );
  _stepper1->setSpeed( 400 );
}

void Penpivot::pivotRight(float deg) {
  
  //      distance travelled by the wheel    /   how many turns of small wheel  * steps per turn
  _leftPosition  = leftStepsToTurn(deg);
  _rightPosition = rightStepsToTurn(deg);
  
  _stepper2->move( _leftPosition );
  _stepper2->setSpeed( 400 );
  _stepper1->move( _rightPosition );
  _stepper1->setSpeed( -400 );
}

void Penpivot::goFowards(float mm) {

  _leftPosition  = leftDistanceToSteps(mm);
  _rightPosition = rightDistanceToSteps(mm);
  
  _stepper1->move( _leftPosition );
  _stepper1->setSpeed( 400 );
  _stepper2->move( _rightPosition );
  _stepper2->setSpeed( 400 );
}

void Penpivot::goBackwards(float mm) {
  
  _leftPosition  = leftDistanceToSteps(mm);
  _rightPosition = rightDistanceToSteps(mm);
  
  _stepper1->move( _leftPosition );
  _stepper1->setSpeed( -400 );
  _stepper2->move( _rightPosition );
  _stepper2->setSpeed( -400 );
}

// Private Methods implementation

float Penpivot::leftStepsToTurn(float deg) {
  //      distance travelled by the wheel    /   how many turns of small wheel  * steps per rotation
  return (_turtleTravelPerTurn * (deg / 360)) / _leftWheelTravelPerTurn           *    _stepsForFullRotation;
}

float Penpivot::rightStepsToTurn(float deg) {
  //      distance travelled by the wheel    /   how many turns of small wheel  * steps per rotation
  return (_turtleTravelPerTurn * (deg / 360)) / _rightWheelTravelPerTurn           *    _stepsForFullRotation;
}

float Penpivot::leftDistanceToSteps(float mm){
  return mm / _leftWheelTravelPerTurn * _stepsForFullRotation;
}

float Penpivot::rightDistanceToSteps(float mm){
  return mm / _rightWheelTravelPerTurn * _stepsForFullRotation;
}


