#include <iostream>
#include <cstdlib>
#include <time.h>
#include "conio2.h"
using namespace std;

#define SZEROKOSC 60
#define WYSOKOSC 15

struct Gracz
{
    //Polozenie i ilosc pionkow gracza
    int pionki[24];
    //ilosc pionkow na dworze
    int dwor;
    //ilosc zbitych pionkow
    int zbite;
    //kierunek ruchow pionkow gracza
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
        if(polePionka == 0 || polePionka == 25)
            zbite = zbite - 1;
        else
            pionki[polePionka-1] = pionki[polePionka-1] - 1;
        pionki[miejsceRuchu - 1] = pionki[miejsceRuchu - 1] + 1;
        if(przeciwnik->pionki[miejsceRuchu - 1] == 1)
        {
            przeciwnik->pionki[miejsceRuchu - 1] = 0;
            przeciwnik->zbite = przeciwnik->zbite + 1;
        }
    }
};

//Funkcja do narysowania strzalki mozliwego zbicia pionka skierowanej w dol
void strzalkaDol(int wybrane, int y)
{
    gotoxy((12 + (wybrane-13) * 5), y);
    cputs("\\/");
}

//Funkcja do narysowania strzalki mozliwego zbicia pionka skierowanej w gore
void strzalkaGora(int wybrane, int y)
{
    gotoxy((12 + (12-wybrane) * 5), y);
    cputs("/\\ ");
}

struct StanGry
{
    //wyniki rzutow kostkami
    int kostki[2];
    //ilosc pozostalych ruchow gracza
    int pozostaleRuchy;
    //ruchy mozlwie do wykonania po wybraniu piona
    int mozliweRuchy[4];
    //bicia mozlwie do wykonania po wybraniu piona
    int mozliweBicia[4];
    //inforamcja czy
    bool turaGracza1;
    bool wykonanoRuch;
    bool bicie;
    bool pas;

    StanGry()
    {
        kostki[0] = 0;
        kostki[1] = 0;
        pozostaleRuchy = 0;
        for(int i=0; i<4; i++)
        {
            mozliweBicia[i] = 0;
            mozliweRuchy[i] =0;
        }
        turaGracza1 = true;
        wykonanoRuch = false;
        bicie = false;
        pas = false;

    }

    //Funkcja porzadkujaca zmienne po zakonczeniu wszystkich ruchow gracza
    void koniecTury()
    {
        turaGracza1 = !turaGracza1;
        kostki[0]=0;
        kostki[1]=0;
        pozostaleRuchy=0;
        bicie = false;
        for(int i=0; i<4; i++)
        {
            mozliweRuchy[i]=0;
            mozliweBicia[i]=0;
        }
    }

    //Funkcja po zakonczeniu ruchu
    //miejsce ruchu - pole do ktorego pion sie rusza
    //wybor - pole z ktorego pion sie rusza
    void poRuchu(int miejsceRuchu, int wybor)
    {
        int delta;
        for(int i=0; i<4; i++)
        {
            mozliweRuchy[i] = 0;
            mozliweBicia[i] = 0;
        }
        //wykrywanie ktora kostka zostala zuzyta
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
        bicie = false;
        wykonanoRuch = true;
        pozostaleRuchy = pozostaleRuchy - 1;
    }

    //Funkcja zapisywania do pliku
    void zapisz(FILE* plik)
    {
        fwrite(kostki, sizeof(int), 2, plik);
        fwrite(&pozostaleRuchy, sizeof(int), 1, plik);
        fwrite(&turaGracza1, sizeof(bool), 1, plik);
    }

    //Funkcja wczytywania stanu gry z pliku
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

    //Sprawdzanie w zaleznosci od zmiennej bicie, czy wybrane przez gracza pole docelowe jest poprwanym celem ruchu
    bool mozliwyRuch(int poleDocelowe)
    {
        if(poleDocelowe>0 && poleDocelowe<25)
            for(int i=0; i<4; i++)
            {
                if(bicie)
                {
                    if(poleDocelowe == mozliweBicia[i])
                        return true;
                }
                else
                {
                    if(poleDocelowe == mozliweRuchy[i])
                        return true;
                }
            }
        return false;
    }

    //Funkcja rysujaca strzalki wskazujace na mozliwe ruchy, na podstawie znalezionych ruchow
    void rysujRuchy()
    {
        if(bicie)
            for(int i=0; i<4; i++)
            {
                if(mozliweBicia[i]>0 && mozliweBicia[i]<13)
                {
                    strzalkaGora(mozliweBicia[i], 22);
                    strzalkaGora(mozliweBicia[i], 23);
                }
                else if(mozliweBicia[i]>12 && mozliweBicia[i]<25)
                {
                    strzalkaDol(mozliweBicia[i], 3);
                    strzalkaDol(mozliweBicia[i], 4);
                }
            }
        else
            for(int i=0; i<4; i++)
            {
                if(mozliweRuchy[i]>0 && mozliweRuchy[i]<13)
                    strzalkaGora(mozliweRuchy[i], 22);
                else if(mozliweRuchy[i]>12 && mozliweRuchy[i]<25)
                    strzalkaDol(mozliweRuchy[i], 4);
            }
    }

    //Sprawdzanie czy dany pionek ma dostepne poprawne ruchy
    bool daSieRuszyc()
    {
        for(int i=0; i<4; i++)
        {
            if(bicie)
            {
                if(mozliweBicia[i] != 0)
                    return true;
            }
            else if(mozliweRuchy[i] != 0)
                return true;
        }
        return false;
    }
};

//Inicjalizacja nowej gry
void nowaGra(Gracz *gracz1, Gracz *gracz2)
{
    *gracz1 = {{2,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,3,0,5,0,0,0,0,0}, 0, 0, true};
    *gracz2 = {{0,0,0,0,0,5,0,3,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,2}, 0, 0, false};
}

//Funkcja zapisujaca stan gry do pliku
//gracz1 - obecnie ruszajacy sie gracz
//gracz2 - obecnie nie ruszajacy sie gracz
//stanGry - struktura z informacjami o stanie gry
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

//Funkcja wczytujaca stan gry z pliku
//gracz1 - obecnie ruszajacy sie gracz
//gracz2 - obecnie nie ruszajacy sie gracz
//stanGry - struktura z informacjami o stanie gry
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

//Funkcja rysujaca obramowanie planszy w konsoli
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
        cout<<i;
    }
    for (int i = 12; i >= 1; --i)
    {
        gotoxy((12 + (12 - i) * 5), 21);
        cout<<i;
    }
}

//Funkcja wypisujaca opcje dostepne po wyborze piona do ruchu
void tekstWyboruPionka()
{
    gotoxy(80, 2);
    cputs("W celu zapisania gry");
    gotoxy(80, 3);
    cputs("i wyjscia wybierz 0.");
    gotoxy(80, 4);
    cputs("Jezli masz zbite pionki wybierz 25.");
    gotoxy(80, 5);
    cputs("Wybierz pole (1-24): ");
}

//Funkcja wypisujaca zbite pionki nad plansza
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

//Funkcja wyrysowujaca piony bydwoch graczy na odpowiednich polach
//gracz1 - obecnie ruszajacy sie gracz
//gracz2 - obecnie nie ruszajacy sie gracz
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

//Funkcja rysujaca plansze na podstawie pionow dwoch graczy
//gracz1 - obecnie ruszajacy sie gracz
//gracz2 - obecnie nie ruszajacy sie gracz
void wyswietlPlansze(Gracz *gracz1, Gracz *gracz2)
{
    system("cls");
    rysujObramowanie();
    rysujPionki(gracz1, gracz2);
}

//Sprawdzanie czy pole docelowe jest poprwanym ruchem lub biciem
//wybrane - docelowe pole ruchu piona
//poleStart - pole poczatkowe piona
//sprawdzone - ile pionow przeciwnik ma na polu docelowym
//stanGry - struktura z informacjami o stanie gry
//i - iteracja petli funkcji wywolujacej
//powrot - informacja czy ruch dotyczy piona wracajacego na plansze
//return informacja czy wybrane pole jest poprawnym ruchem
//false w wypadku zbicia lub niepoprawnego ruchu
bool sprawdzPole(int wybrane, int poleStart, int sprawdzane, StanGry *stanGry, int i, bool powrot)
{
    bool zbicie = false;
    if(wybrane != poleStart)
    {
        if(powrot)
        {
            if((poleStart == 0 && wybrane < 7) || (poleStart == 25 && wybrane > 18))
            {
                if(sprawdzane == 1)
                    stanGry->bicie = zbicie = true;
                else if(sprawdzane > 1)
                    return false;
            }
        }
        else
        {
            if(wybrane>0 && wybrane<25 && sprawdzane == 1)
                stanGry->bicie = zbicie = true;
            else if((wybrane>12 && wybrane<25 && sprawdzane == 0) || (wybrane<12 && wybrane>0 && sprawdzane == 0))
            { }
            else
                return false;
        }
    }
    else
        return false;
    if(zbicie)
    {
        stanGry->mozliweBicia[i]=wybrane;
        return false;
    }
    return true;
}

//Funkcja sprawdzajaca i rysujaca mozliwe ruchy
//czekajacy - wskaznik na gracza ktory obecnie nie ma swojej tury
//poleStart - pole z ktorego pion sie ma poruszyc
//stanGry - struktura z informacjami o stanie gry
//powrot - informacja czy ruch dotyczy piona wracajacego na plansze
void rysujMozliweRuchy(Gracz *czekajacy, int poleStart, StanGry *stanGry, bool powrot)
{
    //wybrane - sprawdzane pole docelowe ruchu piona
    int wybrane;
    bool poprawne = false;

    //Petla sprawdzajaca czy wybrany pion moze sie poruszyc
    for(int i=0; i<4; i++)
    {
        //Ustalenie wartosci zmiennej wybrane
        if(i<2)
            wybrane = poleStart + stanGry->kostki[i];
        else
            wybrane = poleStart - stanGry->kostki[i%2];

        //Sprawdzenie czy wybrane pole docelowe ruchu jest zgodne z kierunkiem ruchu pionow gracza
        if(czekajacy->kierunekDodatni)
        {
            if(wybrane < poleStart)
                poprawne = true;
        }
        else
        {
            if(wybrane > poleStart)
                poprawne = true;
        }

        if(poprawne)
            //Sprawdzanie czy znaleziony ruch jest poprawnym ruchem, jesli jest biciem to kolejny if zwraca false, a pole bicia zpisane jest wewnatrz funkcji sprawdzPole()
            if(sprawdzPole(wybrane, poleStart, czekajacy->pionki[wybrane-1], stanGry, i, powrot))
                //jesli pole jest poprawnym ruchem, zapisujemy go do tablicy
                stanGry->mozliweRuchy[i]=wybrane;

        poprawne=false;
    }
    stanGry->rysujRuchy();
}

//Wyczyszczenie zbednych linii tekstu na konsoli
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

//Informacja wyswietlana przy wyborze zlego pola
void niepoprawne()
{
    gotoxy(80, 6);
    cputs("Wybierz inne, poprawne pole.");
}

//Informacja wyswietlana po przymusowym pasie
void utrataRuchu()
{
    gotoxy(80, 6);
    cputs("Nie ma poprawnego ruchu, pas, wcisnij enter.");
}

//Funckja sprawdzajaca czy wskazany ruch jest poprawny
//czekajacy - obecnie nie ruszajacy sie gracz
//wybor - wartosc pola z ktorego gracz aktywny chce poruszyc piona
//stanGry - struktura z informacjami o stanie gry
//powrot - informacja czy ruch dotyczy piona wracajacego na plansze
bool poprawnyRuch(Gracz *czekajacy, int wybor, StanGry *stanGry, bool powrot)
{
    rysujMozliweRuchy(czekajacy, wybor, stanGry, powrot);
    if(!stanGry->daSieRuszyc())
    {
        gotoxy(80, 5);
        clreol();
        niepoprawne();
        return false;
    }
    else
        return true;
}

//Funkcja wypisujaca informacje ktory gracz sie rusza i w jakim kierunku
//ruchGracza1 - zmienna informujaca czy rusza sie gracz 1
void kolejnosc(bool ruchGracza1)
{
    gotoxy(10, 2);
    cputs("Tura gracza: ");
    if(ruchGracza1)
        cputs("(), w kierunku pola 24");
    else
        cputs("{}, w kierunku pola 1");
}

//Funkcja wypisujaca informacje o obecnym rzucie koscmi
//stanGry - struktura z informacjami o stanie gry
void wynikRzutu(StanGry *stanGry)
{
    gotoxy(80, 8);
    cout << "Wynik rzutu kostkami: " << stanGry->kostki[0] << "  " << stanGry->kostki[1];
    if(stanGry->kostki[0] == stanGry->kostki[1])
    {
        gotoxy(80, 9);
        cout << "Dublet! pozostale ruchy: "<<stanGry->pozostaleRuchy;
    }
    tekstWyboruPionka();
}

//aktywny - obecnie ruszajacy sie gracz
//czekajacy - obecnie nie ruszajacy sie gracz
//wybor - wartosc pola z ktorego gracz aktywny chce poruszyc piona
//stanGry - struktura z informacjami o stanie gry
//powrot - informacja czy ruch dotyczy piona wracajacego na plansze
int petlaRuchu(Gracz *aktywny, Gracz *czekajacy, int wybor, StanGry *stanGry, bool powrot)
{
    bool pionekRuszony = false;
    int miejsceRuchu;
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
            cputs("Wybierz inne, poprawne pole");
        }
    }
    return miejsceRuchu;
}

//Funkcja odpowiadajaca za ruch piona z wybranego pola
//aktywny - obecnie ruszajacy sie gracz
//czekajacy - obecnie nie ruszajacy sie gracz
//wybor - wartosc pola z ktorego gracz aktywny chce poruszyc piona
//stanGry - struktura z informacjami o stanie gry
//powrot - informacja czy ruch dotyczy piona wracajacego na plansze
void ruch(Gracz *aktywny, Gracz *czekajacy, int wybor, StanGry *stanGry, bool powrot)
{
    if((!powrot && aktywny->pionki[wybor-1]>0) || powrot && aktywny->zbite > 0)
    {
        gotoxy(80, 6);
        cputs("Wybierz miejsce ruchu: ");
        int miejsceRuchu = petlaRuchu(aktywny, czekajacy, wybor, stanGry, powrot);
        stanGry->poRuchu(miejsceRuchu, wybor);
        czyscMozliweRuchy();
    }
    else
        niepoprawne();
    gotoxy(80, 5);
    clreol();
}

//Ruch kiedy co najmniej jeden pion gracza jest zbity
//gracz1 - obecnie ruszajacy sie gracz
//gracz2 - obecnie nie ruszajacy sie gracz
//stanGry - struktura z informacjami o stanie gry
//pole - wartosc pola z ktorego gracz aktywny chce poruszyc piona
void powrotPiona(Gracz *gracz1, Gracz *gracz2, StanGry *stanGry, int pole)
{
    if(stanGry->turaGracza1)
    {
        if(gracz1->zbite > 0)
        {
            if(poprawnyRuch(gracz2, 0, stanGry, true))
                ruch(gracz1, gracz2, 0, stanGry, true);
            else
            {
                stanGry->wykonanoRuch = true;
                stanGry->pas = true;
            }
        }
        else
            niepoprawne();
    }
    else
    {
        if(gracz2->zbite > 0)
        {
            if(poprawnyRuch(gracz1, 25, stanGry, true))
                ruch(gracz2, gracz1, 25, stanGry, true);
            else
            {
                stanGry->wykonanoRuch = true;
                stanGry->pas = true;
            }
        }
        else
            niepoprawne();
    }
}

//Ruch kiedy wszystkie piony sa na planszy
//gracz1 - obecnie ruszajacy sie gracz
//gracz2 - obecnie nie ruszajacy sie gracz
//stanGry - struktura z informacjami o stanie gry
//pole - wartosc pola z ktorego gracz aktywny chce poruszyc piona
void normalnyRuch(Gracz *gracz1, Gracz *gracz2, StanGry *stanGry, int pole)
{
    if(stanGry->turaGracza1)
    {
        if(gracz1->pionki[pole-1]>0 && gracz1->zbite == 0)
        {
            if(poprawnyRuch(gracz2, pole, stanGry, false))
                ruch(gracz1, gracz2, pole, stanGry, false);
        }
        else
            niepoprawne();
    }
    else
    {
        if(gracz2->pionki[pole-1]>0 && gracz2->zbite == 0)
        {
            if(poprawnyRuch(gracz1, pole, stanGry, false))
                ruch(gracz2, gracz1, pole, stanGry, false);
        }
        else
            niepoprawne();
    }
}

//Glowna funkcja odpowiadajaca za wybor pola z ktorego bedziemy ruszac piona i wywolujaca kolejne funkcje
//gracz1 - obecnie ruszajacy sie gracz
//gracz2 - obecnie nie ruszajacy sie gracz
//stanGry - struktura z informacjami o stanie gry
int wybierzPole(Gracz *gracz1, Gracz *gracz2, StanGry *stanGry)
{
    stanGry->wykonanoRuch = false;
    while(true)
    {
        int pole;
        wynikRzutu(stanGry);
        cin >> pole;
        if(pole == 0)
            return pole;
        else if(pole == 25)
            powrotPiona(gracz1, gracz2, stanGry, pole);
        else
            normalnyRuch(gracz1, gracz2, stanGry, pole);
        if(stanGry->wykonanoRuch == true)
        {
            stanGry->wykonanoRuch = false;
            return 1;
        }
    }
}

//Funkcja z glowna petla gry, wywolujaca inicjalizacje obiektow graczy i
//nowa - zmienna informujaca czy jest ot nowa gra czy wczytywanie
int gra(bool nowa)
{
    bool start = true;
    int wybor;
    Gracz gracz1, gracz2;
    StanGry stanGry = StanGry();
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
        if(stanGry.pozostaleRuchy == 0 || stanGry.pas)
        {
            stanGry.koniecTury();
            if(stanGry.pas)
            {
                char a;
                stanGry.pas = false;
                utrataRuchu();
                cin>>a;
            }
        }
    }
}

//Funkcja z menu glownym
//stan - zmienna odpowiadajaca za stan wybrany z menu glownego
//error - zmienna informujaca o bledzie odczytu pliku
void menu(int *stan, bool error)
{
    char* menu[] = {"Nowa gra", "Wczytaj gre", "Statystyki", "Wyjscie"};
    int n = 4;
    char strzalka;

    while(true)
    {
        clrscr();
        gotoxy(1,1);

        cputs("Szymon Kula nr. 198068 \n");
        if(error)
            cputs("Blad podczas otwierania pliku. \n");
        for(int i=0; i<n; i++)
        {
            if(i == *stan)
            {
                cputs(" ----> ");
            }
            else
            {
                cputs("       ");
            }
            cout << i + 1 << "  ";
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
            return;
    }
}

//Glowna funkcja programu
int main()
{
    bool aktywna = true, error = false;
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
