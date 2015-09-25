#include "uv.h"

char* ASC_DEGtoSTR_DEG (double Valeur)
{
  int i=0;
  int j=0;
  char* Resultat;
  char Temp[8];

  Resultat=(char*)malloc(8*sizeof(char));
  sprintf(Temp, "%.4f", Valeur);

  for (i=0; i<8; i++) Resultat[i]='0';
  for (i=(8-strlen(Temp)); i<8; i++)
    Resultat[i]=Temp[j++];

  return Resultat;
}
