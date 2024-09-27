#include <windows.h>
#include <string.h>
#include <Lmcons.h>
#include <chrono>
#include <iomanip>
#include <algorithm>	
#include <Madoart.h>
#include <Registry.hpp>
#include <comdef.h>
#include <Wbemidl.h>
#include <stdio.h>
#include <iostream>


#pragma comment(lib, "wbemuuid.lib")
#pragma commnet(lib, "user32.lib")

using namespace m4x1m1l14n::Registry;

std::wstring getusername()
{
	TCHAR username[UNLEN + 1];
	DWORD size = UNLEN + 1;
	GetUserName((TCHAR*)username, &size);
	std::wstring userstring = username;
	return userstring;
}
std::wstring getcomputername()
{
	TCHAR computername[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerName((TCHAR*)computername, &size);
	std::wstring computerstring = computername;
	return computerstring;
}
std::wstring getuptime()
{
	auto uptime = GetTickCount64();
	auto hour = uptime / 360000;
	auto minute = (uptime / 360000) /6000;
	auto seconds = (uptime % 60000) / 1000;
	
	std::wstring ms = std::to_wstring(hour) + L" Hours " + std::to_wstring(minute) + L" Minutes " + std::to_wstring(seconds) + L" Seconds";

	return ms;
}
std::wstring getwiner()
{
	std::wstring winver;
	using namespace m4x1m1l14n;

	try {
		auto key = Registry::LocalMachine->Open(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");

		auto car_bomb = key->GetString(L"ProductName");

		bool win11 = true;
		std::wstring ws = key->GetString(L"CurrentBuild");
		int build = std::stoi(ws);
		if (build > 21999)
		{
			win11 = true;
		}
		else {
			win11 = false;
		}
		if (win11 == true)
		{
			car_bomb = L"Windows 11";
		}
		else {}
		return car_bomb;
	}
	catch (const std::exception& e)
	{
		winver = L"Unknow";
	}
}
std::wstring getwinbuild()
{
	using namespace m4x1m1l14n;
	try {
		auto key = Registry::LocalMachine->Open(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");

		auto buildnum = key->GetString(L"CurrentBuildNumber");

		return buildnum;
	}
	catch (const std::exception& e)
	{
		return L"Unknow Window Build Number";
	}
}
std::wstring getcpu()
{
	using namespace m4x1m1l14n;
	std::wstring cpu;
	
	try {
		auto key = Registry::LocalMachine->Open(L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0");
		cpu = key->GetString(L"ProcessorNameString");

		return cpu;
	}
	catch (const std::exception& e)
	{
		cpu = L"Unknow";
	}
}
ULONGLONG getraminfo(ULONGLONG* totalMemory, ULONGLONG* avaiMemory)
{
	MEMORYSTATUSEX mem;
	mem.dwLength = sizeof(mem);
	
	if (GlobalMemoryStatusEx(&mem))
	{
		if (totalMemory)
		{
			*totalMemory = mem.ullTotalPhys;
			return *totalMemory;
		}
		if (avaiMemory)
		{
			*avaiMemory = mem.ullAvailPhys;
			return *avaiMemory;
		}
	}
	else {
		printf("Error: %d\n", GetLastError());
	}
}
std::wstring getram()
{
	ULONGLONG totalMem = 0;
	ULONGLONG avaiMem = 0;

	getraminfo(&totalMem, &avaiMem);

	ULONGLONG usedMem = totalMem - avaiMem;
	
	

	std::wstring ram = L"Used Ram: " + std::to_wstring(usedMem) + L" / " + L"Total Ram: " + std::to_wstring(totalMem) + L" Bytes";
	return ram;
}
std::wstring getgpu()
{
	for (int i = 0; ; i++)
	{
		DISPLAY_DEVICE dd = { sizeof(dd), 0 };
		BOOL f = EnumDisplayDevices(NULL, i, &dd, EDD_GET_DEVICE_INTERFACE_NAME);
		if (!f)
		{
			break;
		}
		return dd.DeviceString;
	}
}
std::wstring getresolution()
{
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	return std::to_wstring(width) + L"x" + std::to_wstring(height);
}
void magicfetch()
{
	std::wcout << L"Username: " << getusername() << std::endl;
	std::wcout << L"Computername: " << getcomputername() << std::endl;
	std::wcout << L"Win: " << getwiner() << std::endl;
	std::wcout << L"Win build version: " << getwinbuild() << std::endl;
	std::wcout << L"CPU: " << getcpu() << std::endl;
	std::wcout << L"GPU: " << getgpu() << std::endl;
	std::wcout << getram() << std::endl;
	std::wcout << L"Resolution: " << getresolution() << std::endl;
	std::wcout << "Up time: " << getuptime() << std::endl;
}
int main()
{
	magicfetch();
	std::wcout << win10art01 << std::setw(5) << std::endl;
	std::wcout << win10art02 << std::setw(5) << std::endl;
	std::wcout << win10art03 << std::setw(5) << std::endl;
	std::wcout << win10art04 << std::setw(5) << std::endl;
	std::wcout << win10art05 << std::setw(5) << std::endl;
	std::wcout << win10art06 << std::setw(5) << std::endl;
	std::wcout << win10art07 << std::setw(5) << std::endl;
	std::wcout << win10art08 << std::setw(5) << std::endl;
	std::wcout << win10art09 << std::setw(5) << std::endl;
	std::wcout << win10art10 << std::setw(5) << std::endl;
	std::wcout << win10art11 << std::setw(5) << std::endl;
	std::wcout << win10art12 << std::setw(5) << std::endl;
	std::wcout << win10art13 << std::setw(5) << std::endl;
	std::wcout << win10art14 << std::setw(5) << std::endl;
	std::wcout << win10art15 << std::setw(5) << std::endl;
	std::wcout << win10art16 << std::setw(5) << std::endl;
	std::wcout << win10art17 << std::setw(5) << std::endl;
	std::wcout << win10art18 << std::setw(5) << std::endl;
	std::wcout << win10art19 << std::setw(5) << std::endl;
	std::wcout << win10art20 << std::setw(5) << std::endl;


	std::cout << "Ctrl + C to Exit this program..." << std::endl;
	Sleep(100000);
    
}

