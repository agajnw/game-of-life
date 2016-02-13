#include "main.h"

pthread_t pkomunikat_watek;
unsigned short pkomunikat_watek_running = 0;


/* Wydruk podanego tekstu na srodku podanego obszaru w danym oknie
*/
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	/* Jesli nie podano okna, to drukuj na glownym */
	if(win == NULL)
		win = stdscr;
	/* Domyslnie drukujemy w aktualnym polozeniu w oknie */
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

/*  Tworzy okno ncurses z obramowaniem
*/

WINDOW *stworz_okno(int width, int height, int startx, int starty, char* title)
{
	WINDOW *win;

	if (startx < 0)
		startx = (int)(COLS/2 - width/2);
	if (starty < 0)
		starty = (int)(LINES/2 - height/2);

	/* Stworz nowe okno */
	win = newwin(height, width, starty, startx);
	keypad(win, TRUE);

	/* Obramowanie okna */
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');

	/* Tlo okna */
	wbkgd(win, COLOR_PAIR(FORM_CP));

	/* Tytul */
	print_in_middle(win, 1, 2, width-2, title, COLOR_PAIR(FORM_CP));

	/* Linia pod tytulem */
	mvwprintw(win, 2, 0, "+");
	whline(win, '-', width-2);
	mvwprintw(win, 2, width-1, "+");

	/* Przesun kursor w miejsce gotowe do pisania */
	wmove(win, 4, 3);

	/* Pokaz okno */
	wrefresh(win);

	return win;
}


/*  Wyswietla okno sluzace do podania rozmiaru planszy
*/

void rozmiar_planszy_form()
{
	int ch;
	unsigned short akt_pole = 1;
	unsigned short pole1_l = 0;
	char rozm[3];
	unsigned short nieskonczona_petla = 1;

	DEBUG("[rozmiar_planszy_form] start...");
	rozm[0] = '\0';

    WINDOW *rozmiarp_okno;
	rozmiarp_okno = stworz_okno(40, 14, -1, -1, "Rozmiar planszy [NxN]");

	mvwprintw(rozmiarp_okno, 4, 3, "Rozmiar:");
	mvwprintw(rozmiarp_okno, 7, 3, "Nacisnij F1, aby zaakceptowac");
	mvwprintw(rozmiarp_okno, 8, 3, "Nacisnij F10, aby wyjsc z programu");
	wattron(rozmiarp_okno, COLOR_PAIR(FIELD_CP));
	mvwprintw(rozmiarp_okno, 4, 15, "          ");
	wmove(rozmiarp_okno, 4, 15);
	wrefresh(rozmiarp_okno);
	while(nieskonczona_petla)
	{
		ch = getch();
		DEBUG("Nacisnieto klawisz: %d", ch);
		switch(ch) {
			case KEY_F(1):
			case 10: // enter
				if (!pole1_l) {
					wattroff(rozmiarp_okno, COLOR_PAIR(FIELD_CP));
					mvwprintw(rozmiarp_okno, 10, 3, "Podaj wymiar!    ");
					wmove(rozmiarp_okno, 4, 15);
					akt_pole = 1;
					wattron(rozmiarp_okno, COLOR_PAIR(FIELD_CP));
					wrefresh(rozmiarp_okno);
				} else {
					rozm[pole1_l] = '\0';
					rozmiar = (unsigned short)atoi(rozm);
					rozmiar = (unsigned short)atoi(rozm);
					if (rozmiar > PLANSZA_MAX_H) {
						wattroff(rozmiarp_okno, COLOR_PAIR(FIELD_CP));
						mvwprintw(rozmiarp_okno, 10, 3, "Rozm. jest >%d !    ",PLANSZA_MAX_H);
						wmove(rozmiarp_okno, 4, 15+pole1_l);
						akt_pole = 1;
						wattron(rozmiarp_okno, COLOR_PAIR(FIELD_CP));
						wrefresh(rozmiarp_okno);
					} else if (rozmiar < 2) {
						wattroff(rozmiarp_okno, COLOR_PAIR(FIELD_CP));
						mvwprintw(rozmiarp_okno, 10, 3, "Rozm. jest < 2 !    ");
						wmove(rozmiarp_okno, 4, 15+pole1_l);
						akt_pole = 1;
						wattron(rozmiarp_okno, COLOR_PAIR(FIELD_CP));
						wrefresh(rozmiarp_okno);
					} else if (rozmiar > COLS - 2*PLANSZA_OFFSET_X) {
						wattroff(rozmiarp_okno, COLOR_PAIR(FIELD_CP));
						mvwprintw(rozmiarp_okno, 10, 3, "Max rozm. (okna) = %d    ", COLS - 2*PLANSZA_OFFSET_X);
						wmove(rozmiarp_okno, 4, 15+pole1_l);
						akt_pole = 1;
						wattron(rozmiarp_okno, COLOR_PAIR(FIELD_CP));
						wrefresh(rozmiarp_okno);
					} else {
						// Jesli wszystkie wartosci sa w porzadku i nie wykraczaja poza okno, mozemy zakonczyc
						nieskonczona_petla = 0;
					}
				}
				break;
			case KEY_F(10):
				DEBUG("endwin()");
				endwin();
				exit(0);
			case KEY_DOWN:
			case KEY_UP:
			case KEY_BACKSPACE:
			case 127: // Inny kod backspace 
				if (akt_pole == 1) {
					if (pole1_l > 0) {
						pole1_l--;
						rozm[pole1_l] = '\0';
						mvwprintw(rozmiarp_okno, 4, 15+pole1_l, " ");
						wmove(rozmiarp_okno, 4, 15+pole1_l);
						wrefresh(rozmiarp_okno);
					}
				}
				break;
			default:
				if (ch < 48 || ch > 57) break; // Akceptujemy tylko cyfry
				if (akt_pole == 1 && pole1_l == 2 )
						break; // Max to dwie cyfry
				wprintw(rozmiarp_okno, "%c", ch);
				wrefresh(rozmiarp_okno);
				if (akt_pole == 1) {
					rozm[pole1_l] = ch;
					pole1_l++;
				}
				break;
		}
	} /* while */

	// Pozbywamy sie okna
	wattroff(rozmiarp_okno, COLOR_PAIR(FIELD_CP));
	wborder(rozmiarp_okno, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wattron(rozmiarp_okno, COLOR_PAIR(5));
	wbkgd(rozmiarp_okno, COLOR_PAIR(5));
	redrawwin(rozmiarp_okno);
	wrefresh(rozmiarp_okno);
	delwin(rozmiarp_okno);

}

/* Wyswietla okno sluzace do podania rozmiaru planszy
*/
void autoiteracja_form()
{
	int ch;
	unsigned short akt_pole = 1;
	unsigned short pole1_l = 0;
	char interwal[5], iteracje[3];
	unsigned short nieskonczona_petla = 1;

	DEBUG("[autoiteracja_form] start...");
	interwal[0] = '\0'; iteracje[0] = '\0';

    WINDOW *autoit_form;
	autoit_form = stworz_okno(44, 14, -1, -1, "Interwal");

	mvwprintw(autoit_form, 4, 3, "Czas(ms):");
	mvwprintw(autoit_form, 6, 3, "Nacisnij F1, aby zaakceptowac");
	mvwprintw(autoit_form, 7, 3, "Nacisnij F10, aby wyjsc z programu");
	wattron(autoit_form, COLOR_PAIR(FIELD_CP));
	mvwprintw(autoit_form, 4, 15, "          ");
	wmove(autoit_form, 4, 15);
	wrefresh(autoit_form);

	while(nieskonczona_petla)
	{
		ch = getch();
		DEBUG("Nacisnieto klawisz: %d", ch);
		switch(ch) {
			case KEY_F(1):
			case 10: // enter
				if (!pole1_l) {
					wattroff(autoit_form, COLOR_PAIR(FIELD_CP));
					mvwprintw(autoit_form, 8, 3, "Podaj interwal!     ");
					wmove(autoit_form, 4, 15);
					akt_pole = 1;
					wattron(autoit_form, COLOR_PAIR(FIELD_CP));
					wrefresh(autoit_form);
				} else {
					interwal[pole1_l] = '\0';
					autoiteracja = (unsigned int)atoi(interwal);
					if (autoiteracja < 100) {
						wattroff(autoit_form, COLOR_PAIR(FIELD_CP));
						mvwprintw(autoit_form, 8, 3, "Interwal < 100ms !  ");
						wmove(autoit_form, 4, 15+pole1_l);
						akt_pole = 1;
						wattron(autoit_form, COLOR_PAIR(FIELD_CP));
						wrefresh(autoit_form);
					} else {
						// Jesli wszystkie wartosci sa w porzadku i nie wykraczaja poza okno, mozemy zakonczyc
						nieskonczona_petla = 0;
					}
				}
				break;
			case KEY_F(10):
				DEBUG("endwin()");
				endwin();
				exit(0);
				break;
			case KEY_BACKSPACE:
			case 127: // Inny kod backspace 
				if (akt_pole == 1) {
					if (pole1_l > 0) {
						pole1_l--;
						interwal[pole1_l] = '\0';
						mvwprintw(autoit_form, 4, 15+pole1_l, " ");
						wmove(autoit_form, 4, 15+pole1_l);
						wrefresh(autoit_form);
					}
				} 
				break;
			default:
				if (ch < 48 || ch > 57) break; // Akceptujemy tylko cyfry
				if ( akt_pole == 1 && pole1_l == 4)
						break; 
				wprintw(autoit_form, "%c", ch);
				wrefresh(autoit_form);
				if (akt_pole == 1)
					interwal[pole1_l] = ch;
					pole1_l++;
				break;
		}
	} /* while */

	// Pozbywamy sie okna
	wattroff(autoit_form, COLOR_PAIR(FIELD_CP));
	wborder(autoit_form, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wattron(autoit_form, COLOR_PAIR(5));
	wbkgd(autoit_form, COLOR_PAIR(5));
	redrawwin(autoit_form);
	wrefresh(autoit_form);
	delwin(autoit_form);

}



/* Rysuje cala plansze na podstawie wartosci w tablicy @b plansza
*/
void rysuj_plansze(std::vector< std::vector <istota> >&plansza)
{
	DEBUG("[rysuj_plansze] start...");
	unsigned short w, k;
	liczbaA=0;
	liczbaB=0;	
	for (w = 0; w < rozmiar; w++) {
		DEBUG("[rysuj_plansze] --- wiersz %d ---", w);
		for (k = 0; k < rozmiar; k++) {
		DEBUG("[rysuj_plansze] plansza[%d][%d] = %d", w, k, plansza[w][k].stan);

			if (plansza[w][k].stan==1)
			{
			attron(COLOR_PAIR(plansza[w][k].populacja-1 ? KOMA_CP : KOMB_CP));
			mvprintw(PLANSZA_OFFSET_Y+w, PLANSZA_OFFSET_X+(2*k), "%d ", plansza[w][k].rodz);
			attroff(COLOR_PAIR(plansza[w][k].populacja-1 ? KOMA_CP : KOMB_CP));
			if (plansza[w][k].populacja==1) liczbaA++;
			if (plansza[w][k].populacja==2) liczbaB++;
			}
			else {
				attron(COLOR_PAIR(KOMN_CP));
				mvprintw(PLANSZA_OFFSET_Y+w, PLANSZA_OFFSET_X+(2*k), "%d ", plansza[w][k].stan);
				attroff(COLOR_PAIR(KOMN_CP)); 
				}

		}
	}
	kursor_na_miejsce();
	refresh();
}

/*  Rysuje gorny pasek menu
*/

void rysuj_pasek()
{
	DEBUG("[rysuj_pasek] start...");
	attron(COLOR_PAIR(FORM_CP));
	int i;
	for (i = 0; i < COLS; i++) {
		mvprintw(0, i, " ");
		mvprintw(1, i, " ");
		mvprintw(2, i, " ");
	}

	// F1
	attron(A_BOLD);
	mvprintw(1, 3, "F1");
	attroff(A_BOLD);
	mvprintw(1, 6, "- generuj");

	// F2
	attron(A_BOLD);
	mvprintw(1, 21, "F2");
	attroff(A_BOLD);
	mvprintw(1, 24, "- przejscie");
	
	// F3
	attron(A_BOLD);
	mvprintw(1, 42, "F3");
	attroff(A_BOLD);
	mvprintw(1, 46, "- autoiteracja");

	// F10
	attron(A_BOLD);
	mvprintw(1, 61, "F10");
	attroff(A_BOLD);
	mvprintw(1, 67, "- zakoncz");

	// ENTER
	attron(A_BOLD);
	mvprintw(1, 80, "ENTER");
	attroff(A_BOLD);
	mvprintw(1, 86, "- zmien stan komorki");


	attroff(COLOR_PAIR(FORM_CP));
	kursor_na_miejsce();
	refresh();
}

/** Przywraca kursor po kazdym rysowaniu na miejsce na planszy, na ktorym ostatnio zostawil go uzytkownik
*/

void kursor_na_miejsce()
{
	// Przesun kursor tam, gdzie byl
	move(PLANSZA_OFFSET_Y+current_y, PLANSZA_OFFSET_X+(2*current_x));
}


/*  Drukuje komunikat pod plansza na wzor funkcji printf().
*/

void komunikat(const char *fmt, ...) {
	va_list args;
    char str[8192];

    if (!fmt) {
        return;
    }

    va_start(args, fmt);
    vsnprintf(str, sizeof(str), fmt, args);
    va_end(args);

	unsigned int i, l = strlen(str);
	unsigned short linijka = 1;
	for (i = 0; i < l; i++) {
		// Jesli koniec obszaru okna, to trzeba przejsc linijke nizej...
		if (((i+1)%COLS) == 0)
			linijka++;

		/* Max 4-linijkowy komunikat lub nie wychodzacy poza ekran */
		if (linijka >= 4 || linijka > LINES)
			break;

		mvprintw(PLANSZA_OFFSET_Y+rozmiar+linijka, 1+((i+1)%COLS), "%c", str[i]);
	}
	l += 2;
	while (l < COLS) {
		mvprintw(PLANSZA_OFFSET_Y+rozmiar+linijka, l, " ");
		l++;
	}

	kursor_na_miejsce();
	refresh();

	/* Osobny watek usuwaa komunikat po 3 sekundach*/
	if (pkomunikat_watek_running) {
		pthread_cancel(pkomunikat_watek);
		pthread_join(pkomunikat_watek, 0);
	}
	pthread_create(&pkomunikat_watek, NULL, watek_komunikat_wyczysc, NULL);
}

/**  Drukuje komunikat pod plansza na wzor funkcji printf().
 *  Funkcja analogiczna do poprzedniej; komunikat nie znika
*/
void komunikat2(const char *fmt, ...) {
	va_list args;
    char str[8192];

    if (!fmt) {
        return;
    }

    va_start(args, fmt);
    vsnprintf(str, sizeof(str), fmt, args);
    va_end(args);

	unsigned int i, l = strlen(str);
	unsigned short linijka = 1;
	for (i = 0; i < l; i++) {
		// Jesli koniec obszaru okna, to trzeba przejsc linijke nizej...
		if (((i+1)%COLS) == 0)
			linijka++;

		/* Max 4-linijkowy komunikat lub nie wychodzacy poza ekran */
		if (linijka >= 4 || linijka > LINES)
			break;

		mvprintw(PLANSZA_OFFSET_Y+rozmiar+linijka, 1+((i+1)%COLS), "%c", str[i]);
	}
	l += 2;
	while (l < COLS) {
		mvprintw(PLANSZA_OFFSET_Y+rozmiar+linijka, l, " ");
		l++;
	}

	kursor_na_miejsce();
	refresh();
}

void* watek_komunikat_wyczysc(void* arg)
{
	char spacje[512];
	pkomunikat_watek_running = 1;
	usleep(3000000);
	komunikat("%s", spacje);
	pkomunikat_watek_running = 0;
	pthread_exit(NULL);
	return NULL;
}

void* watek_komunikat_wyczysc_bez_czekania(void* arg)
{
	char spacje[512];
	pkomunikat_watek_running = 1;
	komunikat("%s", spacje);
	pkomunikat_watek_running = 0;
	pthread_exit(NULL);
	return NULL;
}
