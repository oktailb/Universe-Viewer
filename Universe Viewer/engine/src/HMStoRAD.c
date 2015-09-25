#include "uv.h"

double HMStoRAD (char* TAB)
{
	double Radians;
	Radians=(HMStoDEG(TAB))*(M_PIl/180);
	return Radians;
}

