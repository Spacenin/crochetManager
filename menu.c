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
    Pixel col;
    int rowItr = 0;
    int colItr = 0;
    int rowNum;
    int colNum;
    char colChoice;

    fprintf(stdout, "Enter in the height and width of your pattern: ");
    fscanf(stdin, "%d %d", &(myPattern.height), &(myPattern.width));

    myPattern.pixels = malloc(myPattern.height * sizeof(Pixel*));

    for (int i = 0; i < myPattern.height; ++i) {
        myPattern.pixels[i] = malloc(myPattern.width * sizeof(Pixel));
    }
    
    while (rowItr < myPattern.height) {
        fprintf(stdout, "Enter how many rows to add now: ");
        fscanf(stdin, "%d", &rowNum);

        if (rowNum + rowItr > myPattern.height) {
            fprintf(stdout, "You entered a row count greater than the max! Defaulting to one row addition...\n");

            rowNum = 1;
        }

        fprintf(stdout, "Would you like the columns of the row(s) to be different? (y or n): ");
        fscanf(stdin, " %c", &colChoice);

        if (colChoice == 'y' || colChoice == 'Y') {
            while (colItr < myPattern.width) {
                fprintf(stdout, "Enter how many columns to add now: ");
                fscanf(stdin, "%d", &colNum);

                if (colNum + colItr > myPattern.width) {
                    fprintf(stdout, "You entered a column ammount greater than the max! Defaulting to one column addition...\n");

                    colNum = 1;
                }

                fprintf(stdout, "Enter the RGB value for row(s) %d-%d and columns %d-%d (r g b): ", rowItr + 1, rowNum + rowItr, colItr + 1, colNum + colItr);
                fscanf(stdin, "%d %d %d", &(col.r), &(col.g), &(col.b));

                for (int i = rowItr; i < rowNum + rowItr; ++i) {
                    for (int j = colItr; j < colNum + colItr; ++j) {
                        myPattern.pixels[i][j] = col;
                    }
                }

                colItr += colNum;
            }
        } 

        else {
            fprintf(stdout, "Enter the RGB value for row(s) %d-%d (r g b): ", rowItr + 1, rowNum + rowItr);
            fscanf(stdin, "%d %d %d", &(row.r), &(row.g), &(row.b));

            for (int i = rowItr; i < rowNum + rowItr; ++i) {
                for (int j = 0; j < myPattern.width; ++j) {
                    myPattern.pixels[i][j] = row;
                }
            }
        }

        rowItr += rowNum;
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

//Add pattern row
Pattern addPattern(Pattern p) {
    Pixel row;
    Pixel col;
    char colChoice;
    int colItr = 0;
    int colNum;

    ++(p.height);

    p.pixels = realloc(p.pixels, p.height * sizeof(Pixel*));
    p.pixels[p.height - 1] = malloc(p.width * sizeof(Pixel));

    fprintf(stdout, "Would you like the entire row to be one color? (y or n): ");
    fscanf(stdin, " %c", &colChoice);

    if (colChoice == 'n' || colChoice == 'N') {
        while (colItr < p.width) {
            fprintf(stdout, "Enter how many columns to add now: ");
            fscanf(stdin, "%d", &colNum);

            if (colNum + colItr > p.width) {
                fprintf(stdout, "You entered a column ammount greater than the max! Defaulting to one column addition...\n");

                colNum = 1;
            }

            fprintf(stdout, "Enter the rgb values for the new row columns %d-%d (r g b): ", colItr + 1, colNum + colItr);
            fscanf(stdin, "%d %d %d", &(col.r), &(col.g), &(col.b));

            for (int i = colItr; i < colNum + colItr; ++i) {
                p.pixels[p.height - 1][i] = col;
            }

            colItr += colNum;
        }
    }
    
    else {
        fprintf(stdout, "Enter the rgb value for the row (r g b): ");
        fscanf(stdin, "%d %d %d", &(row.r), &(row.g), &(row.b));

        for (int i = 0; i < p.width; ++i) {
            p.pixels[p.height - 1][i] = row;
        }
    }

    return(p);
}