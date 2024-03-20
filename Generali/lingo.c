#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

#define MAX_SIZE_LEN 20
#define SIZE_MAT_PAR 5
#define TIME 15

void anagramma(char*,char*);
void *timeCount(void*);
void clear();

int cas;
char parole[][MAX_SIZE_LEN] = {
        "cane",
        "albero",
        "fiore",
        "palle",
        "computer"
    };

char parola[MAX_SIZE_LEN];
char guess[MAX_SIZE_LEN];

time_t inizio;
time_t fine;
int timer;

int main(){
    clear();

    printf("Benvenuto nel gioco del Lingo!\n");
    printf("Ti sarà fornita una sequenza di caratteri e tu dovrai indovinarne l'anagramma di senso compiuto di provenienza.\n");
    printf("Avrai a disposizione tre tentativi da completare entro 15 secondi.");
    printf("\n\nPremere invio per continuare");
    getchar();
    clear();

    pthread_t cronometro;
    int tempo = TIME;
    
    inizio = time(NULL);
    pthread_create(&cronometro, NULL, timeCount, &tempo);
    
    srand(time(0)); 

    bool win = false;  
    cas = rand()%SIZE_MAT_PAR;

    anagramma(parole[cas],parola);
    strcpy(guess,"");

    for(int i = 0; i < 3; i++){
        printf("Indovina un anagramma di %s: ",parola);
        scanf("%s",guess);

        if(!strcmp(guess,parole[cas])){
            win = true;
            break;
        }
    }

    fine = time(NULL);
    timer = difftime(fine,inizio);

    if(timer < 15){
        if(win)printf("Hai vinto!\n");
        else printf("Hai perso!\nLa parola era %s\n",parole[cas]);
        printf("Ci hai messo %d secondi\n",timer);
    }else printf("Ci hai messo troppo tempo, %d secondi e la parola era %s\n",timer,parola);

    exit(EXIT_SUCCESS);
    
    return 0;
}

void anagramma(char *parola,char *mischiata){
    int size = strlen(parola);

    int num[size];
    for(int i = 0; i < size; i++){
        num[i] = i;
    }

    for(char *i = parola; *i != '\0'; i++){
        while(true){
            int pos = rand()%size;

            if(num[pos] != -1){
                num[pos] = -1;
                *(mischiata + pos) = *i;
                break;
            }
        } 
    }

    *(mischiata + size) = '\0';
}
void *timeCount(void *tmp){
    int *temp = (int*)tmp;

    while(true){
        fine = time(NULL);
        if(difftime(fine,inizio) > *temp){
            printf("\nTempo scaduto!\nLa parola era \"%s\"\n",parole[cas]);
            exit(EXIT_SUCCESS);
        }
    }
}
void clear(){
    #ifdef _WIN32
        system("cls");
    #elif defined(__APPLE__) || defined(__linux__)
        system("clear");
    #endif
}