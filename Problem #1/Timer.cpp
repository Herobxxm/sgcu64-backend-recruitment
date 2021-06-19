#include <iostream>
#include <sstream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

using namespace std;


const vector<vector<bool>> Number_code = { // Display code for printing 7 Secment.
{true,true,false,true,true,true,true},// 0
{false,false,false,true,false,false,true},// 1
{true,false,true,true,true,true,false},// 2                      0
{true,false,true,true,false,true,true},// 3                     __
{false,true,true,true,false,false,true},// 4                1 2|__|3
{true,true,true,false,false,true,true},// 5                   4|__|6
{true,true,true,false,true,true,true},// 6                      5  
{true,true,false,true,false,false,true},// 7
{true,true,true,true,true,true,true},// 8
{true,true,true,true,false,true,true},// 9
{false,false,false,false,false,true,false} // 10 -> exception for input with time exception
};

void printer(vector<int> T_Digit){

//      This is how display should be.
//     __   __     __   __     __   __ 
//    |__| |__| · |__| |__| · |__| |__|
//    |__| |__| · |__| |__| · |__| |__| 
//      
//      This function will get the number and print it here.

// line one
    cout << "    ";
    for(int i = 0; i < 6;i++){
        if(i == 2 || i == 4) cout << "   ";
        
        if(Number_code[T_Digit[i]][0]){
            cout << " __ ";
        }else cout << "    ";
    }
    cout << endl;
// line two
    cout << "    ";
    for(int i = 0; i < 6;i++){
        if(i == 2 || i == 4) cout << " . ";
        
        if(Number_code[T_Digit[i]][1]){
            cout << "|";
        }else cout << " ";

        if(Number_code[T_Digit[i]][2]){
            cout << "__";
        }else cout << "  ";

        if(Number_code[T_Digit[i]][3]){
            cout << "|";
        }else cout << " ";
    }
    cout << endl;
// line three
    cout << "    ";
    for(int i = 0; i < 6;i++){
        if(i == 2 || i == 4) cout << " . ";
        
        if(Number_code[T_Digit[i]][4]){
            cout << "|";
        }else cout << " ";

        if(Number_code[T_Digit[i]][5]){
            cout << "__";
        }else cout << "  ";

        if(Number_code[T_Digit[i]][6]){
            cout << "|";
        }else cout << " ";
    }
}

void Clear_console() // Just clear console
{
    cout << flush;
    system("CLS");
}

bool Time_Count(vector<int> &Time){ // Use to count the clock down
    if(Time[0] == 0 && Time[1] == 0 && Time[2] == 0 && Time[3] == 0 && Time[4] == 0 && Time[5] == 0){
        return true;
    }
    if(Time[5] == 0){
        Time[5] = 9;
        if(Time[4] == 0){
            Time[4] = 5;
            if(Time[3] == 0){
                Time[3] = 9;
                if(Time[2] == 0){
                    Time[2] = 5;
                    if(Time[1] == 0){
                        Time[1] = 9;
                        Time[0]--;
                    }else Time[1]--;
                }else Time[2]--;
            }else Time[3]--;
        }else Time[4]--;
    }else Time[5]--;
    return false;
}

void Animated_TimeCount(vector<int> Time){ // Animated clock
    Clear_console();
    while(true){
        printer(Time);
        Sleep(700);
        Clear_console();
        Sleep(300);
        if(Time_Count(Time))break;
    }
    Clear_console();
    cout << "                    ___    ___   ___    _____   " << endl;
    cout << "     |  /    __    |   |  |   | |   |  |  |  |  " << endl;
    cout << "     |--    |__|   |      |   | |   |  |  |  |  " << endl;
    cout << "     |  |   |  |   |___|  |___| |___|  |  |  |  " << endl;

}

int main(){
    string Command;
    cout << "input: ";
    cin >> Command;  // get Data.
    vector<int> Time;
    stringstream SS(Command);
    for(int i; SS >> i;){
        Time.push_back(i);
        if(SS.peek() == ':' || SS.peek() == ' ')
            SS.ignore();
    }
    bool is_Valid = true;
    int a = Time[0]/10;
    int b = Time[0]%10;
    int c = Time[1]/10;
    int d = Time[1]%10;
    int e = Time[2]/10;
    int f = Time[2]%10;
    if(Time[1] >= 60){
        c = 10; d = 10; is_Valid = false;
    }
    if(Time[2] >= 60){
        e = 10; f = 10; is_Valid = false;
    }
    vector<int> Time_digit = {a,b,c,d,e,f}; // get number from data u type. plz dont mind about the method
    printer(Time_digit);
    cout << endl;
    if(is_Valid){ // check if time we put is valid or can be count down.
        string Choice;
        while(true){
        cout << endl << endl << "Do u want me to count the clock down?(y/n) : ";
        cin >> Choice;
        if(Choice == "n" || Choice == "N")break;
        if(Choice == "y" || Choice == "Y"){
            Animated_TimeCount(Time_digit); // Animated clock
            break;
        }
        cout << "Plese insert only /'y/' or /'n/'" << endl; 
        }

    }else{
        cout << "The time u set can not count down."; 
    }
    cout << endl;
    system("PAUSE");
}