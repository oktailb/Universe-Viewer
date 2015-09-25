#include "uv.h"

int get_xml_nb_quasar (Environnement *env, char* NomFichier)
{
    int NBE=0;
    FILE* FD;
    char* RES;
    char LIGNE[255];

    env = env;
    FD = fopen(NomFichier, "r");
    if (!FD) return (-1);

    while(!feof(FD))
    {
	    fgets(LIGNE, 255, FD);
    	    if ((RES = strstr(LIGNE, "<TR>")) != NULL)
            {
		NBE++;
	    }
    }

    fclose(FD);
    return NBE;
}

