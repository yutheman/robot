#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHServo.h>
#include <math.h>
//-----------------------------------MAKE LEFT MOTOR PERCENT NEGATIVE WHEN YOU WANT IT TO MOVE FORWARD-----------------
//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P1_0);
DigitalEncoder left_encoder(FEHIO::P1_1);
FEHMotor right_motor(FEHMotor::Motor1,12.0);
FEHMotor left_motor(FEHMotor::Motor0,12.0);
AnalogInputPin CdS_cell(FEHIO::P0_1);
FEHServo arm_base(FEHServo::Servo0);//MAX VALUE = 2360, MINIMUM VALUE = 500
FEHServo hand_base(FEHServo::Servo1);

//microswitches
DigitalInputPin frontRight(FEHIO::P2_0);
DigitalInputPin frontLeft(FEHIO::P2_1);
DigitalInputPin backRight(FEHIO::P2_2);
DigitalInputPin backLeft(FEHIO::P2_3);

bool red;

void check_x_plus(float x_coordinate) //using RPS while robot is in the +x direction
{
    //check whether the robot is within an acceptable range
    while(RPS.X() < x_coordinate - 1 || RPS.X() > x_coordinate + 1)
    {
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction

            right_motor.SetPercent(-25);
            left_motor.SetPercent(25);
            Sleep(20);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction

            right_motor.SetPercent(25);
            left_motor.SetPercent(-25);
            Sleep(20);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
    }
}

void check_x_minus(float x_coordinate) //using RPS while robot is in the -x direction
{
    //check whether the robot is within an acceptable range
    while(RPS.X() < x_coordinate - 1 || RPS.X() > x_coordinate + 1)
    {
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction

            right_motor.SetPercent(25);
            left_motor.SetPercent(-25);
            Sleep(20);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction

            right_motor.SetPercent(-15);
            left_motor.SetPercent(15);
            Sleep(20);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
    }
}

void check_y_minus(float y_coordinate) //using RPS while robot is in the -y direction
{
    //check whether the robot is within an acceptable range
    while(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1)
    {
        if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(25);
            left_motor.SetPercent(-25);
            Sleep(20);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);

        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction

            right_motor.SetPercent(-25);
            left_motor.SetPercent(25);
            Sleep(20);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
    }
}

void check_y_minus_timeout(float y_coordinate) //using RPS while robot is in the -y direction
{
    float timeOut = TimeNow();
    //check whether the robot is within an acceptable range
    while(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1)
    {
        if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            right_motor.SetPercent(25);
            left_motor.SetPercent(-25);
            Sleep(20);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);

        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction

            right_motor.SetPercent(-25);
            left_motor.SetPercent(25);
            Sleep(20);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }

        if(TimeNow()-timeOut >= 5.0){
            break;
        }
    }
}

void check_y_plus(float y_coordinate) //using RPS while robot is in the +y direction
{
    //check whether the robot is within an acceptable range
    while(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1)
    {
        if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction

            right_motor.SetPercent(-25);
            left_motor.SetPercent(25);
            Sleep(100);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction

            right_motor.SetPercent(25);
            left_motor.SetPercent(-25);
            Sleep(100);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
    }
}

void check_heading(float heading, float timeOut) //using RPS
{
    int to1 = TimeNow();

     if(heading ==0){
     while((RPS.Heading() < 180 || RPS.Heading() >180) && RPS.Heading() > 4 || RPS.Heading() < 356)// || RPS.Heading() < heading - 357) //|| RPS.Heading() > heading +357)
        {
         if (RPS.Heading() > 180)
         {
             right_motor.SetPercent(12);
             left_motor.SetPercent(12);
             Sleep(10);
        }

      if (RPS.Heading() < 180)
      {
          right_motor.SetPercent(-12);
          left_motor.SetPercent(-12);
          Sleep(10);

            }
      if(TimeNow() -to1 >= timeOut){
        break;
      }

        }
     }
     else{
         while(RPS.Heading() < heading - 4 || RPS.Heading() > heading + 4)// || RPS.Heading() < heading - 357) //|| RPS.Heading() > heading +357)
            {
             if (RPS.Heading() < heading)
             {
                 right_motor.SetPercent(12);
                 left_motor.SetPercent(12);
                 Sleep(10);

            }

          if (RPS.Heading() > heading)
          {
              right_motor.SetPercent(-12);
              left_motor.SetPercent(-12);
              Sleep(10);

                }
          if(TimeNow() -to1 >= timeOut){
            break;
          }

    }
     }
     right_motor.SetPercent(0);
     left_motor.SetPercent(0);
    //you will need to fill out this one yourself and take into account
    //the edge conditions (when you want the robot to go to 0 degrees
    //or close to 0 degrees)
}

void move_forward(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(-percent);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts){
//     LCD.WriteLine(left_encoder.Counts() + " <-left right-> "+ right_encoder.Counts());
//     LCD.WriteLine(left_encoder.Counts());
     //Sleep(100);
    }

    //Turn off motors       `
    right_motor.Stop();
    left_motor.Stop();
}
void read_color(){
    float x = CdS_cell.Value();
    LCD.WriteLine(x);
    Sleep(1.);
}

void turn_right(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    //hint: set right motor backwards, left motor forwards

    right_motor.SetPercent(-20);
    left_motor.SetPercent(-20);
    //While the average of the left and right encoder is less than counts,
    //keep running motors

     while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void turn_left(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent

    right_motor.SetPercent(20);
    left_motor.SetPercent(20);

    //While the average of the left and right encoder is less than counts,
    //keep running motors

    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

bool wait_for_light(){
    bool off = true;
    float timeOut = TimeNow();
    while (off){
        if (TimeNow() - timeOut >= 30.){
            off= false;
        }
        float x = CdS_cell.Value();
        if (x < 1) {
            off = false;
         }
    }
    return true;
}
void rotate_arm(int degrees){
    //arm_base
}

void check_red_or_blue(){
    float timeOut = TimeNow();
    float x = CdS_cell.Value();
    while (true){
        if(TimeNow()-timeOut >= 30.){
            break;
        }

    if (x < 0.4){
        LCD.Clear(FEHLCD::Red);
        red = true;
        break;
    } else {
        LCD.Clear(FEHLCD::Blue);
        red = false;
        break;
    }
    }
}


void moveUntilWallFront(int percent){
    //Reset encoder counts

    float timeOut = TimeNow();
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(-percent);

    //keep moving until both front bumpers are closed
    while (!(frontLeft.Value() == 0
             && frontRight.Value() == 0)){
        if(TimeNow() - timeOut >= 10){
            break;
        }

    }
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void moveUntilWallBack(int percent){
    //Reset encoder counts
    float timeOut = TimeNow();
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(-percent);

    //keep moving until both front bumpers are closed
    while (!(backLeft.Value() == 0 && backRight.Value() == 0)){
        if(TimeNow() - timeOut >= 10){
            break;
        }

    }
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

int main(void)
{
    float x,y;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );
    RPS.InitializeTouchMenu();
    //set up the arm
    arm_base.SetMin(500);
    arm_base.SetMax(2360);
    arm_base.SetDegree(5);

    hand_base.SetMin(600);
    hand_base.SetMax(2360);
    hand_base.SetDegree(115);

    while( wait_for_light() )
    {

//        //from start position to button
//        move_forward(15,500);
//        turn_left(15.,260); //face the wall (90 degree turn)
//        move_forward(15., 170); //move under the red/blue light
//        check_red_or_blue();
//        Sleep(1000);
//        turn_left(15,20);

//ENHANCED: read light
        move_forward(20,300);
        check_y_minus(18.2);//yval of light
        turn_left(20,250);
        move_forward(15,130);
        check_x_plus(10.2);//xval of light
        check_red_or_blue();
        //check_heading(5,3);
        turn_left(20,7);
        //check_heading(340,3);

//ENHANCED: turn satelite
        moveUntilWallFront(30);
        move_forward(-30,250);
        check_x_plus(24.3);//xval of antenna
        turn_right(7,265);
        move_forward(-30,50);
        arm_base.SetDegree(90);
        move_forward(30,450);
        //check_y_minus(12);//yval of fully pushed antenna
        check_y_minus_timeout(12);
        arm_base.SetDegree(120);
        move_forward(-50,270);
        check_y_minus(20);//yval of being in the clear
        arm_base.SetDegree(5);
        check_heading(0,10.);
        check_x_plus(19);//xval of being below the ramp
        turn_left(30.,235);

//Toggle LEVER
        move_forward(50,1100);
        check_y_plus(49.5);
        turn_left(30,250);
        check_x_minus(12);//xval of lever
        move_forward(30,50);
        arm_base.SetDegree(105);
        Sleep(500);
        move_forward(-30,100);
        arm_base.SetDegree(5);
        moveUntilWallBack(-30);

        move_forward(30,150); //aligning the robot with the button
        turn_right(30,250);
        moveUntilWallFront(30);
        move_forward(-15,250);
        arm_base.SetDegree(110);
        Sleep(1000);
        move_forward(30,170);
        Sleep(6000);
        check_y_plus(50);
        turn_left(30,250);
        //moveUntilWallBack(20);

////ENHANCED: hitting button
//        move_forward(50.,1100);
//        turn_right(30, 280); //turn slightly to face the button
//        moveUntilWallFront(30);
//        move_forward(-30,150); //aligning the robot with the button
//        turn_left(30,250);
//        moveUntilWallFront(30);
//        move_forward(-15,250);
//        arm_base.SetDegree(110);
//        Sleep(1000);
//        move_forward(30,100);
//        Sleep(6000);

////ENHANCED: Toggle Lever
//        //check_heading(0,2);
//        move_forward(-30., 520);
//        check_y_plus(50);//yval of lever
//        arm_base.SetDegree(5);
//        turn_left(30.,240);
//        check_heading(180,3);
//        moveUntilWallBack(-20);
//        move_forward(30., 660);
//        check_x_minus(12);//xval of lever
//        move_forward(30,50);
//        arm_base.SetDegree(105);
//        Sleep(500);
//        move_forward(-30,100);
//        arm_base.SetDegree(5);
//        check_heading(180,5);

//ENHANCED: Gather Core Sample
        moveUntilWallBack(-30);
        move_forward(30,150);
        check_x_minus(29);//xval of core alignment
        Sleep(2000);
        turn_right(30,30);
        //float angle = atan(18/-22.5); //(lever 'YValue')(Lever 'XValue)
       // check_heading(155,10.);
        check_heading(137,10);
        move_forward(30,500);
        arm_base.SetDegree(145);
        hand_base.SetDegree(130);
        Sleep(2.0);
        move_forward(50,300);
        arm_base.SetDegree(120);
        Sleep(2.0);
        move_forward(-60,400);
//        if(RPS.X()==-1){
//            move_forward(30,20);
//            move_forward(-60,500);
//        }
        check_x_minus(20);//xval of ramp
        turn_left(20,200);
        check_heading(270,10.);

//ENHANCED: Drop Sample into Bucket
        move_forward(30,800);
        check_y_minus(20);//yval of location to dump sample
        if(red){
            turn_right(20,140);
            move_forward(30,320);
            hand_base.SetDegree(0);

        }
        else{
            turn_right(20,250);
            move_forward(30,200);
            hand_base.SetDegree(0);
        }
        Sleep(1000);
        arm_base.SetDegree(0);

//ENHANCED: Push Final Button
        move_forward(-30,50);
        check_heading(170,3);
        moveUntilWallFront(30);
        hand_base.SetDegree(110);
        move_forward(-30,30);
        turn_left(20,250);
        moveUntilWallBack(-30);


//        //from start position to button
//        move_forward(15,500);
//        turn_left(15.,260); //face the wall (90 degree turn)
//        move_forward(15., 170); //move under the red/blue light
//        check_red_or_blue();
//        Sleep(1000);
//        turn_left(15,20);

//        //from start position to button
//        move_forward(15,500);
//        turn_left(15.,260); //face the wall (90 degree turn)
//        move_forward(15., 170); //move under the red/blue light
//        check_red_or_blue();
//        Sleep(1000);
//        turn_left(15,20);


//        //move away from satellite and align with the left wall
//        move_forward(-30,325);
//        turn_right(7,260);
//        arm_base.SetDegree(90);
//        Sleep(1000);
//        move_forward(30,450);
//        arm_base.SetDegree(110);
//        Sleep(1000);
//        move_forward(-50,320);
//        arm_base.SetDegree(5);
//        check_heading(0);
//        move_forward(-30,70);


//Hitting Final button
        //        move_forward(-20,1000);
        //        Sleep(3000);
        //        move_forward(20,100);
        //        turn_right(30  ,250);
        //        move_forward(-20,800);



//        turn_left(30.,245); //face the ramp
//        move_forward(50.,1000); //move up the ramp, 1944
//        turn_right(30, 250); //turn slightly to face the button
//        moveUntilWallFront(30);
//        move_forward(-30,60); //aligning the robot with the button
//        turn_left(30,250);
//        moveUntilWallFront(30);
//        move_forward(-30,200);
//        arm_base.SetDegree(110);
//        move_forward(30,200);




//        //getting to the lever
//        move_forward(-30., 570); //move backward 17.5 inches
//        arm_base.SetDegree(5);
//        turn_left(30.,240);
//        move_forward(30., 650);
//        //trigger the lever
//        arm_base.SetDegree(105);
//        Sleep(1.0);
//        move_forward(-30,100);
//        arm_base.SetDegree(5);  //reset so that the arm is facing up



//        //get to the core sample
//        moveUntilWallBack(-30);
//        move_forward(30,150); //move away from the lever
//        Sleep(2000);
//        turn_right(30,130); //turn slightly right to face the sample
//        move_forward(30,700); //move forward to the sample

//        //adjust the servo arm to get the sample
//        arm_base.SetDegree(145);
//        Sleep(2.0);
//        move_forward(30,150);
//        arm_base.SetDegree(120);
//        Sleep(2.0);
//        move_forward(-60,600); //back up to take out the core sample
//        //arm_base.SetDegree(100);
//        turn_left(30,405); //turn to face the antenna

//  check_heading(0);

//        arm_base.SetDegree(100);
//        move_forward(30,1450);
//        Sleep(500);//move forward all the way down the ramp to touch the antenna
//        //turn_right(30.,30);
//        turn_right(30,100);
//        Sleep(500);
//        move_forward(30.,160);
//        Sleep(500);
//        arm_base.SetDegree(90);
//        arm_base.SetDegree(145);
//        Sleep(500);
//        arm_base.SetDegree(100);
//        arm_base.SetDegree(145);
//        arm_base.SetDegree(65);
//        arm_base.SetDegree(100);
//        arm_base.SetDegree(145);
//        arm_base.SetDegree(65);
//        arm_base.SetDegree(100);
//        arm_base.SetDegree(145);
//        arm_base.SetDegree(65);
//        move_forward(-30,100);
//        arm_base.SetDegree(90);
//        Sleep(1000);
//        arm_base.SetDegree(0);
//        move_forward(-30, 100);
//        turn_left(30,200);
//        move_forward(30,450);


//        if (red){
//            turn_right(30,140);
//            move_forward(30,344);
//            arm_base.SetDegree(145);
//        } else {
//            turn_left(30,140);
//            move_forward(30,344);
//            arm_base.SetDegree(145);
//        }
//        arm_base.SetDegree(45);

//        //get to the color
//        move_forward(-30,325); //reverse so that the robot is positioned above the ramp
//        turn_left(30,225); //to face the ramp
//        move_forward(30,1100); //move down ramp
//        turn_right(30, 225); //face the left wall
//        move_forward(30, 290); //move so that the CdS cell is above the light
//        //call function to determine the light (whether it is red or blue)

}




    return 0;
}
