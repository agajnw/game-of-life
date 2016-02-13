#include <ncurses/form.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include <cstring>
#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <regex.h>
#include "osobniki.h"
#include "gra.h"
#include "gui.h"
using namespace std;



/** O ile ma byc odsunieta plansza od lewego brzegu ekranu? */
#define PLANSZA_OFFSET_X 3
/** O ile ma byc odsunieta plansza od gornego brzegu ekranu? */
#define PLANSZA_OFFSET_Y 4
/** Maksymalna wysoksoc planszy */
#define PLANSZA_MAX_H 25
/** Czy debugowanie jest wlaczone? */
#define DEBUG_ENABLED 0
/** Makro do debugowania */
#define DEBUG(...) \
            do { if (DEBUG_ENABLED) { fprintf(stderr, "DEBUG: [%s:%d] ", __FILE__, __LINE__); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); } } while (0)

/** Szerokosc planszy (domyslnie 80) */
extern unsigned short rozmiar;
/** Obecne polozenie kursora - X */
extern unsigned short current_x;
/** Obecne polozenie kursora - Y */
extern unsigned short current_y;
/** 0, jesli wylaczona jest automatyczna iteracja.
  * W przeciwnym wypadku czas w milisekudach, co jaki zmieniac stan komorek */
extern unsigned int autoiteracja;
/** Jesli liczba_krokow = 0, to nieskonczona_petla = 1 */
extern unsigned short nieskonczona_petla;

/** Numer kolejnej iteracji */
extern unsigned int iteracja;

/** Watek wykorzystywany na potrzeby autoiteracji */
extern pthread_t pwatek;

extern int liczbaA;
extern int liczbaB;
extern szachownica pole;
