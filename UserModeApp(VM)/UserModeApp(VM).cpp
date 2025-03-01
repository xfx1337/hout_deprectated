#include <iostream>
#include <string>
#include <sstream>

#include "KeInterface.h"
//
//std::vector<std::string> names;
//std::vector<std::atomic<bool>&> ptrs;
//
//void bhop(KeInterface Driver, std::atomic<bool> &exit) {
//	
//	while(!exit.load(std::memory_order_relaxed))
//	{	
//		if (GetAsyncKeyState(VK_SPACE))
//		{
//			int Flag = Driver.ReadVirtualMemory<int>(Storage::ProcessId, Storage::LocalPlayer + offsets::netvars::m_fFlags, sizeof(int));
//			if (Flag == 257 || Flag == 263) {
//				Driver.WriteVirtualMemory(Storage::ProcessId, Storage::ClientAddress + offsets::signatures::dwForceJump, 0x5, 8);
//			}
//			else {
//				Driver.WriteVirtualMemory(Storage::ProcessId, Storage::ClientAddress + offsets::signatures::dwForceJump, 0x4, 8);
//			}
//		}
//		Sleep(1);
//	}
//}
//
//void enablehack(KeInterface Driver, std::string hack) {
//	if (hack == "bhop") {
//		std::atomic<bool> exit{ false };
//		std::thread thr(bhop, Driver, exit);
//		names.push_back(hack);
//		ptrs.push_back(exit);
//		thr.detach();
//	}
//}
//
//void disablehack(KeInterface Driver, std::string hack) {
//	if (hack == "bhop") {
//		for (int i = 0; i < names.size(); i++) {
//			if (names.at(i) == "bhop") {
//				auto ptr = &ptrs.at(i);
//				ptr.store(true, std::memory_order_relaxed);
//			}
//		}
//	}
//}


int main()
{
	KeInterface Driver("\\\\.\\kernelhout");

	DWORD ProcessId = Driver.GetTargetPid();
	DWORD ClientAddress = Driver.GetClientModule();
	DWORD LocalPlayer = Driver.ReadVirtualMemory<DWORD>(ProcessId, ClientAddress + offsets::signatures::dwLocalPlayer, sizeof(ULONG));

	std::cout << "Found csgo Process Id: " << ProcessId << std::endl;
	std::cout << "Found client.dll ClientBase: 0x" << std::uppercase
		<< std::hex << ClientAddress << std::endl;
	std::cout << "Found LocalPlayer offsets: 0x" << std::uppercase
		<< std::hex << LocalPlayer << std::endl;
	std::cout << "If you are on map and LocalPlayer offset is 0x0 - update offsets." << std::endl;

	Storage::ClientAddress = ClientAddress;
	Storage::ProcessId = ProcessId;
	Storage::LocalPlayer = LocalPlayer;

	std::string helpmenu = R"(
	h - help menu(this)
	e [hack] - enable hack
	d [hack] - disable hack
	l - load local player(can change every map)
	e - exit
)";

	std::cout << helpmenu << std::endl;

	while (true) {
		std::string cmd;
		std::getline(std::cin, cmd);
		if (cmd.front() == 'h') {
			std::cout << helpmenu;
		}
		else if (cmd.front() == 'e') {
			std::string hack = cmd.substr(2, cmd.size());
			Driver.CallFunction(Storage::ProcessId, hack, 1);
		}
		else if (cmd.front() == 'd') {
			std::string hack = cmd.substr(2, cmd.size());
			Driver.CallFunction(Storage::ProcessId, "bhop", 0);
		}
		else if (cmd.front() == 'l') {
			Storage::LocalPlayer = Driver.ReadVirtualMemory<DWORD>(ProcessId, ClientAddress + offsets::signatures::dwLocalPlayer, sizeof(ULONG));
		}

	}

	return 0;
}

