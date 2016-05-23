#include "Arduino.h"
#include "Penpivot.h"

Penpivot::Penpivot()
{

}

// Public Methods implementation

void Penpivot::pivotLeft(float deg)
{
	// this code is reponsible for pivoting the artbot to the left
}

void Penpivot::pivotRight(float deg)
{
	// this code is reponsible for pivoting the artbot to the right
	// Only the methods within this file can call the protected methods
	// So the next line works 
	translateAngleToStepperSteps(55.2);
}

// Private Methods implementation

int translateAngleToStepperSteps(float angle)
{
	// this code translates the desired pivot angle
	// into stepper steps for each respective wheel.
	// For now, it just returns any integer
	return 1;
}