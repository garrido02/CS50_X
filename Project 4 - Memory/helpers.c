#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate every row and column, find average colour, change every red blue and green to same value which is average
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average_color = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = average_color;
            image[i][j].rgbtGreen = average_color;
            image[i][j].rgbtBlue = average_color;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate over every row and column
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //store each original value (because we need a float)
            float original_red = image[i][j].rgbtRed;
            float original_blue = image[i][j].rgbtBlue;
            float original_green = image[i][j].rgbtGreen;

            //convert the original values to sepia values
            int converted_red = round(0.393 * original_red + 0.769 * original_green + 0.189 * original_blue);
            int converted_green = round(0.349 * original_red + 0.686 * original_green + 0.168 * original_blue);
            int converted_blue = round(0.272 * original_red + 0.534 * original_green + 0.131 * original_blue);

            //check if value is over 255, if it is, cap it at 255
            if (converted_blue > 255)
            {
                converted_blue = 255;
            }

            if (converted_green > 255)
            {
                converted_green = 255;
            }

            if (converted_red > 255)
            {
                converted_red = 255;
            }

            //change original values
            image[i][j].rgbtRed = converted_red;
            image[i][j].rgbtBlue = converted_blue;
            image[i][j].rgbtGreen = converted_green;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate over every row and column
    for (int i = 0; i < height; i++)
    {
        //width/2 because if width is even we want to iterate over every mirror pixels, if its uneven we want to leave the middle pixel alone
        for (int j = 0; j < (width / 2); j++)
        {
            //width - j - 1, because we want to compare pixel 0 with last pixel, which happens in the index width - 1 (we start counting from 0), and we increment j every loop to keep going backwards
            //general swap technique tmp is a temporary variable
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    //iterate over every row and column
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //copy every pixel
            copy[i][j] = image[i][j];
        }
    }

    //iterate over every row and column
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //create a store value for every colour and a counter
            int store_red = 0;
            int store_green = 0;
            int store_blue = 0;
            float counter = 0.0;

            //getting adjacent pixels, we know we only want pixels 1 row and 1 column to the left and right (meaning x - 1, x 0 and x 1 / and y - 1, y 0 and y 1)
            for (int x = - 1; x < 2; x++)
            {
                for (int y = - 1; y < 2; y++)
                {
                    //variable for the adjacent pixels of the current pixel we are looking at
                    int adjacentpixel_x = i + x;
                    int adjacentpixel_y = j + y;

                    //check if adjacent pixels are withtin the borders of the image, if not skip them
                    if (adjacentpixel_x < 0 || adjacentpixel_x > height - 1 || adjacentpixel_y < 0 || adjacentpixel_y > width - 1)
                    {
                        continue;
                    }

                    //store the adjacent pixels colours (of all adjacent pixels) on total value which sums it all, and while we are within picture borders, update counter to keep track
                    store_red += image[adjacentpixel_x][adjacentpixel_y].rgbtRed;
                    store_green += image[adjacentpixel_x][adjacentpixel_y].rgbtGreen;
                    store_blue += image[adjacentpixel_x][adjacentpixel_y].rgbtBlue;

                    counter++;
                }

                //calculate average adjacent pixels, knowing we need to divide by the counter in order to have the average
                copy[i][j].rgbtRed = round(store_red / counter);
                copy[i][j].rgbtGreen = round(store_green / counter);
                copy[i][j].rgbtBlue = round(store_blue / counter);
            }
        }
    }


    //update everypixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
    return;
}