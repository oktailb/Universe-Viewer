#include "uv.h"

char* DEC_DEGtoSTR_DEG (double Valeur)
{
  char* Resultat;
  Resultat=(char*)malloc(10*sizeof(char));
  if (Valeur>0) sprintf(Resultat, "+%.4f", Valeur);
	else sprintf(Resultat, "%.4f", Valeur);

  return Resultat;
}

