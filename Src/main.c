#include "HSM_Lib.h"

int main(void)
{
	InitialiseHSM();
	DisplayHSMBanner();
	if(ChooseOption() != 'M' && ChooseOption() != 'm')
	{
		return 0;
	}
	ClearScreen();

	while(1)
	{
		MenuFunction();
	}
}
