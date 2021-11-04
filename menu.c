#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

//Gets pattern from fp file using double pointer
Pattern getPattern(FILE* fp) {
    Pattern myPattern;

    fscanf(fp, "%d %d", &(myPattern.height), &(myPattern.width));

    myPattern.pixels = malloc(myPattern.height * sizeof(Pixel*));
    
    for (int i = 0; i < myPattern.height; ++i) {
        myPattern.pixels[i] = malloc(myPattern.width * sizeof(Pixel));
    }

    for (int i = 0; i < myPattern.height; ++i) {
        for (int j = 0; j < myPattern.width; ++j) {
            fscanf(fp, " %d %d %d,", &(myPattern.pixels[i][j].r), &(myPattern.pixels[i][j].g), &(myPattern.pixels[i][j].b));
        }
        
        fscanf(fp, "\n");
    }

    myPattern.isSet = 1;

    return(myPattern);
}

//Saves pattern to file
int savePattern(FILE *fp, Pattern pattern) {
    fprintf(fp, "%d %d\n", pattern.height, pattern.width);

    for (int i = 0; i < pattern.height; ++i) {
        for (int j = 0; j < pattern.width; ++j) {
            fprintf(fp, "%d %d %d, ", pattern.pixels[i][j].r, pattern.pixels[i][j].g, pattern.pixels[i][j].b);
        }

        fprintf(fp, "\n");
    }

    return(0);
}

//Create ppm imagae from the pattern
int createImage(FILE* fp, Pattern pattern) {
    fprintf(fp, "P3\n");
    fprintf(fp, "%d %d %d\n", pattern.width, pattern.height, 255);

    for (int i = 0; i < pattern.height; ++i) {
        for (int j = 0; j < pattern.width; ++j) {
            fprintf(fp, " %d %d %d ", pattern.pixels[i][j].r, pattern.pixels[i][j].g, pattern.pixels[i][j].b);
        }

        fprintf(fp, "\n");
    }


    return(0);
}

//Create pattern from user input
Pattern createPattern(void) {
    Pattern myPattern;
    Pixel row;

    fprintf(stdout, "Enter in the height and width of your pattern: ");
    fscanf(stdin, "%d %d", &(myPattern.height), &(myPattern.width));

    myPattern.pixels = malloc(myPattern.height * sizeof(Pixel*));

    for (int i = 0; i < myPattern.height; ++i) {
        myPattern.pixels[i] = malloc(myPattern.width * sizeof(Pixel));
    }

    for (int i = 0; i < myPattern.height; ++i) {
        fprintf(stdout, "Enter the RGB value for row %d (r g b): ", i+1);
        fscanf(stdin, "%d %d %d", &(row.r), &(row.g), &(row.b));

        for (int j = 0; j < myPattern.width; ++j) {
            myPattern.pixels[i][j] = row;
        }
    }

    fprintf(stdout, "\n");

    return(myPattern);
}

//Edit pattern row
Pattern editPattern(Pattern p) {
    int row;
    int r;
    int g;
    int b;

    fprintf(stdout, "Enter the row # you'd like to change: ");
    fscanf(stdin, "%d", &row);
    fprintf(stdout, "Enter the values to change it to (r g b): ");
    fscanf(stdin, "%d %d %d", &r, &g, &b);

    for (int i = 0; i < p.width; ++i) {
        p.pixels[row][i].r = r;
        p.pixels[row][i].g = g;
        p.pixels[row][i].b = b;
    }

    return(p);
}