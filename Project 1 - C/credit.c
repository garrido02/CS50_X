#include <cs50.h>
#include <stdio.h>


long get_cardnumber(void);




int main(void)
{
    //Prompt for input
    long number = get_cardnumber();

    //Calculate every other digit, multiply by 2 and add then
    long digit15 = ((number % 100) / 10) * 2;
    long digit13 = ((number % 10000) / 1000) * 2;
    long digit11 = ((number % 1000000) / 100000) * 2;
    long digit9 = ((number % 100000000) / 10000000) * 2;
    long digit7 = ((number % 10000000000) / 1000000000) * 2;
    long digit5 = ((number % 1000000000000) / 100000000000) * 2;
    long digit3 = ((number % 100000000000000) / 10000000000000) * 2;
    long digit1 = ((number % 10000000000000000) / 1000000000000000) * 2;

    digit15 = ((digit15 % 100) / 10) + (digit15 % 10);
    digit13 = ((digit13 % 100) / 10) + (digit13 % 10);
    digit11 = ((digit11 % 100) / 10) + (digit11 % 10);
    digit9 = ((digit9 % 100) / 10) + (digit9 % 10);
    digit7 = ((digit7 % 100) / 10) + (digit7 % 10);
    digit5 = ((digit5 % 100) / 10) + (digit5 % 10);
    digit3 = ((digit3 % 100) / 10) + (digit3 % 10);
    digit1 = ((digit1 % 100) / 10) + (digit1 % 10);

    int every_other_digit = digit15 + digit13 + digit11 + digit9 + digit7 + digit5 + digit3 + digit1;

    //Calculate sum of remaining digits
    long digit16 = (number % 10);
    long digit14 = ((number % 1000) / 100);
    long digit12 = ((number % 100000) / 10000);
    long digit10 = ((number % 10000000) / 1000000);
    long digit8 = ((number % 1000000000) / 100000000);
    long digit6 = ((number % 100000000000) / 10000000000);
    long digit4 = ((number % 10000000000000) / 1000000000000);
    long digit2 = ((number % 1000000000000000) / 100000000000000);
    long other_digits = digit16 + digit14 + digit12 + digit10 + digit8 + digit6 + digit4 + digit2;

    //Calculate checksum and check if last digit is 0
    long checksum = every_other_digit + other_digits;

    if ((checksum % 10) > 0)     //checking if valid
    {
        printf("INVALID\n");          //finish here
        return 0;
    }


    //If its valid we then get the length of the card
    int length = 0;
    long visa = number;
    long mastercard = number;
    long amex = number;
    while (number > 0)           // loop that keep dividing card by 10, ultil the last digit
    {
        number = number / 10;
        length++;           // length will be = to nr of digits
    }

    //Is card type VISA? Visa can have 13 or 16 digits, so we just keep a loop to know how many there are
    while (visa >= 10)
    {
        visa /= 10;         // /= keep dividing
    }
    if (visa == 4 && (length == 13 || length == 16))
    {
        printf("VISA\n");
        return 0;           // if conditions get skipped if condition is not true
    }


    //Is card type MASTER CARD? master card can only have 14 digits so we know that if we diving by 0^14 (14 zeros) we get the remaining digits (first two)
    while (mastercard >= 100000000000000)
    {
        mastercard /= 100000000000000;
    }
    if (length == 16 && (mastercard == 51 || mastercard == 52 || mastercard == 53 || mastercard == 55))
    {
        printf("MASTERCARD\n");
        return 0;
    }


    //Is card type AMEX?
    while (amex >= 10000000000000) //amex can only have 15 digits, so 0^13 will give first 2 digits
    {
        amex /= 10000000000000;
    }
    if (length == 15 && (amex == 34 || amex == 37))
    {
        printf("AMEX\n");
        return 0;
    }
    else                //Since if function only actually runs if condition is true, we want a situation where if no condition is met, then the card number is invalid
    {
        printf("INVALID\n");
        return 0;
    }
}




long get_cardnumber(void) //prompt user for card number
{
    long number;
    do
    {
        number = get_long("Card Number: ");
    }
    while (number < 0);
    return number;
}










