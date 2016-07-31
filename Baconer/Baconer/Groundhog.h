#ifndef groundhog_h
#define groundhog_h

#include <Windows.h>

class Groundhog {

private:
	//void groundService();		//install as a service
	//void groundAppInit();		//install in appinit key
	//void groundRunKey();		//install in run key
	pigconfig temp;

public:
	Groundhog();
	void getConfig(pigconfig &pgcfg);
	//void setConfig();
	//void setPersistence();
	//~Groundhog();


};

//=================== end declaration =======================//

Groundhog::Groundhog()
{
	printf("-Groundhog initializing.\n");
	//since we dont have reg settings the settings will be static
	ZeroMemory(&temp, sizeof(temp));
	temp.porker_id = PIG_PIN;
	temp.oinkInterval = CALL_DELAY;
	temp.hampost = HAMPOST_IP;
	temp.hamport = HAMPOST_PORT;
}

void Groundhog::getConfig(pigconfig &pgcfg)
{
	pgcfg = temp;
	printf("-Config copied.\n");
}
/*
void Groundhog::setConfig()
{
	//this will change the settings before a reboot
}

void Groundhog::setPersistence()
{
	//based on a task code the persistence can be set
	//each code will correspond to a private function
}

Groundhog::~Groundhog()
{

}
*/


#endif