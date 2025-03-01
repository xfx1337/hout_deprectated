#include <Windows.h>
#include <iostream>

/* IOCTL Codes needed for our driver */

// Request to read virtual user memory (memory of a program) from kernel space
#define IO_READ_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0701 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to write virtual user memory (memory of a program) from kernel space
#define IO_WRITE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0702 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to retrieve the process id of csgo process, from kernel space
#define IO_GET_ID_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0703 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to retrieve the base address of client.dll in csgo.exe from kernel space
#define IO_GET_MODULE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0704 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to get base address of engine.dll
#define IO_GET_ENGINE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0708, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to parse offsets
#define IO_PARSE_OFFSETS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0706, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to get offset value by string
#define IO_GET_OFFSET CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0707, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

typedef struct _KERNEL_READ_REQUEST
{
	ULONG ProcessId;

	ULONG Address;
	unsigned char Response[1024];
	ULONG Size;

} KERNEL_READ_REQUEST, * PKERNEL_READ_REQUEST;

typedef struct _KERNEL_WRITE_REQUEST
{
	ULONG ProcessId;

	ULONG Address;
	unsigned char Value[1024];
	ULONG Size;

} KERNEL_WRITE_REQUEST, * PKERNEL_WRITE_REQUEST;

typedef struct _KERNEL_PARSE_OFFSETS_REQUEST
{
	int placeholder;
} KERNEL_PARSE_OFFSETS_REQUEST, * PKERNEL_PARSE_OFFSETS_REQUEST;


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

	bool ReadVirtualMemory(ULONG ProcessId, ULONG ReadAddress,
		SIZE_T Size, void* Output)
	{
		if (hDriver == INVALID_HANDLE_VALUE)
			return false;

		DWORD Return, Bytes;
		KERNEL_READ_REQUEST ReadRequest;

		ReadRequest.ProcessId = ProcessId;
		ReadRequest.Address = ReadAddress;
		ReadRequest.Size = Size;

		// send code to our driver with the arguments
		if (DeviceIoControl(hDriver, IO_READ_REQUEST, &ReadRequest,
			sizeof(ReadRequest), &ReadRequest, sizeof(ReadRequest), 0, 0)) {
			memcpy(Output, &ReadRequest.Response, Size);
			return true;
		}

		else
			return false;
	}

	DWORD GetOffset(std::string name) {
		char cname[256];

		strcpy_s(cname, sizeof(cname), name.c_str());
		DWORD Bytes;
		int ret;

		if (DeviceIoControl(hDriver, IO_GET_OFFSET, &cname, sizeof(cname),
			&ret, sizeof(ret), &Bytes, NULL)) {
			return (DWORD)ret;
		}
		else
			return false;
	}

	bool WriteVirtualMemoryPTR(ULONG ProcessId, ULONG WriteAddress,
		void* WriteValue, SIZE_T WriteSize)
	{
		if (hDriver == INVALID_HANDLE_VALUE)
			return false;
		DWORD Bytes;

		KERNEL_WRITE_REQUEST  WriteRequest;
		WriteRequest.ProcessId = ProcessId;
		WriteRequest.Address = WriteAddress;
		memcpy(WriteRequest.Value, WriteValue, WriteSize);
		WriteRequest.Size = WriteSize;

		if (DeviceIoControl(hDriver, IO_WRITE_REQUEST, &WriteRequest, sizeof(WriteRequest),
			0, 0, &Bytes, NULL))
			return true;
		else
			return false;
	}

	bool WriteVirtualMemory(ULONG ProcessId, ULONG WriteAddress,
		ULONG WriteValue, SIZE_T WriteSize)
	{
		if (hDriver == INVALID_HANDLE_VALUE)
			return false;
		DWORD Bytes;

		KERNEL_WRITE_REQUEST  WriteRequest;
		WriteRequest.ProcessId = ProcessId;
		WriteRequest.Address = WriteAddress;
		memcpy(WriteRequest.Value, &WriteValue, WriteSize);
		WriteRequest.Size = WriteSize;

		if (DeviceIoControl(hDriver, IO_WRITE_REQUEST, &WriteRequest, sizeof(WriteRequest),
			0, 0, &Bytes, NULL))
			return true;
		else
			return false;
	}

	void ParseOffsets() {
		KERNEL_PARSE_OFFSETS_REQUEST ParseRequest;
		DWORD Bytes;
		ParseRequest.placeholder = 0;

		DeviceIoControl(hDriver, IO_PARSE_OFFSETS, &ParseRequest, sizeof(ParseRequest), 0, 0, &Bytes, NULL);
	}

	DWORD GetTargetPid()
	{
		if (hDriver == INVALID_HANDLE_VALUE)
			return false;

		ULONG Id;
		DWORD Bytes;

		if (DeviceIoControl(hDriver, IO_GET_ID_REQUEST, &Id, sizeof(Id),
			&Id, sizeof(Id), &Bytes, NULL))
			return Id;
		else
			return false;
	}

	DWORD GetClientModule()
	{
		if (hDriver == INVALID_HANDLE_VALUE)
			return false;

		ULONG Address;
		DWORD Bytes;

		if (DeviceIoControl(hDriver, IO_GET_MODULE_REQUEST, &Address, sizeof(Address),
			&Address, sizeof(Address), &Bytes, NULL))
			return Address;
		else
			return false;
	}
	DWORD GetEngineModule()
	{
		if (hDriver == INVALID_HANDLE_VALUE)
			return false;

		ULONG Address;
		DWORD Bytes;

		if (DeviceIoControl(hDriver, IO_GET_ENGINE_REQUEST, &Address, sizeof(Address),
			&Address, sizeof(Address), &Bytes, NULL))
			return Address;
		else
			return false;
	}
};
