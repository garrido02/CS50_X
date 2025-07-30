#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string input);
int rotate(char c, int key);



int main(int argc, string argv[])
{

    //count command lines - return message if no command or more than one or non digit
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }


    //key funcion check if valid (digits between 0 and 9)

    if (only_digits(argv[1]))
    {

    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //converting argv[1] to an int
    int key = atoi(argv[1]);

    //get plaintext from user
    string plain_text = get_string("Plaintext:  ");

    //adding rotation & printing
    char c;
    printf("Ciphertext: ");
    for (int i = 0; i < strlen(plain_text); i++)
    {
        c = plain_text[i];
        c = rotate(c, key);
        printf("%c", c);
    }
    printf("\n");
    return 0;



}

bool only_digits(string input)
{
    bool valid = false;
    for (int i = 0; i < strlen(input); i++)
    {
        char l = input[i];

        if (isdigit(l))
        {
            valid = true;
            continue;
        }
        if (ispunct(l) || isalpha(l) || isspace(l))
        {
            valid = false;
        }
    }
    return valid;
}


int rotate(char c, int key)
{
    int output = 0;
    if (isupper(c))
    {
        c -= 'A';       //takes A value (65) from the character's value
        output = (c + key) % 26; //adds formula
        c = output + 'A'; //readds A's value in order to print the new letter
    }

    if (islower(c))
    {
        c -= 'a';
        output = (c + key) % 26;
        c = output + 'a';
    }

    if (ispunct(c) || isspace(c))
    {
        return c;
    }
    return c;
}