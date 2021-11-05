#ifndef MENU_H
#define MENU_H

//Pixel struct to represent the RGB values
typedef struct Pixel_struct {
    int r;
    int g;
    int b;
} Pixel;

//Pattern struct to represent a pattern with a 2D array of pixels
typedef struct Pattern_struct {
    int width;
    int height;
    int isSet;

    Pixel** pixels;
} Pattern;

Pattern getPattern(FILE* fp);
int savePattern(FILE* fp, Pattern pattern);
int createImage(FILE *fp, Pattern pattern);
Pattern createPattern(void);
void clearPattern(Pattern p);
Pattern editPattern(Pattern p);
Pattern addPattern(Pattern p);

#endif