#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <memory>
#include <string_view>
#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <random>
#include "xor.hpp"
#include "DriverRW.h"
#include "Tools.h"
#include"Offsets.h"
#include"MemProtector.h"
using namespace std;

uintptr_t Pid;
uintptr_t BaseAddress;

struct GlowMode
{
	int8_t GeneralGlowMode, BorderGlowMode, BorderSize, TransparentLevel;
};

DWORD64 GetEntityById(int Ent, DWORD64 Base)
{
	Protect(_ReturnAddress());
	DWORD64 EntityList = Base + TOFFSET(OFFSET_ENTITYLIST);
	DWORD64 BaseEntity = read(EntityList, DWORD64);

	if (!BaseEntity)
		return NULL;

	return read(EntityList + (Ent << 5), DWORD64);
}

int main(int argCount, char** argVector)
{
	Protect(_ReturnAddress());
	srand(time(NULL));
	std::string filePath = argVector[0];
	RenameFile(filePath);
	SetConsoleTitleA(RandomString(20).c_str());


	printf(E("[+] 11  \n"));

	while (!get_process_pid(E("r5apex.exe"))) Sleep(1000);

	Pid = get_process_pid(E("r5apex.exe"));
	printf(E("[+] Pid：%d \n"), Pid);

	if (!kernelHandler.attach("r5apex.exe"))
	{
		MessageBox(0, E("附加到游戏进程失败"), E("错误"), MB_OK | MB_ICONERROR);
		return 1;
	}

	//获取基模块地址
	while (BaseAddress == 0)
	{
		Protect(_ReturnAddress());
		BaseAddress = kernelHandler.get_module_base(E("r5apex.exe"));
		Sleep(1000);
		Unprotect(_ReturnAddress());
	}
	printf(E("[+] BaseAddress：%p \n"), BaseAddress);

	while (true)
	{
		for (int i = 0; i < 10000; i++)
		{
			Protect(_ReturnAddress());
			DWORD64 Entity = GetEntityById(i, BaseAddress);
			if (Entity == 0)
			continue;
			DWORD64 EntityHandle = read(Entity + TOFFSET(OFFSET_NAME), DWORD64); //m_iName
			std::string Identifier = read(EntityHandle, std::string);
			LPCSTR IdentifierC = Identifier.c_str();
			GlowMode glowMode = { 101,101,46,90 };
			if (strcmp(IdentifierC, E("player")))
			{
				Protect(_ReturnAddress());
				write(Entity + TOFFSET(OFFSET_GLOW_ENABLE), 1, int);
				write(Entity + TOFFSET(OFFSET_GLOW_THROUGH_WALLS), 2, int);
				write(Entity + TOFFSET(OFFSET_ITEM_GLOW), glowMode, GlowMode);
				write(Entity + 0x1D0, 61.f, float);
				write(Entity + 0x1D4, 2.f, float);
				write(Entity + 0x1D8, 2.f, float);
				Unprotect(_ReturnAddress());
			}
			Unprotect(_ReturnAddress());
		}
	}
	Unprotect(_ReturnAddress());
}