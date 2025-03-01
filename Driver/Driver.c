#define _NO_CRT_STDIO_INLINE

#include "ntos.h"
#include "ntstrsafe.h"
#include <stdio.h>
#include <string.h>
#include <ntifs.h>
#include <ntddk.h>
#include <wdf.h>
#include <wdm.h>

// Request to read virtual user memory (memory of a program) from kernel space
#define IO_READ_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0701 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to write virtual user memory (memory of a program) from kernel space
#define IO_WRITE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0702 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to retrieve the process id of csgo process, from kernel space
#define IO_GET_ID_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0703 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to retrieve the base address of client.dll in csgo.exe from kernel space
#define IO_GET_MODULE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0704 /* Our Custom Code */, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to retrieve the base address of engine.dll in csgo.exe from kernel space
#define IO_GET_ENGINE_REQUEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0708, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to parse offsets
#define IO_PARSE_OFFSETS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0706, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

// Request to get offset value by string
#define IO_GET_OFFSET CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0707, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

typedef struct Offset {
	char name[256];
	int value;
} Offset;
struct Offset* offsets;

PDEVICE_OBJECT pDeviceObject; // our driver object

UNICODE_STRING dev, dos; // Driver registry paths

ULONG csgoId, ClientAddress, EngineAddress;

// datatype for read request
typedef struct _KERNEL_READ_REQUEST
{
	ULONG ProcessId;

	ULONG Address;
	unsigned char Response[1024];
	ULONG Size;

} KERNEL_READ_REQUEST, *PKERNEL_READ_REQUEST;

typedef struct _KERNEL_WRITE_REQUEST
{
	ULONG ProcessId;

	ULONG Address;
	unsigned char Value[1024];
	ULONG Size;

} KERNEL_WRITE_REQUEST, *PKERNEL_WRITE_REQUEST;

typedef struct _KERNEL_PARSE_OFFSETS_REQUEST
{
	int placeholder;
} KERNEL_PARSE_OFFSETS_REQUEST, *PKERNEL_PARSE_OFFSETS_REQUEST;



NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject);
NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP irp);
NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP irp);

void erasechar(char* str, int n, int st) {

	if (st == 1) {
		int len = strlen(str) - n;
		for (int i = strlen(str); i > len; i--) {
			str[i] = 0;
		}
		str[len] = '\0';
	}
	else {
		for (int j = 0; j < n; j++) {
			for (int i = 0; i < strlen(str); i++) {
				str[i] = str[i + 1];
			}
		}
	}
}

void replacechar(char* str, char* find, char* rep, int st) {
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == find[0]) {
			if (st == 1) {
				int len = strlen(str) - 1;
				for (int j = i; j < len; j++) {
					str[j] = str[j + 1];
				}
			}
			else {
				str[i] = rep[0];
			}
		}
	}
}

int containdigit(char* str) {
	int st = 0;
	for (int i = 0; i < strlen(str); i++) {
		if (isdigit(str[i]) != 0) {
			st = 1;
		}
	}
	return st;
}

int my_getnbr(char* str)
{
	int result;
	int puiss;

	result = 0;
	puiss = 1;
	while (('-' == (*str)) || ((*str) == '+'))
	{
		if (*str == '-')
			puiss = puiss * -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		result = (result * 10) + ((*str) - '0');
		str++;
	}
	return (result * puiss);
}

char* mystrtok(char* s, char d)
{
	// Stores the state of string
	static char* input = NULL;

	// Initialize the input string
	if (s != NULL)
		input = s;

	// Case for final token
	if (input == NULL)
		return NULL;

	// Stores the extracted string
	char* result = ExAllocatePool2(POOL_FLAG_PAGED, strlen(input) + 1, 's');
	int i = 0;

	// Start extracting string and
	// store it in array
	for (; input[i] != '\0'; i++) {

		// If delimeter is not reached
		// then add the current character
		// to result[i]
		if (input[i] != d)
			result[i] = input[i];

		// Else store the string formed
		else {
			result[i] = '\0';
			input = input + i + 1;
			return result;
		}
	}

	// Case when loop ends
	result[i] = '\0';
	input = NULL;

	// Return the resultant pointer
	// to the string
	return result;
}

char* mystrtok2(char* s, char d) {
	// Stores the state of string
	static char* input2 = NULL;

	// Initialize the input string
	if (s != NULL)
		input2 = s;

	// Case for final token
	if (input2 == NULL)
		return NULL;

	// Stores the extracted string
	char* result = ExAllocatePool2(POOL_FLAG_PAGED, strlen(input2) + 1, 's');
	int i = 0;

	// Start extracting string and
	// store it in array
	for (; input2[i] != '\0'; i++) {

		// If delimeter is not reached
		// then add the current character
		// to result[i]
		if (input2[i] != d)
			result[i] = input2[i];

		// Else store the string formed
		else {
			result[i] = '\0';
			input2 = input2 + i + 1;
			return result;
		}
	}

	// Case when loop ends
	result[i] = '\0';
	input2 = NULL;

	// Return the resultant pointer
	// to the string
	return result;
}

int my_strcmp(char* s1, char* s2) {
	int st = 1;
	for (int i = 0; i < strlen(s1); i++) {
		if (s2[i] != s1[i]) {
			st = 0;
		}
	}
	return st;
}

void GetOffsets() {
	DbgPrintEx(0, 0, "[hout] Parsing Offsets\n");
	UNICODE_STRING     uniName;
	OBJECT_ATTRIBUTES  objAttr;
	LARGE_INTEGER      byteOffset;
	size_t  cb;

	RtlInitUnicodeString(&uniName, L"\\DosDevices\\C:\\offsets.txt");
	InitializeObjectAttributes(&objAttr, &uniName,
		OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,
		NULL, NULL);
	HANDLE   handle;
	NTSTATUS ntstatus;
	IO_STATUS_BLOCK    ioStatusBlock;

	if (KeGetCurrentIrql() != PASSIVE_LEVEL) return;

	ntstatus = ZwCreateFile(&handle,
		GENERIC_READ,
		&objAttr, &ioStatusBlock,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		0,
		FILE_OPEN,
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL, 0);

	char buffer[8192];

	byteOffset.LowPart = byteOffset.HighPart = 0;
	ntstatus = ZwReadFile(handle, NULL, NULL, NULL, &ioStatusBlock,
		buffer, 8192, &byteOffset, NULL);

	if (NT_SUCCESS(ntstatus)) {
		buffer[8191] = '\0';
	}
	ZwClose(handle);


	offsets = (Offset*)ExAllocatePoolZero(PagedPool, 256 * sizeof(Offset), 'a');

	int lines = 0;
	char line[256];
	char sline[256];

	char* ptr = mystrtok(buffer, '\n');
	RtlStringCbCopyA(line, strlen(ptr), ptr);

	char f[] = "\"";
	char f2[] = " ";
	char f3[] = ",";
	char r[] = "";

	if (containdigit(line) == 1) {
		erasechar(line, 5, 0);
		replacechar(line, f, r, 1);
		replacechar(line, f2, r, 1);
		replacechar(line, f3, r, 0);

		char* name = mystrtok2(line, ':');
		RtlStringCbCopyA(offsets[lines].name, strlen(name) + 1, name);
		while (name != NULL) {
			name = mystrtok2(NULL, ':');
			if (name != NULL) {
				offsets[lines].value = my_getnbr(name);
			}
		}
		lines++;
	}

	while (ptr != NULL) {
		ptr = mystrtok(NULL, '\n');
		if (ptr != NULL) {
			RtlStringCbCopyA(line, strlen(ptr), ptr);
			if (containdigit(line) == 1) {
				erasechar(line, 5, 0);
				replacechar(line, f, r, 1);
				replacechar(line, f2, r, 1);
				replacechar(line, f3, r, 0);

				char* name = mystrtok2(line, ':');
				RtlStringCbCopyA(offsets[lines].name, strlen(name) + 1, name);
				while (name != NULL) {
					name = mystrtok2(NULL, ':');
					if (name != NULL) {
						offsets[lines].value = my_getnbr(name);
					}
				}
				lines++;
			}
		}
		else {
			break;
		}
	}
}

NTSTATUS KeReadVirtualMemory(PEPROCESS Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size)
{
	PSIZE_T Bytes;
	if (NT_SUCCESS(MmCopyVirtualMemory(Process, SourceAddress, PsGetCurrentProcess(),
		TargetAddress, Size, KernelMode, &Bytes)))
		return STATUS_SUCCESS;
	else
		return STATUS_ACCESS_DENIED;
}

NTSTATUS KeWriteVirtualMemory(PEPROCESS Process, PVOID SourceAddress, PVOID TargetAddress, SIZE_T Size)
{
	PSIZE_T Bytes;
	if (NT_SUCCESS(MmCopyVirtualMemory(PsGetCurrentProcess(), SourceAddress, Process,
		TargetAddress, Size, KernelMode, &Bytes)))
		return STATUS_SUCCESS;
	else
		return STATUS_ACCESS_DENIED;
}

// set a callback for every PE image loaded to user memory
// then find the client.dll & csgo.exe using the callback
PLOAD_IMAGE_NOTIFY_ROUTINE ImageLoadCallback(PUNICODE_STRING FullImageName,
	HANDLE ProcessId, PIMAGE_INFO ImageInfo)
{
	// Compare our string to input
	if (wcsstr(FullImageName->Buffer, L"\\csgo\\bin\\client.dll")) {
		// if it matches
		DbgPrintEx(0, 0, "[hout] Loaded To Process: %d \n", ProcessId);

		ClientAddress = ImageInfo->ImageBase;
		csgoId = ProcessId;
	}
	if (wcsstr(FullImageName->Buffer, L"\\bin\\engine.dll")) {
		EngineAddress = ImageInfo->ImageBase;
	}
}

// IOCTL Call Handler function
NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	NTSTATUS Status;
	ULONG BytesIO = 0;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	// Code received from user space
	ULONG ControlCode = stack->Parameters.DeviceIoControl.IoControlCode;

	if (ControlCode == IO_READ_REQUEST)
	{
		// Get the input buffer & format it to our struct
		PKERNEL_READ_REQUEST ReadInput = (PKERNEL_READ_REQUEST)Irp->AssociatedIrp.SystemBuffer;
		PKERNEL_READ_REQUEST ReadOutput = (PKERNEL_READ_REQUEST)Irp->AssociatedIrp.SystemBuffer;

		PEPROCESS Process;
		// Get our process
		if (NT_SUCCESS(PsLookupProcessByProcessId(ReadInput->ProcessId, &Process)))
			KeReadVirtualMemory(Process, ReadInput->Address,
				&ReadInput->Response, ReadInput->Size);


		Status = STATUS_SUCCESS;
		BytesIO = sizeof(KERNEL_READ_REQUEST);
	}
	else if (ControlCode == IO_WRITE_REQUEST)
	{
		// Get the input buffer & format it to our struct
		PKERNEL_WRITE_REQUEST WriteInput = (PKERNEL_WRITE_REQUEST)Irp->AssociatedIrp.SystemBuffer;

		PEPROCESS Process;
		// Get our process
		if (NT_SUCCESS(PsLookupProcessByProcessId(WriteInput->ProcessId, &Process)))
			KeWriteVirtualMemory(Process, &WriteInput->Value,
				WriteInput->Address, WriteInput->Size);

		Status = STATUS_SUCCESS;
		BytesIO = sizeof(KERNEL_WRITE_REQUEST);
	}
	else if (ControlCode == IO_GET_ID_REQUEST)
	{
		PULONG OutPut = (PULONG)Irp->AssociatedIrp.SystemBuffer;
		*OutPut = csgoId;

		DbgPrintEx(0, 0, "[hout] ProcessId is %#010x\n", csgoId);
		Status = STATUS_SUCCESS;
		BytesIO = sizeof(*OutPut);
	}
	else if (ControlCode == IO_GET_MODULE_REQUEST)
	{
		PULONG OutPut = (PULONG)Irp->AssociatedIrp.SystemBuffer;
		*OutPut = ClientAddress;

		DbgPrintEx(0, 0, "[hout] Client Module at %#010x\n", ClientAddress);
		Status = STATUS_SUCCESS;
		BytesIO = sizeof(*OutPut);
	}
	else if (ControlCode == IO_GET_ENGINE_REQUEST) {
		PULONG OutPut = (PULONG)Irp->AssociatedIrp.SystemBuffer;
		*OutPut = EngineAddress;

		DbgPrintEx(0, 0, "[hout] Engine Module at %#010x\n", EngineAddress);
		Status = STATUS_SUCCESS;
		BytesIO = sizeof(*OutPut);
	}
	else if (ControlCode == IO_PARSE_OFFSETS) {
		GetOffsets();
		Status = STATUS_SUCCESS;
	}
	else if (ControlCode == IO_GET_OFFSET) {
		char *Input = (char*)Irp->AssociatedIrp.SystemBuffer;
		int* OutPut = (int*)Irp->AssociatedIrp.SystemBuffer;

		for (int i = 0; i < 256; i++) {
			if (my_strcmp(Input, offsets[i].name) == 1) {
				*OutPut = offsets[i].value;
				break;
			}
		}

		Status = STATUS_SUCCESS;
		BytesIO = sizeof(*OutPut);
	}
	else
	{
		 // if the code is unknown
		Status = STATUS_INVALID_PARAMETER;
		BytesIO = 0;
	}

	// Complete the request
	Irp->IoStatus.Status = Status;
	Irp->IoStatus.Information = BytesIO;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	
	return Status;
}

// Driver Entrypoint
NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject,
	PUNICODE_STRING pRegistryPath)
{
	DbgPrintEx(0, 0, "[hout] Loaded\n");

	PsSetLoadImageNotifyRoutine(ImageLoadCallback);

	RtlInitUnicodeString(&dev, L"\\Device\\kernelhout");
	RtlInitUnicodeString(&dos, L"\\DosDevices\\kernelhout");

	IoCreateDevice(pDriverObject, 0, &dev, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &pDeviceObject);
	IoCreateSymbolicLink(&dos, &dev);

	pDriverObject->MajorFunction[IRP_MJ_CREATE] = CreateCall;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = CloseCall;
	pDriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IoControl;
	pDriverObject->DriverUnload = UnloadDriver;

	pDeviceObject->Flags |= DO_DIRECT_IO;
	pDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}



NTSTATUS UnloadDriver(PDRIVER_OBJECT pDriverObject)
{
	DbgPrintEx(0, 0, "[hout] Unload routine called.\n");
	PsRemoveLoadImageNotifyRoutine(ImageLoadCallback);
	IoDeleteSymbolicLink(&dos);
	IoDeleteDevice(pDriverObject->DeviceObject);
}

NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP irp)
{
	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}
