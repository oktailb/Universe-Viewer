#include "uv.h"

char* ASC_DEGtoSTR_HMS (double Valeur)
{
  float Seconde;
  int Minute;
  int Heure;
  char* Resultat;
  char SECONDE[5];
  char MINUTE[3];
  char HEURE[3];
  Resultat=(char*)malloc(10*sizeof(char));


  Heure=(Valeur/(15));
  Valeur=Valeur-(double)(Heure*15);

  Minute=(Valeur/(0.25));
  Valeur=Valeur-(double)(Minute*0.25);

  Seconde=(Valeur/(0.25/60));

  sprintf(HEURE, "%d", Heure);
  if (strlen(HEURE)<2)
  {
    HEURE[1]=HEURE[0];
    HEURE[0]='0';
  }
	HEURE[2]='\0';

  sprintf(MINUTE, "%d", Minute);
  if (strlen(MINUTE)<2)
  {
    MINUTE[1]=MINUTE[0];
    MINUTE[0]='0';
  }
	MINUTE[2]='\0';

  sprintf(SECONDE, "%.1f", Seconde);
  if (strlen(SECONDE)<4)
  {
    SECONDE[3]=SECONDE[2];
    SECONDE[2]=SECONDE[1];
    SECONDE[1]=SECONDE[0];
    SECONDE[0]='0';
  }
	SECONDE[4]='\0';

	sprintf(Resultat, "%s %s %s", HEURE, MINUTE, SECONDE);

  return Resultat;
}
