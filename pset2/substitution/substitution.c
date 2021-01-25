#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>


int main(int argc, string argv[]) // the second argument input is the key (NOT void)
{
    if (argc != 2) // return if two command line args are NOT provided
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    else if (strlen(argv[1]) != 26) // return an error if key is NOT 26 chars
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    else
    {   
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            if (isalpha((int) argv[1][j]) == false)  // return if key isn't all alpha chars
            {
                printf("Key must contain only alphabetic characters.\n");
                return 1;
            }
        }

        // check if there is a repeated character
        for (int a = 0; a < strlen(argv[1]); a++)
        {
            for (int b = a + 1; b < strlen(argv[1]); b++)
            {
                if (argv[1][a] == argv[1][b])
                {
                    printf("Characters cannot be repeated.\n");
                    return 1;
                }
            }
        }

        string plaintext = get_string("plaintext: ");

        for (int i = 0; i < strlen(plaintext); i++) // looping through the plaintext
        {
            if (isalpha((int) plaintext[i]))  // convert each alphabetic letter to the corresponding letter in the key
            {
                if (isupper((int) plaintext[i]))
                {
                    for (int k = 0; k < strlen(argv[1]); k++)
                    {
                        if (((int) plaintext[i]) - 65 == k) // if the ascii char - 65 in plain text matches the order of letter (k) in the key
                        {   
                            plaintext[i] = toupper(argv[1][k]);
                            break; // move to next letter in plaintext
                        }
                    }
                }
                    
                else if (islower((int) plaintext[i]))
                {
                    for (int n = 0; n < strlen(argv[1]); n++)
                    {
                        if (((int) plaintext[i]) - 97 == n)  // if the ascii char - 97 in plain text matches the order of letter (k) in the key
                        {   
                            plaintext[i] = tolower(argv[1][n]);
                            break; // move to next letter in plaintext
                        }
                    }
                }

            }
        }

        string ciphertext = plaintext;
        printf("ciphertext: %s\n", ciphertext);

        return 0;
    }
}