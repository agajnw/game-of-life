#ifndef GRAW2_H
#define GRAW2_H

#include "osobniki.h"

class szachownica
{
public:
    int rozmiar;
    void wyzeruj_plansze(std::vector< std::vector <istota> >&);
    void losowe( std::vector< std::vector <istota> >&);
    lSasiadow policz_sasiadow(unsigned short, unsigned short, std::vector< std::vector <istota> > &);
    void zmien_stan_komorek(std::vector< std::vector <istota> >&);
    void wyswietl(std::vector< std::vector <istota> >&);
    void ruch(std::vector< std::vector <istota> > &plansza);
    szachownica operator-(std::vector< std::vector <istota> >& plansza);
};

void* watek_autoiteracja(void *arg);

#endif
