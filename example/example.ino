#include <Penpivot.h>

Penpivot pivotingPen(2048, 63.6, 64, 112);

void setup() {  }

int currentStep = 0;
int leafCount = 0;

void loop()
{
    // Wait for both wheels to stop before going to next step
    if ( pivotingPen.hasFinishedCurrrentMove() ) {

      if (leafCount == 100) {
        // finished!
      } else {
        switch (currentStep) {
          
          case 0: pivotingPen.goFowards(80); break;
          case 1: pivotingPen.pivotLeft(90); break;
          case 2: pivotingPen.goFowards(5); break;
          case 3: pivotingPen.pivotLeft(90); break;
          case 4: pivotingPen.goFowards(80); break;
          case 5: pivotingPen.pivotRight(90); break;
          case 6: pivotingPen.goFowards(5); break;
          case 7: pivotingPen.pivotRight(90); break;
          case 8: 
            currentStep = -1;
            leafCount ++;
            break;
          
        }
      }
      currentStep++;
    }

    pivotingPen.continueMove();
}