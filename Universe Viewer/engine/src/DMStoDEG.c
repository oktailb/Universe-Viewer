#include "uv.h"

double DMStoDEG (char* Chaine)
{
  int moins=0;
  double Resultat;
  char DEGRE[4];
  char ARCMINUTE[3];
  char ARCSECONDE[3];

  DEGRE[0]=Chaine[0];
  DEGRE[1]=Chaine[1];
  DEGRE[2]=Chaine[2];
  DEGRE[3]='\0';

	ARCMINUTE[0]=Chaine[4];
  ARCMINUTE[1]=Chaine[5];
	ARCMINUTE[2]='\0';

  ARCSECONDE[0]=Chaine[7];
  ARCSECONDE[1]=Chaine[8];
	ARCSECONDE[2]='\0';

	if (DEGRE[0]=='-') moins=1;

	Resultat=abs(atoi(DEGRE)) +
 					 atoi(ARCMINUTE)*0.016667 +
    			 atoi(ARCSECONDE)*0.000278;
	if (moins==1) Resultat=(-1)*Resultat;

	return Resultat;
}
