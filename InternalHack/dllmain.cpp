#include <iostream>
#include "windows.h"
#include "Utility/Keys.h"
#include "Utility/PtrChains.h"
#include "Config/Config.h"
#include "Config/ConfigParser.h"


DWORD __stdcall Hack(HMODULE hModule)
{
    // Hijack Console
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "\n======================  INTERNAL HACK INJECTED  ======================" << std::endl;
    std::cout << "Press '8'         Activate speed attack" << std::endl;

    std::cout << "Press '9'         Detach hack from process" << std::endl;
    std::cout << "======================================================================" << "\n" << std::endl;

    uintptr_t pModuleBase = (uintptr_t) GetModuleHandle(NULL); // We get the base from where we are, inside L"ProjectN-Win64-Shipping.exe"

    while (true)
    {
        if (GetAsyncKeyState(KeyPress::VK_8) & 1)
        {
            std::cout << "Internal hack activated!" << std::endl;

            // Config.ini check and parse it's offsets
            std::string filePath = VerifyINI("Hack", "config.ini", { "[Config]", "Attack Speed=" });
            std::string rawAmmoOffs = ReadKey("Config", "Attack Speed", filePath);
            std::vector<unsigned int> ammoOffs = ParseOffsets(rawAmmoOffs);

            // Get pointer chain iteration output
            std::string fileName = GetDesktopPath() + "\\pointerChains.txt";
            std::ofstream fout(fileName);

            // Iterate pointer chain
            uintptr_t pAmmo = FindAddress(pModuleBase, ammoOffs, fout);

            fout.close();

            // Change value
            *(int*) pAmmo = 15000;
        }

        if (GetAsyncKeyState(KeyPress::VK_9) & 1)
        {
            std::cout << "Detaching... " << std::endl;
            Sleep(3000);
            break;
        }
        Sleep(100);
    }

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Hack, hModule, 0, 0));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}