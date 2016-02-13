#include "main.h"



/* Deaktywacja wszystkich komorek na planszy
*/

void szachownica::wyzeruj_plansze(std::vector< std::vector <istota> >& plansza)
{
	typedef std::vector <istota> t2;
	typedef std::vector< std::vector <istota> > t;
	t::iterator it;
	t2::iterator it2;
	for (it=plansza.begin();it!=plansza.end();++it) {
		for (it2=it->begin();it2!=it->end(); ++it2) {
			it2->martwy();
		}
	}

	iteracja = 0;
}

/** Generowanie losowego ulozenia aktywnych komorek na planszy
*/
void szachownica::losowe(std::vector< std::vector <istota> > &plansza)
{
	srand(time(NULL));
	for (int i=0;i<rozmiar;i++)
		for (int j=0;j<rozmiar;j++)
		{
			plansza[i][j].stan = rand() % 2;
			if (plansza [i][j].stan==0)
			{
				plansza[i][j].populacja = 0;
				plansza[i][j].rodz = 0;
				}
			else
			{
				plansza[i][j].populacja = rand() % 2 + 1;
				plansza[i][j].rodz = rand() % 3;
			}
		}
	iteracja = 0;
}

void szachownica::ruch(	std::vector< std::vector <istota> > &plansza)
{
	srand(time(NULL));
	unsigned short w, k;
    lSasiadow sasiedzi;
	for (w = 0; w < rozmiar; w++) {
		for (k = 0; k < rozmiar; k++) {
    		int puste[8], ile_pustych=0;
    		int lewa=-1,prawa=-1,dol=-1,gora=-1;
    		for (int i=0;i<8;i++)
    			puste[i] = 0;

			sasiedzi = policz_sasiadow(w, k, plansza);
//			cout << "";
			for (int i=0;i<8;i++)
			{
				if ((sasiedzi.sasiad[i])->stan == 0)
				{
					puste[ile_pustych] = i;
					ile_pustych++;
				}
			}

	if (ile_pustych!=0){
			int b = rand() % ile_pustych;
			int a = puste[b];
		/// Sasiedzi z lewej strony
	if (k > 0)
		lewa = k-1;

	// Sasiedzi z prawej
	if (k < rozmiar-1)
		prawa = k+1;


	// Sasiedzi u gory
	if (w > 0)
		gora = w-1;


	// Sasiedzi z dolu
	if (w < rozmiar-1)
		dol = w+1;
	if (gora!=-1 && lewa!=-1)
		if (a==0)
		{
			plansza[gora][lewa]=plansza[w][k];
			plansza[w][k].martwy();
		}
	if (lewa!=-1)
		if (a==1)
		{
			plansza[w][lewa]=plansza[w][k];
			plansza[w][k].martwy();
		}
	if (dol!=-1 && lewa!=-1)
		if (a==2)
		{
			plansza[dol][lewa]=plansza[w][k];
			plansza[w][k].martwy();
		}
	if (gora!=-1 && prawa!=-1)
		if (a==3)
		{
			plansza[gora][prawa]=plansza[w][k];
			plansza[w][k].martwy();
		}
	if (prawa!=-1)
		if (a==4)
		{
			plansza[w][prawa]=plansza[w][k];
			plansza[w][k].martwy();
		}
	if (dol!=-1 && prawa!=-1)
		if (a==5)
		{
			plansza[dol][prawa]=plansza[w][k];
			plansza[w][k].martwy();
		}
	if (gora!=-1)
		if (a==6)
		{
			plansza[gora][k]=plansza[w][k];
			plansza[w][k].martwy();
		}
	if (dol!=-1)
		if (a==7)
		{
			plansza[dol][k]=plansza[w][k];
			plansza[w][k].martwy();
		}
	}
		}
	}

}


/** Zmiana stanu komorek w zaleznosci od liczby sasiadow, zgodnie z zasadami Gry w zycie
*/
lSasiadow szachownica::policz_sasiadow(unsigned short wiersz, unsigned short kolumna, std::vector< std::vector <istota> > &plansza)
{
	lSasiadow sasiedzi;
	// Tworze pusty obiekt klasy istota, uzywany wtedy, gdy sasiednie pole jest martwe
	istota pusta;
	pusta.stan=0;
	pusta.populacja=0;
	pusta.rodz=0;
	int lewa = -1, prawa = -1, gora = -1, dol = -1;

	// Sasiedzi z lewej strony
	if (kolumna > 0)
		lewa = kolumna-1;

	// Sasiedzi z prawej
	if (kolumna < rozmiar-1)
		prawa = kolumna+1;


	// Sasiedzi u gory
	if (wiersz > 0)
		gora = wiersz-1;


	// Sasiedzi z dolu
	if (wiersz < rozmiar-1)
		dol = wiersz+1;


	// Lewy górny róg
	if (gora!=-1 && lewa!=-1){
	              sasiedzi.sasiad[0] = &(plansza[gora][lewa]);
               }
               else sasiedzi.sasiad[0] = &pusta;

	// Lewa strona komorki
	if (lewa!=-1){
	               sasiedzi.sasiad[1] = &(plansza[wiersz][lewa]);
                }
            else sasiedzi.sasiad[1] =  &pusta;

	// Lewy dolny rog
	if (dol!=-1 && lewa!=-1){
	            sasiedzi.sasiad[2] = &(plansza[dol][lewa]);
             }
                         else sasiedzi.sasiad[2] =  &pusta;

	// Prawy gorny rog
	if (gora!=-1 && prawa!=-1){
	             sasiedzi.sasiad[3] = &(plansza[gora][prawa]);
              }
                          else sasiedzi.sasiad[3] =  &pusta;

	// Prawa strona komorki
	if (prawa!=-1)
	               sasiedzi.sasiad[4] = &(plansza[wiersz][prawa]);
	                        else sasiedzi.sasiad[4] =  &pusta;

	// Prawy dolny rog
	if (dol!=-1 && prawa!=-1){
	            sasiedzi.sasiad[5] = &(plansza[dol][prawa]);
                }
                        else sasiedzi.sasiad[5] =  &pusta;

	// Sasiad nad komorka
	if (gora!=-1){
	              sasiedzi.sasiad[6] = &(plansza[gora][kolumna]);
               }
                        else sasiedzi.sasiad[6] =  &pusta;

	// Sasiad pod komorka
	if (dol!=-1) {
                  sasiedzi.sasiad[7] = &(plansza[dol][kolumna]);
                  }
                            else sasiedzi.sasiad[7] =  &pusta;
	sasiedzi.licz();
	return sasiedzi;
}


// Zmiana stanu komorek w zaleznosci od liczby sasiadow, zgodnie z zasadami Gry w zycie
void szachownica::zmien_stan_komorek(std::vector< std::vector <istota> > &plansza)
{
	unsigned short w, k;
    lSasiadow sasiedzi;
	for (w = 0; w < rozmiar; w++) {
		for (k = 0; k < rozmiar; k++) {

			sasiedzi = policz_sasiadow(w, k, plansza);

	//ZASADY
	//Populacje: A, B
	//Rodzaj: dzieci, dorosli, starsi
	//Stan: komorka zywa lub martwa zalezy od stanow jej 8 sasiadow (pol, x - os A, y - os B)
	  // 2 - stan posredni, zmiana z 1 na 0
	  // 3 - stan posredni, zmiana z 0 na 1 na populacje A
	  // 4 - stan posredni, zmiana z 0 na 1 na populacje B

	// DLA OSOBNIKOW A

	// Jesli osobnik A lub B  jest w sasiedztwie x==0, y==0, umiera
     	 	if (plansza[w][k].stan==1 && sasiedzi.Aall==0 && sasiedzi.Ball==0)
	  		{
				plansza[w][k].stan=2;
			}



	//1. Na 8 pol: x osobnikow A(rodzaj obojetny), y(>x) osobnikow B - os A umiera, osobniki B
	//   starzej¹ siê (starszy pozostaje taki sam)
     		if ((plansza[w][k].stan==1 || plansza[w][k].stan==3) && plansza[w][k].populacja==1 && sasiedzi.Ball>0 && sasiedzi.Ball>sasiedzi.Aall)
	 		{
          		plansza[w][k].stan=2;
          		for (int i=0;i<8;i++)
          		{
              		if (((sasiedzi.sasiad[i])->populacja)==2)
                 		(sasiedzi.sasiad[i])->starzenie();
          		}
			}

     		if ((plansza[w][k].stan==1 || plansza[w][k].stan==3) && plansza[w][k].populacja==2 && sasiedzi.Aall>0 && sasiedzi.Aall>sasiedzi.Ball)
	 		{
          		plansza[w][k].stan=2;
          		for (int i=0;i<8;i++)
          		{
              		if (((sasiedzi.sasiad[i])->populacja)==1)
                 	(sasiedzi.sasiad[i])->starzenie();
          		}
			}




	//2. Jesli x==y, to decyduje rodzaj(najsilniejszy starszy, pozniej dorosly, dziecko)
	//3. Jesli rodzaj jest ten sam, oba przezyja
	if (plansza[w][k].populacja==1){

     		if ((plansza[w][k].stan==1 || plansza[w][k].stan==3) && sasiedzi.Ball>0 && sasiedzi.Ball==sasiedzi.Aall)
		 	{
				if (sasiedzi.Bstarszy>sasiedzi.Astarszy)
				{
					plansza[w][k].stan=2;
          			for (int i=0;i<8;i++)
          			{
              			if (((sasiedzi.sasiad[i])->populacja)==2 && (sasiedzi.sasiad[i])->stan==1)
                 		sasiedzi.sasiad[i]->starzenie();
          			}
				}
				else if (sasiedzi.Bstarszy==sasiedzi.Astarszy)
			 	if (sasiedzi.Bdorosly>sasiedzi.Adorosly)
			 	{
					plansza[w][k].stan=2;
          			for (int i=0;i<8;i++)
          			{
              			if (((sasiedzi.sasiad[i])->populacja)==2 && (sasiedzi.sasiad[i])->stan==1)
                 		(sasiedzi.sasiad[i])->starzenie();
          			}
				}

			}

	}

	if (plansza[w][k].populacja==2){

     		if ((plansza[w][k].stan==1 || plansza[w][k].stan==3) && sasiedzi.Aall>0 && sasiedzi.Ball==sasiedzi.Aall)
		 	{
				if (sasiedzi.Bstarszy<sasiedzi.Astarszy)
				{
					plansza[w][k].stan=2;
          			for (int i=0;i<8;i++)
          			{
              			if (((sasiedzi.sasiad[i])->populacja)==2 && (sasiedzi.sasiad[i])->stan==1)
                 		sasiedzi.sasiad[i]->starzenie();
          			}
				}
				else if (sasiedzi.Bstarszy==sasiedzi.Astarszy)
			 	if (sasiedzi.Bdorosly<sasiedzi.Adorosly)
			 	{
					plansza[w][k].stan=2;
          			for (int i=0;i<8;i++)
          			{
              			if (((sasiedzi.sasiad[i])->populacja)==2 && (sasiedzi.sasiad[i])->stan==1)
                 		(sasiedzi.sasiad[i])->starzenie();
          			}
				}

			}

			}

	//5. Jesli martwe pole jest w sasiedztwie x os A (x>4) i y=0, ozywa os A (i jest
	//   najmlodszego rodzaju)
	//5. Jesli martwe pole jest w sasiedztwie x os A (x=0) i y os B (y>4), ozywa os B (i jest
	//   najmlodszego rodzaju)
	//6. Martwe pole w sasiedztwie <4 osobnikow jednej populacji pozostaje martwe

			if ((plansza[w][k].stan==0 || plansza[w][k].stan==2) && sasiedzi.Aall>4 && sasiedzi.Ball==0)
			{
				plansza[w][k].stan=3;
			}

			if ((plansza[w][k].stan==0 || plansza[w][k].stan==2) && sasiedzi.Aall==0 && sasiedzi.Ball>4)
			{
				plansza[w][k].stan=4;
			}

	//8. Martwe pole w sasiedztwie x==y==4 osobnikow ozywa jako osobnik populacji, w ktorej bylo
	//   najwiecej najstarszych (jesli po rowno, pozostaje martwe)

     		if ((plansza[w][k].stan==0 || plansza[w][k].stan==2) && sasiedzi.Ball==4 && sasiedzi.Ball==sasiedzi.Aall)
	 		{
				if (sasiedzi.Bstarszy>sasiedzi.Astarszy)
				{
					plansza[w][k].stan=4;
				}
			else if (sasiedzi.Astarszy>sasiedzi.Bstarszy)
			{
				plansza[w][k].stan=3;
			}
			else if (sasiedzi.Bstarszy==sasiedzi.Astarszy)
			 if (sasiedzi.Bdorosly>sasiedzi.Adorosly)
			 	{
					plansza[w][k].stan=4;
				}
			 if (sasiedzi.Bdorosly<sasiedzi.Adorosly)
			 	{
					plansza[w][k].stan=3;
				}


			}

	//9. Jesli osobnik A jest w sasiedztwie x>4 i y==0, i wsrod x os sa starsi, umiera;
	//   jesli nie ma, pozostaje zywy i starzeje siê (starszy pozostaje taki sam)
	//9. Jesli osobnik B jest w sasiedztwie y>4 i x==0, i wsrod y os sa starsi, umiera;
	//   jesli nie ma, pozostaje zywy i starzeje siê (starszy pozostaje taki sam)

			if(plansza[w][k].populacja==1 && (plansza[w][k].stan==1 || plansza[w][k].stan==3) && sasiedzi.Aall>4 && sasiedzi.Ball==0)
			if (sasiedzi.Astarszy>0)
			{
				plansza[w][k].stan=2;
			}
			else plansza[w][k].starzenie();

			if(plansza[w][k].populacja==2 && (plansza[w][k].stan==1 || plansza[w][k].stan==3) && sasiedzi.Ball>4 && sasiedzi.Aall==0)
			if (sasiedzi.Bstarszy>0)
			{
				plansza[w][k].stan=2;

			}
			else	plansza[w][k].starzenie();

	/* Po dokladnym sprawdzeniu obecnego stanu planszy i przypisaniu wartosci tymczasowych
	   dopiero teraz mozemy ingerowac w glowna zawartosc komorek ustawiajac 0 i 1 */

		}
	}

	for (w = 0; w < rozmiar; w++) {
		for (k = 0; k < rozmiar; k++) {
			switch (plansza[w][k].stan) {
				case 2:
					plansza[w][k].martwy();
					break;
				case 3:
					plansza[w][k].zywy(1);
					break;
				case 4:
					plansza[w][k].zywy(2);
					break;
				default:
					break;
				}
			}
		}
	iteracja++;
	ruch(plansza);
}



/** Funkcja wykonywana w osobnym watku, odpowiedzialna za automatyczna zmiane stanow automatu w podanych odstepach czasu
 */
void* watek_autoiteracja(void *arg)
{
	std::vector< std::vector <istota> > &plansza = *((std::vector< std::vector <istota> >*)arg);
	
	do
	{
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, 0);
		DEBUG("zmien_stan_komorek()");
		pole.zmien_stan_komorek(plansza);
		DEBUG("rysuj_plansze()");
		rysuj_plansze(plansza);
		DEBUG("rysuj_pasek()");
		rysuj_pasek();
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, 0);
		usleep(autoiteracja*1000);
	}
	while ((liczbaA!=0) && (liczbaB!=0));
	autoiteracja = 0;
	if (liczbaA==0) komunikat2("Dominacje osiagnela populacja B.");
	else if (liczbaB==0) komunikat2("Dominacje osiagnela populacja A."); 
	DEBUG("rysuj_pasek()");
	rysuj_pasek();
	
	return NULL; 
}
