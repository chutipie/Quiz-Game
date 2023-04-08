#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "functions.c"

int main(){
    struct quizRecord questions[20];
    struct playerRecord data[20];
    int nAction;
    int nScores = 0;
    int nQuestionNumber = 0;

    do {
        displayMainMenu();
        scanf("%d", &nAction);

        switch (nAction){
            case 1: 
                displayGameMenu(questions, data, nQuestionNumber, &nScores);
                break;

            case 2:
                manageData(questions, &nQuestionNumber);
                break;

            case 3:
                printf("\nExiting Program...\n");
                break;

            case 4: 
                printf("\nReturning to Main Menu...\n");
                break;

            default:
                printf("\nInvalid Action. Please try again.\n");
        }
    } while (nAction != 3);

    return 0;
}