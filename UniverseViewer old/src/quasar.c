
#include <X11/Xatom.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
/*
#include <Xm/Xm.h>
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "vector.h"
#include "isotrop.h"
#include "space.h"
#include "projection.h"
#include "distance.h"
#include "quasar.h"
#include "calldraw.h"
#include <interface.h>
#include <callbacks.h>

#define  PI 3.14159265398
extern Vector *quasar_pos;
extern Friedman friedman;
extern int data_lenght;
extern int data_size;
extern char *data_filename;
extern double distance_max;
extern double abacus_max;
extern int is_viewed;
extern int bounced;
extern Vector direction1, direction2, direction3, direction4;
extern int vue_is_displayed[6];
extern double ascension,declination,beta;
char buff[256];
double graphTx_max,graphTy_max;
int radians = 1;

// ========================================================================== //
// Conversion des donn�s en degr� vers radians et inversement
// ========================================================================== //
// ----------------------------------------------------------- //
// Unit�valeure d'entr� : Degr�
// Type valeur sortie : Radians
// ----------------------------------------------------------- //
double DEGtoRAD (double Degres)
{
	double Radians;
  Radians = (Degres)*(M_PI/180);
  return Radians;
}

// ----------------------------------------------------------- //
// Unit�valeure d'entr� : Radians
// Type valeur sortie : Degr�
// ----------------------------------------------------------- //
double RADtoDEG (double Radians)
{
  double Degres;
  Degres = (Radians)*(180/M_PI);
  return Degres;
}

// ========================================================================== //
// Conversion des donn�s du fichier (chaine de caract�e) dans la bonne unit�
// pour la structure
// ========================================================================== //
// ----------------------------------------------------------- //
// Unit�valeure d'entr� : H:M:S (Heure:Minute:Seconde)
// Type valeur sortie : Degr�
// ----------------------------------------------------------- //
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

// ----------------------------------------------------------- //
// Unit�valeure d'entr� : H:M:S (Heure:Minute:Seconde)
// Type valeur sortie : Radians
// ----------------------------------------------------------- //
double HMStoRAD (char* TAB)
{
	double Radians;
	Radians=(HMStoDEG(TAB))*(M_PI/180);
	return Radians;
}

// ------------------------------------------------------------ //
// Unit�valeure d'entr� : D:M:S (Degr�:Arcminute:Arcseconde)
// Type valeur sortie : Degr�
// ------------------------------------------------------------ //
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

// ------------------------------------------------------------ //
// Unit�valeure d'entr� : D:M:S (Degr�:Arcminute:Arcseconde)
// Type valeur sortie : Radians
// ------------------------------------------------------------ //
double DMStoRAD (char* TAB)
{
	double Radians;
	Radians=(DMStoDEG(TAB))*(M_PI/180);
	return Radians;
}

// ========================================================================== //
// Conversion des donn�s de la structure en chaine de caract�es pour les
// �rire dans le fichier
// ========================================================================== //
// ----------------------------------------------------------- //
// Ascension droite : DEGRES
// Resultat : CHAINE en DEGRES
// ----------------------------------------------------------- //
char* ASC_DEGtoSTR_DEG (double Valeur)
{
  int i=0;
  int j=0;
  char* Resultat;
  char Temp[8];

  Resultat=(char*)malloc(8*sizeof(char));
  sprintf(Temp, "%.4f", Valeur);

  for (i=0; i<8; i++) Resultat[i]='0';
  for (i=(8-strlen(Temp)); i<8; i++)
    Resultat[i]=Temp[j++];

  return Resultat;
}

// ----------------------------------------------------------- //
// Ascension droite : RADIANS
// Resultat : CHAINE en DEGRES
// ----------------------------------------------------------- //
char* ASC_RADtoSTR_DEG (double Valeur)
{
	Valeur=RADtoDEG(Valeur);
	return ASC_DEGtoSTR_DEG(Valeur);
}

// ----------------------------------------------------------- //
// Ascension droite : DEGRES
// Resultat : CHAINE en HMS
// ----------------------------------------------------------- //
char* ASC_DEGtoSTR_HMS (double Valeur)
{
  float Seconde;
  int Minute;
  int Heure;
  char* Resultat;
  Resultat=(char*)malloc(10*sizeof(char));

  char SECONDE[5];
  char MINUTE[3];
  char HEURE[3];

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

// ----------------------------------------------------------- //
// Ascension droite : RADIANS
// Resultat : CHAINE en HMS
// ----------------------------------------------------------- //
char* ASC_RADtoSTR_HMS (double Valeur)
{
	Valeur=RADtoDEG(Valeur);
	return ASC_DEGtoSTR_HMS(Valeur);
}

// ========================================================================== //
// ----------------------------------------------------------- //
// D�linaison : DEGRES
// Resultat : CHAINE en DEGRES
// ----------------------------------------------------------- //
char* DEC_DEGtoSTR_DEG (double Valeur)
{
  char* Resultat;
  Resultat=(char*)malloc(10*sizeof(char));
  if (Valeur>0) sprintf(Resultat, "+%.4f", Valeur);
	else sprintf(Resultat, "%.4f", Valeur);

  return Resultat;
}

// ----------------------------------------------------------- //
// D�linaison : RADIANS
// Resultat : CHAINE en DEGRES
// ----------------------------------------------------------- //
char* DEC_RADtoSTR_DEG (double Valeur)
{
	Valeur=RADtoDEG(Valeur);
	return DEC_DEGtoSTR_DEG(Valeur);
}

// ----------------------------------------------------------- //
// D�linaison : DEGRES
// Resultat : CHAINE en DMS
// ----------------------------------------------------------- //
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

// ----------------------------------------------------------- //
// D�linaison : RADIANS
// Resultat : CHAINE en DMS
// ----------------------------------------------------------- //
char* DEC_RADtoSTR_DMS (double Valeur)
{
	Valeur=RADtoDEG(Valeur);
	return DEC_DEGtoSTR_DMS(Valeur);
}

// ========================================================================== //
// ----------------------------------------------------------- //
// Redshift : Num�ique
// Resultat : CHAINE
// ----------------------------------------------------------- //
char* REDtoSTR (double Valeur)
{
  char* Resultat;

  Resultat=(char*)malloc(5*sizeof(char));
  sprintf(Resultat, "%.3f", Valeur);

  if (strlen(Resultat)<5) return "";
  else return Resultat;
}

// ========================================================================== //
// ----------------------------------------------------------- //
// Magnitude : Num�ique
// Resultat : CHAINE
// ----------------------------------------------------------- //
char* MAGtoSTR (double Valeur)
{
  char* Resultat;

  Resultat=(char*)malloc(5*sizeof(char));
  sprintf(Resultat, "%.2f", Valeur);

  if (strlen(Resultat)<5) return "";
  else return Resultat;
}
// ========================================================================== //
// Fin
// ========================================================================== //

/* read the data file "filename" and put data in a pointer		*/

void ENTETE (FILE* Fichier, int NBDonnees)
{
	fprintf(Fichier, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(Fichier, "<VOTABLE xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n");
	fprintf(Fichier, " xsi:noNamespaceSchemaLocation=\"http://vizier.u-strasbg.fr/xml/VOTable.xsd\">\n");
	fprintf(Fichier, " <DESCRIPTION>\n");
	fprintf(Fichier, "  VizieR Astronomical Server: cdsweb.u-strasbg.fr 	2003-04-08T17:16:33\n");
	fprintf(Fichier, "  Explanations and Statistics of UCDs:			See LINK below\n");
	fprintf(Fichier, "  In case of problem, please report to:	question@simbad.u-strasbg.fr\n");
	fprintf(Fichier, " </DESCRIPTION>\n\n");
	fprintf(Fichier, "<DEFINITIONS>\n");
	fprintf(Fichier, "  <COOSYS ID=\"J2000\" system=\"eq_FK5\" equinox=\"J2000\"/>\n");
	fprintf(Fichier, "</DEFINITIONS>\n\n");
	fprintf(Fichier, "<INFO ID=\"Ref\" name=\"-ref\" value=\"VOTx11178\" />\n\n");
	fprintf(Fichier, "<RESOURCE ID=\"yCat_7224\" name=\"VII/224\">\n");
  fprintf(Fichier, "  <DESCRIPTION>Quasars and Active Galactic Nuclei (10th Ed.) (Veron+ 2001)</DESCRIPTION>\n");
  fprintf(Fichier, "  <TABLE ID=\"VII_224_table1\" name=\"VII/224/table1\">\n");
  fprintf(Fichier, "    <DESCRIPTION>Quasars (brighter than absolute magnitude -23)</DESCRIPTION>\n");
  fprintf(Fichier, "      <!-- MatchedRows: %d (upper limit) -->\n\n", NBDonnees);
	fprintf(Fichier, "      <!-- Now comes the definition of each field -->\n");
	fprintf(Fichier, "      <FIELD name=\"_RAJ2000\" ucd=\"POS_EQ_RA_MAIN\" ref=\"J2000\" datatype=\"float\" width=\"8\" precision=\"4\" unit=\"deg\">\n");
  fprintf(Fichier, "        <DESCRIPTION>Right ascension (FK5) Equinox=J2000. (computed by VizieR, not part of the original data)</DESCRIPTION>\n");
  fprintf(Fichier, "      </FIELD>\n");
  fprintf(Fichier, "      <FIELD name=\"_DEJ2000\" ucd=\"POS_EQ_DEC_MAIN\" ref=\"J2000\" datatype=\"float\" width=\"8\" precision=\"4\" unit=\"deg\">\n");
  fprintf(Fichier, "        <DESCRIPTION>Declination (FK5) Equinox=J2000. (computed by VizieR, not part of the original data)</DESCRIPTION>\n");
  fprintf(Fichier, "      </FIELD>\n");
  fprintf(Fichier, "      <FIELD name=\"RAJ2000\" ucd=\"POS_EQ_RA_MAIN\" ref=\"J2000\" datatype=\"char\" arraysize=\"10\" unit=\"&quot;h:m:s&quot;\">\n");
  fprintf(Fichier, "        <DESCRIPTION>Right Ascension J2000 (hours) (see also n_RAh)</DESCRIPTION>\n");
  fprintf(Fichier, "        <LINK href=\"http://cdsweb.u-strasbg.fr/viz-bin/VizieR-5?-info=XML&amp;-out.add=.&amp;-source=VII/224/table1&amp;recno=${recno}\"/>\n");
  fprintf(Fichier, "      </FIELD>\n");
  fprintf(Fichier, "      <FIELD name=\"DEJ2000\" ucd=\"POS_EQ_DEC_MAIN\" ref=\"J2000\" datatype=\"char\" arraysize=\"9\" unit=\"&quot;d:m:s&quot;\">\n");
  fprintf(Fichier, "        <DESCRIPTION>Declination J2000 (degrees)</DESCRIPTION>\n");
  fprintf(Fichier, "      </FIELD>\n");
  fprintf(Fichier, "      <FIELD name=\"z\" ucd=\"REDSHIFT_HC\" datatype=\"float\" width=\"6\" precision=\"3\">\n");
  fprintf(Fichier, "        <DESCRIPTION>? redshift</DESCRIPTION>\n");
  fprintf(Fichier, "      </FIELD>\n");
  fprintf(Fichier, "      <FIELD name=\"Vmag\" ucd=\"PHOT_JHN_V\" datatype=\"float\" width=\"5\" precision=\"2\" unit=\"mag\">\n");
  fprintf(Fichier, "        <DESCRIPTION>? magnitude, V or other (see n_Vmag)</DESCRIPTION>\n");
  fprintf(Fichier, "      </FIELD>\n");
  fprintf(Fichier, "      <FIELD name=\"recno\" ucd=\"RECORD\" datatype=\"int\" width=\"8\" type=\"hidden\">\n");
  fprintf(Fichier, "        <DESCRIPTION>Record number within the original table (starting from 1)</DESCRIPTION>\n");
  fprintf(Fichier, "        <LINK href=\"http://cdsweb.u-strasbg.fr/viz-bin/VizieR-5?-info=XML&amp;-out.add=.&amp;-source=VII/224/table1&amp;recno=${recno}\"/>\n");
  fprintf(Fichier, "      </FIELD>\n\n");
	fprintf(Fichier, "<DATA><TABLEDATA>\n");
}

void CONCLUSION (FILE* Fichier, int NBDonnees)
{
	fprintf(Fichier, "</TABLEDATA>\n");
	fprintf(Fichier, "</DATA>\n");
	fprintf(Fichier, "<!-- Result Truncated to %d -->\n", NBDonnees);
	fprintf(Fichier, "  </TABLE>\n");
	fprintf(Fichier, "</RESOURCE>\n");
	fprintf(Fichier, "</VOTABLE>\n");
}

int get_xml_nb_quasar (char* NomFichier)
{
    int NBE=0;
    FILE* FD;
    char* RES;
    char LIGNE[255];

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

int read_xml_quasar (char* NomFichier, Quasar* quasar)
{
	//char C;
	FILE* FD;
	int i=0, k=0, j=0, NBE=0;
	char LIGNE[255], VAL [10], RS [10], MAG [10];
	char mess[64];
	//double AscensionDroite, Declinaison, RedShift, Magnitude;

	FD = fopen(NomFichier, "r");
	if (!FD) return 0;

	//On recherche dans le fichier la ligne contenant l'unique balise <TABLEDATA>
	fgets(LIGNE, 255, FD);
	while(strstr(LIGNE, "<DATA>")==NULL && !feof(FD)) fgets(LIGNE, 255, FD);
	if (feof(FD))
	{
		alerte("XML file corrupted...\n");
		return 0;
	}

	NBE = get_xml_nb_quasar (NomFichier);
	if (!quasar)
	{
		alerte("Memory allocation error for data\n");
		return 0;
	}

	//On r�up�e les donn�s
	while (i<NBE)
	{
		//gtk_progress_bar_set_fraction((GtkProgressBar *) progressbar1,(double) i/NBE);
		//printf("%lf\n",(double) i/NBE);
		//gtk_widget_show(progressbar1);
		fgets(LIGNE, 255, FD);

		//Lecture de l'ascension droite
		j=8;
		while(LIGNE[j]!='<') VAL[k++]=LIGNE[j++];
		VAL[k]='\0';
		/* ---------------------------------------------------------------------- */
		/*                             ATTENTION !!!                              */
		/* ---------------------------------------------------------------------- */
		/* Si on veut lire l'ascension droite quand celle ci est en radians       */
		if(radians)
		{
			quasar[i].ascension=atof(VAL);
		}
		else
		{
		/* Sinon si on veut lire l'ascension droite quand celle ci est ne H:M:S   */
			quasar[i].ascension=HMStoRAD(VAL);
		/* ---------------------------------------------------------------------- */
		}
		//quasar[i].ascension=atof(VAL);
		k=0;

		//Lecture de la d�linaison
		j+=9;
		while(LIGNE[j]!='<') VAL[k++]=LIGNE[j++];
		VAL[k]='\0';
		/* ---------------------------------------------------------------------- */
		/*                             ATTENTION !!!                              */
		/* ---------------------------------------------------------------------- */
		/* Si on veut lire la declinaison quand celle ci est en radians           */
		if(radians)
		{
			quasar[i].declination=atof(VAL);
		}
		/* Sinon si on veut lire la declinaison quand celle ci est ne H:M:S       */
		else
		{
			quasar[i].declination=DMStoRAD(VAL);
		/* ---------------------------------------------------------------------- */
		}
		//quasar[i].declination=atof(VAL);
		k=0;

		//On saute l'ascension droite mesur� en heure
		j+=9;
		while(LIGNE[j]!='<') j++;

		//On saute la d�linaison mesur� en heure
		j+=9;
		while(LIGNE[j]!='<') j++;

		//Lecture du redshift
		j+=9;
		while(LIGNE[j]!='<') RS[k++]=LIGNE[j++];
		RS[k]='\0';
		if (strlen(RS)!=0) quasar[i].redshift=atof(RS);
		else
		{
			sprintf(mess,"REDSHIFT  missing to record %d\n", i+1);
			NBE--;
			data_lenght--;
			alerte(mess);
		}
		k=0;

		//Lecture de la magnitude
		j+=9;
		while(LIGNE[j]!='<') MAG[k++]=LIGNE[j++];
		MAG[k]='\0';
		if (strlen(MAG)!=0) quasar[i].magnitude=atof(MAG);
		else
		{
			sprintf(mess,"MAGNITUDE missing to record n%d\n", i+1);
			//NBE--;
			//data_lenght--;
			alerte(mess);
		}
		k=0;

		i++;
	}
	fclose(FD);
	return NBE;
}

int get_bin_nb_quasar(char* filename)
{
	FILE *data_file;
	char entete[20];

	data_file =fopen(filename,"r");
	if (data_file)
	{
		fscanf(data_file,"%16s\n",entete);
		if ((entete[0]=='Q')&&(entete[2]=='S')&&(entete[4]=='O'))
		{
			fscanf(data_file,"LENGHT=%d\n",&data_size);
			return data_size;
		}
		else
		{
			sprintf(buff,"%s is not a Q.S.O. data file ",filename);
			alerte(buff);
		}
		fclose(data_file);
	}
	else
	{int get_txt_nb_quasar (char *filename);

		sprintf(buff,"\n   Can not open file %s   \n",filename);
		alerte(buff);
	}
	return -1;
}

int read_bin_quasar (char *filename, Quasar * quasar)
{
	FILE *data_file;
	register int count;
	char entete[20];

	data_file =fopen(filename,"r");
	if (data_file)
	{
		fscanf(data_file,"%16s\n",entete);
		if ((entete[0]=='Q')&&(entete[2]=='S')&&(entete[4]=='O'))
		{
			fscanf(data_file,"LENGHT=%d\n",&data_size);
			//quasar = (Quasar *) calloc(data_size,sizeof(Quasar));
			if (quasar)
				for(count=0;count<data_size;count++)
					fread((double *)(quasar+count),sizeof(double),3,data_file);
			else alerte("\n   Memory allocation error for data   \n");
		}
		else
		{
			sprintf(buff,"%s is not a Q.S.O. data file ",filename);
			alerte(buff);
		}
		fclose(data_file);
	}
	else
	{
		sprintf(buff,"\n   Can not open file %s   \n",filename);
		alerte(buff);
	}
	return 0;
}

int get_txt_nb_quasar (char *filename)
{
	FILE *data_file;
	char c;
	register int count=0;
	data_file =fopen(filename,"r");
	if (data_file)
	{
		count=0;
		while(!feof(data_file))
		{
			fscanf(data_file,"%c",&c);
			if(c == '\n')count++;
		}
		rewind(data_file);
	}
	return count;
}


int read_txt_quasar (char *filename,Quasar * quasar)
{
	FILE *data_file;
	char c;
	register int count;
	data_file =fopen(filename,"r");
	if (data_file)
	{
		count=0;
		while(!feof(data_file))
		{
			fscanf(data_file,"%c",&c);
			if(c == '\n')count++;
		}
		rewind(data_file);
		data_size=count;
		if (quasar)
		{
			for(count=0;count<data_size;count++)
			{
				fscanf(data_file,"%lf %lf %lf",&(quasar[count].ascension),&(quasar[count].declination),&(quasar[count].redshift));
			}
		}
		else alerte("\n   Memory allocation error for data   \n");
		fclose(data_file);
	}
	else
	{
		sprintf(buff,"\n   Can not open file %s    \n",filename);
		alerte(buff);
		return 0;
	}
	return 1;
}

void write_bin_quasar (Quasar * q,char *filename)
{
	FILE *data_file;
	register int count;

	data_file =fopen(filename,"w");
	if (data_file)
	{
		fprintf(data_file,"Q.S.O. data file\n");
		fprintf(data_file,"LENGHT=%d\n",data_size);
		if (q)
		   for(count=0;count<data_size;count++)
			fwrite((double *)(q+count),sizeof(double),3,data_file);
		fclose(data_file);
	}
	else
	{
		sprintf(buff,"Can not open file %s ",filename);
		alerte(buff);
	}
}

void  write_txt_quasar (Quasar *q,char *filename)
{
	FILE *data_file;
	register int count;

	data_file =fopen(filename,"w");
	if (data_file)
	{
		if (q)
		   for(count=0;count<data_size;count++)
			fprintf(data_file,"%lf %lf %lf\n",q[count].ascension,
				q[count].declination,q[count].redshift);
		fclose(data_file);
	}
	else
	{
		sprintf(buff,"Can not open file %s ",filename);
		alerte(buff);
	}
}

void write_xml_quasar (Quasar* Q, char* NomFichier)
{
	int i=0;
	FILE* Fichier;
	//char BUF [80];

	Fichier = fopen(NomFichier, "w+");
	if (Fichier)
	{
		if (Q)
		{
			ENTETE(Fichier, data_size);
			for (i=0; i<data_size; i++)
			{
				fprintf(Fichier, "<TR><TD>%s</TD>", ASC_DEGtoSTR_DEG(Q[i].ascension));
				fprintf(Fichier, "<TD>%s</TD>", DEC_DEGtoSTR_DEG(Q[i].declination));
				fprintf(Fichier, "<TD>%s</TD>", ASC_DEGtoSTR_HMS (Q[i].ascension));
        fprintf(Fichier, "<TD>%s</TD>", DEC_DEGtoSTR_DMS(Q[i].declination));
				fprintf(Fichier, "<TD>%s</TD>", REDtoSTR(Q[i].redshift));
        fprintf(Fichier, "<TD>%s</TD>", MAGtoSTR(Q[i].magnitude));
				fprintf(Fichier, "<TD>%d</TD></TR>\n", i+1);
			}
			CONCLUSION (Fichier, data_size);
		}
		fclose(Fichier);
	}
	else printf("Can not create file %s ", NomFichier);
}

void write_ps_quasar(Quasar* q, char* filename)
{
	int i,count=0,nb=0;
	FILE* f;
	Point scale;
	Point* grf;
	int Xmax,Ymax,Xmin,Ymin;
	double radius;


	f=fopen(filename,"w");
	if(f)
	{
		for(i=0;i<NBVIEWS;i++)
		{
			if(vue_is_displayed[i])
			{
				grf=quasar_proj[i];
			}
		}
		scale.x=512/512;   scale.y=512/512;
		Xmin=300-512/2; Ymin=400-512/2;
		Xmax=300+512/2; Ymax=400+512/2;
		radius=0.5/512;

		fprintf(f,"%%!PS-Adobe-2.0 EPSF-2.0%%%%Title:%s\n%%%%Creator: %s\n"
			,data_filename,TITLE);
		fprintf(f,"%%%%BoundingBox: %d %d %d %d\n\n300 400 translate\n"
			,Xmin,Ymin-100,Xmax,Ymax);
		fprintf(f,"%lf %lf scale\n0 setlinewidth\n0 setgray \n/radius %lf def \n"
			,scale.x,scale.y,radius);
		for(i=0;i<data_lenght;i++)
		{
 			if      (((quasar_pos[i].x-256)*scale.x>Xmin-300)
			   &&((quasar_pos[i].x-256)*scale.x<Xmax-300)
			   &&((quasar_pos[i].y-256)*scale.y>Ymin-400)
			   &&((quasar_pos[i].y-256)*scale.y<Ymax-400))
			{
				if((count%250)==0)
				{
					 fprintf(f,"/quasars%d  \n[\n",nb);
					 nb++;
				}
				fprintf(f,"\t%lf  %lf",quasar_pos[i].x-256,quasar_pos[i].y-256);
				if((count%8)==7) fprintf(f,"\n");
				if((count%250)==249) fprintf(f,"\n] def\n\n");
				count++;
			}
		}
		if((count%250)!=0) { fprintf(f,"\n] def\n\n"); }
		for(i=0;i<nb;i++)
		{
			fprintf(f,"0 1 quasars%d length 1 sub 2 idiv  \n{\n\t/count exch def\n\tnewpath\n"
				,i);
			fprintf(f,"\tquasars%d count 2 mul get\n",i);
			fprintf(f,"\tquasars%d  count 2 mul 1 add get\n\tradius 0 360 arc fill\n} for \n"
				,i);
		}
		fprintf(f,"\n%%Draw a frame\n");
		fprintf(f,"\n %lf %lf moveto %lf %lf lineto\n",-200.0/scale.x,-200.0/scale.y,-200.0/scale.x,200.0/scale.y);
		fprintf(f,"\n %lf %lf lineto %lf %lf lineto\n",200.0/scale.x,200.0/scale.y,200.0/scale.x,-200.0/scale.y);
		fprintf(f,"closepath stroke\n\n%% Cosmological constants value and angles\n");
		fprintf(f,"\n/Symbol findfont %lf scalefont setfont\n",35.0/(scale.x+scale.y));
		fprintf(f,"%lf %lf moveto (W = %lf) show\n",-0.9*200.0/scale.x,-1.1*200.0/scale.y,friedman.omega);
		fprintf(f,"%lf %lf moveto (l = %lf) show\n",-0.9*200.0/scale.x,-1.2*200.0/scale.y,friedman.lambda);
		fprintf(f,"%lf %lf moveto (a = %lf) show\n",-0.9*200.0/scale.x,-1.4*200.0/scale.y,friedman.alpha);
		fprintf(f,"0 %lf moveto (d = %lf) show\n",-1.3*200.0/scale.y,declination);
		fprintf(f,"0 %lf moveto (b = %lf) show\n",-1.4*200.0/scale.y,beta);
		fprintf(f,"\n/Times-Roman findfont %lf scalefont setfont\n",35.0/(scale.x+scale.y));
		fprintf(f,"%lf %lf moveto (k = %lf) show\n",-0.9*200.0/scale.x,-1.3*200.0/scale.y,friedman.k);
		fprintf(f,"%lf %lf moveto (Reper:%lf) show\n",-0.1*200.0/scale.x,-1.1*200.0/scale.y,friedman.omega);
		fprintf(f,"0 %lf moveto (a = %lf) show\n",-1.2*200.0/scale.y,ascension);
		fprintf(f,"\n%%Draw the %d quasars\nshowpage\n",count);
		fclose(f);
	}
	else alerte(" Can not open  file. ");
}

/* give the TAU of all QSO in a pointer					*/
void calc_quasar_tau (Quasar *q, Point *graphT)
{
	register int count;
	//Point *graphT;

	bounced=0;
	graphTx_max=abacus_max;
	graphTy_max=PI;
	if(q)
	{
		//if(graphT) free(graphT);
		//graphT=(Point*) calloc(data_lenght+1,sizeof(Point));
		if(graphT)
		{
		   if (friedman.k<0.0)
			for(count=0;count<data_lenght-1;count++)
			  {
				q[count].tau = sqrt(-friedman.k)*earth_codistance(q+count);
				graphT[count].x=q[count].redshift/graphTx_max;
				graphT[count].y=q[count].tau/graphTy_max;

			  }
		   if (friedman.k>0.0)
			for(count=0;count<data_lenght-1;count++)
			  {
				q[count].tau = sqrt(friedman.k)*earth_codistance(q+count);
				graphT[count].x=q[count].redshift/graphTx_max;
				graphT[count].y=q[count].tau/graphTy_max;

			  }
		   if (friedman.k==0.0)
			for(count=0;count<data_lenght-1;count++)
			  {
				q[count].tau = earth_codistance(q+count);
				if (q[count].tau > distance_max) distance_max=q[count].tau;
				graphT[count].x=q[count].redshift/graphTx_max;
				graphT[count].y=q[count].tau/graphTy_max;
			  }
		}
		else alerte("\n   Memory allocation error for plot   \n");
		if(bounced==1) alerte("\n  This universe is bounced !   \n");
	}
}


/*  give the euclidian position of all QSO 			*/

void calc_quasar_pos (Quasar *q, Vector *v)
{
	//register Vector *v=NULL;
	register int count;

	if(q)
	{
		//v = (Vector *) calloc(data_lenght,sizeof(Vector));
		if (v)
		{
			if (friedman.k>0.0)
				for (count=0;count<data_lenght;count++)
					v[count] = Vpos_curv (q+count);
			if (friedman.k<0.0)
				for (count=0;count<data_lenght;count++)
					v[count] = Vneg_curv (q+count);
			if (friedman.k==0.0)
				for (count=0;count<data_lenght;count++)
					v[count] = Vnul_curv (q+count);
		}
		else alerte("\n   Memory allocation error for vectors   \n");
	}
}

/* give the euclidian projection in d1 and d2 vectors of all QSO	*/

void calc_quasar_proj (Vector *v,Vector d1,Vector d2,int offset, Point *p)
{
	//register Point *p=NULL;
	register int count;

	if (friedman.k>=0.0) offset=0;
	if (v)
	{
		//p = (Point *) calloc(data_lenght,sizeof(Point));
		if (p)
		{
			for(count=0;count<data_lenght;count++)
			{
				p[count].x = Vscalar(v[count],d1);
				p[count].y = Vscalar(v[count],d2) + offset*2;
			}
		}
		else alerte("\n   Memory allocation error for points   \n");
	}
}

/* give a virtual QSO by knowing (A,D,TAU) (uses for calculus)		*/

Quasar Qinit(double ascension ,double declination ,double redshift ,double tau)
{
	Quasar q;

	q.ascension=ascension;
	q.declination=declination;
	q.redshift=redshift;
	q.tau=tau;
	return q;
}




