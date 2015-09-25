#include "uv.h"

char* MAGtoSTR (double Valeur)
{
  char* Resultat;

  Resultat=(char*)malloc(5*sizeof(char));
  sprintf(Resultat, "%.2f", Valeur);

  if (strlen(Resultat)<5) return "";
  else return Resultat;
}
