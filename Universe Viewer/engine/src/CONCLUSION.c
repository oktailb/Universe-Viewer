#include "uv.h"

void CONCLUSION (FILE* Fichier, int NBDonnees)
{
	fprintf(Fichier, "</TABLEDATA>\n");
	fprintf(Fichier, "</DATA>\n");
	fprintf(Fichier, "<!-- Result Truncated to %d -->\n", NBDonnees);
	fprintf(Fichier, "  </TABLE>\n");
	fprintf(Fichier, "</RESOURCE>\n");
	fprintf(Fichier, "</VOTABLE>\n");
}

