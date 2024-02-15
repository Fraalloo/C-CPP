#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool repeat(char[20]);
void invertiStringa(char*);
bool controllo(char[],int);
int exToDec(char[],int);
char *decToEx(int,int);
int stringToInt(char[]);
int decToBase(int,int);
int toDec(int,int);

#define SPAZIO 20

int main(){
    int base;
    char valoreString[SPAZIO];
    int valoreInt;
    int mod;

    do{
        printf("---> Calcolatrice Programmatore <---\n");
        while(true){
            printf("Inserire base di partenza (2-36): ");
            scanf("%d",&base);
            printf("Inserire valore da convertire: ");
            scanf("%s",valoreString);
            
            if(controllo(valoreString,base)) break;

            printf("Valori invalidi, riprova\n\n");
        }

        if(base>=11&&base<=36) valoreInt = exToDec(valoreString,base);
        else if(base==10) valoreInt = stringToInt(valoreString);
        else{
            valoreInt = stringToInt(valoreString);
            valoreInt = toDec(valoreInt,base);
        }

        do{
            printf("Vuoi vedere le conversioni più importanti o tutte (0-1)?: ");
            scanf("%d",&mod);
        }while(mod<0||mod>1);
        
        switch(mod){
            case 0:
                if(base==2) printf("Bin\t%s\n",valoreString);
                else printf("Bin\t%d\n",decToBase(valoreInt,2));

                if(base==8) printf("Oct\t%s\n",valoreString);
                else printf("Oct\t%d\n",decToBase(valoreInt,8));

                printf("Dec\t%d\n",valoreInt);
            
                printf("Hex\t%s\n",(base==16)?valoreString:decToEx(valoreInt,16));
                break;
            case 1:
                for(int i = 2;i<=36;i++){
                    if(i==10) printf("Base 10     %d\n",valoreInt);
                    else if(i>=2&&i<=10) printf("Base %d      %d\n",i,decToBase(valoreInt,i));
                    else if(i>=11&&i<=36) printf("Base %d     %s\n",i,decToEx(valoreInt,i));
                }
                break;
        }
    }while(repeat("la conversione?"));
    
    printf("Grazie per aver usato il programma!\n");
    return 0;
}

void invertiStringa(char *str){
    int lunghezza = strlen(str);
    int i, j;

    for(i = 0, j = lunghezza - 1; i < j; i++, j--){
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}
bool controllo(char x[],int base){
    int dif = base - 11;
    if(base>=2&&base<=10){
        for(int i = 0; x[i] != '\0';i++){
            if(x[i]<'0'||x[i]>'0'+base-1) return false;
        }
        return true;
    }else if(base>=11&&base<=36){
        for(int i = 0; x[i] != '\0';i++){
            x[i] = toupper(x[i]);
            if(!((x[i]>='0'&&x[i]<='9')||(x[i]>='A'&&x[i]<='A'+dif))) return false;
        }
        return true;
    }
    return false;    
}
int stringToInt(char dec[]){
    int len = 0;
    int decc = 0;

    for(int i = 0;dec[i]!='\0';i++){
        len++;
    }

    for(int i = 0;dec[i]!='\0';i++){
        decc += (dec[i]-'0')*pow(10,len-1);
        len--;
    }

    return decc;
}
char *decToEx(int dec,int base){
    char *ex = malloc(8*sizeof(char));

    while(dec!=0){
        int resto = dec % base;
        if(resto<=9){
            char conc[2];
            conc[0] = resto+48;
            conc[1] = '\0';
            strcat(ex,conc);
        }else{
            char A[2] = "A";
            A[0] += resto-10;
            A[1] = '\0';
            strcat(ex,A);
        }
        dec /= base;
    }
    invertiStringa(ex);
    return ex;
}
int exToDec(char x[], int base){
    int ex = 0;
    int len = 0;
    int dif = base - 11;

    for(int i = 0;x[i]!='\0';i++){
        len++;
    }
    int pot = len-1;
    
    for(int i = 0;i<len;i++,pot--){
        x[i] = toupper(x[i]);
        if(x[i]>='0'&&x[i]<='9') ex += (x[i]-48)*pow(base,pot);
        else if(x[i]>='A'&&x[i]<='A'+dif) ex += (x[i]-55)*pow(base,pot);
    }
    return ex;
}
int decToBase(int dec,int base){
    int val = 0;
    int resto;
    int pot = 0;

    while(dec != 0){
        resto = dec % base;
        val += resto * pow(10, pot);
        dec /= base;
        pot++;
    }

    return val;
}
int toDec(int val,int base){
    int resto;
    int pot = 0;
    int dec = 0;

    while(val != 0){
        resto = val % 10;
        dec += resto * pow(base, pot);
        val /= 10;
        pot++;
    }

    return dec;
}
bool repeat(char x[20]){
    char repeatC;
    do{
        printf("Vuoi ripetere %s?(Y/n):\n",x);
        scanf(" %c",&repeatC);
        repeatC = toupper(repeatC);
    }while(repeatC!='Y'&&repeatC!='N');
    if(repeatC=='Y') return true;
    return false;
}