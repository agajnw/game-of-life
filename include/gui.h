
/** Numer zdefiniowanej w @b main() pary kolorow uzywanej do oznaczania zywych komorek populacji A */
#define KOMA_CP 3
/** Numer zdefiniowanej w @b main() pary kolorow uzywanej do oznaczania zywych komore populacji B */
#define KOMB_CP 6
/** Numer zdefiniowanej w @b main() pary kolorow uzywanej do oznaczania martwych komorek */
#define KOMN_CP 2
/** Numer zdefiniowanej w @b main() pary kolorow uzywanej do okien */
#define FORM_CP 1
/** Numer zdefiniowanej w @b main() pary kolorow uzywanej do pol tekstowych */
#define FIELD_CP 4

/** Watek, ktory czeka 3 sekundy i czysci wyswietlony komunikat */
extern pthread_t pkomunikat_watek;
/** Czy watek komunikatu jest uruchomiony? */
extern unsigned short pkomunikat_watek_running;

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
WINDOW *stworz_okno(int width, int height, int startx, int starty, char* title);
void rozmiar_planszy_form();
void autoiteracja_form();
void rysuj_plansze(std::vector< std::vector <istota> >&);
void rysuj_pasek();
void kursor_na_miejsce();

void komunikat(const char*, ...);
void komunikat2(const char*, ...);
void* watek_komunikat_wyczysc(void*);
void* watek_komunikat_wyczysc_bez_czekania(void*);

