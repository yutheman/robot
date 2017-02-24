#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
//-----------------------------------MAKE LEFT MOTOR PERCENT NEGATIVE WHEN YOU WANT IT TO MOVE FORWARD-----------------
//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P0_2);
DigitalEncoder left_encoder(FEHIO::P0_0); //broken pins is left encoder
FEHMotor right_motor(FEHMotor::Motor1,12.0);
FEHMotor left_motor(FEHMotor::Motor0,12.0);
AnalogInputPin CdS_cell(FEHIO::P0_1);

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
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
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
        LCD.WriteLine(x);
        if (x < 1) {
            off = false;
         }
    }
    return true;
}

int main(void)
{
 Sleep(1.);
    float x,y;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );
//    while (true){
//        float x = CdS_cell.Value();
//        LCD.WriteLine(x);
//        Sleep(1.0);
//    }
    while( wait_for_light() )
    {
        //from start position to button
        move_forward(30.,440); //move forward 13 inches
        turn_left(30.,225);
        move_forward(30., 405); //move forward 17.5 inches to the ramp
        turn_left(30.,225);
        move_forward(50.,1000); //move up the ramp, 1944
        move_forward(30,200); //aligning the robot with the button
      //  turn_left(30,50); //turn the robot so that it faces the button
        move_forward(30,800); //cover remaining distance to the button
        Sleep(6.0);

        //getitng to the lever
        move_forward(-30., 709); //move backward 17.5 inches
        turn_left(30.,225);
        move_forward(30., 648);
    }
    return 0;
}
