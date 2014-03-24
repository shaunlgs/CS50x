/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char* argv[])
{
    BYTE buffer[512];
    // open memory card file
    FILE* file = fopen("card.raw", "rb");
    char title[10];
    int index = -1;
    FILE* img;
    // repeat until end of card
    while(fread(buffer, sizeof(BYTE), 512, file) == 512)
    {
        // start of a new jpg
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] == 0xe0) || (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] == 0xe1))
        {
            // if another jpg is open while new jpg is found, close the jpg
            if (index >= 0)
            {
                fclose(img);
            }
            // open new file
            index++;
            sprintf(title, "%03i.jpg", index);
            img = fopen(title, "a");
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
        else
        {
            // if already found jpg, add 512 bytes each round
            if (index >= 0)
            {
                fwrite(buffer, sizeof(BYTE), 512, img);
            }
        }
    }
    // close any remaining files
    fclose(img);
    fclose(file);
}
