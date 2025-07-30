#include <stdio.h>
#include <cs50.h>

int get_size(void);
void print_grid(int size);

int main(void)
{
    // Creating user prompt for pyramid height
    int n = get_size();

    // Creating the printed grid
    print_grid(n);
}


// Creating a new function in order get a return from the user's prompt
int get_size(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}

// Creating a second function to print exactly what we want
void print_grid(int size)
{
    for (int row = 1; row <= size; row++)
    {
        for (int space = 1; space <= size - row; space++)
        {
            printf(" "); // If we stayed here we would only get spaces or dots if applicable
        }
        for (int freq = 1; freq <= row; freq++)
        {
            printf("#"); // We added hashes of the first pyramid
        }
        for (int space = size - 1; space <= size; space++)
        {
            {
                printf(" "); // We added the spaces after the first pyramid
            }
        }
        for (int freq = 1; freq <= row; freq++)
        {
            printf("#"); // And finally the hashes of the second pyramid
        }
        printf("\n");
    }
}