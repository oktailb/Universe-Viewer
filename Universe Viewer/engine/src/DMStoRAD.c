#include "uv.h"

double DMStoRAD (char* TAB)
{
	double Radians;
	Radians=(DMStoDEG(TAB))*(M_PIl/180);
	return Radians;
}

