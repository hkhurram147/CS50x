#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef uint8_t BYTE;
bool check_jpeg_start(BYTE buffer);

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 2)
    {
        printf("Correct Usage: recover [card name].\n");
        return 1;
    }

    if (strcmp(argv[1], "card.raw"))
    {
        printf("Correct Usage: recover [card name].\n");
        return 1;
    }

    else
    {
        int num_blocks;
        int counter = 0; // represents the nth jpeg image we're on...
        bool jpeg_already_found;

        FILE *file = fopen(argv[1], "r");

        char ch;
        while (strcmp((ch = fgetc(file)), "EOF")) // while not at the end of the card file
        {
            BYTE *buffer = malloc(512 * sizeof(BYTE));
            fread(buffer, sizeof(BYTE), 512, argv[1]); // read 1 block: 512 bytes into a buffer

            // check if its the start of a new jpeg
            if (check_jpeg_start(buffer))
            {
                jpeg_already_found = true;

                if (counter == 0) // create then write to the first jpeg file
                {
                    sprintf(filename, "%03i.jpg", counter);
                    FILE *open(filename, "w");
                    fwrite(buffer, sizeof(BYTE), 1, filename); // write block by block???

                }

                else // create and write to a file that is NOT the first jpeg
                {
                    fclose(filename, "%03i.jpg", counter); // close previous jpeg file
                    counter++;
                    FILE *open(filename, "w");
                    fopen(filename, "%03i.jpg", counter)

                }
            }

            free(buffer);

            else
            {
                if (jpeg_already_found)
                    // repeat (loop) to write the next 512 byte block of the current jpeg
                    BYTE *(buffer+512)


            }

        }

        fclose(argv[1]);
    }

}


bool check_jpeg_start(BYTE buffer)
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] = 0xff
        && (buffer[3] & 0xf0) == 0xe0)) // last 4 bits are all set to zero in the 4th byte
    {
        return true;
    }

    else
        return false;
}
