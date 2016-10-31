# include "database.h"

/* Basic functions to return width and heigth of a bmp file */

/* return the width of a bmp file */
unsigned int bmpWidth(char *file_name)
{
    FILE *fp;
    fp = fopen(file_name, "rb");
    int r;
    if(!fp)
    {
        r = 0;
    }
    else
    {
        BMPHEADER file_header;
        if(1 != fread(&file_header, sizeof(BMPHEADER), 1, fp))
            printf("fail");
        r = file_header.Width;
        fclose(fp);
    }
    return r;
}

/* return the height of a bmp file */
unsigned int bmpHeight(char *file_name)
{
    FILE *fp;
    fp = fopen(file_name, "rb");
    int r;
    if(!fp)
    {
        r = 0;
    }
    else
    {
        BMPHEADER file_header;
        if(1 != fread(&file_header, sizeof(BMPHEADER), 1, fp))
            printf("fail");
        r = file_header.Height;
        fclose(fp);
    }
    return r;
}

/* functions to create the database */
int readHeadBMP(char *file_name)
{
    FILE *fp;
    FILE *fp2;
    fp = fopen(file_name, "rb");
    fp2 = fopen("data", "a" );
    int r;
    if (!fp)
    {
        r = 0;
    }
    else
    {
        BMPHEADER file_header;
        if(1 != fread(&file_header, sizeof(BMPHEADER), 1, fp))
            printf("fail");
        if(file_header.type == 19778)
        {
            fprintf(fp2, "name: %s\n", file_name);
            fprintf(fp2, "type: BMP\n");
            fprintf(fp2, "size: %i\n", file_header.size);
            fprintf(fp2, "Width: %i\n", file_header.Width);
            fprintf(fp2, "Height: %i\n", file_header.Height);
        }
        else
        {
            fprintf(fp2, "name: %s\n", file_name);
            fprintf(fp2, "type: UNKNOWN\n");
            fprintf(fp2, "size: UNKNOWN\n");
            fprintf(fp2, "Width: UNKNOWN\n");
            fprintf(fp2, "Height: UNKNOWN\n");
        }
        fclose(fp2);
        fclose(fp);
        r = 1;
    }
    return r;
}

/* do or redo the database from scratch */
/* even if there was already one done before*/
void writeAllFiles()
{
    remove("data"); /* erase the possibly existing database */
    FILE *file;
    int i = 1;
    int b;
    do {
        b = 0; /*boolean to keep going or not */
        /* creation of a dynamical filename */
        /* so that it can be incremented*/
        char title_bmp[8];
        sprintf(title_bmp, "%d.bmp", i);
        
        char title_jpg[8];
        sprintf(title_jpg, "%d.jpg", i);
        
        char title_jpeg[8];
        sprintf(title_jpeg, "%d.jpeg", i);
        
        /* launch the fonction writing the header */
        /* of bmp files if the extention if .bmp */
        if((file = fopen(title_bmp, "r")))
        {
            fclose(file);
            readHeadBMP(title_bmp);
            b = 1;
        };
        /* no header for jpg/jpeg files */
        /* so it directly writes the name of the file*/
        /* and complete the size, width and height with "UNKNOWN" */
        if((file = fopen(title_jpg, "r")))
        {
            fclose(file);
            FILE *file2;
            file2 = fopen("data", "a" );
            fprintf(file2, "name: %s\n", title_jpg);
            fprintf(file2, "type: JPG\n");
            fprintf(file2, "size: UNKNOWN\n");
            fprintf(file2, "Width: UNKNOWN\n");
            fprintf(file2, "Height: UNKNOWN\n");
            fclose(file2);
            b = 1;
        };
        /* same for .jpeg than for .jpg */
        if((file = fopen(title_jpeg, "r")))
        {
            fclose(file);
            FILE *file2;
            file2 = fopen("data", "a" );
            fprintf(file2, "name: %s\n", title_jpeg);
            fprintf(file2, "type: JPEG\n");
            fprintf(file2, "size: UNKNOWN\n");
            fprintf(file2, "Width: UNKNOWN\n");
            fprintf(file2, "Height: UNKNOWN\n");
            fclose(file2);
            b = 1;
        };
        i++;
    }while(b == 1);
}
/* The database is made so that every 5th line */
/* represent the name of a new file. */
/* The 5 lines are Name, Size (of the file, in bytes), */
/* Width and Height (in pixels) */

/*
int main () {
    writeAllFiles();
    return 0;
}*/
