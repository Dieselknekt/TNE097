/*
Implement the function ToUpper(char* Str) that changes all the characters in the string to capital.
•Hint 1: The characters are represented in ASCII code. Find the ASCII code table in the following link: https://www.asciitabell.se/.
•Hint 2: It is a constant between the lower case and upper case of the characters in ASCII code.
•Hint3: The function should consider if the character contained in the string belong to the alphabet or not (skip the numbers).
•Hint 4: The function should not convert the character that is already in upper case.
*/

void ToUpper(char *Str)
{
    //Change characters until the end of string
    while (*Str != '\0')
    {
        int shift_length = 32;

        //only shift lowercase letters
        if (*Str >= 'a' && *Str <= 'z')
        {
            *Str -= shift_length;
        }
        Str++;
    }
}
