#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>

//Declarations for encoders & motors
ButtonBoard buttons(FEHIO::Bank3);
DigitalEncoder right_encoder(FEHIO::P3_0);
DigitalEncoder left_encoder(FEHIO::P3_1);
FEHMotor right_motor(FEHMotor::Motor1,12.0);
FEHMotor left_motor(FEHMotor::Motor0,12.0);

void move_forward(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);

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

    right_motor.SetPercent(20);
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

    right_motor.SetPercent(-20);
    left_motor.SetPercent(20);

    //While the average of the left and right encoder is less than counts,
    //keep running motors

    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}


int main(void)
{

    float x,y;

    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::White );

    while( true )
    {
        if( LCD.Touch(&x,&y) )
        {
            LCD.WriteLine( "Hello World!" );
            Sleep( 100 );
            Sleep(1000);
        }
    }
    return 0;
}
