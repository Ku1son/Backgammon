#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>



extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#define RIGHT_SHORTER_BARIER 930
#define RIGHT_LONGER_BARIER 988
#define LEFT_SHORTER_BARIER 92
#define LEFT_LONGER_BARIER 150
#define FIRST_PODLOGA_Y 82




enum ObecnyEtap
{
	menu = 0,	
	gra = 1,
	poZbiciu = 2,
	wyborEtapu = 3,
	wyniki = 4,
	zapiszWynik = 5,
	wygrana = 6
};

struct Mapa {
	int drabinaX[8];
	int drabinaY[8];
	int podlogaX[8];
	int podlogaY[8];
	int podlogaP3X[2];
	int podlogaP3Y[2];


	Mapa(int nrMapy)
	{
		if (nrMapy == 1)
		{
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
				case 0:
					drabinaX[i] = 530;
					drabinaY[i] = 610;
					break;
				case 1:
					drabinaX[i] = 640;
					drabinaY[i] = 510;
					break;
				case 2:
					drabinaX[i] = 250;
					drabinaY[i] = 510;
					break;
				case 3:
					drabinaX[i] = 250;
					drabinaY[i] = 510;
					break;
				case 4:
					drabinaX[i] = 400;
					drabinaY[i] = 410;
					break;
				case 5:
					drabinaX[i] = 750;
					drabinaY[i] = 410;
					break;
				case 6:
					drabinaX[i] = 570;
					drabinaY[i] = 310;
					break;
				case 7:
					drabinaX[i] = 200;
					drabinaY[i] = 310;
					break;
				}
			}
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
				case 0:
					podlogaX[i] = 70;
					podlogaY[i] = 700;
					break;
				case 1:
					podlogaX[i] = 130;
					podlogaY[i] = 600;
					break;
				case 2:
					podlogaX[i] = 70;
					podlogaY[i] = 500;
					break;
				case 3:
					podlogaX[i] = 130;
					podlogaY[i] = 400;
					break;
				case 4:
					podlogaX[i] = 70;
					podlogaY[i] = 300;
					break;
				}
			}
		}
		else if (nrMapy == 2)
		{
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
				case 0:
					drabinaX[i] = 850;
					drabinaY[i] = 610;
					break;
				case 1:
					drabinaX[i] = 850;
					drabinaY[i] = 610;
					break;
				case 2:
					drabinaX[i] = 450;
					drabinaY[i] = 510;
					break;
				case 3:
					drabinaX[i] = 450;
					drabinaY[i] = 510;
					break;
				case 4:
					drabinaX[i] = 330;
					drabinaY[i] = 410;
					break;
				case 5:
					drabinaX[i] = 830;
					drabinaY[i] = 410;
					break;
				case 6:
					drabinaX[i] = 630;
					drabinaY[i] = 310;
					break;
				case 7:
					drabinaX[i] = 730;
					drabinaY[i] = 310;
					break;
				}
			}
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
				case 0:
					podlogaX[i] = 70;
					podlogaY[i] = 700;
					break;
				case 1:
					podlogaX[i] = 130;
					podlogaY[i] = 600;
					break;
				case 2:
					podlogaX[i] = 70;
					podlogaY[i] = 500;
					break;
				case 3:
					podlogaX[i] = 130;
					podlogaY[i] = 400;
					break;
				case 4:
					podlogaX[i] = 70;
					podlogaY[i] = 300;
					break;
				}
			}
		}
		else if (nrMapy == 3)
		{
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
				case 0:
					drabinaX[i] = 600;
					drabinaY[i] = 610;
					break;
				case 1:
					drabinaX[i] = 590;
					drabinaY[i] = 110;
					break;
				case 2:
					drabinaX[i] = 340;
					drabinaY[i] = 510;
					break;
				case 3:
					drabinaX[i] = 750;
					drabinaY[i] = 510;
					break;
				case 4:
					drabinaX[i] = 480;
					drabinaY[i] = 410;
					break;
				case 5:
					drabinaX[i] = 850;
					drabinaY[i] = 410;
					break;
				case 6:
					drabinaX[i] = 270;
					drabinaY[i] = 210;
					break;
				case 7:
					drabinaX[i] = 640;
					drabinaY[i] = 310;
					break;
				}
			}
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
				case 0:
					podlogaX[i] = 70;
					podlogaY[i] = 700;
					break;
				case 1:
					podlogaX[i] = 130;
					podlogaY[i] = 600;
					break;
				case 2:
					podlogaX[i] = 70;
					podlogaY[i] = 500;
					break;
				case 3:
					podlogaX[i] = 130;
					podlogaY[i] = 400;
					break;
				case 4:
					podlogaX[i] = 70;
					podlogaY[i] = 300;
					break;
				}
			}
			podlogaP3X[0] = 130;
			podlogaP3Y[0] = 200;
			podlogaP3X[1] = 70;
			podlogaP3Y[1] = 100;
		}
	}
};

struct Mario {
	double SpeedMultiplier;
	double SpeedX;
	double SpeedY;
	double X;
	double Y;
	bool naDrabinie;
	bool skok;
	int klatkiSkoku;
	Mario()
	{
		X = SCREEN_WIDTH / 5;
		Y = 680;
		SpeedMultiplier = 300.0;
		SpeedX = 0.0;
		SpeedY = 0.0;
		naDrabinie = false;
		skok = false;
		klatkiSkoku = 200;
	}
	void restart()
	{
		X = SCREEN_WIDTH / 5;
		Y = 680;
		SpeedMultiplier = 300.0;
		SpeedX = 0.0;
		SpeedY = 0.0;
		naDrabinie = false;
		skok = false;
		klatkiSkoku = 200;
	}
	void addX(double delta)
	{
		X += SpeedX * SpeedMultiplier * delta;
	}
	void addY(double delta)
	{
		Y += SpeedY * SpeedMultiplier * delta;
	}
	void ruchX(double wartosc)
	{
		SpeedX = wartosc;
	}
	void ruchY(double wartosc)
	{
		SpeedY = wartosc;
	}
	void zapisz(FILE* plik)
	{
		fwrite(&SpeedMultiplier, sizeof(double), 1, plik);
		fwrite(&SpeedX, sizeof(double), 1, plik);
		fwrite(&SpeedY, sizeof(double), 1, plik);
		fwrite(&X, sizeof(double), 1, plik);
		fwrite(&Y, sizeof(double), 1, plik);
		fwrite(&naDrabinie, sizeof(bool), 1, plik);
		fwrite(&skok, sizeof(bool), 1, plik);
		fwrite(&klatkiSkoku, sizeof(int), 1, plik);
	}
	void wczytaj(FILE* plik)
	{
		fread(&SpeedMultiplier, sizeof(double), 1, plik);
		fread(&SpeedX, sizeof(double), 1, plik);
		fread(&SpeedY, sizeof(double), 1, plik);
		fread(&X, sizeof(double), 1, plik);
		fread(&Y, sizeof(double), 1, plik);
		fread(&naDrabinie, sizeof(bool), 1, plik);
		fread(&skok, sizeof(bool), 1, plik);
		fread(&klatkiSkoku, sizeof(int), 1, plik);
	}
	void skokInterval(Mapa mapa)
	{
		if (klatkiSkoku > 0)
		{
			Y -= ((((double)klatkiSkoku / 20.0) - 5.0) / 1000.0) * SpeedMultiplier;
			klatkiSkoku--;
		}
		if (klatkiSkoku == 0)
		{
			Y -= ((((double)klatkiSkoku / 20.0) - 5.0) / 1000.0) * SpeedMultiplier;
			klatkiSkoku = 200;
			skok = false;
		}
		for (int i = 0; i < 5; i++)
		{
			if (Y + 20 > mapa.podlogaY[i] && Y + 20 < mapa.podlogaY[i] + 10)
				Y = mapa.podlogaY[i] - 20;
		}

	}
};

struct Barrel {
	double SpeedMultiplier;  
	double SpeedX;
	double SpeedY;
	double X;
	double Y;
	bool moveRight = true;

	Barrel()
	{
		X = 140;
		Y = 282;
		SpeedMultiplier = 1000.0;
		SpeedX = 0.0;
		SpeedY = 0.0;
	}
	void restart(int wybranaMapa)
	{
		switch (wybranaMapa)
		{
		case 1:
			X = 140;
			Y = 282;
			break;
		case 2:
			X = 140;
			Y = 282;
			break;
		case 3:
			X = 240;
			Y = 82;
			break;
		}
		SpeedMultiplier = 1000.0;
		SpeedX = 0.0;
		SpeedY = 0.0;
		moveRight = true;
	}
	void addX(double delta)
	{
		X += SpeedX * SpeedMultiplier * delta;
	}
	void addY(double delta)
	{
		Y += SpeedY * SpeedMultiplier * delta;
	}
	void ruchX(double wartosc)
	{
		SpeedX = wartosc;
	}
	void ruchY(double wartosc)
	{
		SpeedY = wartosc;
	}
	void zapisz(FILE* plik)
	{
		fwrite(&SpeedMultiplier, sizeof(double), 1, plik);
		fwrite(&SpeedX, sizeof(double), 1, plik);
		fwrite(&SpeedY, sizeof(double), 1, plik);
		fwrite(&X, sizeof(double), 1, plik);
		fwrite(&Y, sizeof(double), 1, plik);
		fwrite(&moveRight, sizeof(bool), 1, plik);
	}
	void wczytaj(FILE* plik)
	{
		fread(&SpeedMultiplier, sizeof(double), 1, plik);
		fread(&SpeedX, sizeof(double), 1, plik);
		fread(&SpeedY, sizeof(double), 1, plik);
		fread(&X, sizeof(double), 1, plik);
		fread(&Y, sizeof(double), 1, plik);
		fread(&moveRight, sizeof(bool), 1, plik);
	}
	bool kolizja(Mario mario)
	{
		int marioLeft = mario.X - 13;
		int marioRight = mario.X + 13;
		int marioTop = mario.Y - 20;
		int marioBottom = mario.Y + 20;

		int barrelLeft = X - 24;
		int barrelRight = X + 24;
		int barrelTop = Y - 21;
		int barrelBottom = Y + 21;

		if (marioRight >= barrelLeft && marioLeft <= barrelRight &&
			marioBottom >= barrelTop && marioTop <= barrelBottom) {
			return true;
		}
		return false;
	}
};

struct Monkey {
	double X;
	double Y;

	Monkey()
	{
		X = 110;
		Y = 282;
	}
	void restart(int wybranaMapa)
	{
		X = 110;
		Y = 282;
		if (wybranaMapa == 3)
		{
			X = 200;
			Y = 82;
		}
	}
	void zapisz(FILE* plik)
	{
		fwrite(&X, sizeof(double), 1, plik);
		fwrite(&Y, sizeof(double), 1, plik);
	}
	void wczytaj(FILE* plik)
	{
		fread(&X, sizeof(double), 1, plik);
		fread(&Y, sizeof(double), 1, plik);
	}
};

struct Princess {
	double X;
	double Y;

	Princess()
	{
		X = 360;
		Y = 276;
	}
	void restart(int wybranaMapa)
	{
		X = 360;
		Y = 276;
		if (wybranaMapa == 3)
		{
			X = 400;
			Y = 76;
		}
	}
	void zapisz(FILE* plik)
	{
		fwrite(&X, sizeof(double), 1, plik);
		fwrite(&Y, sizeof(double), 1, plik);
	}
	void wczytaj(FILE* plik)
	{
		fread(&X, sizeof(double), 1, plik);
		fread(&Y, sizeof(double), 1, plik);
	}
	bool kolizja(Mario mario)
	{
		int marioLeft = mario.X - 13;
		int marioRight = mario.X + 13;
		int marioTop = mario.Y - 20;
		int marioBottom = mario.Y + 20;

		int princessLeft = X - 17;
		int princessRight = X + 17;
		int princessTop = Y - 30;
		int princessBottom = Y + 30;

		if (marioRight >= princessLeft && marioLeft <= princessRight &&
			marioBottom >= princessTop && marioTop <= princessBottom) {
			return true;
		}
		return false;
	}
};

struct Heart {
	double X[3];
	double Y[3];
	bool isActive[3];

	Heart()
	{
		for (int i = 0; i < 3; i++) {
			X[i] = 30 + i * 52;
			Y[i] = 70;
			isActive[i] = true;
		}
	}
	void restart()
	{
		for (int i = 0; i < 3; i++) {
			isActive[i] = true;
		}
		for (int i = 0; i < 3; i++) {
			X[i] = 30 + i * 52;
			Y[i] = 70;
			isActive[i] = true;
		}
	}
	int heartLeft()
	{
		int n = 0;
		for (int i = 0; i < 3; i++)
		{
			if (isActive[i] == true)
				n++;
		}
		return n;
	}
	void zapisz(FILE* plik)
	{
		fwrite(X, sizeof(double), 3, plik);
		fwrite(Y, sizeof(double), 3, plik);
		fwrite(isActive, sizeof(bool), 3, plik);
	}
	void wczytaj(FILE* plik)
	{
		fread(X, sizeof(double), 3, plik);
		fread(Y, sizeof(double), 3, plik);
		fread(isActive, sizeof(bool), 3, plik);
	}
	bool isGameOver()
	{
		for (int i = 0; i < 3; ++i) {
			if (isActive[i])
				return false;
		}
		return true;
	}
};

struct Trophy {
	double X;
	double Y;
	bool active;

	Trophy()
	{
		X = 120;
		Y = 486;
		active = true;
	}
	bool kolizja(Mario mario)
	{
		if (active == false)
			return false;

		int marioLeft = mario.X - 13;
		int marioRight = mario.X + 13;
		int marioTop = mario.Y - 20;
		int marioBottom = mario.Y + 20;

		int trophyLeft = X - 20;
		int trophyRight = X + 20;
		int trophyTop = Y - 22;
		int trophyBottom = Y + 22;

		if (marioRight >= trophyLeft && marioLeft <= trophyRight &&
			marioBottom >= trophyTop && marioTop <= trophyBottom) {
			return true;
		}
		return false;
	}
};

struct StanGry {
	int punkty;
	int ukonczonePoziomy;
	int bonus;
	int wybranaMapa;
	bool bladOdczytu;
	bool trwaGra;
	ObecnyEtap obecnyEtap;

	StanGry()
	{
		wybranaMapa = 1;
		obecnyEtap = menu;
		trwaGra = bladOdczytu = false;
		punkty = ukonczonePoziomy = bonus = 0;
		//punkty, 1000 na start
		//-10 za każde 2 sekundy w grze
		//-250 za stratę życia, 
		//+500 za poziom
		//+100 za puchar
	}
	void nowaGra()
	{
		wybranaMapa = 1;
		obecnyEtap = gra;
		trwaGra = true;
		punkty = ukonczonePoziomy = bonus = 0;
	}
	void zmienEtap(ObecnyEtap wybrany)
	{
		obecnyEtap = wybrany;
	}
	void liczPunkty(int zycia, int worldTime)
	{
		punkty = 250 + 250 * zycia + 500 * ukonczonePoziomy - (worldTime / 10) * 100 + 100 * bonus;
	}
	void zapisz(FILE* plik)
	{
		fwrite(&bonus, sizeof(int), 1, plik);
		fwrite(&ukonczonePoziomy, sizeof(int), 1, plik);
		fwrite(&wybranaMapa, sizeof(int), 1, plik);
	}
	void wczytaj(FILE* plik)
	{
		fread(&bonus, sizeof(int), 1, plik);
		fread(&ukonczonePoziomy, sizeof(int), 1, plik);
		fread(&wybranaMapa, sizeof(int), 1, plik);
	}
};


void zapisGry(bool active, double worldTime, Mario* mario, Barrel* barell, Monkey* monkey, Princess* princess, Heart* heart, StanGry* stanGry)
{
	const char* nazwaPliku = "zapis.bin";
	FILE* plik = fopen(nazwaPliku, "wb");
	if (!plik)
		return;
	fwrite(&active, sizeof(bool), 1, plik);
	fwrite(&worldTime, sizeof(double), 1, plik);
	stanGry->zapisz(plik);
	mario->zapisz(plik);
	barell->zapisz(plik);
	monkey->zapisz(plik);
	princess->zapisz(plik);
	heart->zapisz(plik);
	fclose(plik);
}

bool wczytanieGry(bool* active, double* worldTime, Mario* mario, Barrel* barell, Monkey* monkey, Princess* princess, Heart* heart, StanGry* stanGry)
{
	const char* nazwaPliku = "zapis.bin";
	FILE* plik = fopen(nazwaPliku, "rb");
	if (!plik)
		return false;
	stanGry->nowaGra();
	fread(&active, sizeof(bool), 1, plik);
	fread(&worldTime, sizeof(double), 1, plik);
	stanGry->wczytaj(plik);
	mario->wczytaj(plik);
	barell->wczytaj(plik);
	monkey->wczytaj(plik);
	princess->wczytaj(plik);
	heart->wczytaj(plik);
	fclose(plik);
	return true;
}

// narysowanie napisu txt na powierzchni screen, zaczynajac od punktu (x, y)
// charset to bitmapa 128x128 zawieraj¹ca znaki
void DrawString(SDL_Surface* screen, int x, int y, const char* text,
	SDL_Surface* charset)
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y) (x, y) to punkt srodka obrazka sprite na ekranie
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y)
{
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color)
{
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

// rysowanie linii o dlugosci l w pionie (gdy dx = 0, dy = 1) b¹dŸ poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color)
{
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

// rysowanie prostok¹ta o d³ugoœci boków l i k
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor)
{
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};

void rysujPodloge(SDL_Surface* screen, int x, int y)
{
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	DrawRectangle(screen, x, y, SCREEN_WIDTH - 200, 10, czarny, czerwony);
}

void rysujDrabine(SDL_Surface* screen, int x, int y)
{
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	DrawRectangle(screen, x, y, 8, 90, czarny, niebieski);
}

void rysujPlansze(SDL_Surface* screen, Mapa mapa, int& wybranaMapa, Monkey& monkey, Princess& princess, Barrel& barrel)
{
	for (int j = 0; j < 5; j++)
	{
		rysujPodloge(screen, mapa.podlogaX[j], mapa.podlogaY[j]);
	}
	for (int j = 0; j < 8; j++)
	{
		rysujDrabine(screen, mapa.drabinaX[j], mapa.drabinaY[j]);
	}
	if (wybranaMapa == 3)
	{
		for (int i = 0; i < 2; i++)
		{
			rysujPodloge(screen, mapa.podlogaP3X[i], mapa.podlogaP3Y[i]);
		}
	}
}

void timeRestart(double& worldTime)
{
	worldTime = 0;
}

bool kolizjaMarioDrabina(Mario mario, Mapa mapa)
{
	int marioLeft = mario.X - 13;
	int marioRight = mario.X + 13;
	int marioTop = mario.Y - 20;
	int marioBottom = mario.Y + 20;

	for (int i = 0; i < 8; i++) {
		int drabinaLeft = mapa.drabinaX[i];
		int drabinaRight = mapa.drabinaX[i] + 8;
		int drabinaTop = mapa.drabinaY[i] - 10;
		int drabinaBottom = mapa.drabinaY[i] + 50;

		if (marioRight >= drabinaLeft && marioLeft <= drabinaRight &&
			marioBottom >= drabinaTop && marioTop <= drabinaBottom) {
			return true;
		}
	}
	return false;
}

bool deleteOnlyOneHeart(bool& flag)
{
	if (flag) {
		flag = false;
		return true;
	}
	return false;
}

void resetFlag(bool& flag)
{
	flag = true;
}

void moveBarrel(Barrel& barrel, bool& flag, double delta, int wybranaMapa)
{
	if (barrel.X > RIGHT_SHORTER_BARIER && barrel.Y > 680) {
		barrel.restart(wybranaMapa);
		resetFlag(flag);
	}
	else {
		if (barrel.moveRight) {
			barrel.X += barrel.SpeedMultiplier * delta;
		}
		else {
			barrel.X -= barrel.SpeedMultiplier * delta;
		}
		if (barrel.X > RIGHT_LONGER_BARIER + 12) {
			barrel.Y += 100;

			barrel.moveRight = false;

			barrel.X = 1000;
		}
		else if (barrel.X < LEFT_LONGER_BARIER - 50) {
			barrel.Y += 100;

			barrel.moveRight = true;

			barrel.X = 100;
		}
	}
}

void gameOver(Mario& mario, Barrel& barrel, Heart& heart, double& worldTime, bool& flag, int wybranaMapa) {	// TODO dodanie logiki gdy koniec gry (wyswietlenie menu)
	mario.restart();
	barrel.restart(wybranaMapa);
	heart.restart();
	timeRestart(worldTime);
	resetFlag(flag);
}

bool canMoveRight(Mario& mario)
{
	if (mario.X >= RIGHT_SHORTER_BARIER && (mario.Y < FIRST_PODLOGA_Y + 600 && mario.Y > FIRST_PODLOGA_Y + 595) ||
		mario.X >= RIGHT_SHORTER_BARIER && (mario.Y < FIRST_PODLOGA_Y + 400 && mario.Y > FIRST_PODLOGA_Y + 395) ||
		mario.X >= RIGHT_SHORTER_BARIER && (mario.Y < FIRST_PODLOGA_Y + 200 && mario.Y > FIRST_PODLOGA_Y + 195) ||
		mario.X >= RIGHT_SHORTER_BARIER && (mario.Y < FIRST_PODLOGA_Y && mario.Y > FIRST_PODLOGA_Y - 5))
	{
		return false;
	}
	else if (mario.X >= RIGHT_LONGER_BARIER && (mario.Y < FIRST_PODLOGA_Y + 500 && mario.Y > FIRST_PODLOGA_Y + 495) ||
			 mario.X >= RIGHT_LONGER_BARIER && (mario.Y < FIRST_PODLOGA_Y + 300 && mario.Y > FIRST_PODLOGA_Y + 295) ||
			 mario.X >= RIGHT_LONGER_BARIER && (mario.Y < FIRST_PODLOGA_Y + 100 && mario.Y > FIRST_PODLOGA_Y + 95))
	{
		return false;
	}

	return true;
}

bool canMoveLeft(Mario& mario)
{
	if (mario.X <= LEFT_SHORTER_BARIER && (mario.Y < FIRST_PODLOGA_Y + 600 && mario.Y > FIRST_PODLOGA_Y + 595) ||
		mario.X <= LEFT_SHORTER_BARIER && (mario.Y < FIRST_PODLOGA_Y + 400 && mario.Y > FIRST_PODLOGA_Y + 395) ||
		mario.X <= LEFT_SHORTER_BARIER && (mario.Y < FIRST_PODLOGA_Y + 200 && mario.Y > FIRST_PODLOGA_Y + 195))

	{
		return false;
	}
	else if (mario.X <= LEFT_LONGER_BARIER && (mario.Y < FIRST_PODLOGA_Y + 500 && mario.Y > FIRST_PODLOGA_Y + 495) ||
		mario.X <= LEFT_LONGER_BARIER && (mario.Y < FIRST_PODLOGA_Y + 300 && mario.Y > FIRST_PODLOGA_Y + 295) ||
		mario.X <= LEFT_LONGER_BARIER && (mario.Y < FIRST_PODLOGA_Y + 100 && mario.Y > FIRST_PODLOGA_Y + 95))
	{
		return false;
	}
	return true;
}

void bonusForBarrel(Barrel& barrel, Mario& mario, StanGry& stanGry)
{
	if (mario.Y < barrel.Y && ((barrel.Y - mario.Y) < 3) && mario.skok)
	{
		stanGry.bonus++;
	}
}


// 11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111

#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char** argv) {

	int t1, t2, quit, frames, rc;
	double worldTime, fpsTimer, fps, distance;
	double delta;
	bool flag = true;
	const char* tytul = "```  KING DONKEY  '''";

	Mapa mapa[3] = { Mapa(1), Mapa(2), Mapa(3) };
	Mario mario = Mario();
	Barrel barrel = Barrel();
	Monkey monkey = Monkey();
	Princess princess = Princess();
	Heart heart = Heart();
	Trophy trophy = Trophy();
	StanGry stanGry = StanGry();

	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* marioPNG;
	SDL_Surface* barrelPNG;
	SDL_Surface* monkeyPNG;
	SDL_Surface* princessPNG;
	SDL_Surface* heartPNG;
	SDL_Surface* trophyPNG;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;

	// okno konsoli nie jest widoczne, je¿eli chcemy zobaczyæ
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmieniæ na "Console"

	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	// tryb pe³noekranowy / fullscreen mode
//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
//	                                 &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Projekt King Donkey - Szymon Kula");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	SDL_SetColorKey(charset, true, 0x000000);

	marioPNG = SDL_LoadBMP("./mario.bmp");
	if (marioPNG == NULL) {
		printf("SDL_LoadBMP(mario.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	barrelPNG = SDL_LoadBMP("./barrel.bmp");
	if (barrelPNG == NULL) {
		printf("SDL_LoadBMP(mario.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	monkeyPNG = SDL_LoadBMP("./monkey.bmp");
	if (monkeyPNG == NULL) {
		printf("SDL_LoadBMP(monkey.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	princessPNG = SDL_LoadBMP("./princess.bmp");
	if (princessPNG == NULL) {
		printf("SDL_LoadBMP(princess.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	heartPNG = SDL_LoadBMP("./heart.bmp");
	if (heartPNG == NULL) {
		printf("SDL_LoadBMP(princess.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	trophyPNG = SDL_LoadBMP("./trophy.bmp");
	if (trophyPNG == NULL) {
		printf("SDL_LoadBMP(trophy.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	t1 = SDL_GetTicks();

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	worldTime = 0;
	distance = 0;

	//zmienne stanu gry
	char* elementyMenu[] = { "Wznow gre", "Nowa gra", "Zapisz gre", "Wczytaj gre", "Wyniki // nie zrobione", "Wybor etapu", "Wyjscie" };
	int iloscElementowMenu = 7, wybranyElement = 1, wybrany = 1;
	char strzalka;

	char nick[10] = "";

	while (!quit) {	// 2222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222

		SDL_FillRect(screen, NULL, czarny);

		// ========================== Menu glowne ========================== //
		if (stanGry.obecnyEtap == menu)
		{
			DrawString(screen, screen->w / 2 - strlen(tytul) * 8 / 2, screen->h / 5, tytul, charset);
			if (wybranyElement == 0 && !stanGry.trwaGra)
				wybranyElement == 1;

			if (!stanGry.trwaGra)
			{
				sprintf(text, "Brak trwajacej gry");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 5 + 30, text, charset);
			}
			if (stanGry.bladOdczytu)
			{
				sprintf(text, "Nie udalo sie wczytac zapisu");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 5 + 40, text, charset);
			}

			for (int i = 0; i < iloscElementowMenu; i++)
			{
				if (i != 0 || stanGry.trwaGra)
				{
					if (i == wybranyElement)
						sprintf(text, "---> %s <---", elementyMenu[i]);
					else
						sprintf(text, elementyMenu[i]);
					DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + i * 15, text, charset);
				}
			}
			sprintf(text, "Podaj swoj nick, maksymalnie 9 znakow:");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 200, text, charset);
			DrawString(screen, screen->w / 2 - strlen(nick) * 8 / 2, screen->h / 3 + 215, nick, charset);

			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
					else if (event.key.keysym.sym == SDLK_UP)
					{
						wybranyElement--;
						if (wybranyElement == -1 && stanGry.trwaGra || wybranyElement == 0 && !stanGry.trwaGra)
							wybranyElement = iloscElementowMenu - 1;
					}
					else if (event.key.keysym.sym == SDLK_DOWN)
					{
						wybranyElement++;
						if (wybranyElement == iloscElementowMenu && stanGry.trwaGra)
							wybranyElement = 0;
						else if (wybranyElement == iloscElementowMenu && !stanGry.trwaGra)
							wybranyElement = 1;
					}
					else if (event.key.keysym.sym == SDLK_RETURN)
					{
						stanGry.bladOdczytu = false;
						//Wybor opcji z menu "Wznow gre", "Nowa gra", "Zapisz gre", "Wczytaj gre", "Wyniki - WIP", "Wybor etapu", "Wyjscie" };
						switch (wybranyElement)
						{
						case 0://wznow gre
							stanGry.zmienEtap(gra);
							break;
						case 1://Nowa gra
							mario.restart();
							stanGry.nowaGra();
							monkey.restart(stanGry.wybranaMapa);
							princess.restart(stanGry.wybranaMapa);
							barrel.restart(stanGry.wybranaMapa);
							heart.restart();
							timeRestart(worldTime);
							trophy.active = true;
							break;
						case 2://Zapisz gre
							if (stanGry.trwaGra)
							{
								zapisGry(trophy.active, worldTime, &mario, &barrel, &monkey, &princess, &heart, &stanGry);
								stanGry.trwaGra = false;
							}
							break;
						case 3://Wczytaj gre
							if (wczytanieGry(&trophy.active, &worldTime, &mario, &barrel, &monkey, &princess, &heart, &stanGry))
								stanGry.zmienEtap(gra);
							else
								stanGry.bladOdczytu = true;
							break;
						case 5://Wybor etapu
							stanGry.zmienEtap(wyborEtapu);
							break;
						case 6://Wyjscie
							quit = 1;
							break;
						}
					}
					else if (event.key.keysym.sym == SDLK_BACKSPACE)
					{
						int length = strlen(nick);
						if (length > 0)
							nick[length - 1] = '\0';
					}
					else
					{
						int length = strlen(nick);
						if (length < 9)
						{
							nick[length] = *SDL_GetKeyName(event.key.keysym.sym);
							nick[length + 1] = '\0';
						}
					}
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
		}
		// ============================= Wybor etapu z menu ============================= //
		else if (stanGry.obecnyEtap == wyborEtapu)
		{
			sprintf(text, "Wybierz etap gry:");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 4, text, charset);
			sprintf(text, "Wcisnij enter aby potwierdzic, lub escape zeby wrocic");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3, text, charset);
			for (int i = 1; i < 4; i++)
			{
				if (wybrany == i)
					sprintf(text, "-->%d<--", i);
				else
					sprintf(text, "%d", i);
				DrawString(screen, screen->w / 3 - strlen(text) * 8 / 2 + 88 * i, screen->h / 4 + 30, text, charset);
			}

			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
						stanGry.zmienEtap(menu);
					else if (event.key.keysym.sym == SDLK_RIGHT)
					{
						wybrany++;
						if (wybrany == 4)
							wybrany = 1;
					}
					else if (event.key.keysym.sym == SDLK_LEFT)
					{
						wybrany--;
						if (wybrany == 0)
							wybrany = 3;
					}
					else if (event.key.keysym.sym == SDLK_RETURN)
					{
						heart.restart();
						timeRestart(worldTime);
						stanGry.nowaGra();
						stanGry.wybranaMapa = wybrany;
						mario.restart();
						princess.restart(stanGry.wybranaMapa);
						monkey.restart(stanGry.wybranaMapa);
						barrel.restart(stanGry.wybranaMapa);
						trophy.active = true;
					}
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
		}
		// ========================= Informacja po utracie życia ========================= //
		else if (stanGry.obecnyEtap == poZbiciu)
		{
			stanGry.liczPunkty(heart.heartLeft(), (int)worldTime);	
			for (int i = 0; i < 3; i++) {	
				if (heart.isActive[i]) {
					DrawSurface(screen, heartPNG, heart.X[i], heart.Y[i]);
				}
			}


			sprintf(text, "Zdobyte punkty: %d", stanGry.punkty);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 15, text, charset);


			if (heart.isGameOver())
			{
				sprintf(text, "GAME OVER");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3, text, charset);
				sprintf(text, "Esc - wyjscie");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 45, text, charset);
			}
			else
			{
				sprintf(text, "Straciles zycie");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3, text, charset);
				sprintf(text, "W - wroc do gry");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 45, text, charset);
				sprintf(text, "Esc - wyjscie");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 60, text, charset);
			}
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						stanGry.obecnyEtap = menu;
						stanGry.trwaGra = false;
						gameOver(mario, barrel, heart, worldTime, flag, stanGry.wybranaMapa);
					}
					else if (event.key.keysym.sym == SDLK_w)
					{
						if (!heart.isGameOver())
							stanGry.obecnyEtap = gra;
					}
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
		}
		// ==================================== Wygrana ==================================== //
		else if (stanGry.obecnyEtap == wygrana)
		{
			sprintf(text, "YOU WON!!!");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3, text, charset);
			sprintf(text, "Zdobyte punkty: %d", stanGry.punkty);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 15, text, charset);
			sprintf(text, "Esc - wyjscie");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 3 + 45, text, charset);

			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						stanGry.obecnyEtap = menu;
						stanGry.trwaGra = false;
						gameOver(mario, barrel, heart, worldTime, flag, stanGry.wybranaMapa);
					}
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
		}


		// ====================================== Gra ====================================== //
		else if (stanGry.obecnyEtap = gra)
		{
			t2 = SDL_GetTicks();
			// w tym momencie t2-t1 to czas w milisekundach,
			// jaki uplynal od ostatniego narysowania ekranu
			// delta to ten sam czas w sekundach
			delta = (t2 - t1) * 0.001;
			t1 = t2;

			worldTime += delta;

			stanGry.liczPunkty(heart.heartLeft(), (int)worldTime);

			moveBarrel(barrel, flag, delta, stanGry.wybranaMapa);

			bonusForBarrel(barrel, mario, stanGry);

			if (mario.skok)
			{
				mario.skokInterval(mapa[stanGry.wybranaMapa - 1]);
			}

			if (mario.naDrabinie)
			{
				if (!kolizjaMarioDrabina(mario, mapa[stanGry.wybranaMapa - 1])) {
					mario.naDrabinie = false;
					mario.ruchY(0.0);
				}
			}

			if (princess.kolizja(mario))
			{
				if (stanGry.wybranaMapa < 3) {
					stanGry.wybranaMapa++;
					trophy.active = true;
					monkey.restart(stanGry.wybranaMapa);
					princess.restart(stanGry.wybranaMapa);
				}
				else
				{
					stanGry.obecnyEtap = wygrana;
				}
				stanGry.ukonczonePoziomy++;
				mario.restart();
				barrel.restart(stanGry.wybranaMapa);
			}

			if (barrel.kolizja(mario))
			{
				if (deleteOnlyOneHeart(flag))
				{
					for (int i = 2; i >= 0; i--)
					{
						if (heart.isActive[i])
						{
							heart.isActive[i] = false;
							stanGry.zmienEtap(poZbiciu);
							mario.restart();
							barrel.restart(stanGry.wybranaMapa);
							resetFlag(flag);
							break;
						}
					}
				}
			}

			if (trophy.kolizja(mario))
			{
				trophy.active = false;
				stanGry.bonus++;
			}


			mario.addX(delta);
			mario.addY(delta);

			sprintf(text, "%d", stanGry.punkty);
			if (stanGry.punkty >= 1000)
				DrawString(screen, mario.X - 15, mario.Y - 30, text, charset);
			else
				DrawString(screen, mario.X - 10, mario.Y - 30, text, charset);

			DrawSurface(screen, marioPNG, mario.X, mario.Y);
			DrawSurface(screen, barrelPNG, barrel.X, barrel.Y);
			DrawSurface(screen, monkeyPNG, monkey.X, monkey.Y);
			DrawSurface(screen, princessPNG, princess.X, princess.Y);
			if (trophy.active)
				DrawSurface(screen, trophyPNG, trophy.X, trophy.Y);

			for (int i = 0; i < 3; i++) {
				if (heart.isActive[i]) {
					DrawSurface(screen, heartPNG, heart.X[i], heart.Y[i]);
				}
			}

			fpsTimer += delta;
			if (fpsTimer > 0.5) {
				fps = frames * 2;
				frames = 0;
				fpsTimer -= 0.5;
			};

			DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, czerwony, niebieski);
			sprintf(text, "Etap %d, czas trwania = %.1lf s  %.0lf klatek / s", stanGry.wybranaMapa, worldTime, fps);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
			sprintf(text, "Esc - wyjscie, n - nowa gra, \032 - ruch w lewo, \033 - ruch w prawo;	A, B, C, D, F");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

			rysujPlansze(screen, mapa[stanGry.wybranaMapa - 1], stanGry.wybranaMapa, monkey, princess, barrel);

			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) stanGry.zmienEtap(menu);
					else if (event.key.keysym.sym == SDLK_SPACE)
					{
						//if (!mario.skok && !mario.naDrabinie)
						if (!mario.skok)
						{
							mario.skok = true;
						}
					}
					else if (event.key.keysym.sym == SDLK_LEFT)
					{
						if (!mario.naDrabinie)
						{
							mario.ruchX(-1.0);
						}
						if (!canMoveLeft(mario))
						{
							mario.ruchX(0.0);
						}
					}
					else if (event.key.keysym.sym == SDLK_RIGHT)
					{
						if (!mario.naDrabinie)
						{
							mario.ruchX(1.0);
						}
						if (!canMoveRight(mario))
						{
							mario.ruchX(0.0);
						}
					}
					else if (event.key.keysym.sym == SDLK_UP)
					{
						if (kolizjaMarioDrabina(mario, mapa[stanGry.wybranaMapa - 1]))
						{
							mario.ruchY(-1.0);
							mario.naDrabinie = true;
							if (mario.skok)
							{
								mario.skok = false;
								mario.naDrabinie = 200;
							}
						}
					}
					else if (event.key.keysym.sym == SDLK_DOWN)
					{
						if (kolizjaMarioDrabina(mario, mapa[stanGry.wybranaMapa - 1]))
						{
							mario.ruchY(1.0);
							mario.naDrabinie = true;
						}
					}
					else if (event.key.keysym.sym == SDLK_n)
					{
						mario.restart();
						barrel.restart(stanGry.wybranaMapa);
						heart.restart();
						trophy.active = true;
						timeRestart(worldTime);
						stanGry.punkty = stanGry.ukonczonePoziomy = stanGry.bonus = 0;

					}
					else if (event.key.keysym.sym == SDLK_1) {
						stanGry.wybranaMapa = 1;
						mapa[stanGry.wybranaMapa - 1] = Mapa(stanGry.wybranaMapa);
						monkey.restart(stanGry.wybranaMapa);
						princess.restart(stanGry.wybranaMapa);
						barrel.restart(stanGry.wybranaMapa);
					}
					else if (event.key.keysym.sym == SDLK_2) {
						stanGry.wybranaMapa = 2;
						mapa[stanGry.wybranaMapa - 1] = Mapa(stanGry.wybranaMapa);
						monkey.restart(stanGry.wybranaMapa);
						princess.restart(stanGry.wybranaMapa);
						barrel.restart(stanGry.wybranaMapa);
					}
					else if (event.key.keysym.sym == SDLK_3) {
						stanGry.wybranaMapa = 3;
						mapa[stanGry.wybranaMapa - 1] = Mapa(stanGry.wybranaMapa);
						monkey.restart(stanGry.wybranaMapa);
						princess.restart(stanGry.wybranaMapa);
						barrel.restart(stanGry.wybranaMapa);
					}
					break;
				case SDL_KEYUP:
					mario.ruchY(0.0);
					mario.ruchX(0.0);
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
		}
		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);
		frames++;
	};

	// zwolnienie powierzchni 
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
