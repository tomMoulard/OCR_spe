# ifndef DATABASE_H_
# define DATABASE_H_

# include <stdio.h>
# include <stdlib.h>
# include <err.h>

/* Structure for the BMP files */
/* it will get all the vaalues*/
/* contained in the Header of */
/* the bmp files (first 54 bytes) */
#pragma pack(1)
typedef struct
{  
    unsigned short type; /* format signature, BMP is 4D42 */
    unsigned int size; /* File size in bytes */
    unsigned short res1; /* reserved, must be zero */
    unsigned short res2; /* reserved, must be zero */
    unsigned int offset; /* Offset to data (in bytes)*/

    /* start of the InfoHeader (seconde part of the header) */
    unsigned int size_header; /* Header size in bytes */
    unsigned int Width; /* Width of the image (in pixels) */
    unsigned int Height; /* Height of the image (in pixels) */
    unsigned short int planes; /* Number of planes, must be 1 */
    unsigned short int bitsPerPixel; /* (1,4,8 or 24) */
    unsigned int compression; /* Compression type (0=none) */
    unsigned int imageSize; /* Image size in bytes (with padding) */
    unsigned int xResolution; /* horizontal res in pixels per meter */
    unsigned int yResolution; /* vertical res in pixels per meter */
    unsigned int colors; /* Number of colors */
    unsigned int importantColors;/* Number of important colors */
}BMPHEADER; /* Total of the header is 54 bytes */

/*--------------------END OF THE STRUCTURE--------------------*/

/* Basic functions to return width and heigth of a bmp file */

/* return the width of a bmp file */
unsigned int bmpWidth(char *file_name);

/* return the height of a bmp file */
unsigned int bmpHeight(char *file_name);

/* functions to create the database */
int readHeadBMP(char *file_name);

/* do or redo the database from scratch */
/* even if there was already one done before*/
void writeAllFiles();

# endif
