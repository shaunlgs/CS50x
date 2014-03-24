/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember factor, n
    int n;
    if (sscanf(argv[1],"%d", &n) != 1)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine original padding
    int paddingOri = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update width and height info
    int biWidthOri = bi.biWidth;
    int biHeightOri = bi.biHeight;
    bi.biWidth *= n;
    bi.biHeight *= n;
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update file size and image size info
    bf.bfSize = 14 + 40 + (bi.biWidth * sizeof(RGBTRIPLE) + padding)  * abs(bi.biHeight);
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(biHeightOri); i < biHeight; i++)
    {
        // write n times for each row vertically
        for (int l = 0; l < n; l++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < biWidthOri; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write n times for each pixel horizontally
                for (int k = 0; k < n; k++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add padding to output file
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
            // go back to the start of current row of input file
            fseek(inptr, -(biWidthOri * sizeof(RGBTRIPLE)), SEEK_CUR);
        }
        // go to the end of current row (not yet include padding) of input file
        fseek(inptr, biWidthOri * sizeof(RGBTRIPLE), SEEK_CUR);
        // skip over padding of input file, if any
        fseek(inptr, paddingOri, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
