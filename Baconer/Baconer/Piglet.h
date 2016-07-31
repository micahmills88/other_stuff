#ifndef piglet_h
#define piglet_h

#include <Windows.h>
#include <tchar.h>

class Piglet {

private:
	HANDLE fileHandle;
	DWORD BytesWritten;
	TCHAR filename[MAX_PATH];
	TCHAR expandfile[MAX_PATH];
	STARTUPINFO si;
    PROCESS_INFORMATION pi;

public:
	Piglet(pigletTask &pgTsk);
	~Piglet();

};

//=================== end declaration =======================//

Piglet::Piglet(pigletTask &pgTsk)
{
	printf("Made it to the piglet!!!!!\n");
	BytesWritten = 0;
	_snwprintf_s(filename, MAX_PATH, L"%%Temp%%\\%ls", pgTsk.TSK.taskName);
	wprintf(L"File will be written to %ls\n", filename);
	ExpandEnvironmentStringsW(filename, expandfile, MAX_PATH);
	wprintf(L"File will be written to %ls\n", expandfile);

	//in the future we will have different types of piglets for each task, or at least a format parser
	//right now lets just get the exe's running
	fileHandle = CreateFile(expandfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(fileHandle, pgTsk.BFFR, pgTsk.TSK.taskSize, &BytesWritten, NULL);
	CloseHandle(fileHandle);
	delete[] pgTsk.BFFR;

	//Now that we have written the file we can start the process.

	ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

	CreateProcess( NULL, expandfile, NULL, NULL, FALSE, DETACHED_PROCESS, NULL, NULL, &si, &pi);
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}

#endif