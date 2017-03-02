#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
//-----------------------------------MAKE LEFT MOTOR PERCENT NEGATIVE WHEN YOU WANT IT TO MOVE FORWARD-----------------
//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P0_3);
DigitalEncoder left_encoder(FEHIO::P0_4); //broken pins is left encoder
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
void read_color(){
    while(true){
    float x = CdS_cell.Value();
    LCD.WriteLine(x);
    Sleep(1.);
    }
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

void check_red_or_blue(){
    float x = CdS_cell.Value();
    while (true){
    if (x < 1.1){
        LCD.Clear(FEHLCD::Red);
        break;
    } else {
        LCD.Clear(FEHLCD::Blue);
        break;
    }
    }
}

int main(void)
{
 Sleep(1.);
    float x,y;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );
    while( wait_for_light() )
    {
        //from start position to button
        move_forward(30.,465);
        turn_left(30.,225); //face the wall (90 degree turn)
        move_forward(30., 101); //position robot under ramp
        check_red_or_blue();
        Sleep(1000);
        move_forward(30.,304);
        turn_left(30.,225); //face the ramp
        move_forward(50.,1000); //move up the ramp, 1944
        turn_right(30, 100); //turn slightly to face the button
        move_forward(30,200); //aligning the robot with the button
      //  turn_left(30,50); //turn the robot so that it faces the button
        move_forward(30,770); //cover remaining distance to the button
        Sleep(6.0);

        //getitng to the lever
        move_forward(-30., 709); //move backward 17.5 inches
        turn_left(30.,225);
        move_forward(30., 420);

        //do something here to toggle the lever

        //get to the color
        move_forward(-30,405); //reverse so that the robot is positioned above the ramp
        turn_left(30,225); //to face the ramp
        move_forward(30,1100); //move down ramp
        turn_right(30, 225); //face the left wall
        move_forward(30, 290); //move so that the CdS cell is above the light
        //call function to determine the light (whether it is red or blue)

}

    return 0;
}
