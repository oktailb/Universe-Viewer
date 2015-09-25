#include "uv.h"

char* DEC_DEGtoSTR_DMS (double Valeur)
{
	double Temp;
  char* Resultat;
  char C='+';
  char DEGRE[4];
  char ARCMINUTE[3];
  char ARCSECONDE[3];

  Resultat=(char*)malloc(15*sizeof(char));
	Temp=Valeur;
	while (Temp>1) Temp=Temp-1;
  while (Temp<-1) Temp=Temp+1;

	sprintf(DEGRE, "%d", (int)(Valeur-Temp));
	Temp=Temp<0?Temp*(-1):Temp;
	sprintf(ARCMINUTE, "%d", (int)floor(Temp/0.016667));
	Temp=Temp-(atoi(ARCMINUTE)*(0.016667));
	sprintf(ARCSECONDE, "%d", (int)floor(Temp/0.000278));

	if (strlen(DEGRE)<3)
  {
  	DEGRE[2]=DEGRE[1];
    DEGRE[1]='0';
  }
    if (Valeur>0)
    {
    	DEGRE[2]=DEGRE[1];
      DEGRE[1]=DEGRE[0];
    	DEGRE[0]='+';
    }
    else DEGRE[0]='-';
  DEGRE[3]='\0';

  if (strlen(ARCMINUTE)<2)
  {
  	ARCMINUTE[1]=ARCMINUTE[0];
    ARCMINUTE[0]='0';
  }
  ARCMINUTE[2]='\0';

  if (strlen(ARCSECONDE)<2)
  {
  	ARCSECONDE[1]=ARCSECONDE[0];
    ARCSECONDE[0]='0';
  }
	ARCSECONDE[2]='\0';

  if (Valeur>=0) sprintf(Resultat, "%c%s %s %s", C,DEGRE,ARCMINUTE,ARCSECONDE);
  sprintf(Resultat, "%s %s %s", DEGRE, ARCMINUTE, ARCSECONDE);

	return Resultat;
}
