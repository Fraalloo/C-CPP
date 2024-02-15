/*
    Francesco Gallo e Stefano D'Ambrosio
*/

#include <iostream>

// Parte copiata
#ifdef __APPLE__
#include <unistd.h>
#elif __linux__
#include <cstdlib>
#elif _WIN32
#include <windows.h>
#endif

using namespace std;

#define MAXERR 7
#define MAXLET 26
#define MAXPAR 12

// Funzioni per i caratteri
int lunghezza(char[]);
void convertiInMinuscoloCarattere(char&);
void convertiInMinuscoloArray(char[]);
bool validitàCaratteri(char[]);
bool validitàParola(char[]);
bool verificaUguaglianza(char[],char[]);
bool cerca(char[],int,char);

// Funzioni per L'impiccato
void personaggio(int);
char chiediLettera();
void mostraLettereTrovate(char[],char[],char[]);
void storico(char[],bool[],int);

// Funzioni di fine programma
void risultato(bool,char[]);
void azzera(char[],char, int);
void fine();
void clear();

int main(){
    // Introduzione
    cout << "-----> IMPICCATO <-----\n";
    cout << "Benvenuto nel gioco de L'impiccato!\n";

    char parola[MAXPAR] = {'\0'};// Immagazzina la parola iniziale, inizializzata a '\0' per usarlo nei cicli
    char tentativi[MAXPAR] = {'\0'};// Immagazzina la parola da confrontare con la parola iniziale, inizializzata a '\0' per usarlo nei cicli
    char copia[MAXPAR];// Immagazzina la parola da mostrare, contenente lettere e '_'
    char lettera;// Lettera da inserire

    char storicoLettere[MAXLET] = {'\0'};// Immagazzina le lettere inserite in ordine cronologico
    bool storicoErrori[MAXLET];// Immagazzina gli errori delle relative lettere inserite in ordine cronologico

    bool vittoria;// Stato della vittoria
    char ripetere = 'y';// Risposta dell'utente per rigiocare

    while(ripetere=='Y'||ripetere=='y'){
        // Richiesta parola da indovinare
        while(true){
            cout << "Inserire la parola da indovinare, massimo 12 caratteri: ";
            cin >> parola;
            if(validitàParola(parola)) break;
        }
        clear();

        int cont = 0;// Conta le lettere inserite
        
        // Inizio gioco
        for(int i = 0/*Conta gli errori fatti*/; i < MAXERR;cont++){
            // Rappresentazione grafica dell'impiccato
            personaggio(i);
            mostraLettereTrovate(parola,copia,storicoLettere);

            if(i == MAXERR - 1){
                cout << "Hai commesso il massimo di errori, ultimo tentativo per indovinare la parola: ";
                cin >> tentativi;
                convertiInMinuscoloArray(tentativi);
                if(verificaUguaglianza(parola,tentativi)) vittoria = true;
                else vittoria = false;
                break;
            }
            
            // Richiesta lettera
            while(true){
                lettera = chiediLettera();
                convertiInMinuscoloCarattere(lettera);
                if(cerca(storicoLettere,MAXLET,lettera)) cout << "Lettera già inserita, riprova\n";
                else if(lettera<'a'||lettera>'z') cout << "Lettera invalida, riprova\n";
                else{
                    storicoLettere[cont] = lettera;
                    break;
                }
            }
            if(cerca(parola,lunghezza(parola),lettera)) storicoErrori[cont] = false;
            else{
                storicoErrori[cont] = true;
                i++;
            }
            mostraLettereTrovate(parola,copia,storicoLettere);
            cout << endl;

            if(verificaUguaglianza(parola,copia)){
                vittoria = true;
                break;
            }

            short scelta;

            do{
                cout << "Scegli l'opzione:\n";
                cout << "1) Continuare\n2) Indovinare\n3) Rinunciare\n";
                cin >> scelta;
            }while(scelta<1||scelta>3);
            
            if(scelta!=1){
                switch(scelta){
                    case 2:
                        cout << "Tenta di indovinare la parola: ";
                        cin >> tentativi;
                        convertiInMinuscoloArray(tentativi);
                        if(verificaUguaglianza(parola,tentativi)) vittoria = true;
                        else vittoria = false;
                        break;
                    case 3:
                        vittoria = false;
                        break;
                }
                break;
            }

            // Storico
            clear();
            cout << "Storico:\n";
            storico(storicoLettere,storicoErrori,cont);
        }

        // Mostra risultato
        risultato(vittoria,parola);

        // Chiedi di ripetere
        do{
            cout << "Vuoi rigiocare?(Y/n): ";
            cin >> ripetere;
            convertiInMinuscoloCarattere(ripetere);
        }while(ripetere!='y'&&ripetere!='n');
        clear();
        
        azzera(parola,'\0',MAXPAR);
        azzera(tentativi,'\0',MAXPAR);
        azzera(storicoLettere,'\0',MAXLET);
    }

    cout << "Grazie di aver usato il programma!!!!!!!!!! :)))\n";
    fine();

    return 0;
}

// Funzioni per i caratteri
int lunghezza(char parola[]){
    // Conta la lunghezza della parola inserita
    int len = 0;
    for(int i = 0; parola[i]!='\0';i++){
        len++;
    }
    return len;
}
void convertiInMinuscoloCarattere(char& lettera){
    if(lettera>='A'&&lettera<='Z') lettera += ' ';
}
void convertiInMinuscoloArray(char parola[]){
    for(int i = 0; i < lunghezza(parola); i++){
        convertiInMinuscoloCarattere(parola[i]);
    }
}
bool validitàCaratteri(char parola[]){
    for(int i = 0; i < lunghezza(parola); i++){
        // Controlla se il carattere è una lettera minuscola
        if(!(parola[i]>='a'&&parola[i]<='z')) return false;
    }
    return true;
}
bool validitàParola(char parola[]){
    convertiInMinuscoloArray(parola);
    if(parola[2]=='\0'&&!validitàCaratteri(parola)){
        // Se la parola ha meno di tre caratteri e contiene non solo lettere
        cout << "Parola troppo corta e invalida, almeno tre caratteri e soltanto lettere\n";
        return false;
    }else if(parola[2]=='\0'){
        // Se la parola ha meno di tre caratteri
        cout << "Parola troppo corta, almeno tre caratteri\n";
        return false;
    }else if(!validitàCaratteri(parola)){
        // Se la parola contiene non solo lettere
        cout << "Parola invalida, soltanto lettere\n";
        return false;
    }
    return true;
}
bool verificaUguaglianza(char parola1[],char parola2[]){
    for(int i = 0;  i < MAXPAR; i++){
        // Controlla se ogni carattere della parola è uguale
        if(parola1[i]!=parola2[i]) return false;
    }
    return true;
}
bool cerca(char arr[],int size,char val){
    for(int i = 0;i<size;i++){
        if(arr[i]==val) return true;
    }
    return false;
}

// Funzioni per L'impiccato
void personaggio(int errori){
    // In base agli errori, mostra un impiccato di livello diverso
    switch(errori){
        case 0:
            cout << "   ____" << endl;
            cout << "  |    |" << endl;
            cout << "       |" << endl;
            cout << "       |" << endl;
            cout << "       |" << endl;
            cout << "      /|\\" << endl;
            cout << "=========" << endl;
            break;
        case 1:
            cout << "   ____" << endl;
            cout << "  |    |" << endl;
            cout << "  O    |" << endl;
            cout << "       |" << endl;
            cout << "       |" << endl;
            cout << "      /|\\" << endl;
            cout << "=========" << endl;
            break;
        case 2:
            cout << "   ____" << endl;
            cout << "  |    |" << endl;
            cout << "  O    |" << endl;
            cout << "  |    |" << endl;
            cout << "       |" << endl;
            cout << "      /|\\" << endl;
            cout << "=========" << endl;
            break;
        case 3:
            cout << "   ____" << endl;
            cout << "  |    |" << endl;
            cout << "  O    |" << endl;
            cout << " /|    |" << endl;
            cout << "       |" << endl;
            cout << "      /|\\" << endl;
            cout << "=========" << endl;
            break;
        case 4:
            cout << "   ____" << endl;
            cout << "  |    |" << endl;
            cout << "  O    |" << endl;
            cout << " /|\\   |" << endl;
            cout << "       |" << endl;
            cout << "      /|\\" << endl;
            cout << "=========" << endl;
            break;
        case 5:
            cout << "   ____" << endl;
            cout << "  |    |" << endl;
            cout << "  O    |" << endl;
            cout << " /|\\   |" << endl;
            cout << " /     |" << endl;
            cout << "      /|\\" << endl;
            cout << "=========" << endl;
            break;
        case 6:
            cout << "   ____" << endl;
            cout << "  |    |" << endl;
            cout << "  O    |" << endl;
            cout << " /|\\   |" << endl;
            cout << " / \\   |" << endl;
            cout << "      /|\\" << endl;
            cout << "=========" << endl;
            break;
    }
}
char chiediLettera(){
    char lettera;
    cout << "Inserire una lettera: ";
    cin >> lettera;
    return lettera;
}
void mostraLettereTrovate(char parola[],char copia[],char storico[]){
    for(int i = 0; i < MAXPAR;i++){
        // Se una lettera inserita si trova nella parola mostra la lettera, altrimenti mostra '_'
        if(cerca(storico,MAXLET,parola[i])) copia[i] = parola[i];
        else copia[i] = '_';
    }
    cout << "Parola: "<< copia << endl;
}
void storico(char storicoLettere[],bool storicoErrori[],int errori){
    for(int i = 0; i < errori + 1;i++){
        // Mostra ogni lettera inserita, dicendo se è stata corretta o errata
        cout << "La " << i+1 << "^ lettera inserita è '" << storicoLettere[i] << "' --> ";
        if(storicoErrori[i]) cout << "Errato";
        else cout << "Corretto";
        cout << endl;
    }
    cout << endl;
}

// Funzioni di fine programma
void risultato(bool vittoria, char parola[]){
    cout << endl;
    if(vittoria) cout << "COMPLIMENTI HAI VINTO!!!!!!! :)\n";
    else cout << "PECCATO HAI PERSO!!!!!!! :(, la parola era " << parola << endl;
}
void azzera(char arr[],char c,int size){
    // Riporta ogni array allo stato iniziale
    for(int i = 0; i < size; i++){
        arr[i] = c;
    }
}
void fine(){
    cout << "  ***   ***  \n";
    cout << " *###* *###* \n";
    cout << " *####*####* \n";
    cout << " *#########* \n";
    cout << "  *#######*  \n";
    cout << "   *#####*   \n";
    cout << "    *###*    \n";
    cout << "     *#*     \n";
    cout << "      *      \n";
}
void clear(){
    // Parte copiata
    #ifdef _WIN32
        system("cls");
    #elif __APPLE__
        system("clear");
    #elif __linux__
        system("clear");
    #endif
}