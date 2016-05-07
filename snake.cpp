#include "snake.h"

void Sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

HANDLE hOut = GetStdHandle( STD_OUTPUT_HANDLE );
HANDLE g_hConsol = GetStdHandle(STD_OUTPUT_HANDLE);

SsSnake::SsSnake(string str) : x_head(10), y_head(35), Size_Snake(0), Punkty(0),
                                level(1), czas(0), Move('d'), Wskaznik_Tab(0),
                                x_ogon(9), y_ogon(35), Spid_Bonus(0), x_spid(-1), y_spid(-1) //konstruktor
{
    Reset_Map();
    Set_Award();
    Nick = str;
}
void SsSnake::Reset_Map() //resetuje mape
{
    for (int i = 0; i<=X_SIZE;i++)
        for (int j = 0; j<=X_SIZE;j++)
            PLANSZA[i][j] = Puste_Pole;
}

string granica(73, 176); // wyswietla****************************

void SsSnake::Show_Map() //wyswietla mape!
{
    cout << "Nick: "<<Nick;
    cout << " Punkty: "<<Punkty
        <<" level: "<<level
        <<" Dlugosc: "<<Size_Snake
        <<" szybkosc: "<<310 - Speed();
    if (Spid_Bonus > 0)
       cout <<" SPEED!"<<endl;
    else
        cout <<endl;
    SetConsoleTextAttribute( hOut, BACKGROUND_RED );
    cout << granica <<endl;
    for (int i = 0; i<=X_SIZE;i++)
    {
        SetConsoleTextAttribute( hOut, BACKGROUND_RED );
        cout <<(char) 176;
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
        for (int j = 0; j<=Y_SIZE;j++)
        {
            if (i == x_award && j == y_award)
                PLANSZA[i][j] = Nagroda;
            else if ( (i != x_award && j != y_award) && PLANSZA[i][j] == Nagroda )
                PLANSZA[i][j] = Puste_Pole;

            cout << (char) PLANSZA[i][j];
        }
        SetConsoleTextAttribute( hOut, BACKGROUND_RED );
        cout <<(char) 176 <<endl;
        SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED );
    }
    SetConsoleTextAttribute( hOut, BACKGROUND_RED );
    cout << granica<<endl;
    SetConsoleTextAttribute( hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
    cout << "X: "<<x_head<<" Y: "<<y_head<<" N: "<<x_award<<" M: "<<y_award;
}

void SsSnake::Set_Snake() // ustawia pozycje glowy weza
{
    cut_snake();
    PLANSZA[x_head][y_head] = Snake;
}

void SsSnake::Set_ogon()
{
    x_ogon = x_head;
    y_ogon = y_head;
}

void SsSnake::Set_Award() // ustawia nagrode
{
    srand(time(NULL));
    for (int i = 0; i<=X_SIZE;i++)
        for (int j = 0; j<=Y_SIZE;j++)
            if (PLANSZA[i][j] == Puste_Pole)
                {
                x_award = rand() % X_SIZE + 0;
                y_award = rand() % Y_SIZE + 0;
                }
    Size_Snake +=1;
    PLANSZA[x_award][y_award] = Nagroda;
}

bool SsSnake::PLAY()
{
        if (x_head > X_SIZE || y_head >Y_SIZE || x_head<0 || y_head<0) //Wyjscie poza mape - skucha!
    {
        cout << "SKUCHA!\n";
        Scores();
        return false;
    }

    for (int i = 0; i<=X_SIZE;i++) //Jesli glowa najedzie na cialo - SKUCHA!
    {
        for (int j = 0; j<=Y_SIZE;j++)
        {
            for (int k =0; k<Size_Snake;k++)
            if ( x_head == Ogon[k].a && y_head == Ogon[k].b ) //uderzyl w siebie jak to ma dzialac? :O
                {
                    cout << "Ugryzles sie - SKUCHA!\n";
                    Scores();
                    return false;
                }
        }
    }

    return true;
}

void SsSnake::ruch() //WASD
{
    int znak;
    if (kbhit())
    {
        znak = getch();
        if (znak == 'p' || znak == 'P')
        {
            while (!kbhit())
            {
                cls();
                cout << "\n\n\n\n\t\t\t\tPauza!\n\n\t\tAby wznowic nacisnij jeden z klawiszy ruchu!";
                Sleep(300);
            }
        }
            if ( (znak == 'A' || znak == 'a' ||znak == 'S' ||znak == 's' ||
                znak == 'D' ||znak == 'd' ||znak == 'W' ||znak == 'w' || znak == 27)) //znak 27 - escape - wyjscie - skucha p - pauza
                Move = znak;
    }
    switch(Move)
    {
    case 'A':
    case 'a': y_head-=1;
        break;
    case 'D':
    case 'd': y_head+=1;
        break;
    case 'W':
    case 'w': x_head-=1;
        break;
    case 'S':
    case 's': x_head+=1;
        break;
    }

    if (x_head == x_award && y_head == y_award) // ustawia nagrode po zjedeniu jej!
    {
        Punkty = Punkty + 10 + 10 * level;
        Set_Award();
        if (Size_Snake % 5 == 0)
        {
            level +=1;
        }
    }

    if (x_head == x_spid && y_head == y_spid) // Dodaje speeeeda!! :D
    {
        Spid_Bonus +=100;
        x_spid = -1;
        y_spid = -1;//usuwa bonus z mapy
        czas =120;
    }

    if (x_head == x_cut && y_head == y_cut) // skraca weza!! :D
    {
        Size_Snake = 3;
        x_cut = -1;
        y_cut = -1;//usuwa bonus z mapy
        czas = 40;
    }

    for (int i = 0; i<=X_SIZE;i++)   //zmienia glowe snake na cialo!
        for (int j = 0; j<=Y_SIZE;j++)
            if (PLANSZA[i][j] == Snake && i != x_head && j != y_head)
                PLANSZA[i][j] = Body;

    Set_ogon(x_ogon, y_ogon); //???

    if (czas == 0 && x_spid <= 0 && x_cut <=0)
    Losuj_bonus();
    else

    if (czas > 0)
        --czas;

    if (Spid_Bonus > 0)
        --Spid_Bonus;

    Sleep(Speed());
}



void SsSnake::cut_snake() // Rysuj cialo!
{
    for (int i = 0; i<=X_SIZE;i++)
        for (int j = 0; j<=Y_SIZE;j++)
            if (PLANSZA[i][j] != Nagroda && PLANSZA[i][j] != Spid && PLANSZA[i][j] != CUT)
            PLANSZA[i][j] = Puste_Pole;

    for (int i = 0; i<=X_SIZE;i++)
        for (int j = 0; j<=Y_SIZE;j++)
            for (int k = 0; k<Size_Snake;k++)
                if (i == Ogon[k].a && j == Ogon[k].b )
                    PLANSZA[i][j] = Body;
}

void SsSnake::Set_ogon(int c, int d)
{
    Ogon[Wskaznik_Tab].a = c;
    Ogon[Wskaznik_Tab].b = d;
    if (Size_Snake-1 <= Wskaznik_Tab)
        Wskaznik_Tab = 0;
    else
    Wskaznik_Tab++;
}

unsigned int SsSnake::Speed()
{
    if (Spid_Bonus > 0 && level < 25)
        return (300 - level * 10 - 40);
    else if (level < 25)
        return (300 - level * 10);
}

void SsSnake::Scores()
{
    cout <<"Twoj wynik:\n";
    cout <<"Nick: "<<Nick<<"\nLiczba punktow: "<<Punkty<<"\nLevel:"
            <<level<<"\nDlugosc Twojego snake: "<<Size_Snake;
    /* Zapis wyniku do pliku - do przerobienie - nie chce mi sie xD
    fstream inFile("Scores.dat", ios_base::out|ios_base::app);
    inFile <<"Nick:"<<Nick<<"\nLiczba punktow: "<<Punkty<<"\nLevel:"<<level
            <<"\nDlugosc Twojego snake: "<<Size_Snake<<endl<<endl;
    inFile.close();
    */
    cin.get();
    cin.get();
}

void SsSnake::Losuj_bonus()
{
    srand(time(NULL));
    switch( (rand() % 5 + 0) )
    {
        case 1: Bonus_SPEEDa();
            break;
        case 2: Skroc();
            break;
        case 0:
            break;
        default:
            break;
    }
}

void SsSnake::Bonus_SPEEDa()
{
    srand(time(NULL));
    for (int i = 0; i<=X_SIZE;i++)
        for (int j = 0; j<=Y_SIZE;j++)
            if (PLANSZA[i][j] == Puste_Pole)
                {
                x_spid = rand() % X_SIZE + 0;
                y_spid = rand() % Y_SIZE + 0;
                }
    PLANSZA[x_spid][y_spid] = Spid;
}

void SsSnake::Skroc()
{
    if (Size_Snake > 40)
    {
        srand(time(NULL));
        for (int i = 0; i<=X_SIZE;i++)
            for (int j = 0; j<=Y_SIZE;j++)
                if (PLANSZA[i][j] == Puste_Pole)
                    {
                    x_cut = rand() % X_SIZE + 0;
                    y_cut = rand() % Y_SIZE + 0;
                    }
        PLANSZA[x_cut][y_cut] = CUT;
    }
}

void cls()
{
   COORD coordScreen = {0,0};
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   DWORD dwConSize;
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   GetConsoleScreenBufferInfo(hConsole, &csbi);
   dwConSize = csbi.dwSize.X*csbi.dwSize.Y;
   FillConsoleOutputCharacter(hConsole,(TCHAR)' ',dwConSize,coordScreen,&cCharsWritten);
   GetConsoleScreenBufferInfo(hConsole,&csbi);
   FillConsoleOutputAttribute(hConsole,csbi.wAttributes,dwConSize,coordScreen,&cCharsWritten);
   SetConsoleCursorPosition(hConsole,coordScreen);
}

void SsSnake::gotoxy(const int x, const int y)
{
        COORD coord = {x, y};
        SetConsoleCursorPosition(g_hConsol, coord);
}
