#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    FILE *file = fopen(argv[1], "r"); //open memory card

    if (file == NULL)
    {
        printf("Image cannot be opened for reading\n");
        return 1;
    }

    unsigned char bytes[512];
    int jpegnum = 0;

    char filename[8];

    FILE *img = NULL; //new blank file for names

    while (!feof(file))
    {
        int reader = fread(bytes, sizeof(unsigned char), 512, file); //read 512 bytes into bytes[]

        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            //if first JPEG write first file ---.JPEG
            if (jpegnum == 0)
            {
                sprintf(filename, "%0.3i.jpg", jpegnum);

                img = fopen(filename, "w");

                //fwrite(bytes, sizeof(unsigned char), reader, img);
            } else //else close previous file, open new one, write next ---.JPEG (do same thing)
            {
                fclose(img);

                sprintf(filename, "%0.3i.jpg", jpegnum);
                img = fopen(filename, "w");
                //fwrite(bytes, sizeof(unsigned char), reader, img);
            }
            jpegnum++;
        }

        if (img != NULL)
        {
            fwrite(bytes, sizeof(unsigned char), reader, img);
        }

    }

    fclose(img);
    fclose(file);

}
