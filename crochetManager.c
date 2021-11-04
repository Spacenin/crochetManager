/*
* This is a simple crochet pattern management program I made for my girlfriend
* using C, ppm files, and txt files.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "menu.h"

int main(void) {
    int userChoice;
    bool looper = true;

    Pattern myPattern;
    myPattern.isSet = 0;

    char fileName[21];
    FILE *fp;
    
    //Display menu
    while(looper) {
        fprintf(stdout, "Enter in your choice of what to do!\n");
        fprintf(stdout, "1. Get pattern from file\n");
        fprintf(stdout, "2. Save pattern to file\n");
        fprintf(stdout, "3. Create image of pattern\n");
        fprintf(stdout, "4. Create new pattern\n");
        fprintf(stdout, "5. Quit program\n");

        fprintf(stdout, "--> ");
        fscanf(stdin, "%d", &userChoice);
        fprintf(stdout, "\n");

        switch(userChoice) {
            //Gets pattern from formatted file
            case 1:
                fprintf(stdout, "Enter the file you'd like to get from <fileName.txt> (max of 20): ");
                fscanf(stdin, " %s", fileName);

                fp = fopen(fileName, "r");

                if (fp == NULL) {
                    fprintf(stdout, "Error, file failed to open!\n");
                }

                else {
                    myPattern = getPattern(fp);

                    fprintf(stdout, "Done!\n");                    
                }
                
                fclose(fp);

                break;
            //Saves pattern to formatted file
            case 2:
                if (myPattern.isSet == 0) {
                    fprintf(stdout, "Your pattern isn't loaded!\n");

                    break;
                }

                fprintf(stdout, "Enter the file you'd like to save to <fileName.txt> (max of 20): ");
                fscanf(stdin, " %s", fileName);

                fp = fopen(fileName, "w");

                int isOpen;

                if (fp == NULL) {
                    fprintf(stdout, "Error, file failed to open!\n");
                }

                else {
                    isOpen = savePattern(fp, myPattern);

                    if (isOpen == -1) {
                        fprintf(stdout, "Error, file did not write correctly!\n");
                    }

                    else {
                        fprintf(stdout, "Done!\n");
                    }
                }

                fclose(fp);

                break;
            //Create ppm image
            case 3:
                fprintf(stdout, "Enter the fileName you'd like to create image in <fileName.ppm> (max of 20): ");
                fscanf(stdin, " %s", fileName);

                fp = fopen(fileName, "w");

                if (fp == NULL) {
                    fprintf(stdout, "Error, file did not open correctly!\n");
                }

                else {
                    if (myPattern.isSet == 0) {
                        fprintf(stdout, "Your pattern isn't set!\n");
                    }

                    else {
                        int check = createImage(fp, myPattern);

                        if (check == -1) {
                            fprintf(stdout, "Error, image was not created successfully!\n");
                        }

                        else {
                            fprintf(stdout, "Done!\n");
                        }
                    }
                }

                fclose(fp);

                break;
            //Create new pattern from user
            case 4:
                myPattern = createPattern();

                myPattern.isSet = 1;

                fprintf(stdout, "Done!\n");

                break;
            //Exit program
            case 5:
                looper = false;

                break;
            //Error option 
            default:
                fprintf(stdout, "That is not a choice! Can't you read?\n");

                break;
        }
    }    
    
    fprintf(stdout, "See you next time!\n\n");

    system("pause");
    return(0);
}