#include "uv.h"

double HMStoDEG (char* TAB)
{
	char HEURE [3];
	char MINUTE [3];
	char SECONDE [5];
	double Degres;

	HEURE[0]=TAB[0];
	HEURE[1]=TAB[1];
	HEURE[2]='\0';

	MINUTE[0]=TAB[3];
	MINUTE[1]=TAB[4];
	MINUTE[2]='\0';

	SECONDE[0]=TAB[6];
	SECONDE[1]=TAB[7];
	SECONDE[2]=TAB[8];
	SECONDE[3]=TAB[9];
	SECONDE[4]='\0';

	Degres=(strtod(HEURE, NULL)*15)+
         (strtod(MINUTE, NULL)*0.25)+
         (strtod(SECONDE, NULL)*(0.25/60));
	return Degres;
}
