#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include <iostream>
using namespace std;

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#define DRABINA_WIDTH 5
#define DRABINA_HEIGHT 90
#define MARIO_WIDTH 27


struct Drabiny {
	int x[8];
	int y[8];
	int xx[8];
	int yy[8];
	int podlogaP3X[2];
	int podlogaP3Y[2];

	Drabiny(int nrMapy)
	{
		if (nrMapy == 1)
		{
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
				case 0:
					x[i] = 530;
					y[i] = 610;
					break;
				case 1:
					x[i] = 640;
					y[i] = 510;
					break;
				case 2:
					x[i] = 250;
					y[i] = 510;
					break;
				case 3:
					x[i] = 250;
					y[i] = 510;
					break;
				case 4:
					x[i] = 400;
					y[i] = 410;
					break;
				case 5:
					x[i] = 750;
					y[i] = 410;
					break;
				case 6:
					x[i] = 570;
					y[i] = 310;
					break;
				case 7:
					x[i] = 200;
					y[i] = 310;
					break;
				}
			}
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
				case 0:
					xx[i] = 70;
					yy[i] = 700;
					break;
				case 1:
					xx[i] = 130;
					yy[i] = 600;
					break;
				case 2:
					xx[i] = 70;
					yy[i] = 500;
					break;
				case 3:
					xx[i] = 130;
					yy[i] = 400;
					break;
				case 4:
					xx[i] = 70;
					yy[i] = 300;
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
					x[i] = 850;
					y[i] = 610;
					break;
				case 1:
					x[i] = 850;
					y[i] = 610;
					break;
				case 2:
					x[i] = 450;
					y[i] = 510;
					break;
				case 3:
					x[i] = 450;
					y[i] = 510;
					break;
				case 4:
					x[i] = 330;
					y[i] = 410;
					break;
				case 5:
					x[i] = 830;
					y[i] = 410;
					break;
				case 6:
					x[i] = 630;
					y[i] = 310;
					break;
				case 7:
					x[i] = 730;
					y[i] = 310;
					break;
				}
			}
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
				case 0:
					xx[i] = 70;
					yy[i] = 700;
					break;
				case 1:
					xx[i] = 130;
					yy[i] = 600;
					break;
				case 2:
					xx[i] = 70;
					yy[i] = 500;
					break;
				case 3:
					xx[i] = 130;
					yy[i] = 400;
					break;
				case 4:
					xx[i] = 70;
					yy[i] = 300;
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
					x[i] = 600;
					y[i] = 610;
					break;
				case 1:
					x[i] = 590;
					y[i] = 110;
					break;
				case 2:
					x[i] = 340;
					y[i] = 510;
					break;
				case 3:
					x[i] = 750;
					y[i] = 510;
					break;
				case 4:
					x[i] = 480;
					y[i] = 410;
					break;
				case 5:
					x[i] = 850;
					y[i] = 410;
					break;
				case 6:
					x[i] = 270;
					y[i] = 210;
					break;
				case 7:
					x[i] = 640;
					y[i] = 310;
					break;
				}
			}
			for (int i = 0; i < 8; i++)
			{
				switch (i)
				{
				case 0:
					xx[i] = 70;
					yy[i] = 700;
					break;
				case 1:
					xx[i] = 130;
					yy[i] = 600;
					break;
				case 2:
					xx[i] = 70;
					yy[i] = 500;
					break;
				case 3:
					xx[i] = 130;
					yy[i] = 400;
					break;
				case 4:
					xx[i] = 70;
					yy[i] = 300;
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


	Mario()
	{
		X = SCREEN_WIDTH / 5;
		Y = 680;
		SpeedMultiplier = 300.0;
		SpeedX = 0.0;
		SpeedY = 0.0;

	}
	void restart()
	{
		X = SCREEN_WIDTH / 5;
		Y = 680;
		SpeedMultiplier = 300.0;
		SpeedX = 0.0;
		SpeedY = 0.0;
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

};

struct Barrel {
	double SpeedMultiplier;  // Mnożnik prędkości Mario
	double SpeedX;
	double SpeedY;
	double X;
	double Y;
	bool moveRight = true;


	Barrel()
	{
		X = 140;
		Y = 282;
		SpeedMultiplier = 1000.0;	// przyspieszone do testow
		SpeedX = 0.0;
		SpeedY = 0.0;
	}
	void restart()
	{
		X = 140;
		Y = 282;
		SpeedMultiplier = 1000.0;	// przyspieszone do testow
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
};

struct Monkey {
	double X;
	double Y;

	Monkey()
	{
		X = 110;
		Y = 282;
	}
	void restart()
	{
		// TODO chyba
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
	void restart()
	{
		// TODO chyba
	}
};

struct Heart {
	double X[3];
	double Y[3];
	bool isActive[3];

	Heart()
	{
		for (int i = 0; i < 3; ++i) {
			X[i] = 30 + i * 52;
			Y[i] = 70;
			isActive[i] = true;
		}
	}
	void restart()
	{
		for (int i = 0; i < 3; ++i) {
			isActive[i] = true;
		}
		for (int i = 0; i < 3; ++i) {
			X[i] = 30 + i * 52;
			Y[i] = 70;
			isActive[i] = true;
		}
	}
};

// narysowanie napisu txt na powierzchni screen, zaczynaj¹c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj¹ca znaki
void DrawString(SDL_Surface* screen, int x, int y, const char* text,
	SDL_Surface* charset) {
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
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};
// rysowanie linii o d³ugoœci l w pionie (gdy dx = 0, dy = 1) b¹dŸ poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};
// rysowanie prostok¹ta o d³ugoœci boków l i k
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor) {
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
	DrawRectangle(screen, x, y, 5, 90, czarny, niebieski);
}

void rysujPlansze(SDL_Surface* screen, Drabiny mapa, int &wybranaMapa)
{
	for (int j = 0; j < 5; j++)
	{
		rysujPodloge(screen, mapa.xx[j], mapa.yy[j]);
	}
	for (int j = 0; j < 8; j++)
	{
		rysujDrabine(screen, mapa.x[j], mapa.y[j]);
	}
	if (wybranaMapa == 3) {
		for (int i = 0; i < 2; i++) {
			rysujPodloge(screen, mapa.podlogaP3X[i], mapa.podlogaP3Y[i]);
		}
	}
}

void timeRestart(double& worldTime) {
	worldTime = 0;
}

bool kolizjaMarioDrabina(Mario mario, Drabiny mapa) {
	int marioLeft = (mario.X - MARIO_WIDTH / 2);
	int marioRight = (mario.X + MARIO_WIDTH / 2);
	int marioTop = (mario.Y - DRABINA_HEIGHT + 110);
	int marioBottom = (mario.Y + DRABINA_HEIGHT - 60);

	for (int i = 0; i < 8; i++) {
		int drabinaLeft = mapa.x[i];
		int drabinaRight = mapa.x[i] + DRABINA_WIDTH;
		int drabinaTop = mapa.y[i];
		int drabinaBottom = mapa.y[i] + DRABINA_HEIGHT;

		if (marioRight >= drabinaLeft && marioLeft <= drabinaRight &&
			marioBottom >= drabinaTop && marioTop <= drabinaBottom) {
			return true;
		}
	}
	return false;
}

bool kolizjaMarioBarrel(Mario mario, Barrel barrel) {
	int marioLeft = mario.X - MARIO_WIDTH / 2;
	int marioRight = mario.X + MARIO_WIDTH / 2;
	int marioTop = mario.Y - DRABINA_HEIGHT + 110;
	int marioBottom = mario.Y + DRABINA_HEIGHT - 60;

	int barrelLeft = barrel.X;
	int barrelRight = barrel.X + DRABINA_WIDTH;
	int barrelTop = barrel.Y;
	int barrelBottom = barrel.Y + DRABINA_HEIGHT;

	if (marioRight >= barrelLeft && marioLeft <= barrelRight &&
		marioBottom >= barrelTop && marioTop <= barrelBottom) {
		return true;
	}
	return false;
}
bool deleteOnlyOneHeart(bool& flag) {
	if (flag) {
		flag = false;
		return true;
	}
	return false;
}
void resetFlag(bool& flag) {
	flag = true;
}

bool kolizjaMarioPrincess(Mario mario, Princess princess) {	// funkcja dziala TODO rezulat zderzenia
	int marioLeft = mario.X - MARIO_WIDTH / 2;
	int marioRight = mario.X + MARIO_WIDTH / 2;
	int marioTop = mario.Y - DRABINA_HEIGHT + 110;
	int marioBottom = mario.Y + DRABINA_HEIGHT - 60;

	int princessLeft = princess.X;
	int princessRight = princess.X + DRABINA_WIDTH;
	int princessTop = princess.Y;
	int princessBottom = princess.Y + DRABINA_HEIGHT;

	if (marioRight >= princessLeft && marioLeft <= princessRight &&
		marioBottom >= princessTop && marioTop <= princessBottom) {
		return true;
	}
	return false;
}

bool isGameOver(Heart heart) {
	for (int i = 0; i < 3; ++i) {
		if (heart.isActive[i]) {
			return false; 
		}
	}
	return true; 
}

void gameOver(Mario &mario, Barrel &barrel, Heart &heart, double &worldTime, bool &flag) {	// TODO dodanie logiki gdy koniec gry (wyswietlenie menu)
	mario.restart();
	barrel.restart();
	heart.restart();
	timeRestart(worldTime);
	resetFlag(flag);  // Dodaj reset flagi po restarcie gry
}




// 1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111

#ifdef __cplusplus
extern "C"
#endif

int main(int argc, char** argv) {
	int t1, t2, quit, frames, rc;
	double worldTime, fpsTimer, fps, distance;
	double delta;
	bool flag = true;  // TODO nie moze byc zmiennej globalnej


	//Dostepne mapy 1-3
	int wybranaMapa = 1;

	Drabiny mapa[3] = { Drabiny(1), Drabiny(2), Drabiny(3) };
	Mario mario = Mario();
	Barrel barrel = Barrel();
	Monkey monkey = Monkey();
	Princess princess = Princess();
	Heart heart = Heart();



	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* marioPNG;
	SDL_Surface* barrelPNG;
	SDL_Surface* monkeyPNG;
	SDL_Surface* princessPNG;
	SDL_Surface* heartPNG;
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

	SDL_SetWindowTitle(window, "Szablon do zdania drugiego 2017");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);


	// wy³¹czenie widocznoœci kursora myszy
	// SDL_ShowCursor(SDL_DISABLE);

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

	while (!quit) {	// 222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222
		t2 = SDL_GetTicks();

		// w tym momencie t2-t1 to czas w milisekundach,
		// jaki uplynal od ostatniego narysowania ekranu
		// delta to ten sam czas w sekundach
		delta = (t2 - t1) * 0.001;
		t1 = t2;

		worldTime += delta;


		// TODO zamien w funkcje
		if (barrel.X > 980 && barrel.Y > 680) {
			barrel.restart();
			resetFlag(flag);
		}
		else {
			if (barrel.moveRight) {
				barrel.X += barrel.SpeedMultiplier * delta;
			}
			else {
				barrel.X -= barrel.SpeedMultiplier * delta;
			}
			if (barrel.X > 1000) {
				barrel.Y += DRABINA_HEIGHT + 7;

				barrel.moveRight = false;

				barrel.X = 1000;
			}
			else if (barrel.X < 100) {
				barrel.Y += DRABINA_HEIGHT + 10;

				barrel.moveRight = true;

				barrel.X = 100;
			}
		}
		// TODO zamien w funkcje


		SDL_FillRect(screen, NULL, czarny);

		if (!kolizjaMarioDrabina(mario, mapa[wybranaMapa - 1]))
		{
			mario.ruchY(0.0);
		}

		if (kolizjaMarioPrincess(mario, princess))
		{
			mario.restart();
			barrel.restart();
		}

		if (kolizjaMarioBarrel(mario, barrel)) {
			if (deleteOnlyOneHeart(flag)) {
				for (int i = 2; i >= 0; --i) {
					if (heart.isActive[i]) {
						heart.isActive[i] = false;
						if (isGameOver(heart)) {
							gameOver(mario, barrel, heart, worldTime, flag);
						}
						break;
					}
				}
			}
		}

		



		mario.addX(delta);
		mario.addY(delta);

		DrawSurface(screen, marioPNG, mario.X, mario.Y);
		DrawSurface(screen, barrelPNG, barrel.X, barrel.Y);
		DrawSurface(screen, monkeyPNG, monkey.X, monkey.Y);
		DrawSurface(screen, princessPNG, princess.X, princess.Y);
		for (int i = 0; i < 3; ++i) {
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
		sprintf(text, "Szablon drugiego zadania, czas trwania = %.1lf s  %.0lf klatek / s", worldTime, fps);
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
		sprintf(text, "Esc - wyjscie, n - nowa gra, \032 - ruch w lewo, \033 - ruch w prawo");
		DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

		rysujPlansze(screen, mapa[wybranaMapa - 1], wybranaMapa);

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);

		//TODO: obsługa zmiany map przez zmienna wybranaMapa
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
				else if (event.key.keysym.sym == SDLK_LEFT)
				{
					if (!kolizjaMarioDrabina(mario, mapa[wybranaMapa - 1]))
						mario.ruchX(-1.0);  // Ustaw prędkość ruchu Mario w lewo
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					if (!kolizjaMarioDrabina(mario, mapa[wybranaMapa - 1]))
						mario.ruchX(1.0);  // Ustaw prędkość ruchu Mario w prawo
				}
				else if (event.key.keysym.sym == SDLK_UP)
				{
					if (kolizjaMarioDrabina(mario, mapa[wybranaMapa - 1]))
					{
						mario.ruchY(-1.0);
					}
				}
				else if (event.key.keysym.sym == SDLK_DOWN)
				{
					if (kolizjaMarioDrabina(mario, mapa[wybranaMapa - 1]))
					{
						mario.ruchY(1.0);
					}
				}
				else if (event.key.keysym.sym == SDLK_n)
				{
					mario.restart();
					barrel.restart();
					heart.restart();
					worldTime = 0;
				}
				else if (event.key.keysym.sym == SDLK_1) {
					wybranaMapa = 1;
					mapa[wybranaMapa - 1] = Drabiny(wybranaMapa);
				}
				else if (event.key.keysym.sym == SDLK_2) {
					wybranaMapa = 2;
					mapa[wybranaMapa - 1] = Drabiny(wybranaMapa);
				}
				else if (event.key.keysym.sym == SDLK_3) {
					wybranaMapa = 3;
					mapa[wybranaMapa - 1] = Drabiny(wybranaMapa);
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
