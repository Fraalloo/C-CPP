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
    for(int i = 0;i < strlen(program);i++){
        strcat(pr,"*");
    }
    printf("%s%s%s",l,pr,l);
}
int main(){
    // Start of the Program
    startProgram("Number Guessing Game");

    // Declaring Variables
    int MIN;
    int MAX;
    int guess;
    int guesses = 0;
    int num;

    // Taking Input
    printf("Now you have to enter the range between the random number should be generated.\n");
    printf("Min value:\n");
    scanf("%d",&MIN);
    printf("Max value:\n");
    scanf("%d",&MAX);

    // Generate Random Number
    srand(time(0));
    num = rand() % MAX + MIN;

    // Start of the Game
    do{
        printf("Enet a guess:\n");
        scanf("%d",&guess);
        guesses++;
        if(guess > MAX){
            printf("You guess is higher than the max!\n");
        }else if(guess < MIN){
            printf("You guess is lower than the min!\n");
        }else if((guess > num - 4)&&(guess < num + 4)&&guess != num){
            printf("Almost there\n");
        }else if(guess < num){
            printf("Go high!\n");
        }else if(guess > num){
            printf("Go lower!\n");
        }else{
            printf("CORRECT!\n ")
        }
    }while(guess != num);
    printf("You guessed the random number afet %d tries!\n",guesses);

    // End of the Program
    endProgram("Number Guessing Game");
    return 0;
}