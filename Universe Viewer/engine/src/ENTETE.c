#include "uv.h"

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
