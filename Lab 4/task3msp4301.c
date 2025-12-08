/*
Develop the code that 2 MSP430 boards can send commands to each other. Once a command is received, the MSP430 board toggles the green or red LED.
As shown in the following figure, MSP430 (1) sends a command to MSP430 (2). When the command is received, MSP430 (2) toggles the green LED. Meanwhile, MSP430 (2) sends a command to MSP430 (1). 
When MSP430 (1) receives the command, it toggles the red LED. A timer is utilized to control the interval between 2 commands.
Important steps:
• Define the commands as a specific character, for example, “Green LED Toggle” defined as ‘g’ and “Red LED Toggle” defined as ‘r’.
• Configure the timer that defines the interval between two commands
• Configure the UART port
  o Utilize the calibrated DCO clock:
▪ BCSCTL1 = CALBC1_1MHZ;
▪ DCOCTL = CALDCO_1MHZ;
  o Configure the TX and RX pin function
  o Configure the UART using SMCLK
  o Configure the baud rate as 19200 (the SMCLK is configured as 1MHz)
  o Initialize USCI state machine
  o Enable the UART RX interrupt
• Send the command when TIMER interrupt triggered
  o MSP430 TX buffer name: UCA0TXBUF
  o MSP430(1) sends “Green LED Toggle” while MSP430(2) sends “Red LED Toggle”.
• Handle the received command in the UART RX interrupt service routine with the interrupt vector “USCIAB0RX_VECTOR”
  o Compare the command in the UART receive buffer UCA0RXBUF
  o Toggle the corresponding LED according to the received command
• In this task, one needs to develop two sets of code, one for MSP430 (1) and one for MSP430 (2). The basic logic and the function are same. The only difference is that MSP430 (1) sends out “Green LED Toggle” command and MSP430 (2) sends out “Red LED Toggle” command.
*/

//MSRP430 1:

#include <msp430g2553.h>

#define CMD_GREEN  'g'
#define CMD_RED    'r'

//UART Setup functions, called in main

void clock_init(void)
{
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;
}

void uart_init(void)
{
    P1SEL  |= BIT1 | BIT2;          // P1.1 = RXD, P1.2 = TXD
    P1SEL2 |= BIT1 | BIT2;

    UCA0CTL1 |= UCSWRST;            // hold USCI in reset
    UCA0CTL1 |= UCSSEL_2;           // SMCLK

    UCA0BR0 = 52;                   // 1MHz/19200
    UCA0BR1 = 0;
    UCA0MCTL = UCBRS0;              // modulation

    UCA0CTL1 &= ~UCSWRST;           // release USCI from reset
    IE2 |= UCA0RXIE;                // enable RX interrupt
}

void timer_init(void)
{
    TACCTL0 = CCIE;
    TACCR0  = 50000;                // ~50 ms @ 1 MHz
    TACTL   = TASSEL_2 | MC_1;      // SMCLK, up mode
}

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;

    clock_init();
    uart_init();
    timer_init();

    P1DIR |= BIT0 | BIT6;

    __bis_SR_register(GIE);

    for (;;)
    {
        __no_operation();
    }
}

// Timer A0 ISR, send 'g' command from controller
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    while (!(IFG2 & UCA0TXIFG));    // wait until buffert is rdy
    UCA0TXBUF = CMD_GREEN;          // send 'g'
}

// UART RX ISR – receive command, toggle red LED when receiven 'r'
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    unsigned char c = UCA0RXBUF;

    if (c == CMD_RED)
    {
        P1OUT ^= BIT0;
    }
}
