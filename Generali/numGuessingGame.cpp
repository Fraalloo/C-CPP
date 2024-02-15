#include <iostream>
#include <cmath>
#include <ctime>
using std::cout;
using std::string;
using std::endl;
using std::cin;

namespace f{
    string nameProgram = "NUMBER GUESSING GAME";
    string start1 = "*********************** ";
    string start2 = " ***********************";
    string ast = "*";
    string end;

    // Start Program Function
    void startProgram(string nameProgram){
        string start3 = nameProgram.append(start2);
        string start = start1.append(start3);
        cout << start << endl; 
    };

    // End Program Function
    void endProgram(string nameProgram){
        int l1 = 24;
        int l2 = 24;
        int l3 = nameProgram.length();
        int total = l1+l2+l3;
        for(int e=1; e<=total;e++){
            end.append(ast);
        }
        cout << end;
    };
}

int main(){
    // Declare Variables
    int num;
    int guess;
    int tries = 0;
    int max;

    // Start of Program
    f::startProgram(f::nameProgram);
    
    // Get Input 1
    cout << "What's the max number?" << endl;
    cin >> max;

    // Generate Random Number
    srand(time(0));
    num = rand() % max + 1;

    // Get Input 2
    do{
        cout << "Enter a guess between (1-" << max << ")" << endl;
        cin >> guess;
        tries++;
        if(guess > max){
            cout << "Your guess is higher than the max" << endl;
        }else if(guess < num){
            cout << "Too low" << endl;
        }else if(guess > num){
            cout << "Too high" << endl;
        }else{
            cout << "CORRECT! With a number of tries of " << tries << "!" << endl;
        }
    }while(guess!=num);
    
    // End of Program
    f::endProgram(f::nameProgram);
}
