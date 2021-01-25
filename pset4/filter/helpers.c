#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {   
            RGBTRIPLE p = image[i][j]; // create a copy of each pixel value
            int avg = round((p.rgbtBlue + p.rgbtGreen + p.rgbtRed) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = avg;
        
        }
    }

    return;
}

// a function that swaps pixels in image
void swap(RGBTRIPLE * a, RGBTRIPLE * b)
{
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width/2; c++)
        {
            swap(&image[r][c], &image[r][width - 1 - c]);
        }
    }

    return;
}




// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    int n_pixels = 0;
    int sum_b, sum_g, sum_r; sum_b = sum_g = sum_r = 0;

    // find the average colour values of pixels within 1 row and col of the pixel
    for (int i = 0; i < height; i++) // rows
    {
        for (int j = 0; j < width; j++) // cols
        {
            for (int r = i - 1; r <= i + 1; r++) // box row
            {
                for (int c = j - 1; c <= j + 1; c++) // box col
                {
                    if (r >= 0 && r < height && c >= 0 && c < width)
                    {
                        sum_r += image[r][c].rgbtRed;
                        sum_g += image[r][c].rgbtGreen;
                        sum_b += image[r][c].rgbtBlue;
                        n_pixels++;
                    }
                }

            }

            // get the avg int values
            sum_b = round( (float) sum_b/n_pixels);
            sum_g = round( (float) sum_g/n_pixels);
            sum_r = round( (float) sum_r/n_pixels);

            image[i][j].rgbtBlue = sum_b;
            image[i][j].rgbtGreen = sum_g;
            image[i][j].rgbtRed = sum_r;

            n_pixels = 0, sum_r = 0, sum_g = 0, sum_b = 0;
        }

    }




    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{


    int Xsum_b = 0, Xsum_g = 0, Xsum_r = 0;
    int Ysum_b = 0, Ysum_g = 0, Ysum_r = 0;
    
    int Gx[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
    int Gy[3][3] = {{-1,-1,-1}, {0,0,0}, {1,2,1}};
    
    
    // make a copy with 4 black edges:
    RGBTRIPLE copy[height + 2][width + 2];
    for (int r = 0; r < height + 2; r++)
    {
        for (int c = 0; c < width + 2; c++)
        {
            // black edges
            if (r == 0 || r == height + 1 || c == 0 || c == width + 1)
            { 
                copy[r][c].rgbtRed = 0;     
                copy[r][c].rgbtGreen = 0;
                copy[r][c].rgbtBlue = 0;
            }
            
            // copy everything in between the edges (the original image)
            else
                copy[r][c] = image[r-1][c-1];
        }
    }
    
    
    
    // edge detection using the sobel operator
    for (int i = 1; i < height; i++) // rows
    {
        for (int j = 1; j < width; j++) // cols
        {
            Xsum_b = 0, Xsum_g = 0, Xsum_r = 0;
            Ysum_b = 0, Ysum_g = 0, Ysum_r = 0;
            
            for (int n = -1; n <= 1; n++) // step in the rows
            {
                for (int m = -1; m <= 1; m++) // step in the cols
                {

                    Xsum_r += copy[i+n][j+m].rgbtRed * Gx[n+1][m+1];
                    Xsum_g += copy[i+n][j+m].rgbtGreen * Gx[n+1][m+1];
                    Xsum_b += copy[i+n][j+m].rgbtBlue * Gx[n+1][m+1];
                    Ysum_r += copy[i+n][j+m].rgbtRed * Gy[n+1][m+1];
                    Ysum_g += copy[i+n][j+m].rgbtGreen * Gy[n+1][m+1];
                    Ysum_b += copy[i+n][j+m].rgbtBlue * Gy[n+1][m+1];
                
                }

            }
            
            // Sobel filter algorithm (square root of the squares of Gx and Gy)
            int G_val_r = round(sqrt(pow(Xsum_r,2) + pow(Xsum_r,2)));
            int G_val_g = round(sqrt(pow(Xsum_g,2) + pow(Xsum_g,2)));
            int G_val_b = round(sqrt(pow(Xsum_b,2) + pow(Xsum_b,2)));
            
            // Max value capped at 255
            if (G_val_r > 255)
                G_val_r = 255;
            if (G_val_g > 255)
                G_val_g = 255;
            if (G_val_b > 255)
                G_val_b = 255;
                
            image[i][j].rgbtBlue = G_val_b;
            image[i][j].rgbtGreen = G_val_g;
            image[i][j].rgbtRed = G_val_r;
        }

    }




    return;
}
