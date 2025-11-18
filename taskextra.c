#include <msp430g2553.h>

volatile unsigned int toggle_count = 0;   // antal toggles kvar
volatile unsigned int toggles_left = 0;

void playTone(unsigned int freq, unsigned int duration_ms)
{
    // Stop timer först
    TA0CTL = MC_0;

    if (freq == 0) {
        // Tystnad
        P1OUT &= ~BIT0;
        __delay_cycles(1000UL * duration_ms);
        return;
    }

    // Timer-intervall för önskad frekvens
    // frekvens = toggles per sekund / 2
    // Toggle-hastighet = freq * 2
    unsigned int period = 1000000 / (freq * 2); // SMCLK = 1 MHz

    TA0CCR0 = period;
    TA0CTL = TASSEL_2 | MC_1;   // SMCLK, up-mode
    TA0CCTL0 = CCIE;            // Enable CCR0 interrupt

    // Hur många toggles behövs?
    toggles_left = (freq * 2) * duration_ms / 1000;

    while(toggles_left > 0);    // vänta tills tonen är färdig

    // Stäng av ljud osv
    TA0CTL = MC_0;
    TA0CCTL0 = 0;
    P1OUT &= ~BIT0;
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0_ISR(void)
{
    // Toggla P1.0
    P1OUT ^= BIT0;

    if (toggles_left > 0)
        toggles_left--;
}

/* Mario-toner */
#define NOTE_E7  2637
#define NOTE_G7  3136
#define NOTE_C7  2093
#define NOTE_E7  2637
#define NOTE_G6  1568
#define NOTE_D7  2349

void marioIntro()
{
    playTone(NOTE_E7, 125);
    playTone(NOTE_E7, 125);
    playTone(0,       75);

    playTone(NOTE_E7, 125);
    playTone(0,       75);

    playTone(NOTE_C7, 125);
    playTone(NOTE_E7, 125);
    playTone(0,       75);

    playTone(NOTE_G7, 125);
    playTone(0,       150);

    playTone(NOTE_G6, 125);
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    P1DIR |= BIT0;   // buzzer på P1.0
    P1OUT &= ~BIT0;

    __enable_interrupt();

    marioIntro();

    while(1);
}
