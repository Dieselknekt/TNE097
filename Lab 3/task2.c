/*
Task 2.1
Change the code from Task 1 such that
➢ The ADC sampling signal is controlled by the Timer0_A CCR1 output unit instead of ADC10SC.
➢ Configure the ADC working mode to “Repeat single channel mode” from A1 so that ADC10 can
be continuously triggered by Timer0_A output.
➢ Read the ADC10 value from ADC interrupts.
➢ When input voltage from A1 is higher than 1.5V, set P1.0, otherwise, reset P1.0.
*/

#include <msp430g2553.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    // ADC: A1, repeat single, 2.5V ref
    ADC10CTL0 = SREF_1 | ADC10SHT_2 | REFON | REF2_5V |
                 ADC10ON | ADC10IE;
    ADC10CTL1 = INCH_1 | CONSEQ_2 | SHS_1; // Trigger = TA0.1 output
    ADC10AE0 |= BIT1;

    P1DIR |= BIT0;

    // Timer0_A: CCR1 toggles sampling
    TACCR0  = 2048 - 1;
    TACCTL1 = OUTMOD_3;         // set/reset
    TACCR1  = 1024 - 1;
    TACTL   = TASSEL_2 | MC_1;  // SMCLK, up-mode

    ADC10CTL0 |= ENC;           // enable ADC

    __bis_SR_register(GIE);

    while (1);
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    if (ADC10MEM > 0x266)       // 1.5V
        P1OUT |= BIT0;
    else
        P1OUT &= ~BIT0;
}
