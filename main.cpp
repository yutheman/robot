#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHServo.h>
//-----------------------------------MAKE LEFT MOTOR PERCENT NEGATIVE WHEN YOU WANT IT TO MOVE FORWARD-----------------
//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P1_0);
DigitalEncoder left_encoder(FEHIO::P1_1);
FEHMotor right_motor(FEHMotor::Motor1,12.0);
FEHMotor left_motor(FEHMotor::Motor0,12.0);
AnalogInputPin CdS_cell(FEHIO::P0_1);
FEHServo arm_base(FEHServo::Servo0);        //MAX VALUE = 2360, MINIMUM VALUE = 500

//microswitches
DigitalInputPin frontRight(FEHIO::P0_3);
DigitalInputPin frontLeft(FEHIO::P0_4);
DigitalInputPin backRight(FEHIO::P0_5);
DigitalInputPin backLeft(FEHIO::P0_6);

bool red;

void check_x_plus(float x_coordinate) //using RPS while robot is in the +x direction
{
    //check whether the robot is within an acceptable range
    while(RPS.X() < x_coordinate - 1 || RPS.X() > x_coordinate + 1)
    {
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction

            right_motor.SetPercent(-30);
            left_motor.SetPercent(-30);
            Sleep(1);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction

            right_motor.SetPercent(30);
            left_motor.SetPercent(30);
            Sleep(1);
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
            right_motor.SetPercent(-30);
            left_motor.SetPercent(-30);
            Sleep(1);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);

        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction

            right_motor.SetPercent(30);
            left_motor.SetPercent(30);
            Sleep(1);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
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

            right_motor.SetPercent(30);
            left_motor.SetPercent(30);
            Sleep(1);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction

            right_motor.SetPercent(-30);
            left_motor.SetPercent(-30);
            Sleep(1);
            right_motor.SetPercent(0);
            left_motor.SetPercent(0);
        }
    }
}

void check_heading(float heading) //using RPS
{

     if(heading ==0){
     while(RPS.Heading() < 180 || RPS.Heading() >180 &&( RPS.Heading() > 3 || RPS.Heading() < 357) )// || RPS.Heading() < heading - 357) //|| RPS.Heading() > heading +357)
        {
         if (RPS.Heading() < 180)
         {
             right_motor.SetPercent(10);
             left_motor.SetPercent(-10);
        }

      if (RPS.Heading() > 180)
      {
          right_motor.SetPercent(-10);
          left_motor.SetPercent(10);

            }

        }
     }
     else{
         while(RPS.Heading() < heading - 3 || RPS.Heading() > heading + 3)// || RPS.Heading() < heading - 357) //|| RPS.Heading() > heading +357)
            {
             if (RPS.Heading() < heading)
             {
                 right_motor.SetPercent(10);
                 left_motor.SetPercent(-10);
            }

          if (RPS.Heading() > heading)
          {
              right_motor.SetPercent(-10);
              left_motor.SetPercent(10);
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
     LCD.WriteLine(left_encoder.Counts() + " <-left right-> "+ right_encoder.Counts());
     LCD.WriteLine(left_encoder.Counts());
     Sleep(100);
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
    while (off){
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
    float x = CdS_cell.Value();
    while (true){
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

int main(void)
{
    float x,y;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );
    //set up the arm
    arm_base.SetMin(500);
    arm_base.SetMax(2360);
    arm_base.SetDegree(5);
    while( wait_for_light() )
    {
        //from start position to button
        move_forward(15.,465);
        turn_left(15.,225); //face the wall (90 degree turn)
        move_forward(15., 162); //move under the red/blue light
        check_red_or_blue();
        Sleep(1000);
        move_forward(30.,270); //position robot under ramp
        turn_left(30.,225); //face the ramp
        move_forward(50.,1000); //move up the ramp, 1944
        turn_right(30, 30); //turn slightly to face the button
        move_forward(30,200); //aligning the robot with the button
      //  turn_left(30,50); //turn the robot so that it faces the button
        move_forward(30,770); //cover remaining distance to the button
        Sleep(6.0);

        //getting to the lever
        move_forward(-30., 603); //move backward 17.5 inches
        turn_left(30.,225);
        move_forward(30., 570);
        //rotate the wheel
        arm_base.SetDegree(90);
        Sleep(1.0);
        move_forward(-30,100);
        arm_base.SetDegree(5);  //reset so that the arm is facing up

        //get to the core sample
        move_forward(-30,608); //move away from the lever
        turn_right(30,140); //turn slightly right to face the sample
        move_forward(30,700); //move forward to the sample

        //adjust the servo arm to get the sample
        arm_base.SetDegree(145);
        Sleep(2.0);
        move_forward(30,150);
        arm_base.SetDegree(100);
        Sleep(2.0);
        move_forward(-60,284); //back up to take out the core sample
       // arm_base.SetDegree(70);
        turn_left(30,390); //turn to face the antenna
        move_forward(30,1600); //move forward all the way down the ramp to touch the antenna
        turn_right(30,225); //turn right to face the red/blue light
        move_forward(30,648); //move forward to align under the light

        if (red){
            turn_right(30,140);
            move_forward(30,344);
        } else {
            turn_left(30,140);
            move_forward(30,344);
        }


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


