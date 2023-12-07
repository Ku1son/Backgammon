#include <iostream>
#include <cstdlib>
#include <time.h>
#include "conio2.h"
using namespace std;

#define SZEROKOSC 60
#define WYSOKOSC 15

struct Gracz
{
    int pionki[24];
    int dwor;
    int zbite;
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

    void zapisz(FILE* plik)
    {
        fwrite(pionki, sizeof(int), 24, plik);
        fwrite(&dwor, sizeof(int), 1, plik);
        fwrite(&zbite, sizeof(int), 1, plik);
        fwrite(&kierunekDodatni, sizeof(bool), 1, plik);
    }

    void wczytaj(FILE* plik)
    {
        fread(pionki, sizeof(int), 24, plik);
        fread(&dwor, sizeof(int), 1, plik);
        fread(&zbite, sizeof(int), 1, plik);
        fread(&kierunekDodatni, sizeof(bool), 1, plik);
    }

    void ruchPionka(Gracz* przeciwnik, int polePionka, int miejsceRuchu)
    {
        pionki[polePionka-1] = pionki[polePionka-1] - 1;
        pionki[miejsceRuchu - 1] = pionki[miejsceRuchu - 1] + 1;
        if(przeciwnik->pionki[miejsceRuchu - 1] == 1)
        {
            przeciwnik->pionki[miejsceRuchu - 1] = 0;
            przeciwnik->zbite = przeciwnik->zbite + 1;
        }
    }
};

struct StanGry
{
    int kostki[2];
    int pozostaleRuchy;
    bool turaGracza1;
    bool wykonanoRuch;
    int mozliweRuchy[4];

    void koniecTury()
    {
        turaGracza1 = !turaGracza1;
        kostki[0]=0;
        kostki[1]=0;
        pozostaleRuchy=0;
        for(int i=0; i<4; i++)
        {
            mozliweRuchy[i]=0;
        }
    }

    void poRuchu(int miejsceRuchu, int wybor)
    {
        int delta;
        for(int i=0; i<4; i++)
        {
            if(miejsceRuchu == mozliweRuchy[i])
            {
                mozliweRuchy[i] = 0;
                break;;
            }
        }
        if(kostki[0] != kostki[1])
        {
            if(wybor - miejsceRuchu > 0)
                delta = wybor - miejsceRuchu;
            else
                delta = miejsceRuchu - wybor;
            for(int i=0; i<2; i++)
            {
                if(delta == kostki[i])
                {
                    kostki[i] = 0;
                    break;
                }
            }
        }

        wykonanoRuch = true;
        pozostaleRuchy = pozostaleRuchy - 1;
    }

    void zapisz(FILE* plik)
    {
        fwrite(kostki, sizeof(int), 2, plik);
        fwrite(&pozostaleRuchy, sizeof(int), 1, plik);
        fwrite(&turaGracza1, sizeof(bool), 1, plik);
    }

    void wczytaj(FILE* plik)
    {
        fread(kostki, sizeof(int), 2, plik);
        fread(&pozostaleRuchy, sizeof(int), 1, plik);
        fread(&turaGracza1, sizeof(bool), 1, plik);
    }

    void rzutKostkami()
    {
        kostki[0] = rand() % 6 + 1;
        kostki[1] = rand() % 6 + 1;
        if(kostki[0] == kostki[1])
            pozostaleRuchy = 4;
        else
            pozostaleRuchy = 2;
    }

    bool mozliwyRuch(int poleDocelowe)
    {
        if(poleDocelowe>0 && poleDocelowe<25)
            for(int i=0; i<4; i++)
            {
                if(poleDocelowe == mozliweRuchy[i])
                    return true;
            }
        return false;
    }

    bool daSieRuszyc()
    {
        for(int i=0; i<4; i++)
        {
            if(mozliweRuchy[i] != 0)
                return true;
        }
        return false;
    }
};

void nowaGra(Gracz *gracz1, Gracz *gracz2)
{
    *gracz1 = {{2,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,3,0,5,0,0,0,0,0}, 0, 0, true};
    *gracz2 = {{0,0,0,0,0,5,0,3,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,2}, 0, 0, false};
}

int zapisz(Gracz *gracz1, Gracz *gracz2, StanGry *stanGry)
{
    const char* nazwaPliku = "zapis.bin";
    FILE* plik = fopen(nazwaPliku, "wb");
    if (!plik)
    {
        std::cerr << "Blad podczas zapisywania pliku: " << nazwaPliku << std::endl;
        return -1;
    }
    stanGry->zapisz(plik);
    gracz1->zapisz(plik);
    gracz2->zapisz(plik);
    fclose(plik);
    return 0;
}

bool wczytaj(Gracz *gracz1, Gracz *gracz2, StanGry *stanGry)
{
    const char* nazwaPliku = "zapis.bin";
    FILE* plik = fopen(nazwaPliku, "rb");
    if (!plik)
    {
        std::cerr << "Blad podczas zapisywania pliku: " << nazwaPliku << std::endl;
        return false;
    }
    stanGry->wczytaj(plik);
    gracz1->wczytaj(plik);
    gracz2->wczytaj(plik);
    fclose(plik);
    return true;
}

void rysujObramowanie()
{
    for (int i=0; i<SZEROKOSC; i++)
    {
        for (int j=6; j<=20; j+=7)
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
            gotoxy(j, 6+i);
            cputs(":");
        }
    }
    for (int i=13; i<=24; i++)
    {
        gotoxy((12 + (i-13) * 5), 5);
        cout << i ;
    }
    for (int i = 12; i >= 1; --i)
    {
        gotoxy((12 + (12 - i) * 5), 21);
        cout << i ;
    }
}

void tekstWyboruPionka()
{
    gotoxy(80, 3);
    cout << "W celu zapisania gry";
    gotoxy(80, 4);
    cout << "i wyjscia wybierz 0.";
    gotoxy(80, 5);
    cout << "Wybierz pole (1-24): ";
}

void rysujZbite(Gracz *gracz)
{
    for(int i=0; i<gracz->zbite; i++)
    {
        if(i>0)
            cputs(", ");
        if(gracz->kierunekDodatni)
            cputs("()");
        else
            cputs("{}");
    }
    cputs("       ");
}

void rysujPionki(Gracz *gracz1, Gracz *gracz2)
{
    for(int i=0; i<12; i++)
    {
        //gorna czesc planszy
        if(gracz1->pionki[12+i]>0)
        {
            for(int j=0; j<gracz1->pionki[12+i]; j++)
            {
                gotoxy(12+5*i, 7+j);
                cputs("()");
            }
        }
        if(gracz2->pionki[12+i]>0)
        {
            for(int j=0; j<gracz2->pionki[12+i]; j++)
            {
                gotoxy(12+5*i, 7+j);
                cputs("{}");
            }
        }
        //dolna czesc planszy
        if(gracz1->pionki[11-i]>0)
        {
            for(int j=0; j<gracz1->pionki[11-i]; j++)
            {
                gotoxy(12+5*i, 19-j);
                cputs("()");
            }
        }
        if(gracz2->pionki[11-i]>0)
        {
            for(int j=0; j<gracz2->pionki[11-i]; j++)
            {
                gotoxy(12+5*i, 19-j);
                cputs("{}");
            }
        }
    }
    gotoxy(10, 3);
    cputs("zbite pionki: ");
    rysujZbite(gracz1);
    rysujZbite(gracz2);
}

void wyswietlPlansze(Gracz *gracz1, Gracz *gracz2)
{
    system("cls");
    rysujObramowanie();
    rysujPionki(gracz1, gracz2);
}

bool sprawdzPole(int wybrane, int sprawdzane)
{
    if(wybrane != sprawdzane)
    {
        if(wybrane>12 && wybrane<25 && sprawdzane == 0)
        {
            gotoxy((12 + (wybrane-13) * 5), 4);
            cout << "\\/" ;
        }
        else if(wybrane>12 && wybrane<25 && sprawdzane == 1)
        {
            gotoxy((12 + (wybrane-13) * 5), 3);
            cout << "\\/" ;
            gotoxy((12 + (wybrane-13) * 5), 4);
            cout << "\\/" ;
        }
        else if(wybrane<12 && wybrane>0 && sprawdzane == 0)
        {
            gotoxy((12 + (12-wybrane) * 5), 22);
            cout << "/\\ " ;
        }
        else if(wybrane<13 && wybrane>0 && sprawdzane == 1)
        {
            gotoxy((12 + (12-wybrane) * 5), 22);
            cout << "/\\ " ;
            gotoxy((12 + (12-wybrane) * 5), 23);
            cout << "/\\ " ;
        }
        else
            return false;
    }
    else
        return false;
    return true;
}

void rysujMozliweRuchy(Gracz *czekajacy, int wybor, StanGry *stanGry)
{
    int wybrane;
    bool poprawne = false;
    for(int i=0; i<4; i++)
    {
        if(i<2)
            wybrane = wybor + stanGry->kostki[i];
        else
            wybrane = wybor - stanGry->kostki[i%2];
        if(czekajacy->kierunekDodatni)
        {
            if(wybrane < wybor)
                poprawne = true;
        }
        else
        {
            if(wybrane > wybor)
                poprawne = true;
        }
        if(poprawne)
            if(sprawdzPole(wybrane, czekajacy->pionki[wybrane-1]))
                stanGry->mozliweRuchy[i]=wybrane;
        poprawne=false;
    }
}

void czyscMozliweRuchy()
{
    gotoxy(1,3);
    clreol();
    gotoxy(1,4);
    clreol();
    gotoxy(1,22);
    clreol();
    gotoxy(1,23);
    clreol();
    gotoxy(80,6);
    clreol();
    gotoxy(80,7);
    clreol();
}

void niepoprawne()
{
    gotoxy(80, 6);
    cout << "Wybierz inne, poprawne pole.";
}

bool poprawnyRuch(Gracz *czekajacy, int wybor, StanGry *stanGry)
{
    rysujMozliweRuchy(czekajacy, wybor, stanGry);
    if(!stanGry->daSieRuszyc())
    {
        gotoxy(80, 5);
        clreol();
        gotoxy(80, 6);
        cout << "Wybierz inne, poprawne pole.";
        return false;
    }
    else
        return true;
}

void kolejnosc(bool ruchGracza1)
{
    gotoxy(10, 2);
    cout << "Tura gracza: ";
    if(ruchGracza1)
        cout << "(), w kierunku pola 24";
    else
        cout << "{}, w kierunku pola 1";
}

void wynikRzutu(StanGry *stanGry)
{
    gotoxy(80, 8);
    cout << "Wynik rzutu kostkami: " << stanGry->kostki[0] << "  " << stanGry->kostki[1];
    if(stanGry->kostki[0] == stanGry->kostki[1])
    {
        gotoxy(80, 9);
        cout<< "Dublet! pozostale ruchy: "<<stanGry->pozostaleRuchy;
    }
}

void ruch(Gracz *aktywny, Gracz *czekajacy, int wybor, StanGry *stanGry)
{
    int miejsceRuchu;
    bool pionekRuszony = false;

    if(aktywny->pionki[wybor-1]>0)
    {
        gotoxy(80, 6);
        cout << "Wybierz miejsce ruchu: ";
        while(!pionekRuszony)
        {
            gotoxy(80, 7);
            cin>>miejsceRuchu;
            if(stanGry->mozliwyRuch(miejsceRuchu))
            {
                aktywny->ruchPionka(czekajacy, wybor, miejsceRuchu);
                pionekRuszony = true;
            }
            else
            {
                gotoxy(80, 9);
                cout << "Wybierz inne, poprawne pole";
            }
        }
        stanGry->poRuchu(miejsceRuchu, wybor);
        czyscMozliweRuchy();
    }
    else
        niepoprawne();
    gotoxy(80, 5);
    clreol();
}

int wybierzPole(Gracz *gracz1, Gracz *gracz2, StanGry *stanGry)
{
    stanGry->wykonanoRuch = false;
    while(true)
    {
        int pole;

        wynikRzutu(stanGry);
        tekstWyboruPionka();
        cin >> pole;
        if(pole == 0)
            return pole;
        else
        {
            if(stanGry->turaGracza1)
            {
                if(gracz1->pionki[pole-1]>0)
                {
                    if(poprawnyRuch(gracz2, pole, stanGry))
                        ruch(gracz1, gracz2, pole, stanGry);
                }
                else
                    niepoprawne();
            }
            else
            {
                if(gracz2->pionki[pole-1]>0)
                {
                    if(poprawnyRuch(gracz1, pole, stanGry))
                        ruch(gracz2, gracz1, pole, stanGry);
                }
                else
                    niepoprawne();
            }
        }
        if(stanGry->wykonanoRuch == true)
        {
            stanGry->wykonanoRuch = false;
            return 1;
        }
    }
}

int gra(bool nowa)
{
    bool start = true;
    int wybor;
    Gracz gracz1, gracz2;
    StanGry stanGry = {{0,0},0,true, true, {0,0,0,0}};
    if(nowa)
        nowaGra(&gracz1, &gracz2);
    else if(!wczytaj(&gracz1, &gracz2, &stanGry))
        return -1;
    while (true)
    {
        if((!start || nowa) && stanGry.pozostaleRuchy == 0)
            stanGry.rzutKostkami();
        else
            start = false;

        wyswietlPlansze(&gracz1, &gracz2);
        kolejnosc(stanGry.turaGracza1);

        if(wybierzPole(&gracz1, &gracz2, &stanGry) == 0)
            return zapisz(&gracz1, &gracz2, &stanGry);
        if(stanGry.pozostaleRuchy == 0)
            stanGry.koniecTury();
    }
}

int menu(int *stan, bool error)
{
    char* menu[] = {"Nowa gra", "Wczytaj gre", "Statystyki", "Wyjscie"};
    int n = 4;
    char strzalka;

    while(true)
    {
        clrscr();
        gotoxy(1,1);

        cout<<"Szymon Kula nr. 198068 \n";
        if(error)
            cout<<"Blad podczas otwierania pliku. \n";
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
    bool error = false;
    int stan = 0;
    Conio2_Init();
    srand(time(NULL));
    setvbuf(stdin, NULL, _IOLBF, 0);

    while(aktywna)
    {
        menu(&stan, error);
        error = false;
        if(stan == 0)
        {
            if(gra(true) == -1)
                error = true;
        }
        else if(stan == 1)
        {
            if(gra(false) == -1)
                error = true;
        }
        else if(stan == 2)
        {
            //statystyki
        }
        else
            aktywna = false;
    }

    return 0;
}
