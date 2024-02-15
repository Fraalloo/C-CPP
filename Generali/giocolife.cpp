#include <iostream>

#ifdef __APPLE__
    #include <unistd.h>
#elif __linux__
    #include <cstdlib>
#elif _WIN32
    #include <windows.h>
#endif

using namespace std;

#define ROW 46
#define COL 46

void initBin(int[][COL], int, int, int);
void visual(int[][COL], int, int);
int cercaIntorno(int[][COL], int, int, int);
int cerca(int[][COL], int, int, int);
bool verificaUguaglianza(int[][COL], int[][COL], int, int);
void cambio(int[][COL], int[][COL], int, int);
void clear();

int main(){
    srand(time(0));
    int mat1[ROW][COL] = {0};
    int mat2[ROW][COL] = {0};
    int contCicli = 0;

    initBin(mat1, ROW, COL, 20);
    visual(mat1, ROW, COL);
    getchar();
    clear();

    while(true){
        if(contCicli % 2 == 0){
            cambio(mat1, mat2, ROW, COL);
            visual(mat2, ROW, COL);

            if(cerca(mat2, ROW, COL, 1) == 0){
                cout << "Le cellule sono morte\n";
                break;
            }else if(verificaUguaglianza(mat1, mat2, ROW, COL)){
                cout << "Le cellule sono in una configurazione stabile\n";
                break;
            }
        }else{
            cambio(mat2, mat1, ROW, COL);
            visual(mat1, ROW, COL);
        }

        getchar();
        clear();
        contCicli++;
    }

    return 0;
}

void initBin(int mat[][COL], int row, int col, int percentuale){
    int num;
    for(int i = 1; i < row - 2; i++){
        for(int j = 1; j < col - 2; j++){
            num = rand() % 101;
            if(num >= 0 && num <= 100 - percentuale) mat[i][j] = 0;
            else mat[i][j] = 1;
        }
    }
}
void visual(int mat[][COL], int row, int col){
    for(int i = 1; i < row - 2; i++){
        for(int j = 1; j < col - 2; j++){
            if (mat[i][j] == 1) cout << "x";
            else cout << ".";
            cout << " ";
        }
        cout << endl;
    }
}
int cerca(int mat[][COL], int row, int col, int val){
    int cont = 0;
    for(int i = 1; i < row - 2; i++){
        for(int j = 1; j < col - 2; j++){
            if (mat[i][j] == val)
                cont++;
        }
    }
    return cont;
}
int cercaIntorno(int mat[][COL], int row, int col, int val){
    int cont = 0;
    for(int i = row - 1; i < row + 2; i++){
        for(int j = col - 1; j < col + 2; j++){
            if (i == row && j == col) continue;
            if (mat[i][j] == val) cont++;
        }
    }
    return cont;
}
bool verificaUguaglianza(int mat1[][COL], int mat2[][COL], int row, int col){
    for (int i = 1; i < row - 1; i++){
        for(int j = 1; j < col - 1; j++){
            if(mat1[i][j] != mat2[i][j]) return false;
        }
    }
    return true;
}
void cambio(int mat1[][COL], int mat2[][COL], int row, int col){
    for(int i = 1; i < row - 2; i++){
        for(int j = 1; j < col - 2; j++){
            int intorno = cercaIntorno(mat1, i, j, 1);
            if(mat1[i][j] == 0 && intorno == 3) mat2[i][j] = 1;
            else if (mat1[i][j] == 1 && (intorno == 2 || intorno == 3)) mat2[i][j] = 1;
            else mat2[i][j] = 0;
        }
    }
}
void clear(){
    #ifdef _WIN32
        system("cls");
    #elif __APPLE__
        system("clear");
    #elif __linux__
        system("clear");
    #endif
}