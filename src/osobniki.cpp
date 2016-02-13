#include "osobniki.h"


void lSasiadow::licz()
{
    for (int i=0; i<8; i++)
    {
        if((sasiad[i])->populacja==0) continue;
        if (((sasiad[i])->populacja)==1)
            if (((sasiad[i])->stan)==1 || ((sasiad[i])->stan)==3)
            {
                Aall++;
                switch ((sasiad[i])->rodz)
                {
                case 0:
                    Adziecko++;
                    break;
                case 1:
                    Adorosly++;
                    break;
                case 2:
                    Astarszy++;
                    break;
                }
            }
        if (((sasiad[i])->populacja)==2)
            if (((sasiad[i])->stan)==1 || ((sasiad[i])->stan)==3)
            {
                Ball++;
                switch ((sasiad[i])->rodz)
                {
                case 0:
                    Bdziecko++;
                    break;
                case 1:
                    Bdorosly++;
                    break;
                case 2:
                    Bstarszy++;
                    break;
                }
            }
    }
}

