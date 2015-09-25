#include "uv.h"

char* REDtoSTR (double Valeur)
{
  char* Resultat;

  Resultat=(char*)malloc(5*sizeof(char));
  sprintf(Resultat, "%.3f", Valeur);

  if (strlen(Resultat)<5) return "";
  else return Resultat;
}
