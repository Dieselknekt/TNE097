/*
Write a program based on interrupts to turn on green LED (Port 1.6) when the switch (Port 1.3) is pressed and turn on red LED (Port 1.0) when the switch is not pressed on MSP430 launchpad.
*/

#include <msp430g2553.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    //Set LEDs (port 1.0 and port 1.6) as output and button (port 1.3) as input
    P1DIR |= BIT0 | BIT6;
    P1DIR &= ~BIT3;

    // Enable pull-up resistor on P1.3
    P1REN |= BIT3;
    P1OUT |= BIT3;

    // Initially turn on red LED and turn off green LED
    P1OUT |= BIT0;
    P1OUT &= ~BIT6;

    // Enable interrupt på P1.3, button press
    P1IE  |= BIT3;

    //set interrupt to trigger on falling edge (button press)
    P1IES |= BIT3;

    //clear interrupt flag on P1.3
    P1IFG &= ~BIT3;

    _BIS_SR(GIE);

    while (1)
    {
        __no_operation();
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    if (P1IFG & BIT3)
    {
        //if falling edge and button is pressed
        if (P1IES & BIT3)
        {
            // Falling edge: button press: green on, red off
            P1OUT |= BIT6;
            P1OUT &= ~BIT0;

            //change interrupt to rising edge (button release)
            P1IES &= ~BIT3;
        }
        else
        {
            // Rising edge: button release: red on, green off
            P1OUT |= BIT0;
            P1OUT &= ~BIT6;

            //change interrupt to falling edge (button press)
            P1IES |= BIT3;
        }

        //clear interrupt flag on P1.3
        P1IFG &= ~BIT3;
    }
}
