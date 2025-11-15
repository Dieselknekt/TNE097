/*
Show the code that solve the following problems.
•Define two variables unsigned char a = 0xAB, b = 0xFE.
•Show the result of a+b, b-a, NOT(a), a XOR b, right shift a by 4, left shift b by 2.
•Toggle the third bit of a and 7th bit of b.
*/

#include <msp430.h>

void task2(void)
{
    //define variables
    unsigned char a = 0xAB; //10101011
    unsigned char b = 0xFE; //11111110

    //operations
    unsigned char result_addition      = a + b;
    unsigned char result_subtraction      = b - a;
    unsigned char result_not_a    = (unsigned char)(~a);
    unsigned char result_xor      = a ^ b; 
    unsigned char result_shift_r4 = a >> 4;
    unsigned char result_shift_l2 = b << 2;

    // toggle
    a ^= 0x04; //0000 0100
    b ^= 0x40; //0100 0000

