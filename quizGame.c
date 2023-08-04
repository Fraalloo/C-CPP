#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
char l[] = "*************************";
void startProgram(char program[30]){
    printf("%s %s %s\n",l,program,l);
}
void endProgram(char program[30]){
    char pr[30];
    for(int i = 0;i < strlen(program)-1;i++){
        strcat(pr,"*");
    }
    printf("%s%s%s",l,pr,l);
}
int main(){
    // Start of the Program
    startProgram("Quiz Game");

    // Declaring Variables
    char questions[][100] = {
                            "1. What year did the C language debut?:",
                            "2. Who is credited with creating C?:",
                            "3. What is the \"successor\" of C?:"
                            };
    char options[][100] = {
                            "A. 1969", "B. 1972", "C. 1970", "D. 1999",
                            "A. Dennis Ritchie", "B. Nikola Tesla", "C. John Carmack", "D. Doc Brown",
                            "A. Objective-C", "B. C#", "C. Java", "D. C++"
                        };
    char answers[] = {'B','A','D'};
    int numberOfQuestions = sizeof(questions)/sizeof(questions[0]);
    char guess;
    int score = 0;
    char sos;

    // Displaying Questions and Options
    for(int i = 0;i < numberOfQuestions;i++){
        printf("\n%s\n",questions[i]);
        for(int j = i*4;j < i * 4 + 4;j++){
            printf("%s\n",options[j]);
        }
        printf("Guess:\n");
        scanf("%c",&guess);
        scanf("%c",&sos);
        guess = toupper(guess);
        if(guess == answers[i]){
            printf("CORRECT!\n");
            score++;
        }else{
            printf("WRONG! The correct answer is %c\n",answers[i]);
        }
    }

    //Display score
    printf("\nFINAL SCORE: %d/%d!\n",score,numberOfQuestions);
    switch(score){
        case 0:
            printf("You did terrible!\n");
            break;
        case 1:
            printf("You did bad!\n");
            break;
        case 2:
            printf("You did good!\n");
            break;
        case 3:
            printf("You did perfet!\n");
            break;
    }

    // End of the Program
    endProgram("Quiz Game");
    return 0;
}