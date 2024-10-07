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
#include <locale>
#include <sstream>
#include <string>

// Light color = Light Magenta (pink-ish)
#define setLclr SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13) // Light Magenta
// Dark color = Dark Purple
#define setDclr SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5) // Dark Purple

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
std::wstring gethostname()
{
	TCHAR hostname[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerName((TCHAR*)hostname, &size);
	std::wstring hoststring = hostname;
	return hoststring;
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
	auto hour = uptime / 3600000;
	auto minute = (uptime % 3600000) / 60000;
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

		std::wstring ws = key->GetString(L"DisplayVersion");
		std::wstring result = car_bomb + L"(OS Version " + ws + L")";
		return result;
	}
	catch (const std::exception& e)
	{
		winver = L"Unknow";
	}
}
int CheckWin()
{
	using namespace m4x1m1l14n;
	int iswin11 = 1;
		try {
			auto key = Registry::LocalMachine->Open(L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");
			auto currentBuild = key->GetString(L"CurrentBuildNumber");
			int build = std::stoi(currentBuild);
			if (build < 22000)
			{
				iswin11 = 0;
			}
			else
			{
				iswin11 = 1;
			}
			
		}
		catch (const std::exception& e)
		{
			return 0;
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
//ULONGLONG getraminfo(ULONGLONG totalMemory, ULONGLONG avaiMemory)
//{
//	MEMORYSTATUSEX mem;
//	mem.dwLength = sizeof(mem);
//	
//	GlobalMemoryStatusEx(&mem);
//	
//	if (totalMemory)
//	{
//		totalMemory = mem.ullTotalPhys / 1048576;
//		return totalMemory;
//	}
//	if (avaiMemory)
//	{
//		avaiMemory = totalMemory - (mem.ullAvailPhys / 1048576);
//		return avaiMemory;
//	}
//	
//	/*if (GlobalMemoryStatusEx(&mem))
//	{
//		if (totalMemory)
//		{
//			*totalMemory = mem.ullTotalPhys / 1048576;
//			return *totalMemory;
//		}
//		if (avaiMemory)
//		{
//			*avaiMemory = *totalMemory - (mem.ullAvailPhys / 1048576);
//			return *avaiMemory;
//		}
//	}
//	else {
//		printf("Error: %d\n", GetLastError());
//	}*/
//}

std::wstring getram()
{
	MEMORYSTATUSEX mem;
	mem.dwLength = sizeof(mem);

	GlobalMemoryStatusEx(&mem);

	float totalMem = static_cast<float>((mem.ullTotalPhys)* 0.000000001);
	float avaiMem = static_cast<float>((mem.ullAvailPhys)* 0.000000001);

	

	float usedMem = totalMem - avaiMem;

	/*std::wstring ram = L"Memory:" + std::to_wstring(usedMem) + L"/" + std::to_wstring(totalMem) + L" GB";*/
	std::wstringstream TestRun;
	TestRun << L"Memory: " << std::fixed << std::setprecision(2) << usedMem << L"/" << totalMem << L" GB";
	return TestRun.str();
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
//to debug
void magicfetch()
{
	std::wcout << getusername() << "@" << gethostname() << std::endl;
	std::wcout <<"- - - - - - - - - -" << std::endl;
	std::wcout << L"OS: " << getwiner() << std::endl;
	std::wcout << L"Build: " << getwinbuild() << std::endl;
	std::wcout << L"CPU: " << getcpu() << std::endl;
	std::wcout << L"GPU: " << getgpu() << std::endl;
	std::wcout << getram() << std::endl;
	std::wcout << L"Resolution: " << getresolution() << std::endl;
	std::wcout << "Up time: " << getuptime() << std::endl;
}
int main()
{
	SetConsoleTitle(L"MagicFetch"); 
	setLclr; std::wcout << win10art01 << std::setw(5) << std::endl;
	setLclr; std::wcout << win10art02 << std::setw(5) << getusername() << "@" << gethostname() << std::endl;
	setLclr; std::wcout << win10art03 << std::setw(22) << "- - - - - - - - - -" << std::endl;
	setLclr; std::wcout << win10art04 << std::setw(7) << L"OS: " << getwiner() << std::endl;
	setLclr; std::wcout << win10art05 << std::setw(10) << L"Build: " << getwinbuild() << std::endl;
	setLclr; std::wcout << win10art06 << std::setw(8) << L"CPU: " << getcpu() << std::endl;
	setLclr; std::wcout << win10art07 << std::setw(8) << L"GPU: " << getgpu() << std::endl;
	setLclr; std::wcout << win10art08 << std::setw(24)	<< getram() << std::endl;
	setLclr; std::wcout << win10art09 << std::setw(15) << L"Resolution: " << getresolution() << std::endl;
	setLclr; std::wcout << win10art10 << std::setw(12) << "Up time: " << getuptime() << std::endl;
	setLclr; std::wcout << win10art11 << std::setw(5) << std::endl;
	setLclr; std::wcout << win10art12 << std::setw(5) << std::endl;
	setLclr; std::wcout << win10art13 << std::setw(5) << std::endl;
	setLclr; std::wcout << win10art14 << std::setw(5) << std::endl;
	setLclr; std::wcout << win10art15 << std::setw(5) << std::endl;
	setLclr; std::wcout << win10art16 << std::setw(5) << std::endl;
	setLclr; std::wcout << win10art17 << std::setw(5) << std::endl;
	setLclr; std::wcout << win10art18 << std::setw(5) << std::endl;
	setLclr; std::wcout << win10art19 << std::setw(5) << std::endl;
	setLclr; std::wcout << win10art20 << std::setw(5) << std::endl;


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);


	std::cout << "Ctrl + C to Exit this program..." << std::endl;
	Sleep(100000);
    
}

