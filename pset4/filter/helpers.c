#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            int currR = image[i][j].rgbtRed;
            int currG = image[i][j].rgbtGreen;
            int currB = image[i][j].rgbtBlue;

            int avg = round((currR+currG+currB)/3.0);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j != round((width-1)/2.0); j++)
        {
            int holderR = image[i][j].rgbtRed;
            int holderG = image[i][j].rgbtGreen;
            int holderB = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width-(j+1)].rgbtRed;
            image[i][j].rgbtGreen = image[i][width-(j+1)].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width-(j+1)].rgbtBlue;

            image[i][width-(j+1)].rgbtRed = holderR;
            image[i][width-(j+1)].rgbtGreen = holderG;
            image[i][width-(j+1)].rgbtBlue = holderB;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE origrefimg[height][width];

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            origrefimg[i][j].rgbtRed = image[i][j].rgbtRed;
            origrefimg[i][j].rgbtGreen = image[i][j].rgbtGreen;
            origrefimg[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //made a copy of the orignal image for reference in a variable called origrefimg

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totsumR = origrefimg[i][j].rgbtRed;
            int totsumG = origrefimg[i][j].rgbtGreen;
            int totsumB = origrefimg[i][j].rgbtBlue;

            float count = 1.0;

            if (j-1 >= 0) //one left
            {
                totsumR += origrefimg[i][j-1].rgbtRed;
                totsumG += origrefimg[i][j-1].rgbtGreen;
                totsumB += origrefimg[i][j-1].rgbtBlue;
                count ++;
            }

            if (j+1 <= width-1) //one right
            {
                totsumR += origrefimg[i][j+1].rgbtRed;
                totsumG += origrefimg[i][j+1].rgbtGreen;
                totsumB += origrefimg[i][j+1].rgbtBlue;
                count ++;
            }

            if (i-1 >= 0) //one up
            {
                totsumR += origrefimg[i-1][j].rgbtRed;
                totsumG += origrefimg[i-1][j].rgbtGreen;
                totsumB += origrefimg[i-1][j].rgbtBlue;
                count ++;
            }

            if (i+1 <= height-1) //one down
            {
                totsumR += origrefimg[i+1][j].rgbtRed;
                totsumG += origrefimg[i+1][j].rgbtGreen;
                totsumB += origrefimg[i+1][j].rgbtBlue;
                count ++;
            }

            if (j-1 >= 0 && i+1 <= height-1) //bottom left
            {
                totsumR += origrefimg[i+1][j-1].rgbtRed;
                totsumG += origrefimg[i+1][j-1].rgbtGreen;
                totsumB += origrefimg[i+1][j-1].rgbtBlue;
                count ++;
            }

            if (j-1 >= 0 && i-1 >= 0) //top left
            {
                totsumR += origrefimg[i-1][j-1].rgbtRed;
                totsumG += origrefimg[i-1][j-1].rgbtGreen;
                totsumB += origrefimg[i-1][j-1].rgbtBlue;
                count ++;
            }

            if (j+1 <= width-1 && i-1 >= 0) //top right
            {
                totsumR += origrefimg[i-1][j+1].rgbtRed;
                totsumG += origrefimg[i-1][j+1].rgbtGreen;
                totsumB += origrefimg[i-1][j+1].rgbtBlue;
                count ++;
            }

            if (j+1 <= width-1 && i+1 <= height-1) //bottom right
            {
                totsumR += origrefimg[i+1][j+1].rgbtRed;
                totsumG += origrefimg[i+1][j+1].rgbtGreen;
                totsumB += origrefimg[i+1][j+1].rgbtBlue;
                count ++;
            }

            image[i][j].rgbtRed = round(totsumR/count);
            image[i][j].rgbtGreen = round(totsumG/count);
            image[i][j].rgbtBlue = round(totsumB/count);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE origrefimg[height][width];

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            origrefimg[i][j].rgbtRed = image[i][j].rgbtRed;
            origrefimg[i][j].rgbtGreen = image[i][j].rgbtGreen;
            origrefimg[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //made a copy of the orignal image for reference in a variable called origrefimg

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            float gxfinvalR = 0.0;
            float gxfinvalG = 0.0;
            float gxfinvalB = 0.0;

            //same thing for variable gyfinval matrix
            float gyfinvalR = 0.0;
            float gyfinvalG = 0.0;
            float gyfinvalB = 0.0;

            if (j-1 >= 0) //one left
            {
                gxfinvalR += (float)(origrefimg[i][j-1].rgbtRed)*-2;
                gxfinvalG += (float)(origrefimg[i][j-1].rgbtGreen)*-2;
                gxfinvalB += (float)(origrefimg[i][j-1].rgbtBlue)*-2;
            }

            if (j+1 <= width-1) //one right
            {
                gxfinvalR += (float)(origrefimg[i][j+1].rgbtRed)*2;
                gxfinvalG += (float)(origrefimg[i][j+1].rgbtGreen)*2;
                gxfinvalB += (float)(origrefimg[i][j+1].rgbtBlue)*2;
            }

            if (i-1 >= 0) //one up
            {
                //gx is 0 here
                gyfinvalR += (float)(origrefimg[i-1][j].rgbtRed)*-2;
                gyfinvalG += (float)(origrefimg[i-1][j].rgbtGreen)*-2;
                gyfinvalB += (float)(origrefimg[i-1][j].rgbtBlue)*-2;
            }

            if (i+1 <= height-1) //one down
            {
                //gx is 0 here
                gyfinvalR += (float)(origrefimg[i+1][j].rgbtRed)*2;
                gyfinvalG += (float)(origrefimg[i+1][j].rgbtGreen)*2;
                gyfinvalB += (float)(origrefimg[i+1][j].rgbtBlue)*2;
            }

            if (j-1 >= 0 && i+1 <= height-1) //bottom left
            {
                gxfinvalR += (float)(origrefimg[i+1][j-1].rgbtRed)*-1;
                gxfinvalG += (float)(origrefimg[i+1][j-1].rgbtGreen)*-1;
                gxfinvalB += (float)(origrefimg[i+1][j-1].rgbtBlue)*-1;

                gyfinvalR += (float)origrefimg[i+1][j-1].rgbtRed;
                gyfinvalG += (float)origrefimg[i+1][j-1].rgbtGreen;
                gyfinvalB += (float)origrefimg[i+1][j-1].rgbtBlue;
            }

            if (j-1 >= 0 && i-1 >= 0) //top left
            {
                gxfinvalR += (float)(origrefimg[i-1][j-1].rgbtRed)*-1;
                gxfinvalG += (float)(origrefimg[i-1][j-1].rgbtGreen)*-1;
                gxfinvalB += (float)(origrefimg[i-1][j-1].rgbtBlue)*-1;

                gyfinvalR += (float)(origrefimg[i-1][j-1].rgbtRed)*-1;
                gyfinvalG += (float)(origrefimg[i-1][j-1].rgbtGreen)*-1;
                gyfinvalB += (float)(origrefimg[i-1][j-1].rgbtBlue)*-1;
            }

            if (j+1 <= width-1 && i-1 >= 0) //top right
            {
                gxfinvalR += (float)origrefimg[i-1][j+1].rgbtRed;
                gxfinvalG += (float)origrefimg[i-1][j+1].rgbtGreen;
                gxfinvalB += (float)origrefimg[i-1][j+1].rgbtBlue;

                gyfinvalR += (float)(origrefimg[i-1][j+1].rgbtRed)*-1;
                gyfinvalG += (float)(origrefimg[i-1][j+1].rgbtGreen)*-1;
                gyfinvalB += (float)(origrefimg[i-1][j+1].rgbtBlue)*-1;
            }

            if (j+1 <= width-1 && i+1 <= height-1) //bottom right
            {
                gxfinvalR += (float)origrefimg[i+1][j+1].rgbtRed;
                gxfinvalG += (float)origrefimg[i+1][j+1].rgbtGreen;
                gxfinvalB += (float)origrefimg[i+1][j+1].rgbtBlue;

                gyfinvalR += (float)origrefimg[i+1][j+1].rgbtRed;
                gyfinvalG += (float)origrefimg[i+1][j+1].rgbtGreen;
                gyfinvalB += (float)origrefimg[i+1][j+1].rgbtBlue;
            }

            int newR = round((float)sqrt(pow(gxfinvalR, 2) + pow(gyfinvalR, 2)));
            int newG = round((float)sqrt(pow(gxfinvalG, 2) + pow(gyfinvalG, 2)));
            int newB = round((float)sqrt(pow(gxfinvalB, 2) + pow(gyfinvalB, 2)));

            if (newR >= 255)
                newR = 255;
            else if (newR <= 0)
                newR = 0;

            if (newG >= 255)
                newG = 255;
            else if (newG <= 0)
                newG = 0;

            if (newB >= 255)
                newB = 255;
            else if (newB <= 0)
                newB = 0;

            image[i][j].rgbtRed = newR;
            image[i][j].rgbtGreen = newG;
            image[i][j].rgbtBlue = newB;

        }
    }

}
