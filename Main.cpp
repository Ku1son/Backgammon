#include <iostream>
#include <cstdlib>
#include <time.h>
#include "conio2.h"
using namespace std;

#define SZEROKOSC 60
#define WYSOKOSC 15

struct Gracz
{
    int pionki[24]; // Tablica pól, na których znajduj¹ siê pionki gracza
    int dwor; // Tablica wysokoœci pionków gracza
    int zbite; // Liczba pionków gracza
    bool kierunekDodatni;
    bool czyZbite()
    {
        if(zbite>0)
            return true;
        return false;
    }
    bool kompletDom()
    {
        if(zbite>0)
            return false;
        for(int i=0; i<18; i++)
        {
            if(pionki[i]!=0)
                return false;
        }
        return true;
    }
};

void nowaGra(Gracz *gracz1, Gracz *gracz2)
{
    *gracz1 = {{2,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,3,0,5,0,0,0,0,0}, 0, 0, true};
    *gracz2 = {{0,0,0,0,0,5,0,3,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,2}, 0, 0, false};
}

int rzutKostkami()
{
    srand(time(NULL));
    int losowyNumer = rand() % 6 + 1;
    return losowyNumer;
}

void rysujObramowanie()
{
    for (int i=0; i<SZEROKOSC; i++)
    {
        for (int j=5; j<=19; j+=7)
        {
            gotoxy(10+i, j);
            if(j==12)
                cputs("-");
            else
                cputs("=");
        }
    }
    for (int i=0; i<WYSOKOSC; i++)
    {
        for (int j=10; j<=70; j+=30)
        {
            gotoxy(j, 5+i);
            cputs(":");
        }
    }
    for (int i=13; i<=24; i++)
    {
        gotoxy((12 + (i-13) * 5), 4);
        cout << i ;
    }
    for (int i = 12; i >= 1; --i)
    {
        gotoxy((12 + (12 - i) * 5), 20);
        cout << i ;
    }
}

void rysujPionki(Gracz *gracz1, Gracz *gracz2)
{
    for(int i=0; i<12; i++)
    {
        //górna czêœæ planszy
        if(gracz1->pionki[12+i]>0)
        {
            for(int j=0; j<gracz1->pionki[12+i]; j++)
            {
                gotoxy(12+5*i, 6+j);
                cputs("()");
            }
        }
        if(gracz2->pionki[12+i]>0)
        {
            for(int j=0; j<gracz2->pionki[12+i]; j++)
            {
                gotoxy(12+5*i, 6+j);
                cputs("{}");
            }
        }
        //dolna czêœæ planszy
        if(gracz1->pionki[11-i]>0)
        {
            for(int j=0; j<gracz1->pionki[11-i]; j++)
            {
                gotoxy(12+5*i, 18-j);
                cputs("()");
            }
        }
        if(gracz2->pionki[11-i]>0)
        {
            for(int j=0; j<gracz2->pionki[11-i]; j++)
            {
                gotoxy(12+5*i, 18-j);
                cputs("{}");
            }
        }
    }
}

void wyswietlPlansze(Gracz *gracz1, Gracz *gracz2)
{
    system("cls");
    rysujObramowanie();
    rysujPionki(gracz1, gracz2);
}

int wybierzPole()
{
    int pole;
    gotoxy(80, 2);
    cout << "W celu zapisania gry";
    gotoxy(80, 3);
    cout << "i wyjscia wybierz 0.";
    gotoxy(80, 4);
    cout << "Wybierz pole (1-24): ";
    cin >> pole;
    return pole;
}

int gra(bool nowa)
{
    Gracz gracz1, gracz2;
    bool ruchGracza1 = true;
    if(nowa)
    {
        nowaGra(&gracz1, &gracz2);
    }
    while (true)
    {
        wyswietlPlansze(&gracz1, &gracz2);

        gotoxy(10, 2);
        cout << "Tura gracza: ";
        if(ruchGracza1)
        {
            cout << "(), w kierunku pola 24";
        }
        else
        {
            cout << "{}, w kierunku pola 1";
        }
        // Rzut kostk¹ i wyœwietlenie wyniku
        int kostka1 = rzutKostkami();
        int kostka2 = rzutKostkami();
        gotoxy(80, 6);
        cout << "Wynik rzutu kostkami: " << kostka1 << "  " << kostka2;

        // Wybór pola i ruch pionkiem dla gracza O
        int wybor = wybierzPole();
        if(wybor == 0)
        {
            //TODO zapis
        }
        else
        {
            //TODO gra
        }
    }
}

int menu(int *stan)
{
    char* menu[] = {"Nowa gra", "Wczytaj gre", "Statystyki", "Wyjscie"};
    int n = 4;
    char strzalka;

    while(true)
    {
        clrscr();
        gotoxy(1,1);

        cout<<"Szymon Kula nr. \n \n";
        for(int i=0; i<n; i++)
        {
            if(i == *stan)
            {
                cout<<" ----> ";
            }
            else
            {
                cout<<"       ";
            }
            cout<<i + 1<<"  ";
            puts(menu[i]);
        }
        strzalka=getch();
        if(strzalka == 0)
        {
            strzalka=getch();
            if(strzalka == 80)
            {
                *stan += 1;
                if(*stan == n)
                {
                    *stan = 0;
                }
            }
            else if(strzalka == 72)
            {
                *stan -= 1;
                if(*stan == -1)
                {
                    *stan = n-1;
                }
            }
        }
        else if(strzalka == 13)
            return *stan;
    }
}

int main()
{
    bool aktywna = true;
    int stan = 0;
    Conio2_Init();
    setvbuf(stdin, NULL, _IOLBF, 0);

    while(aktywna)
    {
        menu(&stan);
        if(stan == 0)
            gra(true);
        else if(stan == 1)
        { //TODO wczytywanie }
        else if(stan == 2)
        { //TODO statystyki }
        else
            aktywna = false;
    }

    return 0;
}
