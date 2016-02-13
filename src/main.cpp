#include "main.h"

unsigned short rozmiar = PLANSZA_MAX_H;

unsigned short current_x = 0;
unsigned short current_y = 0;
int liczbaA;
int liczbaB;
szachownica pole;

unsigned int autoiteracja = 0;
unsigned short nieskonczona_petla = 0;

unsigned int iteracja = 0;

pthread_t pwatek;


int main(int argc, char **argv)
{
    int ch;
    DEBUG("initscr()");
    initscr();


    if(has_colors() == FALSE)
    {
        endwin();
        printf("Twoj terminal nie obsluguje kolorow!\n");
        exit(1);
    }

    DEBUG("start_color()");
    start_color();

    DEBUG("noecho()");
    noecho();

    DEBUG("cbreak()");
    cbreak();

    /* Aktywacja F1, F2, itd... */
    DEBUG("keypad(stdscr, TRUE)");
    keypad(stdscr, TRUE);

    mousemask(ALL_MOUSE_EVENTS, NULL);

    DEBUG("Inicjalizacja kolorow...");
    init_pair(1, COLOR_BLACK, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_YELLOW);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_BLACK, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_CYAN);
    assume_default_colors(COLOR_WHITE,COLOR_BLACK);


    /* Alokacja pamieci dla tablicy */
    vector< vector <istota> > plansza;
    pole.rozmiar = rozmiar;
    iteracja = 0;
    plansza.resize(rozmiar);
    for (unsigned int i=0; i<plansza.size(); i++)
        plansza[i].resize(rozmiar);
    pole.wyzeruj_plansze(plansza);

    DEBUG("rozmiar_planszy_form()");
    rozmiar_planszy_form();

    DEBUG("rysuj_pasek()");
    rysuj_pasek();

    DEBUG("rysuj_plansze()");
    rysuj_plansze(plansza);

    while((ch = getch()) != KEY_F(10))
    {
        DEBUG("Nacisnieto klawisz: %d", ch);
        switch(ch)
        {
        case KEY_F(1):
            if (pkomunikat_watek_running)
            {
                pthread_cancel(pkomunikat_watek);
                pthread_join(pkomunikat_watek, 0);
            }
            pthread_create(&pkomunikat_watek, NULL, watek_komunikat_wyczysc_bez_czekania, NULL);
            if (autoiteracja > 0)
            {
                komunikat("Nie mozna wykonywac zadnych operacji gdy automatyczna symulacja jest wlaczona!");
                break;
            }
            DEBUG("plansza.wyzeruj_plansze()");
            pole.wyzeruj_plansze(plansza);
            DEBUG("plansza.losowe()");
            pole.losowe(plansza);
            DEBUG("plansza.rysuj_plansze()");
            rysuj_plansze(plansza);
            break;
        case KEY_F(2):
            if (autoiteracja > 0)
            {
                komunikat("Nie mozna wykonywac zadnych operacji gdy automatyczna symulacja jest wlaczona!");
                break;
            }
            DEBUG("zmien_stan_komorek()");
            pole.zmien_stan_komorek(plansza);
            DEBUG("rysuj_pasek()");
            rysuj_pasek();
            DEBUG("rysuj_plansze()");
            rysuj_plansze(plansza);
            if (liczbaA==0 && liczbaB!=0) komunikat2("Dominacje osiagnela populacja B.");
            else if (liczbaB==0 && liczbaA!=0) komunikat2("Dominacje osiagnela populacja A.");
            break;
        case KEY_F(3):
            if (autoiteracja > 0)
            {
                komunikat("Nie mozna wykonywac zadnych operacji gdy automatyczna symulacja jest wlaczona!");
                break;
            }
            if (autoiteracja == 0)
            {
                DEBUG("autoiteracja_form()");
                autoiteracja_form();
                DEBUG("rysuj_pasek()");
                rysuj_pasek();
                DEBUG("rysuj_plansze()");
                rysuj_plansze(plansza);

                pthread_create(&pwatek, NULL, watek_autoiteracja, (void*)&plansza);
            }
            else
            {
                pthread_cancel(pwatek);
                pthread_join(pwatek, 0);

                autoiteracja = 0;
                DEBUG("rysuj_pasek()");
                rysuj_pasek();
                DEBUG("rysuj_plansze()");
                rysuj_plansze(plansza);
            }
            break;

        case KEY_LEFT:
            if (autoiteracja > 0)
            {
                komunikat("Nie mozna wykonywac zadnych operacji gdy automatyczna symulacja jest wlaczona!");
                break;
            }
            if (current_x > 0)
            {
                current_x--;
                DEBUG("rysuj_plansze");
                rysuj_plansze(plansza);
            }
            break;

        case KEY_RIGHT:
            if (autoiteracja > 0)
            {
                komunikat("Nie mozna wykonywac zadnych operacji gdy automatyczna symulacja jest wlaczona!");
                break;
            }
            if (current_x < rozmiar-1)
            {
                current_x++;
                DEBUG("rysuj_plansze");
                rysuj_plansze(plansza);
            }
            break;

        case KEY_UP:
            if (autoiteracja > 0)
            {
                komunikat("Nie mozna wykonywac zadnych operacji gdy automatyczna symulacja jest wlaczona!");
                break;
            }
            if (current_y > 0)
            {
                current_y--;
                DEBUG("rysuj_plansze");
                rysuj_plansze(plansza);
            }
            break;

        case KEY_DOWN:
            if (autoiteracja > 0)
            {
                komunikat("Nie mozna wykonywac zadnych operacji gdy automatyczna symulacja jest wlaczona!");
                break;
            }
            if (current_y < rozmiar-1)
            {
                current_y++;
                DEBUG("rysuj_plansze");
                rysuj_plansze(plansza);
            }
            break;

        case 10: // ENTER
            if (autoiteracja > 0)
            {
                komunikat("Nie mozna wykonywac zadnych operacji gdy automatyczna symulacja jest wlaczona!");
                break;
            }
            srand(time(NULL));
            if (plansza[current_y][current_x].stan==0)
            {
                plansza[current_y][current_x].rodz = rand() % 3 ;
                plansza[current_y][current_x].populacja=1+ rand() % 2;
            }
            else
            {
                plansza[current_y][current_x].rodz = 0;
                plansza[current_y][current_x].populacja=0;
            }
            plansza[current_y][current_x].stan = !plansza[current_y][current_x].stan;

            DEBUG("rysuj_plansze");
            rysuj_plansze(plansza);
            break;

        }
    }

    DEBUG("endwin()");
    endwin();
    return 0;
}
