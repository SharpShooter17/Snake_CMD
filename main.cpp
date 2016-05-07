#include "snake.h"
using namespace std;

void Welcome();
void Menu();
void PLAY();
void Control();
void WPISZ_NICK();
//void Ranking();

string NICK = "Brak";

int main()
{
    Welcome();
    Menu();
    return 0;
}

void Welcome()
{
    cout << "\n\n\t\t\t=== SNAKE 2014! ===\n\n\n\t\t\t\t\tBy Bartek";
    Sleep(3000);
    cls();
}

void Menu()
{
    cls();
    cout <<"1: Podaj nick\n2: Gra!\n3: Sterowanie\n0: Wyjscie :(\nTwoj wybor: ";
    int wybor;
    while ( !(cin >> wybor))
    {
        cin.clear();
            while(cin.get()!= '\n')
                continue;
        cout <<"\nNie ma takiej funkcji!\nWybierz jeszcze raz: ";
    }
    switch(wybor)
    {
        case 1: WPISZ_NICK();
            break;
        case 2: PLAY();
            Menu();
            break;
        case 3: Control();
            Menu();
            break;
        case 0: system("exit");
            break;
        /*case 'x': Ranking();
            break;*/
        default:
            cout << "Nie ma takiej funkcji!\n";
            Menu();
            break;
    }
}

void PLAY()
{
    SsSnake GAME(NICK);
    GAME.Reset_Map();
    while (GAME.PLAY())
    {
        GAME.Show_Map();
        GAME.Set_ogon();
        GAME.Set_Snake();
        GAME.ruch();
        cls();
    }
    GAME.Reset_Map();
    getch();
}

void WPISZ_NICK()
{
    cls();
    cout <<"Podaj swój nick: ";
    cin >> NICK;
    Menu();
}

void Control()
{
    cls();
    cout << "W - gora\n"
            "S - dol\n"
            "A - lewo\n"
            "D - Prawo\n"
            "P - pauza\n"
            "ESC - wyjscie\n"
            "\nNacisnij dowolny klawisz aby wrocic do menu...";
    getch();
}
/* ranking graczy z pliku Scores.dat - do modyfikacji nie dziala jak powinno
 void Ranking()
 {
     cls();
    fstream plik("Scores.dat", ios_base::out);
    plik.seekg(0);
    if (plik.is_open())
    {
        string str;
        while (!plik.eof())
        {
            cout << str<<"\n";
        }
    }
    else
    {
        cout << "Brak pliku Scores.dat!";
        plik.close();
    }
    cout <<"Nacisnij dowolny klawisz by wrocic do menu!" ;
    getch();
    Menu();
 }
*/
