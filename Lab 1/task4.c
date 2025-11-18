#include <msp430g2553.h> 

void main(void) 
{ 
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer 

    P1DIR |= 0x01 + 0x02 + 0x40;  // Set P1.0, P1.1 and P1.6 as outputs

    P1IE  |= 0x10;    // P1.4 interrupt enabled 
    P1IES |= 0x10;    // P1.4 falling edge 

    // P1OUT &= 0xFD; //1111 1101 //pull low

    P1IFG &= ~0x10;   // P1.4 IFG cleared 

    _BIS_SR(GIE);     // Global Interrupt Enabled 

    while(1) 
    { 
        int a = 0; 
        int b = 0; 

        for(; a < 10000; a++) 
        { 
            for(; b < 10000; b++) 
            { 
                _NOP(); 
            } 
        } 

        P1OUT ^= 0x02;  // 0000 0010  (toggle P1.1) 
        P1OUT ^= 0x40;  // 0100 0000  (toggle P1.6) 
    } 
} 

// Port 1 interrupt service routine 
#pragma vector=PORT1_VECTOR 
__interrupt void Port_1(void) 
{ 
    P1OUT ^= 0x01;     // P1.0 = toggle 
    P1IFG &= ~0x10;    // P1.4 IFG cleared 
} 
