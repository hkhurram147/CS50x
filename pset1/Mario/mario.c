#include <stdio.h>
#include <cs50.h>

int counter(void);

int main(void)
{
    // call the function that returns the appropriate n value
    int height = counter();
    int spaces = height - 1;

    for (int r = 0; r < height; r++, spaces--) // looping through all the rows...
    {
        for (int s_remaining = spaces; s_remaining > 0; s_remaining--)
        {
            printf(" ");
        }
        for (int hashes1 = r + 1; hashes1 > 0; hashes1--)
        {
            printf("#");
        }

        printf("  ");

        for (int hashes2 = r + 1; hashes2 > 0; hashes2--)
        {
            printf("#");
        }

        printf("\n");
    }
}

int counter(void)
{
    int n;
    do // do once without checking the condition...
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8); // continue to prompt the user for proper input if True

    return n;
}