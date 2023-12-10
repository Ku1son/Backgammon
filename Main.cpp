#include <iostream>
#include <cstdlib>
#include <time.h>
#include "conio2.h"
using namespace std;

#define SZEROKOSC 60
#define WYSOKOSC 15

struct Gracz
{
    int pionki[24];         // 24 pola a wartosc to ilosc pionkow na danym polu
    int dwor;               // ilosc pionkow na dworze
    int zbitePionki;              // ilosc zbitych pionkow
    bool kierunekDodatni;   // kierunek ruchow pionkow gracza


    bool czyZbite()
    {
        if(zbitePionki>0)
            return true;
        return false;
    }

    bool kompletDom()
    {
        if(zbitePionki>0)
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
        fwrite(&zbitePionki, sizeof(int), 1, plik);
        fwrite(&kierunekDodatni, sizeof(bool), 1, plik);
    }

    void wczytaj(FILE* plik)
    {
        fread(pionki, sizeof(int), 24, plik);
        fread(&dwor, sizeof(int), 1, plik);
        fread(&zbitePionki, sizeof(int), 1, plik);
        fread(&kierunekDodatni, sizeof(bool), 1, plik);
    }

    void ruchPionka(Gracz* przeciwnik, int miejsceStartu, int miejsceDocelowe)
    {
        if (miejsceStartu == 0 || miejsceStartu == 25)    // DALCZEGO DLA 0 ZMNIEJSZAMY ILOSC ZBITYCH PIONOW???
        {
            zbitePionki = zbitePionki - 1;  // zmniejszenie ilosc zbitych pionow
        }   
        else
        {
            pionki[miejsceStartu-1] = pionki[miejsceStartu-1] - 1;                 // zmniejszenie wartosci tablicy o 1 (wartosc tablicy to ilosc pionkow na danym polu)
            pionki[miejsceDocelowe - 1] = pionki[miejsceDocelowe - 1] + 1;   // zwiekszenie wartosc tablicy o 1 (tam gdzie pionek ma sie przemiescic)         
        }
        if(przeciwnik->pionki[miejsceDocelowe - 1] == 1)        // jesli jest jeden pion przeciwnika na docelowym miejscu (UTWORZENIE WARUNKU NA BICIE)
        {
            przeciwnik->pionki[miejsceDocelowe - 1] = 0;         // zdjecie zbitego pionka
            przeciwnik->zbitePionki = przeciwnik->zbitePionki + 1;          // zliczanie zbitych pionkow zostaje zwiekszone o 1
        }
    }
};

void strzalkaNaGorze(int miejsceDocelowe, int y)
{
    gotoxy((12 + (miejsceDocelowe-13) * 5), y);
    cputs("\\\/");
}

void strzalkaNaDole(int miejsceDocelowe, int y)
{
    gotoxy((12 + (12-miejsceDocelowe) * 5), y);
    cputs("^");
}

struct StanGry
{
    int kostki[2];
    int pozostaleRuchy;
    int mozliweRuchy[4];        // ruchy mozlwie do wykonania po wybraniu piona     (przyjmuja zakres od 0 do 24 gdzie 0 to brak ruchu)
    int mozliweBicia[4];        // bicia mozlwie do wykonania po wybraniu piona     (przyjmuja zakres od 0 do 24 gdzie 0 to brak bicia)
    bool turaGracza1;
    bool wykonanoRuch;
    bool bicie;
    bool pas;

    StanGry()                   // ????????????????????????? CZYM SIE ROZNI OD koniecTury       I CO TO W OGOLE JEST XD
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

    void koniecTury()               // po zakoneczeniu tury (wszystkich ruchow)
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

    
    void poRuchu(int miejsceDocelowe, int miejsceStartu)        // po zakonczeniu jednego ruchu
    {
        int roznica;
        for(int i=0; i<4; i++)
        {
            mozliweRuchy[i] = 0;
            mozliweBicia[i] = 0;
        }
        if(kostki[0] != kostki[1])      // sprawdzenie ktora kostka zostala uzyta
        {
            if(miejsceStartu - miejsceDocelowe > 0)
                roznica = miejsceStartu - miejsceDocelowe;
            else
                roznica = miejsceDocelowe - miejsceStartu;
            for(int i=0; i<2; i++)
            {
                if(roznica == kostki[i])
                {
                    kostki[i] = 0;      // zerowanie zuzytej kostki
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

    bool mozliwyRuch(int poleDocelowe)          // sprawdzanie w zaleznosci od zmiennej bicie, czy wybrane przez gracza pole docelowe jest poprwanym celem ruchu
    {
        if(poleDocelowe>0 && poleDocelowe<25)       // czy miescimy sie w zakresie
            for(int i=0; i<4; i++)
            {
                if(bicie)        
                {
                    if(poleDocelowe == mozliweBicia[i])     // zwraca true jesli istnieje wykonanie ruchu jako bicie
                        return true;
                }
                else
                {
                    if(poleDocelowe == mozliweRuchy[i])     // zwraca true jesli istnieje wykonanie ruchu jako normalny ruch
                        return true;
                }
            }
        return false;
    }

    void rysujStrzalki()            // funkcja rysujaca strzalki wskazujace na mozliwe ruchy, na podstawie znalezionych ruchow
    {
        if(bicie)                                               // strzalki dla bicia
            for(int i=0; i<4; i++)
            {
                if(mozliweBicia[i]>0 && mozliweBicia[i]<13)
                {
                    strzalkaNaDole(mozliweBicia[i], 22);
                    strzalkaNaDole(mozliweBicia[i], 23);
                }
                else if(mozliweBicia[i]>12 && mozliweBicia[i]<25)
                {
                    strzalkaNaGorze(mozliweBicia[i], 3);
                    strzalkaNaGorze(mozliweBicia[i], 4);
                }
            }
        else                                                   // strzalki dla normalnego ruchu
            for(int i=0; i<4; i++)
            {
                if(mozliweRuchy[i]>0 && mozliweRuchy[i]<13)
                    strzalkaNaDole(mozliweRuchy[i], 22);
                else if(mozliweRuchy[i]>12 && mozliweRuchy[i]<25)
                    strzalkaNaGorze(mozliweRuchy[i], 4);
            }
    }

    bool daSieRuszyc()              // sprawdzanie czy dany pionek ma dostepne poprawne ruchy
    {
        for(int i=0; i<4; i++)
        {
            if(bicie)
            {
                if(mozliweBicia[i] != 0)        // jak 0 to nie mozna sie ruszyc
                    return true;
            }
            else if(mozliweRuchy[i] != 0)       // jak 0 to nie mozna sie ruszyc
                return true;
        }
        return false;
    }
};

void nowaGra(Gracz *gracz1, Gracz *gracz2)      // inicjalizacja nowej gry
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

void rysujObramowanie()
{
    for (int i=0; i<SZEROKOSC; i++)     // dla kazdej kolumny 3 wiersze
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
    for (int i=0; i<WYSOKOSC; i++)      // dla kazdego wiersza 3 kolumny
    {
        for (int j=10; j<=70; j+=30)
        {
            gotoxy(j, 6+i);
            cputs(":");
        }
    }
    for (int i=13; i<=24; i++)      // liczby
    {
        gotoxy((12 + (i-13) * 5), 5);
        cout << i;
    }
    for (int i = 12; i >= 1; --i)    // liczby
    {
        gotoxy((12 + (12 - i) * 5), 21);
        cout << i;
    }
}

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
    for(int i=0; i< gracz->zbitePionki; i++)
    {
        if(i>0)             // ten przecinek wykona sie przynajmniej dla i=1 wiec druga iteracja
            cputs(", ");
        if(gracz->kierunekDodatni)
            cputs("()");
        else
            cputs("{}");
    }
    cputs("       ");
}


void rysujPionki(Gracz *gracz1, Gracz *gracz2)      //gracz1 - obecnie ruszajacy sie gracz    gracz2 - obecnie nie ruszajacy sie gracz
{
    for(int i=0; i<12; i++)
    {
        //gorna czesc planszy
        if(gracz1->pionki[12+i]>0)      // wieksze od 0 bo w tej tablicy wartosc to ilosc pionkow na danym polu
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


void wyswietlPlansze(Gracz *gracz1, Gracz *gracz2)      // gracz1 - obecnie ruszajacy sie gracz  gracz2 - obecnie nie ruszajacy sie gracz
{
    system("cls");
    rysujObramowanie();
    rysujPionki(gracz1, gracz2);
}

//Sprawdzanie czy pole docelowe jest poprwanym ruchem lub biciem
//sprawdzane - ile pionow przeciwnik ma na polu docelowym
//false w wypadku zbicia lub niepoprawnego ruchu
bool sprawdzPole(int miejsceDocelowe, int miejsceStartu, int sprawdzane, StanGry *stanGry, int i, bool powrot)
{
    bool zbicie = false;
    if(miejsceDocelowe != miejsceStartu)
    {
        if(powrot)      // dla powrotu
        {
            if((miejsceStartu == 0 && miejsceDocelowe < 7) || (miejsceStartu == 25 && miejsceDocelowe > 18))        
            {
                if(sprawdzane == 1)                     // jak pion powraca i jest bicie
                    stanGry->bicie = zbicie = true;         // ??????????????
                else if(sprawdzane > 1)
                    return false;
            }
        }
        else    // dla nie powrotu
        {
            if(miejsceDocelowe>0 && miejsceDocelowe<25 && sprawdzane == 1)
                stanGry->bicie = zbicie = true;
            else if((miejsceDocelowe>12 && miejsceDocelowe<25 && sprawdzane == 0) || (miejsceDocelowe<12 && miejsceDocelowe>0 && sprawdzane == 0))
            { }     // ???????????????
            else
                return false;
        }
    }
    else
        return false;
    if(zbicie)
    {
        stanGry->mozliweBicia[i] = miejsceDocelowe;
        return false;                                   // CZEMU ZWRACAMY FALSE???
    }
    return true;
}

// funkcja sprawdzajaca i rysujaca mozliwe ruchy
void rysujMozliweRuchy(Gracz *czekajacy, int miejsceStartu, StanGry *stanGry, bool powrot)      // SKAD WIEMY ZE TO NAPRAWDE JEST CZEKAJACY???
{
    int miejsceDocelowe;
    bool poprawne = false;      // stworzone na potrzeby tej funkcji

    // petla sprawdzajaca czy wybrany pion moze sie poruszyc
    for(int i=0; i<4; i++)
    {
        // ustalenie wartosci zmiennej miejsceDocelowe
        if(i<2)                                                         // dla dwoch kostek po dwa razy
            miejsceDocelowe = miejsceStartu + stanGry->kostki[i];   
        else
            miejsceDocelowe = miejsceStartu - stanGry->kostki[i%2];

        // sprawdzenie czy wybrane pole docelowe ruchu jest zgodne z kierunkiem ruchu pionow gracza
        if(czekajacy->kierunekDodatni)              // CZEMU CZEKAJACY
        {
            if(miejsceDocelowe < miejsceStartu)     // CZY TU NIE MA NA ODWROT???
                poprawne = true;
        }
        else
        {
            if(miejsceDocelowe > miejsceStartu)
                poprawne = true;
        }

        if(poprawne)
            //Sprawdzanie czy znaleziony ruch jest poprawnym ruchem, jesli jest biciem to kolejny if zwraca false, a pole bicia zpisane jest wewnatrz funkcji sprawdzPole()
            if(sprawdzPole(miejsceDocelowe, miejsceStartu, czekajacy->pionki[miejsceDocelowe-1], stanGry, i, powrot))
                //jesli pole jest poprawnym ruchem, zapisujemy go do tablicy
                stanGry->mozliweRuchy[i]=miejsceDocelowe;

        poprawne=false;
    }
    stanGry->rysujStrzalki();       // CZEMU TEGO NIE MA W PETLI???
}

void czyscMozliweRuchy()        // wyczyszczenie zbednych linii tekstu na konsoli   (KIEDY TAK SIE ZDARZYLO???)
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
    cputs("Wybierz inne, poprawne pole.");
}

void utrataRuchu()
{
    gotoxy(80, 6);
    cputs("Nie ma poprawnego ruchu, pas, wcisnij enter.");
}

bool poprawnyRuchFinal(Gracz *czekajacy, int miejsceStartu, StanGry *stanGry, bool powrot)
{
    rysujMozliweRuchy(czekajacy, miejsceStartu, stanGry, powrot);
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

void kolejnosc(bool ruchGracza1)
{
    gotoxy(10, 2);
    cputs("Tura gracza: ");
    if(ruchGracza1)
        cputs("(), w kierunku pola 24");
    else
        cputs("{}, w kierunku pola 1");
}

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
int ruch2(Gracz *aktywny, Gracz *czekajacy, int miejsceStartu, StanGry *stanGry, bool powrot)
{
    bool pionekRuszony = false;
    int miejsceDocelowe;
    while(!pionekRuszony)
    {
        gotoxy(80, 7);
        cin>>miejsceDocelowe;                                                       // wprowadzenie pola docelowego przez gracza
        if(stanGry->mozliwyRuch(miejsceDocelowe))
        {
            aktywny->ruchPionka(czekajacy, miejsceStartu, miejsceDocelowe);       
            pionekRuszony = true;
        }
        else
        {
            gotoxy(80, 9);
            cputs("Wybierz inne, poprawne pole");
        }
    }
    return miejsceDocelowe;
}

//Funkcja odpowiadajaca za ruch piona z wybranego pola
//aktywny - obecnie ruszajacy sie gracz
//czekajacy - obecnie nie ruszajacy sie gracz
void ruch1(Gracz *aktywny, Gracz *czekajacy, int miejsceStartu, StanGry *stanGry, bool powrot)
{
    if((!powrot && aktywny->pionki[miejsceStartu-1]>0) || powrot && aktywny->zbitePionki > 0) // jesli nie powraca i jest >0 pionkow lub powraca i jest cos zbitego   
    {
        gotoxy(80, 6);
        cputs("Wybierz miejsce ruchu: ");
        int miejsceDocelowe = ruch2(aktywny, czekajacy, miejsceStartu, stanGry, powrot);
        stanGry->poRuchu(miejsceDocelowe, miejsceStartu);
        czyscMozliweRuchy();
    }
    else
        niepoprawne();
    gotoxy(80, 5);
    clreol();
}

//gracz1 - obecnie ruszajacy sie gracz
//gracz2 - obecnie nie ruszajacy sie gracz
//stanGry - struktura z informacjami o stanie gry
//pole - wartosc pola z ktorego gracz aktywny chce poruszyc piona
void powrotPiona(Gracz *gracz1, Gracz *gracz2, StanGry *stanGry, int miejsceStartu)      // CZY MOGE ZMIENIC NAZWE NA AKTYWNY I CZEKAJACY???
{                                                                                       // GDZIE WYKORZYSTUJEMY TUTAJ POLE STARTU
    if(stanGry->turaGracza1)
    {
        if(gracz1->zbitePionki > 0)
        {
            if(poprawnyRuchFinal(gracz2, 0, stanGry, true))     // true to powrot
                ruch1(gracz1, gracz2, 0, stanGry, true);        // CZEMU MIEJSCE STARTU TO 0 JAK TYLKO Z 25 WPROWADZAMY
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
        if(gracz2->zbitePionki > 0)
        {
            if(poprawnyRuchFinal(gracz1, 25, stanGry, true))
                ruch1(gracz2, gracz1, 25, stanGry, true);
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
void normalnyRuch(Gracz *gracz1, Gracz *gracz2, StanGry *stanGry, int miejsceStartu)
{
    if(stanGry->turaGracza1)
    {
        if(gracz1->pionki[miejsceStartu-1]>0 && gracz1->zbitePionki == 0)       // jesli na poluStartu sa jakies pionki i nie ma zbitych pionkow
        {
            if(poprawnyRuchFinal(gracz2, miejsceStartu, stanGry, false))
                ruch1(gracz1, gracz2, miejsceStartu, stanGry, false);
        }
        else
            niepoprawne();
    }
    else
    {
        if(gracz2->pionki[miejsceStartu-1]>0 && gracz2->zbitePionki == 0)
        {
            if(poprawnyRuchFinal(gracz1, miejsceStartu, stanGry, false))
                ruch1(gracz2, gracz1, miejsceStartu, stanGry, false);
        }
        else
            niepoprawne();
    }
}

//gracz1 - obecnie ruszajacy sie gracz
//gracz2 - obecnie nie ruszajacy sie gracz
int wybierzPoleStartowe(Gracz *gracz1, Gracz *gracz2, StanGry *stanGry)     // funkcja glowna odpowiadajaca za wybor pola z ktorego bedziemy ruszac piona
{
    stanGry->wykonanoRuch = false;
    while(true)
    {
        int poleStartowe;
        wynikRzutu(stanGry);
        cin >> poleStartowe;
        if(poleStartowe == 0)
            return poleStartowe;  // DLACZEGO???
        else if(poleStartowe == 25)
            powrotPiona(gracz1, gracz2, stanGry, poleStartowe);
        else
            normalnyRuch(gracz1, gracz2, stanGry, poleStartowe);
        if(stanGry->wykonanoRuch == true)
        {
            stanGry->wykonanoRuch = false;
            return 1;       // DLACZEGO RETURN 1???
        }
    }
}

int gra(bool nowa)     // nowa - czy nowa gra czy wczytujemy                     (funkcja matka)
{
    bool start = true;
    int miejsceStartu;
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

        if(wybierzPoleStartowe(&gracz1, &gracz2, &stanGry) == 0)
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
