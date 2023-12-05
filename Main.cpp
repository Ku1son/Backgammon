#include <iostream>
#include <cstdlib>
#include <time.h>
#include "conio2.h"
using namespace std;

#define SZEROKOSC 60
#define DLUGOSC 14

int wynikRzutu = 1;

struct Gracz {
    char symbol;
    int bazaX[5]; // Tablica pól, na których znajdują się pionki gracza
    int bazaY[5]; // Tablica wysokości pionków gracza
    int liczbaPionkow; // Liczba pionków gracza
};

Gracz graczO = {'O', {12, 12, 12, 12, 12}, {6, 7, 8, 9, 10}, 5};
Gracz graczX = {'X', {12, 12, 12, 12, 12}, {13, 12, 11, 10, 9}, 5};

void wyswietlPlansze() {
    system("cls");

     for (int i=0; i<SZEROKOSC; i++)
    {
        gotoxy(10+i, 5);
        cputs("=");
    }
    for (int i=0; i<SZEROKOSC; i++)
    {
        gotoxy(10+i, 18);
        cputs("=");
    }
    for (int i=0; i<DLUGOSC; i++)
    {
        gotoxy(10, 5+i);
        cputs(":");
    }
    for (int i=0; i<DLUGOSC; i++)
    {
        gotoxy(70, 5+i);
        cputs(":");
    }
    for (int i=0; i<DLUGOSC; i++)
    {
        gotoxy(40, 5+i);
        cputs(":");
    }
    for (int i=13; i<=24; i++)
    {
        gotoxy((12+(i-13) * 5), 4);
        cout << i ;
    }
    for (int i = 12; i >= 1; --i)
    {
        gotoxy((12 + (12 - i) * 5), 19);
        cout << i ;
    }
    for (int i=0; i<5; i++)
    {
        gotoxy (12, 6+i);
        cputs("O");
    }
    for (int i=0; i<3; i++)
    {
        gotoxy (32, 15+i);
        cputs("O");
    }
    for (int i=0; i<5; i++)
    {
        gotoxy (42, 13+i);
        cputs("O");
    }
    for (int i=0; i<2; i++)
    {
        gotoxy (67, 6+i);
        cputs("O");
    }
    for (int i=0; i<5; i++)
    {
        gotoxy (12, 13+i);
        cputs("X");
    }
    for (int i=0; i<3; i++)
    {
        gotoxy (32, 6+i);
        cputs("X");
    }
    for (int i=0; i<5; i++)
    {
        gotoxy (42, 6+i);
        cputs("X");
    }
    for (int i=0; i<2; i++)
    {
        gotoxy (67, 16+i);
        cputs("X");
    }


    // Przykładowe użycie gotoxy:
    gotoxy(graczO.bazaX[0], graczO.bazaY[0]);
    cout << graczO.symbol;

    gotoxy(graczX.bazaX[0], graczX.bazaY[0]);
    cout << graczX.symbol;
}

int rzutKostkami() {
    srand(time(NULL));
    int losowyNumer = rand() % 6 + 1;
    return losowyNumer;
}

bool czyPoleJestWolne(int x, int y) {
    // Sprawdza, czy pole na planszy jest wolne
    // Możesz dodać odpowiednie warunki w zależności od logiki gry
    return true;
}

void ruchPionkiem(Gracz &gracz, int liczbaPol) {
    for (int i = 0; i < gracz.liczbaPionkow; i++) {
        int nowePoleX = gracz.bazaX[i] + liczbaPol;
        int nowePoleY = gracz.bazaY[i];

        // Sprawdza, czy na nowym polu nie ma kolizji z innym pionkiem
        if (czyPoleJestWolne(nowePoleX, nowePoleY)) {
            // Usuń pionek z aktualnej pozycji
            gotoxy(gracz.bazaX[i], gracz.bazaY[i]);
            cout << " ";

            // Przesuń pionek o określoną liczbę pól
            gracz.bazaX[i] = nowePoleX;
            gracz.bazaY[i] = nowePoleY;

            // Narysuj pionek na nowej pozycji
            gotoxy(gracz.bazaX[i], gracz.bazaY[i]);
            cout << gracz.symbol;
        }
    }
}

int wybierzPole() {
    int pole;
    gotoxy(80, 2);
    cout << "Wybierz pole (1-24): ";
    cin >> pole;
    return pole;
}



bool czyKoniecGry() {
    // Implementuj logikę sprawdzającą warunki końca gry
    // Na przykład, gdy jeden z graczy osiągnie określoną pozycję na planszy
    return (graczO.bazaX[0] >= 24 || graczX.bazaX[0] <= 1);
}

int main() {
    // Inicjalizacja biblioteki conio2
    Conio2_Init();
    setvbuf(stdin, NULL, _IOLBF, 0);

    // Rysowanie planszy do backgammona
    wyswietlPlansze();

    while (!czyKoniecGry()) {
        // Rzut kostką i wyświetlenie wyniku
        int liczbaPolO = rzutKostkami();
        gotoxy(80, 1);
        cout << "Wynik rzutu kostkami: " << liczbaPolO;

        // Wybór pola i ruch pionkiem dla gracza O
        int poleWyboruO = wybierzPole();
        ruchPionkiem(graczO, liczbaPolO);

        // Aktualizacja planszy po ruchu gracza O
        wyswietlPlansze();

        // Rzut kostką i wyświetlenie wyniku
        int liczbaPolX = rzutKostkami();
        gotoxy(80, 1);
        cout << "Wynik rzutu kostkami: " << liczbaPolX;

        // Wybór pola i ruch pionkiem dla gracza X
        int poleWyboruX = wybierzPole();
        ruchPionkiem(graczX, liczbaPolX);

        // Aktualizacja planszy po ruchu gracza X
        wyswietlPlansze();
    }

    // Oczekiwanie na naciśnięcie klawisza przed zakończeniem programu
    getch();

    return 0;
}
