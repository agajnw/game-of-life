#ifndef OSOBNIKI_H
#define OSOBNIKI_H

//ZASADY
//Populacje: A, B
//Rodzaj: dzieci, dorosli, starsi
//Stan: komorka zywa lub martwa zalezy od stanow jej 8 sasiadow (pol, x - os A, y - os B)
	  // 2 - stan posredni, zmiana z 1 na 0
	  // 3 - stan posredni, zmiana z 0 na 1 na populacje A
	  // 4 - stan posredni, zmiana z 0 na 1 na populacje B


// Jesli osobnik A lub B  jest w sasiedztwie x==0, y==0, umiera
//1. Na 8 pol: x osobnikow A(rodzaj obojetny), y(>x) osobnikow B - os A umiera, osobniki B
//   starzej¹ siê (starszy pozostaje taki sam)
//2. Jesli x==y, to decyduje rodzaj(najsilniejszy starszy, pozniej dorosly, dziecko)
//3. Jesli rodzaj jest ten sam, oba przezyja
//5. Jesli martwe pole jest w sasiedztwie x os A (x>4) i y=0, ozywa os A (i jest 
//   najmlodszego rodzaju)
//5. Jesli martwe pole jest w sasiedztwie x os A (x=0) i y os B (y>4), ozywa os B (i jest 
//   najmlodszego rodzaju)
//6. Martwe pole w sasiedztwie <4 osobnikow jednej populacji pozostaje martwe
//8. Martwe pole w sasiedztwie x==y==4 osobnikow ozywa jako osobnik populacji, w ktorej bylo 
//   najwiecej najstarszych (jesli po rowno, pozostaje martwe)
//9. Jesli osobnik A jest w sasiedztwie x>4 i y==0, i wsrod x os sa starsi, umiera;
//   jesli nie ma, pozostaje zywy i starzeje siê (starszy pozostaje taki sam)
//9. Jesli osobnik B jest w sasiedztwie y>4 i x==0, i wsrod y os sa starsi, umiera;
//   jesli nie ma, pozostaje zywy i starzeje siê (starszy pozostaje taki sam)




class osobnik
{
      public: 
      int stan; // 0 - martwa, 1 - ¿ywa
      osobnik (int a=0) : stan(a) {}
      void zywy(int a)
    	{
            stan=1;
        }
      void martwy()
        {
            stan=0;
        }

};

class istota : public osobnik
{

	public:
      int populacja; // 1 - populacja A, 2 - populacja B
      int rodz; // 0 - dziecko, 1 - dorosly, 2 - starszy
      void starzenie()
      {
           if (rodz!=2)
            rodz++;
      }
      istota(int a=0, int b=0, int c=0) : populacja(a), rodz(b) {}
      void zywy(int a)
    	{
            stan=1;
            rodz=0;
            populacja=a;
        }
      void martwy()
        {
            stan=0;
            populacja=0;
            rodz=0;
        }
};
 
 
class lSasiadow
{
      public:
      int Adziecko;
      int Adorosly;
      int Astarszy;
      int Bdziecko;
      int Bdorosly;
      int Bstarszy;
      int Aall;
      int Ball;
      istota *sasiad[8];
      void licz();
      lSasiadow (int A=0, int B=0, int C=0, int D=0, int E=0, int F=0, int G=0, int H=0) :      
                         Adziecko(A), Adorosly(B), Astarszy(C), 
                         Bdziecko(D), Bdorosly(E), Bstarszy(F),
                         Aall(G), Ball(H) {}
};


#endif
