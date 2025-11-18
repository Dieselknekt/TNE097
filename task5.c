/*
Task 5
1. Change the code that the microcontroller IO Interrupt triggered as low ->high (i.e. rising edge).
2. Change the same function from Pin P1.1 to P1.2 and P1.4 to P1.5. After change, P1.5 should handle interrupt.
*/

#include <msp430g2553.h>
void main(void)
{
     WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

     //P1DIR |= 0x01 + 0x02 + 0x40; // Set P1.0, P1.1 and P1.6 to output direction
     P1DIR |= 0x01+0x04+0x40;
     //P1IE |= 0x10; // P1.4 interrupt enabled
     P1IE |= 0x20;
     //P1IES |= 0x10; // P1.4 falling edge //
     P1IES &= ~0x20;
     //P1OUT &= 0xFD; //1111 1101 //pull low
     P1OUT &= ~0x20;
     //P1IFG &= ~0x10; // P1.4 IFG cleared 
     P1IFG &= ~0x20;
     _BIS_SR(GIE); // Global Interrupt Enabled 

     while(1)
     {
        int a = 0;
        int b = 0;
        for(; a< 10000; a++)
        {
            for(;b < 10000; b++)
            { 
                _NOP(); 
            } 
        }
        //P1OUT ^= 0x02; //00000010
        P1OUT ^= 0x04;
        //P1OUT ^= 0x40;//0100 0000
        P1OUT ^= 0x40;
    }
} 

// Port 1 interrupt service routin
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
     P1OUT ^= 0x01; // P1.0 = toggle
     //P1IFG &= ~0x10; // P1.4 IFG cleared
     P1IFG &= ~0x20;
}
