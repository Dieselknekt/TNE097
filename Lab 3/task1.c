/*
Task 1.1 Modify the code so that MSP430 measures analog voltage from channel A5 and change
reference voltage to internal reference 2.5V.

Task 1.2 Modify the code so that MSP430 uses interrupt to read the measured voltage. If the measured
voltage is higher than 1.5V turn on RED LED by setting P1.0 (to 1). Otherwise, reset P1.0 (to 0). 
*/

#include <msp430g2553.h>

void main(void)
{
    // WDTCTL = WDTPW | WDTHOLD; // Stop WDT
    WDTCTL = WDTPW | WDTHOLD;
    //ADC10CTL0 = SREF_1 + ADC10SHT_2 + REFON + ADC10ON;
    ADC10CTL0 = SREF_1 | ADC10SHT_2 | REFON | REF2_5V | ADC10ON;
    //ADC10CTL1 = INCH_1;          // input A1, pin P1.1  
    ADC10CTL1 = INCH_5;          // A5
    //ADC10AE0 |= 0x02;            // Select ADC function for pin P1.1
    ADC10AE0 |= BIT5;            // Enable P1.5
    //P1DIR |= 0x01;            // Set P1.0 to output direction
    P1DIR |= BIT0;

    /*for(;;)
    {
      ADC10CTL0 |= ENC | ADC10SC;  // Sampling and conversion start
      while (ADC10CTL1 & ADC10BUSY) {}  //wait until the conversion is ready
  
                                //Testing ADC10BUSY bit in ADC10CTL1
      if (ADC10MEM < 0x88)        // ADC10MEM = A1 > V?
        P1OUT &= ~0x01;      // Clear P1.0 LED off
      else
        P1OUT |= 0x01;          // Set P1.0 LED on
    }
    
    */
    while (1)
    {
        ADC10CTL0 |= ENC | ADC10SC;
        while (ADC10CTL1 & ADC10BUSY);

        if (ADC10MEM > 0x266)    // 1.5 V * (1023/2.5V) ≈ 1.5/2.5 * 1023 = 613 ≈ 0x266
            P1OUT |= BIT0;
        else
            P1OUT &= ~BIT0;
    }
}


/* task 1.2:


#include <msp430g2553.h>

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    ADC10CTL0 = SREF_1 | ADC10SHT_2 | REFON | REF2_5V | ADC10ON | ADC10IE;
    ADC10CTL1 = INCH_5;
    ADC10AE0 |= BIT5;

    P1DIR |= BIT0;

    ADC10CTL0 |= ENC | ADC10SC;
    __bis_SR_register(GIE);

    while (1);
}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
    if (ADC10MEM > 0x266) 
        P1OUT |= BIT0;
    else
        P1OUT &= ~BIT0;

    ADC10CTL0 |= ADC10SC;
}


*/
