#include "uv.h"

void write_xml_quasar (Environnement *env, Quasar* Q, char* NomFichier)
{
  int i=0;
  FILE* Fichier;
  
  Fichier = fopen(NomFichier, "w+");
  if (Fichier)
    {
      if (Q)
	{
	  ENTETE(Fichier, env->data_size);
	  for (i=0; i<env->data_size; i++)
	    {
	      fprintf(Fichier, "<TR><TD>%s</TD>", ASC_DEGtoSTR_DEG(Q[i].ascension));
	      fprintf(Fichier, "<TD>%s</TD>", DEC_DEGtoSTR_DEG(Q[i].declination));
	      fprintf(Fichier, "<TD>%s</TD>", ASC_DEGtoSTR_HMS (Q[i].ascension));
	      fprintf(Fichier, "<TD>%s</TD>", DEC_DEGtoSTR_DMS(Q[i].declination));
	      fprintf(Fichier, "<TD>%s</TD>", REDtoSTR(Q[i].redshift));
	      fprintf(Fichier, "<TD>%s</TD>", MAGtoSTR(Q[i].magnitude));
	      fprintf(Fichier, "<TD>%d</TD></TR>\n", i+1);
	    }
	  CONCLUSION (Fichier, env->data_size);
	}
      fclose(Fichier);
    }
  else printf("Can not create file %s ", NomFichier);
}

