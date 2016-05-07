#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

struct Point
{
  int a, b;
};

class SsSnake
{
private:
    enum {X_SIZE = 20, Y_SIZE = 70};
    enum WEZU {Puste_Pole = ' ', Snake = 219, Nagroda = '@', Body = 178, Spid = 'S', CUT = 'C'};
    int Size_Snake;
    unsigned int Punkty;
    int x_head; // glowa sneak-a
    int y_head;
    int x_ogon; // oczko ogonu tuz za glowa
    int y_ogon;
    int x_award; // nagroda papu
    int y_award;
    int x_spid; // nagroda - wiecej speeda
    int y_spid;
    int x_cut; // nagroda - skraca weza
    int y_cut;
    int level;
    char Move;
    double czas; //czas do nastepnego bonusu!
    int Spid_Bonus;//ile jeszcze?
    string Nick;
    WEZU PLANSZA[X_SIZE +1 ][Y_SIZE + 1];
    Point Ogon[X_SIZE*Y_SIZE+1];
    void cut_snake(); // obetnij nie potrzebne elementy ogona - resetuje tablice i ustawia ostacznie oczko na puste pole
    int Wskaznik_Tab;
    void Set_ogon(int c, int d); // ustaw ogon za glowa
    unsigned int Speed(); // szybkosc ruchu - ogolnego
    void Scores();
    void Losuj_bonus();
    void Bonus_SPEEDa(); // speed
    void Set_Award(); //papu - jedzonko
    void Skroc(); //skraca weza
    void gotoxy(const int x, const int y);
public:
    SsSnake(string str); //konstruktor
    ~SsSnake() { Reset_Map(); } // destruktor
    void Reset_Map();
    void Show_Map();
    void Set_Snake();
    void Set_ogon();
    bool PLAY();
    void ruch();
};

void cls();
#endif // SNAKE_H_INCLUDED
