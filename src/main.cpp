/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\derek                                            */
/*    Created:      Fri Jun 25 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 3, 8, 10     
// Claw                 motor         6               
// ClawBump             bumper        A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;



int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  while(true) {
  
  if(!ClawBump.pressing()) {
    if(ClawBump.pressing()){
      Claw.spinFor(directionType::rev, 3, timeUnits::sec) ;
    }
  }
 }
  
  wait(20, msec);
  
}
