#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1 Ensure only 2 command line arguments are given
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    char *input = argv[1];
    FILE *f = fopen(input, "r");

    //check if input is empty
    if (f == NULL)
    {
        printf("Could not open file\n");
        fclose(f);
        return 1;
    }

    // Read header of input
    // TODO #3
    WAVHEADER h;
    fread(&h, sizeof(WAVHEADER), 1, f);

    // Use check_format to ensure WAV format
    // TODO #4 if its not, warn user
    if (!check_format(h))
    {
        printf("File is not a .WAV file\n");
        fclose(f);
        return 1;
    }

    // Open output file for writing
    // TODO #5
    char *output = argv[2];
    FILE *o = fopen(output, "w");

    //check if output exists
    if (o == NULL)
    {
        printf("Could not open output file\n");
        fclose(o);
        fclose(f);
        return 1;
    }

    // Write header to file
    // TODO #6 - copy header from input to output
    fwrite(&h, sizeof(WAVHEADER), 1, o);

    // Use get_block_size to calculate size of block
    // TODO #7
    int size = get_block_size(h);

    // read through the audio file, and count number of blocks of size (size)
    // TODO #8
    int buffer[size];
    int block_counter = 0;

    while (fread(buffer, 1, size, f) == size)
    {
        block_counter++;
    }

    //read backwards and write at the same time to output
    int uneven_counter = 0;
    for (int i = block_counter; i > 0; i--)
    {
        //each sample has 2 blocks. We want to keep the original order (1 2), when backwards it goes (2 1)
        //So we skip 1 block, write the next, and come back for the skipped.

        if (i % 2 != 0)
        {
            fread(buffer, 1, size, f);
            fwrite(buffer, 1, size, o);
            fseek(f, (- 2 * size), SEEK_CUR);
            uneven_counter++;
            i += 2;
            continue;
        }

        if (uneven_counter != 0)
        {
            fread(buffer, 1, size, f);
            fwrite(buffer, 1, size, o);
            fseek(f, (- 2 * size), SEEK_CUR);
            uneven_counter = 0;
            i -= 2;
        }
    }
    fclose(f);
    fclose(o);
    return 0;
}

int check_format(WAVHEADER header)
{
    // TODO #4 to be a header the header.format assumes 4 values, and they have to spell WAVE
    bool format = false;
    for (int i = 0; i <= header.format[i]; i++)
    {
        if ((header.format[i] == 'W') && (header.format[i + 1] == 'A') && (header.format[i + 2] == 'V') && (header.format[i + 3] == 'E'))
        {
            format = true;
        }
    }
    return format;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7 blocksize = number of channels * (bytes per sample) // bytes per sample = (bits per sample / 8)
    int bytesPerSample = header.bitsPerSample / 8;
    int block_size = header.numChannels * bytesPerSample;
    return block_size;
}