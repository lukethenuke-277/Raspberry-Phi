/*
Program: The 67 Code
Creation: Nov 30, 2025
Contributors: Luke Sedaca
Team: Raspberry phi [115]
Use: The code that goes into The 67
*/

// Library Init
#include <Alfredo_NoU3.h>
#include <PestoLink-Receive.h>

// Drive Train Motors Init
NoU_Motor frontLeftMotor(5);
NoU_Motor frontRightMotor(1);
NoU_Motor backLeftMotor(8);  
NoU_Motor backRightMotor(4);

// End Effector Motors Init
//NoU_Motor algaeIntakeMotors(5);
//NoU_Motor coralIntakeMotors(4);
//NoU_Motor coralIntakeMotors2(3);
// End Effector Arm Servos Init
//NoU_Servo leftArmServo(1);

// Elevator Servos Init
 NoU_Servo rightElevatorServo(3);
//NoU_Servo leftElevatorServo(4);
unsigned Speed = 1;
// Drive Train Init
NoU_Drivetrain drivetrain(&frontLeftMotor, &frontRightMotor, &backLeftMotor, &backRightMotor);

float rightElevatorServoDEG = 0;
//float leftElevatorServoDEG = 180;

void setup() {
  NoU3.begin();
  PestoLink.begin("according to all known laws of aviation");



  // coralIntakeMotors.setInverted(true);
     frontRightMotor.setInverted(false);
     frontLeftMotor.setInverted(true);
     backLeftMotor.setInverted(true);
     backRightMotor.setInverted(false);
     rightElevatorServo.write(100);
}


void loop() {
  if (PestoLink.update()) {
    // Get battery voltage and display on PestoLink
    float batteryVoltage = NoU3.getBatteryVoltage();
    PestoLink.printBatteryVoltage(batteryVoltage);

   
        if (PestoLink.keyHeld(Key::T)) {
        rightElevatorServoDEG = 210;
      }

       else if (PestoLink.keyHeld(Key::U)) {
       rightElevatorServoDEG = 120;
    //   leftElevatorServoDEG -= 1;
     }    else if (PestoLink.keyHeld(Key::I)) {
          rightElevatorServoDEG = 10;
    //   leftElevatorServoDEG += 1;
     }
  
    

    // // Update elevator servos
    // leftElevatorServo.write(leftElevatorServoDEG);
     rightElevatorServo.write(rightElevatorServoDEG);

    //---Drive Train Code---
    // Axis Init
    float horizontalAxis = 0;
    float verticalAxis = 0;
    float rotationalAxis = 0;

    // Retrieve 3 axes from PestoLink and set it to given axis
    horizontalAxis = 1 * PestoLink.getAxis(0);
    verticalAxis = -1 * PestoLink.getAxis(1);
    rotationalAxis = -1 * PestoLink.getAxis(2);

    // Apply axes to drive train
    drivetrain.holonomicDrive(horizontalAxis, verticalAxis, rotationalAxis);

  } else {
    drivetrain.curvatureDrive(0, 0); // Stops drifting after code uploads
    PestoLink.update(); // Required piece of code to update robot on pestolink values
  }
}
