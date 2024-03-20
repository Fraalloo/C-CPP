#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define SIZE 3

#define SOLO 1
#define DUE 2

#define EZ 1
#define MED 2
#define HARD 3

char board[SIZE][SIZE];
char *b = &board[0][0];

const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

char PLAYER1NAME[12] = "PLAYER 1";
char PLAYER2NAME[12] = "PLAYER 2";

char space[] = "   |   |   \n";
char bar[] = "---|---|---\n";

int turno = 0;
char winner = ' ';

bool rigiocare();
int selezioneModalità();
int selezioneDifficoltà(); 
void azzera();
void visual();
int cercaSpaziVuoti();
void mossa(int);
bool noControl();
bool mossComputerFacile(bool);
bool mossComputerMedio(bool);
bool mossComputerDifficile(bool);
char cercaVincitore();
void visualVincitore(char);
bool chiediSeInserireNomi();
void chiediNome(int);
void outputFinale(char);
void umanoControUmano();
void umanoControComputer(int);
void clear();


int main(){
    srand(time(0));

    clear();

    int sceltaMod;
    int sceltaDif;

    printf("Benvenuto nel gioco del Tris!\n");
    printf("Il giocatore uno è distinto dal simbolo 'X', mentre il giocatore due dal simbolo 'O'\n\n");

    while(true){
        sceltaMod = selezioneModalità();
        azzera();
        
        switch(sceltaMod){
            case SOLO:
                sceltaDif = selezioneDifficoltà();

                if(chiediSeInserireNomi()){
                    chiediNome(1);
                }

                umanoControComputer(sceltaDif);

                break;
            case DUE:
                if(chiediSeInserireNomi()){
                    chiediNome(1);
                    chiediNome(2);
                }

                umanoControUmano();

                break;
        }

        if(!rigiocare()) break;
    }

    printf("Grazie per aver usato il programma!!\n");

    return 0;
}

bool rigiocare(){
    char rigioc;

    printf("Volete rigiocare?? (S/n): ");
    scanf("%c",&rigioc);
    scanf("%c",&rigioc);

    rigioc = toupper(rigioc);
    clear();

    return rigioc == 'S';
}
int selezioneModalità(){
    int scelta;

    printf("Selezione della modalità\n");
    printf("1) Umano Contro Computer\n2) Umano Contro Umano\n\n");

    do{
        printf("Scelta: ");
        scanf("%d",&scelta);
    }while(scelta < 1 || scelta > 2);
    
    return scelta;
}
int selezioneDifficoltà(){
    int scelta;

    printf("Selezione della difficoltà\n");
    printf("1) Facile\n2) Media\n3) Difficile\n\n");

    do{
        printf("Scelta: ");
        scanf("%d",&scelta);
    }while(scelta < 1 || scelta > 3);
    
    return scelta;
}
void azzera(){ 
    turno = 0;
    winner = ' ';

    strcpy(PLAYER1NAME,"PLAYER 1");
    strcpy(PLAYER2NAME,"PLAYER 2");

    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 3;j++){
            board[i][j] = ' ';
        }
    }
}
void visual(){
    for(int i = 0;i < 3;i++){
        printf("%s",space);
        printf(" %c | %c | %c \n",*(b+i*SIZE),*(b+i*SIZE+1),*(b+i*SIZE+2));
        if(i != 2) printf("%s",bar);
    }
}
int cercaSpaziVuoti(){
    int freeSpaces = 9;

    for(int i = 0; i < SIZE;i++){
        for(int j = 0; j < SIZE;j++){
            if(*(b+i*SIZE+j) != ' ') freeSpaces--;
        }
    }
    
    return freeSpaces;
}
void mossa(int turno){
    int row;
    int col;

    do{
        printf("Inserisci riga (1-3):");
        scanf("%d",&row);

        printf("Inserisci colonna (1-3):");
        scanf("%d",&col);

        row--;
        col--;

        if((row < 0 || row > 2) || (col < 0 || col > 2)){
            printf("Posizione non valida!\n");
            continue;
        }else if(*(b+row*SIZE+col) != ' ') printf("Posizione già selezionata!\n");
        else{ 
            if(turno%2 == 0) *(b+row*SIZE+col) = PLAYER1;
            else *(b+row*SIZE+col) = PLAYER2;
            break;
        }
    }while(*(b+row*SIZE+col) != ' ');
}
bool noControl(){
    while(true){
        int row = rand()%3;
        int col = rand()%3;
        if(board[row][col] == ' '){
            board[row][col] = PLAYER2;
            return true;
        }
    }
}
bool mossComputerFacile(bool use){
    if(
        (*b  == *(b+SIZE+1) &&  *b  != ' ') ||
        (*b  == *(b+2*SIZE+2) && *b  != ' ') ||
        (*(b+SIZE+1) == *(b+2*SIZE+2) && *(b+SIZE+1) != ' ')
    ){
        if(*b  == ' '){
            *b  = PLAYER2;
            return true;
        }else if(*(b+SIZE+1) == ' '){
            *(b+SIZE+1)= PLAYER2;
            return true;
        }else if(*(b+2*SIZE+2) == ' '){
            *(b+2*SIZE+2) = PLAYER2;
            return true;
        }
    }

    if(
        (*(b+2) == *(b+SIZE+1) &&  *(b+2) != ' ') ||
        (*(b+2) == *(b+2*SIZE) && *(b+2) != ' ') ||
        (*(b+SIZE+1) == *(b+2*SIZE) && *(b+SIZE+1) != ' ')
    ){
        if(*(b+2) == ' '){
            *(b+2) = PLAYER2;
            return true;
        }else if(*(b+SIZE+1) == ' '){
            *(b+SIZE+1) = PLAYER2;
            return true;
        }else if(*(b+2*SIZE) == ' '){
            *(b+2*SIZE) = PLAYER2;
            return true;
        }
    }
    
    if(!use) return noControl();
    
    return false;
}
bool mossComputerMedio(bool use){
    if(!mossComputerFacile(true)){
        for(int i = 0; i < SIZE; i++){
            if(
                (*(b+i*SIZE)  == *(b+i*SIZE+1) &&  *(b+i*SIZE)  != ' ') ||
                (*(b+i*SIZE)  == *(b+i*SIZE+2) && *(b+i*SIZE)  != ' ') ||
                (*(b+i*SIZE+1) == *(b+i*SIZE+2) && *(b+i*SIZE+1) != ' ')
            ){
                if(*(b+i*SIZE)  == ' '){
                    *(b+i*SIZE)  = PLAYER2;
                    return true;
                }else if(*(b+i*SIZE+1) == ' '){
                    *(b+i*SIZE+1)= PLAYER2;
                    return true;
                }else if(*(b+i*SIZE+2) == ' '){
                    *(b+i*SIZE+2) = PLAYER2;
                    return true;
                }
            }
        }
    }else return true;

    if(!use) return noControl();

    return false;
}
bool mossComputerDifficile(bool use){
    if(!mossComputerMedio(true)){
        for(int i = 0; i < SIZE; i++){
            if(
                (board[0][i]  == board[1][i] &&  board[0][i] != ' ') ||
                (board[0][i]  == board[2][i] && board[0][i] != ' ') ||
                (board[1][i] == board[2][i] && board[1][i] != ' ')
            ){
                if(board[0][i]  == ' '){
                    board[0][i]  = PLAYER2;
                    return true;
                }else if(board[1][i] == ' '){
                    board[1][i]= PLAYER2;
                    return true;
                }else if(board[2][i] == ' '){
                    board[2][i] = PLAYER2;
                    return true;
                }
            }
        }
    }else return true;

    if(!use) return noControl();

    return false;
}
char cercaVincitore(){
    for(int i = 0; i < SIZE; i++){
        if(*(b+i*SIZE) == *(b+i*SIZE+1) && *(b+i*SIZE) == *(b+i*SIZE+2)) return *(b+i*SIZE);
        if(*(b+i) == *(b+SIZE+i) && *(b+i) == *(b+2*SIZE+i)) return *(b+i);
    }

    if((*b == *(b+1*SIZE+1) && *b == *(b+2*SIZE+2)) || (*(b+2)== *(b+1*SIZE+1)  && *(b+2) == *(b+2*SIZE))) return *(b+SIZE+1);

    return ' ';
}
void visualVincitore(char winner){
    if(winner == PLAYER1) printf("\nHa vinto %s!\n", PLAYER1NAME);
    else if(winner == PLAYER2) printf("\nHa vinto %s!\n", PLAYER2NAME);
    else printf("\nAvete pareggiato!\n");
}
bool chiediSeInserireNomi(){
    char nome;

    printf("Volete inserire un nome? (S/n): ");
    scanf("%c",&nome);
    scanf("%c",&nome);

    nome = toupper(nome);

    if(nome == 'S') return true;
    return false;
}
void chiediNome(int num){
    if(num == 1){
        printf("Inserire il primo nome (max 12 caratteri): ");
        scanf("%s",PLAYER1NAME);
    }else{
        printf("Inserire il secondo nome (max 12 caratteri): ");
        scanf("%s",PLAYER2NAME);
    } 
}
void outputFinale(char winner){
    visual();
    visualVincitore(winner);
}
void umanoControUmano(){
    winner = ' ';

    while(1){
        if(turno%2 == 0) printf("\nTurno di %s:\n",PLAYER1NAME);
        else printf("\nTurno di %s:\n",PLAYER2NAME);

        visual();
        mossa(turno++);

        winner = cercaVincitore();
        if(winner != ' ' || cercaSpaziVuoti() == 0){
            clear();
            break;
        }
        clear();
    }

    outputFinale(winner);
}
void umanoControComputer(int sceltaDif){
    strcpy(PLAYER2NAME,"CPU");
    winner = ' ';

    while(true){
        if(turno%2 == 0){
            printf("\nTurno di %s:\n",PLAYER1NAME);
            visual();
            mossa(turno++);
        }else{
            switch(sceltaDif){
                case EZ:
                    mossComputerFacile(false);

                    break;
                case MED:
                    mossComputerMedio(false);

                    break;
                case HARD:
                    mossComputerDifficile(false);

                    break;
                }
            turno++;
        }

        winner = cercaVincitore();
        if(winner != ' ' || cercaSpaziVuoti() == 0){
            clear();
            break;
        }
        clear();
    }

    outputFinale(winner);
}
void clear(){
    #ifdef _WIN32
        system("cls");
    #elif defined(__APPLE__) || defined(__linux__)
        system("clear");
    #endif
}