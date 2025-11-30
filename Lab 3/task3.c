/*
Implement the function that MSP430 use DTC mode to get multiple ADC readings from one channel.
(The state machine of DTC one block mode is shown in the Figure 22-10.)
• Configure ADC10 as “repeat single channel mode” via A1, using internal reference 2.5V.
• Enable MSC bit to set ADC work continuously.
• Configure the ADC DTC mode as “one block” mode, 16 readings (n = 0x10) and assigned the read
value to an array with 16 elements (as shown in Lecture 4, page 34).
• Handle the ADC DTC reading in the interrupt and calculate the average value of the ADC reading
in the defined array.
• Restart the DTC in the ADC interrupt.
*/


#include <msp430g2553.h>

volatile unsigned int buffer[16];
volatile unsigned int avg;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR |= BIT0;

    // ADC base config
    ADC10CTL0 = SREF_1 | ADC10SHT_2 | REFON | REF2_5V |
                 ADC10ON | ADC10IE | MSC;
    ADC10CTL1 = INCH_1 | CONSEQ_2;      // repeat single channel A1
    ADC10AE0 |= BIT1;

    // DTC: 16 transfers, start address = buffer
    ADC10DTC1 = 0x10;
    ADC10SA   = (unsigned int) buffer;

    ADC10CTL0 |= ENC | ADC10SC;

    __bis_SR_register(GIE);

    while (1);
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    unsigned long sum = 0;

    for (int i = 0; i < 16; i++)
        sum += buffer[i];

    avg = sum >> 4;             // /16

    if (avg > 0x266)            // 1.5V
        P1OUT |= BIT0;
    else
        P1OUT &= ~BIT0;

    // restart DTC block
    ADC10SA = (unsigned int) buffer;
    ADC10CTL0 |= ADC10SC;
}
