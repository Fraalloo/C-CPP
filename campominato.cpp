/*
    Gallo Francesco
    Di Tullo Francesco
    D'Ambrosio Stefano
*/

#include <iostream>

#ifdef __APPLE__
    #include <unistd.h>
    #include <chrono>
    #include <thread>
#elif __linux__
    #include <cstdlib>
    #include <chrono>
    #include <thread>
#elif _WIN32
    #include <windows.h>
    #include <ctime>
    #include <cstdlib>
    #include <cwchar>

    wchar_t BOMB[2];
    wchar_t NBOMB[2];
    wchar_t QUADNER[2];
    wchar_t QUADBIANC[2];
    wchar_t FLAGC[2];
    wchar_t FLAGN[2];
    wchar_t FLAGS[2];
    wchar_t FUOCO[2];

    /**
     * Stampa a schermo i caratteri unicode per il sistema operativo Windows
     * 
     * @param unicode Carattere unicode da stampare.
    */
    void unicodeWindows(wchar_t unicode[]){
        WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), unicode, 2, NULL, NULL);
    }
#endif

using namespace std;

// Dimensione campo
#define ROW 22
#define COL 22

// Quantità bombe nelle varie difficoltà
#define EZ 60
#define MED 90
#define HARD 120
#define INS 150
#define IMP 180
#define AAN 0

// Valore attribuito alle modalità
#define EZ_M 1
#define MED_M 2
#define HARD_M 3
#define INS_M 4
#define IMP_M 5
#define AAN_M 0

// Valore attribuito a contenuto campo minato
#define CORN 0
#define MINA 1
#define VUOTO 2

// Valore attribuito alla selezione
#define NVIS 0
#define VIS 1
#define FLAG 2

// Valori attribuiti alla conclusione
#define WIN 0
#define LOSE 1
#define IDK 2

/**
 * Inizializza il campo minato generando mine casualmente.
 * 
 * @param mat La matrice contenente il campo minato.
 * @param row Righe totali della matrice.
 * @param col Colonne totali della matrice.
 * @param num Quantità di mine da generare.
*/
void init(int[][COL], int, int, int);

/**
 * Visualizza il campo minato come simboli in base alle celle già visitate.
 * 
 * @param mat La matrice contenente il campo minato.
 * @param scelte La matrice dove è immagazzinato 1 se la cella nel campo minato è stata visitata,
 *               0 se non è stata visitata e 2 se si trova una bandiera.
 * @param row Righe totali della matrice.
 * @param col Colonne totali della matrice.
*/
void visual(int[][COL], int[][COL],int, int);

/**
 * Visualizza il campo minato come numeri in base alle celle già visitate.
 * 
 * @param mat La matrice contenente il campo minato.
 * @param col Colonne totali della matrice.
*/
void visualIntero(int[][COL], int, int);

/**
 * Stesso compito di 'visual', ma mostra anche tutte le mine.
 * 
 * @param mat La matrice contenente il campo minato.
 * @param scelte La matrice dove è immagazzinato 1 se la cella nel campo minato è stata visitata,
 *               0 se non è stata visitata e 2 se si trova una bandiera.
 * @param row Righe totali della matrice.
 * @param col Colonne totali della matrice.
*/
void visualMine(int[][COL], int[][COL],int, int);

/**
 * Converte in maiuscolo una lettera minuscola.
 * 
 * @param let Lettera da convertire in maiuscolo passata per riferimento.
*/
void maiuscolo(char&);

/**
 * Conta quante volte viene trovato un valore all'interno dell'intorno della cella di una matrice.
 * 
 * @param mat La matrice contenente il campo minato.
 * @param row Riga del centro dell'intorno.
 * @param col Colonna del centro dell'intorno.
 * @param val Valore da cercare.
 * 
 * @return Quante volte 'val' è stato trovato in 'mat'.
*/
int cercaIntorno(int[][COL], int, int, int);

/**
 * Cerca all'interno di due array contenenti coordinate se delle nuove coordinate sono già presenti.
 * 
 * @param row Array che immagazzina la coordinata della riga.
 * @param col Array che immagazzina la coordinata della colonna.
 * @param rw Nuova coordinata della riga.
 * @param cl Nuova coordinata della colonna.
 * @param num Quantià mine all'interno del campo.
 * 
 * @return Restituisce vero se le coordinate nuove sono già presenti.
*/
bool cercaCoordinate(int[],int[],int,int,int);

/**
 * Segna come visitate o meno le celle del campo.
 * 
 * @param campo La matrice contenente il campo minato.
 * @param scelte La matrice dove è immagazzinato 1 se la cella nel campo minato è stata visitata,
 *               0 se non è stata visitata e 2 se si trova una bandiera.
 * @param row Righe totali della matrice.
 * @param col Colonne totali della matrice.
*/
void scopriCampo(int[][COL],int[][COL],int,int);

/**
 * Controlla la condizione della partita, cioè se è vinta, persa o da continuare.
 * 
 * @param campo La matrice contenente il campo minato.
 * @param scelte La matrice dove è immagazzinato 1 se la cella nel campo minato è stata visitata,
 *               0 se non è stata visitata e 2 se si trova una bandiera.
 * @param row Righe totali della matrice.
 * @param col Colonne totali della matrice.
 * @param num Quantià mine all'interno del campo.
 * 
 * @return Restituisce 'WIN' se tutto il campo è visitato tranne le mine,
 *         'LOSE' se una mina viene visitata e
 *         'IDK' quando nessuna delle precedenti condizioni è verificata.
*/
int verificaRisultato(int[][COL],int[][COL],int,int,int);

/**
 * Calcola la difficoltà del campo minato secondo i criteri 3BV.
 * 
 * @param campo La matrice contenente il campo minato.
 * @param mat3BV La matrice utilizzata per il calcolo del 3BV.
 * 
 * @return Livello di difficoltà 3BV.
*/
int _3BV(int[][COL],int[][COL]);

/**
 * Ripristina tutte le celle di una matrice ad un singolo valore.
 * 
 * @param mat La matrice da azzerare.
 * @param row Righe totali della matrice.
 * @param col Colonne totali della matrice.
 * @param val Valore a cui riazzerare la matrice.
*/
void azzera(int[][COL],int,int,int);

/**
 * Contiene il gioco vero e proprio.
 * 
 * @param campo La matrice contenente il campo minato.
 * @param selezioni La matrice dove è immagazzinato 1 se la cella nel campo minato è stata visitata,
 *               0 se non è stata visitata e 2 se si trova una bandiera.
 * @param mat3BV Matrice utilizzata per il calcolo del 3BV.
 * @param mode Quantità di mine da generare.
*/
void gioco(int[][COL],int[][COL],int[][COL],int);

/**
 * Annuncia la vittoria dell'utente.
 * 
 * @param milliseconds Quantità di millisecondi da aspettare.
*/
void vittoria(int);

/**
 * Esegue l'animazione di un'esplosione con le ASCII art.
 * 
 * @param milliseconds Quantità di millisecondi da aspettare.
*/
void esplosione(int);


/**
 * Ringrazia l'utente e termina il programma.
*/
void fine();

/**
 * Pulisce il terminale cancellando ogni carattere.
*/
void clear();

/**
 * Ferma l'esecuzione per un numero definito di tempo.
 * 
 * @param milliseconds Quantità di millisecondi da aspettare.
 *
 * @return Resituisce sempre 0
*/
int sleep(int);

int main(){
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);

        wcscpy(BOMB,L"\U0001F4A5 ");
        wcscpy(NBOMB,L"\U0001F4A3 ");
        wcscpy(QUADNER,L"\u25A1 ");
        wcscpy(QUADBIANC,L"\u25A0  ");
        wcscpy(FLAGC,L"\U0001F6A9 ");
        wcscpy(FLAGN,L"\U0001F44E ");
        wcscpy(FLAGS,L"\U0001F44D ");
        wcscpy(FUOCO,L"\U0001F525 ");
    #endif

    srand(time(0));

    short scelta; // Scelta della modalità
    char rigioc; // Scelta per rigiocare o no

    cout << "\n\nBENVENUTO NEL CAMPO MINATO\n\n";
    cout << "INFORMAZIONI RIGUARDO AL GIOCO\n";
    cout << "\tSistemi operativi al di fuori di MacOS, Linux e Windows non sono supportati.\n";
    cout << "\tLe coordinate vanno inserite usando le lettere rappresentanti righe, colonne o la presenza o meno della bandiera\n";

    #ifdef _WIN32
        cout << "\tSimbolicamente ";
        unicodeWindows(BOMB);
        cout << " rappresenta la mina esplosa su Windows\n";
        cout << "\tSimbolicamente ";
        unicodeWindows(NBOMB);
        cout << " rappresenta la mina non esplosa su Windows\n";
        cout << "\tSimbolicamente ";
        unicodeWindows(FLAGC);
        cout << " rappresenta la bandiera su Windows\n";
        cout << "\tSimbolicamente ";
        unicodeWindows(QUADBIANC);
        cout << " rappresenta la cella selezionabile su Windows \n";
        cout << "\tSimbolicamente ";
        unicodeWindows(QUADNER);
        cout << " rappresenta la cella vuota su Windows\n";
    #elif defined(__APPLE__) || defined(__linux__)
        cout << "\tSimbolicamente 🧨 rappresenta la mina esplosa su MacOS e Linux\n";
        cout << "\tSimbolicamente 💣 rappresenta la mina non esplosa su MacOS e Linux\n";
        cout << "\tSimbolicamente 🚩 rappresenta la bandiera su MacOS e Linux\n";
        cout << "\tSimbolicamente \u25A0 rappresenta la cella selezionabile su MacOS e Linux\n";
        cout << "\tSimbolicamente \u25A1 rappresenta la cella vuota su MacOS e Linux\n";
    #endif

    cout << endl;

    // Il gioco viene rieseguito finchè l'utente non decide di uscire
    while(true){        
        int campo[ROW][COL] = {0};
        int selezioni[ROW][COL] = {0};
        int mat3BV[ROW][COL] = {0};

        cout << "Selezione della difficolta':\n";
        cout << "1) Modalita' facile \t\t" << EZ << "  mine\n";
        cout << "2) Modalita' media \t\t" << MED << "  mine\n";
        cout << "3) Modalita' difficile \t\t" << HARD << " mine\n";
        cout << "4) Modalita' insana \t\t" << INS << " mine\n";
        cout << "5) Modalita' impossibile \t" << IMP << " mine\n";
        cout << "0) Modalità di testing\n";
        do{
            cin >> scelta;
        }while(scelta<AAN_M||scelta>IMP_M);

        clear();

        switch(scelta){
            case EZ_M:
                gioco(campo,selezioni,mat3BV,EZ);
                
                break;
            case MED_M:
                gioco(campo,selezioni,mat3BV,MED);

                break;
            case HARD_M:
                gioco(campo,selezioni,mat3BV,HARD);

                break;
            case INS_M:
                gioco(campo,selezioni,mat3BV,INS);

                break;
            case IMP_M:
                gioco(campo,selezioni,mat3BV,IMP);

                break;
            case AAN_M:
                gioco(campo,selezioni,mat3BV,AAN);

                break;
        }
        
        cout << "Vuoi rigiocare? (S/n): ";
        cin >> rigioc;
        maiuscolo(rigioc);
        clear();

        if(rigioc != 'S') break;

        azzera(campo,ROW,COL,0);
        azzera(selezioni,ROW,COL,0);
        azzera(mat3BV,ROW,COL,0);
    }

    fine();

    return 0;
}

void init(int mat[][COL], int row, int col, int num){
    if(num == AAN) mat[1][1] = MINA;
    else{
        int memRow[num];
        int memCol[num];

        for(int i = 0; i < num; i++){
            int rw = rand()%(ROW-2)+1;
            int cl = rand()%(COL-2)+1;
            if(cercaCoordinate(memRow,memCol,rw,cl,num)){
                i--;
                continue;
            }
            mat[rw][cl] = MINA;
        }
    }
    
    for(int i = 1; i < row - 1; i++){
        for(int j = 1; j < col - 1; j++){
            if(mat[i][j] != MINA) mat[i][j] = VUOTO;
        }
    }
}
void visual(int mat[][COL],int scelte[][COL], int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(mat[i][j] == CORN){
                char cari = 'A' + i - 1;
                char carj = 'A' + j - 1;
                if(cari == 'A' + row - 2 || carj == 'A' + col - 2) continue;
                else if(i == 0 && j == 0) cout << "  ";
                else if(i == 0) cout << carj << "  ";
                else if(j == 0) cout << cari << " ";
            }else if(scelte[i][j] == VIS && mat[i][j] == VUOTO){
                int num = cercaIntorno(mat,i,j,MINA);
                if(num == 0){
                    #ifdef _WIN32
                        unicodeWindows(QUADNER);
                        cout << " ";
                    #elif defined(__APPLE__) || defined(__linux__)
                        cout << "\u25A1  ";
                    #endif
                }else cout << num << "  ";
            }else if(scelte[i][j] == FLAG){
                #ifdef _WIN32
                    unicodeWindows(FLAGC);
                    cout << " ";
                #elif defined(__APPLE__) || defined(__linux__)
                    cout << "🚩 ";
                #endif
            }else{
                #ifdef _WIN32
                    unicodeWindows(QUADBIANC);
                    cout << " ";
                #elif defined(__APPLE__) || defined(__linux__)
                    cout << "\u25A0  ";
                #endif
            }
        }

        #ifdef _WIN32
            switch(i){
                case 1:
                    cout << "\tLe coordinate vanno inserite usando righe, colonne e bandiera";
                    break;
                case 2:
                    cout << "\tInserire \'B\' per posizionare la bandiera, \'N\' altrimenti";
                    break;
                case 3:
                    cout << "\tPer rimuovere una bandiera, inserire la stessa cella";
                    break;
                case 4:
                    cout << "\tSimbolicamente ";
                    unicodeWindows(FLAGC);
                    cout << " rappresenta la bandiera";
                    break;
                case 5:
                    cout << "\tSimbolicamente ";
                    unicodeWindows(QUADBIANC);
                    cout << " rappresenta la cella selezionabile";
                    break;
                case 6:
                    cout << "\tSimbolicamente ";
                    unicodeWindows(QUADNER);
                    cout << " rappresenta la cella vuota";
                    break;
            }
        #elif defined(__APPLE__) || defined(__linux__)
            switch(i){
                case 1:
                    cout << "\tLe coordinate vanno inserite usando righe, colonne e bandiera";
                    break;
                case 2:
                    cout << "\tInserire \'B\' per posizionare la bandiera, \'N\' altrimenti";
                    break;
                case 3:
                    cout << "\tPer rimuovere una bandiera, inserire la stessa cella";
                    break;
                case 4:
                    cout << "\tSimbolicamente 🚩 rappresenta la bandiera";
                    break;
                case 5:
                    cout << "\tSimbolicamente \u25A0 rappresenta la cella selezionabile";
                    break;
                case 6:
                    cout << "\tSimbolicamente \u25A1 rappresenta la cella vuota";
            }
        #endif
        
        cout << endl;
    }
}
void visualIntero(int mat[][COL], int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(mat[i][j] == CORN) cout << "#";
            else if(mat[i][j] == MINA) cout << "*";
            else if(mat[i][j] == VUOTO) cout << cercaIntorno(mat,i,j,MINA);
            cout << " ";
        }
        cout << endl;
    }
}
void visualMine(int mat[][COL], int scelte[][COL],int row, int col){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(mat[i][j] == CORN){
                char cari = 'A' + i - 1;
                char carj = 'A' + j - 1;
                if(cari == 'A' + row - 2 || carj == 'A' + col - 2) continue;
                else if(i == 0 && j == 0) cout << "  ";
                else if(i == 0) cout << carj << "  ";
                else if(j == 0) cout << cari << " ";
            }else if(scelte[i][j] == VIS){
                if(mat[i][j] == MINA){
                    #ifdef _WIN32
                        unicodeWindows(BOMB);
                        cout << " ";
                    #elif defined(__APPLE__) || defined(__linux__)
                        cout << "💥 ";
                    #endif
                }else if(mat[i][j] == VUOTO){
                    int num = cercaIntorno(mat,i,j,MINA);
                    if(num == 0){
                        #ifdef _WIN32
                            unicodeWindows(QUADNER);
                            cout << " ";
                        #elif defined(__APPLE__) || defined(__linux__)
                            cout << "\u25A1  ";
                        #endif
                    }else cout << num << "  ";
                }
            }else if(mat[i][j] == MINA){
                #ifdef _WIN32
                    if(scelte[i][j] == FLAG) unicodeWindows(FLAGS);
                    else unicodeWindows(NBOMB);
                #elif defined(__APPLE__) || defined(__linux__)
                    if(scelte[i][j] == FLAG) cout << "👍 ";
                    else cout << "💣 "; 
                #endif
            }else if(scelte[i][j] == FLAG){
                #ifdef _WIN32
                    unicodeWindows(FLAGN);
                #elif defined(__APPLE__) || defined(__linux__)
                    cout << "👎 ";
                #endif
            }else{
                #ifdef _WIN32
                    unicodeWindows(QUADBIANC);
                    cout << " ";
                #elif defined(__APPLE__) || defined(__linux__)
                    cout << "\u25A0  ";
                #endif
            }
        }

        #ifdef _WIN32
            switch(i){
                case 1:
                    cout << "\tSimbolicamente ";
                    unicodeWindows(BOMB);
                    cout << " rappresenta la mina esplosa";
                    break;
                case 2:
                    cout << "\tSimbolicamente ";
                    unicodeWindows(NBOMB);
                    cout << " rappresenta la mina non esplosa";
                    break;
                case 3:
                    cout << "\tSimbolicamente ";
                    unicodeWindows(FLAGS);
                    cout << " rappresenta la bandiera sopra ad una mina";
                    break;
                case 4:
                    cout << "\tSimbolicamente ";
                    unicodeWindows(FLAGN);
                    cout << " rappresenta la bandiera non sopra ad una mina";
                    break;
            }
        #elif defined(__APPLE__) || defined(__linux__)
            switch(i){
                case 1:
                    cout << "\tSimbolicamente 💥 rappresenta la mina esplosa";
                    break;
                case 2:
                    cout << "\tSimbolicamente 💣 rappresenta la mina non esplosa";
                    break;
                case 3:
                    cout << "\tSimbolicamente 👍 rappresenta la bandiera sopra ad una mina";
                    break;
                case 4:
                    cout << "\tSimbolicamente 👎 rappresenta la bandiera non sopra ad una mina";
                    break;
            }
        #endif

        cout << endl;
    }
}
void maiuscolo(char &let){
    if(let >= 'a' && let <= 'z') let -= ' ';
}
int cercaIntorno(int mat[][COL], int row, int col, int val){
    int cont = 0;
    for(int i = row - 1; i < row + 2; i++){
        for(int j = col - 1; j < col + 2; j++){
            if(i == row && j == col) continue;
            if(mat[i][j] == val) cont++;
        }
    }
    return cont;
}
bool cercaCoordinate(int row[],int col[], int rw, int cl,int num){
    for(int i = 0; i < num; i++){
        if(row[i] == rw && col[i] == cl) return true;
    }
    return false;
}
void scopriCampo(int campo[][COL],int scelte[][COL],int row,int col){
    if(
        row <= 0 || row >= ROW - 1 || 
        col <= 0 || col >= COL - 1 ||
        scelte[row][col] == VIS ||
        scelte[row][col] == FLAG
    ) return;

    scelte[row][col] = VIS;
    if(campo[row][col] == MINA) return;

    if(cercaIntorno(campo,row,col,MINA) == 0){
        for(int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                if(campo[row + i][col + j] == VUOTO) scopriCampo(campo,scelte,row+i,col+j);
            }
        }
    }
}
int verificaRisultato(int campo[][COL],int scelte[][COL],int row, int col, int num){
    int contVuoti = 0;
    int contFlagMine = 0;
    int contFlagVuote = 0;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(campo[i][j] == MINA && scelte[i][j] == VIS) return LOSE;
            if(campo[i][j] == MINA && scelte[i][j] == FLAG) contFlagMine++;
            else if(campo[i][j] == VUOTO && scelte[i][j] == FLAG) contFlagVuote++;
            else if(campo[i][j] == VUOTO && scelte[i][j] == VIS) contVuoti++;
        }
    }
    if(num == AAN && contFlagVuote == 0 && contVuoti == (row - 2)*(col - 2) - 1 && contFlagMine == 1) return WIN;
    else if(num != AAN && contFlagMine == num && contFlagVuote == 0 && contVuoti == (row - 2)*(col - 2) - num) return WIN;
    return IDK;
}
int _3BV(int campo[][COL], int mat3BV[][COL]){
    int cont = 0;
    for(int i = 1; i < ROW - 2; i++){
        for(int j = 1; j < COL - 2; j++){
            if(cercaIntorno(campo,i,j,MINA) != 0 && campo[i][j] == VUOTO){
                cont++;
                mat3BV[i][j] = VIS;
            }else if(cercaIntorno(campo,i,j,MINA) == 0 && mat3BV[i][j] == NVIS){
                cont++;
                scopriCampo(campo,mat3BV,i,j);
            }
        }
    }
    return cont;
}
void azzera(int mat[][COL],int row,int col,int val){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            mat[i][j] = val;
        }
    }
}
void gioco(int campo[][COL],int selezioni[][COL], int mat3BV[][COL],int mode){
    int condizione; // Condizione: se vittoria, sconfitta o continuare

    char x; // Coordinata colonna inserita
    char y; // Coordinata riga inserita
    char flag;

    int rw; // Coordinata riga convertita
    int cl; // Coordinata colonna convertita

    init(campo,ROW,COL,mode);
    int diff3BV = _3BV(campo,mat3BV);

     while(true){
        cout << "DIFFICOLTA' 3BV: " << diff3BV << endl << endl;
        //visualIntero(campo,ROW,COL);
        visual(campo,selezioni,ROW,COL);

        do{
            cout << "Inserire coordinate (RIGA/COLONNA/BANDIERA): ";
            cin >> y >> x >> flag;

            maiuscolo(x);
            maiuscolo(y);
            maiuscolo(flag);
        }while((y < 'A' || y > 'A' + ROW + 1) || (x < 'A' || x > 'A' + COL + 1) || (flag != 'B' && flag != 'N'));
              
        rw = y - 'A' + 1;
        cl = x - 'A' + 1;
                    
        if(flag == 'N') scopriCampo(campo,selezioni,rw,cl);
        else{
            if(selezioni[rw][cl] == FLAG) selezioni[rw][cl] = NVIS;
            else if(selezioni[rw][cl] == NVIS){
                selezioni[rw][cl] = FLAG;
            }
        }
        clear();

        condizione = verificaRisultato(campo,selezioni,ROW,COL,mode);

        if(condizione == WIN){
            vittoria(2000);

            cout << "Complimenti, hai vinto!!\n\n";
            cout << "Il tuo punteggio e': " << (float)(diff3BV*mode*(rand()%(101)+800))/100  << endl;
            break;
        }else if(condizione == LOSE){
            esplosione(1000);

            cout << "Peccato, sei esploso!!\n\n";
            cout << "Il tuo punteggio e': " << (float)(diff3BV*mode*(rand()%(101)+200))/1000 << endl;
            break;
        }
    }

    visualMine(campo,selezioni,ROW,COL);
}
void vittoria(int milliseconds){
    #if defined(__APPLE__) || defined(__linux__)
        sleep(milliseconds/4);        
        clear();

        cout << "────────────────────░███░" << endl;
        cout << "───────────────────░█░░░█░" << endl;
        cout << "──────────────────░█░░░░░█░" << endl;
        cout << "─────────────────░█░░░░░█░" << endl;
        cout << "──────────░░░───░█░░░░░░█░" << endl;
        cout << "─────────░███░──░█░░░░░█░" << endl;
        cout << "───────░██░░░██░█░░░░░█░" << endl;
        cout << "──────░█░░█░░░░██░░░░░█░" << endl;
        cout << "────░██░░█░░░░░░█░░░░█░" << endl;
        cout << "───░█░░░█░░░░░░░██░░░█░" << endl;
        cout << "──░█░░░░█░░░░░░░░█░░░█░" << endl;
        cout << "──░█░░░░░█░░░░░░░░█░░░█░" << endl;
        cout << "──░█░░█░░░█░░░░░░░░█░░█░" << endl;
        cout << "─░█░░░█░░░░██░░░░░░█░░█░" << endl;
        cout << "─░█░░░░█░░░░░██░░░█░░░█░" << endl;
        cout << "─░█░█░░░█░░░░░░███░░░░█░" << endl;
        cout << "░█░░░█░░░██░░░░░█░░░░░█░" << endl;
        cout << "░█░░░░█░░░░█████░░░░░█░" << endl;
        cout << "░█░░░░░█░░░░░░░█░░░░░█░" << endl;
        cout << "░█░█░░░░██░░░░█░░░░░█░" << endl;
        cout << "─░█░█░░░░░████░░░░██░" << endl;
        cout << "─░█░░█░░░░░░░█░░██░█░" << endl;
        cout << "──░█░░██░░░██░░█░░░█░" << endl;
        cout << "───░██░░███░░██░█░░█░" << endl;
        cout << "────░██░░░███░░░█░░░█░" << endl;
        cout << "──────░███░░░░░░█░░░█░" << endl;
        cout << "──────░█░░░░░░░░█░░░█░" << endl;
        cout << "──────░█░░░░░░░░░░░░█░" << endl;
        cout << "──────░█░░░░░░░░░░░░░█░" << endl;
        cout << "──────░█░░░░░░░░░░░░░█░" << endl;
        cout << "████──░█░████░░░░░░░░█░" << endl;
        cout << "█──█──████──████░░░░░█░" << endl;
        cout << "█──█──█──█──█──████████" << endl;
        cout << "█──█──████──█──█──────█" << endl;
        cout << "█──█──█──█────██──██──█" << endl;
        cout << "█──████──█──█──█──────█" << endl;
        cout << "█─────█──█──█──█──█████" << endl;
        cout << "███████──████──█──────█" << endl;
        cout << "──────████──██████████" << endl;

        sleep(milliseconds);        
        clear();
    #endif
}
void esplosione(int milliseconds){
    sleep(milliseconds/2);
    clear();

    #if defined(__APPLE__) || defined(__linux__)
        cout << "´´´´´´´´´´´´´´´´´´´´´´´$¶´´´´´¶´´´´´¶¢" << endl;
        cout << "´´´´´´´´´´´¶¶¶¶¶¶¶´´´´´´´¶¢´´´¶´´´ø¶" << endl;
        cout << "´´´´´´´´´´¶¶´´´´ø¶¶¶´´´´´´oø´´ø´´øo" << endl;
        cout << "´´´´´´´´´´¶7´´´´´´´¶¶¶´´´´´´1´´´1´´´´1o" << endl;
        cout << "´´´´´´´¶¶¶¶¶¶¶´´´´´´´¶¶¶7´´´´´´´´1o¶¶¶ø" << endl;
        cout << "´´´´´´´¶¶¶¶¶¶¶´´´´´´´´´¶¶¶¶¶¶¶¶´´1" << endl;
        cout << "´´´´´o¶¶¶¶¶¶¶¶¶ø´´´´´´´´´´´´´´´´´´o$¢" << endl;
        cout << "´´´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´´´´´´´´´´¢´´1ø´´´1¶¶" << endl;
        cout << "´´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶o´´´´´´´1$´´´¶" << endl;
        cout << "´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´´´´´´´¶´´´´o¶´" << endl;
        cout << "´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´´´´´¶¶" << endl;
        cout << "´´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´" << endl;
        cout << "´´´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´" << endl;
        cout << "´´´´´¶¶¶¶¶¶¶¶¶¶¶¶´" << endl;
        cout << "´´´´´´´¶¶¶¶¶¶¶¶" << endl;
                
        sleep(milliseconds);
        clear();

        cout << "´´´´´´´´´´´´´´´´´´´´´´´$¶´´´´´¶´´´´´¶¢" << endl;
        cout << "´´´´´´´´´´´¶¶¶¶¶¶¶´´´´´´´¶¢´´´¶´´´ø¶" << endl;
        cout << "´´´´´´´´´´¶¶´´´´ø¶¶¶´´´´´´oø´´ø´´øo" << endl;
        cout << "´´´´´´´´´´¶7´´´´´´´¶¶¶´´´´´´1´´´1´´´´1o" << endl;
        cout << "´´´´´´´¶¶¶🔥¶¶´´´´´´´¶¶¶7´´´´´´´´1o¶¶¶ø" << endl;
        cout << "´´´´´´´¶¶¶¶¶¶¶´´´´´´´´´¶🔥¶¶¶¶¶´´1" << endl;
        cout << "´´´´´o🔥¶¶¶¶¶¶¶ø´´´´´´´´´´´´´´´´´´o$¢" << endl;
        cout << "´´´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´´´´´´´´´´¢´´1ø´´´1¶¶" << endl;
        cout << "´´¶¶¶¶¶¶¶¶¶¶🔥¶¶¶¶¶o´´´´´´´1$´´´¶" << endl;
        cout << "´¶¶¶🔥¶¶¶¶¶¶¶¶¶¶¶¶¶¶´´´´´´´¶´´´´o¶´" << endl;
        cout << "´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´´´´´¶¶" << endl;
        cout << "´´¶¶¶¶¶¶¶¶¶¶🔥¶¶¶¶¶¶´" << endl;
        cout << "´´´¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶´" << endl;
        cout << "´´´´´¶¶¶¶¶¶¶¶¶¶¶¶´" << endl;
        cout << "´´´´´´´¶¶¶¶¶¶¶¶" << endl;

        sleep(milliseconds);
        clear();

        cout << "´´´´´´´´´´´´´´´´´´´´´´´$¶´´´´´¶´´´´´¶¢" << endl;
        cout << "´´´´´´´´´´´¶¶¶🔥¶¶´´´´´´´¶¢´´´¶´´´ø¶" << endl;
        cout << "´´´´´´´´´´¶¶´´´´ø🔥¶´´´´´´oø´´ø´´øo" << endl;
        cout << "´´´´´´´´´´¶7´´´´´´´¶¶¶´´´´´´1´´´1´´´´1o" << endl;
        cout << "´´´´´´´¶¶¶🔥¶¶´´´´´´´¶¶¶7´´´´´´´´1o🔥¶ø" << endl;
        cout << "´´´´´´´¶¶¶¶¶¶¶´´´´´´´´´¶🔥¶¶🔥¶´´1" << endl;
        cout << "´´´´´o🔥¶¶🔥¶¶¶ø´´´´´´´´´´´´´´´´´´o$¢" << endl;
        cout << "´´´🔥¶¶¶¶¶¶¶¶¶¶¶¶¶´´´´´´´´´´¢´´1ø´´´1🔥" << endl;
        cout << "´´¶¶¶¶🔥¶¶¶¶🔥¶¶¶¶¶o´´´´´´´1$´´´¶" << endl;
        cout << "´¶¶¶🔥¶¶¶¶¶¶¶¶¶🔥¶¶¶´´´´´´´¶´´´´o¶´" << endl;
        cout << "´¶¶¶¶¶¶¶🔥¶¶¶¶¶¶¶¶¶¶¶´´´´´🔥" << endl;
        cout << "´´¶¶¶¶¶¶¶¶¶¶🔥¶¶¶¶¶¶´" << endl;
        cout << "´´´¶¶¶🔥¶¶¶¶¶¶¶¶¶¶¶´" << endl;
        cout << "´´´´´¶¶¶¶¶🔥¶¶¶¶¶´" << endl;
        cout << "´´´´´´´¶¶¶¶¶¶¶¶" << endl;

        sleep(milliseconds);
        clear();

        cout << "´´´´´´´´´´´´´´´´´´´´´´´🔥´´´´´🔥´´´´´¶¢" << endl;
        cout << "´´´´´´´´´´´¶¶¶🔥¶¶´´´´´´´¶¢´´´¶´´´ø¶" << endl;
        cout << "´´´´´´´´´´¶¶´´´´ø🔥¶´´´´´´oø´´ø´´øo" << endl;
        cout << "´´´´´´´´´´¶7´´´´´´´¶🔥´´´´´´1´´´1´´´´1o" << endl;
        cout << "´´´´´´´🔥¶🔥¶¶´´´´´´´🔥7´´´´´´´´1o🔥¶ø" << endl;
        cout << "´´´´´´´¶¶¶¶¶🔥´´´´´´´´´¶🔥¶¶🔥¶´´1" << endl;
        cout << "´´´´´o🔥¶¶🔥¶¶¶ø´´´´´´´´´´´´´´´´´´o$¢" << endl;
        cout << "´´´🔥¶¶¶¶¶¶¶¶🔥¶¶¶´´´´´´´´´´¢´´1ø´´´1🔥" << endl;
        cout << "´´¶¶¶¶🔥¶🔥¶🔥¶¶¶¶¶o´´´´´´´1$´´´¶" << endl;
        cout << "´🔥¶🔥¶¶¶¶¶🔥¶¶🔥¶¶¶´´´´´´´¶´´´´o¶´" << endl;
        cout << "´¶¶¶¶¶¶¶🔥🔥¶¶¶¶¶¶¶¶¶´´´´´🔥" << endl;
        cout << "´´¶🔥¶¶¶¶¶¶¶🔥¶¶¶¶¶¶´" << endl;
        cout << "´´´¶¶¶🔥🔥¶¶¶¶¶🔥¶¶´" << endl;
        cout << "´´´´´¶¶¶¶¶🔥¶¶🔥¶´" << endl;
        cout << "´´´´´´´¶🔥¶¶🔥¶" << endl;

        sleep(milliseconds);
        clear();

        cout << "   🔥🔥🔥  🔥🔥🔥" << endl;
        cout << "   🔥🔥 🔥🔥🔥🔥" << endl;
        cout << " 🔥🔥🔥 🔥🔥 🔥🔥 🔥🔥🔥" << endl;
        cout << "  🔥    🔥 🔥🔥🔥 🔥🔥🔥" << endl;
        cout << "   🔥🔥🔥🔥🔥🔥    🔥🔥🔥" << endl;
        cout << "  🔥🔥🔥🔥 🔥🔥    🔥🔥🔥🔥🔥🔥" << endl;
        cout << "    🔥  🔥🔥🔥🔥🔥🔥🔥" << endl;
        cout << "🔥🔥🔥🔥 🔥🔥🔥🔥    🔥🔥🔥 🔥🔥" << endl;
        cout << "     🔥 🔥🔥🔥    🔥🔥🔥🔥🔥🔥" << endl;
        cout << "    🔥🔥🔥 🔥🔥 🔥🔥🔥🔥🔥" << endl;
        cout << " 🔥🔥🔥🔥    🔥🔥 🔥🔥🔥 🔥🔥🔥" << endl;
        cout << "   🔥🔥🔥🔥🔥🔥    🔥 🔥🔥  🔥🔥🔥" << endl;
        cout << "    🔥🔥🔥🔥    🔥🔥🔥" << endl;
        cout << " 🔥🔥🔥 🔥🔥 🔥🔥🔥 🔥🔥🔥" << endl;

        sleep(milliseconds);
        clear();
    #endif
}
void fine(){
    cout << "Grazie per aver giocato!\n";
    cout << "Crediti:\n\tGallo Francesco\n\tDi Tullo Francesco\n\tD'Ambrosio Stefano\n";

    #if defined(__APPLE__) || defined(__linux__)
        cout << "\t\t────────────────────────────────────────" << endl;
        cout << "\t\t────────────────────────────────────────" << endl;
        cout << "\t\t───────────████──███────────────────────" << endl;
        cout << "\t\t──────────█████─████────────────────────" << endl;
        cout << "\t\t────────███───███───████──███───────────" << endl;
        cout << "\t\t────────███───███───██████████──────────" << endl;
        cout << "\t\t────────███─────███───████──██──────────" << endl;
        cout << "\t\t─────────████───████───███──██──────────" << endl;
        cout << "\t\t──────────███─────██────██──██──────────" << endl;
        cout << "\t\t──────██████████────██──██──██──────────" << endl;
        cout << "\t\t─────████████████───██──██──██──────────" << endl;
        cout << "\t\t────███────────███──██──██──██──────────" << endl;
        cout << "\t\t────███─████───███──██──██──██──────────" << endl;
        cout << "\t\t───████─█████───██──██──██──██──────────" << endl;
        cout << "\t\t───██████───██──────██──────██──────────" << endl;
        cout << "\t\t─████████───██──────██─────███──────────" << endl;
        cout << "\t\t─██────██───██─────────────███──────────" << endl;
        cout << "\t\t─██─────███─██─────────────███──────────" << endl;
        cout << "\t\t─████───██████─────────────███──────────" << endl;
        cout << "\t\t───██───█████──────────────███──────────" << endl;
        cout << "\t\t────███──███───────────────███──────────" << endl;
        cout << "\t\t────███────────────────────███──────────" << endl;
        cout << "\t\t────███───────────────────███───────────" << endl;
        cout << "\t\t─────████────────────────███────────────" << endl;
        cout << "\t\t──────███────────────────███────────────" << endl;
        cout << "\t\t────────███─────────────███─────────────" << endl;
        cout << "\t\t────────████────────────██──────────────" << endl;
        cout << "\t\t──────────███───────────██──────────────" << endl;
        cout << "\t\t──────────████████████████──────────────" << endl;
        cout << "\t\t──────────████████████████──────────────" << endl;
        cout << "\t\t────────────────────────────────────────" << endl;
    #endif
}
void clear(){
   #ifdef _WIN32
      system("cls");
   #elif defined(__APPLE__) || defined(__linux__)
      system("clear");
   #else
      cout << "Impossibile pulire lo schermo su questo sistema operativo." << << endl;
   #endif
}
int sleep(int milliseconds){
   #ifdef _WIN32
      Sleep(milliseconds);
   #elif defined(__APPLE__) || defined(__linux__)
      this_thread::sleep_for(chrono::milliseconds(milliseconds));
   #else
      cout << "Impossibile fermare l'esecuzione su questo sistema operativo." << endl;
   #endif
 
   return 0;
}