#include "My_Console.h"

void	PressKey(void)
{
	int ch = 0;
	
	fflush(stdin);
	_tprintf(_TEXT("Please enter a character to exit\n"));
	ch = fgetc(stdin);
}