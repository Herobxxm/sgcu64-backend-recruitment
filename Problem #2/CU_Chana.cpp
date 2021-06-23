#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<string, string> P_Number;      // Collect phone number pair with place(P_number, Place)
map<string, vector<string>> Place; // Collect All place pair with vecter contain all Phone number

// Text color zone
void color_text(int color, string text) // color = 7 white  color = 12 red
{ 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    cout << text << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void set_cursor_pos(int x, int y) // set curser
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
COORD get_cursor_pos()  // get curser
{
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo))
        printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
    COORD Pos;
    Pos.X = screenBufferInfo.dwCursorPosition.X;
    Pos.Y = screenBufferInfo.dwCursorPosition.Y;
    return Pos;
}

string Add_Location(){ // Add location.( A little bit complicated because my special effect.)
    string Pla;
    COORD A = get_cursor_pos();
    while(true){
        set_cursor_pos(A.X,A.Y);
        cout << "Location name :";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            ShowCursor(TRUE);
            getline(cin, Pla);
            ShowCursor(FALSE);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        if (Place.find(Pla) == Place.end())
            {
            cout << "   Location Added!!!" << endl;
            Place[Pla] = {};
            Sleep(800);
            return Pla;
            }
            else
            {
            cout << "   Already have this location!!!!" << endl;
            set_cursor_pos(A.X,A.Y);
            cout << "                                                                   "<< endl;
            cout << "                                                                   "<< endl;
            set_cursor_pos(A.X,A.Y);
            Sleep(800);
            }
    }
}

void initialize_data() // Initialize data for the beginning of this program.
{
    cout << "Welcome to CU_Chana app." << endl;
    cout << "This is the program setup." << endl;
    cout << "This program must have at least 5 location to start the program." << endl;
    string A;
    for (int i = 0; i < 5; i++)
    {
        Add_Location();
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "Finished setup!!!" << endl;
    cout << "Plz enjoy my program." << endl;
    cout << "_____________________________________________________" << endl;
}

int choice(vector<string> Ch) // For display choice and return choice you choose
{
    COORD A = get_cursor_pos();
    int C = 0;
    char Key;
    int X[Ch.size()];
    while (true)
    {
        set_cursor_pos(A.X, A.Y);
        for (int i = 0; i < Ch.size(); i++)
            X[i] = 7;
        X[C] = 12;
        for (int j = 0; j < Ch.size(); j++)
        {
            string prt = "   " + to_string(j + 1) + ". " + Ch[j];
            color_text(X[j], prt);
        }
        while (true)
        {
            Key = _getch(); // Checking input aero key or enter key
            if (Key == 72 && (C > 0))
            {
                C--;
                break;
            }
            if (Key == 80 && (C < Ch.size() - 1))
            {
                C++;
                break;
            }
            if (Key == '\r')
            {
                return C;
            }
        }
        ShowCursor(FALSE);
    }
}


int menu() // main menu function (dont confuse with main function)
{
    ShowCursor(FALSE);
    cout << "Welcome to Chula Chana!!!!" << endl;
    cout << "Avalible commands" << endl;
    vector<string> Select = {"Check in user", "Check out user", "Print people count", "Edit location"};
    int Ret = choice(Select);
    cout << "_____________________________________________________" << endl;
    return Ret;
}

void CheckIn() // checkin function
{
    string Ph_Number;
    cout << "Check In" << endl;
    cout << "Enter  phone number: ";
    ShowCursor(TRUE);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cin >> Ph_Number;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    ShowCursor(FALSE);
    while (true)
    {
        cout << "Check in place" << endl;
        vector<string> choic;
        for (auto i = Place.begin(); i != Place.end(); i++)
        {
            choic.push_back(i->first);
        }
        choic.push_back("add location");
        int A = choice(choic);
        if (A != Place.size())
        {
            if (P_Number.find(Ph_Number) != P_Number.end())
            {
                string p = P_Number[Ph_Number];
                Place[p].erase(find(Place[p].begin(), Place[p].end(), Ph_Number));
            }
            P_Number[Ph_Number] = choic[A];
            Place[choic[A]].push_back(Ph_Number);
            cout << "Check in successfully" << endl;
            Sleep(1500);
            cout << "_____________________________________________________" << endl;
            return;
        }
        else
        {
            Add_Location();
        }
    }
}

void CheckOut() // check out function
{
    string Ph_Number;
    cout << "Check In" << endl;
    cout << "Enter  phone number: ";
    ShowCursor(TRUE);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cin >> Ph_Number;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "Checking out . . .";
    if (P_Number.find(Ph_Number) != P_Number.end())
    {
        string p = P_Number[Ph_Number];
        Place[p].erase(find(Place[p].begin(), Place[p].end(), Ph_Number));
        P_Number.erase(Ph_Number);
    }
    Sleep(1500);
    cout << endl
         << "Check out successfully." << endl;
    Sleep(1500);
    cout << "_____________________________________________________" << endl;
}

void Check_Population() // Check out function
{
    cout << "Current Population:" << endl;
    int C = 1;
    for (auto i = Place.begin(); i != Place.end(); i++)
    {
        cout << C << ". " << i->first << " : " << i->second.size() << endl;
        C++;
    }
    Sleep(1500);
    cout << "_____________________________________________________" << endl;
}

void Edit_Place() // Edit information function
{
    while (true)
    {
        char Key;
        COORD A = get_cursor_pos();
        cout << "Edit menu!!!" << endl;
        COORD B = get_cursor_pos();
        set_cursor_pos(B.X, B.Y);
        vector<string> Select = {"Add location", "Remove location", "Exit"};
        int Ch = choice(Select); // get your choice
        // if choice == ???
        if (Ch == 0) // Add location
        {
            string Ad = Add_Location();
            set_cursor_pos(A.X, A.Y);
            for (int i = 0; i < 6; i++)
                cout << "                                                      " << endl;
            set_cursor_pos(A.X, A.Y); 
            cout << " Add " << Ad << " as a new location." << endl;
            cout << "_____________________________________________________" << endl;
        }
        if (Ch == 1) // Remove location
        {
            set_cursor_pos(B.X, B.Y);
            for (int i = 0; i < 6; i++)
                cout << "                                                      " << endl;
            set_cursor_pos(B.X, B.Y);
            cout << " Remove location?" << endl;
            vector<string> choic;
            for (auto i = Place.begin(); i != Place.end(); i++)
            {
                choic.push_back(i->first);
            }
            choic.push_back("Cancel");
            int Cho = choice(choic);
            set_cursor_pos(B.X, B.Y);
            for (int i = 0; i < Place.size() + 6; i++)
                cout << "                                                 " << endl;
            set_cursor_pos(B.X, B.Y);
            if (Cho == Place.size())
            {
                cout << " Canceled!!!" << endl;
                Sleep(1500);
                set_cursor_pos(A.X, A.Y);
                for(int i = 0; i < Place.size()+5; i++)
                cout << "                                                        " << endl;
                set_cursor_pos(A.X, A.Y);
            }
            else
            {
                Place.erase(choic[Cho]);
                cout << " Erased " << choic[Cho] << " !!!!!!";
                set_cursor_pos(A.X, A.Y);for(int i = 0; i < Place.size()+5; i++)
                cout << "                                                     " << endl;
                set_cursor_pos(A.X, A.Y);
                Sleep(1500);
                cout << " Erased " << choic[Cho] << " !!!!!!" << endl;
                cout << "_____________________________________________________" << endl;
            }
        }
        if (Ch == 2) // Exit this menu
        {
            set_cursor_pos(A.X, A.Y);
            for (int i = 0; i < 6; i++)
                cout << "                                                 " << endl;
            set_cursor_pos(A.X, A.Y);
            return;
        }
    }
}

int main()
{
    initialize_data(); // initialize program
    while (true)
    {
        int X = menu(); // Main menu
        switch (X) // choice???
        {
        case 0: // Check in
            CheckIn();
            break;
        case 1: // Check out
            CheckOut();
            break;
        case 2: // Check people
            Check_Population();
            break;
        case 3: // Edit menu( it is optional. )
            Edit_Place();
            break;
        }
    }
}