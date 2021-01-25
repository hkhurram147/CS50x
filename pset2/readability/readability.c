#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int main(void)
{
    string text = get_string("input: ");

    int letters = 0;
    int words = 1;
    int sentences = 0;

    for (int i = 0; i < strlen(text); i++)  // loop through array of chars in string text
    {
        if (isalpha((int) text[i])) 
            letters++; // if the char is alphabetic

        if (isspace((int) text[i]))  // i element is a letter
            words++;

        if (text[i] == '.' || text[i] == '!' || text[i] == '?') // count sentences
            sentences++;
    }

    float L = ((float) letters / words) * 100;
    float S = ((float) sentences / words) * 100;
    int x = (int) round(0.0588 * L - 0.296 * S - 15.8); // calculate grade level using the Coleman–Liau index 
   
    if (x < 1)
        printf("Before Grade 1\n");
        
    else if (x >= 16)
        printf("Grade 16+\n");

    else 
        printf("Grade %i\n", (int) x);
}