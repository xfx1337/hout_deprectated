#include <Windows.h>

#define IO_CALL_FNC_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0705, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)


// hacks
#define BHOP 0
#define RADAR 1
#define RANKREVEALER 2




typedef struct _KERNEL_CALL_FNC_REQUEST
{
	ULONG ProcessId;

	int Hack;
	int enabled;
} KERNEL_CALL_FNC_REQUEST, * PKERNEL_CALL_FNC_REQUEST;

// interface for our driver
class KeInterface
{
public:
	HANDLE hDriver; // Handle to driver

					// Initializer
	KeInterface(LPCSTR RegistryPath)
	{
		hDriver = CreateFileA(RegistryPath, GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	}


	bool CallFunction(std::string Hack, int enabled) {
		if (hDriver == INVALID_HANDLE_VALUE)
			return false;
		DWORD Bytes;

		KERNEL_CALL_FNC_REQUEST  CallRequest;

		int h = -1;

		if (Hack == "bhop")
			h = BHOP;
		if (Hack == "radar")
			h = RADAR;

		CallRequest.Hack = h;
		CallRequest.enabled = enabled;


		if (DeviceIoControl(hDriver, IO_CALL_FNC_REQUEST, &CallRequest, sizeof(CallRequest),
			0, 0, &Bytes, NULL))
			return true;
		else
			return false;
	}
};
